//
//  MB_TrainerRoadConfigure.cpp
//  ProjectMB
//
//  Created by wenyong on 15-1-16.
//
//

#include "MB_TrainerRoadConfigure.h"
#include "../Common/GameLib/UnityXml/MB_XmlItems.h"

bool MB_TrainerRoadDungeon::init(MB_XmlNode* pNode)
{
    m_nId = pNode->queryAttributeByName("id")->intValue();
    m_nHid = pNode->queryAttributeByName("hid")->getCString();
    m_szName = pNode->queryAttributeByName("name")->getCString();
    const char* pLocation = pNode->queryAttributeByName("location")->getCString();
    int location[2] = {0,0};
    uint16_t real_count = 0;
    NSGameHelper::resolvIntValueFromString(pLocation, location, real_count, 2);
    m_pLocation.x = location[0];
    m_pLocation.y = location[1];

    return true;
}

MB_TrainerRoadDungeon::MB_TrainerRoadDungeon()
{
    m_nId = 0;
}

bool MB_TrainerRoadRewardBox::init(MB_XmlNode* pNode)
{
    m_nId = pNode->queryAttributeByName("id")->intValue();
    const char* pLocation = pNode->queryAttributeByName("location")->getCString();
    int location[2] = {0,0};
    uint16_t real_count = 0;
    NSGameHelper::resolvIntValueFromString(pLocation, location, real_count, 2);
    m_pLocation.x = location[0];
    m_pLocation.y = location[1];
    return true;
}

MB_TrainerRoadRewardBox::MB_TrainerRoadRewardBox()
{
    m_nId = 0;
}

//MB_TrainerRoadPage::MB_TrainerRoadPage()
//{
//    m_pDungeons = new CCArray;
//    m_pRewardBoxes = new CCArray;
//    m_nIndex = 0;
//}
//
//MB_TrainerRoadPage::~MB_TrainerRoadPage()
//{
//    CC_SAFE_RELEASE_NULL(m_pDungeons);
//    CC_SAFE_RELEASE_NULL(m_pRewardBoxes);
//}
//
//bool MB_TrainerRoadPage::init(MB_XmlNode* pNode)
//{
//    CCArray* pArray = CCArray::create();
//    m_pDungeons->removeAllObjects();
//    m_pRewardBoxes->removeAllObjects();
//    
//    m_nIndex = pNode->queryAttributeByName("index")->intValue();
//    m_szFile = pNode->queryAttributeByName("background")->getCString();
//    
//    if(pNode->queryNodesByName("dungeon", pArray))
//    {
//        MB_XmlNode* pNode = NULL;
//        MB_TrainerRoadDungeon* pDungeon = NULL;
//        CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pNode)
//        {
//            pDungeon = new MB_TrainerRoadDungeon();
//            if (pDungeon->init(pNode))
//            {
//                m_pDungeons->addObject(pDungeon);
//            }
//            CC_SAFE_RELEASE_NULL(pDungeon);
//        }
//    }
//    
//    pArray->removeAllObjects();
//    
//    if (pNode->queryNodesByName("box", pArray))
//    {
//        MB_XmlNode* pNode = NULL;
//        MB_TrainerRoadRewardBox* pBox = NULL;
//        CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pNode)
//        {
//            pBox = new MB_TrainerRoadRewardBox();
//            if (pBox->init(pNode))
//            {
//                m_pDungeons->addObject(pBox);
//            }
//            CC_SAFE_RELEASE_NULL(pBox);
//        }
//    }
//    
//    return true;
//}

MB_TrainerRoadConfigure::MB_TrainerRoadConfigure()
{
    m_pDungeons = new CCArray;
    m_pBoxs = new CCArray;
    load();
}

MB_TrainerRoadConfigure::~MB_TrainerRoadConfigure()
{
    CC_SAFE_RELEASE_NULL(m_pDungeons);
    CC_SAFE_RELEASE_NULL(m_pBoxs);
}

bool MB_TrainerRoadConfigure::init(MB_XmlNode* pNode)
{
    CCArray* pArray = CCArray::create();
    if (pNode->queryNodesByName("dungeon", pArray))
    {
        MB_XmlNode* p = NULL;
        MB_TrainerRoadDungeon* pDungeon = NULL;
        CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, p)
        {
            pDungeon = new MB_TrainerRoadDungeon;
            if (pDungeon->init(p))
            {
                m_pDungeons->addObject(pDungeon);
            }
            CC_SAFE_RELEASE_NULL(pDungeon);
        }
    }
    
    pArray->removeAllObjects();
    if (pNode->queryNodesByName("box", pArray))
    {
        MB_XmlNode* p = NULL;
        MB_TrainerRoadRewardBox* pBox = NULL;
        CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, p)
        {
            pBox = new MB_TrainerRoadRewardBox;
            if (pBox->init(p))
            {
                m_pBoxs->addObject(pBox);
            }
            CC_SAFE_RELEASE_NULL(pBox);
        }
    }
    return true;
}

bool MB_TrainerRoadConfigure::load()
{
    m_pDungeons->removeAllObjects();
    m_pBoxs->removeAllObjects();
    MB_XmlFile* pFile = MB_XmlFile::create("config/trainer_road.xml");
    if (pFile)
    {
        CCArray* pArray = CCArray::create();
        if(pFile->queryNodesByName("roads|page", pArray))
        {
            MB_XmlNode* p = NULL;
            CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, p)
            {
                init(p);
            }
            return true;
//            MB_XmlNode* pNode = (MB_XmlNode*)pArray->objectAtIndex(0);
//            return init(pNode);
        }
    }
    return false;
}