//
//  MB_LayerResourceUpdate.cpp
//  ProjectMB
//
//  Created by wenyong on 24/11/2014.
//
//
#include "MB_LayerResourceUpdate.h"
#include "../Common/GameLib/GameHelper/CCGameHelper.h"
MB_LayerResourceUpdate::MB_LayerResourceUpdate()
{
    m_pUpdateDetail	 = NULL;
    m_pProgressBg = NULL;
    m_pProgressBanner = NULL;
    m_pTarget = NULL;
    m_pFunc = NULL;

    m_szResPath = "res/main_layer_launch.ccbi";
}

bool MB_LayerResourceUpdate::init()
{
    MB_ResWindow::init();
    
    CCNode* pNode = loadResource(m_szResPath.c_str());
    if (pNode)
	{
        addChild(pNode);
        m_pProgress = NSGameHelper::makeProgressBar(m_pProgressBanner);
        m_pProgress->setPercentage(0);
        return true;
    }
    
    return false;
}

MB_LayerResourceUpdate::~MB_LayerResourceUpdate()
{
    CC_SAFE_RELEASE_NULL(m_pUpdateDetail);
    CC_SAFE_RELEASE_NULL(m_pProgressBanner);
    CC_SAFE_RELEASE_NULL(m_pProgressBg);
}


void MB_LayerResourceUpdate::setUpdateDetail(const char* pDetail)
{
    m_pUpdateDetail->setString(pDetail);
}

void MB_LayerResourceUpdate::visibleProgress(bool bVisible)
{
    m_pProgressBg->setVisible(bVisible);
    m_pProgressBanner->setVisible(bVisible);
}

void MB_LayerResourceUpdate::setUpdatePercent(int perCent)
{
//    char buf[16] = {};
//    sprintf(buf,"%d%%", perCent);
    m_pProgress->setPercentage((float)perCent);
}

void MB_LayerResourceUpdate::onResetWnd()
{
    
}

bool MB_LayerResourceUpdate::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pUpdateDetail",CCLabelTTF*,m_pUpdateDetail);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pProgressBanner",CCSprite*,m_pProgressBanner);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pProgressBg",CCSprite*,m_pProgressBg);
	return false;
}

SEL_MenuHandler MB_LayerResourceUpdate::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MB_LayerResourceUpdate::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

void MB_LayerResourceUpdate::setClickCallback(CCObject* pTarget,SEL_CallFunc pFunc)
{
    m_pTarget = pTarget;
    m_pFunc = pFunc;
}
