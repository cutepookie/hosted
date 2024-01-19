//
//  MB_AbsolvedConfigure.h
//  ProjectPM
//
//  Created by WenYong on 14-4-15.
//
//

#ifndef __ProjectMB__MB_AbsolvedConfigure__
#define __ProjectMB__MB_AbsolvedConfigure__

#include "cocos2d.h"
USING_NS_CC;

class MB_DungeonData;
class MB_ChapterPageList;
class MB_ChapterPage;
class MB_ChapterData;
class MB_ChapterInterface;
enum ChapterDifficulty
{
    kChapterDifficultyNormal = 1,
    kChapterDifficultyHard   = 2,
    kChapterDifficultyGod    = 3,
};

class MB_ChapterDungeonData:public CCObject
{
public:
    MB_ChapterDungeonData(uint16_t nId);
    ~MB_ChapterDungeonData();
    const MB_DungeonData* getDungeonDataByID(uint16_t nID);
    MB_DungeonData* cloneDungeonData(uint16_t nID);
    bool loadChapter();
private:
    CC_SYNTHESIZE_READONLY (uint16_t, m_nChapterId, ChapterId);
    CCArray*    m_pDungeonData;
};

class MB_AbsolvedConfigure
{
public:
    virtual ~MB_AbsolvedConfigure();
    static MB_AbsolvedConfigure* getInstance();
    static void destroyInstance();
    virtual bool init();
    static bool readPageList(const char* pFile,MB_ChapterPageList** pPageList);
    static bool queryChapterPageById(MB_ChapterPageList* pPageList,int nPageId,MB_ChapterPage** pPage);
    bool queryChapterPage(int nType, int nPageId,MB_ChapterPage** pPage);
    bool queryChapterData(int nType, int nPageId,int nChapterId,MB_ChapterData** pData);
    bool queryChapterDataByID(int nChapterId,MB_ChapterData** pData);
    bool queryPageByTypeAndChapterId(int nType,int nChapterId,MB_ChapterPage** pPage);
    bool goChapter(int nType,int nPage,int nChapterID);
    bool queryChapterInterface(int nType,int nPage,int nChapterID,MB_ChapterInterface** pInterface);
    bool chapterInPage(int nType,int nPage,int nChapter);
    bool chapterExist(int nType,int nChapter);
    MB_ChapterDungeonData* getChapterDungeonsID(uint16_t nChapterId);
    const MB_DungeonData* getChapterDungeonDataById(uint16_t nChapterId,uint16_t nDungeonId);
    MB_ChapterDungeonData* createChapterDungeonsByID(uint16_t nChapterId);
    MB_ChapterData* getChapterDataById(uint16_t cid,int type);
protected:
    MB_ChapterInterface* createChapterInterface(int nType,int nPage,int nChapterID);
private:
    MB_AbsolvedConfigure();
    static MB_AbsolvedConfigure* m_pSingtonInstance;
    MB_ChapterPageList*     m_pChapterPageList[3];
    CCArray*                m_pChapterInterfaces;
    CCArray*                m_pChapterArray;
};
#endif /* defined(__ProjectMB__MB_AbsolvedConfigure__) */
