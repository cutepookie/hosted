//
//  MB_LayerAchievementItem.h
//  ProjectPM
//
//  Create by WenYong on 6/5/2014.
//
//
#ifndef __ProjectMB__MB_LayerAchievementItem__
#define __ProjectMB__MB_LayerAchievementItem__

#include "MB_ResWindow.h"
#include "MB_TaskSystemData.h"
class MB_LayerAchievementItem : public MB_ResWindow,
public CCBMemberVariableAssigner,
public CCBSelectorResolver
{
public:
	MB_LayerAchievementItem();
	virtual ~MB_LayerAchievementItem();
    static MB_LayerAchievementItem* create(MB_TaskServerData* data);
	virtual void onResetWnd();
	virtual bool init(MB_TaskServerData* data);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    CCSize getItemSize(){return size->getContentSize();}
    CCNode* m_pLine;
protected:
    void onStatusClicked(CCObject* pSender);
private:
    CCNode*	size;
    CCLabelTTF*	m_pTTFTaskDescription;
    CCLabelTTF* m_pTTFTaskTitle;
    CCLabelBMFont*	m_pTTFSchedule;
    CCLabelBMFont*    m_pAllCount;
    
    CCSprite*	m_pSpriteTaskFrame;
    CCSprite*	m_pSpriteTaskHead;
    CCLabelBMFont*	m_pNodeReaward_start;
    CCSprite*	m_pSpriteRewardHead;
    CCSprite*	m_pSpriteRewardFrame;
    CCNode* m_pState;
    CCNode* m_pState2;
    MB_TaskServerData* m_pDataSource;
    CCBAnimationManager* m_pAnimation;

    CCNode* m_pNodeComplate;
};
#endif /* defined(__ProjectMB__MB_LayerAchievementItem__) */
