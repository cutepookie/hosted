//
//  MB_FunctionConfig.cpp
//  ProjectPM
//
//  Created by WenYong on 14-3-26.
//
//

#include "MB_FunctionConfig.h"
#include "Game.h"

MB_FunctionItem* MB_FunctionItem::create(MB_XmlNode* pNode)
{
    MB_FunctionItem* pInstance = new MB_FunctionItem;
    if (pInstance && pInstance->init(pNode))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}

bool MB_FunctionItem::init(MB_XmlNode* pNode)
{
    if (pNode == NULL)
    {
        return false;
    }
    
    /*<function type="101" name="任務" openlable="name_renwu.png" closelable="name_close.png" level="10"  enable="btn_index_00.png" disable="btn_index_01.png" activateccbi="res/gui_tutorial_lv10.ccbi" />*/
    
    m_nFunctionType = pNode->queryAttributeByName("type")->intValue();
    m_nLevel        = pNode->queryAttributeByName("level")->intValue();
    m_szFunctionName= pNode->queryAttributeByName("name")->getCString();
    m_szEnableFile  = pNode->queryAttributeByName("enable")->getCString();
    m_szDisableFile = pNode->queryAttributeByName("disable")->getCString();
    m_szActivateCcbi= pNode->queryAttributeByName("activateccbi")->getCString();
    m_szNameEnable = pNode->queryAttributeByName("openlable")->getCString();
    m_szNameDisable = pNode->queryAttributeByName("closelable")->getCString();
    m_szDes = pNode->queryAttributeByName("des")->getCString();
    
    return true;
}

MB_ActivatyRestrict* MB_ActivatyRestrict::create(MB_XmlNode* pNode)
{
    MB_ActivatyRestrict* pInstance = new MB_ActivatyRestrict;
    if (pInstance && pInstance->init(pNode))
    {
        pInstance->autorelease();
        return pInstance;
    }
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

/*<restrict type="" level="" vip=""/>*/
bool MB_ActivatyRestrict::init(MB_XmlNode* pNode)
{
    m_nType = pNode->queryAttributeByName("type")->intValue();
    m_nRestrictRoleLevel = pNode->queryAttributeByName("level")->intValue();
    m_nRestrictVipLevel = pNode->queryAttributeByName("vip")->intValue();
    return true;
}

bool MB_ActivatyRestrict::isActivated()
{
    if (m_nRestrictRoleLevel<=MB_RoleData::getInstance()->getLevel()
        && m_nRestrictVipLevel<=MB_RoleData::getInstance()->getVipLevel())
    {
        return true;
    }
    return false;
}

MB_FunctionConfigure::MB_FunctionConfigure()
{
    m_pContainer = new CCArray;
    m_pRestrictItems = new CCArray;
}

MB_FunctionConfigure::~MB_FunctionConfigure()
{
    CC_SAFE_RELEASE_NULL(m_pContainer);
    CC_SAFE_RELEASE_NULL(m_pRestrictItems);
    removeResourceFromCache();
}

MB_FunctionConfigure* MB_FunctionConfigure::getInstance()
{
    if (m_pSingletonInstance == NULL)
    {
        m_pSingletonInstance = new MB_FunctionConfigure;
        if(!m_pSingletonInstance->init())
        {
            CCLog("[Error]:FunctionConfigure init failed");
        }
    }

    return m_pSingletonInstance;
}

void MB_FunctionConfigure::destroyInstance()
{
    CC_SAFE_DELETE(m_pSingletonInstance);
}


/*
 <functions resource="pic_index_func.plist" />
 <page name="村落" />
 <function type="101" name="任務" openlable="name_renwu.png" closelable="name_close.png" level="10"  enable="btn_index_00.png" disable="btn_index_01.png" activateccbi="res/gui_tutorial_lv10.ccbi" />
 </page>
 <page name="大世界" />
 <function type="201" name="研究所" level="1" openlable="name_yanjiusuo.png" closelable="name_close.png"  enable="btn_index1_00.png" disable="btn_index1_01.png" activateccbi="" />
 </page>
 </functions>
 */
bool MB_FunctionConfigure::init()
{
    MB_XmlFile* pFile = MB_XmlFile::create("config/functions.xml");
    if (NULL == pFile)
    {
        return false;
    }
    
    CCArray* pArray = new CCArray;
    bool ret = false;
    MB_XmlNode* pNode = NULL;
    
    if(pFile->queryNodesByName("functions", pArray))
    {
        const char* pList = ((MB_XmlNode*)(pArray->objectAtIndex(0)))->queryAttributeByName("resource")->getCString();
        if (pList)
        {
            m_pResource = pList;
            loadResource2SpriteCache();
        }
    }
    
    
    ret = pFile->queryNodesByName("functions|page", pArray);
    if (ret)
    {
        m_pContainer->removeAllObjects();
        CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pNode)
        {
            addPage(pNode);
        }
    }
    
    pArray->removeAllObjects();
    ret = pFile->queryNodesByName("functions|restricts|restrict", pArray);
    if (ret)
    {
        MB_ActivatyRestrict* pItem = NULL;
        MB_XmlNode* pNode = NULL;
        m_pRestrictItems->removeAllObjects();
        CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pNode)
        {
            pItem = new MB_ActivatyRestrict;
            if (pItem->init(pNode))
            {
                m_pRestrictItems->addObject(pItem);
            }
            CC_SAFE_RELEASE_NULL(pItem);
        }
    }
    
    pArray->release();
    
    return true;
}
void MB_FunctionConfigure::loadResource2SpriteCache()
{
    if (!m_pResource.empty())
    {
        std::vector<std::string> arr = NSGameHelper::splitEx(m_pResource, ",");
        for (int i = 0; i<arr.size(); ++i)
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(arr[i].c_str());
        }
    }
}
void MB_FunctionConfigure::removeResourceFromCache()
{
    if (!m_pResource.empty())
    {
        std::vector<std::string> arr = NSGameHelper::splitEx(m_pResource, ",");
        for (int i = 0; i<arr.size(); ++i)
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(arr[i].c_str());
        }
    }
}
bool MB_FunctionConfigure::addPage(MB_XmlNode* pNode)
{
    if (pNode == NULL)
    {
        return false;
    }
    
    CCArray* pFunction = new CCArray;
    MB_FunctionItem* pItem = NULL;
    bool ret = NULL;
    
    ret = pNode->queryNodesByName("function", pFunction);
    if (ret)
    {
        CCARRAY_FOREACH_4TYPE(pFunction, MB_XmlNode*, pNode)
        {
            pItem = new MB_FunctionItem;
            if (pItem->init(pNode))
            {
                m_pContainer->addObject(pItem);
            }
            CC_SAFE_RELEASE_NULL(pItem);
        }
    }
    
    pFunction->release();
    
    return true;
}

