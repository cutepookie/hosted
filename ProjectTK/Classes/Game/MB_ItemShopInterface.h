//
//  MB_ItemShopInterface.h
//  ProjectMB
//
//  Created by chenhongkun on 14-9-1.
//
//

#ifndef __ProjectMB__MB_ItemShopInterface__
#define __ProjectMB__MB_ItemShopInterface__
#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"
//神秘商店
class MB_ItemShopInterface:public NSGameFunction::CCFunctionInterface
{
public:
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual void onLoadingScene();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    virtual void onDayPassed();
};

#endif /* defined(__ProjectMB__MB_ItemShopInterface__) */
