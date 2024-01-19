//
//  MB_BudokanProtocol.cpp
//  ProjectMB
//
//  Created by yuanwugang on 14-8-28.
//
//

#include "MB_BudokanProtocol.h"
#include "MB_MsgBuffer.h"
#include "Game.h"

MB_BudokanData::MB_BudokanData()
{
    m_nCurDungeonNum = 0;
    m_nAddAttack = 0;
    m_nAddHp = 0;
    m_nDungeonID = 0;
    m_nChallengeTimes = 0;
    m_bIsOpen = false;
    m_bLastTime = 0;
    m_nMaxDungeonNum = 0;
}

bool MB_BudokanData::read(MB_MsgBuffer* pRecv)
{
    pRecv->readU16(&m_nCurDungeonNum);
    pRecv->readU16(&m_nAddAttack);
    pRecv->readU16(&m_nAddHp);
    pRecv->readU16(&m_nDungeonID);
    pRecv->readU8(&m_nChallengeTimes);
    pRecv->readU8(&m_bIsOpen);
    pRecv->readU32(&m_bLastTime);
    pRecv->readU8(&m_nCoinBuyTimes);
    pRecv->readU8(&m_nMoneyBuyTimes);
    pRecv->readU16(&m_nMaxDungeonNum);
    return true;
}


bool MB_BudokanChapterData::init(MB_XmlNode *pNode)
{
    if (pNode == NULL)
    {
        return false;
    }
    m_nChapterID = pNode->queryAttributeByName("ID")->intValue();
    m_nBoosID = pNode->queryAttributeByName("boosID")->intValue();
    m_nRewardID1 = pNode->queryAttributeByName("reward1")->intValue();
    m_nRewardNum1 = pNode->queryAttributeByName("num1")->intValue();
    m_nRewardID2 = pNode->queryAttributeByName("reward2")->intValue();
    m_nRewardNum2 = pNode->queryAttributeByName("num2")->intValue();
    m_nRewardID3 = pNode->queryAttributeByName("reward3")->intValue();
    m_nRewardNum3 = pNode->queryAttributeByName("num3")->intValue();
    m_nRewardID4 = pNode->queryAttributeByName("reward4")->intValue();
    m_nRewardNum4 = pNode->queryAttributeByName("num4")->intValue();

    return true;
}

    
    
MB_BudokanConfig::MB_BudokanConfig()
{
    m_pBudokanConfig = new CCArray();
}
MB_BudokanConfig::~MB_BudokanConfig()
{
    CC_SAFE_RELEASE_NULL(m_pBudokanConfig);
}
bool MB_BudokanConfig::init(const char* pFile)
{
    MB_XmlFile* pXml = MB_XmlFile::create(pFile);
    if (pXml == NULL)
    {
        return false;
    }
    
    CCArray* pArray = CCArray::create();
    if(!pXml->queryNodesByName("budokan", pArray))
    {
        return false;
    }
    
    m_pBudokanConfig->removeAllObjects();
    MB_XmlNode* pRoot = dynamic_cast<MB_XmlNode*>(pArray->objectAtIndex(0));
    MB_XmlNode* pTemp = NULL;
    
    pArray->removeAllObjects();
    pRoot->queryNodesByName("Chapters|Chapter", pArray);
    CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pTemp)
    {
        MB_BudokanChapterData* pdata = new MB_BudokanChapterData;
        if (pdata->init(pTemp))
        {
            m_pBudokanConfig->addObject(pdata);
        }
        CC_SAFE_RELEASE_NULL(pdata);
    }
    
    
    return true;
}

MB_BudokanChapterData* MB_BudokanConfig::getChapterDataByID(uint16_t id)
{
    MB_BudokanChapterData* pTemp = NULL;
    CCARRAY_FOREACH_4TYPE(m_pBudokanConfig, MB_BudokanChapterData*, pTemp)
    {
        if (pTemp->getChapterID() == id)
        {
            return pTemp;
        }
    }
    return NULL;
}