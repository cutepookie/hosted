//
//  MB_TrainerRoadNodePass.h
//  ProjectMB
//
//  Create by wenyong on 15/1/2015.
//
//
#ifndef __ProjectMB__MB_TrainerRoadNodePass__
#define __ProjectMB__MB_TrainerRoadNodePass__

#include "MB_ResWindow.h"
#include "MB_TrainerRoadProtocol.h"
class MB_TrainerRoadDungeon;
class BYGraySprite;
class MB_TrainerRoadNodePass : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    static MB_TrainerRoadNodePass* create(MB_TrainerRoadDungeon*);
	MB_TrainerRoadNodePass();
	virtual ~MB_TrainerRoadNodePass();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    void setStatus(ERoadDungeonStatus e,bool canFight);
    void setData(MB_TrainerRoadDungeon* pData);
protected:
    void onDungeonClicked(CCObject*);
private:
    CCMenu*	m_pNodeMenu;
    CCMenuItemImage*	m_pMenuItemIcon;
    CCLabelBMFont* m_pName;
    MB_TrainerRoadDungeon* m_pDungeon;
    ERoadDungeonStatus m_eStatu;
    CCSprite* m_pSpriteStatus;
    CCLabelTTF* m_pForTest;
    bool m_bCanFight;
};
#endif /* defined(__ProjectMB__MB_TrainerRoadNodePass__) */
