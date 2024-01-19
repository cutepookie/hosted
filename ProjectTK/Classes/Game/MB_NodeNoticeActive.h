//
//  MB_NodeNoticeActive.h
//  ProjectMB
//
//  Created by yuanwugang on 14-12-18.
//
//

#ifndef __ProjectMB__MB_NodeNoticeActive__
#define __ProjectMB__MB_NodeNoticeActive__

#include "MB_ResWindow.h"
#include "Game.h"
#include "RichText.h"
class MB_NodeNoticeActive:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
    
public:
    MB_NodeNoticeActive();
    virtual ~MB_NodeNoticeActive();
    
    CREATE_FUNC(MB_NodeNoticeActive)
    
public:
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget,const char* pSelectorName);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual bool init();
    
    void setData(MB_MoneyEevntData * data);
protected:
    virtual void onResetWnd(void);
    
    
private:
    CCNode*             m_pNodeContent;
    RichText*           m_pRichBoxContent;
    CCLabelTTF*         m_pTTFName;
    CCLabelTTF*         m_pTTFTime;
    int                 m_nActiveID;
};

class MB_NodeNoticeActiveTitle:public MB_ResWindow
,public CCBMemberVariableAssigner
{
public:
    MB_NodeNoticeActiveTitle();
    virtual ~MB_NodeNoticeActiveTitle();
    
    CREATE_FUNC(MB_NodeNoticeActiveTitle)
    
public:
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
    virtual bool init();
private:
    CCLabelTTF*         m_pTTFTitle;
    CCLabelTTF*         m_pTTFTitle2;
    CCNode*             m_pNodeSize;
};

class MB_NodeNoticePic;
class MB_NodeNotice:public MB_ResWindow
,public CCBMemberVariableAssigner
{
public:
    MB_NodeNotice();
    virtual ~MB_NodeNotice();
    CREATE_FUNC(MB_NodeNotice)
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
    virtual bool init();
    void setData(char* des,CCNode* nnp = NULL);
private:
    CCNode*             m_pNodeContent;
    RichText*           m_pRichBoxContent;
    CCNode* pRootNode;
};
#endif /* defined(__ProjectMB__MB_NodeNoticeActive__) */
