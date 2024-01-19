//
//  MB_LayerFishingReward.cpp
//  ProjectMB
//
//  Created by yuanwugang on 14-10-8.
//
//

#include "MB_LayerFishingReward.h"
#include "MB_ChapterData.h"
#include "MB_NodeRewardUnit.h"
#include "MB_NodeItemBook.h"
#include "MB_FishingRewardData.h"
MB_LayerFishingReward::MB_LayerFishingReward()
{
    m_pNodeItem = NULL;
    m_pTTFExp = NULL;
    m_pTTFCoin = NULL;
    m_pAnimationMgr = NULL;
    m_pNodeCrit1 = NULL;
    m_pNodeCrit2 = NULL;
    m_pNodeCrit3 = NULL;
    m_pNodeGotItem = NULL;
    m_bShowRoleInfoPanel = true;
}
MB_LayerFishingReward::~MB_LayerFishingReward()
{
    CC_SAFE_RELEASE_NULL(m_pNodeItem);
    CC_SAFE_RELEASE_NULL(m_pTTFExp);
    CC_SAFE_RELEASE_NULL(m_pTTFCoin);
    CC_SAFE_RELEASE_NULL(m_pAnimationMgr);
    CC_SAFE_RELEASE_NULL(m_pNodeCrit1);
    CC_SAFE_RELEASE_NULL(m_pNodeCrit2);
    CC_SAFE_RELEASE_NULL(m_pNodeCrit3);
    CC_SAFE_RELEASE_NULL(m_pNodeGotItem);
}


MB_LayerFishingReward* MB_LayerFishingReward::create(MB_FishingRewardData* data)
{
    MB_LayerFishingReward* ptr = new MB_LayerFishingReward();
    if (ptr && ptr->init(data))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}
bool MB_LayerFishingReward::init(MB_FishingRewardData* data)
{
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode * node = pCCBReader->readNodeGraphFromFile("res/fishing_node_reward.ccbi", this);
    if (node == NULL)
    {
        return false;
    }
    
    this->addChild(node);
    m_pAnimationMgr = pCCBReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pAnimationMgr);
    pCCBReader->release();

    
    char str[100] = "";
    sprintf(str,"获得金币: %d",data->getCoin());
    m_pTTFCoin->setString(str);
    
    sprintf(str,"获得经验: %d",data->getRoleExp());
    m_pTTFExp->setString(str);
    
    m_pNodeCrit1->setVisible(false);
    m_pNodeCrit2->setVisible(false);
    m_pNodeCrit3->setVisible(false);
    if(data->getCrit() == 2)
    {
        m_pNodeCrit1->setVisible(true);
    }
    else if(data->getCrit() == 4)
    {
        m_pNodeCrit2->setVisible(true);
    }
    else if(data->getCrit() == 8)
    {
        m_pNodeCrit3->setVisible(true);
    }
    
    if(data->getRewardArray() != NULL && data->getRewardArray()->count() > 0)
    {
        MB_LayerRewardContainerMaoXian* rewardNode = MB_LayerRewardContainerMaoXian::create(data->getRewardArray());
        m_pNodeItem->addChild(rewardNode);
        m_pNodeGotItem->setVisible(true);
    }    
    
    onResetWnd();
    m_pAnimationMgr->setAnimationCompletedCallback(this,callfunc_selector(MB_LayerFishingReward::onAnimationOver));
    m_pAnimationMgr->runAnimationsForSequenceNamed("Default Timeline");
    return true;
}

void MB_LayerFishingReward::onAnimationOver()
{
    m_pAnimationMgr->setAnimationCompletedCallback(NULL,NULL);
    popWindow();
}
cocos2d::SEL_MenuHandler MB_LayerFishingReward::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_LayerFishingReward::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName)
{
    return NULL;
}
bool MB_LayerFishingReward::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeItem",CCNode*,m_pNodeItem);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFExp",CCLabelTTF*,m_pTTFExp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFCoin",CCLabelTTF*,m_pTTFCoin);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeCrit1",CCNode*,m_pNodeCrit1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeCrit2",CCNode*,m_pNodeCrit2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeCrit3",CCNode*,m_pNodeCrit3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeGotItem", CCNode*, m_pNodeGotItem);
    return false;
}

void MB_LayerFishingReward::onResetWnd()
{
    
}

void MB_LayerFishingReward::onExit()
{
    MB_ResWindow::onExit();
    if (m_pAnimationMgr)
    {
        m_pAnimationMgr->setAnimationCompletedCallback(NULL,NULL);
        
    }
}
