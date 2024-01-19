//
//  MB_LayerCalender.cpp
//  ProjectMB
//
//  Created by wenyong on 14-8-28.
//
//

#include "MB_LayerCalender.h"
#include "MB_FunctionModule.h"
#include "MB_NodeCalenderUnit.h"
#include "MB_ItemData.h"
MB_LayerCalender::MB_LayerCalender()
{
    SOCKET_MSG_REGIST(SC_DAILY_GET_LIST, MB_LayerCalender);
    SOCKET_MSG_REGIST(SC_DAILY_DRAW, MB_LayerCalender);
}

MB_LayerCalender::~MB_LayerCalender()
{
    SOCKET_MSG_UNREGIST(SC_DAILY_GET_LIST);
    SOCKET_MSG_UNREGIST(SC_DAILY_DRAW);
}

void MB_LayerCalender::onMsgRecv(CCNode* node, SocketResponse* response)
{
    onResetWnd();
}

bool MB_LayerCalender::init()
{
    MB_ResWindow::init();
    setAnchorPoint(ccp(0.5, 0));
    onResetWnd();
    
    return true;
}

void MB_LayerCalender::onResetWnd()
{
    
    time_t tt = MB_ClientSocket::getInstance()->getServerTime();
    
    tm* pTm = localtime(&tt);
    
    int lday = getWeekDayOfLastDay(pTm);
    
    CCSize unit_sz = MB_NodeCalenderUnit::getWndSize();
    
    int days = getDaysInMonth(pTm->tm_year+1900, pTm->tm_mon+1);
    int today = pTm->tm_mday;
    CCPoint offset = ccp(unit_sz.width*(lday%7),0 );
    
    MB_NodeCalenderUnit* pUnit = NULL;
    
    removeAllChildren();
    
    std::vector<int> login_record = MB_ItemMgr::getInstance()->getLoginRecordList();
//    int index = 0;
    
    for (int i=days; i>0; --i)
    {
        bool bIsToday = false;
        if (today == i)
        {
            bIsToday = true;
        }

        int nState = kNext;
        for (int j = 0;j < login_record.size(); j++)
        {
            if (i == login_record[j])
            {
                nState = kRegister;
            }
        }
        
        if (today > i)
        {
            if (nState != kRegister)
            {
                nState = kMiss;
            }
        }
        
        pUnit = MB_NodeCalenderUnit::create(i, nState,bIsToday);
        if (pUnit)
        {
            addChild(pUnit);
            pUnit->setPosition(offset);
            --lday;
            if (lday < 0)
            {
                offset.y += unit_sz.height;
                offset.x = unit_sz.width*6;
                lday = 6;
            }
            else
            {
                offset.x -= unit_sz.width;
            }
        }
    }
    
    setContentSize(CCSizeMake(unit_sz.width*7, offset.y+unit_sz.height));
}

int MB_LayerCalender::getDaysInMonth(int y,int m)
{
    int d;
    static int day[]= {31,28,31,30,31,30,31,31,30,31,30,31};
    if (2==m)
    {
        bool b = ((y%4==0)&&(y%100))||((y%400)==0);
        d = b?29:28;
    }
    else
    {
        d=day[m-1];
    }
    return d;
}

int MB_LayerCalender::getWeekDayOfLastDay(tm* pt)
{
    int d = getDaysInMonth(pt->tm_year+1900, pt->tm_mon+1);
    
    return (pt->tm_wday + ((d - pt->tm_mday) % 7) % 7)%7;
}
