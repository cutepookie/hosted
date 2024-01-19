
#ifndef ProjectMB_MB_PublicNoticeData_h
#define ProjectMB_MB_PublicNoticeData_h
#include "Game.h"
#include "MB_DateMgr.h"
#include "MB_CommonType.h"


class MB_PublicNoticeData:public MB_DataMgr
{
protected:
                 MB_PublicNoticeData();
    virtual     ~MB_PublicNoticeData();
public:
    //singleton
    static MB_PublicNoticeData* getInstance();
    static void destroyInstance();
    
public:
    //获取公告的标题
    std::string             getTopNotice            (void);
    //获取公告的内容
    std::string             getContentNotice        (void);
    
public:
    void                    sendmessage_notice       (void);
    void                    recvmessage_notice       (MB_MsgBuffer* pbuffer);

protected:
    void                    onMsgRecv         (cocos2d::CCNode *node, cocos2d::extension::SocketResponse *response);

    std::string             getNotice               (uint32_t id);
    uint32_t                getMaxNoticeId          (void);
    
//    void                    saveToXml               (void);
//    void                    loadByXml               (void);
private:
    NoticeMap               m_mapNotice;
    uint32_t                m_topNoticeID;
    uint32_t                m_contentNoticeId;
    CC_SYNTHESIZE_READONLY(uint8_t, m_uNoticePicID, NoticePicID);
};

#define PublicNoticeData MB_PublicNoticeData::getInstance()

#endif
