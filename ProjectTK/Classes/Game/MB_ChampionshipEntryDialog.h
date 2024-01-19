//
//  MB_ChampionshipEntryDialog.h
//  ProjectPM
//
//  Created by chk on 14-3-24.
//
//

#ifndef __ProjectMB__MB_ChampionshipEntryDialog__
#define __ProjectMB__MB_ChampionshipEntryDialog__

#include "MB_NodeBannerEntry.h"
class MB_Championship;

//爭霸入口窗口
class MB_ChampionshipEntryDialog:public MB_NodeBannerEntry
{
    friend class MB_Championship;
private:
    MB_ChampionshipEntryDialog();
public:
    static MB_ChampionshipEntryDialog* create();
    ~MB_ChampionshipEntryDialog();
    virtual void onResetWnd();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
};


#endif /* defined(__ProjectMB__MB_ChampionshipEntryDialog__) */
