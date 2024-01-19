
#ifndef __ProjectMB__MB_MailsOperator__
#define __ProjectMB__MB_MailsOperator__

#include <iostream>
#include "cocos2d.h"
#include "MB_CommonType.h"
#include "MB_MsgBuffer.h"

typedef std::vector<sMailCell*> MailList;

class MB_MailsOperator:public cocos2d::CCObject
{
public:
                    MB_MailsOperator();
    virtual        ~MB_MailsOperator();
public:
    void            insert          (MB_MsgBuffer* recvPacket);
    void            insertHist      (MB_MsgBuffer* recvPacket);
    
    void            remove          (int64_t uid);
    
    void            removeAll       (void);
    
    sMailCell*      query           (int64_t uid);
    
    MailList&       getMails        (void);
    int             getUnReadCount  (void);
    void            setUnReadCout(int unReadCount);
    void            sort            (void);
    
    bool            containsMail    (int64_t uid);
protected:
    static  bool    lowerByTime     ( sMailCell*  elem1, sMailCell*  elem2 );
protected:
    MailList        m_vecMail;
    int             m_unReadCount;
};


#endif /* defined(__ProjectMB__MB_MailsOperator__) */
