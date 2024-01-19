//
//  MB_NodeSubActivatyEntry.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-10.
//
//

#include "MB_NodeActivatyEntry.h"
#include "MB_CommandActivaty.h"
#include "Game.h"
#include "MB_FunctionModule.h"
#include "MB_ConfigActivatyInterface.h"

using namespace NSGameFunction;

MB_NodeActivatyEntry* MB_NodeActivatyEntry::create()
{
    MB_NodeActivatyEntry* pNode  = new MB_NodeActivatyEntry;
    if (pNode && pNode->init())
    {
        pNode->setType(kFunctionActivaty);
        pNode->autorelease();
        return pNode;
    }
    
    CC_SAFE_RELEASE_NULL(pNode);
    return NULL;
}

bool MB_NodeActivatyEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_ConfigActivatyInterface*>(pDataSource);
    return m_pDataSource != NULL;
}

void MB_NodeActivatyEntry::onResetWnd()
{
    MB_NodeHoverEntry::onResetWnd();
}



