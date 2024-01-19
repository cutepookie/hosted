
#ifndef __ProjectMB__MB_PetData__
#define __ProjectMB__MB_PetData__

#include "Game.h"


#define MAXLEVEL 240;
//精灵模板类
class MB_PetTemplate : public CCObject
{
    
public:
    
    MB_PetTemplate();
    ~MB_PetTemplate();
    //模板属性
    CC_SYNTHESIZE(uint16_t, m_uPetTypeID, PetTypeID);
    CC_SYNTHESIZE(uint8_t,m_uPetStar ,PetStar);
    CC_SYNTHESIZE(uint8_t,m_uPetKingdom ,PetKingdom);
    CC_SYNTHESIZE(int ,m_iPetCost,PetCost);
    CC_SYNTHESIZE(uint32_t, m_uPetAttack,PetAttack);
    CC_SYNTHESIZE(uint32_t, m_uPetHpMax,PetHpMax);
    CC_SYNTHESIZE(uint16_t, m_uRankGodID, RankGodID);
    CC_SYNTHESIZE(uint16_t, m_uRankSaintID, RankSaintID);
    
    const char * getPetName();
    //一个ID三个形态要对应三个名字
    const char * getPetName(uint16_t shape);
    void setPetName(const char*);
    void setPetName2(const char*);
    void setPetName3(const char*);
    
    const char * getPetFace();
    //一个ID三个形态要对应三个头像
    const char * getPetFace(uint16_t shape);
    void setPetFace(const char*);
    void setPetFace2(const char*);
    void setPetFace3(const char*);
    
    const char * getPetCard();
    const char * getBattleCard();
    //一个ID三个形态要对应三个卡牌
    const char * getPetCard(uint16_t shape);
    
    void setBattleCard(const char*);
    void setPetCard(const char*);
    void setPetCard2(const char*);
    void setPetCard3(const char*);
    
    const char * getPetDescription();
    void setPetDescription(const char*);
    
    int getSkillIDByIndex(int index);
    int getDestinyByIndex(int index);
    
    void setSkillIDByIndex(int index,int value);
    void setDestinyByindex(int index,int value);
    
    void getSkills(xmlNodePtr node);
    void getDestinys(xmlNodePtr node);
    void getTalents(xmlNodePtr node,xmlDoc *doc);
    CCArray* getTalentList();
    
private:
    
    int skillID[7];
    int destinyID[5];
    std::string m_strPetName;
    std::string m_strPetName2;
    std::string m_strPetName3;
    std::string m_strBattleFace;
    std::string m_strPetFace;
    std::string m_strPetFace2;
    std::string m_strPetFace3;
    std::string m_strPetCard;
    std::string m_strPetCard2;
    std::string m_strPetCard3;
    std::string m_strPetDescription;
    CCArray talentList;

};

//精灵属性类
class MB_PetData : public CCObject
{
 
private:
    
    CCArray *onlineAttribute;
    MB_PetTemplate* m_pTemplete;
public:
    
    MB_PetData();
    ~MB_PetData();
    
    CCArray* getOnlineAttribute(){
    
        return  onlineAttribute;
    }
    //精灵属性
    CC_SYNTHESIZE(uint64_t, m_uPetID, PetID);
    CC_SYNTHESIZE(uint16_t, m_uPetTypeID, PetTypeID);
    //品阶
    CC_SYNTHESIZE(uint16_t, m_uPetQuallity,PetQuallity);
    CC_SYNTHESIZE(uint16_t, m_uPetLevel, PetLevel);
    CC_SYNTHESIZE(uint32_t, m_uPetAttack,PetAttack);
    CC_SYNTHESIZE(uint32_t, m_uPetHpMax,PetHpMax);
    CC_SYNTHESIZE(uint64_t, m_uPetFightPower, PetFightPower);
    CC_SYNTHESIZE(uint64_t, m_uPetExp, PetExp);
    //是否待出售
    CC_SYNTHESIZE(bool,m_nReadyForSold,ReadyForSold);
    CC_SYNTHESIZE(bool,m_nIsHomelandPet, IsHomelandPet);
    int getTemplateStar();
    MB_PetTemplate* getTemplete(){return m_pTemplete;};
    void setTemplete(MB_PetTemplate* templete){m_pTemplete = templete;};
};


