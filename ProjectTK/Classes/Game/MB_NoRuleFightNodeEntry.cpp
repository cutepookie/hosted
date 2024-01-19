//
//  MB_NoRuleFightNodeEntry.cpp
//  ProjectMB
//
//  Created by chk on 15-1-15.
//
//

#include "MB_NoRuleFightNodeEntry.h"
#include "MB_FunctionTrainerRoad.h"
bool MB_NoRuleFightNodeEntry::init()
{
    MB_NodeBannerEntry::init();
    m_pMenuItemImage->setIsScale(false);
    showActivities(true);
    return true;
}

void MB_NoRuleFightNodeEntry::onChapterClicked(CCObject* pSender)
{
    MB_NodeBannerEntry::onChapterClicked(pSender);
}