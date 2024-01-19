//
//  MB_NodeChapterRankUint.h
//  ProjectMB
//
//  Created by yuanwugang on 14-9-27.
//
//

#ifndef __ProjectMB__MB_NodeChapterRankUint__
#define __ProjectMB__MB_NodeChapterRankUint__

#include "MB_ResWindow.h"

class MB_ChapterRankData;
class MB_NodeChapterRankUint:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_NodeChapterRankUint();
    ~MB_NodeChapterRankUint();
    static MB_NodeChapterRankUint* create(MB_ChapterRankData* data);
    static CCSize getSize();
    virtual bool init(MB_ChapterRankData* data);
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
protected:
    void onInfoClicked(CCObject* pSender);
//    CCLabelTTF*
//    CCLabelTTF*
private:
    CCSprite*   m_pSpriteFrame;
    CCSprite*   m_pSpriteHead;
    CCLabelTTF* m_pTTFName;
    CCLabelBMFont*     m_pNodeLv;
    CCLabelTTF* m_pTTFChapter;
    CCNode*     m_pNodeSize;
    CCLabelBMFont*     m_pNodeRankNum;
    CCNode*     m_pNodeBG[5];
    MB_ChapterRankData * m_pData;
};

#endif /* defined(__ProjectMB__MB_NodeChapterRankUint__) */
