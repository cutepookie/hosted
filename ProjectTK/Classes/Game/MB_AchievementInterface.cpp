//
//  MB_AchievementInterface.cpp
//  ProjectPM
//
//  Created by crimoon on 14-6-6.
//
//

#include "MB_AchievementInterface.h"


#include "MB_FunctionMgr.h"
#include "MB_AchievementEntry.h"
#include "MB_LayerAchievementWnd.h"

MB_ResWindow* MB_AchievementInterface::createEntryDialog()
{
    MB_AchievementEntry* pInstance = new MB_AchievementEntry;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        pInstance->setType(getFunctionType());
        return pInstance;
    }
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

MB_ResWindow* MB_AchievementInterface::createFunctionDialog()
{
    MB_LayerAchievementWnd* m_pFunctionDialog =  new MB_LayerAchievementWnd();
    if(m_pFunctionDialog)
    {
        if( m_pFunctionDialog->init())
        {
            m_pFunctionDialog->autorelease();
            return m_pFunctionDialog;
        }
        else
        {
            CC_SAFE_RELEASE_NULL(m_pFunctionDialog);
        }
    }
    return NULL;
}
void MB_AchievementInterface::onLoadingScene()
{
    
}
void MB_AchievementInterface::onMsgRecv(CCNode* node, SocketResponse* response)
{
    
}
bool MB_AchievementInterface::allowShow()
{
    return true;
}
uint16_t MB_AchievementInterface::getFunctionType()
{
    return kFunctionAchievement;
}