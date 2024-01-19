
#include "MB_NodeShow.h"
#include "MB_SceneGame.h"
#include "MB_BattleConfigData.h"

MB_NodeShow::MB_NodeShow()
:mAnimationMgr(NULL),
m_pSpriteFace(NULL),
tk_ActionMgr(NULL),
m_bSprite(NULL),
m_pCamp(NULL),
//m_pElite(NULL),
//m_pCard(NULL),
m_pDamage(NULL),
m_pPetname(NULL),
m_pSp(NULL),
m_pRoot(NULL),
m_pAnimationNode(NULL)
{
    m_pNodeCapacity1 = NULL;
    m_pShadow = NULL;
    m_pSpriteFaceToJump = NULL;
    m_pToScaleNode = NULL;
    m_bBoss = false;
    m_bSetIsDetail = false;
    m_pFighter = new p_fighter;
    m_pCurrentAction  = NULL;
    m_pStartAction =  NULL;
    m_pStarFrame = NULL;
    m_pRankFrame = NULL;
    m_pCardVisible = NULL;
    sprite = NULL;
    m_pNodeSP = NULL;
    m_pPetLevel = NULL;
    m_pDeadSpr = NULL;
}

MB_NodeShow::~MB_NodeShow(){
    
    this->removeAllChildrenWithCleanup(true);
    this->stopAllActions();
    delete m_pFighter;
    m_pRoot = NULL;
    
    CC_SAFE_RELEASE_NULL(m_pNodeCapacity1);
    CC_SAFE_RELEASE_NULL(m_pShadow);
    CC_SAFE_RELEASE_NULL(m_pToScaleNode);
    CC_SAFE_RELEASE_NULL(mAnimationMgr);
    CC_SAFE_RELEASE(m_pSpriteFace);
    CC_SAFE_RELEASE(m_bSprite);
    CC_SAFE_DELETE(tk_ActionMgr);
    CC_SAFE_RELEASE(m_pCamp);
    CC_SAFE_RELEASE(m_pDamage);
    CC_SAFE_RELEASE(m_pPetname);
    CC_SAFE_RELEASE(m_pSp);
    CC_SAFE_RELEASE_NULL(m_pStartAction);
    CC_SAFE_RELEASE_NULL(m_pSpriteFaceToJump);
    
    CC_SAFE_RELEASE(m_pStarFrame);
    CC_SAFE_RELEASE(m_pRankFrame);
    CC_SAFE_RELEASE(m_pCardVisible);
    CC_SAFE_RELEASE_NULL(m_pNodeSP);
    CC_SAFE_RELEASE_NULL(m_pPetLevel);
    CC_SAFE_RELEASE_NULL(m_pDeadSpr);
    
}
bool MB_NodeShow::init(p_fighter *fight,int type,CCNode *rootNode,bool isWorldBoss){
    
//    CCLOG("INIT POS:%d HP:%d",fight->petPos,fight->petHp);
    
    
    m_pFighter->petId = fight->petId;
    m_pFighter->petTypeID = fight->petTypeID;
    m_pFighter->petPos = fight->petPos;
    m_pFighter->petHp = fight->petHp;
    m_pFighter->petHpMax = fight->petHpMax;
    m_pFighter->petSp = fight->petSp;
    m_pFighter->petQuality = fight->petQuality;
    m_pFighter->petLevel = fight->petLevel;
    m_pFighter->next = NULL;

    m_nType = type;
    MB_PetTemplate * templete = MB_PetMgr::getInstance()->getPetTemplateByID(m_pFighter->petTypeID);

    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    CCNode *animations;
    if (isWorldBoss) {
        animations = ccbReader->readNodeGraphFromFile("res/card_node_battle_actionWorldBoss.ccbi",this);
        m_pShadow->removeFromParent();
        m_pToScaleNode->removeFromParent();
    }else
    {
        if (fight->petPos>0) {
            animations = ccbReader->readNodeGraphFromFile("res/card_node_battle_action.ccbi",this);
        }
        else
        {
            animations = ccbReader->readNodeGraphFromFile("res/card_node_battle_action2.ccbi",this);
            m_pShadow->setZOrder(-1);
        }
    }

    
    this->setAnimationMgr(ccbReader->getAnimationManager());
    mAnimationMgr->setAnimationCompletedCallback(this, callfunc_selector(MB_NodeShow::AnimationCompletedCallback));
    m_pAnimationNode = animations;

    
    this->addChild(animations,0);
    this->setContentSize(CCSize(64,96));
    ccbReader->release();
    
    isSetCallBack = false;
    tk_ActionMgr = new MB_ActionMgr(this,rootNode);

    if (templete != NULL) {
        int shape = NSGameHelper::getShapeTypeByRank(m_pFighter->petQuality);
        setFileName(templete->getPetCard(shape));
        
        kindom =templete->getPetKingdom();
        
        CCTexture2D *textrue;
        if (fight->petPos>0) {
            textrue = CCTextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("round_icon_card/round_card_%d.png",templete->getPetTypeID()+shape)->getCString()  );
        }else
        {
            textrue = CCTextureCache::sharedTextureCache()->addImage(templete->getPetCard(NSGameHelper::getShapeTypeByRank(m_pFighter->petQuality)));
        }
        if(textrue !=NULL){
            
            CCSpriteFrame* frame  =CCSpriteFrame::createWithTexture(textrue,CCRect(0,0,textrue->getContentSize().width,textrue->getContentSize().height));
            setSpriteFrame(frame);
            
            if (fight->petPos>0) {
                textrue = CCTextureCache::sharedTextureCache()->addImage(templete->getPetCard(NSGameHelper::getShapeTypeByRank(m_pFighter->petQuality)));
                frame  =CCSpriteFrame::createWithTexture(textrue,CCRect(0,0,textrue->getContentSize().width,textrue->getContentSize().height));
                m_pSpriteFaceToJump->setDisplayFrame(frame);
            }
        }else {
            
            setSpriteFrame(NULL);
        }
        
        NSGameHelper::setRankFrame(m_pRankFrame,templete->getPetStar(),m_pFighter->petQuality);
        m_pCardVisible->setVisible(true);
       
        m_pPetname->setString(templete->getPetName(NSGameHelper::getShapeTypeByRank(m_pFighter->petQuality)));
        m_pPetLevel->setString( CCString::createWithFormat("%d", m_pFighter->petLevel )->getCString());
        
    }else {
            setSpriteFrame(NULL);
        }
  
  
    m_pRoot = dynamic_cast<MB_SceneGame*>(rootNode);
    
    m_pDamage->setZOrder(9);
    return  true;
}


