
#ifndef __ProjectMB__MB_SceneReconnect__
#define __ProjectMB__MB_SceneReconnect__
#include "Game.h"
class MB_SceneReconnect:public CCLayer{
    
public:
    
    MB_SceneReconnect();
    ~MB_SceneReconnect();
    static CCScene *scene();
    static MB_SceneReconnect *create();
    bool init();
};
#endif /* defined(__ProjectMB__File__) */
