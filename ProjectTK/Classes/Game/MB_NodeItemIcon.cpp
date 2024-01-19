//
//  MB_NodeItemIcon.cpp
//  ProjectPM
//
//  Create by WenYong on 23/7/2014.
//
//
#include "MB_NodeItemIcon.h"
#include "MB_FunctionModule.h"

MB_NodeItemIcon::MB_NodeItemIcon()
{
    m_pItemIcon	 = NULL;
    m_pItemFrame	 = NULL;
    m_nTypeID = 0;
    m_nRank = 1;
    m_pSpriteDebris = NULL;
}
MB_NodeItemIcon::~MB_NodeItemIcon()
{
    CC_SAFE_RELEASE_NULL(m_pItemIcon);
    CC_SAFE_RELEASE_NULL(m_pItemFrame);
    CC_SAFE_RELEASE_NULL(m_pSpriteDebris);
}

MB_NodeItemIcon* MB_NodeItemIcon::create(uint16_t tid,int nRank)
{
    MB_NodeItemIcon* pInstance = new MB_NodeItemIcon;
    if (pInstance && pInstance->init())
    {
        pInstance->autorelease();
        pInstance->setData(tid);
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}
bool MB_NodeItemIcon::init()
{
    CCNode* pNode = loadResource("res/achievement_node_itemicon.ccbi");
    if(pNode)
	{
		addChild(pNode);
		return true;
	}
	return false;
}
void MB_NodeItemIcon::onResetWnd()
{
    NSGameHelper::setItemIconDetailByTid(m_nTypeID, m_nRank, m_pItemIcon,NULL,m_pItemFrame);
    MB_ItemTemplate *templete = MB_ItemMgr::getInstance()->getItemTemplateByID(m_nTypeID);
    if(templete)m_pSpriteDebris->setVisible(templete->getIsDebris());
}
bool MB_NodeItemIcon::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pItemIcon",CCSprite*,m_pItemIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pItemFrame",CCSprite*,m_pItemFrame);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteDebris", CCNode*, m_pSpriteDebris);
	return false;
}
void MB_NodeItemIcon::setData(uint16_t tid,int nRank)
{
    m_nTypeID = tid;
    m_nRank = nRank;
    onResetWnd();
}