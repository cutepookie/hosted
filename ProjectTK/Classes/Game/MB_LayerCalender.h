//
//  MB_LayerCalender.h
//  ProjectMB
//
//  Created by wenyong on 14-8-28.
//
//

#ifndef __ProjectMB__MB_LayerCalender__
#define __ProjectMB__MB_LayerCalender__

#include "MB_ResWindow.h"

class MB_LayerCalender : public MB_ResWindow
{
public:
    MB_LayerCalender();
    ~MB_LayerCalender();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    CREATE_FUNC(MB_LayerCalender);
    virtual bool init();
    virtual void onResetWnd();
    static int getWeekDayOfLastDay(tm* pt);
    static int getDaysInMonth(int y,int m);

protected:
    
};

#endif /* defined(__ProjectMB__MB_LayerCalender__) */
