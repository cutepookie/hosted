//
//  MB_NodeHomeEntry.h
//  ProjectPM
//
//  Created by WenYong on 14-4-10.
//
//

#ifndef __ProjectMB__MB_NodeHomeEntry__
#define __ProjectMB__MB_NodeHomeEntry__

#include "MB_NodeCommandEntrance.h"

class MB_NodeHomeEntry:public MB_NodeCommandEntrance
{
public:
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
};

#endif /* defined(__ProjectMB__MB_NodeHomeEntry__) */
