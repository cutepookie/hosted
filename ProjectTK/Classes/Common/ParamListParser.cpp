

#include "ParamListParser.h"
#define ParamSignBegin "@("
#define ParamSignEnd   ")@"

///int 8
int ParamInt8::getSize(MB_MsgBuffer* recvPacket)
{
    return sizeof(int8_t);
}

std::string ParamInt8::convertToRbfString(void* data,int len)
{
    char temp[8];
    sprintf(temp,"%d",*((int8_t*)data));
    return temp;
}

///int16
int ParamInt16::getSize(MB_MsgBuffer* recvPacket)
{
    return sizeof(int16_t);
}

std::string ParamInt16::convertToRbfString(void* data,int len)
{
    char    temp[16];
    sprintf(temp,"%d",HTON_I16(*((int16_t*)data)));
    return temp;
}

//int32
int ParamInt32::getSize(MB_MsgBuffer* recvPacket)
{
    return sizeof(int32_t);
}

std::string ParamInt32::convertToRbfString(void* data,int len)
{
    char    temp[16];
    sprintf(temp,"%d",HTON_I32(*((int32_t*)data)));
    return temp;
}

//int64
int ParamInt64::getSize(MB_MsgBuffer* recvPacket)
{
    return sizeof(int64_t);
}

std::string ParamInt64::convertToRbfString(void* data,int len)
{
    char temp[32];
    sprintf(temp,"%lld",HTON_I64(*((int64_t*)data)));
    return temp;
}

//bool
int ParamBool::getSize(MB_MsgBuffer* recvPacket)
{
    return sizeof(bool);
}

std::string ParamBool::convertToRbfString(void* data,int len)
{
    return *((uint8_t*)data)?"true":"false";
}

//string
int ParamString::getSize(MB_MsgBuffer* recvPacket)
{
    uint16_t data16;
    recvPacket->readU16(&data16);
    return data16;
}

std::string ParamString::convertToRbfString(void* data,int len)
{
    std::string ret;
    char* str = new char[len+1];
    memcpy(str, data, len);
    str[len] = 0;
    ret = str;
    return ret;
}


/////////////////////////paramobject//////////////////////////////
ParamCommonObject::ParamCommonObject()
{
    m_paramInfo.clear();
    m_paramInfo.insert(std::make_pair(kmParamType_int8,new ParamInt8()));
    m_paramInfo.insert(std::make_pair(kmParamType_int16,new ParamInt16()));
    m_paramInfo.insert(std::make_pair(kmParamType_int32,new ParamInt32()));
    m_paramInfo.insert(std::make_pair(kmParamType_int64,new ParamInt64()));
    m_paramInfo.insert(std::make_pair(kmParamType_bool,new ParamBool()));
    m_paramInfo.insert(std::make_pair(kmParamType_string,new ParamString()));
}

ParamCommonObject::~ParamCommonObject()
{
    paramInfo_It it;
    it = m_paramInfo.begin();
    while ( it!= m_paramInfo.end())
    {
        delete it->second;
        it++;
    }
    m_paramInfo.clear();
}

int ParamCommonObject::getParamSize(kmParamType type,MB_MsgBuffer* recvPacket)
{
    int ret = 0;
    paramInfo_It finder;
    finder = m_paramInfo.find(type);
    if (finder != m_paramInfo.end())
        ret = finder->second->getSize(recvPacket);
    return ret;
}

std::string ParamCommonObject::convertParamToRbfString(kmParamType type,void* data,int len)
{
    std::string ret = "";
    paramInfo_It finder;
    finder = m_paramInfo.find(type);
    if (finder != m_paramInfo.end())
        ret = finder->second->convertToRbfString(data, len);
    return ret;
}

//////////////////////////-parser!-//////////////////////////////////////

ParamListParser::ParamListParser()
{
    m_paramList.clear();
}

ParamListParser::~ParamListParser()
{
    removeList();
}

void ParamListParser::parseParamList(MB_MsgBuffer* recvPacket)
{
    removeList();
    uint16_t len;
    recvPacket->readU16(&len);
    for (int i = 0; i<len; ++i)
    {
        paramUint* ppU = new paramUint();
        ppU->type = getParamType(recvPacket);
        ppU->len  = ParamSize(ppU->type,recvPacket);
        ppU->data = new char[ppU->len];
        recvPacket->Read(ppU->data, ppU->len);
        m_paramList.push_back(ppU);
    }
    
}

param_vec& ParamListParser::getParamList(void)
{
    return m_paramList;
}

std::string ParamListParser::convertParamToRbfString(int paramindex)
{
    std::string ret = "";
    if (paramindex<m_paramList.size())
    {
        ret = ParamToRbf(m_paramList[paramindex]->type,
                         m_paramList[paramindex]->data,
                         m_paramList[paramindex]->len);
    }
    return ret;
}

std::string ParamListParser::calculateNewRbfStrByOldRbfStr(std::string rbfstring)
{
    std::string retStr;
    retStr = rbfstring;
    if (m_paramList.size())
    {
        int paramindex;
        int ret;
        
        retStr = "";
        
        for (int i = 0; i<rbfstring.length(); ++i)
        {
            ret = parseParamSign(rbfstring.c_str(),i,paramindex);
            if (ret == -1)
            {
                retStr += rbfstring[i];
            }
            else
            {
                i = ret;
                retStr += convertParamToRbfString(paramindex);
//                CCLOG("%s",retStr.c_str());
            }
        }
    }
    return retStr;
}
paramUint* ParamListParser::getParamAtIndex(int index)
{
    if (m_paramList.size()>index)
    {
        return m_paramList[index];
    }
    return NULL;
}
kmParamType ParamListParser::getParamType(MB_MsgBuffer* recvPacket)
{
    uint16_t datahight8 = 0;
    uint8_t  datalow8 = 0;
    recvPacket->readU8(&datahight8);
    if (datahight8 < kmParamType_int8 )
    {
        recvPacket->readU8(&datalow8);
        datahight8 <<= 8;
        datahight8  |= datalow8;
    }
    return (kmParamType)datahight8;
}

void ParamListParser::removeList()
{
    for (int i = 0; i<m_paramList.size(); ++i)
        delete m_paramList[i];
    m_paramList.clear();
}

int ParamListParser::parseParamSign(const char* str,int pos,int &paramIndex)
{
    int ret = -1;
    int beginSignLen = 0;
    int endSignLen = 0;
    int strlen = 0;
    std::string temp = "";
    std::string s = "";
    strlen = std::strlen(str);
    beginSignLen = std::strlen(ParamSignBegin);
    endSignLen   = std::strlen(ParamSignEnd);
    paramIndex   = 0;
    for (int i = 0; i<beginSignLen&&pos<strlen; ++i)
        s += str[pos++];
    
    if (s == ParamSignBegin)
    {
        s = "";
        for (int i = 0; pos<strlen-1; ++i)
        {
            temp = "";
            for (int k = 0; k<endSignLen&&pos<strlen; ++k)
                temp += str[pos+k];
            
            if (temp == ParamSignEnd)
            {
                ret = pos+endSignLen-1;
                paramIndex = atoi(s.c_str());
                break;
            }
            
            s += str[pos++];
        }
    }
    return ret;
}


