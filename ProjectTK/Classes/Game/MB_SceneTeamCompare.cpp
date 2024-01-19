
#include "MB_SceneTeamCompare.h"
#include "MB_LayerEqCompare.h"
#include "MB_NodeReplayPetUnite.h"
#include "MB_SceneGame.h"
#include "MB_FunctionModule.h"
#include "MB_NodeShow.h"
USING_NS_CC;
USING_NS_CC_EXT;

//pvp排行逻辑功能类
MB_SceneTeamCompare_Old::MB_SceneTeamCompare_Old()
{
    m_pOur_pos = NULL;
    m_pEnemy_pos = NULL;
    m_bIsPopScene = false;
    m_pRoleName = NULL;
    m_pNodeOtherLv = NULL;
    m_pNodeSelfLv = NULL;
}

MB_SceneTeamCompare_Old::~MB_SceneTeamCompare_Old()
{
    CC_SAFE_RELEASE(m_pData);
    CC_SAFE_RELEASE(m_pOur_pos);
    CC_SAFE_RELEASE(m_pEnemy_pos);
    CC_SAFE_RELEASE_NULL(m_pRoleName);
    CC_SAFE_RELEASE_NULL(m_pNodeOtherLv);
    CC_SAFE_RELEASE_NULL(m_pNodeSelfLv);
    SOCKET_MSG_UNREGIST(SC_GER_VIEW_OTHER_DTL);
}

CCScene* MB_SceneTeamCompare_Old::scene(MB_DataTeamCompare* data,bool bIs3v3Match)
{
    CCScene *scene=CCScene::create();
    CCLayer *node = MB_SceneTeamCompare_Old::create(data,bIs3v3Match);
    scene->addChild(node);
    return scene;
}

MB_SceneTeamCompare_Old* MB_SceneTeamCompare_Old::create(MB_DataTeamCompare* data,bool bIs3v3Match)
{
    MB_SceneTeamCompare_Old* layer = new MB_SceneTeamCompare_Old();
    if (layer != NULL && layer->init(data,bIs3v3Match)) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}

// on "init" you need to initialize your instance
bool MB_SceneTeamCompare_Old::init(MB_DataTeamCompare* data,bool bIs3v3Match)
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    m_pData = data;
    m_pData->retain();
    
    //init CCBReader
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode *pScene = pCCBReader->readNodeGraphFromFile("res/formation_layer_compare.ccbi", this);
    this->addChild(pScene);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    int i;
    //敌人精灵
    for (i  = 0; i < m_pData->getTeamArray()->count(); ++i) {
        MB_PetData* petData = (MB_PetData*)m_pData->getTeamArray()->objectAtIndex(i);
        CCPoint pos = ccpSub(CCPointMake(m_pEnemy_pos->getContentSize().width/2, m_pEnemy_pos->getContentSize().height/2), CCPointMake(0, m_pEnemy_pos->getContentSize().height*i));
        
        MB_NodeTeamCompare_Old* pNode = MB_NodeTeamCompare_Old::create(petData, pos,bIs3v3Match);
        pNode->setRoleID(m_pData->getRoleID());
        m_pEnemy_pos->addChild(pNode);
    }
    //自己精灵
    int posOffset = 0;
    for (i  = 0; i < MEMBER_NUM; ++i) {
        MB_PetData* petData = MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet;
        if (petData == NULL) {
            posOffset--;
            continue;
        }
        CCPoint pos = ccpSub(CCPointMake(m_pOur_pos->getContentSize().width/2, m_pOur_pos->getContentSize().height/2) , CCPointMake(0, m_pOur_pos->getContentSize().height * (i + posOffset)));
        MB_NodeTeamCompare_Old* pNode = MB_NodeTeamCompare_Old::create(petData, pos);
        pNode->setRoleID(MB_RoleData::getInstance()->getUID());
        m_pOur_pos->addChild(pNode);
    }
        
    if(MB_TeamData::getInstance()->getLastServerID() == 0 || bIs3v3Match)
    {
        m_pRoleName->setString(m_pData->getRoleName());
        
    }else {
        m_pRoleName->setString(m_pData->getRoleName());
//        char databuf[100];
//        ServerList * server = MB_ServerList::getInstance()->getServerListByID(MB_TeamData::getInstance()->getLastServerID());
//        sprintf(databuf, "%s[%s]",m_pData->getRoleName(),server->name.c_str());
//        m_pRoleName->setString(databuf);
    }

    //玩家等级 没有等级数据
    char buff[64] = "";
    sprintf(buff,"%d",m_pData->getRoleLevel());
    m_pNodeOtherLv->setString(buff);
    
    sprintf(buff,"%d",MB_RoleData::getInstance()->getLevel());
    m_pNodeSelfLv->setString(buff);
    
	return true;
}

