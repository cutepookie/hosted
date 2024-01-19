//
//  MB_LayerScorll.h
//  ProjectMB
//
//  Created by yuanwugang on 14-9-2.
//
//

#ifndef __ProjectMB__MB_LayerScorll__
#define __ProjectMB__MB_LayerScorll__

#include "MB_ResWindow.h"


class MB_LayerScorll:public MB_ResWindow
{
public:
    MB_LayerScorll();
    virtual ~MB_LayerScorll();
    static MB_LayerScorll* create(CCSize size);
    virtual bool init(CCSize size);
    void onResetWnd();
    void addShowNode(CCNode* node);
    void move(float dx);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
    
    void moveTick(float dt);
    void beforeDraw();
    void afterDraw();
    CCRect getViewRect();
    void visit();
    void runCards(float time,float MaxVelocity);
private:
    CCSize m_szNodeSize;
    CCArray* m_pArray;
    CCPoint m_TouchBegain;
    bool    m_bInMove;
    float   m_fVelocity;
    float   m_fNormalVelocity;
    float   m_fMaxVelocity;
    float   m_fRunTime;
    float   m_fMaxRunTime;
    
};

#endif /* defined(__ProjectMB__MB_LayerScorll__) */
