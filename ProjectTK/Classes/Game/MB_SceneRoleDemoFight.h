//
//  MB_SceneRoleDemoFight.h
//  ProjectMB
//
//  Created by wenyong on 15-1-22.
//
//

#ifndef __ProjectMB__MB_SceneRoleDemoFight__
#define __ProjectMB__MB_SceneRoleDemoFight__
#include "MB_ResWindow.h"

class MB_SceneRoleDemoFight : public CCLayer
{
public:
    CREATE_FUNC(MB_SceneRoleDemoFight);
    MB_SceneRoleDemoFight();
    ~MB_SceneRoleDemoFight();
    static CCScene* scene();
    
    void start();

    void onMsgRecv(CCNode* node, SocketResponse* response);
protected:
    void send_role_demo_fight();
    void recv_role_demo_fight(MB_MsgBuffer* );
    
private:
    
};

#endif /* defined(__ProjectMB__MB_SceneRoleDemoFight__) */
