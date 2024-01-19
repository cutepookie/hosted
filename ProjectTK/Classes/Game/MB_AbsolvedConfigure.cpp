//
//  MB_AbsolvedConfigure.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-15.
//
//

#include "MB_AbsolvedConfigure.h"
#include "Game.h"
#include "MB_ChapterData.h"
#include "MB_ChapterInterface.h"
#include "MB_ChapterData.h"

MB_ChapterDungeonData::MB_ChapterDungeonData(uint16_t nId)
{
    m_nChapterId = nId;
    m_pDungeonData = new CCArray;
}

MB_ChapterDungeonData::~MB_ChapterDungeonData()
{
    m_nChapterId = 0;
    CC_SAFE_RELEASE_NULL(m_pDungeonData);
}

const MB_DungeonData* MB_ChapterDungeonData::getDungeonDataByID(uint16_t nID)
{
    MB_DungeonData* pData = NULL;

    CCARRAY_FOREACH_4TYPE(m_pDungeonData, MB_DungeonData*, pData)
    {
        if (pData->getID() == nID)
        {
            return pData;
        }
    }
    
    return NULL;
}

MB_DungeonData* MB_ChapterDungeonData::cloneDungeonData(uint16_t nID)
{
    const MB_DungeonData* pTemp = getDungeonDataByID(nID);
    if (pTemp)
    {
        MB_DungeonData* pData = new MB_DungeonData;
        pData->autorelease();
        
        pData->setID(pTemp->getID());
        pData->setNumber(pTemp->getNumber());
        pData->setActiveNeedPass(pTemp->getActiveNeedPass());
        pData->setName(pTemp->getName());
        pData->setCostEnergy(pTemp->getCostEnergy());
        pData->setMaxTimes(pTemp->getMaxTimes());
        pData->setCoin(pTemp->getCoin());
        pData->setExpRole(pTemp->getExpRole());
        pData->setExpGeneral(pTemp->getExpGeneral());
        pData->setDropItem1(pTemp->getDropItem1());
        pData->setDropItem2(pTemp->getDropItem2());
        pData->setBossList(pTemp->getBossList());
        pData->setAddMorale(pTemp->getAddMorale());
        pData->setDungeon_icon(pTemp->getDungeon_icon());
        pData->setDungeonLevel(pTemp->getDungeonLevel());
    }
    
    return NULL;
}

bool MB_ChapterDungeonData::loadChapter()
{
    char buff[128] = {};
    sprintf(buff, "config/chapter/chapter_%d.xml",m_nChapterId);
    MB_XmlFile* pFile = MB_XmlFile::create(buff);
    if (pFile)
    {
        CCArray* pArray = CCArray::create();
        MB_XmlNode* pNode = NULL;
        MB_DungeonData* pDungeoData = NULL;
        if(pFile->queryNodesByName("Dungeons|Dungeon", pArray))
        {
            m_pDungeonData->removeAllObjects();
            CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pNode)
            {
                pDungeoData = new MB_DungeonData;
                
                pDungeoData->setID(pNode->queryAttributeByName("ID")->intValue());
                pDungeoData->setNumber(pNode->queryAttributeByName("Number")->intValue());
                pDungeoData->setActiveNeedPass(pNode->queryAttributeByName("activeneedpass")->intValue());
                pDungeoData->setName(pNode->queryAttributeByName("Name")->getCString());
                pDungeoData->setCostEnergy(pNode->queryAttributeByName("costenergy")->intValue());
                pDungeoData->setMaxTimes(pNode->queryAttributeByName("maxtimes")->intValue());
                pDungeoData->setCoin(pNode->queryAttributeByName("coin")->intValue());
                pDungeoData->setExpRole(pNode->queryAttributeByName("exprole")->intValue());
                pDungeoData->setExpGeneral(pNode->queryAttributeByName("expgeneral")->intValue());
                pDungeoData->setDropItem1(pNode->queryAttributeByName("dropitem1")->intValue());
                pDungeoData->setDropItem2(pNode->queryAttributeByName("dropitem2")->intValue());
                pDungeoData->setBossList(pNode->queryAttributeByName("boss_postion")->getCString());
                pDungeoData->setAddMorale(pNode->queryAttributeByName("addMorale")->intValue());
                pDungeoData->setDungeon_icon(pNode->queryAttributeByName("dungeon_icon")->intValue());
                pDungeoData->setDungeonLevel(pNode->queryAttributeByName("dungeon_level")->intValue());

                m_pDungeonData->addObject(pDungeoData);
                CC_SAFE_RELEASE_NULL(pDungeoData);
            }
        }
        return true;
    }
    return false;
}