bool MB_SceneTeamCompare_Old::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "enemy_role_name", CCLabelTTF*, m_pRoleName);

    if (strcmp(pMemberVariableName, "enemy_role_power") == 0 && pTarget == this)
    {
        char* str = new char[32];
        sprintf(str, "%llu", m_pData->getRoleFightPower());
        ((CCLabelTTF*)pNode)->setString(str);
        CC_SAFE_DELETE_ARRAY(str);
        return true;
    }
    else if (strcmp(pMemberVariableName, "my_role_name") == 0 && pTarget == this)
    {
        
        if(MB_TeamData::getInstance()->getLastServerID() == 0){
            
            ((CCLabelTTF*)pNode)->setString(MB_RoleData::getInstance()->getName());
            
        }else {
            ((CCLabelTTF*)pNode)->setString(MB_RoleData::getInstance()->getName());
//            char databuf[100];
//            ServerList * server = MB_ServerList::getInstance()->getServerListByID( MB_ServerList::getInstance()->getNowServerID());
//            sprintf(databuf, "%s[%s]",MB_RoleData::getInstance()->getName(),server->name.c_str());
//            ((CCLabelTTF*)pNode)->setString(databuf);
        }
        return true;
    }
    else if (strcmp(pMemberVariableName, "my_role_power") == 0 && pTarget == this)
    {
        char* str = new char[32];
        sprintf(str, "%llu", MB_TeamData::getInstance()->getFightPower());
        ((CCLabelTTF*)pNode)->setString(str);
        CC_SAFE_DELETE_ARRAY(str);
        return true;
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "enemy_pos", CCNode*, m_pEnemy_pos);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "my_pos", CCNode*, m_pOur_pos);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeOtherLv", CCLabelBMFont*, m_pNodeOtherLv);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeSelfLv", CCLabelBMFont*, m_pNodeSelfLv);
    
    return true;
}

SEL_MenuHandler MB_SceneTeamCompare_Old::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_SceneTeamCompare_Old::onBackClicked);
    return NULL;
}
SEL_CCControlHandler MB_SceneTeamCompare_Old::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onTeamClicked", MB_SceneTeamCompare_Old::onTeamClicked);
    
    return NULL;
}

void MB_SceneTeamCompare_Old::onTeamClicked(cocos2d::CCObject *pSender)
{
    MB_LOG("onTeamClicked.");
}

void MB_SceneTeamCompare_Old::onBackClicked(cocos2d::CCObject *pSender)
{
    if (!m_bIsPopScene) {
        m_bIsPopScene = true;
        removeFromParent();
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }
}
void MB_NodeTeamCompare_Old::onMsgRecv(CCNode* node, SocketResponse* response){
    
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
//        case SC_TEAM_VIEW_OTHER_DTL:
//        {
//            onPetTeamDataDtl(recvPacket);
//            SOCKET_MSG_UNREGIST(SC_TEAM_VIEW_OTHER_DTL);
//        }
//            break;
        case SC_GER_VIEW_OTHER_DTL:
        {
            onPetTeamDataDtl(recvPacket);
            SOCKET_MSG_UNREGIST(SC_GER_VIEW_OTHER_DTL);
        }
            break;
        default:
            break;
    }
}

