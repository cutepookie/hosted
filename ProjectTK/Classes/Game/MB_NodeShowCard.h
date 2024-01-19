//
//  MB_NodeShowCard.h
//  ProjectMB
//
//  Created by yuanwugang on 14-10-24.
//
//

#ifndef __ProjectMB__MB_NodeShowCard__
#define __ProjectMB__MB_NodeShowCard__


#include "MB_NodePetTeam.h"


class MB_NodeShowCard:public MB_NodePetTeam
{
public:
    MB_NodeShowCard();
    virtual ~MB_NodeShowCard();
    static MB_NodeShowCard* create(MB_PetData* pData);
    virtual bool init(MB_PetData* pData);
    virtual void onResetWnd(void);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
private:
    CCNode* m_pNodeSize;
};

#endif /* defined(__ProjectMB__MB_NodeShowCard__) */
