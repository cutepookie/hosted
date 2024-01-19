//
//  MB_LayerResultBoss.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14-9-29.
//
//

#include "MB_LayerResultBoss.h"
#include "MB_NodeItemBook.h"
MB_LayerResultBoss::MB_LayerResultBoss()
{
    m_pExpLabel	 = NULL;
    m_pCoinLabel	 = NULL;
    m_pNodeReward	 = NULL;
    m_pAttack = NULL;
    m_bClickedBack = false;
    m_pSpr1= NULL;
    m_pSpr2= NULL;
}
MB_LayerResultBoss::~MB_LayerResultBoss()
{
    CC_SAFE_RELEASE_NULL(m_pExpLabel);
    CC_SAFE_RELEASE_NULL(m_pCoinLabel);
    CC_SAFE_RELEASE_NULL(m_pNodeReward);
    CC_SAFE_RELEASE_NULL(m_pAttack);
    CC_SAFE_RELEASE_NULL(m_pSpr1);
    CC_SAFE_RELEASE_NULL(m_pSpr2);
}

void MB_LayerResultBoss::onResetWnd()
{
    
}
bool MB_LayerResultBoss::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pExpLabel",CCLabelBMFont*,m_pExpLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pCoinLabel",CCLabelBMFont*,m_pCoinLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeReward",CCNode*,m_pNodeReward);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pAttack",CCLabelBMFont*,m_pAttack);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpr1",CCNode*,m_pSpr1);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpr2",CCNode*,m_pSpr2);
	return false;
}
SEL_MenuHandler MB_LayerResultBoss::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onBackClick",MB_LayerResultBoss::onBackClick);
	return NULL;
}
SEL_CCControlHandler MB_LayerResultBoss::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

void MB_LayerResultBoss::onBackClick(CCObject* pSender)
{
    if(m_bClickedBack)return;
    m_bClickedBack = true;
    PlayBackGround(kmBackGround_Normal);
    CCDirector::sharedDirector()->popScene();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void MB_LayerResultBoss::animationOver()
{
    if(m_pAnimationMgr)m_pAnimationMgr->setAnimationCompletedCallback(NULL, NULL);
    
    if(m_nIsSuccess == false)
    {
        if(m_nResultType == kFightResultTypeRocketTeam)
        {
            if(CCUserDefault::sharedUserDefault()->getBoolForKey("autohulao"))
            {
                onBackClick(NULL);
            }
        }
        else  if(m_nResultType == kFightResultTypeNanm)
        {
            if(CCUserDefault::sharedUserDefault()->getBoolForKey("autoworldboss"))
            {
//                scheduleOnce(schedule_selector(MB_LayerResultBoss::goOver),2);
            }
        }
    }
}

MB_LayerResultBoss  * MB_LayerResultBoss::create(int rewardCoin,int rewardreputation,char issuccess,int attack,int resulttype)
{
    MB_LayerResultBoss * ptr = new MB_LayerResultBoss();
    ptr->m_nResultType = resulttype;
    if(ptr && ptr->init(rewardCoin, rewardreputation,issuccess,attack))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}

bool MB_LayerResultBoss::init(int rewardCoin,int rewardreputation,char issuccess,int attack)
{
    MB_ResWindow::init();
    m_nIsSuccess = issuccess == 1;
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    CCNode * node = ccbReader->readNodeGraphFromFile(m_nIsSuccess?"res/pve_layer_bosswin.ccbi":"res/pve_layer_bossfail.ccbi",this);
    this->addChild(node);
    m_pAnimationMgr = ccbReader->getAnimationManager();
    m_pAnimationMgr->setAnimationCompletedCallback(this,callfunc_selector(MB_LayerResultBoss::animationOver));

    CC_SAFE_RETAIN(m_pAnimationMgr);
    
    
    
    ccbReader->release();
    
    char databuf[50];
    sprintf(databuf, "%d",rewardreputation);
    m_pExpLabel->setString(databuf);
    sprintf(databuf, "%d",rewardCoin);
    m_pCoinLabel->setString(databuf);
    sprintf(databuf, "%d",attack);
    m_pAttack->setString(databuf);
    
    m_pSpr1->setPositionX(384+((m_pCoinLabel->getContentSize().width-48)*.4f));
    m_pSpr2->setPositionX(404+((m_pExpLabel->getContentSize().width-93)*.4f));
    //没有动画 这里主动掉 加了动画后取消这里
    animationOver();

    return true;
}


void MB_LayerResultBoss::goOver()
{
    onBackClick(NULL);
}