void MB_NodeTeamCompare_Old::onPetTeamDataDtl(MB_MsgBuffer* recvPacket)
{
    uint16_t data16;
    uint32_t data32;
    uint64_t data64;
    uint8_t data8;
    char *str;
    std::string fullname;
    recvPacket->readU32(&data32);//冒险家id
    str = recvPacket->ReadString();//冒险家名字
    if(str != NULL)fullname = str;
    CC_SAFE_FREE(str);
    
    recvPacket->readU16(&data16);//等级
    recvPacket->readU64(&data64);//战斗力
    TeamDataStruct *temaData[6];
    for (int i = 0 ; i < CARD_IN_GAME; i++) {
        
        temaData[i] = new TeamDataStruct;
        temaData[i]->m_pPet = NULL;
        temaData[i]->m_pEquip1 = NULL;
        temaData[i]->m_pEquip2 = NULL;
        temaData[i]->m_pEquip3 = NULL;
        temaData[i]->m_pTreasure1 = NULL;
        temaData[i]->m_pTreasure2 = NULL;
        temaData[i]->m_pTreasure3 = NULL;
        temaData[i]->m_pTreasure4 = NULL;
        temaData[i]->m_pTreasure5 = NULL;
        temaData[i]->m_pTreasure6 = NULL;
        temaData[i]->m_pTreasure7 = NULL;
        temaData[i]->m_pTreasure8 = NULL;
        
    }
    uint16_t petList;
    recvPacket->readU16(&petList);
    for (int i = 0; i < petList; i++) {
        
        MB_PetData * data = new MB_PetData();
        recvPacket->readU64(&data64);
        data->setPetID(data64);
        recvPacket->readU16(&data16);
        data->setPetTypeID(data16);
        recvPacket->readU16(&data16);
        data->setPetQuallity(data16);
        recvPacket->readU16(&data16);
        data->setPetLevel(data16);
        recvPacket->readU32(&data32);
        data->setPetAttack(data32);
        recvPacket->readU32(&data32);
        data->setPetHpMax(data32);
        recvPacket->readU64(&data64);
        data->setPetFightPower(data64);
        recvPacket->readU64(&data64);
        data->setPetExp(data64);
        temaData[i]->m_pPet = data;
        CCLog("pet pos %d",i);
        
    }
    uint16_t eqList;
    recvPacket->readU16(&eqList);
    for (int i = 0; i < eqList; i++) {
        
        MB_ItemData *data = new MB_ItemData();
        recvPacket->readU64(&data64);
        data->setItemPetID(data64);
        recvPacket->readU16(&data16);
        data->setItemID(data16);
        recvPacket->readU8(&data8);
        data->setItemLevel(data8);
        recvPacket->readU8(&data8);
        data->setItemRank(data8);
        recvPacket->readU64(&data64);
        data->setItemPetID(data64);
        recvPacket->readU8(&data8);
        data->setItemPos(data8);
        recvPacket->readU32(&data32);
        data->setItemRankOverTim(data32);
        recvPacket->readU16(&data16);
        data->setExp(data16);
        for (int i = 0 ; i < CARD_IN_GAME; i++) {
            
            if(temaData[i]->m_pPet != NULL && temaData[i]->m_pPet->getPetID() == data->getItemPetID()){
                
                if(data->getItemPos() == kItemPosEquip1){
                    
                    temaData[i]->m_pEquip1 = data;
                    
                }else if(data->getItemPos() == kItemPosEquip2){
                    
                    temaData[i]->m_pEquip2 = data;
                    
                }else if(data->getItemPos() == kItemPosEquip3){
                    
                    temaData[i]->m_pEquip3 = data;
                }
                if(data->getItemPos() == kItemPosTreasure1){
                    
                    temaData[i]->m_pTreasure1 = data;
                    
                }else if(data->getItemPos() == kItemPosTreasure2){
                    
                    temaData[i]->m_pTreasure2= data;
                    
                }else if(data->getItemPos() == kItemPosTreasure3){
                    
                    temaData[i]->m_pTreasure3= data;
                }
                if(data->getItemPos() ==kItemPosTreasure4){
                    
                    temaData[i]->m_pTreasure4= data;
                    
                }else if(data->getItemPos() == kItemPosTreasure5){
                    
                    temaData[i]->m_pTreasure5 = data;
                    
                }else if(data->getItemPos() == kItemPosTreasure6){
                    
                    temaData[i]->m_pTreasure7 = data;
                    
                }else if(data->getItemPos() == kItemPosTreasure7){
                    
                    temaData[i]->m_pTreasure7 = data;
                    
                }else if(data->getItemPos() == kItemPosTreasure8){
                    
                    temaData[i]->m_pTreasure8= data;
                }
            }
        }
    }
    uint16_t posList;
    recvPacket->readU16(&posList);
    
    for (int i = 0; i < posList; i++) {
        
        uint64_t petid;
        recvPacket->readU64(&petid);
        uint8_t pos;
        recvPacket->readU8(&pos);
        pos--;
        for (int j = 0 ; j < CARD_IN_GAME; j++) {
            
            if(temaData[j]->m_pPet && temaData[j]->m_pPet->getPetID() == petid){
                
                if(j != pos ){
                    
                    TeamDataStruct * temp = temaData[j];
                    temaData[j] = temaData[pos];
                    temaData[pos] = temp;
                    break;
                    
                }
                
            }
        }
    }
    int index = 0;
    for (int i = 0 ; i < CARD_IN_GAME; i++) {
        
        if(temaData[i]->m_pPet){
            
            
            if(temaData[i]->m_pPet->getPetTypeID() == m_nPetType ){
                
                break;
            }
            index ++;

        }
    }
    uint16_t atkadd;
    uint16_t hpadd;
    recvPacket->readU16(&atkadd);
    recvPacket->readU16(&hpadd);
    CCArray *array = CCArray::create();
    uint16_t list;
    recvPacket->readU16(&list);
    for (int i = 0; i < list; i++) {
        
        recvPacket->skipU16();
//        Lieu_ViewData * lvdata = new Lieu_ViewData();
//        array->addObject(lvdata);
//        lvdata->release();
//        
//        
//        recvPacket->readU16(&data16);
//        lvdata->setPetType(data16);
        
        
    }
    
    MB_LayerEqCompare *layer = MB_LayerEqCompare::create(temaData,array,index, fullname.c_str(),atkadd,hpadd);
    for (int i = 0; i < CARD_IN_GAME; i++) {
        
        delete temaData[i];
    }
    CC_SAFE_DELETE_ARRAY(str);
    MB_TARGET_PARENT(MB_SceneTeamCompare, ptr){
        if (ptr) {
            ptr->addChild(layer);
        }
        
    }
}
//比较界面精灵node实现
MB_NodeTeamCompare_Old::MB_NodeTeamCompare_Old()
{
    m_bIs3v3Match = false;
    m_pNodeIcon = NULL;
}

