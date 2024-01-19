//
//  MB_NodeServerZone.cpp
//  ProjectMB
//
//  Created by WenYong on 27/8/2014.
//
//
#include "MB_NodeServerZone.h"
#include "MB_LayerServerPanel.h"
#include "Game.h"

MB_NodeServerZone::MB_NodeServerZone()
{
    size	 = NULL;
    m_pBeginServerZone	 = NULL;
    m_pEndServerZone	 = NULL;
    m_pNodeMenu	 = NULL;
    m_nBeginID = 0;
    m_nEndID = 0;
    m_pNodeSelect = NULL;
    m_pMenuImage = NULL;
}
MB_NodeServerZone::~MB_NodeServerZone()
{
    CC_SAFE_RELEASE_NULL(size);
    CC_SAFE_RELEASE_NULL(m_pBeginServerZone);
    CC_SAFE_RELEASE_NULL(m_pEndServerZone);
    CC_SAFE_RELEASE_NULL(m_pNodeMenu);
    CC_SAFE_RELEASE_NULL(m_pNodeSelect);
    CC_SAFE_RELEASE_NULL(m_pMenuImage);
    m_nBeginID = 0;
    m_nEndID = 0;
}

MB_NodeServerZone* MB_NodeServerZone::create(int beginID,int endID)
{
    MB_NodeServerZone* pInstance = MB_NodeServerZone::create();
    if (pInstance)
    {
        pInstance->setDetail(beginID, endID);
        return pInstance;
    }
    
    return NULL;
}
bool MB_NodeServerZone::init()
{
    CCNode* pNode = loadResource("res/severchoose_node_label.ccbi");
    if(pNode)
	{
		addChild(pNode);
        m_pNodeMenu->setSwallowsTouches(false);
        m_pNodeSelect->setVisible(false);
        if (m_pMenuImage)
        {
            m_pMenuImage->setIsScale(false);
        }
        m_pNodeMenu->setTouchPriority(99);
		return true;
	}
	return false;
}
void MB_NodeServerZone::onResetWnd()
{

}
bool MB_NodeServerZone::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"size",CCNode*,size);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBeginServerZone",CCLabelTTF*,m_pBeginServerZone);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pEndServerZone",CCLabelTTF*,m_pEndServerZone);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeMenu",CCMenu*,m_pNodeMenu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeSelect", CCNode*, m_pNodeSelect);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMenuImage", CCMenuItemImage*, m_pMenuImage);
	return false;
}
SEL_MenuHandler MB_NodeServerZone::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onServerZoneClicked",MB_NodeServerZone::onServerZoneClicked);
	return NULL;
}
SEL_CCControlHandler MB_NodeServerZone::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

void MB_NodeServerZone::setDetail(int beginID,int endID)
{
    char buff[24] = {};
    sprintf(buff, "%d",beginID);
    m_pBeginServerZone->setString(buff);
    sprintf(buff, "%d",endID);
    m_pEndServerZone->setString(buff);
    m_nBeginID = beginID;
    m_nEndID = endID;
}

void MB_NodeServerZone::select(bool bSelect)
{
    m_pNodeSelect->setVisible(bSelect);
}

void MB_NodeServerZone::onServerZoneClicked(CCObject* pSender)
{
    MB_TARGET_PARENT(MB_LayerServerPanel, ptr);
    if (ptr)
    {
        ptr->selectRange(m_nBeginID, m_nEndID);
    }
}

const CCSize& MB_NodeServerZone::getWndSize()
{
    static CCSize sz = CCSizeMake(-1, -1);
    
    if (sz.width < 0.0f)
    {
        MB_NodeServerZone* pTemp = MB_NodeServerZone::create();
        if (pTemp)
        {
            sz = pTemp->size->getContentSize();
        }
    }
    
    return sz;
}