void MB_NodeShow::AnimationCompletedCallback()
{
    callAnimationByName("idle");
    //mAnimationMgr->setAnimationCompletedCallback(NULL, NULL);
}

void MB_NodeShow::setAnimationMgr(CCBAnimationManager *pAnimationMgr){

    CC_SAFE_RELEASE_NULL(mAnimationMgr);
    mAnimationMgr = pAnimationMgr;
    CC_SAFE_RETAIN(mAnimationMgr);
}
cocos2d::SEL_MenuHandler MB_NodeShow::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName){

    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_NodeShow::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

    return NULL;
}
bool MB_NodeShow::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteFace", CCSprite *, this->m_pSpriteFace);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "blood", CCSprite *, this->m_bSprite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pCamp", CCSprite *, m_pCamp);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pCard", CCSprite *, m_pCard);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pElite", CCSprite *, m_pElite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "damage", CCNode *, m_pDamage);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "petname", CCLabelTTF *, m_pPetname);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp", CCSprite *, m_pSp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pStarFrame", CCSprite *, m_pStarFrame);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pRankFrame", CCSprite *, m_pRankFrame);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cardvisible", CCNode *, m_pCardVisible);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeSP", CCNode *, m_pNodeSP);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "petLevel", CCLabelBMFont *, m_pPetLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pDeadSpr", CCNode *, m_pDeadSpr);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pToScaleNode", CCNode *, m_pToScaleNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteFaceToJump", CCSprite *, m_pSpriteFaceToJump);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pShadow", CCNode *, m_pShadow);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeCapacity1", CCNode *, m_pNodeCapacity1);
    
    return  false;
}