MB_NodeTeamCompare_Old::~MB_NodeTeamCompare_Old()
{
      SOCKET_MSG_UNREGIST(SC_GER_VIEW_OTHER_DTL);
    CC_SAFE_RELEASE_NULL(m_pNodeIcon);

}

MB_NodeTeamCompare_Old* MB_NodeTeamCompare_Old::create(MB_PetData *petData, cocos2d::CCPoint pos,bool bIs3v3Match)
{
    MB_NodeTeamCompare_Old* pNode = new MB_NodeTeamCompare_Old();
    if (pNode != NULL && pNode->init(petData, pos, bIs3v3Match)) {
        pNode->autorelease();
        return pNode;
    }
    CC_SAFE_DELETE(pNode);
    return NULL;
}

bool MB_NodeTeamCompare_Old::init(MB_PetData *petData, cocos2d::CCPoint pos,bool bIs3v3Match)
{
    m_bIs3v3Match = false;
    m_nPetType = petData->getPetTypeID();
     const char *petName = MB_PetMgr::getInstance()->getPetRealName(petData->getPetTypeID(), petData->getPetQuallity());
    m_sPetName = petName;
    CC_SAFE_DELETE(petName);
    
    CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/formation_node_compare.ccbi", this);
    pNode->setPosition(pos);
    this->addChild(pNode);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    MB_NodePet* pNodePet = MB_NodePet::create(m_nPetType,petData->getPetLevel(),petData->getPetQuallity());
    pNodePet->showLevel(false);
    pNodePet->showName(false);
    m_pNodeIcon->addChild(pNodePet);
    
    return true;
}
void MB_NodeTeamCompare_Old::onDel2Clicked(CCObject *){

    onDel1Clicked(NULL);
}
void MB_NodeTeamCompare_Old::onDel1Clicked(CCObject *)
{
    SOCKET_MSG_REGIST(SC_GER_VIEW_OTHER_DTL,MB_NodeTeamCompare_Old);
    MB_TeamData::getInstance()->sendpet_view_other_dtl(m_nRoleID,m_nRoleID == MB_RoleData::getInstance()->getUID()? 0 : MB_TeamData::getInstance()->getLastServerID());
}
bool MB_NodeTeamCompare_Old::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    if (strcmp(pMemberVariableName, "name") == 0 && pTarget == this) {
        ((CCLabelTTF*)pNode)->setString(m_sPetName.c_str());
//        CCNodeRGBA pDest;
//        NSGameHelper::setQualityColor(&pDest,(MB_PetMgr::getInstance()->getPetTemplateByID(m_nPetType))->getPetStar());
//        ((CCLabelTTF*)pNode)->setColor(pDest.getColor());
    }
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeIcon",CCNode*,m_pNodeIcon);
    return true;
}


