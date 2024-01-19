//
//  MB_NodeFestivalRank.cpp
//  ProjectMB
//
//  Create by wenyong on 13/1/2015.
//
//
#include "MB_NodeFestivalRank.h"
#include "MB_FestivalProtocol.h"
#include "../Common/GameLib/GameHelper/CCGameHelper.h"
#include "MB_GiftsProtocol.h"
#include "MB_NodeItemBook.h"
#include "MB_Message.h"

MB_NodeFestivalRank::MB_NodeFestivalRank()
{
    m_pNodeSize	 = NULL;
    m_pNodeRankNum	 = NULL;
    m_pSpriteFrame	 = NULL;
    m_pRoleHeader	 = NULL;
    m_pNodeLv	 = NULL;
    m_pLabelRoleName	 = NULL;
    m_pLabelJoinTimes	 = NULL;
    m_pData = NULL;
    m_pNodeReward1 = NULL;
    m_pNodeReward2 = NULL;
    m_pNodeReward3 = NULL;
    m_pNodeMenu = NULL;
}
MB_NodeFestivalRank::~MB_NodeFestivalRank()
{
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(m_pNodeRankNum);
    CC_SAFE_RELEASE_NULL(m_pSpriteFrame);
    CC_SAFE_RELEASE_NULL(m_pRoleHeader);
    CC_SAFE_RELEASE_NULL(m_pNodeLv);
    CC_SAFE_RELEASE_NULL(m_pLabelRoleName);
    CC_SAFE_RELEASE_NULL(m_pLabelJoinTimes);
    CC_SAFE_RELEASE_NULL(m_pNodeReward1);
    CC_SAFE_RELEASE_NULL(m_pNodeReward2);
    CC_SAFE_RELEASE_NULL(m_pNodeReward3);
    CC_SAFE_RELEASE_NULL(m_pNodeMenu);
}
bool MB_NodeFestivalRank::init()
{
    CCNode* pNode = loadResource("res/festival_node_rank.ccbi");
    if(pNode)
	{
		addChild(pNode);
        if (m_pNodeMenu)
        {
            m_pNodeMenu->setSwallowsTouches(false);
        }
		return true;
	}
	return false;
}
void MB_NodeFestivalRank::onResetWnd()
{

}
bool MB_NodeFestivalRank::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize",CCNode*,m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeRankNum",CCLabelBMFont*,m_pNodeRankNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpriteFrame",CCSprite*,m_pSpriteFrame);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pRoleHeader",CCSprite*,m_pRoleHeader);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeLv",CCLabelBMFont*,m_pNodeLv);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelRoleName",CCLabelTTF*,m_pLabelRoleName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelJoinTimes",CCLabelTTF*,m_pLabelJoinTimes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeReward1",CCNode*,m_pNodeReward1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeReward2",CCNode*,m_pNodeReward2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeReward3",CCNode*,m_pNodeReward3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeMenu", CCMenu*, m_pNodeMenu);
	return false;
}
SEL_MenuHandler MB_NodeFestivalRank::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onIconClicked",MB_NodeFestivalRank::onIconClicked);
	return NULL;
}
SEL_CCControlHandler MB_NodeFestivalRank::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
void MB_NodeFestivalRank::onIconClicked(CCObject* pSender)
{
    if (m_pData)
    {
        if(m_pData->getRoleID() == MB_RoleData::getInstance()->getUID())
            return;
        MB_Message::sharedMB_Message()->showMessage("",15);
        MB_TeamData::getInstance()->sendpet_view_other(m_pData->getRoleID(),0);
    }
    else
    {
        MB_Message::sharedMB_Message()->showMessage("尚未有玩家进入该排名");
    }
}

const CCSize& MB_NodeFestivalRank::getNodeSize()
{
    static CCSize sz(-1,0);
    if (sz.width<0)
    {
        MB_NodeFestivalRank* p = MB_NodeFestivalRank::create();
        if (p)
        {
            sz = p->m_pNodeSize->getContentSize();
        }
    }
    return sz;
}

void MB_NodeFestivalRank::setData(MB_FestivalRankData* pData)
{
    if (pData)
    {
        char buf[64] = {};
        sprintf(buf, "%d",pData->getLevel());
        m_pNodeLv->setString(buf);
        
        NSGameHelper::setRoleIcon(m_pRoleHeader, pData->getIsMale(), pData->getHead(), pData->getTitle());

        sprintf(buf,"%d",pData->getRank());
        m_pNodeRankNum->setString(buf);
        
        m_pLabelRoleName->setString(pData->getRoleName().c_str());
        
        sprintf(buf, "%d次",pData->getTotalCount());
        m_pLabelJoinTimes->setString(buf);
        
        m_pData = pData;
    }
}

void MB_NodeFestivalRank::setRankDataOnly(MB_RankReward* pRankReward)
{
    m_pNodeLv->setVisible(false);

    char buf[64] = {};
    m_pNodeRankNum->setTag(2);
    sprintf(buf,"%d",pRankReward->getRank());
    m_pNodeRankNum->setString(buf);

    m_pLabelRoleName->setString("????");
    m_pLabelJoinTimes->setString("????");

    setRewardData(pRankReward->getReward());

    m_pData = NULL;
}

void MB_NodeFestivalRank::replaceReward(CCNode* pRoot,CCNode* pTarget)
{
    if (pRoot && pTarget)
    {
        pTarget->setScale(0.6);
        pRoot->removeAllChildren();
        pRoot->addChild(pTarget);
    }
}
void MB_NodeFestivalRank::setRewardData(MB_MailReward* pRewardData)
{
    if (pRewardData)
    {
        CCArray* pArray = pRewardData->converIDNUM2RewardTempleteValue();
        RewardTempleteValue* pValue = NULL;
        
        MB_NodeRewardItem* pItem = NULL;
        int index = 0;
        CCARRAY_FOREACH_4TYPE(pArray, RewardTempleteValue*, pValue)
        {
            if (pValue->getType() == kRewardValueTypePet)
            {
                pItem = MB_NodeRewardPet::create(pValue->getValueID(),pValue->getNumber(),true);
                pItem->enableClick(true);
            }
            else
            {
                pItem = MB_NodeRewardItem::create(pValue->getValueID(),pValue->getNumber(),false);
                pItem->enableClick(true);
            }
            if (index ==0)
            {
                replaceReward(m_pNodeReward1, pItem);
            }
            else if (index ==1)
            {
                replaceReward(m_pNodeReward2, pItem);
            }
            else if (index ==2)
            {
                replaceReward(m_pNodeReward3, pItem);
            }
            ++index;
        }
    }
}
