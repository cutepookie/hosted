
#ifndef __ProjectMB__MB_LayerEventChangeCoin__
#define __ProjectMB__MB_LayerEventChangeCoin__
#include "Game.h"
#include "MB_PerfectRaceProtocol.h"
//招财
class MB_LayerEventChangeCoin:public MB_FunctionMainWnd,public MB_RaceRecordDelegate
{
    
private:
    
    CCNode *m_pNodeChange;
    CCLabelBMFont *m_pCanGetMoney;
    CCLabelBMFont *m_pLeftTime;
    CCLabelBMFont *m_pNeedGold;
    CCNode   *m_pNodeTimeOver;
    CCParticleSystemQuad *m_pParticle;
    CCControlButton* m_pChangeBtn;
    CCMenuItemImage* m_pMenuSkip;
    
    public :
    
    MB_LayerEventChangeCoin();
    ~MB_LayerEventChangeCoin();
    virtual bool init();
    static   MB_LayerEventChangeCoin * create();
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onResetWnd(void);
    void onClosedClicked(CCObject*);
    void onChargeClick(CCObject *);
    void onChangeClick(CCObject *);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    void onSkipFightClicked(CCObject*);
    void recvfight_request(MB_MsgBuffer* pRecv);
};

#endif /* defined(__ProjectMB__MB_LayerEventChangeCoin__) */
