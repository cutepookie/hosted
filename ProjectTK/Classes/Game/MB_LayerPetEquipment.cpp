#include "MB_LayerPetEquipment.h"
#include "MB_LayerPetCommand.h"
#include "MB_LayerListEquipChange.h"
#include "MB_FunctionMainWnd.h"
#include "MB_LayerPetDetail.h"
#include "MB_NodePetAid.h"
#include "MB_LayerGuard.h"
#include "MB_GuardInterface.h"
#include "MB_ScrollBg.h"
#include "MB_NodePetDuiWu.h"
#include "MB_NodeYaoLingDuiWu.h"
#include "MB_LayerPetRestore.h"
#include "MB_LayerPetEnhance.h"
#include "MB_LayerPetUpdate.h"
#include "MB_SkillDetail.h"
#define LAYER_TAG 50
#define NODE_GER_TAG 50
#define MAX_SHOW_CMD 6
#define AIDLAYER 300
#define TARGETX 200
#define TARGETX_2 375
#define SCALESPAN 80
#define SCALEX (0.97f)
#define SCALEY (0.9f)
#define SUOXIAOX 150
#define M_KaiPaiYiDongHuiFuSpeed (150.0f)
#define XIAZHENY -200
#define NPOSX 80
vector<uint64_t> shouHuV;

bool checkInTeam(uint64_t petID){
    
    for (int i = 0 ; i < CARD_IN_GAME ; i++) {
        if (teamV[i] != -1 && teamV[i] == petID) {
            return true;
        }
    }
    return false;
}
bool checkTypeInTeam(uint64_t petID){
    int typeID = MB_PetMgr::getInstance()->getPetDataByUID(petID)->getPetTypeID();
    for (int i = 0 ; i < CARD_IN_GAME ; i++) {
        if (teamV[i] != -1 && MB_PetMgr::getInstance()->getPetDataByUID(teamV[i])->getPetTypeID() == typeID) {
            return true;
        }
    }
    return false;
}
bool checkShouHu(uint64_t petID){
    uint8_t tempInt = shouHuV.size();
    for (int i = 0 ; i < tempInt ; i++) {
        if (shouHuV[i] == petID) {
            return true;
        }
    }
    return false;
}
bool compare(CCObject *_petData1,CCObject *_petData2)
{
    MB_PetData* petData1 = (MB_PetData*)_petData1;
    MB_PetData* petData2 = (MB_PetData*)_petData2;
    int tempInt1 = checkInTeam(petData1->getPetID())?1:0;
    int tempInt2 = checkInTeam(petData2->getPetID())?1:0;
    if (tempInt1>tempInt2)return true;
    else if (tempInt1<tempInt2)return false;
    tempInt1 = checkShouHu(petData1->getPetID())?1:0;
    tempInt2 = checkShouHu(petData2->getPetID())?1:0;
    if (tempInt1>tempInt2)return true;
    else if (tempInt1<tempInt2)return false;
    if (petData1->getTemplateStar() > petData2->getTemplateStar())return true;
    else if (petData1->getTemplateStar() < petData2->getTemplateStar())return false;
    if (petData1->getPetLevel() > petData2->getPetLevel())return true;
    else if (petData1->getPetLevel() < petData2->getPetLevel())return false;
    if (petData1->getPetQuallity() > petData2->getPetQuallity())return true;
    else if (petData1->getPetQuallity() < petData2->getPetQuallity())return false;
    if (petData1->getPetTypeID() > petData2->getPetTypeID())return true;
    else if (petData1->getPetTypeID() < petData2->getPetTypeID())return false;
    return false;
}


MB_LayerPetEquipment::MB_LayerPetEquipment(){
    isUpdateYaoLing = false;
    isToOnClickGHYSSH = -1;
    toShowDetailPetUID = 0;
    isUpdateUI = false;
    isPopWindow = false;
    isZuZhiTouch = false;
    huiFuSpeedX = -1;
    isTouchBlow = false;
    isStartHuiFuDown = false;
    isStartHuiFuUp = false;
    isTouchUpOrDown = TD_NONE;
    selectNpdw = NULL;
    m_pAllRoleArray = NULL;
    m_pNodeScroller = NULL;
    m_nListSize = 0;
    m_bShowRoleInfoPanel = true;
    m_bShowHomeButton = true;
    m_pFightPower = NULL;
    m_pAttack = NULL;
    m_pLife = NULL;
    m_pPetName = NULL;
    m_pMainPetCmd = NULL;
    m_bShowHomeButton = true;
    m_pNodeLevel = NULL;
    m_pSpriteGuard = NULL;
    m_pTTFAddGuard = NULL;
    m_pNodeNowMaxLevel = NULL;
    m_pMoveNode1 = NULL;
    m_pNodeNaveigation = NULL;
    m_pDetail = NULL;
    m_pDJSZ = NULL;
    m_pItemCount = NULL;
    m_pNumString = NULL;
    m_pTeamFightPower = NULL;
    m_pToMoveNode = NULL;
    m_pToVs2 = NULL;
    m_pFhdwlb = NULL;
    m_pToVs3 = NULL;
    m_pToVs4 = NULL;
    m_pToMoveNode2 = NULL;
    m_pZheZhao = NULL;
    for (int i = 0; i < MAX_GER_STAR; i++) {
        m_pStar[i] = NULL;
    }
    teamV.clear();
    shouHuV.clear();
    for (int i = 0; i < CARD_IN_GAME; i++) {
        teamV.push_back(-1);
        lastTeamV.push_back(-1);
        m_pYlNode[i] = NULL;
    }
}

