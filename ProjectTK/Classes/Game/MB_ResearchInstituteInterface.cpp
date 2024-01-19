//
//  MB_ResearchInstituteInterface.cpp
//  ProjectPM
//
//  Created by chk on 14-4-14.
//
//


#include "MB_ResearchInstituteInterface.h"
#include "MB_FunctionModule.h"
#include "MB_LayerWorldBossMain.h"
#include "MB_NodeResearchInstituteEntry.h"

MB_ResWindow* MB_ResearchInstituteInterface::createEntryDialog()
{
    return MB_NodeResearchInstituteEntry::create();
}

MB_ResWindow* MB_ResearchInstituteInterface::createFunctionDialog()
{
    MB_LayerWorldBossMain* pInstance = new MB_LayerWorldBossMain();
    if (pInstance && pInstance->setDataSource(this) && pInstance->init() )
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return NULL;
}

void MB_ResearchInstituteInterface::onLoadingScene()
{
    
}

void MB_ResearchInstituteInterface::onMsgRecv(CCNode* node, SocketResponse* response)
{
    //将socket数据读取到序列化结构
}

bool MB_ResearchInstituteInterface::allowShow()
{
    return true;
}

uint16_t MB_ResearchInstituteInterface::getFunctionType()
{
    return kFunctionResearchInstitute;
}

void MB_ResearchInstituteInterface::onEntryClicked(CCObject* pSender)
{
    MB_FunctionItem* pFunctionItem = MB_FunctionConfigure::getInstance()->queryFunctionItemByType(getFunctionType());
    if(pFunctionItem)
    {
        int roleLevel = MB_RoleData::getInstance()->getLevel();
        //等级达到
        if(roleLevel >= pFunctionItem->getNeedLevel())
        {
            MB_ResWindow* pWind = this->createFunctionDialog();
            replaceMainSceneSubLayer(pWind);
        }
        else
        {
            char databuf[40];
            sprintf(databuf, "此功能%d级开放",pFunctionItem->getNeedLevel());
            MB_Message::sharedMB_Message()->showMessage(databuf);
            return;
        }
    }
}
