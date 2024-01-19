//
//  MB_NodeLuckyPlayer.cpp
//  ProjectTK
//
//  Created by crimoon00007 on 14-1-2.
//
//

#include "MB_NodeLuckyPlayer.h"

MB_NodeLuckyPlayer::MB_NodeLuckyPlayer()
{
    m_pName = NULL;
    m_pHarmInfo = NULL;
}
MB_NodeLuckyPlayer::~MB_NodeLuckyPlayer()
{
    CC_SAFE_RELEASE(m_pName);
    CC_SAFE_RELEASE(m_pHarmInfo);
}

bool MB_NodeLuckyPlayer::init()
{
    MB_ResWindow::init();

    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);

    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/station_node_rocket_lucky.ccbi",this);
    if (!pNode)
    {
        return false;
    }
    addChild(pNode);
    CC_SAFE_RELEASE(pCCBReader);
    return true;
}

bool MB_NodeLuckyPlayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "name",CCLabelTTF *,m_pName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "harminfo",CCLabelTTF *,m_pHarmInfo);
    return false;
}

void MB_NodeLuckyPlayer::setLuckyPlayerData(const char* name)
{
    if (name == NULL)
    {
        MB_LOG("Name is a null point");
        return;
    }

    m_szRoleName = name;

    dirty();
}

void MB_NodeLuckyPlayer::onResetWnd()
{
    m_pName->setString(m_szRoleName.c_str());
    m_pHarmInfo->setVisible(false);
    
    if(strcmp(m_szRoleName.c_str(),MB_RoleData::getInstance()->getName()) == 0)
    {
        m_pName->setColor(ccRED);
    }
}