MB_LayerPetEquipment::~MB_LayerPetEquipment(){
    global_layerPetEquipment = NULL;
    CC_SAFE_RELEASE_NULL(m_pNodeScroller);
    CC_SAFE_RELEASE_NULL(m_pAttack);
    CC_SAFE_RELEASE_NULL(m_pLife);
    CC_SAFE_RELEASE_NULL(m_pPetName);
    CC_SAFE_RELEASE_NULL(m_pFightPower);
    CC_SAFE_RELEASE_NULL(m_pMainPetCmd);
    CC_SAFE_RELEASE_NULL(m_pNodeLevel);
    CC_SAFE_RELEASE_NULL(m_pSpriteGuard);
    CC_SAFE_RELEASE_NULL(m_pTTFAddGuard);
    CC_SAFE_RELEASE_NULL(m_pNodeNowMaxLevel);
    CC_SAFE_RELEASE_NULL(m_pMoveNode1);
    CC_SAFE_RELEASE_NULL(m_pNodeNaveigation);
    CC_SAFE_RELEASE_NULL(m_pDetail);
    CC_SAFE_RELEASE_NULL(m_pDJSZ);
    CC_SAFE_RELEASE_NULL(m_pItemCount);
    CC_SAFE_RELEASE_NULL(m_pNumString);
    CC_SAFE_RELEASE_NULL(m_pTeamFightPower);
    CC_SAFE_RELEASE_NULL(m_pToMoveNode);
    CC_SAFE_RELEASE_NULL(m_pToVs2);
    CC_SAFE_RELEASE_NULL(m_pFhdwlb);
    CC_SAFE_RELEASE_NULL(m_pToVs3);
    CC_SAFE_RELEASE_NULL(m_pToVs4);
    CC_SAFE_RELEASE_NULL(m_pToMoveNode2);
    CC_SAFE_RELEASE_NULL(m_pZheZhao);
    for (int i = 0; i < MAX_GER_STAR; i++) {
        CC_SAFE_RELEASE_NULL(m_pStar[i]);
    }
    for (int i = 0; i < CARD_IN_GAME; i++) {
        CC_SAFE_RELEASE_NULL(m_pYlNode[i]);
    }
    
    bool isSendZhenxing = false;
    for (int i = 0; i<MEMBER_NUM; i++) {
        if ((MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet==NULL&&teamV[i]!=-1) || (MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet!=NULL&&teamV[i] != MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet->getPetID())) {
            isSendZhenxing = true;
            break;
        }
    }
    if (isSendZhenxing) {
        sendZhenXing();
    }
}

void MB_LayerPetEquipment::sendZhenXing()
{
    MB_Message::sharedMB_Message()->showZuZhiMessage("",3);
    MB_TeamData::getInstance()->sendpet_zhenxing(teamV[0],teamV[1],teamV[2],teamV[3],teamV[4],teamV[5],lastTeamV[zhuangbeiIndexVec[0]%100],lastTeamV[zhuangbeiIndexVec[1]%100],lastTeamV[zhuangbeiIndexVec[2]%100],lastTeamV[zhuangbeiIndexVec[3]%100],lastTeamV[zhuangbeiIndexVec[4]%100],lastTeamV[zhuangbeiIndexVec[5]%100]);
}
MB_LayerPetEquipment *  MB_LayerPetEquipment::create(){
    MB_LayerPetEquipment *ptr = new  MB_LayerPetEquipment();
    if (ptr && ptr->init()){
        
        ptr->autorelease();
        
        return ptr;
    }
    
    CC_SAFE_DELETE(ptr);
    
    return NULL;
}
bool MB_LayerPetEquipment::init(){
    MB_ResWindow::init();
    global_layerPetEquipment = this;
    for (int i =0; i<MEMBER_NUM; i++) {
        MB_PetGuardData* pData = MB_GuardInterface::getInstance()->getPetGuardDataByPos(i+1);
        if (pData != NULL)
        {
            shouHuV.push_back(pData->getPetUid());
        }
        if (MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet == NULL) {
            teamV[i] = -1;
            lastTeamV[i] = -1;
            zhuangbeiIndexVec.push_back(i);
        }else
        {
            TeamDataStruct* ts = MB_TeamData::getInstance()->getTeamMemberByIndex(i);
            teamV[i] = ts->m_pPet->getPetID();
            lastTeamV[i] = ts->m_pPet->getPetID();
            if (ts->m_pEquip1 != NULL||ts->m_pEquip2 != NULL||ts->m_pEquip3 != NULL||ts->m_pTreasure1 != NULL||ts->m_pTreasure2 != NULL||ts->m_pTreasure3 != NULL) {
                zhuangbeiIndexVec.push_back(i+100);
            }else
            {
                zhuangbeiIndexVec.push_back(i);
            }
        }
    }
    MB_PetGuardData* pData;
    for (int i = 0; i<CARD_IN_GAME; i++) {
        pData = MB_GuardInterface::getInstance()->getPetGuardDataByPos(i+1);
        if (pData!=NULL) {
            shouhuPetTypeIDVec.push_back(pData->getPetTypeId());
        }
    }
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/card_layer_equipment.ccbi", this);
    this->addChild(node);
    pCCBReader->release();
    node->addChild(MB_ScrollBg::create(left_top, 0.5f), -1);
    
    m_pNodeScroller->setZOrder(10);
    m_pNodeNaveigation->setZOrder(10);
    
    int level = MB_RoleData::getInstance()->getLevel();
    m_pLockPos = 3;
    if (level >= 25){
        
        m_pLockPos = 0;
        
    }
    else if (level >= 20){
        
        m_pLockPos = 1;
        
    }
    else if (level >= 10){
        
        m_pLockPos = 2;
        
    }
    else {
        
        m_pLockPos = 3;
    }
    
    m_pMainPetCmd->setVisible(true);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("duiwu.plist");
    
    m_nLengthPet = 0;
    m_nLengthEmpty = 0;
    //主将
    MB_NodePetDuiWu* npdw;
    for (int i = 0; i < CARD_IN_GAME; i++) {
        if (teamV[i]!=-1){
            npdw = MB_NodePetDuiWu::create(teamV[i]);
        }
        else {
            npdw = MB_NodePetDuiWu::create(-1);
        }
        npdw->setTag(i+100);
        npdw->opx2 = npdw->m_nWidth*(.5f + i);
        npdw->opy2 = npdw->getPositionY();
        npdw->setPositionX(npdw->opx2);
        m_pNodeScroller->addChild(npdw);
        
        CCSprite* spr =CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("slot_team_empty.png"));
        spr->setPosition(npdw->getPosition());
        m_pNodeScroller->addChild(spr,-1);
        rectV.push_back(CCRectApplyAffineTransform(CCRect(npdw->getPositionX()-npdw->m_nWidth*.5f,npdw->getPositionY()-npdw->m_nHeight*.5f,npdw->m_nWidth,npdw->m_nHeight), m_pNodeScroller->nodeToParentTransform()));
    }
    m_pNodeScroller->setContentSize(CCSize( npdw->m_nWidth*6,m_pNodeScroller->getContentSize().height));
    
    reloadArray();
    
    initFunctions();
    
    scheduleUpdate();
    
    this->setTouchEnabled(true);
    
    char databuf[50];
    sprintf(databuf, "%d", m_nListSize);
    m_pItemCount->setString(databuf);
    m_pNumString->setPositionX(-75.0-(NSGameHelper::get_length(m_nListSize)-3)*7);
    
    
    sprintf(databuf, " / %d", MB_RoleData::getInstance()->getLevel()*2);
    m_pNodeNowMaxLevel->setString(databuf);
    m_pPetName->setPositionX(-3.9+(NSGameHelper::get_length(MB_RoleData::getInstance()->getLevel()*2)-2)*6);
    
    memset(databuf, 0, sizeof(char)* 40);
    sprintf(databuf, "%llu", MB_TeamData::getInstance()->getFightPower());
    m_pTeamFightPower->setString(databuf);
    return true;
}
void MB_LayerPetEquipment::onCloseClick(CCObject* pSender)
{
    if (isPopWindow) {
        popWindow(true);
    }else
    {
        MB_FunctionMgr::getInstance()->goFunction(kFunctionHome, this);
    }
}

