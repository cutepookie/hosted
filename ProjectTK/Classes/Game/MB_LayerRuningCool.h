//
//  MB_LayerRuningCool.h
//  ProjectMB
//
//  Create by wenyong on 26/11/2014.
//
//
#ifndef __ProjectMB__MB_LayerRuningCool__
#define __ProjectMB__MB_LayerRuningCool__

#include "MB_FunctionMainWnd.h"
class MB_NodeRolePKQ;
class MB_AdventureEntry;
class MB_LayerRuningCool : public MB_FunctionMainWnd
{
public:
    CREATE_FUNC(MB_LayerRuningCool);
	MB_LayerRuningCool();
	virtual ~MB_LayerRuningCool();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    virtual void onEnter();
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void onEnterTransitionDidFinish();
protected:
    virtual void onInitialized();
    void updateTick(float dt);
    void onJumpCliked(CCObject* pSender);
    void onJump2Top();
    void recvexplore_one(MB_MsgBuffer* recvPacket);
    void recvrole_up(MB_MsgBuffer* recvPacket);
    void onAotuJumpClicked(CCObject* pSender);
    void resetAutoJump();
    void updateTime();
    void onCloseClick(CCObject* pSender);
    void showAddTimes();
private:
    MB_AdventureEntry* m_pDataSource;
    MB_NodeRolePKQ* m_pRolePKQ;
    CCNode*	m_pNodeRunLand;
    CCSize  m_szWindowSize;
    bool             m_bAutoFishing;
    CCMenuItemImage* m_pAutoFishingItem;
    CCMenuItemImage* m_pAutoFishingImage;
    CCMenu*          m_pAutoFishing;
    CCLabelBMFont*      m_pTextEnableVip;
    CCLabelBMFont*      m_pTextRecover;
    CCLabelBMFont*      m_pTextDiscoveryTimes;
};
#endif /* defined(__ProjectMB__MB_LayerRuningCool__) */
