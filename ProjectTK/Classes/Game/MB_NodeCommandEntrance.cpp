//
//  MB_NodeCommandEntrance.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-10.
//
//

#include "MB_NodeCommandEntrance.h"
#include "MB_FunctionConfig.h"
#include "MB_RoleData.h"



MB_NodeCommandEntrance::MB_NodeCommandEntrance()
{
    m_pAnimation = NULL;
}

MB_NodeCommandEntrance::~MB_NodeCommandEntrance()
{
    CC_SAFE_RELEASE_NULL(m_pAnimation);
}
bool MB_NodeCommandEntrance::init()
{
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/main_node_homepage.ccbi", this);
    if (pNode == NULL)
    {
        CC_SAFE_RELEASE(pCCBReader);
        return false;
    }
    this->addChild(pNode);
    m_pAnimation = pCCBReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pAnimation);
    CC_SAFE_RELEASE(pCCBReader);
    onInitializedWnd();
    return true;
};

void MB_NodeCommandEntrance::onResetWnd()
{
    if (m_pDataSource)
    {
        uint32_t kType = ((NSGameFunction::CCFunctionInterface*)m_pDataSource)->getFunctionType();
        MB_FunctionItem* pItem =  MB_FunctionConfigure::getInstance()->queryFunctionItemByType(kType);
        if (pItem)
        {
            if(pItem->getNeedLevel()<=MB_RoleData::getInstance()->getLevel())
            {
                setEnable();
            }
            else
            {
                setDisable();
            }
        }
    }
    m_pFlagNode2->setVisible(false);
}

void MB_NodeCommandEntrance::setEff(bool bShow)
{
    m_pFlagNode2->setVisible(bShow);
}
