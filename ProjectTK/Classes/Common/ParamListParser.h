

#ifndef __ProjectMB__ParamListParser__
#define __ProjectMB__ParamListParser__

#include <iostream>
#include "cocos2d.h"
#include "MB_MsgBuffer.h"

enum kmParamType
{
    kmParamType_int8    = 241,
    kmParamType_int16   = 242,
    kmParamType_int32   = 243,
    kmParamType_int64   = 244,
    kmParamType_bool    = 245,
    kmParamType_string  = 246,
};


struct paramUint
{
    paramUint(){data = NULL;len = 0;}
    ~paramUint()
    {
    if(len>1)
    {CC_SAFE_DELETE_ARRAY(data);}else\
    {CC_SAFE_DELETE(data);}}
    kmParamType type;
    char*       data;
    int         len;
};

typedef std::vector<paramUint*> param_vec;

/////////////////-param parser-///////////////////////////
class ParamTypeCellParser
{
public:
    virtual int         getSize(MB_MsgBuffer* recvPacket) = 0;
    virtual std::string convertToRbfString(void* data,int len) = 0;
    
    virtual ~ParamTypeCellParser(){}
};


class ParamInt8:public ParamTypeCellParser
{
public:
    virtual int         getSize(MB_MsgBuffer* recvPacket);
    virtual std::string convertToRbfString(void* data,int len);
};


class ParamInt16:public ParamTypeCellParser
{
public:
    virtual int         getSize(MB_MsgBuffer* recvPacket);
    virtual std::string convertToRbfString(void* data,int len);
};


class ParamInt32:public ParamTypeCellParser
{
public:
    virtual int         getSize(MB_MsgBuffer* recvPacket);
    virtual std::string convertToRbfString(void* data,int len);
};

class ParamInt64:public ParamTypeCellParser
{
public:
    virtual int         getSize(MB_MsgBuffer* recvPacket);
    virtual std::string convertToRbfString(void* data,int len);
};


class ParamBool:public ParamTypeCellParser
{
public:
    virtual int         getSize(MB_MsgBuffer* recvPacket);
    virtual std::string convertToRbfString(void* data,int len);
};

class ParamString:public ParamTypeCellParser
{
public:
    virtual int         getSize(MB_MsgBuffer* recvPacket);
    virtual std::string convertToRbfString(void* data,int len);
};



typedef std::map<kmParamType, ParamTypeCellParser*>     paramInfo_Map;
typedef paramInfo_Map::iterator                         paramInfo_It;


////////////////////-ParamCommonObject-/////////////////////////////////
#define ParamSize(type,recvPacket) ParamCommonObject::getInstance().getParamSize(type, recvPacket)
#define ParamToRbf(type,data,len) ParamCommonObject::getInstance().convertParamToRbfString(type,data,len)

class ParamCommonObject
{
public:
    static ParamCommonObject& getInstance()
    {
        static ParamCommonObject inst;
        return inst;
    }
public:
    int         getParamSize(kmParamType type,MB_MsgBuffer* recvPacket);
    std::string convertParamToRbfString(kmParamType type,void* data,int len);
protected:
     ParamCommonObject();
    ~ParamCommonObject();
private:
    paramInfo_Map m_paramInfo;
};

////////////////////////-parser!-//////////////////////////////////////
class ParamListParser
{
public:
                ParamListParser();
    virtual    ~ParamListParser();
public:
    void        parseParamList                  (MB_MsgBuffer* recvPacket);
    param_vec&  getParamList                    (void);
    std::string convertParamToRbfString         (int paramindex);
    std::string calculateNewRbfStrByOldRbfStr   (std::string rbfstring);
    paramUint* getParamAtIndex(int index);
protected:
    kmParamType getParamType                    (MB_MsgBuffer* recvPacket);
    void        removeList                      (void);
    //返回int 非-1為解析完后的位置
    int         parseParamSign                  (const char* str,int pos,int& paramIndex);
    
private:
    param_vec   m_paramList;
};

#endif /* defined(__ProjectMB__ParamListParser__) */
