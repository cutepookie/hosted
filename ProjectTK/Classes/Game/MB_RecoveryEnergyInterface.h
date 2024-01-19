//
//  MB_RecoveryEnergyInterface.h
//  ProjectPM
//
//  Created by chk on 14-4-29.
//
//

#ifndef __ProjectMB__MB_RecoveryEnergyInterface__
#define __ProjectMB__MB_RecoveryEnergyInterface__

#include "MB_CommandActivaty.h"
//补充体力
class MB_RecoveryEnergyInterface:public MB_CommandActivaty
{
public:
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual void onLoadingScene();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
};


#endif /* defined(__ProjectMB__MB_RecoveryEnergyInterface__) */
