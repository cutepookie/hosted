//
//  CCGameHelper.h
//  ProjectSDS
//
//  Created by crimoon00007 on 14-3-4.
//
//

#ifndef __ProjectSDS__CCGameHelper__
#define __ProjectSDS__CCGameHelper__

#include "Game.h"

namespace NSGameHelper
{
    
    bool getRoleNameWithLocation(std::string& result);
    
    void GotoCreateRole();
   
    enum SdkSrcType
    {
        ACCOUNT_TYPE_NORMAL = 0,
		ACCOUNT_TYPE_YJ,
    };

    int getSrcType();

    void setControlButtonTitleAllState(CCControlButton* pButton,const char* pTitle);
    void setControlButtonTitleBMFontAllState(CCControlButton* pButton,const char* fntFile);
    void setControlButtonTitleBMFontScale(CCControlButton* pButton,float sx,float sy);
    void setMenuItemImage4AllState(CCMenuItemImage* pItemImage,const char* pFile);
    void setQualityColor(CCNodeRGBA* pDest,int star); // this function used only for ProjectTK
    CCSpriteFrame* createSpriteFrame(const char* pFile);
    void setSpriteFrameWithFrameCache(CCSprite* pSprite,const char* pFile);
    void setSpriteFrame(CCSprite* pSprite,const char* pFile);

    CCLayer* createDisableTouchLayer();
    CCLayer* createDisableTouchLayer1();
    CCLayer* createDisableTouchLayer12();
    const char*  formatTimeStringDHM(int iLeftTime );
    const char*  formatTimeStringDHMS(int iLeftTime );
    const char*  formatTimeStringHMS(int iLeftTime );
    const char*  formatTimeStringHMS_colon(int iLeftTime );
    const char*  getDataTimeByUnixStamp(uint32_t t);
    
    void setQualityFrameByStar(CCSprite* pSprite,int star);
    //void setMonsterIcon(CCSprite* pSprite,uint16_t tid,int rank);
    void setRankFrame(CCSprite* pSprite,int start,int rank);
    // 只针對头像
    void setColorByStar(CCNodeRGBA* pDest,int star);
    void setHeadFrame(CCSprite* pSprite,int star,int type,int rank = 0,bool bCircle = true);
    
    //根据品階獲取头像特效
    void getHeadEffectsByRank(CCSprite* node,int rank);
    
    //头像
    bool setItemIconDetailByUid(uint64_t uid,CCSprite* pIcon,CCLabelTTF* pName=NULL,CCSprite* pFrame=NULL,bool bCircle = false);
    bool setItemIconDetailByTid(uint16_t tid,uint16_t rank,CCSprite* pIcon,CCLabelTTF* pName=NULL,CCSprite* pFrame=NULL,bool bCircle = false);
    
    bool setItemIconDetailByUid2(uint64_t uid,CCSprite* pIcon,CCLabelTTF* pName=NULL,CCControlButton* pFrame=NULL,bool bCircle = false);
    bool setItemIconDetailByTid2(uint16_t tid,uint16_t rank,CCSprite* pIcon,CCLabelTTF* pName=NULL,CCControlButton* pFrame=NULL,bool bCircle = false);
    
    bool setMonsterIconDetailByUid2(uint64_t uid,CCSprite* pIcon,CCLabelTTF* pName=NULL,CCControlButton* pFrame=NULL,bool bCircle = false);
    bool setMonsterIconDetailByTid2(uint16_t tid,uint16_t rank,CCSprite* pIcon,CCLabelTTF* pName=NULL,CCControlButton* pFrame=NULL,bool bCircle = false);
    bool setMonsterIconDetailByUid(uint64_t uid,CCSprite* pIcon,CCLabelTTF* pName=NULL,CCSprite* pFrame=NULL,bool bCircle = false);
    bool setMonsterIconDetailByTid(uint16_t tid,uint16_t rank,CCSprite* pIcon,CCLabelTTF* pName=NULL,CCSprite* pFrame=NULL,bool bCircle = false);
    bool setMonsterIconDetailWithStarByTid(uint16_t tid,uint16_t rank,CCSprite* pIcon,CCLabelTTF* pName=NULL,CCSprite* pFrame=NULL, CCNode* pStart = NULL,bool bCircle = false);
    //卡牌
    bool setItemCardDetailByUid(uint64_t uid,CCSprite* pIcon,CCLabelTTF* pName=NULL,CCSprite* pStarFrame=NULL,CCSprite* pQualityFrame=NULL);
    bool setItemCardDetailByTid(uint16_t tid,uint16_t rank,CCSprite* pIcon,CCLabelTTF* pName=NULL,CCSprite* pStarFrame=NULL,CCSprite* pQualityFrame=NULL);
    
    bool setMonsterCardDetailByUid(uint64_t uid,CCSprite* pIcon,CCLabelTTF* pName=NULL,CCSprite* pStarFrame=NULL,CCSprite* pQualityFrame=NULL);
    bool setMonsterCardDetailByTid(uint16_t tid,uint16_t rank,CCSprite* pIcon,CCLabelTTF* pName=NULL,CCSprite* pStarFrame=NULL,CCSprite* pQualityFrame=NULL);
    
    int getShapeTypeByRank(int rank);
    
    //检查是否經驗卡牌  是返回true，不是返回false
    bool checkIsExperienceCard(uint16_t tID);
    bool checkIsExperienceCard(uint64_t uID);
    
