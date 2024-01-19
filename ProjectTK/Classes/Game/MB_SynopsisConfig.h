//
//  MB_SynopsisConfig.h
//  ProjectPM
//
//  Created by cri-mac on 14-5-14.
//
//

#ifndef __ProjectMB__MB_SynopsisConfig__
#define __ProjectMB__MB_SynopsisConfig__
#include "cocos2d.h"
#include "MB_ClientData.h"
#include <string>
USING_NS_CC;

class MB_XmlNode;

class MB_Plot:public MB_ClientData
{
public:
    static MB_Plot* create(MB_XmlNode* pNode);
    bool init(MB_XmlNode* pNode);
private:
    CC_SYNTHESIZE_READONLY(std::string, m_szHeadIcon, HeadIcon);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nHeadPos, HeadPos);
    CC_SYNTHESIZE_READONLY(std::string, m_szSound, Sound);
    CC_SYNTHESIZE_READONLY(std::string, m_szText, Text);
};

class MB_SynopsisItem:public MB_ClientData
{
    MB_SynopsisItem();
public:
    virtual ~MB_SynopsisItem();
    static MB_SynopsisItem* create(MB_XmlNode* pNode);
    bool init(MB_XmlNode* pNode);
private:
    CC_SYNTHESIZE_READONLY(int, m_nCondition,Condition);
    CC_SYNTHESIZE_READONLY(int, m_nDungeonID,DungeonID);
    CC_SYNTHESIZE_READONLY(CCArray*, m_Plots, Plots);
};

class MB_LayerStoryPlayer;
class MB_SynopsisConfig
{
public:
    virtual ~MB_SynopsisConfig();
    static MB_SynopsisConfig* getInstance();
    static void destroyInstance();
    
    MB_SynopsisItem* querySynopsisItem(int nDungeonID,int nCondition);          //nDungeonID 关卡ID nCondition条件 1首次进入 2首次通关
    bool querySynopsisItem(int nDungeonID,int nCondition,CCArray** outSynopsis);
    MB_LayerStoryPlayer* createBattlePlotByID(uint16_t nActionId);
protected:
    MB_SynopsisItem* queryBattlePlotItem(int nActionID);
protected:
    virtual bool init();
private:
    MB_SynopsisConfig();
    std::string         m_pResource;
    static MB_SynopsisConfig* m_pSingletonInstance;
    CCArray*            m_pSynopsis;
    CCArray*            m_pBattlePlots;
};




#endif /* defined(__ProjectMB__MB_SynopsisConfig__) */
