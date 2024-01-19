

#ifndef __ProjectMB__MB_LayerPetEnhance__
#define __ProjectMB__MB_LayerPetEnhance__

#include "Game.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum PetEnhanceEntr {
    kPetEnhanceEntrMain = 0,
    kPetEnhanceEntrDetail,
    kPetEnhanceEntrList,
};
class MB_NodePet;
class MB_NodePetDuiWu;
class MB_LayerPetEnhance : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
,public cocos2d::extension::CCScrollViewDelegate
{
public:
    MB_LayerPetEnhance();
    ~MB_LayerPetEnhance();
    
    static MB_LayerPetEnhance* create(PetEnhanceEntr type = kPetEnhanceEntrMain, uint64_t petID = 0);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(PetEnhanceEntr type, uint64_t petID);
    
    virtual void onResetWnd();
    virtual void onEnter();
    
    void resetPetID(uint64_t petID);
    void resetCostPetID(uint64_t petID);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    void onCloseClicked(CCObject* pSender);
    void onCommitClicked(CCObject* pSender);
    void onGodClicked(CCObject* pSender);
    void onSaintClicked(CCObject* pSender);
    
    void onMsgRecv(CCNode* node, SocketResponse* response);
    bool recvpet_up_rank(MB_MsgBuffer* recvPacket);
    void reloadArray();
    void onCommit();
    void update(float dt);
    MB_PetData* getCosePet(uint64_t PetID,uint16_t PetTypeID);
    //材料排序，Id相同优先 其次品阶升序  等级升序 ID升序
    void sortArray(CCArray* pArray,uint16_t nPetTypeID);
    bool initFunctions();
    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view){};
    void onCommitEnd();
    void ScolltoCenter();
    int insertZhen(uint64_t petId);
private:
    bool m_bRoleInfoHeaderShow;
private:
    int m_pLayerType;
    CCArray* m_pAllRoleArray;
    int m_nListSize;
    CCNode* m_pTestNode;
    PetEnhanceEntr m_nType;
    uint64_t m_uPetID;
    uint64_t m_uPetIDCost;
    CCBAnimationManager* m_pCCBAnimationMgr;
    MB_NodePetDuiWu* selectNpdw;
    bool isHomeButtonShow;
    CCSprite* m_pStar[MAX_GER_STAR];
    CCNode* m_pCard;
    CCSprite* m_pExpBar;
    CCLabelTTF* m_pPetName1;
    CCLabelBMFont* m_pTextLevel1;
    CCLabelBMFont* m_pTextAttack1;
    CCLabelBMFont* m_pTextLife1;
    CCLabelBMFont* m_pTextLevel2;
    CCLabelBMFont* m_pTextAttack2;
    CCLabelBMFont* m_pTextLife2;
    
    CCNode* m_pNodeNaveigation;
    CCScrollView* m_pScollerView;
    CCNode* m_pCostIcon;
    CCLabelTTF* m_pTextCostName;
    CCLabelBMFont* m_pTextCostCoin;
    CCControlButton* m_pButtonCommit;
    MB_NodePet* m_CostPetIcon;
    bool isFirstTouch;
    //一转 二转控件
    CCNode* m_pNodeRankMaxTip;
    CCNode* m_pNodeGod;
    CCNode* m_pNodeSaint;
    bool isUpdateUI;
    CCNode* m_pNodePetCost;
    CCNode* m_pNodeCoinCost;
};

#endif /* defined(__ProjectMB__MB_LayerPetEnhance__) */