MB_ChapterDungeonData* MB_AbsolvedConfigure::getChapterDungeonsID(uint16_t nChapterId)
{
    MB_ChapterDungeonData* pTemp = NULL;
    
    CCARRAY_FOREACH_4TYPE(m_pChapterArray, MB_ChapterDungeonData*, pTemp)
    {
        if (pTemp->getChapterId() == nChapterId)
        {
            return pTemp;
        }
    }
    
    pTemp = createChapterDungeonsByID(nChapterId);
    
    if (pTemp)
    {
        m_pChapterArray->addObject(pTemp);
        return pTemp;
    }
    
    return NULL;
}

const MB_DungeonData* MB_AbsolvedConfigure::getChapterDungeonDataById(uint16_t nChapterId,uint16_t nDungeonId)
{
    MB_ChapterDungeonData* pTemp = getChapterDungeonsID(nChapterId);
    if (pTemp)
    {
        return pTemp->getDungeonDataByID(nDungeonId);
    }
    
    return NULL;
}

MB_ChapterDungeonData* MB_AbsolvedConfigure::createChapterDungeonsByID(uint16_t nChapterId)
{
    MB_ChapterDungeonData* pData = new MB_ChapterDungeonData(nChapterId);
    
    pData->autorelease();
    
    if (pData->loadChapter())
    {
        m_pChapterArray->addObject(pData);
        return pData;
    }
    return NULL;
}


MB_AbsolvedConfigure::~MB_AbsolvedConfigure()
{
    for (int i=0; i<3; ++i)
    {
        CC_SAFE_RELEASE_NULL(m_pChapterPageList[i]);
    }
    CC_SAFE_RELEASE_NULL(m_pChapterArray);
    CC_SAFE_RELEASE_NULL(m_pChapterInterfaces);
}

MB_AbsolvedConfigure* MB_AbsolvedConfigure::getInstance()
{
    if (m_pSingtonInstance == NULL)
    {
        m_pSingtonInstance = new MB_AbsolvedConfigure;
        if(!m_pSingtonInstance->init())
        {
            CCLog("[error]:init absolved configure failed");
        }
    }
    return m_pSingtonInstance;
}

void MB_AbsolvedConfigure::destroyInstance()
{
    CC_SAFE_DELETE(m_pSingtonInstance);
}

MB_AbsolvedConfigure::MB_AbsolvedConfigure()
{
    for (int i=0; i<3; ++i)
    {
        m_pChapterPageList[i] = NULL;
    }
    m_pChapterArray = new CCArray;
    m_pChapterInterfaces = new CCArray;
    
}

MB_AbsolvedConfigure* MB_AbsolvedConfigure::m_pSingtonInstance = NULL;


bool MB_AbsolvedConfigure::readPageList(const char* pFile,MB_ChapterPageList** pPageList)
{
    MB_XmlFile* pXmlFile = MB_XmlFile::create(pFile);
    if (pXmlFile == NULL)
    {
        return false;
    }
    
    CCArray* pArray = CCArray::create();
    MB_XmlNode* pTemp = NULL;
    
    if(pXmlFile->queryNodesByName("ChapterPages", pArray))
    {
        CC_SAFE_RELEASE_NULL(*pPageList);
        CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pTemp)
        {
            *pPageList = new MB_ChapterPageList;
            if((*pPageList)->init(pTemp))
            {
                return true;
            }
        }
    }
    
    return false;
}

bool MB_AbsolvedConfigure::init()
{
    const char* files[] = {"config/chapter/chapter_group1.xml","config/chapter/chapter_group2.xml","config/chapter/chapter_group3.xml"};
    for (int i=0; i<3; ++i)
    {
        readPageList(files[i], &(m_pChapterPageList[i]));
    }
    return true;
}

