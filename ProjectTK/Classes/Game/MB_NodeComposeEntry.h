//
//  MB_NodeComposeEntry.h
//  ProjectPM
//
//  Created by WenYong on 14-4-11.
//
//

#ifndef __ProjectMB__MB_NodeComposeEntry__
#define __ProjectMB__MB_NodeComposeEntry__

#include "MB_NodeCommandEntrance.h"

class MB_NodeComposeEntry:public MB_FunctionEntranceWnd
{
public:
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
};

#endif /* defined(__ProjectMB__MB_NodeComposeEntry__) */
