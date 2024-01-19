//
//  MB_FunctionEntery2ActivatyEntery.cpp
//  ProjectMB
//
//  Created by wenyong on 15-1-13.
//
//

#include "MB_FunctionEntery2ActivatyEntery.h"
#include "MB_FunctionConfig.h"
#include "MB_ActivatyMainLayer.h"
#include "MB_ActivatyMgr.h"

bool MB_FunctionEntery2ActivatyEntery::init()
{
    MB_ResWindow::init();
    CCNode * node = loadResource("res/activity_node_btn.ccbi");
    if(node)
    {
        this->addChild(node);
        if(m_pChoose)
            m_pChoose->setVisible(false);
        onInitializedWnd();
        return true;
    }
    return false;
}

MB_FunctionEntery2ActivatyEntery::MB_FunctionEntery2ActivatyEntery()
{
    m_nConvertedActivityID = 0;
    m_pInterface = NULL;
}


void MB_FunctionEntery2ActivatyEntery::onInitializedWnd()
{
    if (m_pInterface)
    {
        MB_FunctionItem* pItem = MB_FunctionConfigure::getInstance()->queryFunctionItemByType(m_pInterface->getFunctionType());
        if (pItem)
        {
            m_pName->setString(pItem->getFunctionName().c_str());
            MB_FunctionConfigure::getInstance()->loadResource2SpriteCache();
            CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pItem->getEnableFile().c_str());
            if (pFrame && m_pIcon)
            {
                m_pIcon->setDisplayFrame(pFrame);
            }
        }
    }
}

bool MB_FunctionEntery2ActivatyEntery::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = pDataSource;
    return setFunction(dynamic_cast<NSGameFunction::CCFunctionInterface*>(pDataSource));
}

bool MB_FunctionEntery2ActivatyEntery::setFunction(NSGameFunction::CCFunctionInterface* pFunction)
{
    m_pInterface = pFunction;
    if (m_pInterface)
    {
        m_nConvertedActivityID = m_pInterface->getActivityID();
        return true;
    }
    return false;
}

int MB_FunctionEntery2ActivatyEntery::getActivityID()
{
    return m_nConvertedActivityID;
}

void MB_FunctionEntery2ActivatyEntery::enter()
{
    if (m_pInterface)
    {
        MB_ResWindow* pWnd = m_pInterface->createFunctionDialog();
        if (m_pMainWnd && pWnd)
        {
            m_pMainWnd->movetoShow(getActivityID());
            m_pMainWnd->setCurActivaty(pWnd);
            MB_ActivatyMgr::getInstance()->lockEntry(this);
            
        }
    }
}

void MB_FunctionEntery2ActivatyEntery::onEntranceClicked(CCObject* pSender)
{
    enter();
}