MB_FunctionItem* MB_FunctionConfigure::queryFunctionItemByType(uint16_t nType)
{
    MB_FunctionItem* pItem = NULL;
    
    CCARRAY_FOREACH_4TYPE(m_pContainer, MB_FunctionItem*, pItem)
    {
        if (pItem->getFunctionType() == nType)
        {
            return pItem;
        }
    }
    
    return NULL;
}

MB_ActivatyRestrict* MB_FunctionConfigure::queryActivatRestrictItemByType(uint16_t nType)
{
    MB_ActivatyRestrict* pItem = NULL;
    CCARRAY_FOREACH_4TYPE(m_pRestrictItems, MB_ActivatyRestrict*, pItem)
    {
        if (pItem->getType() == nType)
        {
            return pItem;
        }
    }
    return NULL;
}

bool MB_FunctionConfigure::getIsRoleOutOfRestrict(uint16_t nType)
{
    MB_ActivatyRestrict* pItem = queryActivatRestrictItemByType(nType);
    if (pItem)
    {
        return pItem->isActivated();
    }
    else
    {
        MB_FunctionItem* p = queryFunctionItemByType(nType);
        if (p)
        {
            return p->getNeedLevel()<=MB_RoleData::getInstance()->getLevel();
        }
    }
    return false;
}
int MB_FunctionConfigure::getFunctionLimitLevel(int type)
{
    MB_FunctionItem* pItem = queryFunctionItemByType(type);
    if (pItem == NULL)
    {
        return 0;
    }
    
    return pItem->getNeedLevel();
}
MB_FunctionConfigure* MB_FunctionConfigure::m_pSingletonInstance = NULL;