cocos2d::SEL_MenuHandler MB_LayerPetEquipment::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSkillClick", MB_LayerPetEquipment::onSkillClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerPetEquipment::onCloseClick);
    
    return NULL;
}

cocos2d::extension::SEL_CCControlHandler MB_LayerPetEquipment::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName)
{
    //CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onEquipAllClicked",MB_LayerPetEquipment::onEquipAllClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClickShangZhen",MB_LayerPetEquipment::onClickShangZhen);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClickDetail",MB_LayerPetEquipment::onClickDetail);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClickGHYSSH",MB_LayerPetEquipment::onClickGHYSSH);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClickFHDWLB",MB_LayerPetEquipment::onClickFHDWLB);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onLevelUpClick",MB_LayerPetEquipment::onLevelUpClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onQualityUpClick",MB_LayerPetEquipment::onQualityUpClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onJiBanClick",MB_LayerPetEquipment::onJiBanClick);
    
    return NULL;
    
}

bool MB_LayerPetEquipment::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){
    
    TutorialAssignLayerWindow
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeScroller", CCNode *, m_pNodeScroller);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeLevel", CCLabelBMFont *, m_pNodeLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pAttack", CCLabelBMFont *, m_pAttack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLife", CCLabelBMFont *, m_pLife);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pPetName", CCLabelTTF *, m_pPetName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeNowMaxLevel", CCLabelBMFont *, m_pNodeNowMaxLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMoveNode1", CCNode *, m_pMoveNode1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pFightPower", CCLabelBMFont *, m_pFightPower);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMainPetCmd", CCNode *, m_pMainPetCmd);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteGuard", CCSprite*, m_pSpriteGuard);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTTFAddGuard", CCLabelTTF*, m_pTTFAddGuard);
    
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeNaveigation", CCNode*, m_pNodeNaveigation);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pDetail",CCControlButton* ,m_pDetail);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pDJSZ",CCControlButton* ,m_pDJSZ);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pItemCount",CCLabelBMFont* ,m_pItemCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNumString",CCNode* ,m_pNumString);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTeamFightPower",CCLabelBMFont* ,m_pTeamFightPower);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pToMoveNode",CCNode* ,m_pToMoveNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pFhdwlb",CCNode* ,m_pFhdwlb);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pToVs2",CCNode* ,m_pToVs2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pToVs3",CCNode* ,m_pToVs3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pToVs4",CCNode* ,m_pToVs4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pToMoveNode2",CCNode* ,m_pToMoveNode2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pZheZhao",CCNode* ,m_pZheZhao);
    
    for (int i = 0; i < MAX_GER_STAR; i++) {
        char starstr[] = "star0";
        starstr[4] = i + '0';
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, starstr, CCSprite *, m_pStar[i]);
    }
    for (int i = 0; i < CARD_IN_GAME; i++) {
        char starstr[] = "ylNode0";
        starstr[6] = i + '0';
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, starstr, CCNode *, m_pYlNode[i]);
    }
    
    return false;
}

void MB_LayerPetEquipment::onSkillClick(CCObject*)
{
}

void MB_LayerPetEquipment::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    
    //将socket数据读取到序列化结构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    MB_Message::sharedMB_Message()->removeALLMessage();
    switch (Msg) {
            
    }
}


void MB_LayerPetEquipment::reloadArray(){
    
    if (m_pAllRoleArray) m_pAllRoleArray->removeAllObjects();
    m_pAllRoleArray = MB_PetMgr::getInstance()->getPetDataArray();
    m_nListSize = m_pAllRoleArray->count();
    //排序
    if (m_nListSize > 1) {
        m_pAllRoleArray->sortArray(compare);
    }
}

