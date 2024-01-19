//
//  MB_LayerChangeName.h
//  ProjectMB
//
//  Created by yuanwugang on 15-1-14.
//
//

#ifndef __ProjectMB__MB_LayerChangeName__
#define __ProjectMB__MB_LayerChangeName__

#include "MB_ResWindow.h"

class MB_LayerChangeName : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
,public CCEditBoxDelegate
{
public:
    MB_LayerChangeName();
    ~MB_LayerChangeName();
    virtual bool init();
    void onResetWnd();
    static MB_LayerChangeName* create();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
    
    void onMsgRecv(CCNode* node, SocketResponse* response);
    void onConfirmClicked(CCObject *);
    void onBreakClicked(CCObject *);
private:
    CCLabelBMFont* m_pTTFItemNum;
    CCEditBox* m_pEditBox;
    std::string m_pName;
};






#endif /* defined(__ProjectMB__MB_LayerChangeName__) */
