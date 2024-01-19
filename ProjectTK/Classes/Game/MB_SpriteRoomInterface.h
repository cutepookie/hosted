//
//  MB_SpriteRoomInterface.h
//  ProjectPM
//
//  Created by WenYong on 14-4-14.
//
//

#ifndef __ProjectMB__MB_SpriteRoomInterface__
#define __ProjectMB__MB_SpriteRoomInterface__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"

class MB_SpriteRoomInterface:public NSGameFunction::CCFunctionInterface
{
public:
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual void onLoadingScene();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
};


#endif /* defined(__ProjectMB__MB_SpriteRoomInterface__) */
