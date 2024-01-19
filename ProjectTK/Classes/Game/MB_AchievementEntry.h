//
//  MB_AchievementEntry.h
//  ProjectPM
//
//  Created by crimoon on 14-6-6.
//
//

#ifndef __ProjectMB__MB_AchievementEntry__
#define __ProjectMB__MB_AchievementEntry__

//#include "MB_NodeCommandEntrance.h"
#include "MB_NodeHoverEntry.h"

class MB_AchievementEntry:public MB_NodeHoverEntry
{
public:
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onResetWnd();
private:
};

#endif /* defined(__ProjectMB__MB_AchievementEntry__) */
