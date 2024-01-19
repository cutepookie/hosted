
#include "MB_LayerPetUpdate.h"
#include "MB_FunctionMgr.h"
#include "MB_LayerRoleInfoHeader.h"
#include "MB_LayerPetEquipment.h"
#include "MB_LayerCommand.h"
#include "MB_NodeItemUnitJingLian.h"
#include "MB_NodeItemUnitShengji.h"
#include "MB_ScrollBg.h"
#define ENHANCECELLNUM 6
MB_LayerPetUpdate* MB_LayerPetUpdate::create(uint64_t petID){
    
    MB_LayerPetUpdate *ptr = new MB_LayerPetUpdate();
    if (ptr && ptr->init(petID)) {
        
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE(ptr);
    return NULL;
}
MB_LayerPetUpdate::MB_LayerPetUpdate(){
    for (int i = 0; i < MAX_GER_STAR; i++) {
        m_pStar[i] = NULL;
    }
    isUpdateUI = false;
    m_pTableContainer = NULL;
    m_pTextLevel2 = NULL;
    m_pTextAttack2 = NULL;
    m_pTextLife2 = NULL;
    m_pPetName = NULL;
    m_pTextLevel1 = NULL;
    m_pTextNextExp = NULL;
    m_pTextAttack1 = NULL;
    m_pTextLife1 = NULL;
    m_pTextExp = NULL;
    m_pExpBar = NULL;
    m_pCard = NULL;
    m_pUpdateBt = NULL;
    m_pCollect = NULL;
    m_bReady = false;
    m_pCCBAnimationMgr = NULL;
    m_nSelectExp = 0;
    for (int i = 0 ; i < 6 ; i++)
    {
        m_pPetNode[i] = NULL;
    }
    
    
    m_pSoldList = new CCArray();
    SOCKET_MSG_REGIST(SC_GER_UPDATE_EXP, MB_LayerPetUpdate);
    SOCKET_MSG_REGIST(SC_GER_UPDATE, MB_LayerPetUpdate);
    SOCKET_MSG_REGIST(SC_GER_EAT, MB_LayerPetUpdate);
    m_bShowRoleInfoPanel = true;
    
    isHomeButtonShow =  ((MB_LayerCommand*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND))->rootNode->isVisible();
    ((MB_LayerCommand*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND))->rootNode->setVisible(false);
}
MB_LayerPetUpdate::~MB_LayerPetUpdate(){
    
    SOCKET_MSG_UNREGIST(SC_GER_UPDATE_EXP);
    SOCKET_MSG_UNREGIST(SC_GER_UPDATE);
    SOCKET_MSG_UNREGIST(SC_GER_EAT);
    for (int i = 0; i < MAX_GER_STAR; i++) {
        CC_SAFE_RELEASE(m_pStar[i]);
    }
    
    CC_SAFE_RELEASE(m_pTableContainer);
    CC_SAFE_RELEASE(m_pTextLevel2);
    CC_SAFE_RELEASE(m_pTextAttack2);
    CC_SAFE_RELEASE(m_pTextLife2);
    CC_SAFE_RELEASE(m_pPetName);
    CC_SAFE_RELEASE(m_pTextLevel1);
    CC_SAFE_RELEASE(m_pTextNextExp);
    CC_SAFE_RELEASE(m_pTextAttack1);
    CC_SAFE_RELEASE(m_pTextLife1);
    CC_SAFE_RELEASE(m_pTextExp);
    CC_SAFE_RELEASE(m_pExpBar);
    CC_SAFE_RELEASE(m_pCard);
    CC_SAFE_RELEASE(m_pUpdateBt);
    CC_SAFE_RELEASE(m_pCollect);
    CC_SAFE_RELEASE(m_pCCBAnimationMgr);
    
    for (int i = 0 ; i < 6 ; i++)
    {
        CC_SAFE_RELEASE(m_pPetNode[i]);
    }
    
    CC_SAFE_DELETE(m_pSoldList);
    
}
bool MB_LayerPetUpdate::init(uint64_t petID){
    
    if (CCLayer::init()== false || petID ==0 ) {
        
        return false;
    }
    m_nExternExp = 50;
    m_nPetId = petID;
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node= pCCBReader->readNodeGraphFromFile("res/card_layer_levelup.ccbi", this);
    this->addChild(node);
    m_pCCBAnimationMgr = pCCBReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pCCBAnimationMgr);
    pCCBReader->release();
    
    
    float scale = m_pExpBar->getScaleX();
    CCPoint pos = m_pExpBar->getPosition();
    CCNode * xparent =  m_pExpBar->getParent();
    int z =  m_pExpBar->getZOrder();
    m_pExpBar->removeFromParentAndCleanup(true);
    m_pExpTimer = CCProgressTimer::create( m_pExpBar);
    m_pExpTimer->setType(kCCProgressTimerTypeBar);
    m_pExpTimer->setMidpoint(ccp(0,1));
    m_pExpTimer->setBarChangeRate(ccp(1, 0));
    m_pExpTimer->setPosition(pos);
    m_pExpTimer->setScaleX(scale);
    xparent->addChild( m_pExpTimer,z);
    
    setPetUid(m_nPetId);
    
    m_pArrayCanChoose = MB_ItemMgr::getInstance()->getExpCardArray();
    m_szCell =MB_NodeItemUnitJingLian::getUnitSize();
    m_szCell = CCSize(m_szCell.width*ENHANCECELLNUM,m_szCell.height) ;
    CCTableView* tableView = CCTableView::create(this, m_pTableContainer->getContentSize());
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_pTableContainer->addChild(tableView);
    tableView->reloadData();
    m_pTableView = tableView;
    
    addChild(MB_ScrollBg::create(right_bottom,.5f,3),-1);
    return true;
}

