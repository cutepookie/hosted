//
//  MB_NodeDeploy.h
//  ProjectMB
//
//  Created by yuanwugang on 14-11-22.
//
//

#ifndef __ProjectMB__MB_NodeDeploy__
#define __ProjectMB__MB_NodeDeploy__

#include "MB_ResWindow.h"

class MB_NodeDeploy : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_NodeDeploy();
    virtual ~MB_NodeDeploy();
    virtual bool init();
    virtual void onResetWnd();
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void setTitle(const char* title);
    virtual void setDeploy() = 0;
    void setStar(int star);
protected:
    CCNode* m_pNodeContainer;
    bool m_bShowBackground;
    CCLabelBMFont*  m_pNowCount;
    CCLabelBMFont*  m_pAllCount;
private:
    
    CCLabelTTF* m_pTTFTitle;
    CCNode* m_pNodeSize;
    CCNode* m_pAllStar;
    CCNode* m_pStar[7];
};


#endif /* defined(__ProjectMB__MB_NodeDeploy__) */
