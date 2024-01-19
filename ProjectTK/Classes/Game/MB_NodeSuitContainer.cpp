//
//  MB_NodeSuitContainer.cpp
//  ProjectPM
//
//  Create by WenYong on 4/5/2014.
//
//
#include "MB_NodeSuitContainer.h"

MB_NodeSuitContainer::MB_NodeSuitContainer()
{
    m_pNodeSize	 = NULL;
    for (int i = 0; i < 6; i++) {
        m_pNodeItems[i] = NULL;
    }
}
MB_NodeSuitContainer::~MB_NodeSuitContainer()
{
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    for (int i = 0; i < 6; i++) {
        CC_SAFE_RELEASE_NULL(m_pNodeItems[i]);
    }
}
bool MB_NodeSuitContainer::init()
{
    CCNode* pNode = loadResource("res/suit_node_details.ccbi");
    if(pNode)
	{
		addChild(pNode);
		return true;
	}
	return false;
}
void MB_NodeSuitContainer::onResetWnd()
{

}

bool MB_NodeSuitContainer::pushSuitItem(CCNode* pNode,uint16_t index)
{
    if (pNode )
    {
        m_pNodeItems[index]->removeAllChildren();
        m_pNodeItems[index]->addChild(pNode);
        return true;
    }
    
    return false;
}

CCSize MB_NodeSuitContainer::getNodeSize()const
{
    return m_pNodeSize->getContentSize();
}

bool MB_NodeSuitContainer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize",CCNode*,m_pNodeSize);
    for (int i = 0; i < 6; i++) {
        char starstr[] = "m_pNodeItem1";
        starstr[11] = i + '1';
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, starstr, CCNode *, m_pNodeItems[i]);
    }
	return false;
}
