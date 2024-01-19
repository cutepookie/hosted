//
//  MB_NodeCommandEntrance.h
//  ProjectPM
//
//  Created by WenYong on 14-4-10.
//
//

#ifndef __ProjectMB__MB_NodeCommandEntrance__
#define __ProjectMB__MB_NodeCommandEntrance__

#include "MB_FunctionEntranceWnd.h"

class MB_NodeCommandEntrance:public MB_FunctionEntranceWnd
{
public:
    MB_NodeCommandEntrance();
    virtual ~MB_NodeCommandEntrance();
    virtual bool init();
    virtual void onResetWnd();
    void setEff(bool bShow);
private:
    CCBAnimationManager* m_pAnimation;
};

#endif /* defined(__ProjectMB__MB_NodeCommandEntrance__) */
