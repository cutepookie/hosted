//
//  MB_GlobelModalDlgMsgQueue.h
//  ProjectPM
//
//  Created by WenYong on 14-5-26.
//
//

#ifndef __ProjectMB__MB_GlobelModalDlgMsgQueue__
#define __ProjectMB__MB_GlobelModalDlgMsgQueue__

#include "cocos2d.h"
USING_NS_CC;

class MB_ResWindow;

class MB_GlobelAchievementMsgQueue : public CCObject
{
public:
    MB_GlobelAchievementMsgQueue();
    ~MB_GlobelAchievementMsgQueue();
    void addMsgWnd(MB_ResWindow* pWnd);
    void addMsgWndQueue(CCArray* pQueue);
    void insertAtIndex(MB_ResWindow* pWnd,int index);
//    CCObject* queryObjectAtIndex(int index);
    virtual void popFront();
    int msgCount();
    static void onEnter();
    void clearMsg();
protected:
    CCArray*            m_pMsgQueue;
};
class MB_GlobelModalDlgMsgQueue:public MB_GlobelAchievementMsgQueue
{
public:
    static MB_GlobelModalDlgMsgQueue* getInstance();
    static void destroyInstance();
    virtual void popFront();
private:
    MB_GlobelModalDlgMsgQueue(){};
private:
    static MB_GlobelModalDlgMsgQueue* m_pInstance;
};

#endif /* defined(__ProjectMB__MB_GlobelModalDlgMsgQueue__) */
