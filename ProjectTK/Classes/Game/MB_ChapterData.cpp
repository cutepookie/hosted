//
//  MB_ChapterData.cpp
//  ProjectTK
//
//  Created  by Yan Jiyong on 13-3-5.
//
//

#include "MB_ChapterData.h"
#include "Game.h"
/*
MB_ChapterData::MB_ChapterData()
:m_uIsPassed(0)
,m_bIsPerfectPass(false)
,m_bIsNicePass(false)
{
}

MB_ChapterData::~MB_ChapterData(){
    
}

static MB_ChapterMgr * s_pChapterMgr = NULL;

MB_ChapterMgr::MB_ChapterMgr()
{
    m_pChapterArray = CCArray::create();
    m_pChapterArray->retain();
    
    if (!initChapterTemplete()) {
        MB_LOG("init chapterlist.xml failed.");
    }
    m_pChapterArray2 = CCArray::create();
    m_pChapterArray2->retain();
    
    if (!initChapterTemplete2()) {
        MB_LOG("init chapterlist.xml failed.");
    }
    
    SOCKET_MSG_REGIST(SC_BATTLE_PROGRESS,MB_ChapterMgr );
    SOCKET_MSG_REGIST(SC_BATTLE_PERFECT_REWARD,MB_ChapterMgr );
    SOCKET_MSG_REGIST(SC_BATTLE_INFO,MB_ChapterMgr );
    
    
}
MB_ChapterMgr::~MB_ChapterMgr()
{
    CC_SAFE_RELEASE_NULL(m_pChapterArray);
    DungeonMap::iterator iter = m_mapDungeonInfo.begin();
    while (iter != m_mapDungeonInfo.end()) {
    
        CC_SAFE_RELEASE_NULL(iter->second);
        iter++;
    }
    
    CC_SAFE_RELEASE_NULL(m_pChapterArray2);
    DungeonMap::iterator iter2 = m_mapDungeonInfo2.begin();
    while (iter2 != m_mapDungeonInfo2.end()) {
        
        CC_SAFE_RELEASE_NULL(iter2->second);
        iter2++;
    }
    SOCKET_MSG_UNREGIST(SC_BATTLE_PROGRESS);
    SOCKET_MSG_UNREGIST(SC_BATTLE_PERFECT_REWARD);
    SOCKET_MSG_UNREGIST(SC_BATTLE_INFO);
    
}
uint16_t MB_ChapterMgr::getNowDungeon(){
    
    return m_nNowDungeon;
}

uint16_t MB_ChapterMgr::getNowChaper(){
    
    return m_nNowChapter;
    
}
uint16_t MB_ChapterMgr::getNowDungeon2(){
    
    return m_nNowDungeon2;
}

uint16_t MB_ChapterMgr::getNowChaper2(){
    
    return m_nNowChapter2;
    
}
MB_ChapterMgr* MB_ChapterMgr::getInstance(){
    
    if (s_pChapterMgr == NULL) {
        
        s_pChapterMgr = new MB_ChapterMgr();
    }
    
    return s_pChapterMgr;
}

void MB_ChapterMgr::destroyInstance()
{
    CC_SAFE_DELETE(s_pChapterMgr);
    s_pChapterMgr = NULL;
}

CCArray * MB_ChapterMgr::getChaperArray()
{
    return m_pChapterArray;
}

MB_ChapterData* MB_ChapterMgr::getChapterDataByID(uint16_t chapterID){
    
    CCObject *chapterData = NULL;
    
    CCARRAY_FOREACH(m_pChapterArray, chapterData){
        
        MB_ChapterData *data =(MB_ChapterData *)chapterData;
        
        if(data->getID() == chapterID ){
            
            return data;
        }
    }
    return  NULL;
}

CCArray* MB_ChapterMgr::getDungeonArrayByChapterID(uint16_t chapterID)
{
    DungeonMap::iterator iter = m_mapDungeonInfo.find(chapterID);
    if (iter != m_mapDungeonInfo.end()) {
        return iter->second;
    }
    else
    {
        if( initDungeonsByChapterID(chapterID)){
            
            return  getDungeonArrayByChapterID(chapterID);
        }
        return NULL;
    }
}
CCArray * MB_ChapterMgr::getChaperArray2()
{
    return m_pChapterArray2;
}

MB_ChapterData* MB_ChapterMgr::getChapterDataByID2(uint16_t chapterID){
    
    CCObject *chapterData = NULL;
    
    CCARRAY_FOREACH(m_pChapterArray2, chapterData){
        
        MB_ChapterData *data =(MB_ChapterData *)chapterData;
        
        if(data->getID() == chapterID ){
            
            return data;
        }
    }
    return  NULL;
}

CCArray* MB_ChapterMgr::getDungeonArrayByChapterID2(uint16_t chapterID)
{
    DungeonMap::iterator iter = m_mapDungeonInfo2.find(chapterID);
    if (iter != m_mapDungeonInfo2.end()) {
        return iter->second;
    }
    else
    {
        if( initDungeonsByChapterID2(chapterID)){
            
            return  getDungeonArrayByChapterID2(chapterID);
        }
        return NULL;
    }
}

bool MB_ChapterMgr::initChapterTemplete()
{
    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/chapter/chapterlist.xml");
    
    if (!g_sharedDoc)
    {
        return false;
    }
    
    xmlNodePtr root;
    
    root=xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    while(curNode != NULL) {
        
        if (xmlStrcmp(curNode->name,BAD_CAST "chapter")) {
            curNode = curNode->next;
            continue;
        }
        
        struct _xmlAttr * attr = curNode->properties;
        
        if (attr != NULL) {
            
            MB_ChapterData* chapterNode = new MB_ChapterData();
            
            if (!xmlStrcmp(attr->name,BAD_CAST "id"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setID(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "number"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setNumber(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "name"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setName(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "description"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setDescription(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "icon"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setIcon(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "dialog"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setDialog(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "type"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setType(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "closetime"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                // chapterNode->setCloseTime(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "activeneedlevel"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setNeedLevel(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "activeneedpass"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setNeedPass(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "coin"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setCoin(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "goldbonus"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setGoldBonus(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "reputation"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setReputation(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "pos"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setPos(atoi(value));
                CC_SAFE_FREE(value);
                
            }
            
            m_pChapterArray->addObject(chapterNode);
            chapterNode->release();
        }
        else
        {
            MB_LOG("Error:empty chapter in templete.");
        }
        curNode = curNode->next;
    }
    xmlFreeDoc(g_sharedDoc);
    
    return true;
}
bool MB_ChapterMgr::initChapterTemplete2()
{
    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/chapter/chapterlist2.xml");
    
    if (!g_sharedDoc)
    {
        return false;
    }
    
    xmlNodePtr root;
    
    root=xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    while(curNode != NULL) {
        
        if (xmlStrcmp(curNode->name,BAD_CAST "chapter")) {
            curNode = curNode->next;
            continue;
        }
        
        struct _xmlAttr * attr = curNode->properties;
        
        if (attr != NULL) {
            
            MB_ChapterData* chapterNode = new MB_ChapterData();
            
            if (!xmlStrcmp(attr->name,BAD_CAST "id"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setID(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "number"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setNumber(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "name"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setName(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "description"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setDescription(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "icon"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setIcon(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "dialog"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setDialog(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "type"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setType(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "closetime"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                // chapterNode->setCloseTime(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "activeneedlevel"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setNeedLevel(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "activeneedpass"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setNeedPass(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "coin"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setCoin(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "goldbonus"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setGoldBonus(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "reputation"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setReputation(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "pos"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                chapterNode->setPos(atoi(value));
                CC_SAFE_FREE(value);
                
            }
            chapterNode->setType(kChapterTypeAdvance);
            m_pChapterArray2->addObject(chapterNode);
            chapterNode->release();
        }
        else
        {
            MB_LOG("Error:empty chapter in templete.");
        }
        curNode = curNode->next;
    }
    xmlFreeDoc(g_sharedDoc);
    
    return true;
}


bool MB_ChapterMgr::initDungeonsByChapterID(uint16_t chapterID)
{
    //是否已經初始化
    DungeonMap::iterator iterMD = m_mapDungeonInfo.find(chapterID);
    if (iterMD != m_mapDungeonInfo.end()) {
        return true;
    }
    
    char  filename[50];
    sprintf(filename, "config/chapter/chapter_%d.xml",chapterID);
    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml(filename);
    
    if (!g_sharedDoc)
    {
        return false;
    }
    
    xmlNodePtr root;
    
    root=xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    
    CCArray* dungeonArray = CCArray::create();
    dungeonArray->retain();
    
    while(curNode != NULL) {
        
        if (xmlStrcmp(curNode->name,BAD_CAST "Dungeon")) {
            curNode = curNode->next;
            continue;
        }
        
        struct _xmlAttr * attr = curNode->properties;
        MB_DungeonData* dungeonNode = new MB_DungeonData();
        
        if (attr != NULL) {
            
            if (!xmlStrcmp(attr->name,BAD_CAST "ID"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setID(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "Number"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setNumber(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "Name"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setName(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "activeneedpass"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setActiveNeedPass(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "costenergy"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setCostEnergy(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "maxtimes"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setMaxTimes(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "general01"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setGeneral1(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "general02"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setGeneral2(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "general03"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setGeneral3(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "general04"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setGeneral4(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "general05"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setGeneral5(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "general06"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setGeneral6(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "coin"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setCoin(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "exprole"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setExpRole(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "expgeneral"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setExpGeneral(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "dropitem1"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setDropItem1(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "dropitem2"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setDropItem2(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            if (!xmlStrcmp(attr->name,BAD_CAST "boss_postion"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setBossList(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            if (!xmlStrcmp(attr->name,BAD_CAST "addMorale"))
            {
                
                attr = attr->next;
            }
            if (!xmlStrcmp(attr->name,BAD_CAST "dungeon_icon"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setDungeon_icon(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
                
            }
            if(!xmlStrcmp(attr->name, BAD_CAST "dungeon_level")){
                
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setDungeonLevel(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }

            
            //初始化的時候剩余次數等於最大次數
            dungeonNode->setLeftTime(dungeonNode->getMaxTimes());
            //初始化的時候未通關
            dungeonNode->setBestScore(0);
            dungeonArray->addObject(dungeonNode);
            dungeonNode->release();
        }
        else
        {
            MB_LOG("Error:empty chapter in templete.");
        }
        
        curNode = curNode->next;
    }
    
    m_mapDungeonInfo.insert(DungeonMapEntry(chapterID, dungeonArray));
    
    xmlFreeDoc(g_sharedDoc);
    
    return true;
}

bool MB_ChapterMgr::initDungeonsByChapterID2(uint16_t chapterID)
{
    //是否已經初始化
    DungeonMap::iterator iterMD = m_mapDungeonInfo2.find(chapterID);
    if (iterMD != m_mapDungeonInfo2.end()) {
        return true;
    }
    
    char  filename[50];
    sprintf(filename, "config/chapter/chapter_%d.xml",chapterID);
    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml(filename);
    
    if (!g_sharedDoc)
    {
        return false;
    }
    
    xmlNodePtr root;
    
    root=xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    
    CCArray* dungeonArray = CCArray::create();
    dungeonArray->retain();
    
    while(curNode != NULL) {
        
        if (xmlStrcmp(curNode->name,BAD_CAST "Dungeon")) {
            curNode = curNode->next;
            continue;
        }
        
        struct _xmlAttr * attr = curNode->properties;
        MB_DungeonData* dungeonNode = new MB_DungeonData();
        
        if (attr != NULL) {
            
            if (!xmlStrcmp(attr->name,BAD_CAST "ID"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setID(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "Number"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setNumber(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "Name"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setName(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "activeneedpass"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setActiveNeedPass(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "costenergy"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setCostEnergy(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "maxtimes"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setMaxTimes(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "general01"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setGeneral1(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "general02"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setGeneral2(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "general03"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setGeneral3(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "general04"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setGeneral4(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "general05"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setGeneral5(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "general06"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setGeneral6(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "coin"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setCoin(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "exprole"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setExpRole(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "expgeneral"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setExpGeneral(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "dropitem1"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setDropItem1(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "dropitem2"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setDropItem2(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            if (!xmlStrcmp(attr->name,BAD_CAST "boss_postion"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setBossList(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            if (!xmlStrcmp(attr->name,BAD_CAST "addMorale"))
            {
                
                attr = attr->next;
            }
            if (!xmlStrcmp(attr->name,BAD_CAST "dungeon_icon"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setDungeon_icon(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
                
            }
            if(!xmlStrcmp(attr->name, BAD_CAST "dungeon_level")){
                
                value = (char*)xmlNodeGetContent(attr->children);
                dungeonNode->setDungeonLevel(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            
            //初始化的時候剩余次數等於最大次數
            dungeonNode->setLeftTime(dungeonNode->getMaxTimes());
            //初始化的時候未通關
            dungeonNode->setBestScore(0);
            dungeonArray->addObject(dungeonNode);
            dungeonNode->release();
        }
        else
        {
            MB_LOG("Error:empty chapter in templete.");
        }
        
        curNode = curNode->next;
    }
    
    m_mapDungeonInfo2.insert(DungeonMapEntry(chapterID, dungeonArray));
    xmlFreeDoc(g_sharedDoc);
    
    return true;
}

void MB_ChapterMgr::initChapterPassStatus()
{
    for (int i = 0; i < m_pChapterArray->count(); ++i) {
        
        
        MB_ChapterData* chapterData = (MB_ChapterData*)m_pChapterArray->objectAtIndex(i);
        if (chapterData->getID() < m_nNowChapter) {
            chapterData->setIsPassed(1);
        }
        else if (chapterData->getID() == m_nNowChapter)
        {
            chapterData->setIsPassed(2);
        }
        CCObject *dungeon;
        CCArray *dunArray = this->getDungeonArrayByChapterID( chapterData->getID());
        if (dunArray != NULL){
            
            CCARRAY_FOREACH(dunArray ,dungeon){
                
                ((MB_DungeonData *)dungeon)->setBestScore(0);
                ((MB_DungeonData *)dungeon)->setLeftTime(((MB_DungeonData *)dungeon)->getMaxTimes());
                
            }
        }
        
    }
    for (int i = 0; i < m_pChapterArray2->count(); ++i) {
        
        
        MB_ChapterData* chapterData = (MB_ChapterData*)m_pChapterArray2->objectAtIndex(i);
        if (chapterData->getID() < m_nNowChapter2) {
            chapterData->setIsPassed(1);
        }
        else if (chapterData->getID() == m_nNowChapter2)
        {
            chapterData->setIsPassed(2);
        }
        CCObject *dungeon;
        CCArray *dunArray = this->getDungeonArrayByChapterID2( chapterData->getID());
        if (dunArray != NULL){
            
            CCARRAY_FOREACH(dunArray ,dungeon){
                
                ((MB_DungeonData *)dungeon)->setBestScore(0);
                ((MB_DungeonData *)dungeon)->setLeftTime(((MB_DungeonData *)dungeon)->getMaxTimes());
                
            }
        }
    }

}
void MB_ChapterMgr::initChapterPassStatus2()
{
    for (int i = 0; i < m_pChapterArray2->count(); ++i) {
        
        MB_ChapterData* chapterData = (MB_ChapterData*)m_pChapterArray2->objectAtIndex(i);
        if (chapterData->getID() < m_nNowChapter2) {
            
            chapterData->setIsPassed(1);
        }
        else if (chapterData->getID() == m_nNowChapter2)
        {
            chapterData->setIsPassed(2);
        }
        CCObject *dungeon;
        CCArray *dunArray = this->getDungeonArrayByChapterID2( chapterData->getID());
        if (dunArray != NULL){
            
            CCARRAY_FOREACH(dunArray ,dungeon){
                
                ((MB_DungeonData *)dungeon)->setBestScore(0);
                ((MB_DungeonData *)dungeon)->setLeftTime(((MB_DungeonData *)dungeon)->getMaxTimes());
                
            }
        }
    }
}

bool MB_ChapterMgr::sendbattle_progress()
{
    SOCKET_REQUEST_START(CS_BATTLE_PROGRESS);
    SOCKET_REQUEST_END(SC_BATTLE_PROGRESS, MB_ChapterMgr::onMsgRecv);
    return true;
}

bool MB_ChapterMgr::recvbattle_progress(MB_MsgBuffer *recvPacket)
{
    uint16_t curDungeonID, curChapterID;
    if (recvPacket->readU16(&curDungeonID)
        && recvPacket->readU16(&curChapterID))
    {
        m_nNowDungeon = curDungeonID;
        m_nNowChapter = curChapterID;
        
        recvPacket->readU16(&curDungeonID);
        recvPacket->readU16(&curChapterID);
        
        m_nNowDungeon2 = curDungeonID;
        m_nNowChapter2 = curChapterID;
        
        uint16_t lenghth,addChapterID;
        recvPacket->readU16(&lenghth);
        initChapterPassStatus();
        
        for (int i = 0 ; i < lenghth; i++) {
            
            recvPacket->readU16(&addChapterID);
            MB_ChapterData * chapter = getChapterDataByID(addChapterID);
            if(chapter == NULL){
            
                chapter = getChapterDataByID2(addChapterID);

            }
            if(chapter != NULL){
             
                chapter->setIsNicePass(true);
            }
            
        }
        
        return true;
    }
    else
    {
        return false;
    }
}
void MB_ChapterMgr::setNowDungeon( uint16_t dungeon){
    
    m_nNowDungeon =  dungeon;
}
void MB_ChapterMgr::setNowChaper(uint16_t Chaper){
    
    m_nNowChapter = Chaper;
}
void MB_ChapterMgr::setNowDungeon2( uint16_t dungeon){
    
    m_nNowDungeon2 =  dungeon;
}
void MB_ChapterMgr::setNowChaper2(uint16_t Chaper){
    
    m_nNowChapter2 = Chaper;
}
bool MB_ChapterMgr::sendbattle_info(uint16_t chapterID,uint8_t type)
{
    m_nNowBattleType = type;
    
    //初始化dungeon模板數据
    if( m_nNowBattleType == kChapterTypeNormal){
    
        initDungeonsByChapterID(chapterID);
        
    }else {
    
        initDungeonsByChapterID2(chapterID);

    }
    SOCKET_REQUEST_START(CS_BATTLE_INFO);
    packet->writeU16(chapterID);
    SOCKET_REQUEST_END(SC_BATTLE_INFO, MB_ChapterMananhpet::onMsgRecv);
    return true;
}

bool MB_ChapterMgr::recvbattle_info(MB_MsgBuffer *recvPacket)
{
    return true;
    uint16_t chapterID;
    DungeonMap::iterator iter;
    CCArray* dungeonArray = NULL;
    int i;
    
    if (recvPacket->readU16(&chapterID)) {
        
        if(m_nNowBattleType ==  kChapterTypeNormal){
           
            iter = m_mapDungeonInfo.find(chapterID);
            if (iter != m_mapDungeonInfo.end()) {
                dungeonArray = iter->second;
            }
            else{
                MB_LOG("recvbattle_info error chapterID:%d",chapterID);
                return false;
            }
        }else {
        
            iter = m_mapDungeonInfo2.find(chapterID);
            if (iter != m_mapDungeonInfo2.end()) {
                dungeonArray = iter->second;
            }
            else{
                MB_LOG("recvbattle_info error chapterID:%d",chapterID);
                return false;
            }

        }
    }
    //是否已領取章節獎勵
    uint8_t isGetReward;
    recvPacket->readU8(&isGetReward);
    MB_ChapterData* chapterData;
    if(m_nNowBattleType ==  kChapterTypeNormal){
     
        for (i = 0; i < m_pChapterArray->count(); ++i)
        {
            chapterData = (MB_ChapterData*)m_pChapterArray->objectAtIndex(i);
            if (chapterData->getID() == chapterID) {
                if (isGetReward == 1) {
                    chapterData->setPerfectRewarded(true);
                    chapterData->setIsNicePass(true);
                }
                else
                {
                    chapterData->setPerfectRewarded(false);
                }
                break;
            }
        }
        
    }else {
        
        for (i = 0; i < m_pChapterArray2->count(); ++i)
        {
            chapterData = (MB_ChapterData*)m_pChapterArray2->objectAtIndex(i);
            
            if (chapterData->getID() == chapterID) {
                if (isGetReward == 1) {
                    chapterData->setPerfectRewarded(true);
                    chapterData->setIsNicePass(true);
                }
                else
                {
                    chapterData->setPerfectRewarded(false);
                }
                break;
            }
        }
    }
    

    //關卡數据中加入剩余次數和最高分
    uint16_t count = 0;
    if (recvPacket->readU16(&count))
    {
        
        uint16_t totalScore = 0;
        for (i = 0; i < count; ++i) {
            
            uint16_t dungeonid,leftime;
            uint8_t bestscore;
            recvPacket->readU16(&dungeonid);
            recvPacket->readU16(&leftime);
            recvPacket->readU8(&bestscore);
            totalScore += bestscore;
            MB_DungeonData* dungeonData = (MB_DungeonData*)dungeonArray->objectAtIndex(i);
            if (dungeonData != NULL) {
                
                if(dungeonData->getID() == dungeonid){
                    
                    dungeonData->setLeftTime(leftime);
                    dungeonData->setBestScore(bestscore);
                }
            }
            else
            {
                MB_LOG("dungeon data is null at index:%d", i);
                return false;
            }
        }
        //perfect scroe is 3
        if (totalScore == dungeonArray->count() * 3) {
            chapterData->setIsPerfectPass(true);
            chapterData->setIsNicePass(true);
        }
    }
    else
    {
        return false;
    }
    return true;
}

bool MB_ChapterMgr::sendbattle_perfect_reward(uint16_t chapterID)
{
    
    SOCKET_REQUEST_START(CS_BATTLE_PERFECT_REWARD);
    packet->writeU16(chapterID);
    SOCKET_REQUEST_END(SC_BATTLE_PERFECT_REWARD, MB_ChapterMgr::onMsgRecv);
    return true;
}

bool MB_ChapterMgr::recvbattle_perfect_reward(MB_MsgBuffer *recvPacket)
{
    uint8_t result;
    
    recvPacket->readU8(&result);
    
    MB_Message::removeALLMessage();
    
    if( result==1){
        
               
    }else if(result==2){
        
        
        MB_Message::sharedMB_Message()->showMessage("失敗", "不能重複領取！","確定",NULL,NULL,NULL,NULL,NULL);
        
    }else{
        
        MB_Message::sharedMB_Message()->showMessage("失敗", "未完美通關！","確定",NULL,NULL,NULL,NULL,NULL);
    }
    
    if (result == 1) {
        return true;
    }
    else{
        MB_LOG("recvbattle_perfect_reward errcode:%d", result);
        return false;
    }
}

void MB_ChapterMgr::onMsgRecv(CCNode *node, SocketResponse *response)
{
    assert(response != NULL);
    
    //將socket數据读取到序列化結构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议號
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg) {
            
        case SC_BATTLE_PROGRESS:
            recvbattle_progress(recvPacket);
            break;
        case SC_BATTLE_INFO:
            recvbattle_info(recvPacket);
            break;
        case SC_BATTLE_PERFECT_REWARD:
            recvbattle_perfect_reward(recvPacket);
            break;
            
        default:
            break;
    }
    
}

MB_ExplorerData::MB_ExplorerData(){
    
    setPos(-1);
    setChapterisgiveup(false);
    setCollectEndTime(0);
    setCollectType(0);
    setCollectValue(0);
    setCollectNum(0);
}
MB_ExplorerData::~MB_ExplorerData(){
    
}
void MB_ExplorerData::setChapterCard(const char * chapterCard){
    
    m_strChapterCard = chapterCard;
}
const char * MB_ExplorerData::getChapterCard(){
    
    return m_strChapterCard.c_str();
}
const char *MB_ExplorerData::getUitKey(char *databuf){
    
    sprintf(databuf, "chapter%dtype%d",getID(),getType());
    return databuf;
}*/

