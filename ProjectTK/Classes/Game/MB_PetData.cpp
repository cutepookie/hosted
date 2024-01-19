
#include "MB_PetData.h"
#include "../Common/GameLib/GameHelper/CCGameHelper.h"


//Pet模板类 实现
MB_PetTemplate::MB_PetTemplate()
{
    for (int i = 0 ; i < 7; i++) {
        
        skillID[i] = 0;
    }
    for (int i = 0 ; i < 5; i++) {
        
        destinyID[i] = 0;
    }
    
}

MB_PetTemplate::~MB_PetTemplate()
{
    
}

const char * MB_PetTemplate::getPetName()
{
    return  m_strPetName.c_str();
}

const char * MB_PetTemplate::getPetName(uint16_t shape)
{
    if (SHAPE_1 == shape)
    {
        return  m_strPetName.c_str();
    }
    if (SHAPE_2 == shape)
    {
        return  m_strPetName2.c_str();
    }
    if (SHAPE_3 <= shape)
    {
        return  m_strPetName3.c_str();
    }
    else
    {
        MB_LOG("MB_PetTemplate::getPetName ERROR");
    }
    return NULL;
    
}

const char * MB_PetTemplate::getPetFace()
{
    //MB_LOG("旧方法 只能取到第一阶段属性");
    return  m_strPetFace.c_str();
}

const char * MB_PetTemplate::getPetFace(uint16_t shape)
{
    if (SHAPE_1 == shape)
    {
        return  m_strPetFace.c_str();
        
    }
    if (SHAPE_2 == shape)
    {
        return  m_strPetFace2.c_str();
        
    }
    if (SHAPE_3 <= shape)
    {
        return  m_strPetFace3.c_str();
        
    }
    else
    {
        MB_LOG("MB_PetTemplate::getPetFace ERROR");
        return  m_strPetFace.c_str();
    }
    return NULL;
}

const char * MB_PetTemplate::getPetCard()
{
    //MB_LOG("旧方法 只能取到第一阶段属性");
    return  m_strPetCard.c_str();
}
const char * MB_PetTemplate::getBattleCard()
{
     return  m_strBattleFace.c_str();
}
const char * MB_PetTemplate::getPetCard(uint16_t shape)
{
    if (SHAPE_1 == shape)
    {
        return  m_strPetCard.c_str();
        
    }
    if (SHAPE_2 == shape)
    {
        return  m_strPetCard2.c_str();
        
    }
    if (SHAPE_3 <= shape)
    {
        return  m_strPetCard3.c_str();
        
    }
    else
    {
        MB_LOG("MB_PetTemplate::getPetCard ERROR");
    }
    return NULL;
}

const char * MB_PetTemplate::getPetDescription(){
    
    return  m_strPetDescription.c_str();
}

void MB_PetTemplate::setPetName(const char* data){
    
    m_strPetName = data;
}
void MB_PetTemplate::setPetName2(const char* data){
    
    m_strPetName2 = data;
}
void MB_PetTemplate::setPetName3(const char* data){
    
    m_strPetName3 = data;
}

void MB_PetTemplate::setPetFace(const char* data){
    
    m_strPetFace = data;
}
void MB_PetTemplate::setPetFace2(const char* data){
    
    m_strPetFace2 = data;
}
void MB_PetTemplate::setPetFace3(const char* data){
    
    m_strPetFace3 = data;
}
void MB_PetTemplate::setBattleCard(const char* data){
    m_strBattleFace = data;
}
void MB_PetTemplate::setPetCard(const char* data){
    
    m_strPetCard = data;
}
void MB_PetTemplate::setPetCard2(const char* data){
    
    m_strPetCard2 = data;
}
void MB_PetTemplate::setPetCard3(const char* data){
    
    m_strPetCard3 = data;
}
void MB_PetTemplate::setPetDescription(const char* data){
    
    m_strPetDescription = data;
}
int MB_PetTemplate::getSkillIDByIndex(int index){
    
    return skillID[index];
}
int MB_PetTemplate::getDestinyByIndex(int index){
    
    return destinyID[index];
    
}
void MB_PetTemplate::setSkillIDByIndex(int index,int value){
    
    skillID[index] = value;
}
void MB_PetTemplate::setDestinyByindex(int index,int value){
    
    destinyID[index] = value;
}
CCArray* MB_PetTemplate::getTalentList(){
    
    return &talentList;
}
//MB_PetData类 实现

MB_PetData::MB_PetData()
{
    m_nReadyForSold = false;
    m_nIsHomelandPet = false;
    onlineAttribute = new CCArray();
    m_pTemplete = NULL;
}

MB_PetData::~MB_PetData()
{
    delete onlineAttribute;
}
int MB_PetData::getTemplateStar()
{

    if(m_pTemplete == NULL)
    {
        MB_PetMgr::getInstance()->getPetTemplateByID(getPetTypeID());
    }
    if (m_pTemplete)
    {
        return m_pTemplete->getPetStar();
    }
    return 0;
}
//PetMgr类 实现

static MB_PetMgr* s_pPetMgr = NULL;

MB_PetMgr::MB_PetMgr()
{
    m_pPetDataArray = CCArray::create();
    m_pPetDataArray->retain();
    m_pEatArray = new CCArray();
    m_pPetQualityUpCost = CCArray::create();
    m_pPetQualityUpCost->retain();
    m_pPetGodCost = CCArray::create();
    m_pPetGodCost->retain();
    
    if (!initTemplete()) {
        MB_LOG("init general templete failed.");
    }
    
    if (!initQualityCost()) {
        MB_LOG("init quality cost templete failed.");
    }
    
    if (!initExp()) {
        MB_LOG("init role exp failed.");
    }
    
    if (!initGodCost()) {
        MB_LOG("init pet god cost failed.");
    }
    
    SOCKET_MSG_REGIST(SC_GER_INFO, MB_PetMgr);
    SOCKET_MSG_REGIST(SC_GER_SELL, MB_PetMgr);
    SOCKET_MSG_REGIST(SC_GER_UPDATE, MB_PetMgr);
    SOCKET_MSG_REGIST(SC_GER_UPDATE_EXP, MB_PetMgr);
    SOCKET_MSG_REGIST(SC_GER_NEW, MB_PetMgr);
    SOCKET_MSG_REGIST(SC_GER_EAT, MB_PetMgr);
    SOCKET_MSG_REGIST(SC_GER_UP_RANK, MB_PetMgr);
    SOCKET_MSG_REGIST(SC_GER_DEL, MB_PetMgr);
    SOCKET_MSG_REGIST(SC_GER_NEW_LIST, MB_PetMgr);
    SOCKET_MSG_REGIST(SC_GER_MORE, MB_PetMgr);
}

bool MB_PetMgr::getPetInPackage(uint16_t tid)
{
    MB_PetData* pData = NULL;
    
    CCARRAY_FOREACH_4TYPE(m_pPetDataArray, MB_PetData*, pData)
    {
        if (pData->getPetTypeID() == tid)
        {
            return true;
        }
    }
    
    return false;
}

bool MB_PetMgr::isPetExist(uint64_t petUID)
{
    MB_PetData* pData = NULL;
    
    CCARRAY_FOREACH_4TYPE(m_pPetDataArray, MB_PetData*, pData)
    {
        if (pData->getPetID() == petUID)
        {
            return true;
        }
    }
    return false;
}

int MB_PetMgr::getPetTemplateStarByUID(uint64_t uid)
{
    MB_PetData* pData = getPetDataByUID(uid);
    if (pData)
    {
        return pData->getTemplateStar();
    }
    return 0;
}

MB_PetMgr::~MB_PetMgr()
{
    CC_SAFE_RELEASE_NULL(m_pPetDataArray);
    CC_SAFE_RELEASE_NULL(m_pEatArray);
    CC_SAFE_RELEASE_NULL(m_pPetQualityUpCost);
    CC_SAFE_RELEASE_NULL(m_pPetGodCost);
    
    MB_PetTemplateMap::iterator itr =  m_mapPetTemplate.begin();
    MB_PetTemplateMap::iterator end =  m_mapPetTemplate.end();
    while (itr != end) {
        
        CC_SAFE_RELEASE(itr->second);
        itr++;
    }
    
    SOCKET_MSG_UNREGIST(SC_GER_INFO);
    SOCKET_MSG_UNREGIST(SC_GER_SELL);
    SOCKET_MSG_UNREGIST(SC_GER_UPDATE);
    SOCKET_MSG_UNREGIST(SC_GER_UPDATE_EXP);
    SOCKET_MSG_UNREGIST(SC_GER_NEW);
    SOCKET_MSG_UNREGIST(SC_GER_EAT);
    SOCKET_MSG_UNREGIST(SC_GER_DEL);
    SOCKET_MSG_UNREGIST(SC_GER_UP_RANK);
    SOCKET_MSG_UNREGIST(SC_GER_NEW_LIST);
    SOCKET_MSG_UNREGIST(SC_GER_MORE);
}

