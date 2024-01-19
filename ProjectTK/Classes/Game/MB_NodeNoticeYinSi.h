//
//  MB_NodeNoticeYinSiYinSi.h
//  ProjectMB
//
//  Created by yuanwugang on 14-12-18.
//
//

#ifndef __ProjectMB__MB_NodeNoticeYinSiYinSi__
#define __ProjectMB__MB_NodeNoticeYinSiYinSi__

#include "MB_ResWindow.h"
#include "Game.h"
#include "RichText.h"


class MB_NodeNoticeYinSiPic;
class MB_NodeNoticeYinSi:public MB_ResWindow
,public CCBMemberVariableAssigner
{
public:
    MB_NodeNoticeYinSi();
    virtual ~MB_NodeNoticeYinSi();
    CREATE_FUNC(MB_NodeNoticeYinSi)
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
    virtual bool init();
    void setData(char* des);
private:
    CCNode*             m_pNodeContent;
    RichText*           m_pRichBoxContent;
    CCNode* pRootNode;
};
#endif /* defined(__ProjectMB__MB_NodeNoticeYinSiYinSi__) */