bool MB_LayerPetEquipment::initFunctions()
{
    m_pScollerView = CCScrollView::create(m_pNodeNaveigation->getContentSize());
    m_pScollerView->setDirection(kCCScrollViewDirectionHorizontal);
    m_pNodeNaveigation->addChild(m_pScollerView);
    m_pScollerView->setSwaller(false);
    m_pScollerView->setDelegate(this);
    int nPosX = NPOSX;
    int nPosY = 95;
    m_pScollerView->setClippingToBounds(false);
    m_pTestNode = CCNode::create();
    m_pScollerView->addChild(m_pTestNode);
    for (int i = 0; i < m_nListSize; i++)
    {
        MB_PetData* petData = (MB_PetData*)m_pAllRoleArray->objectAtIndex(i);
        if (petData!=NULL) {
            MB_NodePetDuiWu* npdw = MB_NodePetDuiWu::create(petData->getPetID(),false);
            npdw->m_nZorder =99999-i;
            m_pTestNode->addChild(npdw,npdw->m_nZorder);
            npdw->opx2 =nPosX+npdw->m_nWidth;
            npdw->opy2 = nPosY;
            npdw->opx =npdw->m_pMoveNode->getPositionX();
            npdw->setShangZhen(checkInTeam(npdw->m_nPetId));
            npdw->setShouHu(MB_GuardInterface::getInstance()->checkIsGuardPet(npdw->m_nPetId));
            npdw->setPosition(ccp(npdw->opx2,npdw->opy2));
            nPosX += npdw->m_nWidth;
            npdw->m_pDetailBtn->setTouchEnabled(false);
        }
    }
    m_pScollerView->setContentSize(CCSize( nPosX+444, m_pNodeNaveigation->getContentSize().height));
    
    update(0);
    
    if(MB_TutorialMgr::getInstance()->getSkipTutorial())
    {
        m_pScollerView->setContentOffset(ccp(-300,0));
        m_pScollerView->getContainer()->stopAllActions();
        m_pScollerView->m_tScrollDistance = ccp(17.3f,0);
        m_pScollerView->schedule(schedule_selector(CCScrollView::deaccelerateScrolling));
    }else{
        if (m_pTestNode->getChildrenCount()==2) {
            m_pScollerView->setContentOffset(ccp(-300,0));
            m_pScollerView->getContainer()->stopAllActions();
            m_pScollerView->m_tScrollDistance = ccp(17.3f,0);
            m_pScollerView->schedule(schedule_selector(CCScrollView::deaccelerateScrolling));
        }else
        {
            m_pScollerView->setContentOffset(ccp(-186,0));
            m_pScollerView->getContainer()->stopAllActions();
            m_pScollerView->schedule(schedule_selector(CCScrollView::deaccelerateScrolling));
        }
    }
    
    return true;
}
void MB_LayerPetEquipment::setDJSZ(bool b)
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("duiwu.plist");
    CCSpriteFrame *frame;
    if (b) {
        frame  =CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_inteam.png");
        m_pDJSZ->setTouchEnabled(false);
        
    }else{
        frame  =CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_enterteam.png");
        m_pDJSZ->setTouchEnabled(true);
    }
    m_pDJSZ->setBackgroundSpriteFrameForState(frame,CCControlStateNormal);
    m_pDJSZ->setBackgroundSpriteFrameForState(frame,CCControlStateHighlighted);
    m_pDJSZ->setBackgroundSpriteFrameForState(frame,CCControlStateSelected);
    m_pDJSZ->setBackgroundSpriteFrameForState(frame,CCControlStateDisabled);
}

void MB_LayerPetEquipment::update(float dt)
{
    CCArray* children = m_pTestNode->getChildren();
    for (int i=0; i< children->count();i++) {
        MB_NodePetDuiWu* npdw =  (MB_NodePetDuiWu*)children->objectAtIndex(i);
        CCPoint p =m_pTestNode->convertToWorldSpace( npdw->getPosition());
        if (npdw!=selectNpdw&&  p.x+25>TARGETX&&p.x+25< TARGETX+npdw->m_nWidth) {
            if (!(selectNpdw!=NULL&&selectNpdw->m_nPetId == npdw->m_nPetId)) {
                if (selectNpdw!=NULL) {
                    selectNpdw->setSelectedState(false);
                }
                selectNpdw = npdw;
                setDetail();
                npdw->setSelectedState(true);
                NSGameHelper::changeParent(npdw->m_pToVis,m_pDJSZ);
                NSGameHelper::changeParent(npdw,m_pDetail);
                m_pDJSZ->setPosition(ccp( npdw->m_nWidth/2-53,npdw->m_nHeight-30));
                m_pDetail->setPosition(ccp(npdw->m_nWidth/2-69,-50));
                setDJSZ(checkInTeam(selectNpdw->m_nPetId));
            }
        }
        if(p.x<-1000||p.x>1640)npdw->setVisible(false);
        else npdw->setVisible(true);
        
        float span =fabs(p.x-TARGETX);
        if (span>SCALESPAN) {
            npdw->m_pMoveNode->setScale(SCALEX,SCALEY);
        }else
        {
            float sx =SCALEX+(1-SCALEX)* (1-(span/SCALESPAN));sx =sx>1?1:sx;sx = sx<SCALEX?SCALEX:sx;
            float sy =SCALEY+(1-SCALEY)* (1-(span/SCALESPAN));sy =sy>1?1:sy;sy = sy<SCALEY?SCALEY:sy;
            npdw->m_pMoveNode->setScale(sx,sy);
        }
        
        span = p.x-TARGETX_2;
        if (span>0) {
            float tempFloat =span/(660-TARGETX_2);
            npdw->m_pMoveNode->setPositionX(npdw->opx-tempFloat*SUOXIAOX);
        }else
        {
            npdw->m_pMoveNode->setPositionX(npdw->opx);
        }
    }
    
    
    if(isStartHuiFuDown)
    {
        selectNpdw->setPositionY(selectNpdw->getPositionY()-M_KaiPaiYiDongHuiFuSpeed);
        if (selectNpdw->getPositionY()<selectNpdw->opy2) {
            selectNpdw->setPositionY(selectNpdw->opy2);
            isStartHuiFuDown = false;
        }
    }else if(isStartHuiFuUp){
        if (huiFuSpeedX==-1) {
            selectNpdw_Up->setPositionY(selectNpdw_Up->getPositionY()+M_KaiPaiYiDongHuiFuSpeed);
            if (selectNpdw_Up->getPositionY()>selectNpdw_Up->opy2) {
                selectNpdw_Up->setPositionY(selectNpdw_Up->opy2);
                isStartHuiFuUp = false;
                selectNpdw_Up->setZOrder(0);
                unschedule(schedule_selector(MB_LayerPetEquipment::updateSelectNpdw_Up));
                NSGameHelper::setAllOpacity(selectNpdw_Up,255);
            }
        }else
        {
            selectNpdw_Up->setPositionX(selectNpdw_Up->getPositionX()+huiFuSpeedX);
            if ((huiFuSpeedX>0&& selectNpdw_Up->getPositionX()>selectNpdw_Up->opx2)||(huiFuSpeedX<0&& selectNpdw_Up->getPositionX()<selectNpdw_Up->opx2)) {
                selectNpdw_Up->setPositionX(selectNpdw_Up->opx2);
                isStartHuiFuUp = false;
                selectNpdw_Up->setZOrder(0);
            }
        }
    }
}
void MB_LayerPetEquipment::scrollViewDidScroll(CCScrollView* view)
{
    if (view->isTouchMoved () == false && fabsf(view->getScrollDistance().x)<1.5f) {
        ScolltoCenter();
    }
}

void MB_LayerPetEquipment::ScolltoCenter()
{
    int offset =-selectNpdw->opx2+200;
    m_pScollerView->getContainer()->stopAllActions();
    m_pScollerView->unschedule(schedule_selector(CCScrollView::deaccelerateScrolling));
    m_pScollerView->getContainer()->runAction(CCMoveTo::create(fabsf(m_pScollerView->getContainer()->getPositionX()-offset)/400, ccp(offset,0)));
}
void MB_LayerPetEquipment::scrollViewDidZoom(CCScrollView* view)
{
    
}

