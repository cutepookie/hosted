

#ifndef __ProjectMB__MB_NodeRocketTeamPreReport__
#define __ProjectMB__MB_NodeRocketTeamPreReport__
#include "Game.h"
class MB_EventData;
class MB_NodeRocketTeamPreReport:public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver {
    
    private:
    
        CCLabelBMFont *m_pBossLevel;
        CCLabelBMFont *m_pLevelTime;
        CCNode *m_pNodeWin;
        CCNode *m_pNodeLose;
        CCNode *m_pNodeLuckyPlayer;
        CCLabelTTF *m_pAttack[11];
        CCLabelTTF *m_pUserName[11];
    
        CCNode *m_pLostInfo;
        int m_nIndex;

    public :
    
    MB_NodeRocketTeamPreReport();
    ~MB_NodeRocketTeamPreReport();
    virtual bool init(int index);
    static  MB_NodeRocketTeamPreReport* create(int index);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    void onBackClick(CCObject *);
    virtual void onResetWnd();
    bool sendhula_open();
    bool sendWorldBoss_open();
    void onMsgRecv(CCNode* node, SocketResponse* response);
    
};


#endif /* defined(__ProjectMB__MB_NodeRocketTeamPreReport__) */