MB_DungeonData::MB_DungeonData(){
    m_iBestScore = 0;
}

MB_DungeonData::~MB_DungeonData(){
    
}
MB_ExpDungeonData::MB_ExpDungeonData(){

    m_nState  = 100;
}
MB_ExpDungeonData::~MB_ExpDungeonData(){
}

MB_EventHarm::MB_EventHarm(){
    
    
}
MB_EventHarm::~MB_EventHarm(){
    
}
MB_EventLastReport::MB_EventLastReport(){
    
    m_pHuLaInfoList = new CCArray();
    m_pLuckyRoleList = new CCArray();
    m_nBossLevel = 0;
    m_nBossMaxHp = 0;
    m_nInterValSec = 0;
    
}
MB_EventLastReport::~MB_EventLastReport(){
    
    CC_SAFE_RELEASE_NULL(m_pHuLaInfoList);
    CC_SAFE_RELEASE_NULL(m_pLuckyRoleList);
}
CCArray * MB_EventLastReport::getHuaInfoList(){
    
    return m_pHuLaInfoList;
}
CCArray * MB_EventLastReport::getLuckyRoleList(){
    
    return  m_pLuckyRoleList;
}
const char *MB_EventHarm::getName(){
    
    return m_strName.c_str();
}
void MB_EventHarm::setName(const char *name){
    
    m_strName = name;
}
const char * MB_EventData::getEventName(){
    
    return m_strEventName.c_str();
}
void MB_EventData::setEventName(const char *eventName){
    
    m_strEventName = eventName;
}
CCArray *MB_EventData::getHarmList(){
    
    return m_pHarmList;
}
MB_EventLastReport *  MB_EventData::getEventLastReport(){
    
    return   m_pEventLastReport;
}
void MB_EventData::loadRank(){
    return;
    char filename[1000];
    sprintf(filename, "%s%dacivity%d.xml", CCFileUtils::sharedFileUtils()->getWritablePath().c_str(),MB_ServerList::getInstance()->getNowServerID(),m_nEventId);
    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml(filename);
    if (g_sharedDoc == NULL)
    {
        return ;
    }
    
    xmlNodePtr root;
    root=xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    
    for ( struct _xmlAttr * attr = root->properties; attr != NULL ; attr = attr->next ) {
        
        if (!xmlStrcmp(attr->name,BAD_CAST "serverid")){
            
            value = (char*)xmlNodeGetContent(attr->children);
            
            if ( MB_ServerList::getInstance()->getNowServerID() != atoi(value)){
                
                m_nCurSavedInfoId = 0;
                xmlFreeDoc(g_sharedDoc);
                return;
            }
            CC_SAFE_FREE(value);
        }else if (!xmlStrcmp(attr->name,BAD_CAST "cursavedinfoid")){
            
            value = (char*)xmlNodeGetContent(attr->children);
            m_nCurSavedInfoId = atoi(value);
            CC_SAFE_FREE(value);
        }
        
    }
    while(curNode != NULL) {
        
        if (!xmlStrcmp(curNode->name,BAD_CAST "report")){
            
            loadLastReport(curNode);
            curNode = curNode->next;
            continue;
        }
        curNode = curNode->next;
    }
    xmlFreeDoc(g_sharedDoc);
}
void MB_EventData::loadLastReport( xmlNodePtr curNode){
    
    char *value = NULL;
    for ( struct _xmlAttr * attr = curNode->properties; attr != NULL ; attr = attr->next ) {
        
        if (!xmlStrcmp(attr->name,BAD_CAST "bosslevel")){
            
            value = (char*)xmlNodeGetContent(attr->children);
            m_pEventLastReport->setBossLevel(atoi(value));
            CC_SAFE_FREE(value);
            
        }else if (!xmlStrcmp(attr->name,BAD_CAST "intervalsec")){
            
            value = (char*)xmlNodeGetContent(attr->children);
            m_pEventLastReport->setInterValSec(atoi(value));
            CC_SAFE_FREE(value);
            
        }else if (!xmlStrcmp(attr->name,BAD_CAST "bossmaxhp")){
            
            value = (char*)xmlNodeGetContent(attr->children);
            m_pEventLastReport->setBossMaxHp(atoi(value));
            CC_SAFE_FREE(value);
        }
        
    }
    m_pEventLastReport->getHuaInfoList()->removeAllObjects();
    m_pEventLastReport->getLuckyRoleList()->removeAllObjects();
    xmlNodePtr child = curNode->children;
    for (; child != NULL ; child = child->next) {
        
        if (!xmlStrcmp(child->name,BAD_CAST "rank")){
            
            MB_EventHarm * data = new   MB_EventHarm();
            for ( struct _xmlAttr * attr = child->properties; attr != NULL ; attr = attr->next ) {
                
                if (!xmlStrcmp(attr->name,BAD_CAST "username")){
                    
                    value = (char*)xmlNodeGetContent(attr->children);
                    data->setName(value);
                    CC_SAFE_FREE(value);
                    
                }else  if (!xmlStrcmp(attr->name,BAD_CAST "harm")){
                    
                    value = (char*)xmlNodeGetContent(attr->children);
                    data->setHarm(atoi(value));
                    CC_SAFE_FREE(value);
                    
                }
            }
            m_pEventLastReport->getHuaInfoList()->addObject(data);
            data->release();
            
            
        }else if(!xmlStrcmp(child->name,BAD_CAST "lucky")){
            
            std::string str;
            for ( struct _xmlAttr * attr = child->properties; attr != NULL ; attr = attr->next ) {
                
                if (!xmlStrcmp(attr->name,BAD_CAST "username")){
                    
                    value = (char*)xmlNodeGetContent(attr->children);
                    str = (const char *)value;
                    CC_SAFE_FREE(value);
                    
                }
            }
            m_pEventLastReport->getLuckyRoleList()->addObject(CCString::create(str));
        }
    }
    
    
}
void MB_EventData::saveRank(){
    return;
    char filename[1000];
    sprintf(filename, "%s%dacivity%d.xml", CCFileUtils::sharedFileUtils()->getWritablePath().c_str(),MB_ServerList::getInstance()->getNowServerID(),m_nEventId);
    xmlDocPtr  g_sharedDoc = xmlNewDoc(BAD_CAST "1.0");
    xmlNodePtr root = xmlNewNode(NULL, BAD_CAST"EventData");
    xmlDocSetRootElement(g_sharedDoc, root);
    char datastr[10];
    sprintf(datastr, "%d",MB_ServerList::getInstance()->getNowServerID());
    xmlNewProp(root,BAD_CAST "serverid",BAD_CAST datastr);
    sprintf(datastr, "%d",m_nCurSavedInfoId);
    xmlNewProp(root,BAD_CAST "cursavedinfoid",BAD_CAST datastr);
    xmlNodePtr preReport = xmlNewNode(NULL,BAD_CAST "report");
    xmlAddChild(root,preReport);
    sprintf(datastr, "%d",m_pEventLastReport->getBossLevel());
    xmlNewProp(preReport,BAD_CAST "bosslevel",BAD_CAST datastr);
    sprintf(datastr, "%d",m_pEventLastReport->getInterValSec());
    xmlNewProp(preReport,BAD_CAST "intervalsec",BAD_CAST datastr);
    sprintf(datastr, "%lld",m_pEventLastReport->getBossMaxHp());
    xmlNewProp(preReport,BAD_CAST "bossmaxhp",BAD_CAST datastr);
    CCObject *obj;
    CCARRAY_FOREACH( m_pEventLastReport->getHuaInfoList() , obj){
        
        MB_EventHarm  * data =  (MB_EventHarm *)obj;
        xmlNodePtr node;
        node = xmlNewNode(NULL,BAD_CAST "rank");
        xmlAddChild(preReport,node);
        xmlNewProp(node,BAD_CAST "username",BAD_CAST data->getName());
        char datastr[10];
        sprintf(datastr, "%lld",data->getHarm());
        xmlNewProp(node,BAD_CAST "harm",BAD_CAST datastr);
        
    }
    
    CCARRAY_FOREACH( m_pEventLastReport->getLuckyRoleList() , obj){
        
        CCString  * data =  (CCString *)obj;
        xmlNodePtr node;
        node = xmlNewNode(NULL,BAD_CAST "lucky");
        xmlAddChild(preReport,node);
        xmlNewProp(node,BAD_CAST "username",BAD_CAST data->getCString());
        
    }
    int nRel = xmlSaveFormatFileEnc(filename, g_sharedDoc, "UTF-8", 1);
    if (nRel != -1)
    {
        printf("%s被创建，写入%d个字节\n",filename, nRel);
    }
    
    //释放文档内節点動态申請的内存
    xmlFreeDoc(g_sharedDoc);
    
    char filename2[1000];
    sprintf(filename2, "%seventrank%d.cb", CCFileUtils::sharedFileUtils()->getWritablePath().c_str(),m_nEventId);
    MB_Aescypt::encrypt_stream(filename, filename2);
    remove(filename);
    
}
MB_EventMgr* MB_EventMgr::m_pSharedEventMgr = NULL;

