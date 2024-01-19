//
//  MB_NodeDeploy.cpp
//  ProjectMB
//
//  Created by yuanwugang on 14-11-22.
//
//

#include "MB_NodeDeploy.h"
#include "MB_LayerDeploy.h"
#include "MB_LocalProto.h"
MB_NodeDeploy::MB_NodeDeploy()
{
    m_pNodeContainer = NULL;
    m_pTTFTitle = NULL;
    m_pNodeSize = NULL;
    m_bShowBackground = false;
    m_pAllStar = NULL;
    m_pNowCount = NULL;
    m_pAllCount = NULL;
    for (int i=0 ; i<MAX_GER_STAR ; i++) {
        m_pStar[i] = NULL;
    }
}
MB_NodeDeploy::~MB_NodeDeploy()
{
    CC_SAFE_RELEASE_NULL(m_pNodeContainer);
    CC_SAFE_RELEASE_NULL(m_pTTFTitle);
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(m_pAllStar);
    CC_SAFE_RELEASE_NULL(m_pNowCount);
    CC_SAFE_RELEASE_NULL(m_pAllCount);
    for (int i=0 ; i<MAX_GER_STAR ; i++) {
        CC_SAFE_RELEASE(m_pStar[i]);
    }
}
bool MB_NodeDeploy::init()
{
    CCNode* pNode = loadResource("res/card_attribute_node_title.ccbi");
    if(pNode)
	{
		addChild(pNode);
        this->setContentSize(m_pNodeSize->getContentSize());
		return true;
	}
	return false;
}
void MB_NodeDeploy::onResetWnd()
{
    if (m_pNodeContainer->getChildrenCount() == 0)
    {
        CCLOG("ERROR MB_NodeDeploy::onResetWnd()");
        return;
    }
    CCSize sz;
    sz.width = m_pNodeSize->getContentSize().width;
    CCNode* node = (CCNode*)m_pNodeContainer->getChildren()->objectAtIndex(0);
    sz.height = m_pNodeSize->getContentSize().height + node->getContentSize().height;
    this->setContentSize(sz);
    m_pNodeContainer->setVisible(true);
}

bool MB_NodeDeploy::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeContainer",CCNode*,m_pNodeContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFTitle",CCLabelTTF*,m_pTTFTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize",CCNode*,m_pNodeSize);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pAllStar",CCNode*,m_pAllStar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNowCount",CCLabelBMFont*,m_pNowCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pAllCount",CCLabelBMFont*,m_pAllCount);
    for (int i=0 ; i<MAX_GER_STAR; i++) {
        
        char starstr[]="star0";
        
        starstr[4] = i+'0';
        
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, starstr, CCNode *, m_pStar[i]);
    }
    return false;
}
SEL_MenuHandler MB_NodeDeploy::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}
SEL_CCControlHandler MB_NodeDeploy::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

void MB_NodeDeploy::setTitle(const char* title)
{
    m_pTTFTitle->setVisible(true);
    m_pTTFTitle->setString(title);
    for (int i =0; i<MAX_GER_STAR; i++) {
        m_pStar[i]->setVisible(false);
    }
}

void MB_NodeDeploy::setStar(int star)
{
    for (int i =star; i<MAX_GER_STAR; i++) {
        m_pStar[i]->setVisible(false);
    }
}
