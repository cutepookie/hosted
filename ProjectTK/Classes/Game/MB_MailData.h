
#ifndef ProjectMB_MB_MailData_h
#define ProjectMB_MB_MailData_h
#include "Game.h"
#include "MB_DateMgr.h"
#include "MB_MailsOperator.h"
class MB_MailData:public CCObject{
public:
                 MB_MailData();
    virtual     ~MB_MailData();

public:
    //singleton
    static MB_MailData* getInstance();
    static void destroyInstance();
    
public:
    //查询总的邮件未读数
    int             queryMailTotalUnRead    (void);
    //查寻某个类型的邮件的未读个数
    int             queryMailUnRead         (kmMailsTable table);
    //查询邮件信息
    sMailCell*      queryMail               (int64_t uid);
    //根据邮件UID查询这封邮件属于什么类型
    kmMailsTable    queryMailTabel          (int64_t uid);
    //查询邮件应以显示的Rbf内容
    std::string     queryMailRbfContent     (int64_t uid);
    std::string     queryMailTitle     (int64_t uid);
    //清楚所有邮件
    void            removeMail              (int64_t uid);
    //获取对应类型的邮件列表
    MailList&       getMails                (kmMailsTable table);
protected:
    //xml字符串不能使用’<‘，所以用{}来替换
    std::string     convertToRbfString      (std::string str);
    
public:
    //请求分页邮件列表
    void            sendmail_info            (kmMailsTable table);
    void            recvmail_info            (MB_MsgBuffer* recvPacket);
 
    //领取奖励邮件
    void            sendmail_draw_reward     (int64_t uid);
    void            recvmail_draw_reward     (MB_MsgBuffer* recvPacket);
    
    //删除邮件
    void            sendmail_delete          (int64_t uid);
    void            recvmail_delete          (MB_MsgBuffer* recvPacket);
    
    //写邮件
    void            sendmail_new             (sNewMail& newMailInfo);
    void            recvmail_new             (MB_MsgBuffer* recvPacket);
    
    //请求未读邮件个数
    void            sendmail_unread_num      (void);
    void            recvmail_unread_num      (MB_MsgBuffer* recvPacket);
    
    //请求更多的邮件
//    void            sendmail_more            (kmMailsTable table);
//    void            recvmail_more            (MB_MsgBuffer* recvPacket);
    
    //系统好友加入请求
    void            sendmail_agree_friend    (int64_t uid);
//    void            recvmail_agree_friend    (MB_MsgBuffer* recvPacket);
    
    void            recvfriend_remove_request(MB_MsgBuffer* recvPacket);
    
    //请求战报
    void            sendhist_get_list        (kmMailsTable table);
    void            recvhist_get_list        (MB_MsgBuffer* recvPacket);
    
    //请求战报
    void            sendhist_more            (kmMailsTable table);
    void            recvhist_more            (MB_MsgBuffer* recvPacket);
    
    //请求重播
    void            sendhist_replay          (kmMailsTable table,uint64_t uid);
    void            recvhist_replay          (MB_MsgBuffer* recvPacket);

    //未读数量增加
    void            recvhist_unreadNum       (MB_MsgBuffer* recvPacket);
    
    MB_MailsOperator* getMailsOperaor(kmMailsTable table){return m_mailsTable[int(table-1)];}
protected:
    //service
    void            onMsgRecv         (CCNode* node, SocketResponse* response);

private:
    MB_MailsOperator*   m_mailsTable[kmMailsTable_Num];
    bool initData[kmMailsTable_Num];
    int64_t             m_currentMailUID;
    uint64_t            m_nReplayID;
    uint8_t             m_nTable;
};

#define MailMgr MB_MailData::getInstance()

#endif