    //检查是否守護精靈
    bool checkIsGuardPet(uint64_t uid);
    bool checkIsGuardPetType(uint16_t tid);
    
    const ccColor3B& getCorlorByShape(uint16_t nShape);

    bool resolvIntValueFromString(const char* pStr,int* pArray,uint16_t& realCount,uint16_t count);
    bool resolvInt16ValueFromString(const char* pStr,uint16_t* pArray,uint16_t& realCount,uint16_t count);

    bool getActivatedSuitPartsByPetPos(uint16_t* result,uint16_t count,uint16_t& realCount,uint16_t petPos,int nSuitID);
    bool getSuitItemsWithTeamDataStruct(TeamDataStruct* ts,int nSuitID,int16_t nCount,uint16_t& nRealCount,uint16_t* result);
    
    // Compose unity
    bool getItemMaterialComplateStatus(uint16_t nComposeID);
    bool getPetMaterialComplateStatus(uint16_t nComposeID);
    // item
    const int filter_used = 1;
    const int filter_unused = 2;
    const int filter_ignore = -1;
    bool getEquipItemsFromItemMgrByTid(std::vector<uint64_t>& vUid,uint16_t tid,int filter=filter_ignore);
    bool getEquipItemsFromItemMgrByStar(std::vector<uint64_t>& vUid,uint16_t star,int filter=filter_ignore);
    bool getAllEquipItemsFromItemMgr(std::vector<uint64_t>& vUid,uint16_t maxStar,int filter=filter_ignore);
    bool getMonstersFromPetMgrByTid(std::vector<uint64_t>& vUid,uint16_t tid,int filter=filter_ignore);
    bool getMonstersFromPetMgrByStar(std::vector<uint64_t>& vUid,uint16_t star,int filter=filter_ignore);
    bool getAllMonstersUidFromPetMgr(std::vector<uint64_t>& vUid,uint16_t maxStar,int filter=filter_ignore);
    bool getAllValideMonstersUidFromPetMgr(std::vector<uint64_t>& vUid);
    
    //金幣≥10万的時候，显示為xxx万：xxx取整 >=1亿 显示亿
    bool LabelFormatNumber(CCLabelProtocol* label,uint64_t value,bool showTitle = false,const char* title = "金币：");
    bool FormatNumber(char* strNumber,uint64_t value,bool showTitle = false,const char* title = "金币：");
    int FormatNumber2(char* strNumber,uint64_t value,bool showTitle = false,const char* title = "金币：");
    
    bool AutoScale9Sprite(CCScale9Sprite* sp);
    bool PreProcessNode(CCNode* pNode,const char* pName);
    bool adjustScrollNode(CCNode* pNode);
    
    bool petHasEquipThisItem(uint64_t petId,uint16_t nTypeId);
    
    void centerStars(CCSprite* pStars[],uint8_t nCount,uint8_t nShowCount);
    
    void getItemUseByType(uint8_t type,std::vector<uint64_t>& vContainer);
    void getOtherItemByTypeID(uint16_t tid,std::vector<uint64_t>& vContainer);
    
    void convertToRbfString(std::string& str);
    
    bool mailRewardConvert2ValueTemplateArray(sMailReward* pMail,CCArray* pArray);
    
    bool setRoleIcon(CCSprite* pIcon,bool bMail,uint32_t nHeadID,uint8_t title,CCSprite *pIconFrame = NULL);
    
    std::string convertDeltaTime2Data(int deltaTime);
    std::string convertDeltaTime2String(int deltaTime);
    //粒子特效控制
//    void stopAllParticle(CCParticleSystemQuad* particle);
//    void BeginAllParticle(CCParticleSystemQuad* particle);
    
    void reloadDataWithNoMove(CCTableView* pView);
    
    CCNode* createRichBox(const std::string& szContent,const CCSize& sz,bool bLockHeight);
    CCNode* createLabelText(const std::string& szContent,const CCSize& sz);
    
    bool safeContentChect(const std::string& constent);
    
    std::vector<std::string> splitEx(const std::string& src, std::string separate_character);
    

    CCRenderTexture* creatMaskSprite(CCSprite* pFlower,CCSprite* pMask = NULL,bool bUse = false);
    
    CCProgressTimer* makeProgressBar(CCSprite* pTexture);
    
    int getServerByRoleID(uint32_t uid);
    
    void runMoveAndOptAction(CCNode* node,float delayTime,float moveTime,bool isDoMove,bool isContainsChild);
    void runOptActionIn(CCNode* node,float fadeTime,bool isContainsChild);
    void runOptActionOut(CCNode* node,float fadeTime,bool isContainsChild);
    void setColorGray(CCSprite* spr,bool isGray);
    
    int get_length(int x);
    
    void setAllOpacity(CCNode* node,int o);
    
    void changeParent(CCNode* parent,CCNode* child);
    
    void setStar(CCSprite ** Stars, uint8_t star);
    
    void setBtnFrame(CCControlButton* btn, const char* atlasName,const char* frameName1);
    void setBtnFrame(CCControlButton* btn, const char* atlasName,const char* frameName1,const char* frameName2,const char* frameName3);
    CCLayer* createDisableTouchLayerAll();
    bool isOneDay();
}

#endif /* defined(__ProjectSDS__CCGameHelper__) */








