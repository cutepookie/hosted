//
//  MB_NodeResearchInstituteEntry.h
//  ProjectPM
//
//  Created by chk on 14-4-14.
//
//

#ifndef __ProjectMB__MB_NodeResearchInstituteEntry__
#define __ProjectMB__MB_NodeResearchInstituteEntry__

#include "MB_NodeBannerEntry.h"

class MB_NodeResearchInstituteEntry:public MB_NodeBannerEntry
{
public:
    static MB_NodeResearchInstituteEntry* create();
    MB_NodeResearchInstituteEntry();
    ~MB_NodeResearchInstituteEntry();
    virtual void onResetWnd();
    void onMsgRecv(CCNode* node, SocketResponse* response);
    
    void UpDataState(float dt);
};

#endif /* defined(__ProjectMB__MB_NodeResearchInstituteEntry__) */