MB_EventMgr::MB_EventMgr(){
    
    m_pEvenList = new CCArray();
    MB_EventData * worldboss = new  MB_EventData();
    m_pEvenList->addObject(worldboss);
    worldboss->release();
    worldboss->setEventID(2);
    worldboss->setEventName("火箭队");
    worldboss->loadRank();
    
    m_pIsRocketTeamOnline = false;
    m_pIsNanMOnline = true;
    
    SOCKET_MSG_REGIST(SC_HULA_OPEN,MB_EventMgr);
    SOCKET_MSG_REGIST(SC_HULA_INIT_STATE,MB_EventMgr);
    SOCKET_MSG_REGIST(SC_HULA_BUFF, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_HULA_LAST_INFO_IGNORE, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_HULA_LAST_INFO_WIN, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_HULA_LAST_INFO_FAIL, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_HULA_CUR_INFO, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_HULA_CUR_INFO_IGNORE, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_HULA_HP_SYNC, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_HULA_HARM_BROADCAST, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_HULA_RANK_SYNC, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_HULA_OPEN_TIME,MB_EventMgr);
    SOCKET_MSG_REGIST(SC_HULA_REBORN, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_HULA_OFFLINE_PLAY, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_HULA_BUFF_SYNC,MB_EventMgr);
    
    SOCKET_MSG_REGIST(SC_NANM_OPEN,MB_EventMgr);
    SOCKET_MSG_REGIST(SC_NANM_INIT_STATE,MB_EventMgr);
    SOCKET_MSG_REGIST(SC_NANM_BUFF, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_NANM_LAST_INFO_IGNORE, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_NANM_LAST_INFO_WIN, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_NANM_LAST_INFO_FAIL, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_NANM_CUR_INFO, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_NANM_CUR_INFO_IGNORE, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_NANM_HP_SYNC, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_NANM_HARM_BROADCAST, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_NANM_RANK_SYNC, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_NANM_OPEN_TIME,MB_EventMgr);
    SOCKET_MSG_REGIST(SC_NANM_REBORN, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_NANM_OFFLINE_PLAY, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_NANM_BUFF_SYNC,MB_EventMgr);
    
    SOCKET_MSG_REGIST(SC_HRON_INFO_WAIT, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_HRON_INFO_STOP, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_HRON_INFO_ON, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_HRON_LAST_RANK_LIST, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_HRON_CUR_RANK_LIST, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_HRON_BUY, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_HRON_STOP, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_HRON_OPEN_TIME, MB_EventMgr);
    SOCKET_MSG_REGIST(SC_PUSH_HIGHLIGHT_INFO , MB_EventMgr);
    SOCKET_MSG_REGIST(SC_HRON_SUCC_REWARD, MB_EventMgr);

}
CCArray *MB_EventMgr::getEvenlist(){
    return m_pEvenList;
}
MB_EventMgr::~MB_EventMgr(){
    
    SOCKET_MSG_UNREGIST(SC_HULA_OPEN);
    SOCKET_MSG_UNREGIST(SC_HULA_INIT_STATE);
    SOCKET_MSG_UNREGIST(SC_HULA_BUFF);
    SOCKET_MSG_UNREGIST(SC_HULA_LAST_INFO_IGNORE);
    SOCKET_MSG_UNREGIST(SC_HULA_LAST_INFO_WIN);
    SOCKET_MSG_UNREGIST(SC_HULA_LAST_INFO_FAIL);
    SOCKET_MSG_UNREGIST(SC_HULA_CUR_INFO);
    SOCKET_MSG_UNREGIST(SC_HULA_CUR_INFO_IGNORE);
    SOCKET_MSG_UNREGIST(SC_HULA_HP_SYNC);
    SOCKET_MSG_UNREGIST(SC_HULA_BUFF_SYNC);
    SOCKET_MSG_UNREGIST(SC_HULA_HARM_BROADCAST);
    SOCKET_MSG_UNREGIST(SC_HULA_RANK_SYNC);
    SOCKET_MSG_UNREGIST(SC_HRON_OPEN_TIME);
    SOCKET_MSG_UNREGIST(SC_HULA_OPEN_TIME);
    SOCKET_MSG_UNREGIST(SC_HULA_REBORN);
    SOCKET_MSG_UNREGIST(SC_HULA_OFFLINE_PLAY);
    SOCKET_MSG_UNREGIST(SC_HRON_INFO_WAIT);
    SOCKET_MSG_UNREGIST(SC_HRON_INFO_STOP);
    SOCKET_MSG_UNREGIST(SC_HRON_INFO_ON);
    SOCKET_MSG_UNREGIST(SC_HRON_LAST_RANK_LIST);
    SOCKET_MSG_UNREGIST(SC_HRON_CUR_RANK_LIST);
    SOCKET_MSG_UNREGIST(SC_HRON_BUY);
    SOCKET_MSG_UNREGIST(SC_HRON_STOP);

    
    SOCKET_MSG_UNREGIST(SC_NANM_OPEN);
    SOCKET_MSG_UNREGIST(SC_NANM_INIT_STATE);
    SOCKET_MSG_UNREGIST(SC_NANM_BUFF);
    SOCKET_MSG_UNREGIST(SC_NANM_LAST_INFO_IGNORE);
    SOCKET_MSG_UNREGIST(SC_NANM_LAST_INFO_WIN);
    SOCKET_MSG_UNREGIST(SC_NANM_LAST_INFO_FAIL);
    SOCKET_MSG_UNREGIST(SC_NANM_CUR_INFO);
    SOCKET_MSG_UNREGIST(SC_NANM_CUR_INFO_IGNORE);
    SOCKET_MSG_UNREGIST(SC_NANM_HP_SYNC);
    SOCKET_MSG_UNREGIST(SC_NANM_HARM_BROADCAST);
    SOCKET_MSG_UNREGIST(SC_NANM_RANK_SYNC);
    SOCKET_MSG_UNREGIST(SC_NANM_OPEN_TIME);
    SOCKET_MSG_UNREGIST(SC_NANM_REBORN);
    SOCKET_MSG_UNREGIST(SC_NANM_OFFLINE_PLAY);
    SOCKET_MSG_UNREGIST(SC_NANM_BUFF_SYNC);
    SOCKET_MSG_UNREGIST(SC_PUSH_HIGHLIGHT_INFO);
    SOCKET_MSG_UNREGIST(SC_HRON_SUCC_REWARD);

    CC_SAFE_RELEASE_NULL(m_pEvenList);
    
}
MB_EventMgr * MB_EventMgr::getInstence(){
    
    if(m_pSharedEventMgr == NULL ){
        
        m_pSharedEventMgr = new MB_EventMgr();
    }
    return m_pSharedEventMgr;
}
void MB_EventMgr::destroyInstance(){
    
    if(m_pSharedEventMgr != NULL){
        
        delete m_pSharedEventMgr;
        m_pSharedEventMgr = NULL;
    }
    
}/************************************************/
bool MB_EventMgr::sendworldboss_open_time(){
    
    SOCKET_REQUEST_START(CS_NANM_OPEN_TIME);
    SOCKET_REQUEST_END(SC_NANM_OPEN_TIME, MB_EventMgr::onMsgRecv);
    return true;
    
}
bool MB_EventMgr::recvworldboss_open_time(MB_MsgBuffer *recvPacket){
    MB_EventData * data = (MB_EventData *) m_pEvenList->objectAtIndex(0);
    int time ;
    recvPacket->readU32(&time);
    data->setBeginTime(time);
    return true;
}


