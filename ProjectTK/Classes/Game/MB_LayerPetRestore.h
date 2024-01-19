//
//  MB_LayerPetRestore.h
//  ProjectPM
//
//  Create by WenYong on 30/5/2014.
//
//
#ifndef __ProjectMB__MB_LayerPetRestore__
#define __ProjectMB__MB_LayerPetRestore__

#include "MB_ResWindow.h"

/*
 // 武将降品
 message     sendpet_down_rank[id=10475]{
 required    int64               srcPetID        =1;//选择降低品阶的武将ID
 }
 
 message     recvpet_down_rank[id=10476]{
 required    int8                result          =1;//0表示成功
 repeated    p_pet_view          add_pet_list    =2;//退化得到的卡牌
 }
 */

#define CS_GER_DOWN_RANK    10475
#define SC_GER_DOWN_RANK    10476

class MB_LayerPetRestore : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
	MB_LayerPetRestore();
    static MB_LayerPetRestore* create(uint64_t uid);
	virtual ~MB_LayerPetRestore();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    static void sendpet_down_rank(uint64_t uid);
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual void onExit();
    void setUid(uint64_t uid);
protected:
    void onCloseClick(CCObject* pSender);
    void onCommitClicked(CCObject* pSender);
    void recvpet_down_rank(MB_MsgBuffer* pRecv);
    void onAnimationFinished();
    void setStars(int nStar);
private:
    bool isHomeButtonShow;
    uint64_t    m_nPetUid;
    CCNode*	m_pPetCard;
    CCLabelTTF*	m_pPetNameSrc;
    CCLabelBMFont*	m_pTextLevelSrc;
    CCLabelBMFont*	m_pTextAttackSrc;
    CCLabelBMFont*	m_pTextLifeSrc;
    CCLabelBMFont*	m_pTextLevelDes;
    CCLabelBMFont*	m_pTextAttackDes;
    CCLabelBMFont*	m_pTextLifeDes;
    CCSprite*	m_pStar[7];
    CCNode*	m_pNodeCommit;
    CCControlButton*	m_pButtonCommit;
    CCNode*	m_pReward;
    CCBAnimationManager*    m_pAnimation;
    bool isUpdateUI;
    CCArray*    m_pRewardArray;
    bool        m_bCanExit;
    CCPoint     m_pStarPt[7];
};
#endif /* defined(__ProjectMB__MB_LayerPetRestore__) */
