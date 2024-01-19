//
//  MB_ShowPicInterface.cpp
//  ProjectPM
//
//  Created by chk on 14-4-2.
//
//

#include "MB_LayerShowPic.h"
#include "MB_ShowPicInterface.h"
#include "MB_FunctionModule.h"
MB_ShowPicInterface::MB_ShowPicInterface()
{

}

MB_ShowPicInterface::~MB_ShowPicInterface()
{

}

void MB_ShowPicInterface::onEntryClicked(CCObject* pSender)
{
    MB_LayerShowPic* layer = MB_LayerShowPic::create(kShowPicTypePet);
    if (layer)
    {
        replaceMainSceneSubLayer(layer);
    }
}


MB_ResWindow* MB_ShowPicInterface::createEntryDialog()
{
    MB_NodeShowPicEntry* pInstance = new MB_NodeShowPicEntry();
    if (pInstance && pInstance->setDataSource(this) && pInstance->init() )
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return NULL;
}

MB_ResWindow* MB_ShowPicInterface::createFunctionDialog()
{
    return MB_LayerShowPic::create();
}

bool MB_ShowPicInterface::allowShow()
{
    return true;
}

uint16_t MB_ShowPicInterface::getFunctionType()
{
    return kFunctionPic;
}

void MB_ShowPicInterface::onLoadingScene()
{
}




MB_NodeShowPicEntry::MB_NodeShowPicEntry()
{

}

MB_NodeShowPicEntry::~MB_NodeShowPicEntry()
{
}

bool MB_NodeShowPicEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource =  dynamic_cast<MB_ShowPicInterface*>(pDataSource);
    return m_pDataSource != NULL;
}


void MB_NodeShowPicEntry::onResetWnd()
{
    MB_FunctionEntranceWnd::onResetWnd();
}
