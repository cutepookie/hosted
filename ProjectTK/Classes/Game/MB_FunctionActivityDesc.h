//
//  MB_FunctionActivityDesc.h
//  ProjectMB
//
//  Created by wenyong on 15-1-15.
//
//

#ifndef __ProjectMB__MB_FunctionActivityDesc__
#define __ProjectMB__MB_FunctionActivityDesc__

#include "MB_LayerEventDiscription.h"

class MB_FunctionActivityDesc : public MB_LayerEventDiscription
{
public:
    CREATE_FUNC(MB_FunctionActivityDesc);
    virtual void onMsgRecv(CCNode* node, SocketResponse* response){};
    virtual void tickTime(float dt);
};


#endif /* defined(__ProjectMB__MB_FunctionActivityDesc__) */
