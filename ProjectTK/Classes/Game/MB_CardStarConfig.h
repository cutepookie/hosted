//
//  MB_CardStarConfig.h
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-13.
//
//

#ifndef __ProjectMB__MB_CardStarConfig__
#define __ProjectMB__MB_CardStarConfig__

#include "Game.h"


/***********************************************
 <Property>
 <item star="1" cardFrame="pic_monster_0.png" 
 MonsterHeadFrame ="icon_monster_0.png"
 ItemHeadFrame = "icon_item_0.png"
 rankFrame1="" rankFrame2="" rankFrame3="" />
 </Property>
 ***********************************************/
enum {
    MONSTER_HEADFRAME = 0,
    ITEM_HEADFRAME 
};
class MB_XmlNode;
class MB_CardProperty:public CCObject
{
public:
    MB_CardProperty();
    bool init(MB_XmlNode* pXmlNode);
    int getCardStar()const{return m_nStar;};
    const ccColor3B& getHeadFrameColor()const{return m_headFrameColor;}
    const char* getCardFrame()const{return m_cardFrame.c_str();}
    const char* getRankFrameByRank(uint16_t rank)const;
    //Monster tpye=0,Item type=1
    const char* getHeadFrame(uint8_t type)const;
    const char* getHeadCircleFrame(uint8_t type)const;
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(std::string, m_szPetCircleFrame, PetCircleFrame);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(std::string, m_szItemCircleFrame, ItemCircleFrame);
    
private:
    int m_nStar;
    ccColor3B m_headFrameColor;
    std::string m_cardFrame;
    std::string m_RankFrame[3];
    std::string m_HeadFrame[2];

};

class MB_CardPropertyMgr:public CCObject
{
public:
    static MB_CardPropertyMgr* getInstance();
    static void destroyInstance();
    const MB_CardProperty* getCardPropertyByStar(int star);
    CCNode* creatEffectByRank(uint16_t rank);
protected:
    bool init();
private:
    MB_CardPropertyMgr();
    ~MB_CardPropertyMgr();
    static MB_CardPropertyMgr* m_pSingletonInstance;
    CCArray*            m_pContainer;
};
#endif /* defined(__ProjectMB__MB_CardStarConfig__) */