bool MB_LayerPetUpdate::setPetUid(uint64_t petID)
{
    m_pExpTimer->setPercentage(0.0f);
    m_pTextAttack1->setString("0");
    m_pTextLife1->setString("0");
    m_pTextLevel1->setString("0");
    m_pTextAttack2->setString("0");
    m_pTextLife2->setString("0");
    m_pTextLevel2->setString("0");
    m_pTextExp->setString("0");
    m_pTextNextExp->setString("");
    m_pPetName->setString(" ");
    
    if (!MB_PetMgr::getInstance()->isPetExist(petID))
    {
        return false;
    }
    
    m_nPetId = petID;
    
    onResetWnd();
    
    return true;
}

void MB_LayerPetUpdate::onResetWnd()
{
    if (m_pCard->getChildrenCount()==0) {
        m_pCard->removeAllChildren();
        MB_NodePetCard *card = MB_NodePetCard::create(m_nPetId);
        m_pCard->addChild(card);
        card->setTag(1);
    }
    MB_PetData *data = MB_PetMgr::getInstance()->getPetDataByUID(m_nPetId);
    MB_PetTemplate *templete = data->getTemplete();
    
    char databuf[50] ;
    MB_PetMgr::getInstance()->getPetRealName(databuf, m_nPetId);
    m_pPetName->setString(databuf);
    int attack1 = MB_PetMgr::getInstance()->calPetAttack(templete->getPetAttack(), data->getPetLevel(), data->getPetQuallity());
    setAttribute("", databuf, attack1);
    m_pTextAttack1->setString(databuf);
    
    int hp1 = MB_PetMgr::getInstance()->calPetHP(templete->getPetHpMax(), data->getPetLevel(), data->getPetQuallity());
    setAttribute("", databuf, hp1);
    m_pTextLife1->setString(databuf);
    
    setAttribute("", databuf, data->getPetLevel());
    m_pTextLevel1->setString(databuf);
        m_pTextAttack2->setString("0");
        m_pTextLife2->setString("0");
        m_pTextLevel2->setString("0");
    m_pTextExp->setString("0");
    reloadData();
    
    m_nNowExp = data->getPetExp();
    m_nNowLevel = data->getPetLevel();
    m_nNextExp = MB_PetMgr::getInstance()->getExpByLevel(data->getPetLevel());
    int64_t needexp = m_nNextExp - m_nNowExp;
    
    sprintf(databuf, "%lld",needexp);
    m_pTextNextExp->setString(databuf);
    int64_t  m_nPreExp =  MB_PetMgr::getInstance()->getExpByLevel(data->getPetLevel()-1);
    
    float m_tPerccent =  (m_nNowExp-m_nPreExp)*100.f/(m_nNextExp-m_nPreExp);;
    m_pExpTimer->setPercentage(m_tPerccent);
    
    NSGameHelper::centerStars(m_pStar, MAX_GER_STAR, templete->getPetStar());
    
}
void MB_LayerPetUpdate::reloadData(){
    m_bReady = false;
    CCObject *data;
    int index = 0;
    int64_t expCount= 0;
    for (int i = 0 ; i< 6; i++) {
        
        m_pPetNode[i]->removeAllChildrenWithCleanup(true);
    }
    CCARRAY_FOREACH(m_pSoldList,data){
        
        if(index < 6){
            MB_NodeItem* node = MB_NodeItem::create((MB_ItemData*)data);
            node->showNameCount(false);
            node->setOnClickEnable(false);
            m_pPetNode[index]->addChild(node);
            expCount += MB_ItemMgr::getInstance()->getExpByTid(((MB_ItemData*)data)->getItemID());

        }
        index++;
    }
    char* databuf = new char[50];
    m_nSelectExp = expCount;
    sprintf(databuf, "+ %lld",expCount);
    m_pTextExp->setString(databuf);
    
    //预测精灵属性
    MB_PetData* petData = MB_PetMgr::getInstance()->getPetDataByUID(m_nPetId);
    MB_PetTemplate* petTemplete = petData->getTemplete();
    
    uint16_t level2 = MB_PetMgr::getInstance()->calLevelByExp(expCount + petData->getPetExp());
    if (level2 > MB_RoleData::getInstance()->getLevel())
    {
        level2 = MB_RoleData::getInstance()->getLevel();
    }
    sprintf(databuf, "%u", petData->getPetLevel());
    m_pTextLevel1->setString(databuf);
    
    uint32_t attack1 = MB_PetMgr::getInstance()->calPetAttack(petTemplete->getPetAttack(), petData->getPetLevel(), petData->getPetQuallity());
    sprintf(databuf, "%u", attack1);
    m_pTextAttack1->setString(databuf);
    
    uint32_t hpMax1 = MB_PetMgr::getInstance()->calPetHP(petTemplete->getPetHpMax(), petData->getPetLevel(), petData->getPetQuallity());
    sprintf(databuf, "%u", hpMax1);
    m_pTextLife1->setString(databuf);
    
    
    sprintf(databuf, "%u",level2);
    m_pTextLevel2->setString(databuf);
    
    uint32_t attack2 = MB_PetMgr::getInstance()->calPetAttack(petTemplete->getPetAttack(), level2, petData->getPetQuallity());
    sprintf(databuf, "%u", attack2);
    m_pTextAttack2->setString(databuf);
    
    uint32_t hpMax2 = MB_PetMgr::getInstance()->calPetHP(petTemplete->getPetHpMax(), level2, petData->getPetQuallity());
    sprintf(databuf, "%u",hpMax2);
    m_pTextLife2->setString(databuf);
    
    CC_SAFE_DELETE_ARRAY(databuf);
}
bool  MB_LayerPetUpdate::addData(MB_ItemData *data){
    
    if (m_pSoldList->count()<6) {
        
        m_pSoldList->addObject(data);
        return true;
    }
    return false;
}
void MB_LayerPetUpdate::removeData(MB_ItemData *data){
    
    m_pSoldList->removeObject(data);
    
}

