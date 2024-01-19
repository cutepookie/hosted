//
//  MB_NodeGroupRecordLive.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-24.
//
//

#include "MB_NodeGroupRecordLive.h"
#include "MB_PerfectRaceProtocol.h"
#include "MB_LocalProto.h"

MB_NodeGroupRecordLive::MB_NodeGroupRecordLive()
{
    m_pAtkName = NULL;
    m_pDefName = NULL;
    m_pLabelWin = NULL;
//    m_pAtkStatus = NULL;
//    m_pDefStatus = NULL;
    m_pRaceRecord = NULL;
    
    m_pDefLose = NULL;
    m_pAtkLose = NULL;
    m_pDefWin = NULL;
    m_pAtkWin = NULL;
}

MB_NodeGroupRecordLive::~MB_NodeGroupRecordLive()
{
    CC_SAFE_RELEASE_NULL(m_pDefLose);
    CC_SAFE_RELEASE_NULL(m_pAtkLose);
    CC_SAFE_RELEASE_NULL(m_pDefWin);
    CC_SAFE_RELEASE_NULL(m_pAtkWin);
    CC_SAFE_RELEASE_NULL(m_pAtkName);
    //CC_SAFE_RELEASE_NULL(m_pDefStatus);
    CC_SAFE_RELEASE_NULL(m_pLabelWin);
    //CC_SAFE_RELEASE_NULL(m_pAtkStatus);
    CC_SAFE_RELEASE_NULL(m_pDefName);
    CC_SAFE_RELEASE_NULL(m_pRaceRecord);
}

bool MB_NodeGroupRecordLive::init(MB_RaceRecord* pRecord)
{
    if (pRecord == NULL)
    {
        return false;
    }
    
    CCNode* pNode = loadResource("res/monsterrace_node_title1.ccbi");
    if (pNode)
    {

        addChild(pNode);
        CC_SAFE_RELEASE_NULL(m_pRaceRecord);
        m_pRaceRecord = pRecord;
        m_pRaceRecord->retain();
        onResetWnd();
        return true;
    }
    return false;
}

void MB_NodeGroupRecordLive::onResetWnd()
{
    if (m_pRaceRecord)
    {
        m_pDefName->setString(m_pRaceRecord->getDefName().c_str());
        m_pAtkName->setString(m_pRaceRecord->getAtkName().c_str());
        
        std::string winner = m_pRaceRecord->getAtkName();
        if (!m_pRaceRecord->m_vResultList[0])
        {
            winner = m_pRaceRecord->getDefName();
            m_pAtkWin->setVisible(false);
            m_pAtkLose->setVisible(true);
            m_pDefWin->setVisible(true);
            m_pDefLose->setVisible(false);
        }
        else
        {
            m_pAtkWin->setVisible(true);
            m_pAtkLose->setVisible(false);
            m_pDefWin->setVisible(false);
            m_pDefLose->setVisible(true);
        }
        char buff[128] = "";
        sprintf(buff, "恭喜%s进入了下一轮",winner.c_str());
        m_pLabelWin->setString(buff);
    }
}

uint64_t MB_NodeGroupRecordLive::getRecordUid()
{
    return m_pRaceRecord->m_vRecordList[0];
}

bool MB_NodeGroupRecordLive::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_atk_name", CCLabelTTF*, m_pAtkName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_def_name", CCLabelTTF*, m_pDefName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_win", CCLabelTTF*, m_pLabelWin);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_atk_status", CCLabelTTF*, m_pAtkStatus);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_def_status", CCLabelTTF*, m_pDefStatus);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_atk_win", CCSprite*, m_pAtkWin);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_atk_lose", CCSprite*, m_pAtkLose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_def_win", CCSprite*, m_pDefWin);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_def_lose", CCSprite*, m_pDefLose);
    return false;
}

SEL_MenuHandler MB_NodeGroupRecordLive::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler MB_NodeGroupRecordLive::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onReplayClicked", MB_NodeGroupRecordLive::onReplayClicked);
    return NULL;
}

MB_NodeGroupRecordLive* MB_NodeGroupRecordLive::create(MB_RaceRecord* pRecord)
{
    MB_NodeGroupRecordLive* pInstance = new MB_NodeGroupRecordLive;
    if (pInstance && pInstance->init(pRecord))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

void MB_NodeGroupRecordLive::onReplayClicked(CCObject* pSender)
{
    MB_TARGET_PARENT(MB_RaceRecordDelegate, ptr);
    
    if (ptr)
    {
        ptr->onRecrodRequest(m_pRaceRecord->m_vRecordList[0],m_pRaceRecord->getAtkName(),m_pRaceRecord->getDefName());
    }
}
