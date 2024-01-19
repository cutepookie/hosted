//
//  MB_NodeNoticePic.h
//  ProjectMB
//
//  Created by yuanwugang on 15-1-21.
//
//

#ifndef __ProjectMB__MB_NodeNoticePic__
#define __ProjectMB__MB_NodeNoticePic__

#include "MB_ResWindow.h"

class MB_NodeNoticePic : public MB_ResWindow
,public CCBMemberVariableAssigner
{
public:
    MB_NodeNoticePic();
    ~MB_NodeNoticePic();
    
    CREATE_FUNC(MB_NodeNoticePic);
    virtual bool init();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    
    bool setPic(int picID);
    CCSprite* m_pSpritePic;
};

#endif /* defined(__ProjectMB__MB_NodeNoticePic__) */
