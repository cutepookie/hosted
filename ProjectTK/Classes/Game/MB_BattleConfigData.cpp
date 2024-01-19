//
//  MB_BattleConfigData.cpp
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-13.
//
//

#include "MB_BattleConfigData.h"


MB_BattleConfigData* MB_BattleConfigData::getInstance()
{
    if (m_pSingletonInstance==NULL)
    {
        m_pSingletonInstance = new MB_BattleConfigData;
        m_pSingletonInstance->init();
    }
    return m_pSingletonInstance;
}

void MB_BattleConfigData::destroyInstance()
{
    CC_SAFE_DELETE(m_pSingletonInstance);
}

MB_BattleConfigData* MB_BattleConfigData::m_pSingletonInstance = NULL;

MB_BattleConfigData::MB_BattleConfigData()
{
    m_pData = NULL;
    m_nCount = 0;
}

MB_BattleConfigData::~MB_BattleConfigData()
{
    CC_SAFE_DELETE_ARRAY(m_pData);
}

bool MB_BattleConfigData::init()
{
    MB_XmlFile* pFile = new MB_XmlFile;

    if(pFile->readXmlData("config/description/sp_color.xml"))
    {
        CCArray* array = new CCArray;
        if(pFile->queryNodesByName("SpColor|color",array))
        {
            CC_SAFE_DELETE_ARRAY(m_pData);
            CCObject* pObject = NULL;
            MB_XmlNode* pNode = NULL;
            m_pData = new ccColor3B[array->count()];

            int i = 0;
            m_nCount = array->count();
            CCARRAY_FOREACH(array, pObject)
            {
                pNode = dynamic_cast<MB_XmlNode*>(pObject);
                if (pNode)
                {
                    m_pData[i].r = pNode->queryAttributeByName("r")->intValue();
                    m_pData[i].g = pNode->queryAttributeByName("g")->intValue();
                    m_pData[i].b = pNode->queryAttributeByName("b")->intValue();
                }
                ++i;
            }
        }
        CC_SAFE_RELEASE_NULL(array);
    }
    CC_SAFE_RELEASE_NULL(pFile);
    return true;
}

bool MB_BattleConfigData::getColorBySpiritValue(ccColor3B* pColor,int nSpirit)
{
    if (m_pData == NULL)
    {
        return false;
    }

    int index = nSpirit / 100;
    if (nSpirit % 100 == 0 && nSpirit != 0)
    {
        --index;
    }

    if (index >= m_nCount)
    {
        return false;
    }

    pColor->r = m_pData[index].r;
    pColor->g = m_pData[index].g;
    pColor->b = m_pData[index].b;

    return true;
}