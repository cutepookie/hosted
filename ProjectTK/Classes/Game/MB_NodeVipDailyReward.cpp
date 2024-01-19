//
//  MB_NodeVipDailyReward.cpp
//  ProjectMB
//
//  Create by wenyong on 23/12/2014.
//
//
#include "MB_NodeVipDailyReward.h"
#include "MB_GiftsProtocol.h"
#include "MB_NodeItemBook.h"
#include "MB_IngotsShopInterface.h"
#include "MB_RoleData.h"
#include "MB_LayerVipInfo.h"
MB_NodeVipDailyReward::MB_NodeVipDailyReward()
{
    isReceiveEnable = false;
    m_pVipInfoBg= NULL;
    m_pVipInfoBg2 = NULL;
    m_pVipInfo1= NULL;
    m_pVipInfo2= NULL;
    m_pVipLevelSpr = NULL;
    m_pNodeReward	 = NULL;
    m_pMenuReceive	 = NULL;
}
MB_NodeVipDailyReward::~MB_NodeVipDailyReward()
{
    CC_SAFE_RELEASE_NULL(m_pVipInfo2);
    CC_SAFE_RELEASE_NULL(m_pVipInfo1);
    CC_SAFE_RELEASE_NULL(m_pVipInfoBg);
    CC_SAFE_RELEASE_NULL(m_pVipInfoBg2);
    CC_SAFE_RELEASE_NULL(m_pVipLevelSpr);
    CC_SAFE_RELEASE_NULL(m_pNodeReward);
    CC_SAFE_RELEASE_NULL(m_pMenuReceive);
}
bool MB_NodeVipDailyReward::init()
{
    CCNode* pNode = loadResource("res/vip_node_get.ccbi");
    if(pNode)
	{
		addChild(pNode);
        onInitialized();
		return true;
	}
	return false;
}

void MB_NodeVipDailyReward::onInitialized()
{
    m_pVipLevelSpr->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("icon_vip_%d.png",MB_RoleData::getInstance()->getVipLevel())->getCString()));
    
    char strVipInfo[128] = { 0 };
    if (MB_RoleData::getInstance()->getVipLevel() >= MAX_VIP_LEVEL)
    {
        m_pVipInfo1->setVisible(false);
        m_pVipInfo2->setVisible(false);
        m_pVipInfoBg->setVisible(false);
        m_pVipInfoBg2->setVisible(false);
    }
    else
    {
        char strVipInfo[30] = { 0 };
        int vipLevel = MB_RoleData::getInstance()->getVipLevel();
        sprintf(strVipInfo, "%d元", MB_RoleData::getInstance()->getVipLevelUpPay());
        m_pVipInfo1->setString(strVipInfo);
        sprintf(strVipInfo, "VIP%d", vipLevel + 1);
        m_pVipInfo2->setString(strVipInfo);
    }
}

void MB_NodeVipDailyReward::setReceiveEnable(bool bEnable)
{
    isReceiveEnable = bEnable;
    m_pMenuReceive->setEnabled(isReceiveEnable);
}

void MB_NodeVipDailyReward::onResetWnd()
{
    
}
bool MB_NodeVipDailyReward::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pVipInfoBg",CCNode*,m_pVipInfoBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pVipInfoBg2",CCNode*,m_pVipInfoBg2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pVipInfo1",CCLabelBMFont*,m_pVipInfo1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pVipInfo2",CCLabelBMFont*,m_pVipInfo2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pVipLevelSpr",CCSprite*,m_pVipLevelSpr);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeReward",CCNode*,m_pNodeReward);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMenuReceive",CCMenuItemImage*,m_pMenuReceive);
    return false;
}
SEL_MenuHandler MB_NodeVipDailyReward::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onClickCollect",MB_NodeVipDailyReward::onClickCollect);
        CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onVipClicked", MB_NodeVipDailyReward::onVipClicked);  //查看VIP
	return NULL;
}
SEL_CCControlHandler MB_NodeVipDailyReward::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

void MB_NodeVipDailyReward::onVipClicked(CCObject* pSender)
{
    //查看VIP
    MB_LayerVipInfo* layer = MB_LayerVipInfo::create(this);
    CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
}
void MB_NodeVipDailyReward::onClickCollect(CCObject* pSender)
{
    if (isReceiveEnable) {
        MB_Message::sharedMB_Message()->showMessage("",15);
        MB_IngotsShopInterface::send_daily_vip_draw();
    }
}

void MB_NodeVipDailyReward::setMailReward(MB_MailReward* pReward)
{
    if (pReward)
    {
        CCArray* pArray = pReward->converIDNUM2RewardTempleteValue();
        if (pArray)
        {
            MB_LayerRewardContainer* pContainer = MB_LayerRewardContainer::create(pArray);
            if (pContainer)
            {
                m_pNodeReward->removeAllChildren();
                m_pNodeReward->addChild(pContainer);
            }
        }
    }
}
