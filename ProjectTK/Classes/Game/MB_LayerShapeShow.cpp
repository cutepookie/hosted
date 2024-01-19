//
//  MB_LayerShapeShow.cpp
//  ProjectMB
//
//  Create by wenyong on 23/12/2014.
//
//
#include "MB_LayerShapeShow.h"
#include "MB_PetData.h"
MB_LayerShapeShow::MB_LayerShapeShow()
{
    m_pShap1	 = NULL;
    m_pShap2	 = NULL;
    m_pShap3	 = NULL;
    m_pLabelTitle = NULL;
    
    m_pNameShap1 = NULL;
    m_pNameShap2 = NULL;
    m_pNameShap3 = NULL;
}
MB_LayerShapeShow::~MB_LayerShapeShow()
{
    CC_SAFE_RELEASE_NULL(m_pShap1);
    CC_SAFE_RELEASE_NULL(m_pShap2);
    CC_SAFE_RELEASE_NULL(m_pShap3);
    CC_SAFE_RELEASE_NULL(m_pNameShap1);
    CC_SAFE_RELEASE_NULL(m_pNameShap2);
    CC_SAFE_RELEASE_NULL(m_pNameShap3);
    CC_SAFE_RELEASE_NULL(m_pLabelTitle);
}
bool MB_LayerShapeShow::init()
{
    CCNode* pNode = loadResource("res/card_node_smallview.ccbi");
    if(pNode)
	{
        addChild(NSGameHelper::createDisableTouchLayer());
		addChild(pNode);
		return true;
	}
	return false;
}
void MB_LayerShapeShow::onResetWnd()
{

}
bool MB_LayerShapeShow::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pShap1",CCSprite*,m_pShap1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pShap2",CCSprite*,m_pShap2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pShap3",CCSprite*,m_pShap3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNameShap1",CCLabelTTF*,m_pNameShap1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNameShap2",CCLabelTTF*,m_pNameShap2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNameShap3",CCLabelTTF*,m_pNameShap3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTitle", CCLabelTTF*, m_pLabelTitle);
	return false;
}
SEL_MenuHandler MB_LayerShapeShow::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClicked",MB_LayerShapeShow::onCloseClicked);
	return NULL;
}
SEL_CCControlHandler MB_LayerShapeShow::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
void MB_LayerShapeShow::onCloseClicked(CCObject* pSender)
{
    removeFromParent();
//    popWindow();
}

void MB_LayerShapeShow::setTypeId(uint16_t tid)
{
    MB_PetTemplate* pTemplate = MB_PetMgr::getInstance()->getPetTemplateByID(tid);
    setTemplate(pTemplate,"组合技能");
}

void MB_LayerShapeShow::setTemplate(MB_PetTemplate* pTemp,const char* skillName)
{
    if (pTemp)
    {
        NSGameHelper::setSpriteFrame(m_pShap1, pTemp->getPetCard(1));
        NSGameHelper::setSpriteFrame(m_pShap2, pTemp->getPetCard(2));
        NSGameHelper::setSpriteFrame(m_pShap3, pTemp->getPetCard(3));
        
        m_pNameShap1->setString(pTemp->getPetName(SHAPE_1));
        m_pNameShap2->setString(pTemp->getPetName(SHAPE_2));
        m_pNameShap3->setString(pTemp->getPetName(SHAPE_3));
    }
    
    if(skillName)m_pLabelTitle->setString(skillName);
}