void MB_LayerPetEquipment::movetoShow()
{
    
}

void MB_LayerPetEquipment::onClickShangZhen(CCObject* obj)
{
    TutorialTriggerComplete
    if (checkInTeam(selectNpdw->m_nPetId)) {
        toTiShi(1);
        return;
    }else if(checkTypeInTeam(selectNpdw->m_nPetId))
    {
        toTiShi(0);
        return;
    }else if(selectNpdw->m_pInguard->isVisible())
    {
        toTiShi(3);
        return;
    }
    else
    {
        MB_PetData* pData = MB_PetMgr::getInstance()->getPetDataByUID(selectNpdw->m_nPetId);
        for (int i =0; i<shouhuPetTypeIDVec.size(); i++) {
            if (pData->getPetTypeID()==shouhuPetTypeIDVec[i]) {
                toTiShi(5);
                return;
            }
        }
    }
    int i;
    for (i=0 ; i <CARD_IN_GAME;  i++) {
        if(teamV[i] == -1){
            teamV[i] = selectNpdw->m_nPetId;
            MB_NodePetDuiWu* npdw = (MB_NodePetDuiWu*)m_pNodeScroller->getChildByTag(100+i);
            npdw->setPetID(selectNpdw->m_nPetId);//设置上场卡牌为焦点卡牌
            CCArray* children = m_pTestNode->getChildren();
            selectNpdw->setShangZhen(true);
            float tempOpx2 = selectNpdw->opx2;
            int _pos = children->count()-1-insertZhen(selectNpdw->m_nPetId);
            MB_NodePetDuiWu* toExchangeNode = (MB_NodePetDuiWu*)children->objectAtIndex(_pos);
            selectNpdw->retain();
            children->removeObject(selectNpdw);
            children->insertObject(selectNpdw,_pos);
            selectNpdw->release();
            if (toExchangeNode!=NULL && toExchangeNode->opx2<selectNpdw->opx2 ) {
                selectNpdw->m_nZorder = toExchangeNode->m_nZorder;
                selectNpdw->setZOrder(selectNpdw->m_nZorder);
                selectNpdw->opx2 =toExchangeNode->opx2;
                selectNpdw->setPosition(ccp(selectNpdw->opx2, selectNpdw->opy2));
                selectNpdw->setSelectedState(false);
                selectNpdw = NULL;
            }else
            {
                setDJSZ(true);
            }
            
            for (int j = 0; j< _pos+1; j++) {
                npdw = (MB_NodePetDuiWu*)children->objectAtIndex(j);
                if (npdw->opx2<=tempOpx2&&npdw->m_nPetId!=teamV[i]) {
                    npdw->m_nZorder--;
                    npdw->setZOrder(npdw->m_nZorder);
                    npdw->opx2+=+npdw->m_nWidth;
                    npdw->setPositionX(npdw->opx2);
                }
            }
            
            update(0);
            break;
        }
    }
    if(obj!=NULL &&i==CARD_IN_GAME)
    {
        ScolltoCenter();
        m_pZheZhao->setVisible(true);
        setMyTouchEnable(false,false);
    }
}

void MB_LayerPetEquipment::xiaZhen(bool isCheckEquip)
{
    for (int i = 0; i < CARD_IN_GAME; i++) {
        if (teamV[i]!=-1){
            if (teamV[i] == selectNpdw_Up->m_nPetId){
                //TODODO 如果携带装备不可下阵
                if (isCheckEquip) {
                    if (zhuangbeiIndexVec[i]>99) {
                        toTiShi(2);
                        return;
                    }
                    
                    if(MB_GuardInterface::getInstance()->checkIsGuardPos(i+1)) {
                        toTiShi(4);
                        return;
                    }
                }
                
                CCArray* children = m_pTestNode->getChildren();
                for (int j=0; j< children->count();j++) {
                    MB_NodePetDuiWu* npdw =  (MB_NodePetDuiWu*)children->objectAtIndex(j);
                    if (npdw->m_nPetId==selectNpdw_Up->m_nPetId) {
                        if (npdw->m_nPetId==selectNpdw->m_nPetId) {
                            setDJSZ(false);
                        }
                        teamV[i] = -1;
                        selectNpdw_Up->setPetID(-1);
                        selectNpdw_Up->setPositionY(selectNpdw_Up->opy2);
                        isStartHuiFuUp = true;
                        float tempOpx2 = npdw->opx2;
                        int _pos = children->count()-1- insertZhen(npdw->m_nPetId);
                        MB_NodePetDuiWu* toExchangeNode = (MB_NodePetDuiWu*)children->objectAtIndex(_pos);
                        npdw->setShangZhen(false);
                        npdw->retain();
                        children->removeObject(npdw);
                        children->insertObject(npdw,_pos);
                        npdw->release();
                        if (toExchangeNode!=NULL && toExchangeNode->opx2>npdw->opx2 ) {
                            npdw->m_nZorder = toExchangeNode->m_nZorder;
                            npdw->setZOrder(npdw->m_nZorder);
                            npdw->opx2 =toExchangeNode->opx2;
                            npdw->setPosition(ccp(npdw->opx2,npdw->opy2));
                        }
                        
                        for (int k = _pos+1; k<children->count(); k++) {
                            npdw = (MB_NodePetDuiWu*)children->objectAtIndex(k);
                            if (npdw->opx2>tempOpx2) {
                                npdw->m_nZorder++;
                                npdw->setZOrder(npdw->m_nZorder);
                                npdw->opx2-=npdw->m_nWidth;
                                npdw->setPositionX(npdw->opx2);
                            }
                        }
                        
                        update(0);
                        break;
                    }
                }
                return;
            }
        }
    }
}



int MB_LayerPetEquipment::insertZhen(uint64_t petId)
{
    MB_PetData* petData1;
    m_pAllRoleArray->sortArray(compare);
    for (int i = 0; i < m_nListSize; ++i)
    {
        petData1 = (MB_PetData*)m_pAllRoleArray->objectAtIndex(i);
        
        if (petData1->getPetID()==petId) {
            return i;
        }
    }
}

