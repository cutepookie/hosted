//
//  MB_ChapterInterface.h
//  ProjectPM
//
//  Created by WenYong on 14-4-16.
//
//

#ifndef __ProjectMB__MB_ChapterInterface__
#define __ProjectMB__MB_ChapterInterface__

#include "MB_FunctionModule.h"
class MB_LayerAbsolvedPage;
class MB_ChapterProgress;
class MB_ChapterData;
class MB_BattleInfo;
class MB_ChapterPage;
class MB_ChapterInterface:public NSGameFunction::CCFunctionInterface
{
public:
    //static MB_ChapterInterface* create(int nType,int nPage,int nChapterId);
    MB_ChapterInterface();
    ~MB_ChapterInterface();
    //virtual bool init(int nType,int nPage,int nChapterId);
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual void onLoadingScene();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual bool allowShow();
    virtual void onEntryClicked(CCObject* pSender);
    MB_ChapterProgress* getChapterProgress();
    MB_ChapterData* getChapterData();
    int getChapterStar();
    MB_BattleInfo* getBattleInfo();
    void recvbattle_info(MB_MsgBuffer* recvPacket);
    MB_ChapterPage* getChapterPage();
    friend class MB_AbsolvedConfigure;
    bool hasRequestedData();
    bool enterChapter();
    bool complated();
    bool isProgressPage();
private:
    CC_SYNTHESIZE_READONLY(int, m_nType, Type);
    CC_SYNTHESIZE_READONLY(int, m_nChapterId, ChapterId);
    CC_SYNTHESIZE_READONLY(int, m_nPageId, PageId);
    
    // request once. will be updated dynamic
    MB_BattleInfo*          m_pBattleInfo;
};
#endif /* defined(__ProjectMB__MB_ChapterInterface__) */