bool MB_EventMgr::sendworldboss_open(){
    
    SOCKET_REQUEST_START(CS_NANM_OPEN);
    SOCKET_REQUEST_END(SC_NANM_OPEN, MB_EventMgr::onMsgRecv);
    //可能收不到
    return true;
}

/*
 message recvworldboss_open[id=12402]{
 required	bool		isOpen			=1;//活動是否開始
 required	int64		maxHp			=2;//BOSS最大血量 ++
 required	int16		bossQuality		=3;//BOSS品階
 required	bool		isBuffed		=4;//是否已經擂鼓
 required	int16		buffNum			=5;//擂鼓层數
 required	bool		isOfflinePlay	=6;//是否已經設置离线參与
 required	int32		beginTime		=7;//活動開始時間
 }
 */
bool MB_EventMgr::recvworldboss_open(MB_MsgBuffer* recvPacket){
    MB_EventData * data = (MB_EventData *) m_pEvenList->objectAtIndex(0);
    uint16_t data16;
    uint32_t data32;
    uint64_t data64;
    uint8_t data8;
    recvPacket->readU8(&data8);
    data->setIsOpen(data8==1);
    recvPacket->readU64(&data64);
    data->setMaxHp(data64);
    recvPacket->readU16(&data16);
    data->setbossLevel(data16);
    recvPacket->readU8(&data8);
    data->setIsBuffed(data8==1);
    recvPacket->readU16(&data16);
    data->setBuffNum(data16);
    recvPacket->readU8(&data8);
    data->setIsOfflinePlay(data8 == 1);
    recvPacket->readU32(&data32);
    data->setBeginTime(data32);
    return true;
}

