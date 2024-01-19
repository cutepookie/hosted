//
//  MB_NodePetDesc.cpp
//  ProjectMB
//
//  Create by WenYong on 25/9/2014.
//
//
#include "MB_NodePetDesc.h"

MB_NodePetDesc::MB_NodePetDesc()
{
    m_pNodeSize	 = NULL;
    m_pTextDesc	 = NULL;
}
MB_NodePetDesc::~MB_NodePetDesc()
{
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(m_pTextDesc);
}
bool MB_NodePetDesc::init()
{
    CCNode* pNode = loadResource("res/card_node_des.ccbi");
    if(pNode)
	{
		addChild(pNode);
        setContentSize(m_pNodeSize->getContentSize());
		return true;
	}
	return false;
}
void MB_NodePetDesc::onResetWnd()
{

}

MB_NodePetDesc* MB_NodePetDesc::create(const char* pText)
{
    MB_NodePetDesc* pInstance = MB_NodePetDesc::create();
    if (pInstance && pInstance->setText(pText))
    {
        return pInstance;
    }
    
    return NULL;
}

bool MB_NodePetDesc::setText(const char* pText)
{
    if (pText == NULL)
    {
        return false;
    }
    m_pTextDesc->setString(pText);
    return true;
}
bool MB_NodePetDesc::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize",CCNode*,m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTextDesc",CCLabelTTF*,m_pTextDesc);
	return false;
}
