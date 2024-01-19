//
//  MB_NodeSpriteRoomEntry.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-14.
//
//

#include "MB_NodeSpriteRoomEntry.h"
#include "MB_SpriteRoomInterface.h"

bool MB_NodeSpriteRoomEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_SpriteRoomInterface*>(pDataSource);
    
    return m_pDataSource;
}