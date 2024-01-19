//
//  MB_EquipmentSuitsMgr.cpp
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-14.
//
//

#include "MB_EquipmentSuitsMgr.h"
#include "MB_SuitTemplate.h"
MB_SuitEquipmentMgr::~MB_SuitEquipmentMgr()
{
    CC_SAFE_RELEASE_NULL(m_pSuitsTemplate);
}

MB_SuitEquipmentMgr* MB_SuitEquipmentMgr::getInstance()
{
    if (m_pSingletonInstance==NULL)
    {
        m_pSingletonInstance = new MB_SuitEquipmentMgr;
        if (!m_pSingletonInstance->init())
        {
            CCLOG("[Error]:Init suit equipment data failed!!!!");
        }
    }

    return m_pSingletonInstance;
}

void MB_SuitEquipmentMgr::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(m_pSingletonInstance);
}


/*  this is the data file format
 <?xml version="1.0" encoding="UTF-8"?>
 <suits>
    <set id="10001" name="青铜套装" group="10207,10208,10209,10210,10211,10212">
        <activate needAmount="2">
            <attr type="1" value="100" />
            <attr type="2" value="100" />
            <attr type="3" value="100" />
        </activate>
    </set>
 </suits>
 */

bool MB_SuitEquipmentMgr::init()
{
    MB_XmlFile* pFile = MB_XmlFile::create("config/item/suit.xml");
    if (pFile == NULL)
    {
        return false;
    }

    CCArray* pSuits = new CCArray;

    if(pFile->queryNodesByName("suits|set", pSuits))
    {
        CCObject* pObject = NULL;
        MB_XmlNode* pNode = NULL;
        MB_SuitTemplate* pTemplate = NULL;

        CC_SAFE_RELEASE_NULL(m_pSuitsTemplate);
        m_pSuitsTemplate = new CCArray;

        CCARRAY_FOREACH(pSuits, pObject)
        {
            pNode = dynamic_cast<MB_XmlNode*>(pObject);
            if (pNode)
            {
                pTemplate = MB_SuitTemplate::create(pNode);
                if (pTemplate)
                {
                    m_pSuitsTemplate->addObject(pTemplate);
                }
            }
        }
    }

    CC_SAFE_RELEASE_NULL(pSuits);
    return true;
}

MB_SuitTemplate* MB_SuitEquipmentMgr::getSuitTemplateBy(int nSuitId)const
{
    if (m_pSuitsTemplate == NULL)
    {
        return NULL;
    }

    MB_SuitTemplate* pTarget = NULL;

    CCARRAY_FOREACH_4TYPE(m_pSuitsTemplate,MB_SuitTemplate*,pTarget)
    {
        if(pTarget->getId() == nSuitId)
        {
            // no incress reference count,user shouldn't release the object
            return pTarget;
        }
    }

    return NULL;
}

MB_SuitEquipmentMgr::MB_SuitEquipmentMgr():m_pSuitsTemplate(NULL)
{

}

MB_SuitEquipmentMgr* MB_SuitEquipmentMgr::m_pSingletonInstance = NULL;