void MB_LayerPetEquipment::toTiShi(int index)
{
    isStartHuiFuDown = true;
    m_pDJSZ->setVisible(true);
    m_pDetail->setVisible(true);
    if(index==0)
    {
        MB_Message::sharedMB_Message()->showMessage("不能上阵相同卡牌");
    }else if(index==1)
    {
        MB_Message::sharedMB_Message()->showMessage("该卡牌已在队伍中");
    }else if(index==2)
    {
        MB_Message::sharedMB_Message()->showMessage("携带装备的卡牌不可下阵");
    }else if(index==3)
    {
        MB_Message::sharedMB_Message()->showMessage("守护不可上阵");
    }else if(index==4)
    {
        MB_Message::sharedMB_Message()->showMessage("拥有守护的卡牌不可下阵");
    }else if(index==5)
    {
        MB_Message::sharedMB_Message()->showMessage("守护中已有相同精灵");
    }
}

void MB_LayerPetEquipment::onClickDetail(CCObject*)
{
    TutorialTriggerComplete
    MB_ResWindow* layerDetail = MB_LayerPetDetail::createWithPetID(selectNpdw->m_nPetId);
    pushWindow(layerDetail,true);
}

void MB_LayerPetEquipment::onClickGHYSSH(CCObject* pSender)//更换妖灵守护
{
    m_pToVs4->setVisible(false);
    m_pToVs3->setVisible(false);
    m_pDJSZ->setVisible(false);
    m_pToMoveNode->runAction(CCSequence::create( CCMoveTo::create(.3f, ccp(320,996)),CCCallFunc::create(this, callfunc_selector(MB_LayerPetEquipment::finish)),NULL));
    m_pToMoveNode2->runAction(CCMoveTo::create(.3f, ccp(320,478)));
    m_pNodeNaveigation->runAction(CCMoveTo::create(.3f, ccp(320,268)));
    
    if (m_pYlNode[0]->getChildrenCount()==0) {
        MB_NodeYaoLingDuiWu* yldw;
        for (int i = 0; i < CARD_IN_GAME; i++) {
            yldw = MB_NodeYaoLingDuiWu::create(i);
            m_pYlNode[i]->addChild(yldw);
        }
    }
}

void MB_LayerPetEquipment::onClickFHDWLB(CCObject* pSender)//关闭妖灵守护
{
    m_pToMoveNode->runAction(CCSequence::create( CCMoveTo::create(.3f, ccp(320,1136)),CCCallFunc::create(this, callfunc_selector(MB_LayerPetEquipment::finish)),NULL));
    m_pToMoveNode2->runAction(CCMoveTo::create(.3f, ccp(320,568)));
    m_pNodeNaveigation->runAction(CCMoveTo::create(.3f, ccp(320,408)));
}

void MB_LayerPetEquipment::finish()
{
    if (m_pFhdwlb->isVisible()) {
        m_pToVs2->setVisible(true);
        m_pToVs3->setVisible(true);
        m_pToVs4->setVisible(true);
        m_pDJSZ->setVisible(true);
        m_pFhdwlb->setVisible(false);
        
        for (int i = 0; i < CARD_IN_GAME; i++) {
            m_pYlNode[i]->removeAllChildren();
        }
    }else
    {
        m_pToVs2->setVisible(false);
        m_pFhdwlb->setVisible(true);
    }
}
void MB_LayerPetEquipment::updateSelectNpdw_Up(float dt)
{
    float py = selectNpdw_Up->getPositionY();
    float o = (1-(-py/(selectNpdw_Up->opy2-XIAZHENY-50)))*255;
    o = o<0?0:o;
    NSGameHelper::setAllOpacity(selectNpdw_Up,o);
}
void MB_LayerPetEquipment::registerWithTouchDispatcher(void){
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 128 , false);
}
bool MB_LayerPetEquipment::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    if (m_pZheZhao->isVisible())return true;
    if(isStartHuiFuDown||isStartHuiFuUp||m_pFhdwlb->isVisible())return false;
    CCPoint point = pTouch->getLocation();
    if (point.y>785  &&point.y<1100) {
        for (int i=0; i<rectV.size(); i++) {
            if (rectV[i].containsPoint(point)) {
                selectNpdw_Up = (MB_NodePetDuiWu*)m_pNodeScroller->getChildByTag(i+100);
                if (selectNpdw_Up->m_nPetId==-1) {
                    return false;
                }
                selectNpdw_Up->setZOrder(999);
                m_pNodeScroller->setZOrder(m_pNodeNaveigation->getZOrder()+1);
                return true;
            }
        }
    }else if(point.y>475  &&point.y<710)
    {
        m_pNodeNaveigation->setZOrder(m_pNodeScroller->getZOrder()+1);
        isTouchBlow = true;
        return true;
    }
    return false;
}
void MB_LayerPetEquipment::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    if(isStartHuiFuDown||isStartHuiFuUp||isZuZhiTouch||m_pZheZhao->isVisible())return;
    CCPoint point = pTouch->getLocation();
    CCPoint point2 = pTouch->getDelta();
    if (isTouchUpOrDown>2|| (isTouchUpOrDown==0&& point.y<750)) {//触摸下方
        if (isTouchUpOrDown==TD_Down_V) {
            selectNpdw->setPositionY(selectNpdw->getPositionY() + point2.y);
            if (selectNpdw->getPositionY()< selectNpdw->opy2) {
                selectNpdw->setPositionY(selectNpdw->opy2);
            }else if(selectNpdw->getPositionY()>350)
            {
                isZuZhiTouch = true;
                onClickShangZhen(NULL);
                isStartHuiFuDown = true;
                m_pDJSZ->setVisible(true);
                m_pDetail->setVisible(true);
                return;
            }
        }else if (point2.y>fabsf(point2.x)) {
            isTouchUpOrDown = TD_Down_V;
            m_pDJSZ->setVisible(false);
            m_pDetail->setVisible(false);
            m_pScollerView->setTouchEnabled(false);
            m_pScollerView->unschedule(schedule_selector(CCScrollView::deaccelerateScrolling));
            selectNpdw->m_pDetailBtn->setTouchEnabled(false);
        }else{
            isTouchUpOrDown = TD_Down_H;
            selectNpdw->m_pDetailBtn->setTouchEnabled(false);
        }
    }
    else if (isTouchUpOrDown<3|| (isTouchUpOrDown==0&&point.y>750))//触摸上方
    {
        if (isTouchUpOrDown==TD_Up_V) {
            selectNpdw_Up->setPositionY(selectNpdw_Up->getPositionY() + point2.y);
            if (selectNpdw_Up->getPositionY()> selectNpdw_Up->opy2) {
                selectNpdw_Up->setPositionY(selectNpdw_Up->opy2);
            }else if(selectNpdw_Up->getPositionY()<XIAZHENY)
            {
                isZuZhiTouch = true;
                xiaZhen(true);
                isStartHuiFuUp = true;
                return;
            }
        }else if (isTouchUpOrDown==TD_Up_H) {
            selectNpdw_Up->setPositionX(selectNpdw_Up->getPositionX() + point2.x);
            int supTag =selectNpdw_Up->getTag();
            MB_NodePetDuiWu* node;
            if (supTag>100)
            {
                node =(MB_NodePetDuiWu*)m_pNodeScroller->getChildByTag(supTag-1);
                if (selectNpdw_Up->getPositionX()<node->opx2+selectNpdw_Up->m_nWidth/2)
                {
                    exchangeNpdw(node);
                    return;
                }
            }
            if (supTag<100+CARD_IN_GAME-1)
            {
                node =(MB_NodePetDuiWu*)m_pNodeScroller->getChildByTag(supTag+1);
                if (selectNpdw_Up->getPositionX()>node->opx2-selectNpdw_Up->m_nWidth/2)
                {
                    exchangeNpdw((MB_NodePetDuiWu*)node);
                    return;
                }
            }
        }else if (-point2.y>fabsf(point2.x)) {
            isTouchUpOrDown = TD_Up_V;
            m_pScollerView->setTouchEnabled(false);
            selectNpdw_Up->m_pDetailBtn->setTouchEnabled(false);
            schedule(schedule_selector(MB_LayerPetEquipment::updateSelectNpdw_Up));
        }else{
            isTouchUpOrDown = TD_Up_H;
            selectNpdw_Up->m_pDetailBtn->setTouchEnabled(false);
        }
    }
}



