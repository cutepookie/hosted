
#include "MB_MailsOperator.h"
#include <algorithm>

MB_MailsOperator::MB_MailsOperator()
{
    m_unReadCount = 0;
    m_vecMail.clear();
}

MB_MailsOperator::~MB_MailsOperator()
{
    removeAll();
}

void MB_MailsOperator::insertHist(MB_MsgBuffer *recvPacket)
{
    uint8_t     data8;
    uint16_t    data16;
    uint16_t    len;
    uint32_t    data32;
    uint64_t    data64;
    recvPacket->readU16(&len);
    for(int k = 0;k<len;++k)
    {
        sMailCell* pMailCell = new sMailCell();
        pMailCell->clear();
        
        recvPacket->readU64(&data64);
        pMailCell->mailUID = data64;
        
        recvPacket->readU8(&data8);
        pMailCell->hisType  = data8;
        
        pMailCell->mailType = ((data8>>4)&0x01) == 1? \
                                kmMailType_Pvp: \
                                kmMailType_TreasureRob;
        pMailCell->mailTemplateID = data8;
        char *str;
        str = recvPacket->ReadString();
        if(str)
        {
            pMailCell->senderName = str;
            CC_SAFE_FREE(str);
        }
        
        recvPacket->readU32(&data32);
        pMailCell->senderID = data32;
        
        recvPacket->readU32(&data32);
        pMailCell->time = data32;
        
        recvPacket->readU16(&data16);
        pMailCell->arg = data16;
        
        recvPacket->readU32(&data32);
        pMailCell->addRepu = data32;
        
       // CCAssert(!containsMail(pMailCell->mailUID), "同UID的邮件已经存在了!!!");
        remove(pMailCell->mailUID);
        m_vecMail.push_back(pMailCell);
    }
    sort();
}

void MB_MailsOperator::insert(MB_MsgBuffer *recvPacket)
{
    uint8_t     data8;
    uint16_t    data16;
    uint16_t    len;
    uint32_t    data32;
    uint64_t    data64;
    recvPacket->readU16(&len);
    for(int k = 0;k<len;++k)
    {
        sMailCell* pMailCell = new sMailCell();
        pMailCell->clear();
        
        recvPacket->readU64(&data64);
        pMailCell->mailUID = data64;
        
        recvPacket->readU8(&data8);
        pMailCell->mailType = (kmMailType)data8;
        
        recvPacket->readU32(&data32);
        pMailCell->senderID = data32;
     
        char *str;
        str = recvPacket->ReadString();
        if(str)
        {
            pMailCell->senderName = str;
            CC_SAFE_FREE(str);
        }
        
        str = recvPacket->ReadString();
        if(str)
        {
            pMailCell->content = str;
            CC_SAFE_FREE(str);
        }
        recvPacket->readU32(&data32);
        pMailCell->time = data32;
        
        recvPacket->readU16(&data16);
        pMailCell->mailTemplateID = data16;
        
        pMailCell->paramList.parseParamList(recvPacket);
        
        recvPacket->readU16(&data16);
        if (data16>0)
        {
            uint16_t id;
            uint32_t num;
            
            recvPacket->readU16(&data16);
            for (int i = 0; i<data16; ++i)
            {
                recvPacket->readU16(&id);
                recvPacket->readU32(&num);
                pMailCell->mailReward.ItemRewards.insert(std::make_pair(id,num));
            }
            recvPacket->readU16(&data16);
            for (int i = 0; i<data16; ++i)
            {
                recvPacket->readU16(&id);
                recvPacket->readU32(&num);
                pMailCell->mailReward.PetRewards.insert(std::make_pair(id,num));
            }
        }
        CCAssert(!containsMail(pMailCell->mailUID), "同UID的邮件已经存在了!!!");// 2014.5.16 wy
        remove(pMailCell->mailUID);
        m_vecMail.push_back(pMailCell);
    }
    sort();
}

void MB_MailsOperator::remove(int64_t uid)
{
    for (int i = 0; i<m_vecMail.size(); ++i)
    {
        if (m_vecMail[i]->mailUID == uid)
        {
            delete m_vecMail[i];
            m_vecMail.erase(m_vecMail.begin()+i);
            break;
        }
    }
}

void MB_MailsOperator::removeAll()
{
    for (int i = 0; i<m_vecMail.size(); ++i)
        delete m_vecMail[i];
    m_vecMail.clear();
}

sMailCell* MB_MailsOperator::query(int64_t uid)
{
    sMailCell* ret = NULL;
    for (int i = 0; i<m_vecMail.size(); ++i)
    {
        if (m_vecMail[i]->mailUID == uid)
        {
            ret = m_vecMail[i];
            break;
        }
    }
    return ret;
}

MailList& MB_MailsOperator::getMails()
{
    return m_vecMail;
}

int MB_MailsOperator::getUnReadCount()
{
    return m_unReadCount;
}
void MB_MailsOperator::setUnReadCout(int unReadCount){

    m_unReadCount = unReadCount;
}
bool MB_MailsOperator::containsMail(int64_t uid)
{
    return query(uid)!=NULL;
}

void MB_MailsOperator::sort()
{
    std::sort(m_vecMail.begin(), m_vecMail.end(),lowerByTime);
}

bool MB_MailsOperator::lowerByTime(sMailCell* elem1, sMailCell* elem2)
{
    return elem1->mailUID>=elem2->mailUID;
}