void MB_LayerPetUpdate::setAttribute(const char *buf,char *databuf, int attribute){
    
    sprintf(databuf, "%s%d",buf,attribute);
    
}
cocos2d::SEL_MenuHandler MB_LayerPetUpdate::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerPetUpdate::onCloseClick);
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_LayerPetUpdate::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){
    
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onUpdateClick", MB_LayerPetUpdate::onUpdateClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onAutoUpdateClick", MB_LayerPetUpdate::onAutoUpdateClick);
    
    return NULL;
    
}
bool MB_LayerPetUpdate::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode)
{
    TutorialAssignLayerWindow
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTableContainer", CCNode *,m_pTableContainer);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextLevel2", CCLabelBMFont *,m_pTextLevel2);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextAttack2", CCLabelBMFont *,m_pTextAttack2);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextLife2", CCLabelBMFont *,m_pTextLife2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pPetName", CCLabelTTF *,m_pPetName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextLevel1", CCLabelBMFont *,m_pTextLevel1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextNextExp", CCLabelBMFont *,m_pTextNextExp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextAttack1", CCLabelBMFont *,m_pTextAttack1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextLife1", CCLabelBMFont *,m_pTextLife1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextExp", CCLabelBMFont *,m_pTextExp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pExpBar", CCSprite *, m_pExpBar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pCard", CCNode *, m_pCard);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pCollect", CCControlButton *, m_pCollect);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pUpdateBt", CCControlButton *, m_pUpdateBt);
    char petNode[ ] = "m_pPet1";
    for (int i = 0 ; i < 6 ; i++) {
        petNode[6] = '1'+i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this,petNode,CCNode *, m_pPetNode[i]);
    }
    
    char strStar[] = "m_pStar1";
    for (int i = 0; i < MAX_GER_STAR; i++) {
        strStar[7] = '1'+i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, strStar, CCSprite*, m_pStar[i]);
    }
    
    return false;
    
}

