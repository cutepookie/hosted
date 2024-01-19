//
//  MB_AbsolvedInterface.h
//  ProjectPM
//
//  Created by WenYong on 14-4-15.
//
//

#ifndef __ProjectMB__MB_AbsolvedInterface__
#define __ProjectMB__MB_AbsolvedInterface__

#include "MB_FunctionModule.h"

class MB_ServerData;
class MB_ChapterProgress;
class MB_MsgBuffer;
class MB_AbsolvedInterface:public NSGameFunction::CCFunctionInterface
{
public:
    MB_AbsolvedInterface();
    ~MB_AbsolvedInterface();
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual void onLoadingScene();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    MB_ChapterProgress* getChapterProgressByType(int nType);
    bool hasPassed(int nDungeonID);
    void sendbattle_progress();
    static void sendbattle_info(uint8_t nType,uint16_t nChapterId);
    static void sendbattle_challenge(uint8_t nType,uint16_t nDungeonID);
    void addPerfectDungeonID(uint16_t id);
    bool isDungeonPerfect(uint16_t id);
    void resetCurrentPageId();
    
    void sendbattle_rank();
    void recvbattle_rank(MB_MsgBuffer* recvPacket);
    CCArray* getRankInfoArray(){return m_pArrayRankInfo;};
protected:
    
    void recvbattle_progress(MB_MsgBuffer* recvPacket);
    
    void recvbattle_info(MB_MsgBuffer* recvPacket);
    
    void recvbattle_challenge(MB_MsgBuffer* recvPacket);
    
    CCArray* m_pChapterProgress;
    
    CC_SYNTHESIZE(int,m_nCurrentType,CurrentType);
    CC_SYNTHESIZE(int, m_nCurrentPage, CurrentPage);
    std::map<uint16_t, uint16_t>    m_vPerfectDungeonID;
    
    
    CCArray*                m_pArrayRankInfo;
};
#endif /* defined(__ProjectMB__MB_AbsolvedInterface__) */