/*
 // 請求sendworldboss_open后，如果當前活動正在進行，则返回下面一条协议
 message	recvworldboss_init_state[id=12403]{
 required	int64		curHp			=1;//BOSS當前血量 ++
 required	int64		curHarm			=2;//當前累积傷害  ++
 required	int32		curRank			=3;//當前排名
 required	int32		rebornTime		=4;//複活時間，當前非倒計時狀態，则此值為0
 }

 */
bool MB_EventMgr::recvworldboss_init_state(MB_MsgBuffer* recvPacket){
    MB_EventData * data = (MB_EventData *) m_pEvenList->objectAtIndex(0);
    uint32_t data32;
    uint64_t data64;
    recvPacket->readU64(&data64);
    data->setCurHp(data64);
    recvPacket->readU64(&data64);
    data->setCurHarm(data64);
    recvPacket->readU32(&data32);
    data->setCurRank(data32);
    recvPacket->readU32(&data32);
    data->setRebornTime(data32);
    return true;
}
bool MB_EventMgr::sendworldboss_offline_play(){
    
//    MB_EventData * data = (MB_EventData *) m_pEvenList->objectAtIndex(2);
//    SOCKET_REQUEST_START(CS_NANM_OFFLINE_PLAY);
//    packet->writeU8(data->getIsOfflinePlay());
//    SOCKET_REQUEST_END(SC_NANM_OFFLINE_PLAY,MB_EventMgr::onMsgRecv);
//    
    return true;
}
bool MB_EventMgr::recvworldboss_offline_play(MB_MsgBuffer *recvPacket){
    
//    int8_t data8;
//    recvPacket->readU8(&data8);
//    if (data8 == 1 ){
//        
//        MB_Message::removeALLMessage();
//        recvPacket->readU8(&data8);
//        MB_EventData * data = (MB_EventData *) m_pEvenList->objectAtIndex(2);
//        data->setIsOfflinePlay(data8 == 1);
//        
//    }else{
//        
//        if (data8 == 2) {
//            
//            MB_Message::sharedMB_Message()->showMessage("失敗","設置以后將不能關閉","確定");
//            
//        }else if (data8 == 3) {
//            
//            MB_Message::sharedMB_Message()->showMessage("失敗","vip等級不足","確定");
//            
//        }else if (data8 == 4) {
//            
//            MB_Message::sharedMB_Message()->showMessage("失敗","寶石不足","確定");
//            
//        }else if (data8 == 5) {
//            
//            MB_Message::sharedMB_Message()->showMessage("失敗","未知錯誤","確定");
//        }
//        
//    }
//    
    return true;
}
bool MB_EventMgr::sendworldboss_close(){
    
    SOCKET_REQUEST_START(CS_NANM_CLOSE);
    SOCKET_REQUEST_END(CS_NANM_CLOSE,MB_EventMgr::onMsgRecv);
    
    return true;
}
bool MB_EventMgr::sendworldboss_buff(int times){
    
    SOCKET_REQUEST_START(CS_NANM_BUFF);
    packet->writeU8(times);
    SOCKET_REQUEST_END(SC_NANM_BUFF,MB_EventMgr::onMsgRecv);
    return true;
    
}
bool MB_EventMgr::recvworldboss_buff(MB_MsgBuffer* recvPacket){
    uint8_t data8;
    recvPacket->readU8(&data8);
    recvPacket->readU8(&data8);
    int result = data8;
    if (result == 1) {
        
        MB_EventData *data =  (MB_EventData *) m_pEvenList->objectAtIndex(0);
        data->setIsBuffed(true);
    }
    
    return true;
}
bool MB_EventMgr::sendworldboss_last_info(){
    
    MB_EventData * data = (MB_EventData *) m_pEvenList->objectAtIndex(0);
    SOCKET_REQUEST_START(CS_NANM_LAST_INFO);
    packet->writeU32(data->getCurSaveInfoID());
    SOCKET_REQUEST_END(SC_NANM_LAST_INFO_WIN,MB_EventMgr::onMsgRecv);
    return true;
    
}
bool MB_EventMgr::recvworldboss_last_info_ignore(MB_MsgBuffer* recvPacket){
    
    return true;
    
}

