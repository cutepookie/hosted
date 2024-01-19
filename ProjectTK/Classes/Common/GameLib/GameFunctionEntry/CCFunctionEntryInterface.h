//
//  CCFunctionEntryInterface.h
//  ProjectTK
//
//  Created by crimoon00007 on 14-2-28.
//
//

#ifndef __ProjectMB__CCFunctionEntryInterface__
#define __ProjectMB__CCFunctionEntryInterface__

#include "../../../Game/MB_ResWindow.h"
#include <map>

class MB_FunctionActivatedTip;

namespace NSGameFunction
{

    enum FunctionType
    {

    };
    
    class CCFunctionDataSource
    {
    public:
        virtual void onLoadingScene()=0;
        virtual void onMsgRecv(CCNode* node, SocketResponse* response)=0;
        virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv){};
    private:
    };

    class CCFunctionInterface:public CCObject,public CCFunctionDataSource
    {
    public:
        virtual MB_ResWindow* createEntryDialog()=0;
        virtual MB_ResWindow* createFunctionDialog()=0;
        virtual bool allowShow()=0;
        virtual uint16_t getFunctionType(){return 0;}
        virtual void onEntryClicked(CCObject* pSender);
        static void replaceMainSceneLayer(MB_ResWindow* pWnd);
        static void replaceMainSceneSubLayer(MB_ResWindow* pWnd);
        static MB_ResWindow* getCurrentFunctionWnd();
        static void goFunctionHome();
        static void removeUnusedResource();
        virtual bool onRoleLevelUp(int nRoleLevel);
        virtual void onEnterThisFunction(CCObject* pSender);
        virtual void onCloseMainDialog(CCObject* pSender);
        virtual void onMsgRecv(CCNode* node, SocketResponse* response);
        virtual MB_FunctionActivatedTip* createFunctionTipsByLevel(int nRoleLevel);
        virtual void onDayPassed(){}
        virtual int getActivityID(){return getFunctionType()+100000;}
    protected:

    };

    class CCActivityInterface:public CCFunctionInterface
    {
    public:
        virtual bool isOpen()=0;
        virtual void onEntryClicked(CCObject* pSender);
    };

    class CCFunctionWnd:public MB_ResWindow,public CCFunctionDataSource
    {
    protected:
        CCFunctionWnd():m_pDataSource(NULL){};
        virtual bool setDataSource(CCFunctionDataSource* pDataSource)=0;
        virtual void onLoadingScene(){}
        virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    protected:
        CCFunctionDataSource*       m_pDataSource;
    };
}

#endif /* defined(__ProjectMB__CCFunctionEntryInterface__) */