void MB_LayerPetUpdate::onCloseClick(CCObject *)
{
    TutorialTriggerComplete
    if (isUpdateUI) {
        MB_LayerPetDetail* ptr =  dynamic_cast<MB_LayerPetDetail*>(getLogicParent());
        if (ptr) {
            ptr->resetBaseInfo();
        }
    }
    
    ((MB_LayerCommand*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND))->rootNode->setVisible(isHomeButtonShow);
    popWindow(true);
}

void MB_LayerPetUpdate::onUpdateClick(CCObject *)
{
    MB_PetData* petData = MB_PetMgr::getInstance()->getPetDataByUID(m_nPetId);
    TutorialTriggerComplete
    if (petData == NULL)
    {
        MB_Message::sharedMB_Message()->showMessage("请选择需要升级的精灵.");
        return;
    }
    else if (m_pSoldList ->count() == 0)
    {
        MB_Message::sharedMB_Message()->showMessage("请先选择被吞噬的升级材料.");
        return;
        
    }
    else if (petData->getPetLevel() >= MB_RoleData::getInstance()->getLevel())
    {
        MB_Message::sharedMB_Message()->showMessage("精灵等级不能大于玩家等级.");
        return;
    }
    sendpet_eat();
}
void MB_LayerPetUpdate::onAutoUpdateClick(CCObject *){
    
    MB_PetData* petData = MB_PetMgr::getInstance()->getPetDataByUID(m_nPetId);
    TutorialTriggerComplete
    if (petData == NULL)
    {
        MB_Message::sharedMB_Message()->showMessage("请选择需要升级的精灵.");
        return;
    }
    else if (m_pSoldList->count() >= 6)
    {
        MB_Message::sharedMB_Message()->showMessage("升级材料添加已满, 最多选择6个");
        return;
        
    }
    else if (petData->getPetLevel() >= MB_RoleData::getInstance()->getLevel())
    {
        MB_Message::sharedMB_Message()->showMessage("精灵等级不能大于玩家等级.");
        return;
    }
    
    reloadData();
    uint16_t level2 = MB_PetMgr::getInstance()->calLevelByExp(m_nSelectExp + petData->getPetExp());
    //已经足够经验了  还在点击自动添加
    if(MB_RoleData::getInstance()->getLevel() <= level2)
    {
        MB_Message::sharedMB_Message()->showMessage("精灵等级不能大于玩家等级.");
        return;
    }
    
    MB_Message::sharedMB_Message()->showMessage("载入中",600);
    this->runAction(CCCallFunc::create(this, callfunc_selector(MB_LayerPetUpdate::autoAdd)));
}
void  MB_LayerPetUpdate::autoAdd()
{
    int index = m_pSoldList->count();
    int preCount = index;
    int64_t needExp;
    if (MB_PetMgr::getInstance()->getExpByLevel(MB_RoleData::getInstance()->getLevel()) > 1) {
        
        needExp = MB_PetMgr::getInstance()->getExpByLevel(MB_RoleData::getInstance()->getLevel() - 1);
    }
    else
    {
        needExp = MB_PetMgr::getInstance()->getExpByLevel(MB_RoleData::getInstance()->getLevel());
    }
    needExp -= m_nNowExp;
    CCObject *costData;

    CCARRAY_FOREACH_REVERSE(m_pArrayCanChoose, costData){
        if(index >= 6){
            break;
        }
        if(m_pSoldList->containsObject(costData) == false )
        {
            if (needExp > 0)
            {
                needExp -= MB_ItemMgr::getInstance()->getExpByTid(((MB_ItemData*)costData)->getItemID());
                m_pSoldList->addObject(costData);
                index ++;
            }else{
                
                //已经有足够经验升级精灵了
                if (needExp < 0)
                {
                    break;
                }
                
            }
        }
    }
    CCPoint p =  m_pTableView->getContentOffset();
    m_pTableView->reloadData();
    m_pTableView->setContentOffset(p);
//    m_pTableView->getcell
//    MB_ItemData* itemData = (MB_ItemData*)m_pArrayCanChoose->objectAtIndex(idx);
//    MB_NodeItemUnitShengji* pNode = MB_NodeItemUnitShengji::create(this,itemData->getItemUID());
//    layer->addChild(pNode);
//    for (int j = 0; j<m_pSoldList->count(); j++) {
//        if (itemData->getItemUID()==((MB_ItemData*)m_pSoldList->objectAtIndex(j))->getItemUID()) {
//            pNode->m_pSelectSpr->setVisible(true);
//        }
//    }
    
    
    MB_Message::sharedMB_Message()->removeALLMessage();
    if (m_pSoldList->count() > 0) {
        
        reloadData();
        if(preCount == m_pSoldList->count()){
            
            MB_Message::sharedMB_Message()->showMessage("材料不足", "糖果不足, 我们去友好商店购买吧.", "前往", "取消", this, menu_selector(MB_LayerPetUpdate::goItemShop), NULL);
        }
        
    }else {
        
        //MB_Message::sharedMB_Message()->showMessage("没有未上阵的1，2星精灵了");
        MB_Message::sharedMB_Message()->showMessage("材料不足", "糖果不足, 我们去友好商店购买吧.", "前往", "取消", this, menu_selector(MB_LayerPetUpdate::goItemShop), NULL);
    }
    
}
void MB_LayerPetUpdate::goItemShop(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionItemShop, this);
}
bool MB_LayerPetUpdate::sendpet_eat(){
    
    CCLOG("go update");
    MB_Message::sharedMB_Message()->showMessage("吞噬中",600);
    MB_PetMgr::getInstance()->sendpet_eat(m_nPetId, m_pSoldList);
    return true;
}
void MB_LayerPetUpdate::changeLevel(){
    
    MB_PetData* data =MB_PetMgr::getInstance()->getPetDataByUID(m_nPetId);
    m_nNowLevel ++;
    if (m_nNowLevel > data->getPetLevel()) {
        
        m_nNowLevel = data->getPetLevel();
    }
    char databuf[50];
    setAttribute("", databuf, m_nNowLevel );
    m_pTextLevel1->setString(databuf);
    m_pTextLevel2->setString(databuf);
    MB_Audio::getInstance()->playEffect(GET_BACKGROUND(ksSound_Card_Level_Up).c_str());
}
void MB_LayerPetUpdate::reloadShow(){
    isUpdateUI = true;
    if (global_layerPetEquipment!=NULL) {
        global_layerPetEquipment->isUpdateUI = true;
    }

    MB_PetData* data =MB_PetMgr::getInstance()->getPetDataByUID(m_nPetId);
    m_nNextExp =(MB_PetMgr::getInstance()->getExpByLevel(data->getPetLevel()));
    int64_t  m_nPreExp = MB_PetMgr::getInstance()->getExpByLevel(data->getPetLevel()-1);
    float finalpercent = (data->getPetExp()-m_nPreExp)*100.f/(m_nNextExp-m_nPreExp);;
    m_pCCBAnimationMgr->runAnimationsForSequenceNamed("par1");
    //经验条动画
    if (data->getPetLevel() > m_nNowLevel) {
        
        CCArray* actionList = CCArray::create();
        actionList->addObject(CCProgressTo::create(0.2f, 100));
        float timecount = 0.2f;
        for (int i= m_nNowLevel+1; i < (data->getPetLevel()); i++) {
            
            actionList->addObject(CCSequence::create(CCProgressFromTo::create(0.2f,0, 100),CCCallFunc::create(this, callfunc_selector(MB_LayerPetUpdate::changeLevel)),NULL));
            timecount+=0.2f;
        }
        
        actionList->addObject(CCSequence::create(CCProgressTo::create(0.2f, finalpercent),CCCallFunc::create(this, callfunc_selector(MB_LayerPetUpdate::changeLevel)),NULL));
        m_pExpTimer->runAction(CCSequence::create(actionList));
        m_nNowExp = data->getPetExp();
        timecount+=0.2f;
        // MB_Message::sharedMB_Message()->showMessage(timecount);
        
    }else {
        
        m_nNowLevel = data->getPetLevel();
        m_pExpTimer->runAction(CCProgressTo::create(0.2f,finalpercent));
        m_nNowExp = data->getPetExp();
        
    }
    
    char databuf[50];
    sprintf(databuf, "%lld",(m_nNextExp-m_nNowExp));
    m_pTextNextExp->setString(databuf);
    
    MB_PetTemplate* petTemplete = data->getTemplete();
    int attack = MB_PetMgr::getInstance()->calPetAttack(petTemplete->getPetAttack(), data->getPetLevel(), data->getPetQuallity());
    setAttribute("", databuf, attack);
    m_pTextAttack1->setString(databuf);
    
    int hpMax = MB_PetMgr::getInstance()->calPetHP(petTemplete->getPetHpMax(), data->getPetLevel(), data->getPetQuallity());
    setAttribute("", databuf, hpMax);
    m_pTextLife1->setString(databuf);
    
    setAttribute("", databuf, m_nNowLevel);
    m_pTextLevel1->setString(databuf);
    
    
    m_pTextAttack2->setString("0");
    m_pTextLife2->setString("0");
    m_pTextLevel2->setString("0");
    m_pTextExp->setString("0");
    

    m_pSoldList->removeAllObjects();
    reloadData();
    m_pArrayCanChoose = MB_ItemMgr::getInstance()->getExpCardArray();
    m_pTableView->reloadData();
    
}
void  MB_LayerPetUpdate::onMsgRecv(CCNode* node, SocketResponse* response){
    
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
        case SC_GER_EAT:
            
            MB_Message::removeALLMessage();
            reloadShow();
            break;
        case SC_GER_UPDATE_EXP:
            
            break;
        case SC_GER_UPDATE:
            
            break;
            
        default:
            break;
    }
    
}
void  MB_LayerPetUpdate::readLoadPet(uint64_t petID){
    
    m_nPetId = petID;
    deallocAndReload();
    init(m_nPetId);
    
}
void MB_LayerPetUpdate::deallocAndReload(){
    
    this->removeAllChildrenWithCleanup(true);
    
    CC_SAFE_RELEASE(m_pPetName);
    CC_SAFE_RELEASE(m_pTextLevel1);
    CC_SAFE_RELEASE(m_pTextNextExp);
    CC_SAFE_RELEASE(m_pTextAttack1);
    CC_SAFE_RELEASE(m_pTextLife1);
    CC_SAFE_RELEASE(m_pTextExp);
    CC_SAFE_RELEASE(m_pExpBar);
    CC_SAFE_RELEASE(m_pCard);
    CC_SAFE_RELEASE(m_pUpdateBt);
    CC_SAFE_RELEASE(m_pCollect);
    
    for (int i = 0 ; i < 6 ; i++) {
        
        CC_SAFE_RELEASE(m_pPetNode[i]);
    }
    
    CC_SAFE_DELETE(m_pSoldList);
    m_pPetName = NULL;
    m_pTextLevel1 = NULL;
    m_pTextNextExp = NULL;
    m_pTextAttack1 = NULL;
    m_pTextLife1 = NULL;
    m_pTextExp = NULL;
    m_pExpBar = NULL;
    m_pCard = NULL;
    m_pUpdateBt = NULL;
    m_pCollect = NULL;
    for (int i = 0 ; i < 6 ; i++) {
        
        m_pPetNode[i] = NULL;
    }
    m_pSoldList = new CCArray();
    
    
    
}
CCSize MB_LayerPetUpdate::cellSizeForTable(CCTableView *table)
{
    return m_szCell;
}