class MB_PetQualityCostTemplete: public CCObject
{
public:
    MB_PetQualityCostTemplete();
    
    CC_SYNTHESIZE(uint8_t, m_nStar, Star);
    CC_SYNTHESIZE(uint16_t, m_nQuality, Quality);
    CC_SYNTHESIZE(int64_t, m_nCoin, Coin);
};

class MB_PetQualityCostSpecialTemplete: public CCObject
{
public:
    
    MB_PetQualityCostSpecialTemplete();
    ~MB_PetQualityCostSpecialTemplete();
    CC_SYNTHESIZE(uint16_t, m_uCostID, CostID);
    CCArray* getCostArray() { return m_pCostArray;}
 
private:
    CCArray* m_pCostArray;
};


class MB_PetQualityCostSpecialTempleteValue: public CCObject
{
public:
    MB_PetQualityCostSpecialTempleteValue();
    
    CC_SYNTHESIZE(uint16_t, m_uItemTypeID, ItemTypeID);
    CC_SYNTHESIZE(uint32_t, m_uNum, Num);
};

//精灵管理类

typedef std::map<uint16_t, MB_PetTemplate*> MB_PetTemplateMap;
typedef std::pair<uint16_t, MB_PetTemplate*> MB_PetTemplateMapEntry;

class MB_PetMgr : public CCObject
{
public :
    
    ~MB_PetMgr();
    MB_PetMgr();
    
    static MB_PetMgr * getInstance();
    static void destroyInstance();
    static MB_PetData* createInstance(MB_PetTemplate* pTemplate,uint16_t nRank=0,uint16_t nLevel=1);
    
    MB_PetTemplateMap* getPetTemplateMap();
    MB_PetTemplate* getPetTemplateByID(uint16_t petTypeID);
    MB_PetTemplate* getPetTemplateByUID(uint64_t petUID);

    int getPetTemplateStarByUID(uint64_t uid);
    
    CCArray* getPetDataArray();
    MB_PetData* getPetDataByUID(uint64_t petUID);
    
    bool isPetExist(uint64_t petUID);
    
    bool getPetInPackage(uint16_t tid);
    
    //排序规则:上阵精灵>星级>等级>id
    void sortPetDataArray();
    
    CCArray* getPetQualityCostArray() {
        return m_pPetQualityUpCost;}
    CCArray* getPetGodArray() {
        return m_pPetGodCost;}
    
    CCArray* getPetRestoreMaterial(uint8_t rank,uint16_t tid,uint8_t star);

    //清空待售列表
    void clearPetForSell();
    //是否在待售列表
    bool checkInSell(uint64_t petID);
    //获取精灵列表
    bool sendpet_info();
    bool recvpet_info(MB_MsgBuffer* recvPacket);

    //出售待售列表中精灵
    bool sendpet_sell();
    bool recvpet_sell(MB_MsgBuffer* recvPacket);
    
    //精灵属性修改
    bool recvpet_update(MB_MsgBuffer* recvPacket);
    bool recvpet_update_exp(MB_MsgBuffer* recvPacket);
    bool sendpet_eat(uint64_t petID,CCArray *arry);
    bool recvpet_eat(MB_MsgBuffer* recvPacket);
    bool recvpet_del(MB_MsgBuffer *recvPacket);
    
    void recvpet_ger_more(MB_MsgBuffer* recvPacket);
    
    //精灵添加
    bool recvpet_new(MB_MsgBuffer* recvPacket);
    bool recvpet_new_list(MB_MsgBuffer *recvPacket);
    
    //精灵升品
    bool sendpet_up_rank(uint64_t srcPetID, uint64_t costPetID);
    bool recvpet_up_rank(MB_MsgBuffer* recvPacket);
    
    void onMsgRecv(CCNode* node, SocketResponse* response);
    
    const char* getPetRealName(char *buf,int64_t petID);
    const char* getPetRealNameNoSpace(char *buf,int64_t petID);
    const char* getPetRealName(uint16_t petTypeID, uint16_t petQuality);
    const char * getPetRealNameWithType(char *buf,int16_t petType,int16_t petShape);
    
