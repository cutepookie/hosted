//
//  MB_AchievementComplate.cpp.h
//  ProjectPM
//
//  Created by crimoon on 14-6-7.
//
//

#ifndef __ProjectMB__MB_AchievementComplate_cpp__
#define __ProjectMB__MB_AchievementComplate_cpp__



#define  MB_AchievementTag    199999
#include "MB_ResWindow.h"
#include "MB_TaskSystemData.h"
class MB_AchievementComplate : public MB_ResWindow,public CCBMemberVariableAssigner
{
public:
	MB_AchievementComplate();
	virtual ~MB_AchievementComplate();
    static MB_AchievementComplate* create(MB_TaskServerData* pData);

	virtual void onResetWnd();
	virtual bool init(MB_TaskServerData* pData);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onExit();
    virtual void onEnter();
    void onAnimationCallback();
protected:

private:
    CCLabelTTF*	ttf_task_description;
    CCLabelTTF* ttf_task_title;
    CCNode*	m_pWCLabel;
    CCSprite*	m_pSpriteTaskHead;
    bool            m_bRun;
    CCBAnimationManager* m_pAnimation;
    MB_TaskServerData* m_pDataSource;
};

#endif /* defined(__ProjectMB__MB_AchievementComplate_cpp__) */
