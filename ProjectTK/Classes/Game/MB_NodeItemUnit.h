
#ifndef __ProjectMB__MB_NodeItemUnit__
#define __ProjectMB__MB_NodeItemUnit__

#include "MB_ResWindow.h"
#include "MB_LocalProto.h"
//#include "CCLabelFX.h"
USING_NS_CC;
USING_NS_CC_EXT;

class MB_NodeItemUnit: public MB_ResWindow
, public CCBMemberVariableAssigner
, public CCBSelectorResolver
{
    
public:
    MB_NodeItemUnit();
    ~MB_NodeItemUnit();
    
    static MB_NodeItemUnit* create(int type = 0, uint64_t itemUID = 0,bool bShowTutorial = false);
    static CCSize getUnitSize();
    virtual bool init(int type, uint64_t itemUID = 0);
    
    virtual void onResetWnd();
    
    void onMsgRecv(CCNode* node, SocketResponse* response);
    
    virtual bool                 onAssignCCBMemberVariable      (CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
    virtual SEL_MenuHandler      onResolveCCBCCMenuItemSelector (CCObject * pTarget,const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector  (CCObject * pTarget,const char* pSelectorName);
    
    void onDetailClicked(CCObject* pSender);
    void onEnhanceClicked(CCObject* pSender);   //装备升品
    void onEnhance2Clicked(CCObject* pSender);  //宝物升品
    void onLevelUpClicked(CCObject* pSender);
    void onSaleClicked(CCObject* pSender);
    void onChangeClicked(CCObject* pSender);
    void onChooseClicked(CCObject* pSender);
    void onOpenClicked(CCObject* pSender);
    void onOpenMoreClicked(CCObject* pSender);
    void onUseClicked(CCObject* pSender);
    void onTreChooseClicked(CCObject* pSender);
    void onInitSelect(bool select);
    void initNormal();
    void tickTime();
    
    bool recvitem_use(MB_MsgBuffer* recvPacket);
    CC_SYNTHESIZE(int, m_kSubType, SubType);
    CC_SYNTHESIZE(uint64_t, m_uItemUID, ItemUID);
    
    void setShowSelect(bool bShow);
private:
    CCNode* m_pNodeChange;
    CCNode* m_pNodeNormal1;
    CCNode* m_pNodeSale;
    CCNode* m_pNodeChoose;
    CCNode* m_pNodeChoose2;
    CCNode* m_pNodeOpenOne;
    CCNode* m_pNodeUse;
    CCNode* m_pNodeIcon;
        CCNode* m_pToLeft1;
    bool m_bShowTutoral;
    
    CCControlButton* m_pBtnOpenMore;
    CCSprite* m_pSpriteType[MAX_ITEM_ATTR];
    CCSprite* m_pStars[MAX_ITEM_STAR];
    CCSprite* m_pSpriteIsChecked;
    CCSprite* m_pSpriteIsChecked2;
    CCLabelTTF* m_pTTFType[MAX_ITEM_ATTR];
    CCLabelTTF* m_pLabelName;
    CCLabelTTF* m_pLabelBeEquip;
    //CCLabelTTF* m_pTTFCoin;
    CCLabelTTF* m_pTTFDescription;
    CCNode* m_pTTFDescriptionBg;
    CCLabelTTF* m_pTTFOverTime;
    CCLabelTTF * m_pExp;
    CCLabelTTF * m_pLastTimes;
    
    CCNode* m_pNodeOpenMore;
//    CCLabelTTF* m_pTTFOpenMore;
    CCNode* m_pNodeOpenNum;
    CCMenuItemImage* m_pBtEquipUp;
    
    CCBAnimationManager* m_pAnimationMgr;
    uint32_t m_uOverTime;
    static CCSize m_cellSizeItem;
};

#endif /* defined(__ProjectMB__MB_NodeItemUnit__) */
