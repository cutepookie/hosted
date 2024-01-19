//
//  MB_NodeRuleFightEntry.cpp
//  ProjectPM
//
//  Created by chk on 14-4-14.
//
//

#include "MB_NodeRuleFightEntry.h"
#include "MB_ResearchInstituteInterface.h"
#include "MB_RoleData.h"
#include "MB_FunctionModule.h"
#include "MB_RuleFightInterface.h"
MB_NodeRuleFightEntry* MB_NodeRuleFightEntry::create()
{
    MB_NodeRuleFightEntry* pNode = new MB_NodeRuleFightEntry;
    if (pNode && pNode->init())
    {
        pNode->setType(kFunctionRuleFight);
        pNode->autorelease();
        return pNode;
    }
    
    CC_SAFE_RELEASE_NULL(pNode);
    
    return NULL;
}

MB_NodeRuleFightEntry::MB_NodeRuleFightEntry()
{
}

MB_NodeRuleFightEntry::~MB_NodeRuleFightEntry()
{
}

void MB_NodeRuleFightEntry::onResetWnd()
{
    MB_NodeBannerEntry::onResetWnd();
    setEnable();
    showActivities(true);
}

void MB_NodeRuleFightEntry::onChapterClicked(CCObject* pSender)
{
//    MB_Message::sharedMB_Message()->showMessage("该功能暂未开启");//天梯
//    return;
    MB_NodeBannerEntry::onChapterClicked(pSender);
    MB_Message::sharedMB_Message()->showMessage("",5);
    QUERY_FUNCTION_BEGIN(MB_RuleFightInterface, kFunctionRuleFight, pInterface);
    pInterface->cs_rule_info();
    QUERY_FUNCTION_END;
}