void MB_LayerPetEquipment::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    if (m_pZheZhao->isVisible()) {
        m_pZheZhao->setVisible(false);
        setMyTouchEnable(true,false);
        CCPoint point = pTouch->getLocation();
        if (point.y>785  &&point.y<1100) {
            for (int i=0; i<rectV.size(); i++) {
                if (rectV[i].containsPoint(point)) {
                    selectNpdw_Up = (MB_NodePetDuiWu*)m_pNodeScroller->getChildByTag(i+100);
                    MB_NodePetDuiWu* tempNpdw = selectNpdw;
                    xiaZhen();
                    selectNpdw= tempNpdw;
                    onClickShangZhen(NULL);
                    return;
                }
            }
        }
    }else
    {
        if (!m_pScollerView->isTouchEnabled()) {
            m_pScollerView->setTouchEnabled(true);
        }
        if (isTouchUpOrDown>2)//触摸下方离手
        {
            if (isTouchBlow) {
                toTiShi(-1);
            }
            selectNpdw->m_pDetailBtn->setTouchEnabled(true);
        }else if(isTouchUpOrDown!=TD_NONE)//触摸上方离手
        {
            isStartHuiFuUp = true;
            if (isTouchUpOrDown==TD_Up_H) {
                if (selectNpdw_Up->getPositionX()>selectNpdw_Up->opx2) {
                    huiFuSpeedX = -M_KaiPaiYiDongHuiFuSpeed;
                }else
                {
                    huiFuSpeedX = M_KaiPaiYiDongHuiFuSpeed;
                }
            }else
            {
                huiFuSpeedX = -1;
            }
            selectNpdw_Up->m_pDetailBtn->setTouchEnabled(true);
        }
        isZuZhiTouch = false;
        isTouchUpOrDown = TD_NONE;
        isTouchBlow = false;
    }
}

void MB_LayerPetEquipment::exchangeNpdw(MB_NodePetDuiWu* npdw)
{
    float opx2 = npdw->opx2;
    float opy2 = npdw->opy2;
    int tag = npdw->getTag();
    
    npdw->stopAllActions();
    npdw->runAction(CCMoveTo::create(.1f, ccp(selectNpdw_Up->opx2,npdw->getPositionY())));
    npdw->opx2 = selectNpdw_Up->opx2;
    npdw->opy2 = selectNpdw_Up->opy2;
    npdw->setTag(selectNpdw_Up->getTag());
    
    selectNpdw_Up->opx2 = opx2;
    selectNpdw_Up->opy2 = opy2;
    selectNpdw_Up->setTag(tag);
    
    teamV[npdw->getTag()-100] = npdw->m_nPetId;
    teamV[selectNpdw_Up->getTag()-100] = selectNpdw_Up->m_nPetId;
    
    int zhuangbeiIndex1 = npdw->getTag()-100;
    int zhuangbeiIndex2 = selectNpdw_Up->getTag()-100;
    int tempInt = zhuangbeiIndexVec[zhuangbeiIndex1];
    zhuangbeiIndexVec[zhuangbeiIndex1] = zhuangbeiIndexVec[zhuangbeiIndex2];
    zhuangbeiIndexVec[zhuangbeiIndex2] = tempInt;
}

void MB_LayerPetEquipment::setDetail()
{
    MB_PetData  *petData = MB_PetMgr::getInstance()->getPetDataByUID(selectNpdw->m_nPetId);
    if (petData==NULL)
    {
        return;
    }
    char reaalname[100];
    m_pPetName->setString(MB_PetMgr::getInstance()->getPetRealName(reaalname, petData->getPetID()));
    char databuf[50];
    sprintf(databuf, "%d", petData->getPetAttack());
    m_pAttack->setString(databuf);
    sprintf(databuf, "%d", petData->getPetHpMax());
    m_pLife->setString(databuf);
    sprintf(databuf, "%llu", petData->getPetFightPower());
    m_pFightPower->setString(databuf);
    sprintf(databuf, "%d", petData->getPetLevel());
    m_pNodeLevel->setString(databuf);
    m_pMoveNode1->setPositionX((NSGameHelper::get_length(petData->getPetLevel())-2)*7);
    
    NSGameHelper::setStar(m_pStar, petData->getTemplateStar());
}
void MB_LayerPetEquipment::setMyTouchEnable(bool b,bool isContainSelf)
{
    m_pScollerView->setTouchEnabled(b);
    MB_NodePetDuiWu* npdw;
    for (int i=0 ; i <CARD_IN_GAME;  i++) {
        npdw = (MB_NodePetDuiWu*)m_pNodeScroller->getChildByTag(100+i);
        npdw->m_pDetailBtn->setTouchEnabled(b);
    }
    CCArray* children = m_pTestNode->getChildren();
    for (int i=0; i< children->count();i++) {
        npdw =  (MB_NodePetDuiWu*)children->objectAtIndex(i);
        npdw->m_pDetailBtn->setTouchEnabled(b);
    }
    
    if (isContainSelf) {
        this->setTouchEnabled(b);
    }
}

