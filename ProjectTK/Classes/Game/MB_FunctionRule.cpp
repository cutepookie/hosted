//
//  MB_FunctionRule.cpp
//  ProjectPM
//
//  Created by WenYong on 14-7-26.
//
//

#include "MB_FunctionRule.h"
#include "MB_FunctionModule.h"

bool MB_RuleData::init(MB_XmlNode* pNode)
{
    if (pNode==NULL)
    {
        return false;
    }
    
    m_nType = pNode->queryAttributeByName("functionType")->intValue();
    m_bRichText = pNode->queryAttributeByName("richText")->boolValue();
    m_pszContent = pNode->queryAttributeByName("content")->getCString();
    
    return true;
}

MB_FunctionRule* MB_FunctionRule::getInstance()
{
    if (m_pInstance==NULL)
    {
        m_pInstance = new MB_FunctionRule;
        if(!m_pInstance->readConfig())
        {
            CCLOG("[Error]:Load rule config failed");
        }
    }
    return m_pInstance;
}
void MB_FunctionRule::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(m_pInstance);
}

MB_FunctionRule::MB_FunctionRule()
{
    m_pRules = new CCArray;
}
MB_FunctionRule::~MB_FunctionRule()
{
    CC_SAFE_RELEASE_NULL(m_pRules);
}
MB_FunctionRule* MB_FunctionRule::m_pInstance = NULL;

bool MB_FunctionRule::readConfig()
{
    MB_XmlFile* pFile = MB_XmlFile::create("config/rules.xml");
    if (pFile == NULL)
    {
        return false;
    }
    
    CCArray* pArray = CCArray::create();
    MB_XmlNode* pNode = NULL;
    MB_RuleData* pRuleData = NULL;
    m_pRules->removeAllObjects();
    
    if( pFile->queryNodesByName("Rules|Rule", pArray))
    {
        CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pNode)
        {
            pRuleData = new MB_RuleData;
            if (pRuleData->init(pNode))
            {
                m_pRules->addObject(pRuleData);
            }
            CC_SAFE_RELEASE_NULL(pRuleData);
        }
    }
    
    return true;
}

const MB_RuleData* MB_FunctionRule::getRuleByType(int nType)
{
    MB_RuleData* pData = NULL;
    
    CCARRAY_FOREACH_4TYPE(m_pRules, MB_RuleData*, pData)
    {
        if (pData->getType() == nType)
        {
            return pData;
        }
    }
    
    return NULL;
}

CCNode* MB_FunctionRule::craeteRuleNodeByType(int nType,const CCSize& sz)
{
    const MB_RuleData* pData = getRuleByType(nType);
    if (pData)
    {
        if (pData->getRichText())
        {
            return NSGameHelper::createRichBox(pData->getContent(), sz,true);
        }
        else
        {
            return NSGameHelper::createLabelText(pData->getContent(), sz);
        }
    }
    
    return NULL;
}