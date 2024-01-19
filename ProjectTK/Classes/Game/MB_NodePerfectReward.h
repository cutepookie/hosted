//
//  MB_NodePerfectReward.h
//  ProjectMB
//
//  Created by yuanwugang on 14-9-26.
//
//

#ifndef __ProjectMB__MB_NodePerfectReward__
#define __ProjectMB__MB_NodePerfectReward__

#include "MB_ResWindow.h"



enum
{
    kCanNotReceive = 1,     //不可领取
    kNoReceive,             //没领取
    kHasReceive             //已领取
};


class MB_LayerChapterWnd;
class MB_NodePerfectReward:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_NodePerfectReward();
    ~MB_NodePerfectReward();
    static MB_NodePerfectReward* create(CCArray* array,int state);
    virtual bool init(CCArray* array,int state);
    virtual void onEnter();
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    void setDataRouse(MB_LayerChapterWnd* pChapterLayer){m_pChapterLayer = pChapterLayer;};
protected:
    void onCloseClick(CCObject* pSender);
    void onCommitClicked(CCObject* pSender);
   
private:
    CCNode*  m_pNodeReward;
    CCScrollView*   m_pScrollView;
    CCMenuItemImage* m_pBtGive;
    CCMenuItemImage* m_pBtCanNotGive;
    int m_nState;
    
    MB_LayerChapterWnd* m_pChapterLayer;
};


#endif /* defined(__ProjectMB__MB_NodePerfectReward__) */
