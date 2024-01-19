//
//  MB_LayerShielding.cpp
//  ProjectPM
//
//  Created by WenYong on 14-5-8.
//
//

#include "MB_LayerShielding.h"
#include "Game.h"

static ccColor4B color = ccc4(125,125,125,125);
bool MB_LayerUnTouchable::init()
{
//    CCLayerColor::initWithColor(color);
    CCLayer::init();
    setTouchEnabled(true);
    center();
    return true;
}

bool MB_LayerUnTouchable::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pEvent);
    CCRect rc(m_obPosition.x,m_obPosition.y,m_obContentSize.width,m_obContentSize.height);
    if (!rc.containsPoint(pTouch->getLocation()))
    {
        return false;
    }
    return true;
}

void MB_LayerUnTouchable::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void MB_LayerUnTouchable::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}

void MB_LayerUnTouchable::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}


void MB_LayerUnTouchable::center()
{
    CCSize sz1 = m_obContentSize;
    CCSize sz2 = CCDirector::sharedDirector()->getWinSize();
    CCPoint pt((sz2.width-sz1.width)/2.0,(sz2.height-sz1.height)/2.0);
    setPosition(pt);
}

void MB_LayerUnTouchable::top()
{
    setAnchorPoint(ccp(0, 1));
    CCSize sz = CCDirector::sharedDirector()->getWinSize();
    setPosition(0,sz.height-m_obContentSize.height);
}
void MB_LayerUnTouchable::buttom()
{
    setPosition(0,0);
}


MB_LayerUnTouchable* MB_LayerUnTouchable::create1()
{
    MB_LayerUnTouchable* p = create();
    if (p)
    {
        p->m_obContentSize.height -= 100;
        p->setContentSize(p->m_obContentSize);
        p->top();
    }
    return p;
}

void MB_LayerUnTouchable::registerWithTouchDispatcher(void)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

MB_LayerUnTouchable* MB_LayerUnTouchable::create12()
{
    MB_LayerUnTouchable* p = create();
    if (p)
    {
        p->m_obContentSize.height -= 200;
        p->setContentSize(p->m_obContentSize);
        p->center();
    }
    return p;
}
bool MB_LayerUnTouchable2::init()
{
    CCLayer::init();
    setTouchEnabled(true);
    return true;
}
void MB_LayerUnTouchable2::registerWithTouchDispatcher(void)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this,-999, true);
}
bool MB_LayerUnTouchable2::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}
