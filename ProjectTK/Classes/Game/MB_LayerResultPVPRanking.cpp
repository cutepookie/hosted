
#include "MB_LayerResultPVPRanking.h"
//#include "MB_WorldKingInterface.h"
#include "MB_RechargeSystem.h"
USING_NS_CC;
USING_NS_CC_EXT;

MB_LayerResultPVPRanking::MB_LayerResultPVPRanking()
{
    m_bIsPopScene = false;
    m_pTTFyl = NULL;
    m_pTTFRank = NULL;
    m_pTTFRankUp = NULL;

}

MB_LayerResultPVPRanking::~MB_LayerResultPVPRanking()
{
    CC_SAFE_RELEASE_NULL(m_pTTFyl);
    CC_SAFE_RELEASE_NULL(m_pTTFRank);
    CC_SAFE_RELEASE_NULL(m_pTTFRankUp);
}

CCScene* MB_LayerResultPVPRanking::scene(p_result_ranking* fightResult)
{
    CCScene *scene=CCScene::create();
    CCLayer *node = MB_LayerResultPVPRanking::create(fightResult);
    scene->addChild(node);
    return scene;
}

MB_LayerResultPVPRanking* MB_LayerResultPVPRanking::create(p_result_ranking* fightResult)
{
    MB_LayerResultPVPRanking* layer = new MB_LayerResultPVPRanking();
    if (layer != NULL && layer->init(fightResult)) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}

bool MB_LayerResultPVPRanking::init(p_result_ranking* fightResult)
{
	if ( !CCLayer::init() )
	{
		return false;
	}
    
    m_pResult = fightResult;

    this->addChild(NSGameHelper::createDisableTouchLayer());
    if (fightResult->_isSuccess) {
      
        CCNode* pNode = loadResource("res/pvp_layer_win.ccbi");
        if(pNode)
        {
            addChild(pNode);
            onResetWnd();
        }
    }
    else
    {
        CCNode* pNode = loadResource("res/pvp_layer_lose.ccbi");
        if(pNode)
        {
            addChild(pNode);
            onResetWnd();
        }
    }
	return true;
}

void MB_LayerResultPVPRanking::onResetWnd()
{
    char str[32] = "";
    sprintf(str, "%d",m_pResult->_addCoin);
    m_pTTFyl->setString(str);
    if (m_pResult->_isSuccess)
    {
        sprintf(str, "%d",m_pResult->_myRank);
    }
    else
    {
        sprintf(str, "%d",m_pResult->_myOldRank);
    }
    m_pTTFRank->setString(str);
    
    if (m_pResult->_isSuccess)
    {
        sprintf(str, "%d",m_pResult->_myOldRank - m_pResult->_myRank);
        m_pTTFRankUp->setString(str);
    }
   
 }
bool MB_LayerResultPVPRanking::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFyl", CCLabelBMFont*,m_pTTFyl);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFRank", CCLabelBMFont*,m_pTTFRank);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFRankUp", CCLabelBMFont*,m_pTTFRankUp);
    
    return true;
}

SEL_MenuHandler MB_LayerResultPVPRanking::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{

    return NULL;
}



SEL_CCControlHandler MB_LayerResultPVPRanking::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onFightClicked", MB_LayerResultPVPRanking::onFightClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onToyShopClicked", MB_LayerResultPVPRanking::onToyShopClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPowerUpClicked", MB_LayerResultPVPRanking::onPowerUpClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCompareClicked", MB_LayerResultPVPRanking::onCompareClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBackClicked", MB_LayerResultPVPRanking::onBackClicked);
    return NULL;
}
void MB_LayerResultPVPRanking::onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader)
{
    MB_LOG("onNodeLoaded succeed!");
}

void MB_LayerResultPVPRanking::onFightClicked(cocos2d::CCObject *pSender)
{
    uint32_t roleID = m_pResult->_dataPVPRank->getRoleID();
    uint16_t rank = m_pResult->_dataPVPRank->getRoleRank();
    
    
    if (!m_bIsPopScene) {
        MB_DataPVPMgr::getInstance()->setGoFight(true);
        MB_DataPVPMgr::getInstance()->setFightRoleID(roleID);
        MB_DataPVPMgr::getInstance()->setFightRank(rank);
        m_bIsPopScene = true;
        PlayBackGround(kmBackGround_Normal);
        CCDirector::sharedDirector()->popScene();
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
        
    }
}

