//
//  MB_TrainerRoadNodeBox.cpp
//  ProjectMB
//
//  Create by wenyong on 15/1/2015.
//
//
#include "MB_TrainerRoadNodeBox.h"
#include "MB_TrainerRoadProtocol.h"
#include "MB_TrainerRoadLayerMain.h"
#include "MB_LocalProto.h"
#include "MB_Message.h"
#include "../Common/GameLib/GameHelper/CCGameHelper.h"
#include "../Common/BYGraySprite.h"
void MB_TrainerRoadNodeBox::setStatus(ERoadBoxStatus e)
{
    m_eStatu = e;
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shilian.plist");
    switch (m_eStatu)
    {
        case BOX_ACTIVATED:
        {
            m_pSpriteStatus->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tmzz_btn_road_chest_1.png"));
        }
            break;
        case BOX_NOT_ACTIVATED:
        {
            m_pSpriteStatus->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tmzz_btn_road_chest_1.png"));
        }
            break;
        case BOX_ACTIVATED_REWARDED:
        {
            m_pSpriteStatus->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tmzz_btn_road_chest_2.png"));
        }
            break;
        default:
            break;
    }
    if(m_pForTest)m_pForTest->setString("");
}

MB_TrainerRoadNodeBox* MB_TrainerRoadNodeBox::create(MB_TrainerRoadRewardBox* pBox)
{
    MB_TrainerRoadNodeBox* pNode = new MB_TrainerRoadNodeBox;
    if (pNode && pNode->init())
    {
        pNode->setData(pBox);
        pNode->autorelease();
        return pNode;
    }
    CC_SAFE_DELETE(pNode);
    return NULL;
}

void MB_TrainerRoadNodeBox::setData(MB_TrainerRoadRewardBox* pData)
{
    m_pBox = pData;
    onResetWnd();
}

MB_TrainerRoadNodeBox::MB_TrainerRoadNodeBox()
{
    m_pNodeMenu	 = NULL;
    m_pMenuImageIcon	 = NULL;
    m_pBox = NULL;
    m_pSpriteStatus = NULL;
    m_pForTest = NULL;
}
MB_TrainerRoadNodeBox::~MB_TrainerRoadNodeBox()
{
    CC_SAFE_RELEASE_NULL(m_pNodeMenu);
    CC_SAFE_RELEASE_NULL(m_pMenuImageIcon);
    CC_SAFE_RELEASE_NULL(m_pSpriteStatus);
    CC_SAFE_RELEASE_NULL(m_pForTest);
}
bool MB_TrainerRoadNodeBox::init()
{
    CCNode* pNode = loadResource("res/road_node_box.ccbi");
    if(pNode)
	{
		addChild(pNode);
        m_pNodeMenu->setSwallowsTouches(false);
        onResetWnd();
		return true;
	}
	return false;
}
void MB_TrainerRoadNodeBox::onResetWnd()
{

}
bool MB_TrainerRoadNodeBox::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeMenu",CCMenu*,m_pNodeMenu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMenuImageIcon",CCMenuItemImage*,m_pMenuImageIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStatus", CCSprite*, m_pSpriteStatus);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pForTest", CCLabelTTF*, m_pForTest);
	return false;
}

SEL_MenuHandler MB_TrainerRoadNodeBox::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onBoxClicked",MB_TrainerRoadNodeBox::onBoxClicked);
    return NULL;
}
SEL_CCControlHandler MB_TrainerRoadNodeBox::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

void MB_TrainerRoadNodeBox::onBoxClicked(CCObject*)
{
    if(m_eStatu == BOX_NOT_ACTIVATED)
    {
        MB_Message::sharedMB_Message()->showMessage("通关上一关卡后激活该关卡");
        return;
    }
    else if(m_eStatu == BOX_ACTIVATED_REWARDED )
    {
        MB_Message::sharedMB_Message()->showMessage("已经领取");
        return;
    }
    
    
    MB_TARGET_PARENT(MB_TrainerRoadLayerMain, ptr)
    {
        if(ptr)ptr->send_road_box();
    }
}

