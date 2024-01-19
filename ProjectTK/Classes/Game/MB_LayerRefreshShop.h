//
//  MB_LayerRefreshShop.h
//  ProjectMB
//
//  Create by chk on 5/9/2014.
//
//
#ifndef __ProjectMB__MB_LayerRefreshShop__
#define __ProjectMB__MB_LayerRefreshShop__

//神秘商店
//神秘商店
//神秘商店
//神秘商店


#include "MB_FunctionMainWnd.h"
class MB_Treasure;
class MB_RefreshShopInterface;
class MB_LayerRefreshShop :  public NSGameFunction::CCFunctionWnd,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    static MB_LayerRefreshShop* create();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
	MB_LayerRefreshShop();
	virtual ~MB_LayerRefreshShop();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    void sendshop_treasure_buy(MB_Treasure*);
    void onEnter();
    void onExit();
    void onCloseClick(CCObject*);
    void onQuickFreeClick(CCObject*);
    SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
protected:
    void recvshop_treasure_new_activity();
    void recvshop_treasure_buy(MB_MsgBuffer* recvPacket);
    void tick(float dt);
    
    
private:
    CCNode*	m_pPromotionsNode;
    CCLabelTTF*	m_pTimeTtf;
    CCLabelTTF*	m_pNameTtf;
    CCLabelTTF*	m_pNextRefreshTimeTtf;
    CCLabelTTF*	m_pRefreshTimeTtf;
    CCNode*	m_pContainerNode;
    MB_RefreshShopInterface* m_pInterface;
    CCTableView* m_pTableView;
    CCLabelTTF* m_pFreshCount;
    
    MB_Treasure* m_pCurTreasure;
    bool m_bPlayerRefresh;
};
#endif /* defined(__ProjectMB__MB_LayerRefreshShop__) */