void MB_NodeShow::callAnimationByName(const char *animationName){

    m_ActionName = animationName;
    //executeAction();
    onStartAction();
}
p_fighter * MB_NodeShow::getFighter(){

    return m_pFighter;
}
void MB_NodeShow::setSpriteFrame(CCSpriteFrame *frame) {
    

    if (frame != NULL) {
        
        m_pSpriteFace->setDisplayFrame(frame);
    }
    
    CCNode *node=m_bSprite->getParent();
    CCPoint pos=m_bSprite->getPosition();
    int z= m_bSprite->getZOrder();
    float scalex = m_bSprite->getScaleX();
    float scaley = m_bSprite->getScaleY();
    m_bSprite->setVisible(false);
 
    CCSprite* sprite1 =CCSprite::createWithSpriteFrame(m_bSprite->displayFrame());
    sprite1->setColor(m_bSprite->getColor());
    
    m_pBlood = CCProgressTimer::create(sprite1);
    m_pBlood->setType(kCCProgressTimerTypeBar);
    m_pBlood->setMidpoint(ccp(0,0));
    m_pBlood->setBarChangeRate(ccp(1,0));
//    m_pBlood->setReverseProgress(true);
    m_pBlood->setPosition(pos);
    m_pBlood->setScaleX(scalex);
    m_pBlood->setScaleY(scaley);
    node->addChild( m_pBlood ,z );
    changeBooldAndSpPercentage(m_pFighter->petHp*100.0f/m_pFighter->petHpMax,0);
        
    node=m_pSp->getParent();
    pos=m_pSp->getPosition();
    z= m_pSp->getZOrder();
    scalex = m_pSp->getScaleX();
    scaley = m_pSp->getScaleY();

    m_pSp->setVisible(false);
    
    sprite =CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("tmzz_rage_%d.png",kindom)->getCString()));
    m_pSpbar = CCProgressTimer::create(sprite);
    m_pSpbar->setType(kCCProgressTimerTypeRadial);
    m_pSpbar->setReverseProgress(true);
    m_pSpbar->setPosition(pos);
    node->addChild(m_pSpbar,z );
    m_pSpbar->setScaleX(scalex);
    m_pSpbar->setScaleY(scaley);
    changeBooldAndSpPercentage(m_pFighter->petSp,1);
}
void  MB_NodeShow::onExit(){

    CCNode::onExit();
    mAnimationMgr->setAnimationCompletedCallback(NULL, NULL);
}
void  MB_NodeShow::changeBooldAndSpPercentage(int per,int index){
    if (index==0) {
        m_pBlood->setPercentage(per);
    }else{
        m_pSpbar->setPercentage(per);
    }
    
}