void MB_LayerPetEquipment::reloadZhuangbeiIndexVec()
{
    zhuangbeiIndexVec.clear();
    for (int i =0; i<MEMBER_NUM; i++) {
        MB_PetGuardData* pData = MB_GuardInterface::getInstance()->getPetGuardDataByPos(i+1);
        if (pData != NULL)
        {
            shouHuV.push_back(pData->getPetUid());
        }
        if (MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet == NULL) {
            teamV[i] = -1;
            lastTeamV[i] = -1;
            zhuangbeiIndexVec.push_back(i);
        }else
        {
            TeamDataStruct* ts = MB_TeamData::getInstance()->getTeamMemberByIndex(i);
            teamV[i] = ts->m_pPet->getPetID();
            lastTeamV[i] = ts->m_pPet->getPetID();
            if (ts->m_pEquip1 != NULL||ts->m_pEquip2 != NULL||ts->m_pEquip3 != NULL||ts->m_pTreasure1 != NULL||ts->m_pTreasure2 != NULL||ts->m_pTreasure3 != NULL) {
                zhuangbeiIndexVec.push_back(i+100);
            }else
            {
                zhuangbeiIndexVec.push_back(i);
            }
        }
    }
}

void MB_LayerPetEquipment::onLevelUpClick(CCObject *){
    TutorialTriggerComplete
    MB_LayerPetUpdate* layer = MB_LayerPetUpdate::create(selectNpdw->m_nPetId);
    if (layer != NULL) {
        
        this->pushWindow(layer, true);
    }
}
void MB_LayerPetEquipment::onQualityUpClick(CCObject *){
    MB_LayerPetEnhance* layer = MB_LayerPetEnhance::create(kPetEnhanceEntrDetail, selectNpdw->m_nPetId);
    if (layer != NULL){
        
        this->pushWindow(layer,true);
    }
}

void MB_LayerPetEquipment::onJiBanClick(CCObject* obj)
{
    this->addChild(MB_SkillDetail::create(selectNpdw->m_nPetId,2));
}

void MB_LayerPetEquipment::onResetWnd()
{
    MB_ResWindow::onResetWnd();
    if (isUpdateUI) {
        isUpdateUI = false;
        updateUI();
    }
    if (isUpdateYaoLing) {
        MB_PetGuardData* pData;
        for (int i = 0; i<CARD_IN_GAME; i++) {
            pData = MB_GuardInterface::getInstance()->getPetGuardDataByPos(i+1);
            if (pData!=NULL) {
                shouhuPetTypeIDVec.push_back(pData->getPetTypeId());
            }
        }
        isUpdateYaoLing =false;
        MB_NodeYaoLingDuiWu* yldw;
        for (int i = 0; i < CARD_IN_GAME; i++) {
            m_pYlNode[i]->removeAllChildren();
            yldw = MB_NodeYaoLingDuiWu::create(i);
            m_pYlNode[i]->addChild(yldw);
        }
    }
}
void MB_LayerPetEquipment::updateUI()
{
    shouHuV.clear();
    for (int i = 0; i < CARD_IN_GAME; i++) {
        MB_PetGuardData* pData = MB_GuardInterface::getInstance()->getPetGuardDataByPos(i+1);
        if (pData != NULL)
        {
            shouHuV.push_back(pData->getPetUid());
        }
    }
    
    m_nListSize = m_pAllRoleArray->count();
    //排序
    if (m_nListSize > 1) {
        m_pAllRoleArray->sortArray(compare);
    }
    selectNpdw = NULL;
    MB_NodePetDuiWu* npdw;
    m_pTestNode->removeAllChildren();
    int nPosX = NPOSX;
    int nPosY = 95;
    for (int i = 0; i < m_nListSize; i++)
    {
        MB_PetData* petData = (MB_PetData*)m_pAllRoleArray->objectAtIndex(i);
        if (petData!=NULL) {
            npdw = MB_NodePetDuiWu::create(petData->getPetID(),false);
            npdw->m_nZorder =99999-i;
            m_pTestNode->addChild(npdw,npdw->m_nZorder);
            npdw->opx2 =nPosX+npdw->m_nWidth;
            npdw->opy2 = nPosY;
            npdw->opx =npdw->m_pMoveNode->getPositionX();
            npdw->setShangZhen(checkInTeam(npdw->m_nPetId));
            npdw->setShouHu(MB_GuardInterface::getInstance()->checkIsGuardPet(npdw->m_nPetId));
            npdw->setPosition(ccp(npdw->opx2,npdw->opy2));
            nPosX += npdw->m_nWidth;
            npdw->m_pDetailBtn->setTouchEnabled(false);
            
            if (i==5 && selectNpdw!=NULL) {
                selectNpdw->setSelectedState(false);
            }
            selectNpdw =npdw;
        }
    }
    m_pScollerView->setContentSize(CCSize( nPosX+444, m_pNodeNaveigation->getContentSize().height));
    
    m_pNodeScroller->removeAllChildren();
    //主将
    for (int i = 0; i < CARD_IN_GAME; i++) {
        if (teamV[i]!=-1){
            npdw = MB_NodePetDuiWu::create(teamV[i]);
        }
        else {
            npdw = MB_NodePetDuiWu::create(-1);
        }
        npdw->setTag(i+100);
        npdw->opx2 = npdw->m_nWidth*(.5f + i);
        npdw->opy2 = npdw->getPositionY();
        npdw->setPositionX(npdw->opx2);
        m_pNodeScroller->addChild(npdw);
        
        CCSprite* spr =CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("slot_team_empty.png"));
        spr->setPosition(npdw->getPosition());
        m_pNodeScroller->addChild(spr,-1);
        rectV.push_back(CCRectApplyAffineTransform(CCRect(npdw->getPositionX()-npdw->m_nWidth*.5f,npdw->getPositionY()-npdw->m_nHeight*.5f,npdw->m_nWidth,npdw->m_nHeight), m_pNodeScroller->nodeToParentTransform()));
    }
    m_pNodeScroller->setContentSize(CCSize( npdw->m_nWidth*6,m_pNodeScroller->getContentSize().height));
    
    
    update(0);
}