SEL_MenuHandler MB_NodeTeamCompare_Old::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onDel1Clicked",MB_NodeTeamCompare_Old::onDel1Clicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onDel2Clicked",MB_NodeTeamCompare_Old::onDel2Clicked);
    return NULL;
}

SEL_CCControlHandler MB_NodeTeamCompare_Old::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}




///
MB_SceneTeamCompare::MB_SceneTeamCompare():m_pDataSefCp(NULL){}
MB_SceneTeamCompare::~MB_SceneTeamCompare(){CC_SAFE_RELEASE_NULL(m_pDataSefCp);}

CCScene* MB_SceneTeamCompare::scene(MB_DataTeamCompare* data)
{
    CCScene *scene=CCScene::create();
    CCLayer *node = MB_SceneTeamCompare::create(data);
    scene->addChild(node);
    return scene;
}
MB_SceneTeamCompare* MB_SceneTeamCompare::create(MB_DataTeamCompare* petData)
{
    MB_SceneTeamCompare* layer = new MB_SceneTeamCompare();
    if (layer != NULL && layer->init(petData)) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}

MB_SceneTeamCompare* MB_SceneTeamCompare::create(MB_DataTeamCompare* data0,MB_DataTeamCompare* data1)
{
    MB_SceneTeamCompare* layer = new MB_SceneTeamCompare();
    if (layer != NULL && layer->init(data0,data1)) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}


// on "init" you need to initialize your instance
bool MB_SceneTeamCompare::init(MB_DataTeamCompare* data)
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    m_pData = data;
    m_pData->retain();
    
    //init CCBReader
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode *pScene = pCCBReader->readNodeGraphFromFile("res/formation_layer_compare.ccbi", this);
    this->addChild(pScene);
    CC_SAFE_RELEASE_NULL(pCCBReader);
  
    if(global_sceneGame==NULL)
    {
        int i;
        //敌人精灵
        for (i  = 0; i < m_pData->getTeamArray()->count(); ++i) {
            MB_PetData* petData = (MB_PetData*)m_pData->getTeamArray()->objectAtIndex(i);
            MB_NodeReplayPetUnite * node = MB_NodeReplayPetUnite::create(petData->getPetTypeID(),petData->getPetQuallity(),petData->getPetLevel(), false);
            node->setPet(petData->getPetTypeID(),petData->getPetQuallity());
            m_pEnemy_pos->addChild(node);
            node->setPosition(ccp(66+node->getContentSize().width*i,40));
        }
        //自己精灵
        for (i  = 0; i < MEMBER_NUM; ++i) {
            MB_PetData* petData = MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet;
            if (petData) {
                MB_NodeReplayPetUnite * node = MB_NodeReplayPetUnite::create(petData->getPetTypeID(),petData->getPetQuallity(),petData->getPetLevel(), false);
                node->setPet(petData->getPetTypeID(),petData->getPetQuallity());
                m_pOur_pos->addChild(node);
                node->setPosition(ccp(66+node->getContentSize().width*i,40));
            }
        }
    }else
    {
        for (int i = 0 ; i  < 6 ; i++) {
            MB_NodeShow *m_pData = global_sceneGame->getActorByindexAndType(i, 1);
            if(m_pData){
                MB_NodeReplayPetUnite * node = MB_NodeReplayPetUnite::create(m_pData->getFighter()->petTypeID, m_pData->getFighter()->petQuality,m_pData->getFighter()->petLevel, m_pData->getFighter()->petHp <= 0);
                node->setPet(m_pData->getFighter()->petTypeID,m_pData->getFighter()->petQuality);
                m_pOur_pos->addChild(node);
                node->setPosition(ccp(66+node->getContentSize().width*i,40));
            }
        }
        for (int i = 0; i < 6; i++) {
            
            MB_NodeShow *m_pData = global_sceneGame->getActorByindexAndType(i, 0);
            if(m_pData){
                MB_NodeReplayPetUnite * node = MB_NodeReplayPetUnite::create(m_pData->getFighter()->petTypeID, m_pData->getFighter()->petQuality,m_pData->getFighter()->petLevel, m_pData->getFighter()->petHp <= 0);
                node->setPet(m_pData->getFighter()->petTypeID,m_pData->getFighter()->petQuality);
                m_pEnemy_pos->addChild(node);
                node->setPosition(ccp(66+node->getContentSize().width*i,40));
            }
        }
    }
    if(MB_TeamData::getInstance()->getLastServerID() == 0)
    {
        m_pRoleName->setString(m_pData->getRoleName());
        
    }else {
        m_pRoleName->setString(m_pData->getRoleName());
    }
    
    //玩家等级 没有等级数据
    char buff[64] = "";
    sprintf(buff,"%d",m_pData->getRoleLevel());
    m_pNodeOtherLv->setString(buff);
    
    sprintf(buff,"%d",MB_RoleData::getInstance()->getLevel());
    m_pNodeSelfLv->setString(buff);
	return true;
}