void MB_NodeShow::removeAndClean(){
    
    mAnimationMgr->setAnimationCompletedCallback(NULL, NULL);
    this->removeFromParentAndCleanup(true);
}
MB_NodeShow * MB_NodeShow::createMB_NodeShow(p_fighter *fighter,int type,CCNode *rootNode,bool isWorldBoss){
    
    MB_NodeShow *node = new MB_NodeShow();
    
    if(node && node->init(fighter,type,rootNode,isWorldBoss)){
       
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return NULL;
}

//开始攻击 返回攻击时间
void MB_NodeShow::startAction(p_action *list )
{
    m_pCurrentAction = list;
    tk_ActionMgr->playKillTheAnimation(list);
}
void MB_NodeShow::onStartAction()
{
    m_PosBeforeAnimation.x = 0;
    m_PosBeforeAnimation.y = 0;
    executeAction();
}
void MB_NodeShow::executeAction()
{
    mAnimationMgr->runAnimationsForSequenceNamed(m_ActionName.c_str());
}
void MB_NodeShow::changeBoold(int blooddt){
    
    
    
     m_pFighter->petHp = m_pFighter->petHp + blooddt ;
    
    if( m_pFighter->petHp  >  m_pFighter->petHpMax)
    {
        m_pFighter->petHp  = m_pFighter->petHpMax;
    }
    
//    CCLOG("POS:%d HP:%d",m_pFighter->petPos,m_pFighter->petHp);
    //89-33=56 89是满圈百分比，33是空圈百分比
    float nowpercent= m_pFighter->petHp*100.f / m_pFighter->petHpMax ;
    changeBooldAndSpPercentage(nowpercent,0);
   
}
void MB_NodeShow::whenDead(){
    
    changeBooldAndSpPercentage(0,0);
    m_pFighter->petHp = 0;
    m_pNodeSP->setVisible(false);
    mAnimationMgr->setAnimationCompletedCallback(NULL,NULL);
    
    if(m_pFighter->petPos<0)
    {
//        m_pCardVisible->setVisible(false);
    }else
    {
        runAction(CCSequence::create(CCDelayTime::create(.3f),CCCallFunc::create(this, callfunc_selector(MB_NodeShow::playDead)) ,NULL));
//            m_pDeadSpr->setVisible(true);
    }
}
void MB_NodeShow::playDead()
{
    m_pDeadSpr->setVisible(true);
}
CCNode * MB_NodeShow::getDamageNode(){

    return m_pDamage;
}
void  MB_NodeShow::setDetailShow(bool isshow){

    m_bSetIsDetail = isshow;
}
bool MB_NodeShow::isDetailShow(){

    return m_bSetIsDetail;
}
void MB_NodeShow::changeSp(int sp){
    
//    if (sp > 0 && m_pFighter->petSp < 100) 怒气上限可变
//    {
//        m_pFighter->petSp += sp;
////        m_pFighter->petSp = m_pFighter->petSp > 100 ? 100 :m_pFighter->petSp;
//    }
    
    
//    if( m_pFighter->petSp > 100)
//    {
//    
//        m_pFighter->petSp = 100;
//        
//    }
//    else if( m_pFighter->petHp < 100)
//    {
//        m_pFighter->petSp = 0;
//    }
    m_pFighter->petSp  = m_pFighter->petSp + sp;
    
//    ccColor3B color;
//    MB_BattleConfigData::getInstance()->getColorBySpiritValue(&color,m_pFighter->petSp);
    int progress = m_pFighter->petSp;
    if (progress == 0 && m_pFighter->petSp != 0)
    {
        progress = 56;
    }
    m_pSp->setVisible(false);
//    sprite->setColor(color);
    
    //减100怒气只能这样刷新 否则不会刷新颜色
    if (sp < 0)
    {
        changeBooldAndSpPercentage(progress+1, 1);
        changeBooldAndSpPercentage(progress-1, 1);
    }
    changeBooldAndSpPercentage(progress, 1);
}
void MB_NodeShow::setBoss(bool isBoss){

    m_bBoss = isBoss;
    if(isBoss){
    
        this->setScale(1.2f);
   
    }else {
    
        this->setScale(1);
    }
}
bool MB_NodeShow::getBoss(){
    
    return m_bBoss;
}
void  MB_NodeShow::onResetFiter(p_fighter *fight){

    m_pFighter->petId = fight->petId;
    m_pFighter->petTypeID = fight->petTypeID;
    m_pFighter->petPos = fight->petPos;
    m_pFighter->petHp = fight->petHp;
    m_pFighter->petHpMax = fight->petHpMax;
    m_pFighter->petSp = fight->petSp;
    m_pFighter->petQuality = fight->petQuality;
    m_pFighter->petLevel = fight->petLevel;
    m_pFighter->next = NULL;
}

void MB_NodeShow::setShowCard()
{
    m_pCardVisible->setVisible(true);
    m_pNodeSP->setVisible(true);
    mAnimationMgr->setAnimationCompletedCallback(this, callfunc_selector(MB_NodeShow::AnimationCompletedCallback));
    AnimationCompletedCallback();
}
void MB_NodeShow::setFileName(const char * name ){

    m_strFileName = name;
}
const char * MB_NodeShow::getFilaeName(){

    return m_strFileName.c_str();
}



void MB_NodeShow::addCapacity(CCNode* node1)
{
    if (m_pNodeCapacity1==NULL) {
        return;
    }
    m_pNodeCapacity1->removeAllChildren();
    m_pNodeCapacity1->addChild(node1);
}
void MB_NodeShow::removeCapacity()
{
    if (m_pNodeCapacity1==NULL) {
        return;
    }
    m_pNodeCapacity1->removeAllChildren();
}
