//
//  MB_NodeLuckyPlayer.h
//  ProjectTK
//
//  Created by crimoon00007 on 14-1-2.
//
//

#ifndef __ProjectMB__MB_NodeLuckyPlayer__
#define __ProjectMB__MB_NodeLuckyPlayer__

#include "Game.h"
class MB_NodeLuckyPlayer:
public MB_ResWindow,
public CCBMemberVariableAssigner
{
public:
    MB_NodeLuckyPlayer();
    ~MB_NodeLuckyPlayer();

    virtual bool init();

    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);

    void setLuckyPlayerData(const char* name);

    CREATE_FUNC(MB_NodeLuckyPlayer);
protected:
    virtual void onResetWnd();

private:
    std::string         m_szRoleName;

    CCLabelTTF*         m_pName;
    CCLabelTTF*         m_pHarmInfo;
};

#endif /* defined(__ProjectMB__MB_NodeLuckyPlayer__) */
