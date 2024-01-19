//
//  MB_NodeSuitName.cpp
//  ProjectPM
//
//  Create by WenYong on 4/5/2014.
//
//
#include "MB_NodeSuitName.h"
#include "MB_FunctionModule.h"
MB_NodeSuitName::MB_NodeSuitName()
{
    m_pNodeSize	 = NULL;
    m_pSuitName	 = NULL;
}
MB_NodeSuitName::~MB_NodeSuitName()
{
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(m_pSuitName);
}
bool MB_NodeSuitName::init()
{
    CCNode* pNode = loadResource("res/suit_node_name.ccbi");
    if(pNode)
	{
		addChild(pNode);
        onResetWnd();
		return true;
	}
	return false;
}

CCSize MB_NodeSuitName::getNodeSize()const
{
    return m_pNodeSize->getContentSize();
}

void MB_NodeSuitName::setName(const char* pName)
{
    if (pName)
    {
        m_szSuitName = pName;
        onResetWnd();
    }
}
void MB_NodeSuitName::onResetWnd()
{
    m_pSuitName->setString(m_szSuitName.c_str());
}
bool MB_NodeSuitName::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize",CCNode*,m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSuitName",CCLabelTTF*,m_pSuitName);
	return false;
}
