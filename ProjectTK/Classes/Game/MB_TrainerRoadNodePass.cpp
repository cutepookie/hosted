//
//  MB_TrainerRoadNodePass.cpp
//  ProjectMB
//
//  Create by wenyong on 15/1/2015.
//
//
#include "MB_TrainerRoadNodePass.h"
#include "MB_TrainerRoadConfigure.h"
#include "MB_LocalProto.h"
#include "MB_TrainerRoadLayerMain.h"
#include "MB_Message.h"
#include "../Common/GameLib/GameHelper/CCGameHelper.h"
#include "../Common/BYGraySprite.h"
MB_TrainerRoadNodePass* MB_TrainerRoadNodePass::create(MB_TrainerRoadDungeon* pDungeon)
{
    MB_TrainerRoadNodePass* pNode = new MB_TrainerRoadNodePass;
    if (pNode && pNode->init())
    {
        pNode->setData(pDungeon);
        pNode->autorelease();
        return pNode;
    }
    CC_SAFE_DELETE(pNode);
    return NULL;
}

MB_TrainerRoadNodePass::MB_TrainerRoadNodePass()
{
    m_pNodeMenu	 = NULL;
    m_pMenuItemIcon	 = NULL;
    m_pName = NULL;
    m_pDungeon = NULL;
    m_pSpriteStatus = NULL;
    m_pForTest = NULL;
    m_bCanFight = false;
}
MB_TrainerRoadNodePass::~MB_TrainerRoadNodePass()
{
    CC_SAFE_RELEASE_NULL(m_pNodeMenu);
    CC_SAFE_RELEASE_NULL(m_pMenuItemIcon);
    CC_SAFE_RELEASE_NULL(m_pName);
    CC_SAFE_RELEASE_NULL(m_pSpriteStatus);
    CC_SAFE_RELEASE_NULL(m_pForTest);
}
bool MB_TrainerRoadNodePass::init()
{
    CCNode* pNode = loadResource("res/road_node_pass.ccbi");
    if(pNode)
	{
		addChild(pNode);
        m_pNodeMenu->setSwallowsTouches(false);
        onResetWnd();
		return true;
	}
	return false;
}

void MB_TrainerRoadNodePass::setStatus(ERoadDungeonStatus e,bool canFight)
{
    m_eStatu = e;
    m_bCanFight = canFight;
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shilian.plist");
    switch (m_eStatu) {
        case DUNGEON_NOT_PASS:
        {
            m_pSpriteStatus->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tmzz_btn_road_1.png"));
        }
            break;
        case DUNGEON_PASSED:
        case DUNGEON_REWARDED:
            m_pSpriteStatus->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tmzz_btn_road_2.png"));
            break;
        default:
            break;
    }
    if(m_pForTest)m_pForTest->setString("");
}

void MB_TrainerRoadNodePass::setData(MB_TrainerRoadDungeon* pData)
{
    m_pDungeon = pData;
    onResetWnd();
}

void MB_TrainerRoadNodePass::onResetWnd()
{
    if(m_pDungeon)
    {
        m_pName->setString(m_pDungeon->getName().c_str());
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shilian.plist");
        m_pSpriteStatus->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tmzz_btn_road_2.png"));
    }
}
bool MB_TrainerRoadNodePass::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeMenu",CCMenu*,m_pNodeMenu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMenuItemIcon",CCMenuItemImage*,m_pMenuItemIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pName", CCLabelBMFont*, m_pName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStatus", CCSprite*, m_pSpriteStatus);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pForTest", CCLabelTTF*, m_pForTest);
	return false;
}

SEL_MenuHandler MB_TrainerRoadNodePass::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onDungeonClicked",MB_TrainerRoadNodePass::onDungeonClicked);
    return NULL;
}

SEL_CCControlHandler MB_TrainerRoadNodePass::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

void MB_TrainerRoadNodePass::onDungeonClicked(CCObject*)
{
    if(m_eStatu == DUNGEON_PASSED)
    {
        MB_Message::sharedMB_Message()->showMessage("已经通过该关卡");
        return;
    }
    else if(m_eStatu == DUNGEON_NOT_PASS && !m_bCanFight)
    {
        MB_Message::sharedMB_Message()->showMessage("通关上一关卡后激活该关卡");
        return;
    }
    
    MB_TARGET_PARENT(MB_TrainerRoadLayerMain, ptr)
    {
        if (ptr)ptr->send_road_fight(m_pDungeon->getName());
    }
}
