//
//  MB_LayerPackage.cpp
//  ProjectPM
//
//  Create by WenYong on 19/6/2014.
//
//
#include "MB_LayerPackage.h"
#include "MB_FunctionMgr.h"
MB_LayerPackage::MB_LayerPackage()
{
    m_pNodeStore	 = NULL;
    m_pNodeMonsters	 = NULL;
    m_pNodeEquip	 = NULL;
}
MB_LayerPackage::~MB_LayerPackage()
{
    CC_SAFE_RELEASE_NULL(m_pNodeStore);
    CC_SAFE_RELEASE_NULL(m_pNodeMonsters);
    CC_SAFE_RELEASE_NULL(m_pNodeEquip);
}
bool MB_LayerPackage::init()
{
    CCNode* pNode = loadResource("res/gui_package_index.ccbi");
    if(pNode)
	{
		addChild(pNode);
//        MB_FunctionMgr::getInstance()->bindEntry2Target(kFunctionPackage,m_pNodeStore);
//        MB_FunctionMgr::getInstance()->bindEntry2Target(kFunctionSpriteRoom,m_pNodeMonsters);
//        MB_FunctionMgr::getInstance()->bindEntry2Target(kFunctionEquipStore,m_pNodeEquip);
		return true;
	}
	return false;
}
void MB_LayerPackage::updateNode(CCNode* pNode)
{
    if (pNode==NULL || pNode->getChildrenCount()==0)
    {
        return;
    }
    
    MB_ResWindow* pWnd = dynamic_cast<MB_ResWindow*>(pNode->getChildren()->objectAtIndex(0));
    if (pWnd)
    {
        pWnd->onResetWnd();
    }
}
void MB_LayerPackage::onResetWnd()
{
    updateNode(m_pNodeStore);
    updateNode(m_pNodeMonsters);
    updateNode(m_pNodeEquip);
}
bool MB_LayerPackage::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeStore",CCNode*,m_pNodeStore);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeMonsters",CCNode*,m_pNodeMonsters);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeEquip",CCNode*,m_pNodeEquip);
	return false;
}
