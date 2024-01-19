//
//  MB_LayerBudokanSweep.cpp
//  ProjectMB
//
//  Created by yuanwugang on 15-2-26.
//
//

#include "MB_LayerBudokanSweep.h"


MB_LayerBudokanSweep::MB_LayerBudokanSweep()
{
    m_pTTFReward = NULL;
    m_pSpriteReward = NULL;
}

MB_LayerBudokanSweep::~MB_LayerBudokanSweep()
{
    CC_SAFE_RELEASE_NULL(m_pTTFReward);
    CC_SAFE_RELEASE_NULL(m_pSpriteReward);
}

MB_LayerBudokanSweep * MB_LayerBudokanSweep::create(p_reward *pReward,uint16_t length){
    
    MB_LayerBudokanSweep *ptr = new MB_LayerBudokanSweep();
    if(ptr && ptr->init(pReward,length)){
        
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
bool MB_LayerBudokanSweep::init(p_reward *pReward,uint16_t length)
{
    
    if( !MB_ResWindow::init())
    {
        return false;
    }
    
    CCNode* pNode = loadResource("res/Sweep_layer.ccbi");
    if(pNode)
    {
        addChild(NSGameHelper::createDisableTouchLayer());
        addChild(pNode);
        m_pReward = pReward;
        m_nRewardLength = length;
        
        m_pOver->setVisible(false);
        //        m_pEnergyLow->setVisible(false);
        
        char buff[100] = {0};
        sprintf(buff, "0/%d",m_nRewardLength);
        
        m_pNameLabel->setString(strCurDungeonName.c_str());
        m_pCoinLabel->setString("0");
        m_pExpLabel->setString("0");
        
        m_pScrollView = CCScrollView::create(m_pNodeContainer->getContentSize());
        m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
        m_pNodeContainer->addChild(m_pScrollView);
        
        this->schedule(schedule_selector(MB_LayerBudokanSweep::showOver), 1.0f, m_nRewardLength, 1.0f);
        
        
        m_pTTFReward->setString("获得补天石");
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("global.plist");
        NSGameHelper::setSpriteFrameWithFrameCache(m_pSpriteReward,GET_CONFIG_VALUE("currency.xml",3,"Icon").c_str());
        m_pSpriteReward->setScale(0.8);
        return true;
    }
    return false;

}
bool MB_LayerBudokanSweep::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    if(MB_LayerSweep::onAssignCCBMemberVariable(pTarget,pMemberVariableName,pNode))
    {
        return true;
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFReward",CCLabelTTF*,m_pTTFReward);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpriteReward",CCSprite*,m_pSpriteReward);
    return false;
}


void MB_LayerBudokanSweep::showOver(float)
{
    if(m_n < m_nRewardLength)
    {
        m_nCoin += m_pReward[m_n].coin;
        m_nExp += m_pReward[m_n].reputation;
        
        char buff[100] = {0};
        sprintf(buff, "%d/%d",m_n+1,m_nRewardLength);
        m_pProcessLabel->setString(buff);
        
        sprintf(buff, "%d",m_nCoin);
        m_pCoinLabel->setString(buff);
        
        sprintf(buff, "%d",m_nExp);
        m_pExpLabel->setString(buff);
        
        
        //奖励
        p_item_view *item = m_pReward[m_n].item;
        while ( item!=NULL)
        {
            if(item->itemNum>0)
            {
                RewardTempleteValue* pValue = new RewardTempleteValue;
                
                pValue->setType(1);
                pValue->setValueID(item->itemTypeId);
                pValue->setNumber(item->itemNum);
                
                addReward(pValue);
                CC_SAFE_RELEASE_NULL(pValue);
            }
            else
            {
                RewardTempleteValue* pValue = new RewardTempleteValue;
                
                pValue->setType(2);
                pValue->setValueID(item->itemTypeId);
                pValue->setNumber(item->itemNum);
                addReward(pValue);
                CC_SAFE_RELEASE_NULL(pValue);
            }
            item = item->next;
        }
        if(m_pRewards->count())
        {
            onResetWnd();
        }
    }
    
    if(m_n == m_nRewardLength - 1)
    {
    }
    ++m_n;
}