void MB_LayerResultPVPRanking::onCompareClicked(cocos2d::CCObject *pSender)
{
    MB_TeamData::getInstance()->sendpet_view_other(m_pResult->_dataPVPRank->getRoleID(),0);
}

void MB_LayerResultPVPRanking::onBackClicked(cocos2d::CCObject *pSender)
{
    if (!m_bIsPopScene) {
        m_bIsPopScene = true;
        PlayBackGround(kmBackGround_Normal);
        CCDirector::sharedDirector()->popScene();
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }
}

void MB_LayerResultPVPRanking::onToyShopClicked(CCObject* pSender)
{
    onBackClicked(NULL);
    
    MB_RoleData::getInstance()->setWillShowLayer(kSceneTipLayerTypeShopToy);
}

void MB_LayerResultPVPRanking::onPowerUpClicked(CCObject* pSender)
{
    onBackClicked(NULL);
    MB_RoleData::getInstance()->setWillShowLayer(kSceneTipLayerTypePetUp);
}














MB_LayerResultCommonFight* MB_LayerResultCommonFight::create(SResultData* data)
{
    MB_LayerResultCommonFight* layer = new MB_LayerResultCommonFight();
    if (layer != NULL && layer->init(data))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}

MB_LayerResultCommonFight::MB_LayerResultCommonFight()
{
    m_pLabel[0] = NULL;
    m_pLabel[1] = NULL;
    m_pLabel[2] = NULL;
    m_bIsPopScene = false;
    m_Data = NULL;
    m_pSpr1 = NULL;
}

MB_LayerResultCommonFight::~MB_LayerResultCommonFight()
{
    CC_SAFE_RELEASE(m_pLabel[0]);
    CC_SAFE_RELEASE(m_pLabel[1]);
    CC_SAFE_RELEASE(m_pLabel[2]);
    CC_SAFE_RELEASE(m_Data);
    CC_SAFE_RELEASE(m_pSpr1);
}

bool MB_LayerResultCommonFight::init(SResultData* data)
{
    if ( !CCLayer::init() )return false;
    
    CC_SAFE_RELEASE(m_Data);
    m_Data = data;
    CC_SAFE_RETAIN(m_Data);
    this->addChild(NSGameHelper::createDisableTouchLayer());
    
    const char* szWin[] = {"res/pvp_rulefight_layer_win.ccbi","res/pvp_norulefight_layer_win.ccbi"};
    const char* szLose[] = {"res/pvp_rulefight_layer_lose.ccbi","res/pvp_norulefight_layer_lose.ccbi"};
    
    const char* win = NULL;
    const char* lose = NULL;
    
    if(data->type == kFightResultTypeNoRule)
    {
        win = szWin[1];
        lose= szLose[1];
    }
    else if(data->type == kFightResultTypeRuleFight)
    {
        win = szWin[0];
        lose= szLose[0];
    }

    CCNode* pNode = NULL;
    if (data->bWin)
        pNode = loadResource(win);
    else
        pNode = loadResource(lose);
    
    if(pNode)
    {
        addChild(pNode);
        onResetWnd();
    }
    
    return true;
}

