//
//  MB_NodeDestiny.cpp
//  ProjectMB
//
//  Create by WenYong on 25/9/2014.
//
//
#include "MB_NodeDestiny.h"
#include "MB_petData.h"
#include "MB_ItemData.h"
#include "MB_FunctionModule.h"
#include "MB_LayerShapeShow.h"

MB_NodeDestiny::MB_NodeDestiny()
{
    m_pIcon	 = NULL;
    m_pSkillName	 = NULL;
    m_pSkillEffective	 = NULL;
    m_pDesc	 = NULL;
    m_pNodeSize = NULL;
    m_bActive = false;
    m_pPetTemplate = NULL;
    m_pItemTemplate = NULL;
}
MB_NodeDestiny::~MB_NodeDestiny()
{
    CC_SAFE_RELEASE_NULL(m_pIcon);
    CC_SAFE_RELEASE_NULL(m_pSkillName);
    CC_SAFE_RELEASE_NULL(m_pSkillEffective);
    CC_SAFE_RELEASE_NULL(m_pDesc);
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
}

MB_NodeDestiny* MB_NodeDestiny::create(MB_DestinyData* pData,bool active)
{
    MB_NodeDestiny* pInstance = new MB_NodeDestiny();
    
    if (pInstance && pInstance->init() && pInstance->setData(pData,active))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    return NULL;
}
bool MB_NodeDestiny::init()
{
    CCNode* pNode = loadResource("res/card_node_skill.ccbi");
    if(pNode)
    {
        addChild(pNode);
        this->setContentSize(m_pNodeSize->getContentSize());
        return true;
    }
    return false;
}
bool MB_NodeDestiny::setData(MB_DestinyData *pData,bool active)
{
    if (pData == NULL)
    {
        return false;
    }
//    if (!active)
//    {
//        m_pSkillName->setColor(ccc3(127, 127, 127));
//        m_pSkillEffective->setColor(ccc3(127, 127, 127));
//        m_pDesc->setColor(ccc3(127, 127, 127));
//        m_pIcon->setColor(ccc3(127, 127, 127));
//    }
//    else
//    {
//        m_pSkillName->setColor(ccc3(108, 29, 35));
//        m_pSkillEffective->setColor(ccc3(108, 29, 35));
//        m_pDesc->setColor(ccc3(108, 29, 35));
//        m_pIcon->setColor(ccc3(255, 255, 255));
//    }
    
    char buff[64] = {};
    if (pData->getDestinyType() == 1)
    {
        MB_PetTemplate* pTemplate = MB_PetMgr::getInstance()->getPetTemplateByID(pData->getDestinyNeed1());
        if (pTemplate)
        {
            NSGameHelper::setSpriteFrame(m_pIcon, CCString::createWithFormat("round_icon_card/round_card_%d.png",pTemplate->getPetTypeID()+1)->getCString());
            NSGameHelper::creatMaskSprite(m_pIcon);
            sprintf(buff, "同\"%s\"组队",pTemplate->getPetName());
            m_pDesc->setString(buff);
            m_pPetTemplate = pTemplate;
        }
    }
    else if(pData->getDestinyType() == 2)
    {
        MB_ItemTemplate* pTemplate = MB_ItemMgr::getInstance()->getItemTemplateByID(pData->getDestinyNeed1());
        if (pTemplate)
        {
            NSGameHelper::setSpriteFrame(m_pIcon, pTemplate->getItemIcon());
            NSGameHelper::creatMaskSprite(m_pIcon);
            sprintf(buff, "装备\"%s\"",pTemplate->getItemName());
            m_pDesc->setString(buff);
            m_pItemTemplate = NULL;
        }
    }

    m_pSkillName->setString(pData->getDestinyName());
    
    CCObject* attribute;
    std::string detailString="";
    CCARRAY_FOREACH(pData->getDestinyAttributeArray(),attribute)
    {
        if(((MB_DestinyAttribute *)attribute)->getValue()  <= 0 ){
            
            continue;
        }
        
        if (((MB_DestinyAttribute *)attribute)->getType() == 17 || ((MB_DestinyAttribute *)attribute)->getType() ==18 ||((MB_DestinyAttribute *)attribute)->getType() == 13 || ((MB_DestinyAttribute *)attribute)->getType() == 14)
        {
            sprintf(buff, "%s +%.0f%%",((MB_DestinyAttribute *)attribute)->getName(),((MB_DestinyAttribute *)attribute)->getValue()/100.0f);
        }
        else
        {
            sprintf(buff,"%s +%.0f ", ((MB_DestinyAttribute *)attribute)->getName(),((MB_DestinyAttribute *)attribute)->getValue());
        }
        
        detailString = detailString + buff;
        
    }
    m_pSkillEffective->setString( detailString.c_str());
    
    

    return true;
}


void MB_NodeDestiny::onResetWnd()
{

}

//void MB_NodeDestiny::onIconClicked(CCObject* pSender)
//{
//    if (m_pPetTemplate)
//    {
//        MB_LayerShapeShow* pNode = MB_LayerShapeShow::create();
//        if (pNode)
//        {
//            pNode->setTemplate(m_pPetTemplate,m_pSkillName->getString());
//            MB_TARGET_PARENT(MB_LayerPetDetail, ptr);
//            if (ptr)
//            {
//                ptr->addChild(pNode);
//            }
//        }
//    }
//}

SEL_MenuHandler MB_NodeDestiny::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onIconClicked", MB_NodeDestiny::onIconClicked);
    return NULL;
}

bool MB_NodeDestiny::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pIcon",CCSprite*,m_pIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSkillName",CCLabelTTF*,m_pSkillName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSkillEffective",CCLabelTTF*,m_pSkillEffective);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pDesc",CCLabelTTF*,m_pDesc);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize",CCNode*,m_pNodeSize);
    
	return false;
}