MB_PetMgr* MB_PetMgr::getInstance(){
    
    if(s_pPetMgr == NULL )
    {
        s_pPetMgr = new  MB_PetMgr();
    }
    
    return  s_pPetMgr;
}
void MB_PetMgr::setPetInHomeLand(uint64_t petId,bool bIn)
{
    MB_PetData* pData = getPetDataByUID(petId);
    if (pData)
    {
        pData->setIsHomelandPet(bIn);
    }
}
bool MB_PetMgr::checkPetInHomeLand(uint64_t petId)
{
    MB_PetData* pData = getPetDataByUID(petId);
    if (pData)
    {
        return pData->getIsHomelandPet();
    }
    return false;
}
void MB_PetMgr::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(s_pPetMgr);
    s_pPetMgr = NULL;
}

bool MB_PetMgr::initTemplete()
{
    
    xmlDocPtr g_sharedDoc =  MB_XmlReader::readXml("config/card.xml");
    if (!g_sharedDoc)
    {
        return false;
    }
    
    xmlDocPtr g_sharedDoc2 = MB_XmlReader::readXml("config/description/card_property.xml");
    
    xmlNodePtr root;
    
    root=xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    while(curNode != NULL) {
        
        if (xmlStrcmp(curNode->name,BAD_CAST "general")) {
            curNode = curNode->next;
            continue;
        }
        
        struct _xmlAttr * attr = curNode->properties;
        
        if (attr != NULL) {
            
            MB_PetTemplate* petTempleteNode = new MB_PetTemplate();
            
            if (attr != NULL && !xmlStrcmp(attr->name,BAD_CAST "pettypeid"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petTempleteNode->setPetTypeID(atoi(value));

                CC_SAFE_FREE(value);
                attr = attr->next;
                
            }
            if (attr != NULL && !xmlStrcmp(attr->name,BAD_CAST "petname"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petTempleteNode->setPetName(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            //添加读取2，3阶名称
            if (attr != NULL && !xmlStrcmp(attr->name,BAD_CAST "petname2"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petTempleteNode->setPetName2(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (attr != NULL && !xmlStrcmp(attr->name,BAD_CAST "petname3"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petTempleteNode->setPetName3(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (attr != NULL && !xmlStrcmp(attr->name,BAD_CAST "petface"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petTempleteNode->setPetFace(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            //添加读取2，3阶名称头像
            if (attr != NULL && !xmlStrcmp(attr->name,BAD_CAST "petface2"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petTempleteNode->setPetFace2(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (attr != NULL && !xmlStrcmp(attr->name,BAD_CAST "petface3"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petTempleteNode->setPetFace3(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            if (attr != NULL && !xmlStrcmp(attr->name,BAD_CAST "battleface"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petTempleteNode->setBattleCard(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            if (attr != NULL && !xmlStrcmp(attr->name,BAD_CAST "petcard"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petTempleteNode->setPetCard(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            //添加读取2，3阶卡牌
            if (attr != NULL && !xmlStrcmp(attr->name,BAD_CAST "petcard2"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petTempleteNode->setPetCard2(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (attr != NULL && !xmlStrcmp(attr->name,BAD_CAST "petcard3"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petTempleteNode->setPetCard3(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (attr != NULL && !xmlStrcmp(attr->name,BAD_CAST "petdescription"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petTempleteNode->setPetDescription(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (attr != NULL && !xmlStrcmp(attr->name,BAD_CAST "gestar"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petTempleteNode->setPetStar(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (attr != NULL && !xmlStrcmp(attr->name,BAD_CAST "petkingdom"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petTempleteNode->setPetKingdom(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (attr != NULL && !xmlStrcmp(attr->name,BAD_CAST "petAttack"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petTempleteNode->setPetAttack(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            if (attr != NULL && !xmlStrcmp(attr->name,BAD_CAST "petHpMax"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petTempleteNode->setPetHpMax(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            if (attr != NULL && !xmlStrcmp(attr->name,BAD_CAST "petCost"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petTempleteNode->setPetCost(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            if (attr != NULL && !xmlStrcmp(attr->name,BAD_CAST "rankgod"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petTempleteNode->setRankGodID(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            if (attr != NULL && !xmlStrcmp(attr->name,BAD_CAST "ranksaint"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petTempleteNode->setRankSaintID(atoi(value));
                CC_SAFE_FREE(value);
                //                attr = attr->next;
            }
            
            for ( xmlNodePtr child = curNode ->xmlChildrenNode; child != NULL ; child = child->next ) {
                
                
                if (!xmlStrcmp(child->name,BAD_CAST "Atrributes")){
                    
                    petTempleteNode->getTalents(child,g_sharedDoc2);
                    
                }else if (!xmlStrcmp(child->name,BAD_CAST "skills")) {
                    
                    petTempleteNode->getSkills(child);
                    
                }else  if (!xmlStrcmp(child->name,BAD_CAST "destinys")){
                    
                    petTempleteNode->getDestinys(child);
                    
                }else {
                    
                    continue;
                }
                
            }
            
            //加入到模板map中
            m_mapPetTemplate.insert(MB_PetTemplateMapEntry(petTempleteNode->getPetTypeID(), petTempleteNode));
            
        }
        else
        {
            MB_LOG("Error:empty general in templete.");
        }
        
        curNode = curNode->next;
    }
    
    xmlFreeDoc(g_sharedDoc);
    xmlFreeDoc(g_sharedDoc2);
    PRINT_TIME("readpet");
    return true;
}
int MB_PetMgr::getPetNumByType(uint16_t type){
    int count = 0;
    CCObject *obj;
    CCARRAY_FOREACH(m_pPetDataArray, obj){
        
        MB_PetData *data = (MB_PetData *)obj;
        if(data->getPetTypeID() == type){
            
            if(MB_TeamData::getInstance()->checkInTeam(data) == false ){
                
                if(data->getPetLevel() < 10 && data->getPetQuallity() <1){
                    
                    count++;
                }
            }
        }
    }
    return  count;
}
bool MB_PetMgr::initQualityCost()
{
    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/card_rank.xml");
    
    if (!g_sharedDoc)
    {
        return false;
    }
    
    xmlNodePtr root;
    
    root=xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    while(curNode != NULL) {
        
        if (xmlStrcmp(curNode->name,BAD_CAST "rank")) {
            curNode = curNode->next;
            continue;
        }
        
        struct _xmlAttr * attr = curNode->properties;
        
        if (attr != NULL) {
            
            MB_PetQualityCostTemplete* petQCT = new MB_PetQualityCostTemplete();
            
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "star"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petQCT->setStar(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "quality"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petQCT->setQuality(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "coin"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petQCT->setCoin(atoll(value));
                CC_SAFE_FREE(value);
            }
            
            //加入到模板中
            m_pPetQualityUpCost->addObject(petQCT);
            petQCT->release();
            
        }
        
        curNode = curNode->next;
    }
    
    xmlFreeDoc(g_sharedDoc);
    
    return true;
}

bool MB_PetMgr::initGodCost()
{
    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/card_breakthrough.xml");
    
    if (!g_sharedDoc)
    {
        return false;
    }
    
    xmlNodePtr root;
    
    root=xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    while(curNode != NULL) {
        
        if (xmlStrcmp(curNode->name,BAD_CAST "pet")) {
            curNode = curNode->next;
            continue;
        }
        
        struct _xmlAttr * attr = curNode->properties;
        
        if (attr != NULL) {
            
            MB_PetQualityCostSpecialTemplete* petQCST = new MB_PetQualityCostSpecialTemplete();
            
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "id"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                petQCST->setCostID(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            xmlNodePtr curNodeChild = curNode->xmlChildrenNode;
            char* atrributeValue;
            while(NULL != curNodeChild)
            {
                if (xmlStrcmp(curNodeChild->name,BAD_CAST "item"))
                {
                    curNodeChild = curNodeChild->next;
                    continue;
                }
                
                struct _xmlAttr * attr1 = curNodeChild->properties;
                
                if (attr1 != NULL)
                {
                    MB_PetQualityCostSpecialTempleteValue* templeteValue = new MB_PetQualityCostSpecialTempleteValue();
                    
                    if ( 0 == xmlStrcmp(attr1->name,BAD_CAST "typeid"))
                    {
                        atrributeValue = (char*)xmlNodeGetContent(attr1->children);
                        templeteValue->setItemTypeID(atoi(atrributeValue));
                        CC_SAFE_FREE(atrributeValue);
                        attr1 = attr1->next;
                    }
                    
                    if (0 == xmlStrcmp(attr1->name,BAD_CAST "num"))
                    {
                        atrributeValue = (char*)xmlNodeGetContent(attr1->children);
                        templeteValue->setNum(atoi(atrributeValue));
                        CC_SAFE_FREE(atrributeValue);
                    }
                    //加入模板
                    petQCST->getCostArray()->addObject(templeteValue);
                    templeteValue->release();
                }
                curNodeChild = curNodeChild->next;
            }
            
            //加入到模板中
            m_pPetGodCost->addObject(petQCST);
            petQCST->release();
            
        }
        
        curNode = curNode->next;
    }
    
    xmlFreeDoc(g_sharedDoc);
    
    return true;
}

CCArray* MB_PetMgr::getPetRestoreMaterial(uint8_t rank,uint16_t tid,uint8_t star)
{
    MB_PetQualityCostSpecialTemplete* p = NULL;
    CCArray* pArray = CCArray::create();
    RewardTempleteValue* pValue = new RewardTempleteValue;
    pValue->setNumber(1);
    pValue->setType(kRewardValueTypePet);
    pValue->setValueID(tid);
    pArray->addObject(pValue);
    pValue->release();
    if (rank != 10 || rank!=20)
    {
        return pArray;
    }
    
    rank /= 10;
    
    uint16_t cshap = 0;
    uint8_t cstar = 0;
    uint16_t cid = 0;
    CCARRAY_FOREACH_4TYPE(m_pPetGodCost, MB_PetQualityCostSpecialTemplete*, p)
    {
        cshap = p->getCostID();
        cid /= 10000;
        cstar = p->getCostID()%10;
        if (rank==cid && cstar==star)
        {
            CCArray* pMaterial = p->getCostArray();
            
            MB_PetQualityCostSpecialTempleteValue* pV = NULL;
            CCARRAY_FOREACH_4TYPE(pMaterial, MB_PetQualityCostSpecialTempleteValue*, pV)
            {
                pValue = new RewardTempleteValue;
                pValue->setNumber(pV->getNum());
                pValue->setType(kRewardValueTypeItem);
                pValue->setValueID(pV->getItemTypeID());
                pArray->addObject(pValue);
                pValue->release();
            }
            return pArray;
        }
    }
    return pArray;
}

bool MB_PetMgr::initExp()
{
    for (int i = 0; i < MAX_LEVEL; ++i) {
        m_ExpList[i] = 0;
    }
    
    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/card_exp.xml");
    
    if (!g_sharedDoc)
    {
        return false;
    }
    
    xmlNodePtr root;
    
    root=xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    while(curNode != NULL) {
        
        if (xmlStrcmp(curNode->name,BAD_CAST "level")) {
            curNode = curNode->next;
            continue;
        }
        int level = 0;
        int64_t exp = 0;
        struct _xmlAttr * attr = curNode->properties;
        
        if (attr != NULL)
        {
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "value"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                level = atoi(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if(attr&&!xmlStrcmp(attr->name,BAD_CAST "exp"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                exp = atoll(value);
                CC_SAFE_FREE(value);
            }
            if (level < MAX_LEVEL)
            {
                m_ExpList[level] = exp;
            }
        }
        
        curNode = curNode->next;
    }
    
    xmlFreeDoc(g_sharedDoc);
    return true;
}

void MB_PetTemplate::getSkills(xmlNodePtr node){
    
    for (xmlNodePtr child = node->children; child != NULL; child = child->next) {
        
        int index = -1;
        
        if (!xmlStrcmp(child->name,BAD_CAST "skill1")) {
            
            index = 0;
            char * value;
            int skillID = 0;
            for(struct _xmlAttr * attr = child->properties; attr != NULL ; attr = attr->next ){
                
                if (!xmlStrcmp(attr->name,BAD_CAST "skillID")){
                    
                    value = (char*)xmlNodeGetContent(attr->children);
                    skillID = atoi(value);
                    CC_SAFE_FREE(value);
                    break;
                }
                
            }
            setSkillIDByIndex(index, skillID);
            
        }else if (!xmlStrcmp(child->name,BAD_CAST "skill2")) {
            
            index = 1;
            char * value;
            int skillID = 0;
            for(struct _xmlAttr * attr = child->properties; attr != NULL ; attr = attr->next ){
                
                if (!xmlStrcmp(attr->name,BAD_CAST "skillID")){
                    
                    value = (char*)xmlNodeGetContent(attr->children);
                    skillID = atoi(value);
                    CC_SAFE_FREE(value);
                    break;
                }
                
            }
            setSkillIDByIndex(index, skillID);
            
        }else if (!xmlStrcmp(child->name,BAD_CAST "skill3")) {
            
            index = 2;
            char * value;
            int skillID = 0;
            for(struct _xmlAttr * attr = child->properties; attr != NULL ; attr = attr->next ){
                
                if (!xmlStrcmp(attr->name,BAD_CAST "skillID")){
                    
                    value = (char*)xmlNodeGetContent(attr->children);
                    skillID = atoi(value);
                    CC_SAFE_FREE(value);
                    break;
                }
                
            }
            setSkillIDByIndex(index, skillID);
            
        }else if (!xmlStrcmp(child->name,BAD_CAST "skill4")) {
            
            index = 3;
            char * value;
            int skillID = 0;
            for(struct _xmlAttr * attr = child->properties; attr != NULL ; attr = attr->next ){
                
                if (!xmlStrcmp(attr->name,BAD_CAST "skillID")){
                    
                    value = (char*)xmlNodeGetContent(attr->children);
                    skillID = atoi(value);
                    CC_SAFE_FREE(value);
                    break;
                }
                
            }
            setSkillIDByIndex(index, skillID);
            
        }else if (!xmlStrcmp(child->name,BAD_CAST "skill5")) {
            
            index = 4;
            char * value;
            int skillID = 0;
            for(struct _xmlAttr * attr = child->properties; attr != NULL ; attr = attr->next ){
                
                if (!xmlStrcmp(attr->name,BAD_CAST "skillID")){
                    
                    value = (char*)xmlNodeGetContent(attr->children);
                    skillID = atoi(value);
                    CC_SAFE_FREE(value);
                    break;
                }
                
            }
            setSkillIDByIndex(index, skillID);
            
        }else if (!xmlStrcmp(child->name,BAD_CAST "skill6")) {
            
            index = 5;
            char * value;
            int skillID = 0;
            for(struct _xmlAttr * attr = child->properties; attr != NULL ; attr = attr->next ){
                
                if (!xmlStrcmp(attr->name,BAD_CAST "skillID")){
                    
                    value = (char*)xmlNodeGetContent(attr->children);
                    skillID = atoi(value);
                    CC_SAFE_FREE(value);
                    break;
                }
                
            }
            setSkillIDByIndex(index, skillID);
            
        }else if (!xmlStrcmp(child->name,BAD_CAST "skill7")) {
            
            index = 6;
            char * value;
            int skillID = 0;
            for(struct _xmlAttr * attr = child->properties; attr != NULL ; attr = attr->next ){
                
                if (!xmlStrcmp(attr->name,BAD_CAST "skillID")){
                    
                    value = (char*)xmlNodeGetContent(attr->children);
                    skillID = atoi(value);
                    CC_SAFE_FREE(value);
                    break;
                }
                
            }
            setSkillIDByIndex(index, skillID);
            
        }
        
        
    }
}
void MB_PetTemplate::getTalents(xmlNodePtr node,xmlDoc *doc){
    
    for(xmlNodePtr child = node->children; child != NULL ; child = child->next){
        
        if (xmlStrcmp(child->name,BAD_CAST "Attribute")) {
            
            continue;
        }
        MB_DestinyAttribute * attribute = new MB_DestinyAttribute();
        char *value;
        for (struct _xmlAttr * attr = child->properties; attr != NULL ; attr = attr->next) {
            
            if (!xmlStrcmp(attr->name,BAD_CAST "Type")){
                
                value = (char*)xmlNodeGetContent(attr->children);
                attribute->setType(atoi(value));
                CC_SAFE_FREE(value);
                
            }else  if (!xmlStrcmp(attr->name,BAD_CAST "Value")){
                
                value = (char*)xmlNodeGetContent(attr->children);
                attribute->setValue(atof(value));
                CC_SAFE_FREE(value);
            }
            
        }
        MB_DestinyMgr::getInstance()->getDestinyAttribute(attribute, doc);
        talentList.addObject(attribute);
        attribute->release();
        
    }
    
    
}
void MB_PetTemplate::getDestinys(xmlNodePtr node){
    
    int index = 0;
    
    for (xmlNodePtr child = node->children; child != NULL; child = child->next) {
        
        if (xmlStrcmp(child->name,BAD_CAST "destiny")) {
            
            continue;
            
        }
        char * value;
        int destinyID = 0;
        for(struct _xmlAttr * attr = child->properties; attr != NULL ; attr = attr->next ){
            
            if (!xmlStrcmp(attr->name,BAD_CAST "destinyID")){
                
                value = (char*)xmlNodeGetContent(attr->children);
                destinyID = atoi(value);
                CC_SAFE_FREE(value);
                break;
            }
            
        }
        setDestinyByindex(index, destinyID);
        index++;
    }
    
}
MB_PetTemplateMap* MB_PetMgr::getPetTemplateMap()
{
    return &m_mapPetTemplate;
}

MB_PetTemplate* MB_PetMgr::getPetTemplateByID(uint16_t petTypeID)
{
    MB_PetTemplateMap::iterator petTempleteIterator = m_mapPetTemplate.find(petTypeID);
    if ( petTempleteIterator != m_mapPetTemplate.end()) {
        
        return petTempleteIterator->second;
    }
    else
    {
        MB_LOG("ID:%d pet not exist.", petTypeID);
        return  NULL;
    }
}

MB_PetTemplate* MB_PetMgr::getPetTemplateByUID(uint64_t petUID)
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pPetDataArray, pObj)
    {
        MB_PetData* petData = (MB_PetData*)pObj;
        if ( petData->getPetID() == petUID)
        {
            return petData->getTemplete();
        }
    }
    MB_LOG("UID:%llu pet instance not exist.", petUID);
    return NULL;
}
CCArray* MB_PetMgr::getPetDataArray()
{
    return m_pPetDataArray;
}

MB_PetData* MB_PetMgr::getPetDataByUID(uint64_t petUID)
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pPetDataArray, pObj)
    {
        MB_PetData* petData = (MB_PetData*)pObj;
        if ( petData->getPetID() == petUID)
        {
            return petData;
        }
    }
    MB_LOG("UID:%llu pet instance not exist.", petUID);
    return NULL;
}

int64_t  MB_PetMgr::getExpByLevel(int level){
    assert(level < MAX_LEVEL);
    return m_ExpList[level];
}

uint16_t MB_PetMgr::calLevelByExp(uint64_t exp)
{
    for (int i = 1; i < MAX_LEVEL; ++i) {
        if (m_ExpList[i] <= exp) {
            continue;
        }
        return i;
    }
    MB_LOG("Invalid exp:%llu",exp);
    return MAX_LEVEL-1;
}

int64_t MB_PetMgr::calEatExpByUID(uint64_t petUID)
{
    return 0;
}

int MB_PetMgr::calPetAttack(int attack, uint16_t level, uint16_t quality)
{
    //没有算伙伴加成
    return attack * (1 + (level-1)*0.1f) * (powf(2,(quality*0.1f)));
}

int MB_PetMgr::calPetHP(int hp, uint16_t level, uint16_t quality)
{
    //没有算伙伴加成
    return hp * (1 + (level-1)*0.1f) * (powf(2,(quality*0.1f)));
}

void MB_PetMgr::sortPetDataArray()
{
    int i,j;
    MB_PetData *pet1, *pet2;
    MB_PetTemplate* pPet1 = NULL;
    MB_PetTemplate* pPet2 = NULL;
    for (i = 0; i < m_pPetDataArray->count(); i++) {
        for (j = i + 1; j < m_pPetDataArray->count(); j++) {
            pet1 = (MB_PetData*)m_pPetDataArray->objectAtIndex(i);
            pet2 = (MB_PetData*)m_pPetDataArray->objectAtIndex(j);
            
            if (MB_TeamData::getInstance()->checkInTeam(pet1) == true
                && MB_TeamData::getInstance()->checkInTeam(pet2) == false) {
                continue;
            }
            else if (MB_TeamData::getInstance()->checkInTeam(pet1) == false
                     && MB_TeamData::getInstance()->checkInTeam(pet2) == true) {
                m_pPetDataArray->exchangeObjectAtIndex(i, j);
            }
            else
            {
                pPet1 = m_mapPetTemplate[pet1->getPetTypeID()];
                pPet2 = m_mapPetTemplate[pet2->getPetTypeID()];
                if (pPet1==NULL)
                {
                    CCLog("[Error]:ivalid petID %d",pet1->getPetTypeID());
                    continue;
                }
                if (pPet2==NULL)
                {
                    CCLog("[Error]:ivalid petID %d",pet2->getPetTypeID());
                    continue;
                }
                //经验卡牌 排最后
                if (NSGameHelper::checkIsExperienceCard(pet1->getPetTypeID()) && !(NSGameHelper::checkIsExperienceCard(pet2->getPetTypeID())))
                {
                    m_pPetDataArray->exchangeObjectAtIndex(i, j);
                    continue;
                }
                if (!(NSGameHelper::checkIsExperienceCard(pet1->getPetTypeID())) && NSGameHelper::checkIsExperienceCard(pet2->getPetTypeID())) {
                    continue;
                }
                
                if (pPet1->getPetStar() < pPet2->getPetStar())
                {
                    m_pPetDataArray->exchangeObjectAtIndex(i, j);
                }
                else if (pPet1->getPetStar() == pPet2->getPetStar())
                {
                    if (pet1->getPetQuallity() < pet2->getPetQuallity())
                    {
                        m_pPetDataArray->exchangeObjectAtIndex(i, j);
                    }
                    else if(pet1->getPetQuallity() == pet2->getPetQuallity())
                    {
                        if (pet1->getPetLevel() > pet2->getPetLevel()) {
                            continue;
                        }
                        else if (pet1->getPetLevel() < pet2->getPetLevel()) {
                            m_pPetDataArray->exchangeObjectAtIndex(i, j);
                        }
                        else
                        {
                            if (pet1->getPetTypeID() > pet2->getPetTypeID())
                            {
                                m_pPetDataArray->exchangeObjectAtIndex(i, j);
                            }
                        }
                    }    
                }
            }
        }
    }
}


void MB_PetMgr::clearPetForSell()
{
    CCObject *obj;
    CCARRAY_FOREACH(m_pPetDataArray,obj){
        
        if( ((MB_PetData *)obj)->getReadyForSold()){
            
            ((MB_PetData *)obj)->setReadyForSold(false);
        }
        
    }
}

bool MB_PetMgr::checkInSell(uint64_t petID)
{
    return true;
}

void MB_PetMgr::removePetAfterSell()
{
    CCObject *obj;
    int cout = m_pPetDataArray->count();
    for ( int i = 0; i < cout ; i++) {
        
        obj = m_pPetDataArray->objectAtIndex(i);
        if( ((MB_PetData *)obj)->getReadyForSold()){
            
            m_pPetDataArray->removeObjectAtIndex(i);
            i--;
            cout--;
        }
        
    }
}

bool MB_PetMgr::removePetByUID(uint64_t petID)
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pPetDataArray, pObj)
    {
        MB_PetData* petData = (MB_PetData*)pObj;
        
        if ( petData->getPetID() == petID)
        {
            m_pPetDataArray->removeObject(petData);
            return true;
        }
    }
    
    MB_LOG("error:removePetByUID UID:%llu pet not exist.", petID);
    return false;
}

bool MB_PetMgr::sendpet_info(){
    
    SOCKET_REQUEST_START(CS_GER_INFO);
    SOCKET_REQUEST_END(SC_GER_INFO, MB_PetMgr::onMsgRecv);
    return true;
}

bool  MB_PetMgr::recvpet_info(MB_MsgBuffer* recvPacket){

    uint16_t len;
    uint16_t data16;
    uint32_t data32;
    uint64_t data64;
    
    recvPacket->readU16(&len);
    
    m_pPetDataArray->removeAllObjects();
    
    for ( int i = 0; i< len; i++) {
        
        MB_PetData *petData = new MB_PetData();
        
        if (recvPacket->readU64(&data64)) {
            petData->setPetID(data64);
        }
        if (recvPacket->readU16(&data16)) {
            petData->setPetTypeID(data16);
        }
        if (recvPacket->readU16(&data16)) {
            petData->setPetQuallity(data16);
        }
        if (recvPacket->readU16(&data16)) {
            petData->setPetLevel(data16);
        }
        if (recvPacket->readU32(&data32)) {
            petData->setPetAttack(data32);
        }
        if (recvPacket->readU32(&data32)) {
            petData->setPetHpMax(data32);
        }
        if (recvPacket->readU64(&data64)) {
            petData->setPetFightPower(data64);
        }
        if (recvPacket->readU64(&data64)) {
            petData->setPetExp(data64);
        }
        else
        {
            petData->release();
            MB_LOG("parse recvpet_info error.");
            break;
        }
        
        if(petData->getPetHpMax() <= 0){
            
            MB_PetTemplate* templete = getPetTemplateByID(petData->getPetTypeID());
            if(templete != NULL){
                
                petData->setPetAttack(calPetAttack(templete->getPetAttack(), petData->getPetLevel(), petData->getPetQuallity()));
                petData->setPetHpMax(calPetHP(templete->getPetHpMax(), petData->getPetLevel(), petData->getPetQuallity()));
                
                petData->setTemplete(templete);
            }
        }
        else
        {
            MB_PetTemplate* templete = getPetTemplateByID(petData->getPetTypeID());
            if(templete != NULL)
            {
                petData->setTemplete(templete);
            }
        }
        m_pPetDataArray->addObject(petData);
        petData->release();
    }
    //排序
    sortPetDataArray();
    return true;
}

bool MB_PetMgr::sendpet_sell()
{
    SOCKET_REQUEST_START(CS_GER_SELL);
    CCObject *obj;
    uint16_t count =0;
    CCARRAY_FOREACH(m_pPetDataArray,obj){
        
        if( ((MB_PetData *)obj)->getReadyForSold()){
            
            count++;
        }
        
    }
    packet->writeU16(count);
    CCARRAY_FOREACH(m_pPetDataArray,obj){
        
        if( ((MB_PetData *)obj)->getReadyForSold()){
            
            packet->WriteUINT64(((MB_PetData *)obj)->getPetID());
        }
        
    }
    SOCKET_REQUEST_END(SC_GER_SELL, MB_PetMgr::onMsgRecv);
    return true;
}

bool MB_PetMgr::recvpet_sell(MB_MsgBuffer *recvPacket)
{
    uint8_t result;
    recvPacket->readU8(&result);
    if (result == 1) {
        
        removePetAfterSell();
    }
    else
    {
        clearPetForSell();
        MB_LOG("SC_GER_SELL errorcode:%d", result);
        return false;
    }
    return true;
}

void MB_PetMgr::recvpet_ger_more(MB_MsgBuffer *recvPacket)
{
    uint16_t len = 0;
    uint16_t data16;
    uint32_t data32;
    uint64_t data64;
    recvPacket->readU16(&len);
    for (int i = 0; i < len; i++)
    {
        MB_PetData *petData = new MB_PetData();
        
        if (recvPacket->readU64(&data64))
        {
            petData->setPetID(data64);
        }
        if (recvPacket->readU16(&data16))
        {
            petData->setPetTypeID(data16);
        }
        if (recvPacket->readU16(&data16))
        {
            petData->setPetQuallity(data16);
        }
        if (recvPacket->readU16(&data16))
        {
            petData->setPetLevel(data16);
        }
        if (recvPacket->readU32(&data32))
        {
            petData->setPetAttack(data32);
        }
        if (recvPacket->readU32(&data32))
        {
            petData->setPetHpMax(data32);
        }
        if (recvPacket->readU64(&data64))
        {
            petData->setPetFightPower(data64);
        }
        if (recvPacket->readU64(&data64))
        {
            petData->setPetExp(data64);
        }
        else
        {
            petData->release();
            MB_LOG("parse recvpet_info error.");
            return;
        }
        if(petData->getPetHpMax() <= 0)
        {
            MB_PetTemplate* templete = getPetTemplateByID(petData->getPetTypeID());
            if(templete != NULL)
            {
                petData->setPetAttack(calPetAttack(templete->getPetAttack(), petData->getPetLevel(), petData->getPetQuallity()));
                petData->setPetHpMax(calPetHP(templete->getPetHpMax(), petData->getPetLevel(), petData->getPetQuallity()));
                petData->setTemplete(templete);
            }
        }
        else
        {
            MB_PetTemplate* templete = getPetTemplateByID(petData->getPetTypeID());
            if(templete != NULL)
            {
                petData->setTemplete(templete);
            }
        }
        m_pPetDataArray->addObject(petData);
        petData->release();
    }
    if(len == 0)sortPetDataArray();
}

bool MB_PetMgr::recvpet_update(MB_MsgBuffer *recvPacket)
{
    uint16_t data16 = 0;
    uint32_t data32 = 0;
    uint64_t data64 = 0;
    recvPacket->readU64(&data64);
    MB_PetData* petData = getPetDataByUID(data64);
    if (petData != NULL) {
        
        petData->getOnlineAttribute()->removeAllObjects();
        if(recvPacket->readU16(&data16)) {
            petData->setPetQuallity(data16);
        }
        if (recvPacket->readU16(&data16)) {
            petData->setPetLevel(data16);
        }
        if (recvPacket->readU32(&data32)) {
            petData->setPetAttack(data32);
        }
        if (recvPacket->readU32(&data32)) {
            petData->setPetHpMax(data32);
        }
        if (recvPacket->readU64(&data64)) {
            petData->setPetFightPower(data64);
        }
        if (recvPacket->readU64(&data64)) {
            petData->setPetExp(data64);
        }
        else {
            MB_LOG("recvpet_update error.");
            return false;
        }
        if(petData->getPetHpMax() <= 0){
            
            MB_PetTemplate* templete = petData->getTemplete();
            if(templete != NULL){
                
                petData->setPetAttack(calPetAttack(templete->getPetAttack(), petData->getPetLevel(), petData->getPetQuallity()));
                petData->setPetHpMax(calPetHP(templete->getPetHpMax(), petData->getPetLevel(), petData->getPetQuallity()));
            }
        }
        
        
    }
    else
    {
        MB_LOG("pet not exist.petID:%luu",data64);
        return false;
    }
    //排序
    sortPetDataArray();
    return true;
}
bool MB_PetMgr::sendpet_eat(uint64_t petID,CCArray *array){
    
    SOCKET_REQUEST_START(CS_GER_EAT);
    packet->WriteUINT64(petID);
    packet->writeU16(array->count());
    CCObject *data;
    m_pEatArray->removeAllObjects();
    CCARRAY_FOREACH(array, data){
        
        m_pEatArray->addObject(data);
        packet->WriteUINT64(((MB_ItemData *)data)->getItemUID());
        
    }
    SOCKET_REQUEST_END(SC_GER_EAT, MB_PetMgr::onMsgRecv);
    return true;
}
bool MB_PetMgr::recvpet_eat(MB_MsgBuffer *recvPacekt){
    uint8_t data8;
    recvPacekt->readU8(&data8);
    uint64_t data64;
    recvPacekt->readU64(&data64);
    if (data8 != 1) {
        
        MB_Message::removeALLMessage();;
    }
    
    if (data8 == 1) {
        
        CCObject *object ;
        CCARRAY_FOREACH(m_pEatArray, object){
            
            CCLOG("remove general %llu",((MB_ItemData *)object)->getItemUID());
            m_pPetDataArray->removeObject(object);
        }
        
        
    }else if(data8 == 2){
        
        MB_Message::sharedMB_Message()->showMessage("吞噬失败","被吞噬精灵有已上阵精灵","确定");
        
    }else if(data8 == 3){
        
        MB_Message::sharedMB_Message()->showMessage("吞噬失败","被吞噬精灵超过8个","确定");
        
    }else if(data8 == 4){
        
        MB_Message::sharedMB_Message()->showMessage("吞噬失败","该角色等级，大于或等于了玩家等级","确定");
        
    }else if(data8 == 5){
        
        MB_Message::sharedMB_Message()->showMessage("吞噬失败","该精灵经验已满","确定");
        
    }else if(data8 == 6){
        
        MB_Message::sharedMB_Message()->showMessage("吞噬失败","数据不存在","确定");
        
    }else if(data8 == 7){
        
        MB_Message::sharedMB_Message()->showMessage("吞噬失败","未知原因","确定");
        
    }
    else if(data8 == 8)
    {
        MB_Message::sharedMB_Message()->showMessage("吞噬失败","经验卡牌不能吞噬其他卡牌","确定");
    }
    else if(data8 == 9)
    {
        MB_Message::sharedMB_Message()->showMessage("吞噬失败","不能吞噬炼金工厂守护神","确定");
    }
    else{
        
        MB_Message::sharedMB_Message()->showMessage("吞噬失败","未知原因","确定");
    }
    m_pEatArray->removeAllObjects();
    return true;
    
    
}


bool MB_PetMgr::recvpet_update_exp(MB_MsgBuffer* recvPacket){
    uint64_t data64 = 0;
    recvPacket->readU64(&data64);
    MB_PetData* petData = getPetDataByUID(data64);
    if (petData != NULL) {
        if(recvPacket->readU64(&data64)) {
            petData->setPetExp(data64);
        }
    }
    return true;
}

MB_PetData* MB_PetMgr::createInstance(MB_PetTemplate* pTemplate,uint16_t nRank,uint16_t nLevel)
{
    if (pTemplate == NULL)
    {
        return NULL;
    }
    
    MB_PetData* pTarget = new MB_PetData;
    pTarget->autorelease();
    
    pTarget->setPetID(0);
    pTarget->setPetTypeID(pTemplate->getPetTypeID());
    pTarget->setPetQuallity(nRank);
    pTarget->setPetLevel(nLevel);
    pTarget->setPetAttack(calPetAttack(pTemplate->getPetAttack(), nLevel, nRank));
    pTarget->setPetHpMax(calPetHP(pTemplate->getPetHpMax(), nLevel, nRank));
    pTarget->setPetFightPower(pTarget->getPetAttack());
    pTarget->setPetExp(0);
    pTarget->setTemplete(pTemplate);
    
    return pTarget;
}

bool MB_PetMgr::recvpet_new(MB_MsgBuffer *recvPacket)
{
    uint16_t data16;
    uint32_t data32;
    uint64_t data64;
    
    MB_PetData *petData = new MB_PetData();
    
    if (recvPacket->readU64(&data64)) {
        petData->setPetID(data64);
    }
    if (recvPacket->readU16(&data16)) {
        petData->setPetTypeID(data16);
    }
    if (recvPacket->readU16(&data16)) {
        petData->setPetQuallity(data16);
    }
    if (recvPacket->readU16(&data16)) {
        petData->setPetLevel(data16);
    }
    if (recvPacket->readU32(&data32)) {
        petData->setPetAttack(data32);
    }
    if (recvPacket->readU32(&data32)) {
        petData->setPetHpMax(data32);
    }
    if (recvPacket->readU64(&data64)) {
        petData->setPetFightPower(data64);
    }
    if (recvPacket->readU64(&data64)) {
        petData->setPetExp(data64);
    }
    else
    {
        petData->release();
        MB_LOG("parse recvpet_info error.");
        return false;
    }
    if(petData->getPetHpMax() <= 0){
        
        MB_PetTemplate* templete = getPetTemplateByID(petData->getPetTypeID());
        if(templete != NULL){
            
            petData->setPetAttack(calPetAttack(templete->getPetAttack(), petData->getPetLevel(), petData->getPetQuallity()));
            petData->setPetHpMax(calPetHP(templete->getPetHpMax(), petData->getPetLevel(), petData->getPetQuallity()));
            petData->setTemplete(templete);
        }

    }
    else
    {
        MB_PetTemplate* templete = getPetTemplateByID(petData->getPetTypeID());
        if(templete != NULL)
        {
            petData->setTemplete(templete);
        }
    }
    
    m_pPetDataArray->addObject(petData);
    petData->release();
    
    //排序
    sortPetDataArray();
    
    return true;
}

bool MB_PetMgr::sendpet_up_rank(uint64_t srcPetID, uint64_t costPetID)
{
    SOCKET_REQUEST_START(CS_GER_UP_RANK);
    packet->WriteUINT64(srcPetID);
    packet->WriteUINT64(costPetID);
    SOCKET_REQUEST_END(SC_GER_UP_RANK, MB_PetMgr);
    return true;
}

bool MB_PetMgr::recvpet_up_rank(MB_MsgBuffer *recvPacket)
{
    uint8_t result;
    uint64_t srcPetID = 0, costPetID = 0;
    if (recvPacket->readU8(&result))
    {
        MB_Message::sharedMB_Message()->removeALLMessage();
        if (result == 1) {
            MB_LOG("升品成功");
            if (recvPacket->readU64(&srcPetID) && recvPacket->readU64(&costPetID))
            {
                
                MB_PetData *petData = getPetDataByUID(srcPetID);
                petData->getOnlineAttribute()->removeAllObjects();
                
                
                
                MB_PetData *costData = getPetDataByUID(costPetID);
                if(costData != NULL)
                {
                    removePetByUID(costPetID);
                }
                else
                {
                    CCArray* costArray = NULL;
                    MB_PetTemplate* pTemplete = getPetTemplateByID(petData->getPetTypeID());
                    
                    uint16_t rankGodID = 0;
                    if (petData->getPetQuallity() == 10)
                    {
                        rankGodID = pTemplete->getRankGodID();
                        
                    }
                    else if (petData->getPetQuallity() == 20)
                    {
                        rankGodID = pTemplete->getRankSaintID();
                    }
                    
                    for (int i = 0; i < MB_PetMgr::getInstance()->getPetGodArray()->count(); i++)
                    {
                        MB_PetQualityCostSpecialTemplete* costTemplete = (MB_PetQualityCostSpecialTemplete*)getPetGodArray()->objectAtIndex(i);
                        if (costTemplete->getCostID() == petData->getTemplete()->getRankGodID()) {
                            costArray = costTemplete->getCostArray();
                            break;
                        }
                    }
                    //没有找到材料模板
                    if (costArray == NULL) {
                        MB_LOG("Pet rank up err! rank:%d", rankGodID);
                        return true;
                    }
                }
                return true;
            }
        }
        else
        {
            MB_LOG("升品失败,errcode:%d", result);
            if (result == 2) {
                MB_Message::sharedMB_Message()->showMessage("", "升品失败, 精灵已达到最高品阶", "确定");
            }
            else if (result == 3)
            {
                MB_Message::sharedMB_Message()->showMessage("", "升品失败, 主精灵不存在", "确定");
            }
            else if (result == 4)
            {
                MB_Message::sharedMB_Message()->showMessage("", "升品失败, 被吞噬精灵不存在", "确定");
            }
            else if (result == 5)
            {
                MB_Message::sharedMB_Message()->showMessage("", "升品失败, 不是同一种精灵, 不能吞噬", "确定");
            }
            else if (result == 6)
            {
                MB_Message::sharedMB_Message()->showMessage("", "升品失败, 金币不足", "确定");
            }
            else if (result == 8)
            {
                MB_Message::sharedMB_Message()->showMessage("", "升品失败, 材料不足.", "确定");
            }
            else if (result == 9)
            {
                MB_Message::sharedMB_Message()->showMessage("", "升品失败, 不能跨阶升品", "确定");
            }
            else if(result == 12)
            {
                MB_Message::sharedMB_Message()->showMessage("", "炼金工厂守护神不能作为材料", "确定");
            }
            else if(result == 13)
            {
 
                MB_Message::sharedMB_Message()->showMessage("精灵需要转生");
            }
            else
            {
                MB_Message::sharedMB_Message()->showMessage("", "升品失败,请检查您的升品条件.", "确定");
            }
        }
    }
    
    return true;
}
bool MB_PetMgr::recvpet_del(MB_MsgBuffer *recvPacket){
    uint16_t data16;
    uint64_t data64;
    recvPacket->readU16(&data16);
    for (int i = 0; i < data16 ; i++) {
        
        recvPacket->readU64(&data64);
        removePetByUID(data64);
    }
    
    return true;
}

bool MB_PetMgr::recvpet_new_list(MB_MsgBuffer *recvPacket)
{
    //十连抽
    uint16_t len = 0;
    uint16_t data16;
    uint32_t data32;
    uint64_t data64;
    
    if (!recvPacket->readU16(&len))
    {
        return false;
    }
    
    if (len < 1)
    {
        return false;
    }
    
    for (int i = 0; i < len; i++)
    {
        MB_PetData *petData = new MB_PetData();
        
        if (recvPacket->readU64(&data64)) {
            petData->setPetID(data64);
        }
        if (recvPacket->readU16(&data16)) {
            petData->setPetTypeID(data16);
        }
        if (recvPacket->readU16(&data16)) {
            petData->setPetQuallity(data16);
        }
        if (recvPacket->readU16(&data16)) {
            petData->setPetLevel(data16);
        }
        if (recvPacket->readU32(&data32)) {
            petData->setPetAttack(data32);
        }
        if (recvPacket->readU32(&data32)) {
            petData->setPetHpMax(data32);
        }
        if (recvPacket->readU64(&data64)) {
            petData->setPetFightPower(data64);
        }
        if (recvPacket->readU64(&data64)) {
            petData->setPetExp(data64);
        }
        else
        {
            petData->release();
            MB_LOG("parse recvpet_info error.");
            return false;
        }
        if(petData->getPetHpMax() <= 0){
            
            MB_PetTemplate* templete = getPetTemplateByID(petData->getPetTypeID());
            if(templete != NULL){
                
                petData->setPetAttack(calPetAttack(templete->getPetAttack(), petData->getPetLevel(), petData->getPetQuallity()));
                petData->setPetHpMax(calPetHP(templete->getPetHpMax(), petData->getPetLevel(), petData->getPetQuallity()));
                petData->setTemplete(templete);
            }
        }
        else
        {
            MB_PetTemplate* templete = getPetTemplateByID(petData->getPetTypeID());
            if(templete != NULL)
            {
                petData->setTemplete(templete);
            }
        }
        m_pPetDataArray->addObject(petData);
        petData->release();
    }
    
    //排序
    sortPetDataArray();
    
    return true;
}
void MB_PetMgr::onMsgRecv(CCNode* node, SocketResponse* response){
    
    assert(response != NULL);
    
    //将socket数据读取到序列化结构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg) {
            
        case SC_GER_INFO:
            recvpet_info(recvPacket);
            break;
        case SC_GER_SELL:
            recvpet_sell(recvPacket);
            break;
        case SC_GER_UPDATE:
            recvpet_update(recvPacket);
            break;
        case SC_GER_MORE:
            recvpet_ger_more(recvPacket);
            break;
        case SC_GER_UPDATE_EXP:
            recvpet_update_exp(recvPacket);
            break;
        case SC_GER_NEW:
            recvpet_new(recvPacket);
            break;
        case SC_GER_EAT:
            recvpet_eat(recvPacket);
            break;
        case SC_GER_UP_RANK:
            recvpet_up_rank(recvPacket);
            break;
        case SC_GER_DEL:
            recvpet_del(recvPacket);
        case SC_GER_NEW_LIST:
            recvpet_new_list(recvPacket);
            break;
        default:
            break;
    }
}
const char * MB_PetMgr::getPetRealName(char *buf,int64_t petID){
    MB_PetData *t_gData = this->getPetDataByUID(petID);
    //容错处理
    if (t_gData == NULL) {
        sprintf(buf, " ");
        return buf;
    }
    
    MB_PetTemplate *t_gTData = t_gData->getTemplete();
    //容错处理
    if (t_gTData == NULL) {
        sprintf(buf, " ");
        return buf;
    }
    
    std::string Name = "";
    
    if (t_gData->getPetQuallity() >= 20) {
        
        Name = t_gTData->getPetName(SHAPE_3);
        
    }
    else if(t_gData->getPetQuallity() >= 10){
        
        Name = t_gTData->getPetName(SHAPE_2);
    }
    else
    {
        Name = t_gTData->getPetName(SHAPE_1);
    }
    sprintf(buf, "%s",Name.c_str());
    
    int ql = t_gData->getPetQuallity() %10;
    if(ql > 0){
        
        sprintf(buf, "%s +%d",buf,ql);
    }
    return buf;
    
}
const char * MB_PetMgr::getPetRealNameNoSpace(char *buf,int64_t petID){
    MB_PetData *t_gData = this->getPetDataByUID(petID);
    //容错处理
    if (t_gData == NULL) {
        sprintf(buf, " ");
        return buf;
    }
    
    MB_PetTemplate *t_gTData = t_gData->getTemplete();
    //容错处理
    if (t_gTData == NULL) {
        sprintf(buf, " ");
        return buf;
    }
    
    std::string Name = "";
    
    if (t_gData->getPetQuallity() >= 20) {
        
        Name = t_gTData->getPetName(SHAPE_3);
        
    }
    else if(t_gData->getPetQuallity() >= 10){
        
        Name = t_gTData->getPetName(SHAPE_2);
    }
    else
    {
        Name = t_gTData->getPetName(SHAPE_1);
    }
    sprintf(buf, "%s",Name.c_str());
    int ql = t_gData->getPetQuallity() %10;
    if(ql > 0){
        
        sprintf(buf, "%s+%d",buf,ql);
    }
    return buf;
    
}

const char * MB_PetMgr::getPetRealNameWithType(char *buf,int16_t petType){
    MB_PetTemplate *t_gTData = this->getPetTemplateByID(petType);
    //容错处理
    if (t_gTData == NULL) {
        sprintf(buf, " ");
        return buf;
    }
    
    sprintf(buf, "%s",t_gTData->getPetName(SHAPE_1));
    return buf;
}

const char * MB_PetMgr::getPetRealNameWithType(char *buf,int16_t petType,int16_t petShape){
    MB_PetTemplate *t_gTData = this->getPetTemplateByID(petType);
    //容错处理
    if (t_gTData == NULL) {
        sprintf(buf, " ");
        return buf;
    }
    
    sprintf(buf, "%s",t_gTData->getPetName(petShape));
    return buf;
}


const char* MB_PetMgr::getPetRealName(uint16_t petTypeID, uint16_t petQuality)
{
    char* buf = new char[64];
    MB_PetTemplate* petTemplete = getPetTemplateByID(petTypeID);
    //容错处理
    if (petTemplete == NULL) {
        sprintf(buf, " ");
        return buf;
    }
    
    if (petQuality >= 20)
    {
        sprintf(buf, "%s", petTemplete->getPetName(SHAPE_3));
    }
    else if (petQuality >= 10)
    {
        sprintf(buf, "%s", petTemplete->getPetName(SHAPE_2));
    }
    else
    {
        sprintf(buf, "%s", petTemplete->getPetName(SHAPE_1));
    }
    int ql = petQuality %10;
    if(ql > 0){
        
        sprintf(buf, "%s +%d",buf,ql);
    }
    
    return buf;
}

MB_PetQualityCostTemplete::MB_PetQualityCostTemplete()
{
    m_nStar = 0;
    m_nQuality = 0;
    m_nCoin = 0;
}

MB_PetQualityCostSpecialTemplete::MB_PetQualityCostSpecialTemplete()
{
    m_uCostID = 0;
    m_pCostArray = CCArray::create();
    m_pCostArray->retain();
}

MB_PetQualityCostSpecialTemplete::~MB_PetQualityCostSpecialTemplete()
{
    CC_SAFE_RELEASE_NULL(m_pCostArray);
}

MB_PetQualityCostSpecialTempleteValue::MB_PetQualityCostSpecialTempleteValue()
{
    m_uItemTypeID = 0;
    m_uNum = 0;
}

const char *  MB_SkillData::getSkillName(){
    
    return  m_strSkillName.c_str();
}
const char * MB_SkillData::getSkillIcon(){
    
    return m_strSkillIcon.c_str();
}
const char * MB_SkillData::getSkillDescription(){
    
    return  m_strSkillDescription.c_str();
}
void MB_SkillData::setSkillName( const char *skillName){
    
    m_strSkillName = skillName;
}
void MB_SkillData::setSkillIcon( const char *skillIcon){
    
    m_strSkillIcon = skillIcon;
}
void MB_SkillData::setSkillDescription(const char * skillDescription){
    
    m_strSkillDescription = skillDescription;
}

MB_SkillMgr * MB_SkillMgr::m_pSharedSkillMgr = NULL;

MB_SkillMgr::MB_SkillMgr(){
    initSkillData();
}
MB_SkillMgr::~MB_SkillMgr(){
    
    SkillMap::iterator itr =  m_mapSkill.begin();
    SkillMap::iterator end =  m_mapSkill.end();
    while (itr != end) {
        
        CC_SAFE_RELEASE(itr->second);
        itr++;
    }
    
}
void MB_SkillMgr::initSkillData(){
    
    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/skill/skill.xml");
    
    if (!g_sharedDoc)
    {
        return ;
    }
    
    xmlNodePtr root;
    root=xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    while(curNode != NULL) {
        
        if (xmlStrcmp(curNode->name,BAD_CAST "skill")) {
            
            curNode = curNode->next;
            continue;
        }
        MB_SkillData * data = new MB_SkillData();
        for ( struct _xmlAttr * attr = curNode->properties; attr != NULL ; attr = attr->next ) {
            
            
            if (!xmlStrcmp(attr->name,BAD_CAST "skillID")){
                
                value = (char*)xmlNodeGetContent(attr->children);
                data->setSkillID(atoi(value));
                CC_SAFE_FREE(value);
                
            }else  if (!xmlStrcmp(attr->name,BAD_CAST "skillName")){
                
                value = (char*)xmlNodeGetContent(attr->children);
                data->setSkillName(value);
                CC_SAFE_FREE(value);
                
            }else  if (!xmlStrcmp(attr->name,BAD_CAST "skillIcon")){
                
                value = (char*)xmlNodeGetContent(attr->children);
                data->setSkillIcon(value);
                CC_SAFE_FREE(value);
                
            }else  if (!xmlStrcmp(attr->name,BAD_CAST "skillDescription")){
                
                value = (char*)xmlNodeGetContent(attr->children);
                data->setSkillDescription(value);
                CC_SAFE_FREE(value);
                
            }
            
        }
        
        m_mapSkill.insert(SkillMapEntry(data->getSkillID(),data));
        curNode = curNode->next;
    }
    
    xmlFreeDoc(g_sharedDoc);
}
MB_SkillData * MB_SkillMgr::getSkillDataByID(int skillID){
    
    
    SkillMap::iterator skillDataIterator = m_mapSkill.find(skillID);
    if ( skillDataIterator!= m_mapSkill.end()) {
        
        return skillDataIterator->second;
    }
    else
    {
        MB_LOG("ID:%d skill not exist.", skillID);
        return  NULL;
    }
    
    
}
MB_SkillMgr * MB_SkillMgr::getInstance(){
    
    if (m_pSharedSkillMgr == NULL) {
        
        m_pSharedSkillMgr = new MB_SkillMgr();
    }
    
    return m_pSharedSkillMgr;
}
void MB_SkillMgr::purgeData(){
    
    if (m_pSharedSkillMgr != NULL){
        
        delete m_pSharedSkillMgr;
    }
    m_pSharedSkillMgr = NULL;
}

MB_DestinyAttribute::MB_DestinyAttribute(){
}
MB_DestinyAttribute::~MB_DestinyAttribute(){
    
}
const char * MB_DestinyAttribute::getName(){
    
    return m_strName.c_str();
}
void MB_DestinyAttribute::setName(const char * name){
    
    m_strName = name;
}
MB_DestinyData::MB_DestinyData(){
    DestinyAttributeArrary = new CCArray();
}
MB_DestinyData::~MB_DestinyData(){
    
    DestinyAttributeArrary->removeAllObjects();
    delete DestinyAttributeArrary;
}
const char * MB_DestinyData::getDestinyName(){
    
    return m_strDestinyName.c_str();
}
void MB_DestinyData::setDestinyName(const char *destinyName){
    
    m_strDestinyName = destinyName;
}
CCArray * MB_DestinyData::getDestinyAttributeArray(){
    
    return  DestinyAttributeArrary;
}


MB_DestinyMgr::MB_DestinyMgr(){
    
    initDestinyData();
}
MB_DestinyMgr::~MB_DestinyMgr(){
    
    DestinyDataMap::iterator itr = m_mapDestiny.begin();
    DestinyDataMap::iterator end = m_mapDestiny.end();
    while (itr != end) {
        
        CC_SAFE_RELEASE(itr->second);
        itr++;
    }
    
}
void MB_DestinyMgr::initDestinyData(){
    
    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/Bond.xml");
    
    if (!g_sharedDoc)
    {
        return ;
    }
    
    xmlDocPtr g_sharedDoc2 = MB_XmlReader::readXml("config/description/card_property.xml");
    
    xmlNodePtr root;
    root=xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    while(curNode != NULL) {
        
        if (xmlStrcmp(curNode->name,BAD_CAST "destiny")) {
            
            curNode = curNode->next;
            continue;
        }
        MB_DestinyData * data = new  MB_DestinyData();
        for ( struct _xmlAttr * attr = curNode->properties; attr != NULL ; attr = attr->next ) {
            
            if (!xmlStrcmp(attr->name,BAD_CAST "destinyID")){
                
                value = (char*)xmlNodeGetContent(attr->children);
                data->setDestinyID(atoi(value));
                CC_SAFE_FREE(value);
                
            }else  if (!xmlStrcmp(attr->name,BAD_CAST "destinyName")){
                
                value = (char*)xmlNodeGetContent(attr->children);
                data->setDestinyName(value);
                CC_SAFE_FREE(value);
                
            }else  if (!xmlStrcmp(attr->name,BAD_CAST "destinyType")){
                
                value = (char*)xmlNodeGetContent(attr->children);
                data->setDestinyType(atoi(value));
                CC_SAFE_FREE(value);
                
            }else  if (!xmlStrcmp(attr->name,BAD_CAST "destinyNeed1")){
                
                value = (char*)xmlNodeGetContent(attr->children);
                data->setDestinyNeed1(atoi(value));
                CC_SAFE_FREE(value);
                
            }else  if (!xmlStrcmp(attr->name,BAD_CAST "destinyNeed2")){
                
                value = (char*)xmlNodeGetContent(attr->children);
                data->setDestinyNeed2(atoi(value));
                CC_SAFE_FREE(value);
                
            }else  if (!xmlStrcmp(attr->name,BAD_CAST "destinyNeed3")){
                
                value = (char*)xmlNodeGetContent(attr->children);
                data->setDestinyNeed3(atoi(value));
                CC_SAFE_FREE(value);
                
            }else  if (!xmlStrcmp(attr->name,BAD_CAST "destinyNeed4")){
                
                value = (char*)xmlNodeGetContent(attr->children);
                data->setDestinyNeed4(atoi(value));
                CC_SAFE_FREE(value);
                
            }
            
        }
        
        for ( xmlNodePtr child = curNode->xmlChildrenNode; child != NULL; child = child->next ) {
            
            if (xmlStrcmp(child->name,BAD_CAST "Attribute"))
            {    
                continue;
            }
            MB_DestinyAttribute * attribute = new MB_DestinyAttribute();
            for (struct _xmlAttr * attr = child->properties; attr != NULL ; attr = attr->next) {
                
                if (!xmlStrcmp(attr->name,BAD_CAST "Type")){
                    
                    value = (char*)xmlNodeGetContent(attr->children);
                    attribute->setType(atoi(value));
                    CC_SAFE_FREE(value);
                    
                }else  if (!xmlStrcmp(attr->name,BAD_CAST "Value")){
                    
                    value = (char*)xmlNodeGetContent(attr->children);
                    attribute->setValue(atof(value));
                    CC_SAFE_FREE(value);
                    
                }
                
            }
            getDestinyAttribute(attribute, g_sharedDoc2);
            data->getDestinyAttributeArray()->addObject(attribute);
            attribute->release();
        }
        
        
        m_mapDestiny.insert(DestinyDataEntry(data->getDestinyID(),data));
        curNode = curNode->next;
    }
    
    xmlFreeDoc(g_sharedDoc);
    xmlFreeDoc(g_sharedDoc2);
}
void  MB_DestinyMgr::getDestinyAttribute(MB_DestinyAttribute *attribute,xmlDoc *doc){
    
    xmlNodePtr root;
    root=xmlDocGetRootElement(doc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    while(curNode != NULL) {
        
        if (xmlStrcmp(curNode->name,BAD_CAST "Attribute")) {
            
            curNode = curNode->next;
            continue;
        }
        
        for ( struct _xmlAttr * attr = curNode->properties; attr != NULL ; attr = attr->next ) {
            
            if (!xmlStrcmp(attr->name,BAD_CAST "Type")){
                
                value = (char*)xmlNodeGetContent(attr->children);
                int type = atoi(value);
                CC_SAFE_FREE(value);
                if(type != attribute->getType()){
                    
                    break;
                }
                
                
            }else  if (!xmlStrcmp(attr->name,BAD_CAST "Name")){
                
                value = (char*)xmlNodeGetContent(attr->children);
                attribute->setName(value);
                CC_SAFE_FREE(value);
                return;
            }
        }
        
        curNode = curNode->next;
        
    }
    
}
MB_DestinyData * MB_DestinyMgr::getDestinyDataByID(int destinyID){
    
    DestinyDataMap::iterator destinyDataIterator = m_mapDestiny.find(destinyID);
    if ( destinyDataIterator !=  m_mapDestiny.end()) {
        
        return destinyDataIterator->second;
    }
    else
    {
        MB_LOG("ID:%d destiny not exist.", destinyID);
        return  NULL;
    }
    
}
MB_DestinyMgr * MB_DestinyMgr::getInstance(){
    
    if (m_pSharedDestinyMgr == NULL) {
        
        m_pSharedDestinyMgr = new  MB_DestinyMgr();
    }
    
    return m_pSharedDestinyMgr;
    
}
void MB_DestinyMgr::purgeData(){
    
    if (m_pSharedDestinyMgr != NULL) {
        
        delete m_pSharedDestinyMgr;
    }
    
    m_pSharedDestinyMgr = NULL;
}
MB_DestinyMgr *  MB_DestinyMgr::m_pSharedDestinyMgr = NULL;
