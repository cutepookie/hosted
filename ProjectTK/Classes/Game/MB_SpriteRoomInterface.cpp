//
//  MB_SpriteRoomInterface.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-14.
//
//

#include "MB_SpriteRoomInterface.h"
#include "MB_FunctionModule.h"
#include "MB_NodeSpriteRoomEntry.h"
#include "MB_NodePetList.h"

MB_ResWindow* MB_SpriteRoomInterface::createEntryDialog()
{
    MB_NodeSpriteRoomEntry* pInstance = new MB_NodeSpriteRoomEntry;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        pInstance->setType(getFunctionType());
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

MB_ResWindow* MB_SpriteRoomInterface::createFunctionDialog()
{
    return MB_NodePetList::create(kPetTeamTypeMain, 0, kListTypeList);
}

void MB_SpriteRoomInterface::onLoadingScene()
{
    
}

void MB_SpriteRoomInterface::onMsgRecv(CCNode* node, SocketResponse* response)
{
    
}

bool MB_SpriteRoomInterface::allowShow()
{
    return true;
}

uint16_t MB_SpriteRoomInterface::getFunctionType()
{
    return kFunctionPetPackage;
}
