//
//  MB_DailyInterface.h
//  ProjectPM
//
//  Created by ywg on 14-6-6.
//
//

#ifndef __ProjectMB__MB_DailyInterface__
#define __ProjectMB__MB_DailyInterface__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"

class MB_DailyInterface:public NSGameFunction::CCFunctionInterface
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

#endif /* defined(__ProjectMB__MB_DailyInterface__) */
