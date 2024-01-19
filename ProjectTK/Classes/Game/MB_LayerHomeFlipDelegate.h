//
//  MB_LayerWindowFlipDelegate.h
//  ProjectPM
//
//  Created by WenYong on 14-5-12.
//
//

#ifndef __ProjectMB__MB_LayerHomeFlipDelegate__
#define __ProjectMB__MB_LayerHomeFlipDelegate__

#include "MB_FunctionMainWnd.h"

#define DELTA_FLIP 100
class MB_LayerFlipWindow;
class MB_FlipDelegate
{
    friend class MB_LayerFlipWindow;
public:
protected:
    virtual void onFlipLeft()=0;
    virtual void onFlipRight()=0;
};
class MB_LayerFlipWindow:public MB_ResWindow,public MB_FlipDelegate
{
    
public:
    MB_LayerFlipWindow():m_fDelta(DELTA_FLIP),m_pDalegate(NULL)
    {
        m_pOnFunctionLeft = NULL;
        m_pOnFunctionRight = NULL;
        m_pDalegate = NULL;
    };
    virtual ~MB_LayerFlipWindow()
    {
        CC_SAFE_RELEASE_NULL(m_pDalegate);
        m_pOnFunctionLeft = NULL;
        m_pOnFunctionRight = NULL;
    };
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
    void setCallBack(CCObject* pTarget,SEL_CallFunc onLeft,SEL_CallFunc onRight);
protected:
    virtual void onFlipLeft(){};
    virtual void onFlipRight(){};
protected:
    CCObject*    m_pDalegate;
    SEL_CallFunc m_pOnFunctionLeft;
    SEL_CallFunc m_pOnFunctionRight;
    CCPoint     m_TouchBegain;
    CC_SYNTHESIZE(float, m_fDelta, Delta);
};

class MB_LayerFlipFunctionWnd:public MB_FunctionMainWnd
{
public:
    MB_LayerFlipFunctionWnd():m_fDelta(DELTA_FLIP){};
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
    virtual void onFlipLeft()=0;
    virtual void onFlipRight()=0;
protected:
    CCPoint     m_TouchBegain;
    CC_SYNTHESIZE(float, m_fDelta, Delta);
};

#endif /* defined(__ProjectMB__MB_LayerHomeFlipDelegate__) */