CCTableViewCell* MB_LayerPetUpdate::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell = table->dequeueCell();
    if (cell == NULL)
    {
        cell = new CCTableViewCell();
        cell->autorelease();
    }
    else
    {
        cell->removeAllChildren();
    }
    
    CCLayer* layer = CCLayer::create();
    layer->setContentSize(m_szCell);
    
    for (int i = idx*ENHANCECELLNUM;i < (idx+1)*ENHANCECELLNUM && i < m_pArrayCanChoose->count();i++)
    {
        MB_ItemData* itemData = (MB_ItemData*)m_pArrayCanChoose->objectAtIndex(i);
        MB_NodeItemUnitShengji* pNode = MB_NodeItemUnitShengji::create(this,itemData->getItemUID());
        layer->addChild(pNode);
        for (int j = 0; j<m_pSoldList->count(); j++) {
            if (itemData->getItemUID()==((MB_ItemData*)m_pSoldList->objectAtIndex(j))->getItemUID()) {
                pNode->m_pSelectSpr->setVisible(true);
                break;
            }
        }
        pNode->setPosition(ccp(m_szCell.width/ENHANCECELLNUM*(0.5 + i%ENHANCECELLNUM) + 21, m_szCell.height/2));
    }
    cell->addChild(layer);
    return cell;
}

unsigned int MB_LayerPetUpdate::numberOfCellsInTableView(CCTableView *table)
{
    return m_pArrayCanChoose->count()/ENHANCECELLNUM + ((m_pArrayCanChoose->count()%ENHANCECELLNUM) == 0? 0:1);
}