//#define COIN_ID 30007//21100//钱币图标
//#define FRESH_ID 30003//21111 //黑石货币图表
//#define COLLECT_ID 21108 //感恩书图标
//#define SPEED_ID 21109    //神速令图标
//#define GOLD_ID 30008//21101 //元宝
//#define REPUTATION_ID 30006//21102//徽章
//#define ROLE_EXP_ID 30005 //角色经验
//#define GER_EXP_ID 21104
void MB_LayerResultCommonFight::onResetWnd()
{
    if(m_Data->type == kFightResultTypeNoRule)
    {
        RewardTempleteValue* pOjb = NULL;
        CCARRAY_FOREACH_4TYPE(m_Data->getRewards(), RewardTempleteValue*, pOjb)
        {
            if(pOjb->getValueID() == COIN_ID)
            {
                m_pLabel[0]->setString(CCString::createWithFormat("%d",pOjb->getNumber())->getCString());
            }
        }
        m_pLabel[1]->setString(CCString::createWithFormat("%d",m_Data->nNowRank)->getCString());
    }
    else if(m_Data->type == kFightResultTypeRuleFight)
    {
        RewardTempleteValue* pOjb = NULL;
        CCARRAY_FOREACH_4TYPE(m_Data->getRewards(), RewardTempleteValue*, pOjb)
        {
            if(pOjb->getValueID() == COIN_ID)
            {
                m_pLabel[0]->setString(CCString::createWithFormat("%d",pOjb->getNumber())->getCString());
            }
        }
        
        m_pLabel[1]->setString(CCString::createWithFormat("%d",m_Data->nNowRank)->getCString());
        if(m_Data->bWin)
        {
            m_pLabel[2]->setString(CCString::createWithFormat("%d",m_Data->nOldRank - m_Data->nNowRank)->getCString());
        }
        else
        {
            m_pLabel[1]->setString(CCString::createWithFormat("%d",0)->getCString());
        }
    }
    
    m_pSpr1->setPositionX(384+((m_pLabel[0]->getContentSize().width-48)*.4f));
}

bool MB_LayerResultCommonFight::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabel0", CCLabelBMFont*,m_pLabel[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabel1", CCLabelBMFont*,m_pLabel[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabel2", CCLabelBMFont*,m_pLabel[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpr1", CCNode*,m_pSpr1);
    return true;
}

SEL_MenuHandler MB_LayerResultCommonFight::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCompareClicked", MB_LayerResultCommonFight::onCompareClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBackClicked", MB_LayerResultCommonFight::onBackClicked);
    return NULL;
}

SEL_CCControlHandler MB_LayerResultCommonFight::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onFightClicked", MB_LayerResultCommonFight::onFightClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onToyShopClicked", MB_LayerResultCommonFight::onToyShopClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPowerUpClicked", MB_LayerResultCommonFight::onPowerUpClicked);
    return NULL;
}

#include "MB_RuleFightInterface.h"
#include "MB_FunctionNoRuleFight.h"
void MB_LayerResultCommonFight::onFightClicked(cocos2d::CCObject *pSender)
{
    if (!m_bIsPopScene) {
        m_bIsPopScene = true;
        PlayBackGround(kmBackGround_Normal);
        CCDirector::sharedDirector()->popScene();
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }
    
//    if(m_Data->type == kFightResultTypeRuleFight)
//    {
//        QUERY_FUNCTION_BEGIN(MB_RuleFightInterface, kFunctionRuleFight, pInterface);
//        pInterface->cs_hist_replay(pInterface->getFightReplayUID());
//        QUERY_FUNCTION_END;
//    }
}

void MB_LayerResultCommonFight::onCompareClicked(cocos2d::CCObject *pSender)
{
    if(m_Data->roleID == MB_RoleData::getInstance()->getUID())return;
    MB_Message::sharedMB_Message()->showMessage("",15);
    MB_TeamData::getInstance()->sendpet_view_other(m_Data->roleID,0);
}

void MB_LayerResultCommonFight::onBackClicked(cocos2d::CCObject *pSender)
{
    if (!m_bIsPopScene) {
        m_bIsPopScene = true;
        PlayBackGround(kmBackGround_Normal);
        CCDirector::sharedDirector()->popScene();
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }
}

void MB_LayerResultCommonFight::onToyShopClicked(CCObject* pSender)
{
    onBackClicked(NULL);
    MB_RoleData::getInstance()->setWillShowLayer(kSceneTipLayerTypeShopToy);
}

void MB_LayerResultCommonFight::onPowerUpClicked(CCObject* pSender)
{
    onBackClicked(NULL);
    MB_RoleData::getInstance()->setWillShowLayer(kSceneTipLayerTypePetUp);
}
