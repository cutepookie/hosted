//
//  MB_LayerAnimation.cpp
//  ProjectMB
//
//  Created by wenyong on 15-1-22.
//
//

#include "MB_LayerAnimation.h"
#include "../Common/GameLib/GameHelper/CCGameHelper.h"

MB_LayerAnimation::MB_LayerAnimation()
{
    m_pAnimation = NULL;
    m_pTarget = NULL;
    m_pCallBack = NULL;
}

MB_LayerAnimation::~MB_LayerAnimation()
{
    CC_SAFE_RELEASE_NULL(m_pAnimation);
    m_pTarget = NULL;
    m_pCallBack = NULL;
}

MB_LayerAnimation* MB_LayerAnimation::create(const char* pRes)
{
    MB_LayerAnimation* pInstance = new MB_LayerAnimation;
    if (pInstance && pInstance->init(pRes))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

bool MB_LayerAnimation::init(const char* pRes)
{
    CCLayer::init();
    
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile(pRes);
    
    if (pNode)
    {
        addChild(NSGameHelper::createDisableTouchLayer());
        addChild(pNode);
        m_pAnimation = pCCBReader->getAnimationManager();
        CC_SAFE_RETAIN(m_pAnimation);
        return true;
    }
    
    return false;
}

void MB_LayerAnimation::runAnimationWithCallBack(const char* pTimeLine,CCObject* pTarget,SEL_CallFuncN callback)
{
    if (pTimeLine && m_pAnimation)
    {
        m_pTarget = pTarget;
        m_pCallBack = callback;
        
        m_pAnimation->setAnimationCompletedCallback(this, callfunc_selector(MB_LayerAnimation::timeLineCallBack));
        runAnimation(pTimeLine);
    }
}

void MB_LayerAnimation::runAnimation(const char* pTimeLine)
{
    if (m_pAnimation && pTimeLine)
    {
        m_pAnimation->runAnimationsForSequenceNamed(pTimeLine);
    }
}

void MB_LayerAnimation::timeLineCallBack()
{
    if (m_pAnimation)
    {
        m_pAnimation->setAnimationCompletedCallback(NULL, NULL);
        if (m_pTarget && m_pCallBack)
        {
            (m_pTarget->*m_pCallBack)(this);
        }
    }
}