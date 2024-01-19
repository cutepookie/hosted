//
//  MB_NodeFinalRecordLive.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-24.
//
//

#include "MB_NodeFinalRecordLive.h"
#include "MB_PerfectRaceProtocol.h"
#include "MB_LayerFinalRecordLive.h"
#include "MB_LocalProto.h"

MB_NodeFinalRecordLive::MB_NodeFinalRecordLive()
{
    m_pAtkName = NULL;
    m_pDefName = NULL;
    m_pAtkScore = NULL;
    m_pDefScore = NULL;
    m_pLabelWin = NULL;
    m_pRoundRecord = NULL;
}

MB_NodeFinalRecordLive::~MB_NodeFinalRecordLive()
{
    CC_SAFE_RELEASE_NULL(m_pRoundRecord);
    CC_SAFE_RELEASE_NULL(m_pAtkName);
    CC_SAFE_RELEASE_NULL(m_pDefName);
    CC_SAFE_RELEASE_NULL(m_pAtkScore);
    CC_SAFE_RELEASE_NULL(m_pDefScore);
    CC_SAFE_RELEASE_NULL(m_pLabelWin);
}

bool MB_NodeFinalRecordLive::init(MB_RaceRoundRecord* pRoundRecord)
{
    CCNode* pNode = loadResource("res/monsterrace_node_title2.ccbi");
    if (pNode)
    {
        addChild(pNode);
        CC_SAFE_RELEASE_NULL(m_pRoundRecord);
        m_pRoundRecord = pRoundRecord;
        m_pRoundRecord->retain();
        onResetWnd();
        return true;
    }
    return false;
}

void MB_NodeFinalRecordLive::onResetWnd()
{
    if (m_pRoundRecord)
    {
        char buff[64] = {};
        m_pAtkName->setString(m_pRoundRecord->getAtkName().c_str());
        m_pDefName->setString(m_pRoundRecord->getDefName().c_str());
        sprintf(buff, "%d",m_pRoundRecord->getAtkScore());
        m_pAtkScore->setString(buff);
        sprintf(buff, "%d",m_pRoundRecord->getDefScore());
        m_pDefScore->setString(buff);
        if (m_pRoundRecord->getIsAtkWin())
        {
            m_pLabelWin->setPositionX(m_pAtkName->getPositionX());
        }
        else
        {
            m_pLabelWin->setPositionX(m_pDefName->getPositionX());
        }
    }
}

bool MB_NodeFinalRecordLive::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)

{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "label_atk_name", CCLabelTTF*, m_pAtkName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "label_def_name", CCLabelTTF*, m_pDefName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "label_atk_score", CCLabelBMFont*, m_pAtkScore);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "label_def_score", CCLabelBMFont*, m_pDefScore);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "label_win", CCNode*, m_pLabelWin);
    return false;
}

SEL_MenuHandler MB_NodeFinalRecordLive::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler MB_NodeFinalRecordLive::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onReplayClicked", MB_NodeFinalRecordLive::onReplayClicked);
    return NULL;
}

MB_NodeFinalRecordLive* MB_NodeFinalRecordLive::create(MB_RaceRoundRecord* pRoundRecord)
{
    MB_NodeFinalRecordLive* pInstance = new MB_NodeFinalRecordLive;
    if (pInstance && pInstance->init(pRoundRecord))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

void MB_NodeFinalRecordLive::onReplayClicked(CCObject* pSender)
{
    MB_TARGET_PARENT(MB_RaceRecordDelegate, ptr);
    
    if (ptr)
    {
        ptr->onRecrodRequest(m_pRoundRecord->getRecordUID(),m_pRoundRecord->getAtkName(),m_pRoundRecord->getDefName());
    }
}
