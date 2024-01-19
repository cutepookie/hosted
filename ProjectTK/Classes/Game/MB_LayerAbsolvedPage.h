//
//  MB_LayerAbsolvedPage.h
//  ProjectPM
//
//  Created by WenYong on 14-4-15.
//
//

#ifndef __ProjectMB__MB_LayerAbsolvedPage__
#define __ProjectMB__MB_LayerAbsolvedPage__

#include "MB_LayerHomeFlipDelegate.h"
#include "MB_RoleSoundSystem.h"
class MB_MsgBuffer;
class MB_BattleInfo;
class MB_ChapterInterface;
class MB_LayerAbsolvedPage:public MB_LayerFlipFunctionWnd
{
public:
    MB_LayerAbsolvedPage();
    
    virtual ~MB_LayerAbsolvedPage();
    virtual bool init();

    virtual bool setData(int nType,int nPageId);
    
    virtual void onResetWnd();
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);

    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    
    virtual void onLoadingScene();
    
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    
    int calcChapterStarById(int nChapterId);
    bool queryChapterInterfaceByChapterId(int nChapterId,MB_ChapterInterface** pInterface);
    void selectChapterDiffcuty(int kDiffcutyType);
    void complatePage();
    bool pageExist(int pageId);
    void goChapter(int id);
    virtual void onFlipLeft();
    virtual void onFlipRight();
    bool containChapter(int id);
    
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    void onEnter();
protected:
    void resetChapters();
    bool initChapterInterface();
    
    void onNormalClicked(CCObject* pSender);
    void onHardClicked(CCObject* pSender);
    void onCloseClick(CCObject* pSender);
    
    void removeCurrentPageResource();
    void finish();
    void finish2();
    void finish3();
private:
    CCSprite*   m_pPageBackground;
    int         m_nType;
    int         m_nPageId;
    int         m_nUsedNode;
    bool        m_bPageComplate;
    CCNode*     m_pChapterContainer;
    CCNode*     m_pChapterNode[5];
    CCSprite*     m_pGuanQia_Dian[5];
    

    MB_BattleInfo*  m_CurrentBattleInfo;
    CCArray*    m_pChapterInterfaceList;
    CCNode*     m_pNanDu_putong;
    CCNode*     m_pNanDu_kunnan;
    CCNode*     sceneNode;
    CCNode* m_pGuanPointNode;
};


#endif /* defined(__ProjectMB__MB_LayerAbsolvedPage__) */
