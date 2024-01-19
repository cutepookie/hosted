
#ifndef __MB__MB_ShopPay__
#define __MB__MB_ShopPay__

#include "Game.h"
#include "MB_ShopBase.h"

#include "MB_RoleSoundSystem.h"
USING_NS_CC;
USING_NS_CC_EXT;
//充值界面
class MB_ShopMain;


#define OPEN_PAY

class MB_ShopPay:public MB_ShopPageBase
{
    friend class MB_ShopMain;
    
public:
    MB_ShopPay(void);
    virtual ~MB_ShopPay(void);
    
    static MB_ShopPay* create();
    
    virtual bool onAssignCCBMemberVariable (CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
    
    SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void onMsgRecv (CCNode*    node, SocketResponse* response);
    
    void onResetWnd();
    
    virtual bool init();
    
	void refreshGoldPay();
    void onEnter()
    {
        MB_ShopPageBase::onEnter();
        PlayRoleSound(kSoundEnterPay);
    }
    static bool hasFirstPayDouble();
    
    void recv_tencent_pay_check(MB_MsgBuffer* pRecv);
    void recv_appstore_pay_check(MB_MsgBuffer* pRecv);
private:
    void onBuyClicked(CCObject* pSender);   //购买
    void onVipClicked(CCObject* pSender);
    void onCloseClick(CCObject*);
    void initContianer();
    static int  get_int32_pos_bit(int data,int pos);
    CCNode*  m_pRoot;
    CCLabelBMFont*     m_pVipInfo;             //再冲xxxxxxxxx;
    CCLabelBMFont*     m_pVipInfo2;
    CCNode*     m_pVipInfoBg;
    CCNode*     m_pVipInfoBg2;
    
    CCScrollView*   m_pScrollView;
    CCLabelBMFont*      m_pGold;
    CCLabelBMFont*      m_pPrice;
    CCNode*         m_pFirstPay;
    CCControlButton* m_pBuyButton;
    CCSprite*       m_pDoubleRewad;
    CCNode*         m_pFirstPayNode[4];
    CCSize m_cellSize;
    CCNode* m_pYkNode;
    CCNode* m_pBsNode;
};

#endif
