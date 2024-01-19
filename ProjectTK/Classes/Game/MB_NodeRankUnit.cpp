//
//  MB_NodeRankUnit.cpp
//  ProjectMB
//
//  Create by wenyong on 24/12/2014.
//
//
#include "MB_NodeRankUnit.h"
#include "MB_FunctionRankingProtocol.h"
#include "MB_FunctionModule.h"
#include "MB_ServerRewardData.h"
#include "MB_AbsolvedConfigure.h"
#include "MB_LayerRankMain.h"
MB_NodeRankUnit::MB_NodeRankUnit()
{
    m_pBg1 = NULL;
    m_pBg2 = NULL;
    m_pStar     = NULL;
    m_pPaiMingSpr     = NULL;
    m_pNodeSize	 = NULL;
    m_pNodeRankNum	 = NULL;
    m_pSpriteFrame	 = NULL;
    m_pRoleHeader	 = NULL;
    m_pDesc0	 = NULL;
    m_pDesc1	 = NULL;
    m_pDesc2	 = NULL;
    m_pDesc3     = NULL;
    m_pNodeLv	 = NULL;
    m_pRankData = NULL;
}
MB_NodeRankUnit::~MB_NodeRankUnit()
{
    CC_SAFE_RELEASE_NULL(m_pBg1);
    CC_SAFE_RELEASE_NULL(m_pBg2);
    CC_SAFE_RELEASE_NULL(m_pStar);
    CC_SAFE_RELEASE_NULL(m_pPaiMingSpr);
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(m_pNodeRankNum);
    CC_SAFE_RELEASE_NULL(m_pSpriteFrame);
    CC_SAFE_RELEASE_NULL(m_pRoleHeader);
    CC_SAFE_RELEASE_NULL(m_pDesc0);
    CC_SAFE_RELEASE_NULL(m_pDesc1);
    CC_SAFE_RELEASE_NULL(m_pDesc2);
    CC_SAFE_RELEASE_NULL(m_pDesc3);
    CC_SAFE_RELEASE_NULL(m_pNodeLv);
}
bool MB_NodeRankUnit::init()
{
    CCNode* pNode = loadResource("res/rank_node_pvp.ccbi");
    if(pNode)
    {
        addChild(pNode);
        return true;
    }
    return false;
}


bool MB_NodeRankArena::init()
{
    CCNode* pNode = loadResource("res/rank_node_pvp.ccbi");
    if(pNode)
    {
        addChild(pNode);
        return true;
    }
    return false;
}

bool MB_NodeRankPower::init()
{
    CCNode* pNode = loadResource("res/rank_node_power.ccbi");
    if(pNode)
    {
        addChild(pNode);
        return true;
    }
    return false;
}

bool MB_NodeRankAbsolved::init()
{
    CCNode* pNode = loadResource("res/rank_node_absolved.ccbi");
    if(pNode)
    {
        addChild(pNode);
        return true;
    }
    return false;
}

bool MB_NodeRankLevel::init()
{
    CCNode* pNode = loadResource("res/rank_node_lv.ccbi");
    if(pNode)
    {
        addChild(pNode);
        return true;
    }
    return false;
}


void MB_NodeRankUnit::onResetWnd()
{

}
bool MB_NodeRankUnit::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBg1",CCNode*,m_pBg1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBg2",CCNode*,m_pBg2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize",CCNode*,m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeRankNum",CCLabelBMFont*,m_pNodeRankNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpriteFrame",CCSprite*,m_pSpriteFrame);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pRoleHeader",CCSprite*,m_pRoleHeader);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pDesc0",CCLabelTTF*,m_pDesc0);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pDesc1",CCLabelBMFont*,m_pDesc1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pDesc2",CCLabelTTF*,m_pDesc2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pDesc3",CCLabelTTF*,m_pDesc3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeLv",CCLabelBMFont*,m_pNodeLv);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pStar",CCNode*,m_pStar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pPaiMingSpr",CCSprite*,m_pPaiMingSpr);
	return false;
}
SEL_MenuHandler MB_NodeRankUnit::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onIconClicked",MB_NodeRankUnit::onIconClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onInfoClicked",MB_NodeRankUnit::onInfoClicked);
	return NULL;
}
SEL_CCControlHandler MB_NodeRankUnit::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

