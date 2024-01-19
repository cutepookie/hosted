//
//  MB_LayerAnimation.h
//  ProjectMB
//
//  Created by wenyong on 15-1-22.
//
//

#ifndef __ProjectMB__MB_LayerAnimation__
#define __ProjectMB__MB_LayerAnimation__

#include <cocos2d.h>
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class MB_LayerAnimation : public CCLayer
{
public:
    MB_LayerAnimation();
    virtual ~MB_LayerAnimation();
    static MB_LayerAnimation* create(const char* pRes);
    virtual bool init(const char* pRes);
    void runAnimationWithCallBack(const char* pTimeLine,CCObject* pTarget,SEL_CallFuncN callback);
    void runAnimation(const char* pTimeLine);
private:
    void timeLineCallBack();
private:
    CCBAnimationManager*    m_pAnimation;
    CCObject*               m_pTarget;
    SEL_CallFuncN           m_pCallBack;
};

#endif /* defined(__ProjectMB__MB_LayerAnimation__) */
