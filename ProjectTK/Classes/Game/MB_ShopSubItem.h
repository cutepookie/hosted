
#ifndef ProjectMB_MB_ShopSubItem_h
#define ProjectMB_MB_ShopSubItem_h

#include "Game.h"

#include "MB_LayerBuyNumberInput.h"
class MB_ShopGoodsItem;

class MB_ShopSubItem:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
,public MB_NodeItemDelegate
,public BuyNumberInputDelegate
{
public:
    MB_ShopSubItem();
    virtual ~MB_ShopSubItem();
public:
    static MB_ShopSubItem* create(uint16_t shopID = 0, MB_ShopGoodsItem* pGoodsItem = NULL, int isSpecial = 0,bool bShowTutril = false);
    virtual bool init(uint16_t shopID, MB_ShopGoodsItem* pGoodsItem, int isSpecial);
    virtual bool onAssignCCBMemberVariable (CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_CCControlHandler    onResolveCCBCCControlSelector   (CCObject * pTarget,const char* pSelectorName);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    CCSize getUnitSize() { return m_pNodeSize->getContentSize();}
    virtual void onNumberInputed(int num);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual void onClicked(MB_NodeItem* );
    void onClickBuy10(CCObject* psender);
    void showBuy10(bool b){if(m_pBuy10)m_pBuy10->setVisible(b);}
protected:
    virtual void                    onResetWnd                      (void);
    void                            onClickBuy                      (CCObject* psender);
    void onDetailClicked(CCObject* pSender);
    CCLabelTTF*                     m_pItemName;
    CCLabelTTF*                     m_pItemNum;
    CCLabelBMFont*                  m_pMoney;
    CCLabelBMFont*                  m_pCanBuyTimes;
    CCNode*                         m_pCanBuyTimes2;
    CCSprite*                       m_pMoneyIcon;
    CCNode*                         m_pItemIcon;
    CCControlButton*                m_pBuy;
    CCControlButton*                m_pBuy10;
    CCNode *                        m_pNodeSize;
    CCLabelTTF *                    m_pDiscribe;
    CC_SYNTHESIZE(uint16_t, m_uShopID, ShopID);
    MB_ShopGoodsItem*               m_pShopGoodsItem;
    bool m_bShowTutorial;
};


class MB_VIPShopSubItem: public MB_ShopSubItem
{
public:
    static MB_VIPShopSubItem* create(uint16_t shopID = 0, MB_ShopGoodsItem* pGoodsItem = NULL, int isSpecial = 0,bool bShowTutril = false);
    virtual bool init(uint16_t shopID, MB_ShopGoodsItem* pGoodsItem, int isSpecial);
};

#endif
