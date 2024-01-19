//
//  MB_ComposeTemplate.cpp
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-18.
//
//

#include "MB_ComposeTemplate.h"

MB_ComposeTemplate::MB_ComposeTemplate()
{
    m_nComposeID = 0;
    m_nComposeType = kComposeUnknow;
    m_nTartgetID = 0;
    m_nMaterialCount = 0;
    m_nCostCoin = 0;
    memset(m_pMaterialArray, 0, sizeof(uint16_t)*MAX_MATERIAL);
}

MB_ComposeTemplate::~MB_ComposeTemplate()
{
    m_nComposeID = 0;
    m_nComposeType = kComposeUnknow;
    m_nTartgetID = 0;
    m_nMaterialCount = 0;
    m_nCostCoin = 0;
}

const uint16_t* MB_ComposeTemplate::getMaterialsArray()const
{
    return m_pMaterialArray;
}

MB_ComposeTemplate* MB_ComposeTemplate::create(MB_XmlNode* pNode)
{
    MB_ComposeTemplate* pInstance = new MB_ComposeTemplate;
    if (pInstance && pInstance->init(pNode))
    {
        pInstance->autorelease();
        return pInstance;
    }

    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}

bool MB_ComposeTemplate::init(MB_XmlNode *pNode)
{
    if (pNode == NULL)
    {
        return false;
    }

    m_nComposeID = pNode->queryAttributeByName("id")->intValue();
    m_nComposeType = pNode->queryAttributeByName("type")->intValue();
    m_nCostCoin = pNode->queryAttributeByName("coin")->intValue();
    const char* temp = pNode->queryAttributeByName("material")->getCString();
    NSGameHelper::resolvInt16ValueFromString(temp, m_pMaterialArray, m_nMaterialCount, MAX_MATERIAL);

    m_nTartgetID = pNode->queryAttributeByName("target")->intValue();
    return true;
}