void MB_NodeRankUnit::onIconClicked(CCObject* pSender)
{
    MB_TARGET_PARENT(MB_LayerRankMain, ptr)
    {
        if(ptr)
        {
            ptr->sendpet_view_other(m_pRankData->getRoleID());
        }
    }
}

void MB_NodeRankUnit::onInfoClicked(CCObject* pSender)
{
    uint32_t uid = m_pRankData->getRoleID();
    if(uid == MB_RoleData::getInstance()->getUID())
    {
        MB_Message::sharedMB_Message()->showMessage("不能添加自己");
        return;
    }
    MB_Message::sharedMB_Message()->showMessage("",15);
    MB_FriendMgr::getInstance()->sendfriend_add(1,&uid);
}

void MB_NodeRankUnit::setBase(MB_RankData* pData)
{
    m_pRankData = pData;
    
    char buf[64] = {};
    sprintf(buf, "Lv.%d",pData->getLevel());
    m_pNodeLv->setString(buf);
    
    NSGameHelper::setRoleIcon(m_pRoleHeader, pData->getIsMale(), pData->getHead(), pData->getTitle());
    sprintf(buf,"%d",pData->getRank());
    m_pNodeRankNum->setString(buf);
    
    if (pData->getRank()==1) {
        m_pBg1->setVisible(true);
        m_pBg2->setVisible(true);
        m_pStar->setVisible(true);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("jingjichang.plist");
        m_pPaiMingSpr->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("txt_rank.png"));
        m_pPaiMingSpr->setPosition(ccp(-265.5f,33.2f));
    }else
    {
        m_pBg1->setVisible(false);
        m_pBg2->setVisible(false);
        m_pStar->setVisible(false);
    }
}
void MB_NodeRankUnit::setData(MB_RankData* pData)
{
    if (pData)
    {
        setBase(pData);
        
        setDesc(pData);
    }
}

void MB_NodeRankUnit::setDesc(MB_RankData* pData)
{
    
}

const CCSize& MB_NodeRankUnit::getNodeSize()
{
    static CCSize sz = CCSizeMake(-1, -1);
    if (sz.width < 0)
    {
        MB_NodeRankUnit* pNode = MB_NodeRankUnit::create();
        if (pNode)
        {
            sz = pNode->m_pNodeSize->getContentSize();
        }
    }
    return sz;
}


void MB_NodeRankArena::setDesc(MB_RankData* pData)
{
    char buf[128] = {};
    sprintf(buf, "%lld",pData->getPower());
    m_pDesc0->setString(pData->getName().c_str());
    m_pDesc1->setString(buf);
    m_pDesc2->setString("");
}
void MB_NodeRankPower::setDesc(MB_RankData* pData)
{
    char buf[128] = {};
    sprintf(buf, "%lld",pData->getPower());
    m_pDesc0->setString(pData->getName().c_str());
    m_pDesc1->setString(buf);
    m_pDesc2->setString("");
}
void MB_NodeRankAbsolved::setDesc(MB_RankData* pData)
{
    std::string chapter = "";
    MB_ChapterData* pd = MB_AbsolvedConfigure::getInstance()->getChapterDataById(pData->getChapter(), 1);
    if (pd)
    {
        chapter = pd->getName();
    }
    m_pDesc0->setString(pData->getName().c_str());
    CC_SAFE_RELEASE_NULL(m_pDesc1);
    m_pDesc2->setString(pData->getDungeonName().c_str());
    m_pDesc3->setString(chapter.c_str());
}
void MB_NodeRankLevel::setDesc(MB_RankData* pData)
{
    char buf[128] = {};
    sprintf(buf, "%lld",pData->getPower());
    m_pDesc0->setString(pData->getName().c_str());
    m_pDesc1->setString(buf);
    m_pDesc2->setString("");
}




