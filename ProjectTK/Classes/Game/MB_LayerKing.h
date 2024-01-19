//
//  MB_LayerKing.h
//  ProjectMB
//
//  Created by yuanwugang on 15-1-14.
//
//

#ifndef __ProjectMB__MB_LayerKing__
#define __ProjectMB__MB_LayerKing__

#include "MB_FunctionModule.h"

class MB_FunctionKingInterface;
class MB_LayerKing : public MB_FunctionMainWnd
{
public:
    MB_LayerKing();
    ~MB_LayerKing();
    CREATE_FUNC(MB_LayerKing);
    virtual bool init();
    void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    bool setDataSource(CCFunctionDataSource* pDataSource);
    
    void sc_king_harm_broadcast(MB_MsgBuffer* pRecv);

    virtual void onEnter();
private:
    void onCloseClicker(CCObject*);
    void onRuleClicked(CCObject*);
    void onFightClicked(CCObject*);
    
    void updataTick(float dt);
    

    void resetBoosInfo();
    void resetBossIcon();
protected:
    CCLabelTTF* m_pTTFLastTimeTitle;
    CCLabelTTF* m_pTTFLastTimeValue;
    CCNode* m_pNodeRevive;
    CCLabelTTF* m_pTTFReviveTime;
    CCSprite* m_pSpriteBoosHead[4];
    CCLabelTTF* m_pTTFBoosName[4];
    CCNode* m_pNodeFightInfo;
    CCLabelTTF* m_pTTFCurBossName;
    CCSprite* m_pSpriteBossHP;
    CCLabelTTF* m_pTTFBossHp;
    CCLabelTTF* m_pTTFReviveMoney;
    CCNode* m_pNodeHarm;
    CCMenuItemImage* m_pBtFight;
    CCProgressTimer* m_pBossHP;
    MB_FunctionKingInterface* m_pFunction;
    bool    m_bFirstEnter;
    bool m_bHasKing;
};

#endif /* defined(__ProjectMB__MB_LayerKing__) */
