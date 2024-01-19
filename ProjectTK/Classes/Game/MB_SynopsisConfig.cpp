//
//  MB_SynopsisConfig.cpp
//  ProjectPM
//
//  Created by cri-mac on 14-5-14.
//
//

#include "MB_SynopsisConfig.h"
#include "Game.h"
#include "MB_LayerStory.h"

MB_Plot* MB_Plot::create(MB_XmlNode* pNode)
{
    MB_Plot* pInstance = new MB_Plot;
    if (pInstance && pInstance->init(pNode))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}

bool MB_Plot::init(MB_XmlNode* pNode)
{
    if (pNode == NULL)return false;
    
    /*<plot headIcon = "xxx/frm_2.png" headPos="1" sound="" text="" />*/
    m_szHeadIcon = pNode->queryAttributeByName("headIcon")->getCString();
    m_nHeadPos = pNode->queryAttributeByName("headPos")->intValue();
    m_szSound= pNode->queryAttributeByName("sound")->getCString();
    m_szText = pNode->queryAttributeByName("text")->getCString();
    
    if(m_szHeadIcon.length() == 0)
    {
        if(MB_RoleData::getInstance()->getSex() == 1)
        {
            m_szHeadIcon = "pic_mal1_1.png";
        }
        else
        {
            m_szHeadIcon = "pic_fem1_1.png";
        }
    }
    return true;
}






MB_SynopsisItem::MB_SynopsisItem()
{
    m_Plots = new CCArray();
    
}

MB_SynopsisItem::~MB_SynopsisItem()
{
    CC_SAFE_RELEASE_NULL(m_Plots);
    
}


MB_SynopsisItem* MB_SynopsisItem::create(MB_XmlNode* pNode)
{
    MB_SynopsisItem* pInstance = new MB_SynopsisItem;
    if (pInstance && pInstance->init(pNode))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}

bool MB_SynopsisItem::init(MB_XmlNode* pNode)
{
    if (pNode == NULL)return false;
    
    
    m_nDungeonID = pNode->queryAttributeByName("dungeonID")->intValue();
    m_nCondition = pNode->queryAttributeByName("condition")->intValue();
    
    CCArray* pArray = new CCArray;
    MB_XmlNode* pTempNode = NULL;
    if(pNode->queryNodesByName("plot", pArray))
    {
        m_Plots->removeAllObjects();
        CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pTempNode)
        {
            MB_Plot* pPlot = MB_Plot::create(pTempNode);
            if(pPlot)m_Plots->addObject(pPlot);
        }
    }
    pArray->release();
    return true;
}





MB_SynopsisConfig::MB_SynopsisConfig()
{
    m_pSynopsis = new CCArray;
    m_pBattlePlots = new CCArray();
}

MB_SynopsisConfig::~MB_SynopsisConfig()
{
    CC_SAFE_RELEASE_NULL(m_pSynopsis);
    CC_SAFE_RELEASE_NULL(m_pBattlePlots);
}

MB_SynopsisConfig* MB_SynopsisConfig::getInstance()
{
    if (m_pSingletonInstance == NULL)
    {
        m_pSingletonInstance = new MB_SynopsisConfig;
        if(!m_pSingletonInstance->init())
        {
            CCLog("[Error]:MB_SynopsisConfig init failed");
        }
    }
    
    return m_pSingletonInstance;
}

void MB_SynopsisConfig::destroyInstance()
{
    CC_SAFE_DELETE(m_pSingletonInstance);
}


bool MB_SynopsisConfig::init()
{
    MB_XmlFile* pFile = MB_XmlFile::create("config/story.xml");
    
    if (NULL == pFile)return false;
    
    CCArray* pArray = new CCArray;
    MB_XmlNode* pNode = NULL;
    
    if(pFile->queryNodesByName("synopsis|plots", pArray))
    {
        m_pSynopsis->removeAllObjects();
        CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pNode)
        {
            MB_SynopsisItem* pItem = MB_SynopsisItem::create(pNode);
            if(pItem)m_pSynopsis->addObject(pItem);
        }
    }
    
    pArray->removeAllObjects();
    if(pFile->queryNodesByName("synopsis|battle", pArray))
    {
        CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pNode)
        {
            MB_SynopsisItem* pItem = MB_SynopsisItem::create(pNode);
            if(pItem)
                m_pBattlePlots->addObject(pItem);
        }
    }

    pArray->release();
    return true;
}

MB_LayerStoryPlayer* MB_SynopsisConfig::createBattlePlotByID(uint16_t nActionId)
{
    MB_SynopsisItem* pItem = queryBattlePlotItem(nActionId);
    if (pItem)
    {
        CCArray* pArray = pItem->getPlots();
        MB_LayerStoryPlayer* pLayer = MB_LayerStoryPlayer::create(pArray);
        return pLayer;
    }
    return NULL;
}

MB_SynopsisItem* MB_SynopsisConfig::queryBattlePlotItem(int nActionID)
{
    MB_SynopsisItem* pItem = NULL;
    CCARRAY_FOREACH_4TYPE(m_pBattlePlots, MB_SynopsisItem*, pItem)
    {
        if (nActionID == pItem->getDungeonID())
        {
            return pItem;
        }
    }
    return NULL;
}

bool MB_SynopsisConfig::querySynopsisItem(int nDungeonID,int nCondition,CCArray** outPlots)
{
    if (*outPlots==NULL)
    {
        return false;
    }
    MB_SynopsisItem* pItem = querySynopsisItem(nDungeonID,nCondition);
    if(pItem)
    {
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(pItem->getPlots(), pObj)
        {
            (*outPlots)->addObject(pObj);
        }
        
        return true;
    }
    return false;
}

MB_SynopsisItem* MB_SynopsisConfig::querySynopsisItem(int nDungeonID,int nCondition)
{
    MB_SynopsisItem* pItem = NULL;
    CCARRAY_FOREACH_4TYPE(m_pSynopsis,MB_SynopsisItem*,pItem)
    {
        if((pItem->getDungeonID() == nDungeonID)
           && (pItem->getCondition() == nCondition))
        {
            return pItem;
        }
    }
    return NULL;
}

MB_SynopsisConfig* MB_SynopsisConfig::m_pSingletonInstance = NULL;

