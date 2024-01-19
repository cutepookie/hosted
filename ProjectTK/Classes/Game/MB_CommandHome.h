//
//  MB_CommandHome.h
//  ProjectPM
//
//  Created by WenYong on 14-4-10.
//
//

#ifndef __ProjectMB__MB_CommandHome__
#define __ProjectMB__MB_CommandHome__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"

class MB_CommandHome:public NSGameFunction::CCFunctionInterface
{
public:
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual void onLoadingScene();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    virtual void onEntryClicked(CCObject* pSender);
};

#endif /* defined(__ProjectMB__MB_CommandHome__) */