/*
 // 告诉客户端，前回戰報勝利，和具体信息
 message recvworldboss_last_info_win[id=12413]{
 required	int16		bossQuality		=1;//BOSS品階
 required	int32		intervalSec		=2;//总共消耗的秒數
 required	int64		bossMaxHp		=3;//BOSS总血量  ++
 repeated	p_worldboss_info	worldbossInfolist	=4;//依次對应最后一擊玩家、贡献第一玩家、贡献第二玩家、贡献第三玩家的信息
 repeated	string		luckyRoleList	=5;//獲得幸运獎勵的玩家
 }

 */
bool MB_EventMgr::recvworldboss_last_info_win(MB_MsgBuffer* recvPacket){
    MB_EventData * data = (MB_EventData *) m_pEvenList->objectAtIndex(0);
    uint16_t data16;
    uint32_t data32;
    uint64_t data64;
    
    recvPacket->readU16(&data16);
    data->getEventLastReport()->setBossLevel(data16);
    recvPacket->readU32(&data32);
    data->getEventLastReport()->setInterValSec(data32);
    recvPacket->readU64(&data64);
    data->getEventLastReport()->setBossMaxHp(data64);
    recvPacket->readU16(&data16);
    int halainfolength = data16;
    data->getEventLastReport()->getLuckyRoleList()->removeAllObjects();
    data->getEventLastReport()->getHuaInfoList()->removeAllObjects();
    for (int i = 0 ; i< halainfolength; i++) {
        
        MB_EventHarm *harmData = new MB_EventHarm();
        char *str = recvPacket->ReadString();
        if(str)harmData->setName(str);
        CC_SAFE_FREE(str);
        recvPacket->readU64(&data64);
        harmData->setHarm(data64);
        data->getEventLastReport()->getHuaInfoList()->addObject(harmData);
        harmData->release();
    }
    recvPacket->readU16(&data16);
    int luckylength = data16;
    for (int i = 0 ; i< luckylength; i++) {
        
        char * strbuf = recvPacket->ReadString();
        CCString *str =  CCString::create(strbuf?strbuf:"");
        CC_SAFE_FREE(strbuf);
        data->getEventLastReport()->getLuckyRoleList()->addObject(str);
    }
    data->saveRank();
    
    return true;
    
}
bool MB_EventMgr::recvworldboss_last_info_fail(MB_MsgBuffer* recvPacket){
    MB_EventData * data = (MB_EventData *) m_pEvenList->objectAtIndex(0);
    uint16_t data16;
    uint32_t data32;
    recvPacket->readU16(&data16);
    data->getEventLastReport()->setBossLevel(data16);
    recvPacket->readU32(&data32);
    data->getEventLastReport()->setInterValSec(data32);
    recvPacket->readU32(&data32);
    data->getEventLastReport()->getLuckyRoleList()->removeAllObjects();
    data->getEventLastReport()->getHuaInfoList()->removeAllObjects();
    data->saveRank();
    
    return true;
    
}
bool MB_EventMgr::sendworldboss_cur_info(){
    
    
    SOCKET_REQUEST_START(CS_NANM_CUR_INFO);
    SOCKET_REQUEST_END(SC_NANM_CUR_INFO,MB_EventMgr::onMsgRecv);
    
    return true;
}
bool MB_EventMgr::recvworldboss_cur_info_ignore(MB_MsgBuffer* recvPacket){
    
    return true;
}

