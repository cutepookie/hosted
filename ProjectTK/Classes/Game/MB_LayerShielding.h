//
//  MB_LayerShielding.h
//  ProjectPM
//
//  Created by WenYong on 14-5-8.
//
//

#ifndef __ProjectMB__MB_LayerShielding__
#define __ProjectMB__MB_LayerShielding__

#include "MB_ResWindow.h"

class MB_LayerUnTouchable : public CCLayer
{
public:

    CREATE_FUNC(MB_LayerUnTouchable);          // 全屏遮挡
    static MB_LayerUnTouchable* create1();     // 菜单栏可触摸
    static MB_LayerUnTouchable* create12();    // 菜单栏和头像可触摸
    void center();
    void top();
    void buttom();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
private:
    virtual bool init();
};
class MB_LayerUnTouchable2 : public CCLayer
{
public:
    
    CREATE_FUNC(MB_LayerUnTouchable2);          // 全屏遮挡，层级最高
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
private:
    virtual bool init();
};
#endif /* defined(__ProjectMB__MB_LayerShielding__) */
