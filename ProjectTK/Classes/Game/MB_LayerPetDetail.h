//
//  MB_LayerPetDetail.h
//  ProjectMB
//
//  Create by WenYong on 25/9/2014.
//
//
#ifndef __ProjectMB__MB_LayerPetDetail__
#define __ProjectMB__MB_LayerPetDetail__
#include "MB_LocalProto.h"
#include "MB_ResWindow.h"
#include "MB_TeamData.h"
class MB_PetData;
class MB_ItemData;
class MB_LayerPetAttibutes;
class MB_LayerPetDetail : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    CREATE_FUNC(MB_LayerPetDetail);
    static MB_ResWindow* createWithPetID(int64_t petId);
    //参数petType 10进制的最后位表示宠物形态  除最后位表示宠物ID
    static MB_ResWindow* create(int32_t petType,uint16_t shape = 1);
    static MB_LayerPetDetail* create(MB_PetData* pData,bool isSubLayer = false);
    MB_LayerPetDetail();
    virtual ~MB_LayerPetDetail();
    virtual void onResetWnd();
    virtual bool init();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool setData(MB_PetData* pData);
    void resetBaseInfo();
    void onMsgRecv(CCNode* node, SocketResponse* response);
    bool m_bIsSubLayer;
    int m_nZBItemPos;
    MB_PetData* m_pData;
    bool isShowAllBtn;
    void setAllBtnShowFalse();
protected:
    void setItemShow(MB_ItemData* data, int index);
    void setStar(uint8_t nStar);
    void onCloseClick(CCObject* pSender);
    void recvpet_detail(MB_MsgBuffer* pRecv);
    void installAttribute(CCArray* pArray);
    void onJuesejianjieClick(CCObject * pTarget);
    void onJianShangClick(CCObject * pTarget);
    void onLikeClick(CCObject * pTarget);
    bool sendrole_change_head(uint32_t headID);
    void onSkillClick(CCObject * pTarget);
    void onZuHeSkillClick(CCObject * pTarget);
    void onqianghuaClick(CCObject * pTarget);
    void ontiquClick(CCObject * pTarget);
    void onjinhuaClick(CCObject * pTarget);
    void onZidongzhuangbeiClick(CCObject * pTarget);
    void onAndOffBtn();
    void onWeaponClick(CCObject * pTarget);
    void setZhuangBei();
    
private:
    CCNode* m_pMoveEquipNode;
    CCControlButton* m_pZBBtn[EQUIP_MAX];
    CCLabelBMFont*    m_pFightPower;
    CCLabelBMFont*	m_pTextAttack;
    CCLabelBMFont*	m_pTextLife;
    CCLabelBMFont*	m_pTextTalent;
    CCLabelBMFont*    m_pTextTalent2;
    CCSprite*   m_pPetCard;
    CCSprite*	m_pStar[7];
    CCLabelTTF*	m_pTextPetName;
    CCLabelBMFont*	m_pTextLevel;
    CCLabelBMFont*  m_pTextLevelMax;
    CCNode* m_pMoveNode1;
    
    CCNode* m_pNodeTalent;
    CCLabelTTF* m_pTTFDesc;
    CCLabelBMFont* m_pAttribute[14];
    int m_nShowRank;
    CC_SYNTHESIZE(bool,m_bChangeState,ChangeState);
    CCMenuItemImage* m_pJusesejianjie;
    CCNode* m_pNode1;
    CCNode* m_pNode2;
    CCNode* m_pNode3;
    bool isOn;
    CCPoint leftP,rightP;
    CCNode* m_pLeft;
    CCNode* m_pRight;
    CCMenuItemImage* m_pLikeMenu;
    bool isLayerCommandVis;
    uint32_t m_nHeadID;
    bool isUpdateUI;
    TeamDataStruct* tdata;
    
    CCNode* m_pZDZBBtn;
    CCNode* m_pJHBtn;
    CCNode* m_pTQBtn;
    CCNode* m_pQHBtn;
    
};
#endif /* defined(__ProjectMB__MB_LayerPetDetail__) */
