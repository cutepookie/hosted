//
//  MB_NodeRuleFightEntry.h
//  ProjectPM
//
//  Created by chk on 14-4-14.
//
//

#ifndef __ProjectMB__MB_NodeRuleFightEntry__
#define __ProjectMB__MB_NodeRuleFightEntry__

#include "MB_NodeBannerEntry.h"

class MB_RuleFightInterface;
class MB_NodeRuleFightEntry:public MB_NodeBannerEntry
{
public:
    static MB_NodeRuleFightEntry* create();
    MB_NodeRuleFightEntry();
    ~MB_NodeRuleFightEntry();
    virtual void onResetWnd();
    void onChapterClicked(CCObject* pSender);
};

#endif /* defined(__ProjectMB__MB_NodeRuleFightEntry__) */
