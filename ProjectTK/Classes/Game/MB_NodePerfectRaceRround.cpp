//
//  MB_NodePerfectRaceRround.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-24.
//
//

#include "MB_NodePerfectRaceRround.h"
MB_NodePerfectRaceRround::MB_NodePerfectRaceRround()
{
    m_pShowString = NULL;
    m_nRound = 0;
}

MB_NodePerfectRaceRround::~MB_NodePerfectRaceRround()
{
    CC_SAFE_RELEASE_NULL(m_pShowString);
}
bool MB_NodePerfectRaceRround::init(uint8_t nRound)
{
    if (nRound > 9)
    {
        return false;
    }
    CCNode* pNode = loadResource("res/monsterrace_node_title0.ccbi");
    if (pNode)
    {
        addChild(pNode);
        m_nRound = nRound;
        onResetWnd();
        return true;
    }
    
    return false;
}

void MB_NodePerfectRaceRround::onResetWnd()
{
    if (m_nRound > 10)
    {
        return;
    }
    
    static const char* text[10] = \
    {
        "---------------未知赛----------------",
        "----------------决赛----------------",
        "---------------半决赛----------------",
        "---------------八强赛----------------",
        "---------------16进8----------------",
        "---------------32进16---------------",
        "---------------64进32---------------",
        "--------------128进64---------------",
        "--------------256进128--------------",
        "--------------512进256--------------",
    };
    
    m_pShowString->setString(text[m_nRound]);
}

void MB_NodePerfectRaceRround::forceSetShowString(const char* pString)
{
    m_pShowString->setString(pString);
}

bool MB_NodePerfectRaceRround::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_round", CCLabelTTF*, m_pShowString);
    return false;
}

MB_NodePerfectRaceRround* MB_NodePerfectRaceRround::create(uint8_t nRound)
{
    MB_NodePerfectRaceRround* pInstance = new MB_NodePerfectRaceRround;
    if (pInstance && pInstance->init(nRound))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}