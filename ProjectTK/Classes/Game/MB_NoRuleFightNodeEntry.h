//
//  MB_NoRuleFightNodeEntry.h
//  ProjectMB
//
//  Created by chk on 15-1-15.
//
//

#ifndef __ProjectMB__MB_NoRuleFightNodeEntry__
#define __ProjectMB__MB_NoRuleFightNodeEntry__

#include "MB_NodeBannerEntry.h"

class MB_NoRuleFightNodeEntry : public MB_NodeBannerEntry
{
public:
    virtual bool init();
    virtual void onChapterClicked(CCObject* pSender);
};

#endif /* defined(__ProjectMB__MB_NoRuleFightNodeEntry__) */
