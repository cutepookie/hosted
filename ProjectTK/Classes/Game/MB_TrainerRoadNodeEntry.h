//
//  MB_TrainerRoadNodeEntry.h
//  ProjectMB
//
//  Created by wenyong on 15-1-15.
//
//

#ifndef __ProjectMB__MB_TrainerRoadNodeEntry__
#define __ProjectMB__MB_TrainerRoadNodeEntry__

#include "MB_NodeBannerEntry.h"

class MB_TrainerRoadNodeEntry : public MB_NodeBannerEntry
{
public:
    virtual bool init();
    virtual void onChapterClicked(CCObject* pSender);
};

#endif /* defined(__ProjectMB__MB_TrainerRoadNodeEntry__) */
