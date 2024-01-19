//
//  MB_CommandFormation.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-10.
//
//

#include "MB_CommandFormation.h"
#include "MB_FunctionModule.h"
#include "MB_NodeFormationEntry.h"
#include "MB_LayerPetCommand.h"
#include "MB_LayerCommand.h"

MB_ResWindow* MB_CommandFormation::createEntryDialog()
{
    CCUserDefault::sharedUserDefault()->setBoolForKey("LayerPetCommand",false);
    MB_NodeFormationEntry* pInstance = new MB_NodeFormationEntry;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        return  pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

MB_ResWindow* MB_CommandFormation::createFunctionDialog()
{
    MB_LayerCommand* LayerCommand = dynamic_cast<MB_LayerCommand*>(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND));
    if(LayerCommand)LayerCommand->setSelectedSprPos(1);
    return MB_LayerPetCommand::create((m_nEnterType));
}

void MB_CommandFormation::onLoadingScene()
{

}

void MB_CommandFormation::onMsgRecv(CCNode* node, SocketResponse* response)
{
    
}

bool MB_CommandFormation::allowShow()
{
    return true;
}

uint16_t MB_CommandFormation::getFunctionType()
{
    return kFunctionFormation;
}

void MB_CommandFormation::onEntryClicked(CCObject *pSender)
{
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("LayerPetCommand",false)) {
        TutorialTriggerComplete
        
        m_nEnterType = kSubLayerTypePet;
        
        MB_ResWindow* pWnd = createFunctionDialog();
        if (pWnd)
        {
            replaceMainSceneSubLayer(pWnd);
        }
        else
        {
            MB_FunctionItem* pFunctionItem = MB_FunctionConfigure::getInstance()->queryFunctionItemByType(getFunctionType());
            char databuf[40];
            sprintf(databuf, "该功能将%d级开放",pFunctionItem->getNeedLevel());
            MB_Message::sharedMB_Message()->showMessage(databuf);
        }
    }
}
