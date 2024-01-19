//
//  MB_LayerShopMain.h
//  ProjectMB
//
//  Create by wenyong on 26/11/2014.
//
//
#ifndef __ProjectMB__MB_LayerShopMain__
#define __ProjectMB__MB_LayerShopMain__

#include "MB_ResWindow.h"

class MB_LayerShopMain : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    enum ShopType
    {
        kRefreshShop = 0,//========月卡
        kItemShop,//========道具商城
        kVipShop,//=========vip
        kPayShop,//========充值
        kBerryShop,
        kShopCount,
        kDefaultShop=kRefreshShop,
    };
    CREATE_FUNC(MB_LayerShopMain);
    static MB_LayerShopMain* createRefreshShop();
    static MB_LayerShopMain* createItemShop();
    static MB_LayerShopMain* createVipShop();
    static MB_LayerShopMain* createPayShop();
    static MB_LayerShopMain* createBerryShop();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
	MB_LayerShopMain();
	virtual ~MB_LayerShopMain();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool enterShop(int type);
    void onExit();
    void onEnterTransitionDidFinish();
    bool autoBuy;
protected:
    virtual void onInitialized();
    virtual void switchShop(int type);
    virtual void resetShopPage();
    void onCloseClicked(CCObject* pSender);
    void onVipShopClicked(CCObject* pSender);
    void onItemShopClicked(CCObject* pSender);
    void onRefreshShopClicked(CCObject* pSender);
    void onPayShopCicked(CCObject* pSender);
private:
    CCNode*	m_pNodePageRoot;
    CCNode*             m_pNodeVipPageFlag;
    CCNode*             m_pNodeShopBg;
    CCLabelBMFont*         m_pTextVipFlag;
    int                 m_nCurrentShop;
    CCMenuItemImage*	m_pMenuVipShop;
    CCMenuItemImage*	m_pMenuItemShop;
    CCMenuItemImage*	m_pMenuRefreshShop;
    CCMenuItemImage*	m_pMenuPayShop;
    CCMenuItemImage*    m_pMenuBerryShop;
    CCLabelBMFont*	m_pPageName1;
    CCNode* m_pSelectedSpr;
};
#endif /* defined(__ProjectMB__MB_LayerShopMain__) */
