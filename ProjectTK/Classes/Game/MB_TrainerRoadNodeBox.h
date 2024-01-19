//
//  MB_TrainerRoadNodeBox.h
//  ProjectMB
//
//  Create by wenyong on 15/1/2015.
//
//
#ifndef __ProjectMB__MB_TrainerRoadNodeBox__
#define __ProjectMB__MB_TrainerRoadNodeBox__

#include "MB_ResWindow.h"
#include "MB_TrainerRoadProtocol.h"
class MB_TrainerRoadRewardBox;
class BYGraySprite;
class MB_TrainerRoadNodeBox : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    static MB_TrainerRoadNodeBox* create(MB_TrainerRoadRewardBox*);
	MB_TrainerRoadNodeBox();
	virtual ~MB_TrainerRoadNodeBox();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    void setStatus(ERoadBoxStatus e);
    void setData(MB_TrainerRoadRewardBox* pData);
protected:
    void onBoxClicked(CCObject*);
private:
    CCMenu*	m_pNodeMenu;
    CCMenuItemImage*	m_pMenuImageIcon;
    
    MB_TrainerRoadRewardBox* m_pBox;
    ERoadBoxStatus m_eStatu;
    CCSprite* m_pSpriteStatus;
    CCLabelTTF* m_pForTest;
};
#endif /* defined(__ProjectMB__MB_TrainerRoadNodeBox__) */