/*
 message recvworldboss_cur_info[id=12418]{
 repeated	p_worldboss_info	worldbossInfoList	=1;//排行榜的玩家信息
 }

 */
bool MB_EventMgr::recvworldboss_cur_info(MB_MsgBuffer* recvPacket){
    
    MB_EventData * data = (MB_EventData *) m_pEvenList->objectAtIndex(0);
    data->getHarmList()->removeAllObjects();
    uint16_t data16;
    uint64_t data64;
    recvPacket->readU16(&data16);
    for(int i = 0 ; i < data16 ; i++){
        
        MB_EventHarm *harmData = new MB_EventHarm();
        char *str =recvPacket->ReadString();
        if(str)harmData->setName(str);
        CC_SAFE_FREE(str);
        recvPacket->readU64(&data64);
        harmData->setHarm(data64);
        data->getHarmList()->addObject(harmData);
        harmData->release();
    }
    
    return true;
}
bool MB_EventMgr::recvworldboss_hp_sync(MB_MsgBuffer* recvPacket){
    
    MB_EventData * data = (MB_EventData *) m_pEvenList->objectAtIndex(0);
    uint64_t data64;
    recvPacket->readU64(&data64);
    data->setCurHp(data64);
    return true;
    
}
bool MB_EventMgr::recvworldboss_harm_broadcast(MB_MsgBuffer* recvPacket){
    
    return true;
    
}
bool MB_EventMgr::recvworldboss_rank_sync(MB_MsgBuffer* recvPacket){
    
    MB_EventData * data = (MB_EventData *) m_pEvenList->objectAtIndex(0);
    uint16_t data16;
    recvPacket->readU16(&data16);
    data->setCurRank(data16);
    
    return true;
}
bool MB_EventMgr::recvworldboss_buff_sync(MB_MsgBuffer* recvPacket){
    
    MB_EventData * data = (MB_EventData *) m_pEvenList->objectAtIndex(0);
    uint16_t  data16;
    recvPacket->readU16(&data16);
    data->setBuffNum(data16);
    return true;
    
}
bool MB_EventMgr::sendworldboss_fight(){
    
    SOCKET_REQUEST_START(CS_NANM_FIGHT);
    SOCKET_REQUEST_END(SC_NANM_FIGHT,MB_EventMgr::onMsgRecv);
    return true;
}
bool MB_EventMgr::recvworldboss_fight(MB_MsgBuffer* recvPacket){
    
    return true;
}
bool MB_EventMgr::sendworldboss_reborn(){
    
    SOCKET_REQUEST_START(CS_NANM_REBORN);
    SOCKET_REQUEST_END(SC_NANM_REBORN,MB_EventMgr::onMsgRecv);
    return true;
}
bool MB_EventMgr::recvworldboss_reborn(MB_MsgBuffer *recvPacket){
    
    int8_t result;
    recvPacket->readU8(&result);
    MB_LOG("recvworldboss_reborn %d",result);
    if(result == 1){
        
        MB_EventData * data = (MB_EventData *) m_pEvenList->objectAtIndex(0);
        data->setRebornTime(0);
    }
    return true;
}
/************************************************/
void MB_EventMgr::onMsgRecv(CCNode* node, SocketResponse* response){
    
    assert(response != NULL);
    
    //將socket數据读取到序列化結构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议號
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg) {
        case SC_NANM_OPEN:
            recvworldboss_open(recvPacket);
            break;
        case SC_NANM_INIT_STATE:
            recvworldboss_init_state(recvPacket);
            break;
        case SC_NANM_BUFF:
            recvworldboss_buff(recvPacket);
            break;
        case SC_NANM_LAST_INFO_IGNORE:
            recvworldboss_last_info_ignore(recvPacket);
            break;
        case SC_NANM_LAST_INFO_WIN:
            recvworldboss_last_info_win(recvPacket);
            break;
        case SC_NANM_LAST_INFO_FAIL:
            recvworldboss_last_info_fail(recvPacket);
            break;
        case SC_NANM_CUR_INFO:
            recvworldboss_cur_info(recvPacket);
            break;
        case SC_NANM_CUR_INFO_IGNORE:
            recvworldboss_cur_info_ignore(recvPacket);
            break;
        case SC_NANM_HP_SYNC:
            recvworldboss_hp_sync(recvPacket);
            break;
        case SC_NANM_BUFF_SYNC:
            recvworldboss_buff_sync(recvPacket);
            break;
        case SC_NANM_HARM_BROADCAST:
            recvworldboss_harm_broadcast(recvPacket);
            break;
        case SC_NANM_RANK_SYNC:
            recvworldboss_rank_sync(recvPacket);
            break;
        case SC_NANM_STOP:
            CCUserDefault::sharedUserDefault()->setBoolForKey("autoworldboss",false);
            break;
        case SC_NANM_REBORN:
            recvworldboss_reborn(recvPacket);
            break;
        case SC_NANM_OFFLINE_PLAY:
            recvworldboss_offline_play(recvPacket);
            break;
        case SC_NANM_OPEN_TIME:
            recvworldboss_open_time(recvPacket);
            break;
        case SC_PUSH_HIGHLIGHT_INFO:{
            
            uint8_t data8;
            recvPacket->readU8(&data8);
            if(data8 == 1){
            
                recvPacket->readU8(&data8);
                m_pIsRocketTeamOnline = (data8 == 1);
                
            }else if(data8 == 2){
                
                recvPacket->readU8(&data8);
                m_pIsNanMOnline = (data8 ==1);
            }
            break;
        }
        default:
            break;
    }
}
void MB_EventMgr::saveEvent(){
    
    CCObject *obj;
    CCARRAY_FOREACH(m_pEvenList, obj){
        
        if(dynamic_cast<MB_EventData *>(obj)!=NULL){
            
            MB_EventData *data = (MB_EventData *)obj;
            data->saveRank();
        }
    }
}

/*
 <?xml version="1.0" encoding="UTF-8"?>
 <ChapterPages>
 <Page id="" name="" description="" >
 <chapter id="1001" name="妖精世界"  description=""  activateIcon="ico_chaptertype_1.png" disableIcon="" activeneedlevel="1"  activeneedpass="0" location="100,100" >
 <rewards>
 <reward id="" type="" value=""/>
 <rewards>
 </chapter>
 </Page>
 </ChapterPages>
 */