bool MB_AbsolvedConfigure::queryChapterPageById(MB_ChapterPageList* pPageList,int nPageId,MB_ChapterPage** pPage)
{
    if (pPageList == NULL)
    {
        return false;
    }
    
    return pPageList->queryPageById(nPageId, pPage);
}

bool MB_AbsolvedConfigure::queryChapterPage(int nType, int nPageId,MB_ChapterPage** pPage)
{
    if (nType > 3 || nType < 1)
    {
        return false;
    }
    
    return queryChapterPageById(m_pChapterPageList[nType-1],nPageId,pPage);
}

bool MB_AbsolvedConfigure::queryChapterData(int nType, int nPageId,int nChapterId,MB_ChapterData** pData)
{
    MB_ChapterPage* pPage = NULL;
    if (queryChapterPage(nType, nPageId, &pPage))
    {
        return pPage->queryChapterById(nChapterId, pData);
    }
    
    return false;
}

bool MB_AbsolvedConfigure::queryChapterDataByID(int nChapterId,MB_ChapterData** pData)
{
    for (int i=1; i<=3; ++i)
    {
        if(m_pChapterPageList[i-1]->queryChapterByID(nChapterId,pData))
            return true;
    }
    return false;
}

bool MB_AbsolvedConfigure::queryPageByTypeAndChapterId(int nType,int nChapterId,MB_ChapterPage** pPage)
{
    if (nType > 3 || nType<1)
    {
        return false;
    }
    
    return m_pChapterPageList[nType-1]->queryPageByChapterId(nChapterId, pPage);
}

bool MB_AbsolvedConfigure::goChapter(int nType,int nPage,int nChapterID)
{
    MB_ChapterInterface* pInterface = NULL;
    queryChapterInterface(nType,nPage,nChapterID,&pInterface);
    if (pInterface)
    {
        pInterface->onEntryClicked(NULL);
        return true;
    }

    return false;
}

bool MB_AbsolvedConfigure::queryChapterInterface(int nType,int nPage,int nChapterID,MB_ChapterInterface** pInterface)
{
    MB_ChapterInterface* pTemp = NULL;
    
    CCARRAY_FOREACH_4TYPE(m_pChapterInterfaces, MB_ChapterInterface*, pTemp)
    {
        if (pTemp->getType() == nType
            && pTemp->getPageId() == nPage
            && pTemp->getChapterId() == nChapterID)
        {
            *pInterface = pTemp;
            return true;
        }
    }
    
    *pInterface = createChapterInterface(nType, nPage, nChapterID);
    
    if (*pInterface)
    {
        m_pChapterInterfaces->addObject(*pInterface);
    }
    
    return *pInterface != NULL;
}

MB_ChapterInterface* MB_AbsolvedConfigure::createChapterInterface(int nType,int nPage,int nChapterID)
{
    MB_ChapterPage* pPage = NULL;
    
    queryPageByTypeAndChapterId(nType,nChapterID,&pPage);

    
    if (pPage!=NULL)
    {
        MB_ChapterData* pData = NULL;
        if(pPage->queryChapterById(nChapterID,&pData))
        {
            MB_ChapterInterface* pInterface = new MB_ChapterInterface;
            if (pInterface)
            {
                pInterface->m_nChapterId = nChapterID;
                pInterface->m_nType = nType;
                pInterface->m_nPageId = pPage->getPageId();
                pInterface->autorelease();
                return pInterface;
            }
        }
    }
    return NULL;
}

bool MB_AbsolvedConfigure::chapterInPage(int nType,int nPage,int nChapter)
{
    MB_ChapterData* pData = NULL;
    return queryChapterData(nType, nPage,nChapter,&pData);
}

bool MB_AbsolvedConfigure::chapterExist(int nType,int nChapter)
{
    MB_ChapterPage* pPage = NULL;
    return queryPageByTypeAndChapterId(nType,nChapter,&pPage);
}

MB_ChapterData* MB_AbsolvedConfigure::getChapterDataById(uint16_t cid,int type)
{
    if (type>0&&type<=kChapterDifficultyGod)
    {
        MB_ChapterData* pData = NULL;
        m_pChapterPageList[type-1]->queryChapterByID(cid, &pData);
        return pData;
    }
    return NULL;
}