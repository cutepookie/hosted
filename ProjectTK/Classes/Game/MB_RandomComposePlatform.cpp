//
//  MB_RandomComposePlatform.cpp
//  ProjectPM
//
//  Created by cri-mac on 14-5-9.
//
//

#include "MB_RandomComposePlatform.h"


MB_RandomComposePlatform* MB_RandomComposePlatform::create(int nType)
{
    MB_RandomComposePlatform* pInstance = new MB_RandomComposePlatform;
    if (pInstance && pInstance->init(0,nType))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return pInstance;
}

void MB_RandomComposePlatform::onCloseClicked(CCObject*)
{
    if(m_bInAnimation)return;
//    popWindow();
}

bool MB_RandomComposePlatform::init(uint16_t nComposeID,int nType)
{
    MB_ResWindow::init();
    
    m_nComposeID = nComposeID;
    m_PlatformType = kPlatformCount;
    m_pComposeTemplate = MB_ComposeMgr::getInstance()->getComposeTemplateByID(m_nComposeID);
    if (m_pComposeTemplate)
    {
        const int temp[] = {kPlatformCount,kPlatformCount,kPlatform2IN1,kPlatform3IN1,kPlatform4IN1,kPlatform5IN1,kPlatform5IN1Random,kPlatformCount,kPlatformCount};
        m_PlatformType = temp[m_pComposeTemplate->getMaterialCount()];
        m_nType = m_pComposeTemplate->getComposeType();
    }
    else
    {
        m_PlatformType = kPlatform5IN1Random;
        m_nType = nType;
    }
    
    if (m_nType > 2)
    {
        return false;
    }
    if (m_PlatformType >= kPlatformCount)
    {
        return false;
    }
    CC_SAFE_RELEASE_NULL(m_pUnitRoot);
    m_pUnitRoot = loadResource("res/compose_layer_cost.ccbi");
    
    reloadComposeUnit(m_pUnitRoot);
    removeAllChildren();
    addChild(m_pUnitRoot);
    
    for (int i=0; i<5; ++i)
    {
        m_PlatformUint[i].setType(m_nType);
    }
    
    onResetWnd();
    
    return true;
}

void MB_RandomComposePlatform::setType(int type)
{
    m_nType = type;
    for (int i=0; i<5; ++i)
    {
        m_PlatformUint[i].clear();
        m_PlatformUint[i].setType(m_nType);
        
    }
}
