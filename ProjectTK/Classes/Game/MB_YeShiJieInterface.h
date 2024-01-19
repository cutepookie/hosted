//
//  MB_YeShiJieInterface.h
//  ProjectPM
//
//  Created by WenYong on 14-5-17.
//
//

#ifndef __ProjectMB__MB_YeShiJieInterface__
#define __ProjectMB__MB_YeShiJieInterface__

#include "MB_FunctionModule.h"
class MB_YeShiJieInterface:public CCFunctionInterface
{
public:
    MB_YeShiJieInterface();
    ~MB_YeShiJieInterface();
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual void onLoadingScene();
    virtual bool allowShow(){return true;};
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual uint16_t getFunctionType();
};

#endif /* defined(__ProjectMB__MB_YeShiJieInterface__) */
