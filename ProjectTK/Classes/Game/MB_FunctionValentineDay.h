//
//  MB_FunctionValentineDay.h
//  ProjectMB
//
//  Created by wenyong on 15-1-22.
//
//

#ifndef __ProjectMB__MB_FunctionValentineDay__
#define __ProjectMB__MB_FunctionValentineDay__

#include "MB_FunctionFestival.h"

class MB_FunctionValentineDay : public  MB_FunctionFestival
{
public:
    virtual uint16_t getFunctionType();
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual MB_ResWindow* createRankDialog();
};

#endif /* defined(__ProjectMB__MB_FunctionValentineDay__) */
