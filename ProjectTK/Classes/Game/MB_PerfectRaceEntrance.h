//
//  MB_PerfectRaceEntrance.h
//  ProjectPM
//
//  Created by crimoon on 14-4-14.
//
//

#ifndef __ProjectMB__MB_PerfectRaceEntrance__
#define __ProjectMB__MB_PerfectRaceEntrance__

#include "MB_NodeBannerEntry.h"
class MB_PerfectRaceInterface;
class MB_PerfectRaceEntrance:public MB_NodeBannerEntry
{
public:
    MB_PerfectRaceEntrance();
    ~MB_PerfectRaceEntrance();
    
    virtual void onResetWnd();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    
private:
    MB_PerfectRaceInterface*    m_pPerfectRaceInterface;
};


#endif /* defined(__ProjectMB__MB_PerfectRaceEntrance__) */
