//
//  MB_LayerFinalRecordLive.h
//  ProjectPM
//
//  Created by WenYong on 14-4-24.
//
//
// 决赛直播界面
#ifndef __ProjectMB__MB_LayerFinalRecordLive__
#define __ProjectMB__MB_LayerFinalRecordLive__

#include "MB_LayerGroupRecordLive.h"

class MB_LayerFinalRecordLive:public MB_LayerGroupRecordLive
{
public:
    MB_LayerFinalRecordLive();
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual void recvrace_new_fight(MB_MsgBuffer* pRecv);
protected:
    void star();
    void tickRuningSchedule(float dt);
private:
    int  m_nCurrentLength;
    bool m_bIsRuningSchedule;
};

#endif /* defined(__ProjectMB__MB_LayerFinalRecordLive__) */
