//
//  MB_TrainerRoadNodeEntry.cpp
//  ProjectMB
//
//  Created by wenyong on 15-1-15.
//
//

#include "MB_TrainerRoadNodeEntry.h"
#include "MB_FunctionTrainerRoad.h"
bool MB_TrainerRoadNodeEntry::init()
{
    MB_NodeBannerEntry::init();
    m_pMenuItemImage->setIsScale(false);
    showActivities(true);
    return true;
}

void MB_TrainerRoadNodeEntry::onChapterClicked(CCObject* pSender)
{
    MB_NodeBannerEntry::onChapterClicked(pSender);
}