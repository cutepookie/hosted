
#include "MB_LayerResultRepLay.h"
#include "MB_NodeReplayPetUnite.h"
#include "MB_NodeReplayPetUnite.h"
#include "MB_NodeShow.h"
#include "MB_SceneGame.h"
MB_LayerResultRepLay::MB_LayerResultRepLay(){

    isClickBack = false;
    m_pEnenmy_Role_Name = NULL;
    m_pOur_Role_Name = NULL;
    m_pEnemy_pos = NULL;
    m_pOur_pos = NULL;
    m_pNodeSuccess = NULL;
    m_pNodeFailed = NULL;
}
MB_LayerResultRepLay::~MB_LayerResultRepLay(){

   CC_SAFE_RELEASE(m_pEnenmy_Role_Name);
   CC_SAFE_RELEASE(m_pOur_Role_Name);
   CC_SAFE_RELEASE(m_pEnemy_pos);
   CC_SAFE_RELEASE(m_pOur_pos);
   CC_SAFE_RELEASE(m_pNodeSuccess);
   CC_SAFE_RELEASE(m_pNodeFailed);
}
MB_LayerResultRepLay* MB_LayerResultRepLay::create(MB_SceneGame *gameScene){

    MB_LayerResultRepLay *ptr = new MB_LayerResultRepLay();
    if(ptr && ptr->init(gameScene)){
    
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
bool MB_LayerResultRepLay::init(MB_SceneGame *gameScene){

    MB_ResWindow::init();
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    CCNode * node = ccbReader->readNodeGraphFromFile("res/formation_layer_compare3.ccbi",this);
    this->addChild(node);
    CC_SAFE_DELETE(ccbReader);
    bool isSuccess = false;
    for (int i = 0 ; i  < 6 ; i++) {
        MB_NodeShow *m_pData = gameScene->getActorByindexAndType(i, 1);
        if(m_pData){
            
            if(m_pData->getFighter()->petHp > 0){
                
                isSuccess = true;
            }
            MB_NodeReplayPetUnite * node = MB_NodeReplayPetUnite::create(m_pData->getFighter()->petTypeID, m_pData->getFighter()->petQuality,m_pData->getFighter()->petLevel, m_pData->getFighter()->petHp <= 0);
            node->setPet(m_pData->getFighter()->petTypeID,m_pData->getFighter()->petQuality);
            m_pOur_pos->addChild(node);
            node->setPosition(ccp(66+node->getContentSize().width*i,40));
        }
    }
    for (int i = 0; i < 6; i++) {
        
        MB_NodeShow *m_pData = gameScene->getActorByindexAndType(i, 0);
        if(m_pData){
            MB_NodeReplayPetUnite * node = MB_NodeReplayPetUnite::create(m_pData->getFighter()->petTypeID, m_pData->getFighter()->petQuality,m_pData->getFighter()->petLevel, m_pData->getFighter()->petHp <= 0);
            node->setPet(m_pData->getFighter()->petTypeID,m_pData->getFighter()->petQuality);
            m_pEnemy_pos->addChild(node);
            node->setPosition(ccp(66+node->getContentSize().width*i,40));
        }
    }

    m_pNodeSuccess->setVisible(isSuccess);
    m_pNodeFailed->setVisible(isSuccess == false);
    m_pOur_Role_Name->setString(gameScene->getDefenceName());
    m_pEnenmy_Role_Name->setString(gameScene->getAttackName());
    
    return true;
}
bool MB_LayerResultRepLay::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "enemy_role_name",CCLabelTTF*,m_pEnenmy_Role_Name);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "my_role_name",CCLabelTTF *,m_pOur_Role_Name);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "enemy_pos",CCNode *,m_pEnemy_pos);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "my_pos",CCNode *, m_pOur_pos);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeFailed",CCNode *,m_pNodeFailed);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeSuccess",CCNode *, m_pNodeSuccess);
    return  false;
}
SEL_MenuHandler MB_LayerResultRepLay::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onBackClicked", MB_LayerResultRepLay::onBackClicked);
    return NULL;
}
SEL_CCControlHandler MB_LayerResultRepLay::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){

    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onReplayClicked", MB_LayerResultRepLay::onReplayClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBackClicked", MB_LayerResultRepLay::onBackClicked);    
    return NULL;
}
void MB_LayerResultRepLay::onReplayClicked (CCObject* sender){

    ((MB_SceneGame *)this->getParent())->rePlay();
    this->removeFromParent();
}
void MB_LayerResultRepLay::onBackClicked (CCObject* sender){
    
    if(isClickBack){
    
        return;
    }
    isClickBack = true;
    PlayBackGround(kmBackGround_Normal);
    CCDirector::sharedDirector()->popScene();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}
