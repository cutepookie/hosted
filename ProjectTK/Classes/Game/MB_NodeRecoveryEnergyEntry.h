  //
//  MB_NodeRecoveryEnergyEntry.h
//  ProjectPM
//
//  Created by chk on 14-4-29.
//
//

#ifndef __ProjectMB__MB_NodeRecoveryEnergyEntry__
#define __ProjectMB__MB_NodeRecoveryEnergyEntry__


#include "MB_NodeHoverEntry.h"
class MB_RecoveryEnergyInterface;

class MB_NodeRecoveryEnergyEntry:public MB_NodeHoverEntry
{
    friend class MB_RecoveryEnergyInterface;
    MB_NodeRecoveryEnergyEntry(){}
    void tick(float dt);
public:
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onEntranceClicked(CCObject* pSender);
};

#endif /* defined(__ProjectMB__MB_NodeRecoveryEnergyEntry__) */
