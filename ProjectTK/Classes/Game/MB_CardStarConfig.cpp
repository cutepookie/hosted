//
//  MB_CardStarConfig.cpp
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-13.
//
//

#include "MB_CardStarConfig.h"

MB_CardProperty::MB_CardProperty():m_nStar(0)
{
    m_headFrameColor = ccc3(0, 0, 0);
}

bool MB_CardProperty::init(MB_XmlNode* pXmlNode)
{
    if (pXmlNode == NULL)
    {
        return false;
    }

    m_nStar = pXmlNode->queryAttributeByName("star")->intValue();
    m_cardFrame = pXmlNode->queryAttributeByName("cardFrame")->getCString();

    const char* pColor = pXmlNode->queryAttributeByName("headFrameColor")->getCString();
    m_szPetCircleFrame = pXmlNode->queryAttributeByName("petCircleIcon")->getCString();
    m_szItemCircleFrame = pXmlNode->queryAttributeByName("itemCircleIcon")->getCString();
    int data[3] = {};
    uint16_t realcount = 0;
    if (NSGameHelper::resolvIntValueFromString(pColor,data,realcount,3))
    {
        m_headFrameColor.r = data[0];
        m_headFrameColor.g = data[1];
        m_headFrameColor.b = data[2];
    }
    
    m_HeadFrame[MONSTER_HEADFRAME] = pXmlNode->queryAttributeByName("MonsterHeadFrame")->getCString();
    m_HeadFrame[ITEM_HEADFRAME] = pXmlNode->queryAttributeByName("ItemHeadFrame")->getCString();
    
    m_RankFrame[0] = pXmlNode->queryAttributeByName("rankFrame1")->getCString();
    m_RankFrame[1] = pXmlNode->queryAttributeByName("rankFrame2")->getCString();
    m_RankFrame[2] = pXmlNode->queryAttributeByName("rankFrame3")->getCString();

    return true;
}

const char* MB_CardProperty::getRankFrameByRank(uint16_t rank)const
{
    if ((0 <= rank) && (rank <= 9))
    {
        return m_RankFrame[0].c_str();
    }
    else if( (rank >= 10) && (rank <=19 ))
    {
        return m_RankFrame[1].c_str();
    }
    else if( rank == 20)
    {
        return m_RankFrame[2].c_str();
    }
    else
    {
        return m_RankFrame[0].c_str();
    }
}

const char* MB_CardProperty::getHeadFrame(uint8_t type)const
{
    if (type == MONSTER_HEADFRAME
        || type == ITEM_HEADFRAME)
    {
        return m_HeadFrame[type].c_str();
    }
    else
    {
        MB_LOG("ERROR MB_CardProperty::getHeadFrame %d",type);
    }
    return m_HeadFrame[0].c_str();
}

const char* MB_CardProperty::getHeadCircleFrame(uint8_t type)const
{
    return (type == MONSTER_HEADFRAME)?m_szPetCircleFrame.c_str():m_szItemCircleFrame.c_str();
}

MB_CardPropertyMgr* MB_CardPropertyMgr::m_pSingletonInstance = NULL;

MB_CardPropertyMgr* MB_CardPropertyMgr::getInstance()
{
    if (m_pSingletonInstance == NULL)
    {
        m_pSingletonInstance = new MB_CardPropertyMgr;
        m_pSingletonInstance->init();
    }
    return m_pSingletonInstance;
}

void MB_CardPropertyMgr::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(m_pSingletonInstance);
}

MB_CardPropertyMgr::MB_CardPropertyMgr()
{
    m_pContainer = NULL;
}

MB_CardPropertyMgr::~MB_CardPropertyMgr()
{
    CC_SAFE_RELEASE_NULL(m_pContainer);
}

bool MB_CardPropertyMgr::init()
{
    MB_XmlFile* pFile = new MB_XmlFile;

    if (pFile->readXmlData("config/battle_card_color.cb"))
    {
        CCArray* pArray = new CCArray;
        if(pFile->queryNodesByName("Property|item",pArray))
        {
            CC_SAFE_RELEASE_NULL(m_pContainer);
            m_pContainer = new CCArray;
            CCObject* pObject = NULL;
            MB_XmlNode* pNode = NULL;
            MB_CardProperty* pProperty = NULL;
            CCARRAY_FOREACH(pArray, pObject)
            {
                pNode = dynamic_cast<MB_XmlNode*>(pObject);
                if (pNode)
                {
                    pProperty = new MB_CardProperty;
                    pProperty->init(pNode);
                    m_pContainer->addObject(pProperty);
                    pProperty->release();
                }
            }
        }
        CC_SAFE_RELEASE_NULL(pArray);
    }
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("global.plist");

    CC_SAFE_RELEASE_NULL(pFile);
    return true;
}

const MB_CardProperty* MB_CardPropertyMgr::getCardPropertyByStar(int star)
{
    if (m_pContainer && m_pContainer->count())
    {
        CCObject* pObject = NULL;
        MB_CardProperty* pty = NULL;
        CCARRAY_FOREACH(m_pContainer,pObject)
        {
            pty = dynamic_cast<MB_CardProperty*>(pObject);
            if (pty && pty->getCardStar() == star)
            {
                return pty;
            }
        }
    }
    return NULL;
}


CCNode* MB_CardPropertyMgr::creatEffectByRank(uint16_t rank)
{
    CCNode* pNode = NULL;
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    if(rank<10)
    {
    }
    else if(rank<20)
    {
        CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
        pNode = pCCBReader->readNodeGraphFromFile("res/eff_monsterheadside_0.ccb");
        CC_SAFE_RELEASE_NULL(pCCBReader);
    }
    else
    {
        CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
        pNode = pCCBReader->readNodeGraphFromFile("res/eff_monsterheadside_1.ccbi");
        CC_SAFE_RELEASE_NULL(pCCBReader);
    }
    return pNode;
}


