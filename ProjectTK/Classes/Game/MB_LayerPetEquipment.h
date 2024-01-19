

#ifndef __ProjectMB__MB_LayerPetEquipment__
#define __ProjectMB__MB_LayerPetEquipment__

#include "Game.h"
using namespace std;

typedef enum {
    TD_NONE = 0,
    TD_Up_H,
    TD_Up_V,
    TD_Down_H,
    TD_Down_V,
}TOUCHDIC;
class MB_NodePetDuiWu;
class MB_LayerPetEquipment :public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver
,public cocos2d::extension::CCScrollViewDelegate
{
    public :
    
    MB_LayerPetEquipment ();
    ~MB_LayerPetEquipment ();
    
    virtual bool init();
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    static MB_LayerPetEquipment * create();
    virtual void onResetWnd();
    void onEquipClicked(CCObject*);
    
    void onMsgRecv(CCNode* node, SocketResponse* response);
    void setMyTouchEnable(bool b,bool isContainSelf = true);
    
    void updateUI();
    
    bool isPopWindow;
    bool isUpdateUI;
    bool isUpdateYaoLing;
    uint64_t toShowDetailPetUID;
    void sendZhenXing();
    uint8_t isToOnClickGHYSSH;
    void onClickGHYSSH(CCObject* pSender);
    void reloadZhuangbeiIndexVec();
private:
    void onResetAid();
    void ScolltoCenter();

    void onSkillClick(CCObject*);
    void onCloseClick(CCObject* pSender);

    void onClickFHDWLB(CCObject* pSender);
    void onJiBanClick(CCObject* pSender);
    
	bool initFunctions();
	virtual void scrollViewDidScroll(CCScrollView* view);
	virtual void scrollViewDidZoom(CCScrollView* view);
	void movetoShow();
    void reloadArray();
    int insertZhen(uint64_t petId);
    void update(float dt);
    void onClickShangZhen(CCObject*);
    void xiaZhen(bool isCheckEquip = false);
    void onClickDetail(CCObject*);
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void toTiShi(int index);
//   static bool checkInTeam(uint64_t petID);
    void exchangeNpdw(MB_NodePetDuiWu* npdw);
    void setDJSZ(bool b);
    void updateSelectNpdw_Up(float dt);
    void setDetail();
    void finish();
    void onQualityUpClick(CCObject *);
    void onLevelUpClick(CCObject *);

private:
    vector<uint16_t> shouhuPetTypeIDVec;
    vector<uint64_t> lastTeamV;
    int m_nListSize;
    int m_nLength;
    vector<int8_t> zhuangbeiIndexVec;
    CCArray* m_pAllRoleArray;
    CCNode *m_pNodeScroller;
    uint8_t m_nLengthPet;                   //主将数量
    uint8_t m_nLengthEmpty;
    uint8_t m_pLockPos;
    int m_nCMDLength;
    float m_nCmdWidth;
    CCLabelBMFont *m_pAttack;
    CCLabelBMFont *m_pLife;
    CCLabelTTF *m_pPetName;
    CCLabelBMFont* m_pNodeLevel;
    CCLabelBMFont* m_pNodeNowMaxLevel;
    CCLabelBMFont *m_pFightPower;
    CCNode* m_pMoveNode1;
    CCNode *m_pMainPetCmd;
    CCSprite* m_pSpriteGuard;
    CCLabelTTF* m_pTTFAddGuard;
    CCSprite *m_pStar[MAX_GER_STAR];
    CCNode* m_pNodeNaveigation;
	CCScrollView* m_pScollerView;
    vector<CCRect> rectV;
    bool isTouchBlow;
    bool isStartHuiFuDown;
    bool isStartHuiFuUp;
    bool isZuZhiTouch;
    MB_NodePetDuiWu* selectNpdw;
    MB_NodePetDuiWu* selectNpdw_Up;
    CCNode* m_pTestNode;
    CCControlButton* m_pDetail;
    CCControlButton* m_pDJSZ;
    TOUCHDIC isTouchUpOrDown;
    float huiFuSpeedX;
    CCLabelBMFont* m_pItemCount;
    CCNode* m_pNumString;
    CCLabelBMFont* m_pTeamFightPower;
    CCNode* m_pToMoveNode;
    CCNode* m_pToVs2;
    CCNode* m_pFhdwlb;
    CCNode* m_pToVs3;
    CCNode* m_pToVs4;
    CCNode* m_pToMoveNode2;
    CCNode *m_pYlNode[CARD_IN_GAME];
    CCNode* m_pZheZhao;
//    CCLabelTTF* m_pTTFAddGuard;
//    CCLabelTTF* m_pTTFAddGuard;
    
};

#endif /* defined(__ProjectMB__MB_LayerGeneral__) */
