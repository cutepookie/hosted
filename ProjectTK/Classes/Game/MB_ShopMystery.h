//
//  MB_ShopMystery.h
//  ProjectTK
//
//  Created by CHK on 14-3-11.
//
//

#ifndef __ProjectMB__MB_ShopMystery__
#define __ProjectMB__MB_ShopMystery__

#include "MB_RoleSoundSystem.h"
#include "MB_FunctionMainWnd.h"
class MB_ShopMain;
class MB_MysteryShopInterface;

class MB_ShopMystery:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
    friend class MB_ShopMain;
    friend class MB_MysteryShopInterface;
    MB_ShopMystery(void);
private:
    
    CCLabelBMFont* m_pRefreshTime;     //刷新时间
    CCLabelBMFont* m_pFreshCount;      //刷新次数
    CCNode * m_pPageNode;           //关联的显示节点
    //
    CCNode* m_pContainerNode;
    bool m_bPlayerRefresh;
    CC_SYNTHESIZE(int, m_nBackFuntion, BackFunction);
    MB_MysteryShopInterface* m_pMysteryShopInterface;
public:
    CREATE_FUNC(MB_ShopMystery);
    virtual ~MB_ShopMystery(void);
    void tickFresh(float dt);
    
    virtual bool init();
    
    virtual bool onAssignCCBMemberVariable (CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector (CCObject * pTarget,const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    void sendshop_buy(uint16_t sellID, uint8_t num,uint8_t cointype,int cost);
    
    void onBuyClicked(CCObject* pSender);
    void onDetailIconClicked(CCObject* pSender);
    void onQuickFreeClick(CCObject* pSender);
    void onCloseClick(CCObject*);
    void onMsgRecv (CCNode*    node, SocketResponse* response);
    void onResetWnd();
    
    void ShowPageNode(bool b);
    virtual void tick(float dt);
};

#endif /* defined(__ProjectMB__MB_ShopMystery__) */
