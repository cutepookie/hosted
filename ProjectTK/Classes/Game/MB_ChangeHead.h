//
//  MB_ChangeHead.h
//  ProjectPM
//
//  Created by crimoon on 14-4-9.
//
//

#ifndef __ProjectMB__MB_ChangeHead__
#define __ProjectMB__MB_ChangeHead__

#include "Game.h"

class MB_ChangeHead : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_ChangeHead();
    ~MB_ChangeHead();
    static MB_ChangeHead* create();
    
    virtual bool init();
    virtual void onResetWnd();
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    
    bool sendrole_change_head(uint32_t headID);
    bool recvrole_change_head(MB_MsgBuffer *recvPacket);
    
    void onBreakClicked(CCObject *);
    void onDefClicked(CCObject *);
    
    void sortArray();
    void EventTouchDown(CCObject * sender, CCControlEvent controlEvent);
    void EventTouchDragEnter(CCObject * sender, CCControlEvent controlEvent);
    void onDetailClicked(cocos2d::CCObject *sender);
private:
    CCArray* m_pIconArray;
    CCNode *m_pContainer;
    CCSprite *m_pHead;
    CCScrollView* m_pScrollView;
    CCSize m_cellSize;
    bool isChangeIcon;
    //cell控件
    CCSprite* m_pItemIcon;
    CCSprite* m_pIconFrame;
    CCControlButton* m_pDetailButton;
    CCNode* m_pActiveNode;
    bool isReset;
};

#endif /* defined(__ProjectMB__MB_ChangeHead__) */
