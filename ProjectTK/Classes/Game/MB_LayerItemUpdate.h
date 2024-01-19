

#ifndef __ProjectMB__MB_LayerItemUpdate__
#define __ProjectMB__MB_LayerItemUpdate__

#include "Game.h"
#include "MB_NodeItem.h"
#include "MB_LayerRoleInfoHeader.h"
#include "MB_RoleSoundSystem.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define MAX_ATRR_NUM 2
#define MAX_ANIMATION_NUM 5


class MB_LayerItemUpdate: public MB_ResWindow
, public CCBMemberVariableAssigner
, public CCBSelectorResolver
,public MB_NodeItemDelegate
{
    
public:
    MB_LayerItemUpdate();
    ~MB_LayerItemUpdate();
    
    static MB_LayerItemUpdate* create(uint64_t itemUID = 0);
    virtual bool init(uint64_t itemUID);
    
    virtual void onResetWnd();
    void tickParticle(float dt);
    
    void onMsgRecv(CCNode* node, SocketResponse* response);
    
    virtual bool                 onAssignCCBMemberVariable      (CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
    virtual SEL_MenuHandler      onResolveCCBCCMenuItemSelector (CCObject * pTarget,const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector  (CCObject * pTarget,const char* pSelectorName);
    
    void onCloseClick(CCObject* pSender);
    void onClickEnhance(CCObject* pSender);
    void onClickAutoEnhance(CCObject* pSender);
    
    void onRefreshNameAndLevel();
    void onRefreshAtrr();
    void onRefreshCost();
    void onRefreshCard();
    void onRefreshEnhanceButton();
    
    void onRefreshAnimation(int animationLevel);
    void playEnhanceAnimation(void);
    void playEnhancePreAnim();
    
    virtual void onExit();
    void onEnter()
    {
        PlayRoleSound(kSoundEnterLevelUp);
        MB_ResWindow::onEnter();
    }
    void resetItemUID(uint64_t);
private:
    virtual void onClicked(MB_NodeItem* );
    void initEquips();
    CC_SYNTHESIZE(uint64_t, m_uItemUID, ItemUID);
    bool isUpdateUI;
    CCNode*                  m_pPosition;
    CCLabelTTF*              m_pItemName;
    CCLabelBMFont*           m_pItemLevel;
    CCLabelBMFont*           m_pItemLevel2;
    CCLabelBMFont*              m_pItemCost;
    MB_NodeItem*             m_pItemCard;
    CCControlButton*         m_pEnhance;
    CCControlButton*         m_pAutoEnhance;
    CCNode*                  m_pAnimationNode[MAX_ANIMATION_NUM];
    int                      m_animationIndex;
    bool                     m_animateRunning;
    CCBAnimationManager*     m_pAnimationMgr;
    CCLabelTTF* m_pOwerLabel;
    CCNode* m_pNodeEquip[6];
    TeamDataStruct* m_pDataStruct;
    MB_NodeItem* m_pSelectItem;
    int m_nCurSelectItemLevel;
    CCLabelTTF* m_pTextDetailA1_Title;
    CCLabelTTF* m_pTextDetailA2_Title;
    CCLabelBMFont* m_pTextDetailA1;
    CCLabelBMFont* m_pTextDetailA2;
    CCLabelBMFont* m_pTextDetailB1;
    CCLabelBMFont* m_pTextDetailB2;
    CCNode* m_pJianTouA;
    CCNode* m_pJianTouB;
    bool lastShowRoleInfoPanel;
};

#endif /* defined(__ProjectMB__MB_LayerItemUpdate__) */
