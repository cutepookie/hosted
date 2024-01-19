//
//  MB_NodeSelectControl.cpp
//  ProjectPM
//
//  Create by WenYong on 22/6/2014.
//
//
#include "MB_NodeSelectControl.h"
#include "Game.h"

MB_NodeSelectControl::MB_NodeSelectControl()
{
    m_pSelectFlag	 = NULL;
    m_pText	 = NULL;
    m_bSelected = false;
    m_pRoleIcon = NULL;
    m_pTextBMF = NULL;
    m_pIconFrame = NULL;
}
MB_NodeSelectControl::~MB_NodeSelectControl()
{
    CC_SAFE_RELEASE_NULL(m_pIconFrame);
    CC_SAFE_RELEASE_NULL(m_pSelectFlag);
    CC_SAFE_RELEASE_NULL(m_pText);
    CC_SAFE_RELEASE_NULL(m_pRoleIcon);
    CC_SAFE_RELEASE_NULL(m_pTextBMF);
    
}
bool MB_NodeSelectControl::init()
{
    CCNode* pNode = loadResource("res/main_node_select.ccbi");
    if(pNode)
	{
		addChild(pNode);
        m_pSelectFlag->setIsScale(false);
		return true;
	}
	return false;
}
void MB_NodeSelectControl::onResetWnd()
{

}
bool MB_NodeSelectControl::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSelectFlag",CCMenuItemImage*,m_pSelectFlag);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pText",CCLabelTTF*,m_pText);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pRoleIcon", CCSprite*, m_pRoleIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pIconFrame", CCSprite*, m_pIconFrame);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTextBMF",CCLabelBMFont*,m_pTextBMF);
    
	return false;
}
SEL_MenuHandler MB_NodeSelectControl::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onButtonClicked",MB_NodeSelectControl::onButtonClicked);
	return NULL;
}
SEL_CCControlHandler MB_NodeSelectControl::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

void MB_NodeSelectControl::onButtonClicked(CCObject* pSender)
{
    if(m_bSelected)
    {
        select();
        return;
    }
    MB_TARGET_PARENT(MB_ControlEventDelegate, ptr);
    if (ptr)
    {
        ptr->onControlClicked(this);
    }
    else
    {
        if (m_bSelected)
        {
            unselect();
        }
        else
        {
            select();
        }
    }
}

bool MB_NodeSelectControl::getSelected()const
{
    return m_bSelected;
}

bool MB_NodeSelectControl::select()
{
    m_bSelected = true;
    m_pSelectFlag->selected();
    return true;
}
bool MB_NodeSelectControl::unselect()
{
    m_bSelected = false;
    m_pSelectFlag->unselected();
    return true;
}

void MB_NodeSelectControl::setText(const char* pText)
{
    if (m_pText != NULL)
    {
        m_pText->setString(pText);
        
    }else if(m_pTextBMF != NULL)
    {
        m_pTextBMF->setString(pText);
    }
}

bool MB_NodeSelectCoin::init()
{
    CCNode* pNode = loadResource("res/obj_select_coin.ccbi");
    if(pNode)
	{
		addChild(pNode);
        m_pSelectFlag->setIsScale(false);
		return true;
	}
	return false;
}

void MB_NodeSelectPlayer::setHeadID(bool isMale,int roleID, int nTitle)
{
    NSGameHelper::setRoleIcon(m_pRoleIcon, isMale,roleID,nTitle,m_pIconFrame);
}

