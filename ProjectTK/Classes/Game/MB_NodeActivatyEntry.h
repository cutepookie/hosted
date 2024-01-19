//
//  MB_NodeActivatyEntry.h
//  ProjectPM
//
//  Created by WenYong on 14-4-10.
//
//

#ifndef __ProjectMB__MB_NodeActivatyEntry__
#define __ProjectMB__MB_NodeActivatyEntry__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"
#include "MB_NodeHoverEntry.h"

class MB_NodeActivatyEntry:public MB_NodeHoverEntry
{
public:
    static MB_NodeActivatyEntry* create();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    void onResetWnd();
};



#endif /* defined(__ProjectMB__MB_NodeActivatyEntry__) */

