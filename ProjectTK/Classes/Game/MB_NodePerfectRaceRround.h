//
//  MB_NodePerfectRaceRround.h
//  ProjectPM
//
//  Created by WenYong on 14-4-24.
//
//

#ifndef __ProjectMB__MB_NodePerfectRaceRround__
#define __ProjectMB__MB_NodePerfectRaceRround__

#include "MB_ResWindow.h"

class MB_NodePerfectRaceRround:public MB_ResWindow
,public CCBMemberVariableAssigner
{
public:
    MB_NodePerfectRaceRround();
    ~MB_NodePerfectRaceRround();
    virtual bool init(uint8_t nRound);
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    static MB_NodePerfectRaceRround* create(uint8_t nRound);
    virtual void forceSetShowString(const char* pString);
private:
    uint8_t m_nRound;
    CCLabelTTF* m_pShowString;
};
#endif /* defined(__ProjectMB__MB_NodePerfectRaceRround__) */
