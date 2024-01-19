//
//  MB_NodePicIcon.h
//  ProjectMB
//
//  Created by yuanwugang on 14-11-23.
//
//

#ifndef __ProjectMB__MB_NodePicIcon__
#define __ProjectMB__MB_NodePicIcon__

#include "MB_ResWindow.h"

class MB_PicShow;
class MB_NodePicIcon : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    CREATE_FUNC(MB_NodePicIcon);
    static MB_NodePicIcon* create2();
    MB_NodePicIcon();
    ~MB_NodePicIcon();
    void setData(MB_PicShow* data,int type);
    virtual bool init();
    bool init2();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);

    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    static CCSize getNodeSize();
    void runAnimation();
        virtual void onExit();
protected:
    void onDetailClicked(CCObject* pSender);
private:
        CCBAnimationManager *m_pAnimation;
    CCNode* m_pNodeSize;
    CCSprite* m_pSpriteItemIcon;
    CCSprite* m_pSpriteItemKuang;
    CCLabelTTF* m_pTTFName;
    int m_nType;
};

#endif /* defined(__ProjectMB__MB_NodePicIcon__) */
