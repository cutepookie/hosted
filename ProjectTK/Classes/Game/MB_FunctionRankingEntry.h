//
//  MB_FunctionRankingEntry.h
//  ProjectMB
//
//  Created by wenyong on 14-12-24.
//
//

#ifndef __ProjectMB__MB_FunctionRankingEntry__
#define __ProjectMB__MB_FunctionRankingEntry__

#include "MB_NodeCommandEntrance.h"

class MB_FunctionRankingEntry:public MB_FunctionEntranceWnd
{
public:
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onEntranceClicked(CCObject* pSender);
};


#endif /* defined(__ProjectMB__MB_FunctionRankingEntry__) */
