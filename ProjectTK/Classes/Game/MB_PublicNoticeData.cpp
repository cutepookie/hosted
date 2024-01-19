

#include "MB_PublicNoticeData.h"
#include "MB_CommonType.h"

MB_PublicNoticeData* s_pPublicNoticeData = NULL;

MB_PublicNoticeData::MB_PublicNoticeData()
{
    SOCKET_MSG_REGIST(SC_MESSAGE_NOTICE,MB_PublicNoticeData);
    m_topNoticeID       = 0;
    m_contentNoticeId   = 0;
    m_uNoticePicID = 0;
}

MB_PublicNoticeData::~MB_PublicNoticeData()
{
    SOCKET_MSG_UNREGIST(SC_MESSAGE_NOTICE);
}

MB_PublicNoticeData* MB_PublicNoticeData::getInstance()
{
    if (s_pPublicNoticeData == NULL) {
        s_pPublicNoticeData = new MB_PublicNoticeData();
    }
    return s_pPublicNoticeData;
}

void MB_PublicNoticeData::destroyInstance()
{
    CC_SAFE_RELEASE(s_pPublicNoticeData);
    s_pPublicNoticeData = NULL;
}

std::string MB_PublicNoticeData::getTopNotice(void)
{
    std::string str = getNotice(m_topNoticeID);
    return str;
}

std::string MB_PublicNoticeData::getContentNotice(void)
{
    std::string str = getNotice(m_contentNoticeId);
    return str;
}

std::string MB_PublicNoticeData::getNotice(uint32_t id)
{
    NoticeMap_It finder;
    finder = m_mapNotice.find(id);
    return finder != m_mapNotice.end()? \
                     finder->second.notice:"";
}

void MB_PublicNoticeData::onMsgRecv(cocos2d::CCNode *node, cocos2d::extension::SocketResponse *response)
{
    assert(response != NULL);
    
    //将socket数据读取到序列化结构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg)
    {
        case SC_MESSAGE_NOTICE:
            recvmessage_notice(recvPacket);
            break;
    }
}

void MB_PublicNoticeData::recvmessage_notice(MB_MsgBuffer* pbuffer)
{
    pbuffer->readU8(&m_uNoticePicID);
    uint16_t    data16;
    uint32_t    data32;
    pbuffer->readU16(&data16);
    if(data16 > 0){
        
        pbuffer->readU32(&data32);
        m_topNoticeID     = data32;
    }
    if(data16 > 1){
       
        pbuffer->readU32(&data32);
        m_contentNoticeId = data32;
    }
    
    pbuffer->readU16(&data16);
    for (int i = 0; i<data16; ++i)
    {
        sNoticeInfo ni;       
        pbuffer->readU32(&data32);
        ni.identity = data32;
        
        char* str = pbuffer->ReadString();
        if (str != NULL)
            CC_SAFE_FREE(str);
        
        str = pbuffer->ReadString();
        if (str != NULL)
        {
            CCLOG("NOTICE:%s",str);
            ni.notice = str;
            CC_SAFE_FREE(str);
        }
        m_mapNotice.insert(std::make_pair(ni.identity, ni));
    }
    
    
    MB_MoneyEevntMgr::getInstance()->recvactivity_get_list(pbuffer);
    pbuffer->readU16(&data16);
    for (int i = 0;i < data16;i++)
    {
        MB_MoneyEevntMgr::getInstance()->recvactivity_info(pbuffer);
    }
    MB_MoneyEevntMgr::getInstance()->recvactivity_get_list2(pbuffer);
   // saveToXml();
    MB_MoneyEevntMgr::getInstance()->recvsort(pbuffer);
    CCNotificationCenter::sharedNotificationCenter()->postNotification("notice_received");
}

void MB_PublicNoticeData::sendmessage_notice(void)
{
    SOCKET_REQUEST_START(CS_MESSAGE_NOTICE);
    packet->writeU32(getMaxNoticeId());
    SOCKET_REQUEST_END(SC_MESSAGE_NOTICE, MB_PublicNotice::onMsgRecv);
}
//
////////////////////////////////////////////////////////////////////////
//
uint32_t MB_PublicNoticeData::getMaxNoticeId()
{
    uint32_t ret = 0;
    NoticeMap_It it;
    it = m_mapNotice.begin();
    while (it != m_mapNotice.end())
    {
        ret = MAX(ret, it->second.identity);
        it++;
    }
    return ret;
}