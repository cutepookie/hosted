//
//  MB_NodeDestinyContainer.cpp
//  ProjectMB
//
//  Create by WenYong on 25/9/2014.
//
//
#include "MB_NodeDestinyContainer.h"
#include "MB_petData.h"
#include "MB_NodeDestiny.h"
#include "MB_TeamData.h"

MB_NodeDestinyContainer* MB_NodeDestinyContainer::create(MB_PetData* pData)
{
    MB_NodeDestinyContainer* pInstance = MB_NodeDestinyContainer::create();
    if (pInstance && pInstance->setData(pData))
    {
        return pInstance;
    }
    
    return NULL;
}

MB_NodeDestinyContainer::MB_NodeDestinyContainer()
{
    m_pNodeSize          = NULL;
    m_pContainer = NULL;
}
MB_NodeDestinyContainer::~MB_NodeDestinyContainer()
{
    CC_SAFE_RELEASE_NULL(m_pContainer);
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
}
bool MB_NodeDestinyContainer::init()
{
    CCNode* pNode = loadResource("res/skill_unit_2.ccbi");
    if(pNode)
	{
		addChild(pNode);
        setContentSize(m_pNodeSize->getContentSize());
		return true;
	}
	return false;
}

void MB_NodeDestinyContainer::onResetWnd()
{

}

bool MB_NodeDestinyContainer::setData(MB_PetData* pData)
{
    if (pData==NULL)
    {
        return false;
    }
    
    m_pContainer->removeAllChildren();
    MB_PetTemplate* pTemplate = pData->getTemplete();
    if (pTemplate)
    {
        MB_NodeDestiny* pNode = NULL;
        int index = 0;
        for (int i=0; i<5; ++i)
        {
            MB_DestinyData* data = MB_DestinyMgr::getInstance()->getDestinyDataByID(pTemplate->getDestinyByIndex(i));
            if (data)
            {
                pNode = MB_NodeDestiny::create(data,pData->getPetID() != 0 && MB_TeamData::getInstance()->IsFindInTeam(data->getDestinyNeed1()));
                if (pNode)
                {
                    m_pContainer->addChild(pNode);
                    pNode->setPosition((i%2 + 0.5)*pNode->getContentSize().width,(i/2 + 0.5)*pNode->getContentSize().height);
                    ++index;
                }
            }
        }
    }
    
    return true;
}
bool MB_NodeDestinyContainer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pContainer",CCNode*,m_pContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeSize", CCNode*, m_pNodeSize);
	return false;
}

