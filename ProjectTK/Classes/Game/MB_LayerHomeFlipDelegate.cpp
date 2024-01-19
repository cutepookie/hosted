//
//  MB_LayerHomeFlipDelegate.cpp
//  ProjectPM
//
//  Created by WenYong on 14-5-12.
//
//

#include "MB_LayerHomeFlipDelegate.h"
void MB_LayerFlipWindow::setCallBack(CCObject* pTarget,SEL_CallFunc onLeft,SEL_CallFunc onRight)
{
    CC_SAFE_RELEASE_NULL(m_pDalegate);
    m_pDalegate = pTarget;
    m_pOnFunctionLeft = onLeft;
    m_pOnFunctionRight = onRight;
    CC_SAFE_RETAIN(m_pDalegate);
}
void MB_LayerFlipWindow::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint pt = pTouch->getLocationInView();
    if (pt.x > getContentSize().width
        || pt.x < 0
        || pt.y > getContentSize().height
        || pt.y < 0)
    {
        return;
    }
    if (m_TouchBegain.x < 0)
    {
        return;
    }
    
    if (pt.x - m_TouchBegain.x > m_fDelta)
    {
        if(m_pDalegate)
        {
            (m_pDalegate->*m_pOnFunctionLeft)();
        }
    }
    else if (pt.x - m_TouchBegain.x < -m_fDelta)
    {
        if (m_pDalegate)
        {
            (m_pDalegate->*m_pOnFunctionRight)();
        }
    }
    
    m_TouchBegain.x = -1.0;
}

bool MB_LayerFlipWindow::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    m_TouchBegain = pTouch->getLocationInView();
    
    return true;
}

void MB_LayerFlipWindow::registerWithTouchDispatcher(void)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 1 , false);
}

void MB_LayerFlipFunctionWnd::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint pt = pTouch->getLocationInView();
    if (m_TouchBegain.y < 0)
    {
        return;
    }
    
    if (pt.y - m_TouchBegain.y > m_fDelta)
    {
        onFlipRight();
    }
    else if (pt.y - m_TouchBegain.y < -m_fDelta)
    {
        onFlipLeft();
    }
    
    m_TouchBegain.y = -1.0;
}

bool MB_LayerFlipFunctionWnd::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    m_TouchBegain = pTouch->getLocationInView();
    
    return true;
}

void MB_LayerFlipFunctionWnd::registerWithTouchDispatcher(void)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 1 , false);
}