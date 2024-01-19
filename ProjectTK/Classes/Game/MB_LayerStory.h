//
//  MB_LayerStory.h
//  ProjectPM
//
//  Created by crimoon on 14-5-14.
//
//

#ifndef __ProjectMB__MB_LayerStory__
#define __ProjectMB__MB_LayerStory__

#include "MB_ResWindow.h"

class MB_LayerStoryPlayer: public MB_ResWindow
,public CCBSelectorResolver
,public CCBMemberVariableAssigner
{
private:
    CCNode* m_pNodeLeftRole;
    CCNode* m_pNodeRightRole;
    CCLabelTTF* m_pTTFShow;
    
    char*   m_pText;
    int     m_nMaxLength;
    int     m_nNowLength;
    
    unsigned short* m_pDialogUnicode;
    int     m_nDialogUnicodePos;
    int     m_nDialogUnicodeLength;
    
    int     m_nNowIndx;
    
    CCArray* m_pArrayStory;
public:
    MB_LayerStoryPlayer();
    ~MB_LayerStoryPlayer();
    
    virtual bool init(CCArray* array);
    static MB_LayerStoryPlayer* create(CCArray* array);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    void onNextStepClicked(CCObject *);
    
    void tickShowText(float dt);
    
    void setNextDialogue();
    
    void setTarget(CCObject* target,SEL_MenuHandler callback);
    
    void over();
    virtual void onEnter();
private:
    CCObject *m_pTarget;        //按钮回调消息处理
    SEL_MenuHandler m_pMenuCall; //回调函数
    int effectId;
};
#endif /* defined(__ProjectMB__MB_LayerStory__) */