#include "MB_ChapterData.h"
#include "../Common/GameLib/CCGameLib.h"

bool MB_RewardData::init(MB_XmlNode *pNode)
{
    if (pNode == NULL)
    {
        return false;
    }
    
    m_nTypeId = pNode->queryAttributeByName("id")->intValue();
    m_nType = pNode->queryAttributeByName("type")->intValue();
    m_nValue = pNode->queryAttributeByName("value")->intValue();
    
    return true;
}

CCArray* MB_ChapterData::getRewardArray()const
{
    return m_pRewardArray;
}

MB_ChapterData::MB_ChapterData()
{
    m_pRewardArray = new CCArray;
}

MB_ChapterData::~MB_ChapterData()
{
    CC_SAFE_RELEASE_NULL(m_pRewardArray);
}

bool MB_ChapterData::init(MB_XmlNode *pNode)
{
    if (pNode == NULL)
    {
        return false;
    }
    
    m_nChapterId = pNode->queryAttributeByName("id")->intValue();
    m_szName = pNode->queryAttributeByName("name")->getCString();
    m_szDescription = pNode->queryAttributeByName("description")->getCString();
    m_szActovateIcon = pNode->queryAttributeByName("activateIcon")->getCString();
    m_szDisableIcon = pNode->queryAttributeByName("disableIcon")->getCString();
    m_nNeedLevel = pNode->queryAttributeByName("activeneedlevel")->intValue();
    m_nNeedPass = pNode->queryAttributeByName("activeneedpass")->intValue();
    
    int location[2] = {};
    uint16_t real_count = 0;
    const char* pLocation = pNode->queryAttributeByName("location")->getCString();
    NSGameHelper::resolvIntValueFromString(pLocation, location, real_count, 2);
    m_location.x = location[0];
    m_location.y = location[1];
    
    CCArray* pArray = CCArray::create();
    MB_XmlNode* pTemp = NULL;
    MB_RewardData* pData = NULL;
    
    if(pNode->queryNodesByName("rewards|reward", pArray))
    {
        m_pRewardArray->removeAllObjects();
        CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pTemp)
        {
            pData = new MB_RewardData;
            if (pData->init(pTemp))
            {
                m_pRewardArray->addObject(pData);
            }
            CC_SAFE_RELEASE_NULL(pData);
        }
    }
    
    return true;
}

MB_ChapterPage::MB_ChapterPage()
{
    m_pChapterArray = new CCArray;
}

MB_ChapterPage::~MB_ChapterPage()
{
    CC_SAFE_RELEASE_NULL(m_pChapterArray);
}

bool MB_ChapterPage::hasChapter(int nChapterId)
{
    MB_ChapterData* pChapterData = NULL;
    CCARRAY_FOREACH_4TYPE(m_pChapterArray, MB_ChapterData*, pChapterData)
    {
        if (pChapterData->getChapterId() == nChapterId)
        {
            return true;
        }
    }
    
    return false;
}

void MB_ChapterPage::loadResource2SpriteCache()
{
    if (!m_szResource.empty())
    {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(m_szResource.c_str());
        //        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pic_index_func.plist");
    }
}
void MB_ChapterPage::removeResourceFromSpriteCache()
{
    if (!m_szResource.empty())
    {
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(m_szResource.c_str());
    }
}

bool MB_ChapterPage::init(MB_XmlNode *pNode)
{
    if (pNode == NULL)
    {
        return false;
    }
    
    m_nId = pNode->queryAttributeByName("id")->intValue();
    m_szName = pNode->queryAttributeByName("name")->getCString();
    m_szDescription = pNode->queryAttributeByName("description")->getCString();
    m_szBackground = pNode->queryAttributeByName("bg")->getCString();
    m_szBattleBg = pNode->queryAttributeByName("battlebg")->getCString();
    m_szResource = pNode->queryAttributeByName("Resource")->getCString();
    //    loadResource2SpriteCache();
    
    CCArray* pArray = CCArray::create();
    MB_XmlNode* pTemp = NULL;
    MB_ChapterData* pData = NULL;
    
    if(pNode->queryNodesByName("chapter", pArray))
    {
        m_pChapterArray->removeAllObjects();
        CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pTemp)
        {
            pData = new MB_ChapterData;
            if (pData->init(pTemp))
            {
                m_pChapterArray->addObject(pData);
            }
            CC_SAFE_RELEASE_NULL(pData);
        }
    }
    return true;
}

const char* MB_ChapterPage::getChapterName(uint16_t nChapterID)
{
    MB_ChapterData* pData = NULL;
    
    if(queryChapterById(nChapterID, &pData))
    {
        return pData->getName().c_str();
    }
    
    return "";
}

bool MB_ChapterPage::queryChapterById(int nChapterId,MB_ChapterData** pData)
{
    MB_ChapterData* pTempData = NULL;
    
    CCARRAY_FOREACH_4TYPE(m_pChapterArray, MB_ChapterData*, pTempData)
    {
        if (pTempData->getChapterId() == nChapterId)
        {
            *pData = pTempData;
            return true;
        }
    }
    
    return false;
}

MB_ChapterPageList::MB_ChapterPageList()
{
    m_pPageList = new CCArray;
}

MB_ChapterPageList::~MB_ChapterPageList()
{
    CC_SAFE_RELEASE_NULL(m_pPageList);
}

bool MB_ChapterPageList::init(MB_XmlNode *pNode)
{
    if (pNode == NULL)return false;
    
    CCArray* pArray = CCArray::create();
    MB_XmlNode* pTemp = NULL;
    MB_ChapterPage* pPage = NULL;
    pNode->print();
    if(pNode->queryNodesByName("Page", pArray))
    {
        m_pPageList->removeAllObjects();
        CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pTemp)
        {
            pPage = new MB_ChapterPage;
            if (pPage->init(pTemp))
            {
                m_pPageList->addObject(pPage);
            }
            CC_SAFE_RELEASE_NULL(pPage);
        }
    }
    
    return true;
}

bool MB_ChapterPageList::queryPageById(int nPageId,MB_ChapterPage** pPage)
{
    MB_ChapterPage* pPageTemp = NULL;
    
    CCARRAY_FOREACH_4TYPE(m_pPageList, MB_ChapterPage*, pPageTemp)
    {
        if (pPageTemp->getPageId() == nPageId)
        {
            *pPage = pPageTemp;
            return true;
        }
    }
    return false;
}

bool MB_ChapterPageList::queryPageByChapterId(int nChapterId,MB_ChapterPage** pPage)
{
    MB_ChapterPage* pPageTemp = NULL;
    
    CCARRAY_FOREACH_4TYPE(m_pPageList, MB_ChapterPage*, pPageTemp)
    {
        if (pPageTemp->hasChapter(nChapterId))
        {
            *pPage = pPageTemp;
            return true;
        }
    }
    
    return false;
}

bool MB_ChapterPageList::queryChapterByID(int nChapterId,MB_ChapterData** pData)
{
    MB_ChapterPage* pPageTemp = NULL;
    CCARRAY_FOREACH_4TYPE(m_pPageList, MB_ChapterPage*, pPageTemp)
    {
        if (pPageTemp->queryChapterById(nChapterId, pData))
        {
            return true;
        }
    }
    return false;
}

MB_ChapterRankData::MB_ChapterRankData()
{
}
bool MB_ChapterRankData::read(MB_MsgBuffer* recvPacket)
{
    recvPacket->readU8(&m_nRank);
    recvPacket->readU32(&m_nRoleID);
    
    recvPacket->readU16(&m_nLv);
    
    char* pString = recvPacket->ReadString();
    if (pString)
    {
        m_szName = pString;
        CC_SAFE_FREE(pString);
    }
    recvPacket->readU32(&m_nHead);
    recvPacket->readU8(&m_nTitle);
    recvPacket->readU8(&m_bIsMale);
    
    char* pString2 = recvPacket->ReadString();
    if (pString2)
    {
        m_szDungeonName = pString2;
        CC_SAFE_FREE(pString2);
    }
    return true;
}

