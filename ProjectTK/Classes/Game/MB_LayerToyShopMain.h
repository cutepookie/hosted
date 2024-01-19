//
//  MB_LayerToyShopMain.h
//  ProjectPM
//
//  Created by CHK on 14-3-14.
//
//

#ifndef __ProjectMB__LayerToyShopMaln__
#define __ProjectMB__LayerToyShopMaln__

#include "MB_LayerScorll.h"
#include "MB_FunctionMainWnd.h"
class MB_NodeCallcardUnit;
class MB_ToyShopInterface;
class MB_LayerToyShopMain:public MB_FunctionMainWnd
{
    enum ECallFun
    {
        kCallPet,
        kCallEquip,
    };
private:
    MB_NodeCallcardUnit*   NodeCallcardUnit;
    CCNode* m_pNodeReward;
    CCNode* m_pShielding;

    CCMenuItemImage*    m_pFunctionPet;
    CCMenuItemImage*    m_pFunctionEquip;
    CCNode* m_pNodeEquip;
    CCNode* m_pNodePet;
    CCNode* m_pNodeEquipContainer;
    CCLabelBMFont* m_pEquipCostItem;
    CCLabelBMFont* m_pEquipCostGlod;
    CCLabelBMFont* m_pEquipSelfItem;
    CCPoint m_equipPos[6];
    CCArray* m_pItemEquipGet;
    CCLabelTTF* m_pLabelRate;
    
    CCControlButton* m_pBtnEquipRefresh;
    CCControlButton* m_pBtnEquipBegin;
public:
    MB_LayerToyShopMain(void);
    void onOnceAgain(CCObject*);
    void onCommit(CCObject*);

    virtual ~MB_LayerToyShopMain(void);
        void goCharge(CCObject*);
    virtual bool onAssignCCBMemberVariable (CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector (CCObject * pTarget,const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    
    void onCallElfClicked(CCObject* pSender);
    void onCallEquipClick(CCObject*);
    void onEquipRefreshClick(CCObject*);
    void onChooseEquip(uint16_t);
    void onFunctionPet(CCObject*);
    void onFunctionEquip(CCObject*);
    void resetItemEquips();
    void shuffleItemEquips();
    
            bool check(int tag,int32_t& shopID);
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    virtual bool init();
    void onResetWnd();
    int m_nSizeWidth;
    void showRewardCard();
    void onExit();
    void onEnterTransitionDidFinish();
private:
    void shuffleItemEquipsComplete();
    void recv_card_draw(MB_MsgBuffer* pRecv);
    void recv_box_shop(MB_MsgBuffer* recvPacket);
    void changeFunction(ECallFun);
    void showShielding();
    void hideShielding();
    void shuffle(int *pArray, unsigned int nLen);
    ECallFun m_nCurFun;
    MB_ToyShopInterface* m_pInterface;

    int     m_nLastTag;
    bool m_bUseItemCall;
    bool isReCreate;
};


#endif /* defined(__ProjectMB__MB_LayerToyShopMain__) */
