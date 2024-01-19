//
//  MB_ActivatyConfigure.cpp
//  ProjectPM
//
//  Created by chk on 14-4-30.
//
//

#include "MB_ActivatyConfigure.h"

#include "Game.h"

MB_ActivatyItem* MB_ActivatyItem::create(MB_XmlNode* pNode)
{
    MB_ActivatyItem* pInstance = new MB_ActivatyItem;
    if (pInstance && pInstance->init(pNode))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}

bool MB_ActivatyItem::init(MB_XmlNode* pNode)
{
    if (pNode == NULL)
    {
        return false;
    }
    
    /*<function type="101" name="任務" openlable="" closelable="" level="10"  enable="" disable="" activateccbi="res/gui_tutorial_lv10.ccbi" />*/
    
    m_nActivatyType = pNode->queryAttributeByName("type")->intValue();
    m_nLevel        = pNode->queryAttributeByName("level")->intValue();
    m_szActivatyName= pNode->queryAttributeByName("name")->getCString();
//    m_szEnableFile  = pNode->queryAttributeByName("enable")->getCString();
//    m_szDisableFile = pNode->queryAttributeByName("disable")->getCString();
    m_szActivateCcbi= pNode->queryAttributeByName("activateccbi")->getCString();
//    m_szNameEnable = pNode->queryAttributeByName("openlable")->getCString();
//    m_szNameDisable = pNode->queryAttributeByName("closelable")->getCString();
    
    return true;
}

MB_ActivatyConfigure::MB_ActivatyConfigure()
{
    m_pContainer = new CCArray;
}

MB_ActivatyConfigure::~MB_ActivatyConfigure()
{
    m_pContainer->removeAllObjects();
}

MB_ActivatyConfigure* MB_ActivatyConfigure::getInstance()
{
    if (m_pSingletonInstance == NULL)
    {
        m_pSingletonInstance = new MB_ActivatyConfigure;
        if(!m_pSingletonInstance->init())
        {
            CCLog("[Error]:ActivatyConfigure init failed");
        }
    }
    
    return m_pSingletonInstance;
}

void MB_ActivatyConfigure::destroyInstance()
{
    CC_SAFE_DELETE(m_pSingletonInstance);
}


/*
 <activatys resource="pic_index_func.plist">
    <activaty type="401" name="補充精力" openlable="name_renwu.png" closelable="name_close.png" level="1"  enable="btn_index_00.png" disable="btn_index_01.png" activateccbi="" />
    <activaty type="402" name="招財" openlable="name_jinglingwang.png" closelable="name_close.png" level="1"  enable="btn_index_10.png" disable="btn_index_11.png" activateccbi="" />
 </activatys>
 */
bool MB_ActivatyConfigure::init()
{
    MB_XmlFile* pFile = MB_XmlFile::create("config/dailywelfare.xml");
    if (NULL == pFile)
    {
        return false;
    }
    
    CCArray* pArray = new CCArray;
    bool ret = true;
    MB_XmlNode* pNode = NULL;
    
    if(pFile->queryNodesByName("activatys", pArray))
    {
        const char* pList = ((MB_XmlNode*)(pArray->objectAtIndex(0)))->queryAttributeByName("resource")->getCString();
        if (pList)
        {
            m_pResource = pList;
            loadResource2SpriteCache();
        }
        
        CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pNode)
        {
            ret = ret && addActivaty(pNode);
        }
    }
    
    pArray->release();
    
    return ret;
}

bool MB_ActivatyConfigure::addActivaty(MB_XmlNode* pNode)
{
    if (pNode == NULL)
    {
        return false;
    }

    CCArray* pActivaty = new CCArray;
    MB_ActivatyItem* pItem = NULL;
    bool ret = NULL;
    
    ret = pNode->queryNodesByName("activaty", pActivaty);
    if (ret)
    {
        CCARRAY_FOREACH_4TYPE(pActivaty, MB_XmlNode*, pNode)
        {
            pItem = new MB_ActivatyItem;
            if (pItem->init(pNode))
            {
                m_pContainer->addObject(pItem);
            }
            CC_SAFE_RELEASE_NULL(pItem);
        }
    }
    
    pActivaty->release();
    return true;
}

void MB_ActivatyConfigure::loadResource2SpriteCache()
{
    if (!m_pResource.empty())
    {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(m_pResource.c_str());
    }
}


MB_ActivatyItem* MB_ActivatyConfigure::queryActivatyItemByType(uint16_t nType)
{
    MB_ActivatyItem* pItem = NULL;
    
    CCARRAY_FOREACH_4TYPE(m_pContainer, MB_ActivatyItem*, pItem)
    {
        if (pItem->getActivatyType() == nType)
        {
            return pItem;
        }
    }
    
    return NULL;
}
MB_ActivatyConfigure* MB_ActivatyConfigure::m_pSingletonInstance = NULL;