bool MB_SceneTeamCompare::init(MB_DataTeamCompare* data,MB_DataTeamCompare* data1)
{
    //////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    m_pData = data;
    m_pData->retain();
    
    m_pDataSefCp = data1;
    m_pDataSefCp->retain();
    
    //init CCBReader
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode *pScene = pCCBReader->readNodeGraphFromFile("res/formation_layer_compare.ccbi", this);
    this->addChild(pScene);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    for (int i = 0 ; i  < 6 ; i++) {
        MB_NodeShow *m_pData = global_sceneGame->getActorByindexAndType(i, 1);
        if(m_pData){
            MB_NodeReplayPetUnite * node = MB_NodeReplayPetUnite::create(m_pData->getFighter()->petTypeID, m_pData->getFighter()->petQuality,m_pData->getFighter()->petLevel, m_pData->getFighter()->petHp <= 0);
            node->setPet(m_pData->getFighter()->petTypeID,m_pData->getFighter()->petQuality);
            m_pOur_pos->addChild(node);
            node->setPosition(ccp(66+node->getContentSize().width*i,40));
        }
    }
    for (int i = 0; i < 6; i++) {
        
        MB_NodeShow *m_pData = global_sceneGame->getActorByindexAndType(i, 0);
        if(m_pData){
            MB_NodeReplayPetUnite * node = MB_NodeReplayPetUnite::create(m_pData->getFighter()->petTypeID, m_pData->getFighter()->petQuality,m_pData->getFighter()->petLevel, m_pData->getFighter()->petHp <= 0);
            node->setPet(m_pData->getFighter()->petTypeID,m_pData->getFighter()->petQuality);
            m_pEnemy_pos->addChild(node);
            node->setPosition(ccp(66+node->getContentSize().width*i,40));
        }
    }
    
    m_pRoleName->setString(m_pData->getRoleName());
    
    
    //玩家等级 没有等级数据
    char buff[64] = "";
    sprintf(buff,"%d",m_pData->getRoleLevel());
    m_pNodeOtherLv->setString(buff);
    
    sprintf(buff,"%d",MB_RoleData::getInstance()->getLevel());
    m_pNodeSelfLv->setString(buff);
	return true;
}

CCScene* MB_SceneTeamCompare::scene(MB_DataTeamCompare* data0,MB_DataTeamCompare* data1)
{
    CCScene *scene=CCScene::create();
    CCLayer *node = MB_SceneTeamCompare::create(data0,data1);
    scene->addChild(node);
    return scene;
}
