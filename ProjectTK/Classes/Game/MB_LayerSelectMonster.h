//
//  MB_LayerSelectMonster.h
//  ProjectPM
//
//  Created by WenYong on 14-3-25.
//
//

#ifndef __ProjectMB__MB_LayerSelectMonster__
#define __ProjectMB__MB_LayerSelectMonster__

#include "MB_ResWindow.h"

class MB_LayerSelectMonster:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    static CCScene* scene();
    MB_LayerSelectMonster();
    virtual ~MB_LayerSelectMonster();
    virtual bool init();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    CREATE_FUNC(MB_LayerSelectMonster);
    
    void onMonsterSelectConfirmed(uint16_t index);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    
protected:
    bool initConfig();
    void onEnterClicked(CCObject* pSender);
    void onCloseClick(CCObject* pSender);
    void onMonsterOneClicked(CCObject* pSender);
    void onMonsterTwoClicked(CCObject* pSender);
    void onMonsterThreeClicked(CCObject* pSender);
    bool sendrole_select_pet(uint16_t uid);
    bool recvrole_select_pet(MB_MsgBuffer *recvPacket);
    void recv_role_demo_fight(MB_MsgBuffer* pRecv);
    void setShow();
private:
    CCScale9Sprite* m_pSpriteNameBG[3];
    CCScale9Sprite* m_pSpriteBG[3];
    CCSprite* m_pSpriteCard3[3];
    int m_nAnimationID[3];
    
    
    CCBAnimationManager* m_pAnimation;
    void goConfirm(uint16_t nSelectIndex);
    int*    m_pInitMonster;
    uint32_t m_nCount;
    int  m_nSelectIndex;
};

#endif /* defined(__ProjectMB__MB_LayerSelectMonster__) */
