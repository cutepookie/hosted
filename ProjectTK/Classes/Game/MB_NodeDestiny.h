//
//  MB_NodeDestiny.h
//  ProjectMB
//
//  Create by WenYong on 25/9/2014.
//
//
#ifndef __ProjectMB__MB_NodeDestiny__
#define __ProjectMB__MB_NodeDestiny__

#include "MB_ResWindow.h"

class MB_DestinyData;
class MB_PetTemplate;
class MB_ItemTemplate;
class MB_NodeDestiny : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
//    CREATE_FUNC(MB_NodeDestiny);
    static MB_NodeDestiny* create(MB_DestinyData* pData,bool active);
	MB_NodeDestiny();
	virtual ~MB_NodeDestiny();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    bool setData(MB_DestinyData* pData,bool active);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){return NULL;}
//protected:
//    void onIconClicked(CCObject* pSender);
private:
    CCSprite*	m_pIcon;
    CCLabelTTF*	m_pSkillName;
    CCLabelTTF*	m_pSkillEffective;
    CCLabelTTF*	m_pDesc;
    CCNode*     m_pNodeSize;
    bool        m_bActive;
    MB_PetTemplate* m_pPetTemplate;
    MB_ItemTemplate* m_pItemTemplate;
};
#endif /* defined(__ProjectMB__MB_NodeDestiny__) */
