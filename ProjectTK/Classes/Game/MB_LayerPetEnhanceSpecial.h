
//

#ifndef __ProjectMB__MB_LayerPetEnhanceSpecial__
#define __ProjectMB__MB_LayerPetEnhanceSpecial__

#include "Game.h"

USING_NS_CC;
USING_NS_CC_EXT;


#define MAX_ITEM_RANKGOD 4


class MB_LayerPetEnhanceSpecial : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_LayerPetEnhanceSpecial();
    ~MB_LayerPetEnhanceSpecial();
    
    static MB_LayerPetEnhanceSpecial* create(uint64_t petID = 0);
    
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(uint64_t petID);
    
    virtual void onResetWnd();
    
    void resetPetID(uint64_t petID);
    void resetCostPetID(uint64_t petID);
	
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    void onCloseClick(CCObject* pSender);
    void onRankClicked(CCObject* pSender);
    void onGodClicked(CCObject* pSender);
    void onSaintClicked(CCObject* pSender);
   
    void onMsgRecv(CCNode* node, SocketResponse* response);
    bool recvpet_up_rank(MB_MsgBuffer* recvPacket);

    void OnAnimationOver();
    void onExit();
    virtual void onEnter();

private:
    bool m_bRoleInfoHeaderShow;
private:

    uint64_t m_uPetID;
    
    CCBAnimationManager* m_pCCBAnimationMgr;
    
    CCNode* m_pCard;
    CCLabelBMFont* m_pTTFLevel1;
    CCLabelBMFont* m_pTTFLevel2;
    CCLabelBMFont* m_pTTFAttack1;
    CCLabelBMFont* m_pTTFAttack2;
    CCLabelBMFont* m_pTTFLife1;
    CCLabelBMFont* m_pTTFLife2;
    CCSprite* m_pStar[MAX_GER_STAR];
    CCLabelTTF* m_pPetName1;
    CCNode* m_pCostIcon[MAX_ITEM_RANKGOD];
    CCLabelTTF* m_pTextCostName[MAX_ITEM_RANKGOD];
    CCNode* m_pNodeCover[MAX_ITEM_RANKGOD];
     CCNode* m_pNodeCost[MAX_ITEM_RANKGOD];
    CCControlButton* m_pButtonCommit;
    
    //一转 二转控件
    CCNode* m_pNodeRank;
    CCNode* m_pNodeRankMaxTip;
    CCNode* m_pNodeGod;
    CCNode* m_pNodeSaint;
    
    int m_nNowShape;
    int m_nNextShape;
    bool isUpdateUI;
    
};

#endif /* defined(__ProjectMB__MB_LayerPetEnhanceSpecial__) */
