//
//  MB_FunctionPvpRoot.h
//  ProjectPM
//
//  Created by WenYong on 14-3-26.
//
//

#ifndef __ProjectMB__MB_FunctionPvpRoot__
#define __ProjectMB__MB_FunctionPvpRoot__

#include "MB_FunctionPveRoot.h"

class MB_FunctionPvpMain:public MB_FunctionPveMain
{
public:
    CREATE_FUNC(MB_FunctionPvpMain);
protected:
    virtual bool initFunctions();
    virtual bool init();
};

#endif /* defined(__ProjectMB__MB_FunctionPvpRoot__) */
