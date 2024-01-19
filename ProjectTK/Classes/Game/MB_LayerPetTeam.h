

#ifndef __ProjectMB__MB_LayerPetTeam__
#define __ProjectMB__MB_LayerPetTeam__

#include "Game.h"
#include "MB_NodePetTeam.h"

enum PetTeamType{
    
    kPetTeamTypeMain = 0,
    kPetTeamTypeMove,
    kPetTeamTypeUpdate, 
    kPetTeamTypeEnhance,
    kPetTeamTypeEnhanceCost,
    kPetTeamTypeUpdateCost,
    kPetTeamTypeCost,
    kPetTeamTypeEquipment,
    kPetGuardTypeSelect
};

enum PetTeamLimit
{
    kTeamLimit10_4 = 10,
    kTeamLimit20_5 = 20,
    kTeamLimit30_6 = 30,
};

class MB_NodePetCard;

class MB_LayerPetTeam : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
    
private:

    CCLabelBMFont *m_pText_attackCount;
//    CCLabelTTF *m_pText_name[6];
    CCNode *m_pNode[6];
    CCMenuItemImage * m_pItem[6];
//    CCLabelTTF* m_pItemLevel[6];
    MB_NodePetTeam* m_pShowNode[6];
    int m_nCount;
    uint64_t m_nAttackCount;
    CCMenu *m_pMenu;
    int m_nSelItem;
    int m_nTagItem;
    
    int m_nLiSelItem;
    int m_nLiTagItem;
    
    CC_SYNTHESIZE(int ,m_nType ,Type);    
    CCNode* m_pTrigpetMenu;
    CCBAnimationManager* m_pPetAnimMgr;
    int m_nCurIndex;
    
    CCLabelTTF *m_pLock[6];
    CCLabelTTF *m_pAddAttck;
    CCLabelTTF *m_pAddHp;
    CCNode* m_pNodeAid[6];
//    CCNode* m_pLevelBgNode[6];
    bool isShowLock;
    CCSize m_nSize;
//    CCNode *m_pLibox;
//    CCNode *m_pNodeShardow[6];
    
public :
    
    MB_LayerPetTeam();
    ~MB_LayerPetTeam();
    
    virtual bool init(int type);
    virtual void onResetWnd();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    bool isInRect(CCPoint & pos);
    void onPet1ChangeClick(CCObject *);
    void onPet2ChangeClick(CCObject *);
    void onPet3ChangeClick(CCObject *);
    void onPet4ChangeClick(CCObject *);
    void onPet5ChangeClick(CCObject *);
    void onPet6ChangeClick(CCObject *);
    void onTeamClicked(CCObject *);
    void onEquipClicked(CCObject *);
    //trigpet menu
    void onDetailClicked(CCObject*);
    void onEquipClicked2(CCObject *);
    void onLevelClicked(CCObject*);
    void onQualityClicked(CCObject*);
    void onPetClicked(CCObject*);
    void onCloseClicked(CCObject *);
    
    void check_posAndChangeCand(int index);
    void changeCard(int pos, int64_t petId);
    
    void onEnterNodePetList(int layertype,int pos,int type);
    void onEnterLayerGeneralEquipment(int64_t petid);
    void onEnterLayerPetUpdate(int64_t petid, int type);
    void trigpetPet(int index);
    
    CCNode *itemForTouch(CCTouch *touch);
    CCNode *itemForTouchAid(CCTouch *touch);
    static MB_LayerPetTeam * create(int type);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void registerWithTouchDispatcher(void);
    
    bool sendpet_move_pos(uint8_t petPos, uint8_t targetPos);
    bool recvpet_move_pos(MB_MsgBuffer* recvPacket);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    void onRestShow();
};
#endif /* defined(__ProjectMB__MB_LayerPetTeam__) */
