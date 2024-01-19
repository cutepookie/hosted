//
//  MB_FunctionActivityDesc.cpp
//  ProjectMB
//
//  Created by wenyong on 15-1-15.
//
//

#include "MB_FunctionActivityDesc.h"

void MB_FunctionActivityDesc::tickTime(float dt)
{
    int timelift = m_nCloseTime -MB_ClientSocket::getInstance()->getServerTime();
    char databuf[50];
    sprintf(databuf,"%d天%02d时%02d分%02d秒",timelift/(3600*24),timelift%(3600*24)/3600,timelift%3600/60,timelift%3600%60);
    m_pTimeCount->setString(databuf);
}