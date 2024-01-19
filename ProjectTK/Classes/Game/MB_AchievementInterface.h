//
//  MB_AchievementInterface.h
//  ProjectPM
//
//  Created by crimoon on 14-6-6.
//
//

#ifndef __ProjectMB__MB_AchievementInterface__
#define __ProjectMB__MB_AchievementInterface__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"

class MB_AchievementInterface:public NSGameFunction::CCFunctionInterface
{
public:
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual void onLoadingScene();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
};

#endif /* defined(__ProjectMB__MB_AchievementInterface__) */
