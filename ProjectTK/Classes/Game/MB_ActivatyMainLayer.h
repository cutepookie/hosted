//
//  MB_ActivatyMainLayer.h
//  ProjectPM
//
//  Created by cri-mac on 14-4-30.
//
//

#ifndef __ProjectMB__MB_ActivatyMainLayer__
#define __ProjectMB__MB_ActivatyMainLayer__
#include "MB_ResWindow.h"
#include "MB_FunctionModule.h"
#include "MB_CommandActivaty.h"
class MB_NodeConfigActivatyEntry;
class MB_FunctionEntery2ActivatyEntery;
//活動主窗口
class MB_ActivatyMainLayer:public CCFunctionWnd
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
,public cocos2d::extension::CCScrollViewDelegate
{
    friend class MB_NodeConfigActivatyEntry;
    friend class MB_NodeSubActivatyEntry;
    friend class MB_FunctionEntery2ActivatyEntery;
public:
    MB_ActivatyMainLayer();
    virtual ~MB_ActivatyMainLayer();
    virtual bool init();
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    
    static MB_ActivatyMainLayer * create();
    
    
    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view);
    void onCloseClick(CCObject*);
    void setShowActivatyID(int activatyID);
    bool clickedActivatyIcon(int activatyID);
    void movetoShow(int activatyID);
protected:
    void setCurActivaty(MB_ResWindow* player);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    bool initFunctions();
    bool recvactivity_info(MB_MsgBuffer* recvPacket);
    void resetNodePos();
    
    
    void whenMoveOver();
private:
    CCNode* m_pNodeNaveigation;
    CCNode* m_pNodeActivatyContainer;
    

    int     m_nShowIndex;
    
    CCScrollView* m_pScollerView;
    bool    m_bMove;
    float m_nMoveSpeed;
};


#endif /* defined(__ProjectMB__MB_ActivatyMainLayer__) */