    //旧接口  只能取到第一形态名字
    const char * getPetRealNameWithType(char *buf,int16_t petType);
    
    int64_t getExpByLevel(int level);
    uint16_t calLevelByExp(uint64_t exp);
    int64_t calEatExpByUID(uint64_t petUID);
    static int calPetAttack(int attack, uint16_t level, uint16_t quality);
    static int calPetHP(int hp, uint16_t level, uint16_t quality);
    int getPetNumByType(uint16_t type);
    
    void setPetInHomeLand(uint64_t petId,bool bIn);
    bool checkPetInHomeLand(uint64_t petId);
private:

    MB_PetTemplateMap m_mapPetTemplate;
    CCArray* m_pPetDataArray;
    CCArray* m_pEatArray;
    CCArray* m_pPetQualityUpCost;
    CCArray* m_pPetGodCost;
    int64_t m_ExpList[MAX_LEVEL];
    
    bool initTemplete();
    bool initQualityCost();
    bool initGodCost();
    bool initExp();
    void removePetAfterSell();
    bool removePetByUID(uint64_t petID);
};

class MB_SkillData: public CCObject{
    
    private:
    
        std::string m_strSkillName;
        std::string m_strSkillIcon;
        std::string m_strSkillDescription;
    
    public :
    
        MB_SkillData(){
        }
        ~MB_SkillData(){
        
        }
        CC_SYNTHESIZE(int, m_nSKillID, SkillID);
        const char * getSkillName();
        const char * getSkillIcon();
        const char * getSkillDescription();
        void setSkillName( const char *skillName);
        void setSkillIcon( const char *skillIcon);
        void setSkillDescription(const char * skillDescription);

};

typedef std::map<uint32_t, MB_SkillData*> SkillMap;
typedef std::pair<uint32_t, MB_SkillData *> SkillMapEntry;

class MB_SkillMgr{
    
    private:
    
        SkillMap m_mapSkill;
        static MB_SkillMgr * m_pSharedSkillMgr;
        void initSkillData();
    
    public:
 
        MB_SkillMgr();
        ~MB_SkillMgr();
 
        MB_SkillData *getSkillDataByID(int skillID);
        static MB_SkillMgr *getInstance();
        void purgeData();
    
};

class MB_DestinyAttribute :public CCObject{

    private:
    
        std::string m_strName;
    
    public:
    
        MB_DestinyAttribute();
        ~MB_DestinyAttribute();
        const char *getName();
        void setName(const char *);
        CC_SYNTHESIZE(int, m_nType, Type)
        CC_SYNTHESIZE(float ,m_nValue, Value)
};
class MB_DestinyData :public CCObject {

    private:
    
        std::string m_strDestinyName;
        CCArray *DestinyAttributeArrary;
    
    public:
    
        MB_DestinyData();
        ~MB_DestinyData();       
        const char * getDestinyName();
        void setDestinyName(const char *);
        CCArray *getDestinyAttributeArray();
        CC_SYNTHESIZE(int, m_nDestinyID , DestinyID);
        CC_SYNTHESIZE(int, m_nDestinyType , DestinyType);
        CC_SYNTHESIZE(int, m_nDestinyNeed1 , DestinyNeed1);
        CC_SYNTHESIZE(int, m_nDestinyNeed2 , DestinyNeed2);
        CC_SYNTHESIZE(int, m_nDestinyNeed3 , DestinyNeed3);
        CC_SYNTHESIZE(int, m_nDestinyNeed4 , DestinyNeed4);
};

typedef std::map<uint32_t, MB_DestinyData*> DestinyDataMap;
typedef std::pair<uint32_t, MB_DestinyData *> DestinyDataEntry;
class MB_DestinyMgr{
    
private:
    
    DestinyDataMap m_mapDestiny;
    static MB_DestinyMgr * m_pSharedDestinyMgr;
    void initDestinyData();
    
public:
    
    MB_DestinyMgr();
    ~MB_DestinyMgr();
    
    MB_DestinyData *getDestinyDataByID(int destinyID);
    static MB_DestinyMgr *getInstance();
    void getDestinyAttribute(MB_DestinyAttribute *attribute,xmlDoc *);
    void purgeData();

};

#endif /* defined(__ProjectMB__MB_PetData__) */
