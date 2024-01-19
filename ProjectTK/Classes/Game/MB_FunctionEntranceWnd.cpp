//
//  MB_FunctionEntranceWnd.cpp
//  ProjectPM
//
//  Created by wenyong on 14-3-21.
//
//

#include "MB_FunctionEntranceWnd.h"
#include "MB_FunctionConfig.h"
#include "Game.h"
#include "MB_FunctionMgr.h"
using namespace NSGameFunction;

MB_FunctionEntranceWnd::MB_FunctionEntranceWnd():\
m_pFlagNode2(NULL),
m_pFlag2(NULL),
m_bEnable(true),
m_pItemImage(NULL),
m_pSpriteName(NULL),
m_pScroller(NULL),
m_nType(0)
{
    //CCLOG("CreateEntranceWnd:%p",this);
}

MB_FunctionEntranceWnd::~MB_FunctionEntranceWnd()
{
    CC_SAFE_RELEASE_NULL(m_pFlagNode2);
    CC_SAFE_RELEASE_NULL(m_pFlag2);
    CC_SAFE_RELEASE_NULL(m_pItemImage);
    CC_SAFE_RELEASE_NULL(m_pSpriteName);
    CC_SAFE_RELEASE_NULL(m_pScroller);
    
    //CCLOG("DestroyEntranceWnd:%p",this);
}


bool MB_FunctionEntranceWnd::init()
{
    CCNode* pNode = loadResource("res/main_node_structure.ccbi");
    if (pNode)
    {
        addChild(pNode);
    }
    m_pScroller->setSwallowsTouches(true);
    onInitializedWnd();
    return true;
}



void MB_FunctionEntranceWnd::onInitializedWnd()
{
//    m_pItemImage->setIsScale(false);
    onResetWnd();
}

void MB_FunctionEntranceWnd::onResetWnd()
{
    if (m_pDataSource)
    {
        uint32_t kType = ((NSGameFunction::CCFunctionInterface*)m_pDataSource)->getFunctionType();
        MB_FunctionItem* pItem =  MB_FunctionConfigure::getInstance()->queryFunctionItemByType(kType);
        if (pItem)
        {
            if(pItem->getNeedLevel()<=MB_RoleData::getInstance()->getLevel())
            {
                setEnable();
            }
            else
            {
                setDisable();
            }
        }
    }
    m_pFlagNode2->setVisible(false);
}

bool MB_FunctionEntranceWnd::onAssignCCBMemberVariable(CCObject* pTarget,
                                                       const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_flag_2", CCNode*,m_pFlagNode2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "flag_2", CCLabelBMFont*,m_pFlag2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "MenuIcon", CCMenuItemImage*,m_pItemImage);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sprite_name", CCSprite*, m_pSpriteName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "scroller", CCMenu*, m_pScroller);
    return false;
}

void MB_FunctionEntranceWnd::onEntranceClicked(CCObject* pSender)
{
//    CCNode* node = this->getParent();
//    CCSize size = CCDirector::sharedDirector()->getWinSize();
//    
//    CCRipple3D* effect = CCRipple3D::create(5, CCSizeMake(3,2),node->getPosition(), 120, 5, 240);
//    
////    CCShaky3D* effect =CCShaky3D::create(0.5, CCSizeMake(5,4), 4, false);
//    node->runAction(effect);
//    return;
    
    TutorialTriggerComplete
    if (m_pDataSource)
    {
        if (m_bEnable)
        {
            ((CCFunctionInterface*)m_pDataSource)->onEntryClicked(this);
        }
        else
        {
            MB_FunctionItem* pItem = MB_FunctionConfigure::getInstance()->queryFunctionItemByType(((CCFunctionInterface*)m_pDataSource)->getFunctionType());
            if (pItem)
            {
                char buff[64] = {};
                sprintf(buff,"%s将在%d级开放",pItem->getFunctionName().c_str(),pItem->getNeedLevel());
                MB_Message::sharedMB_Message()->showMessage(buff);
            }
            
            CCLog("function is not opened");
        }
    }

}

SEL_MenuHandler MB_FunctionEntranceWnd::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onEntranceClicked", MB_FunctionEntranceWnd::onEntranceClicked);
    return NULL;
}

SEL_CCControlHandler MB_FunctionEntranceWnd::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

void MB_FunctionEntranceWnd::setEnable()
{
    if (m_pDataSource)
    {
        MB_FunctionConfigure::getInstance()->loadResource2SpriteCache();
        MB_FunctionItem* pItem = MB_FunctionConfigure::getInstance()->queryFunctionItemByType(((CCFunctionInterface*)m_pDataSource)->getFunctionType());
        if (pItem && !pItem->getEnableFile().empty())
        {
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("btn_2.plist");
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pItem->getEnableFile().c_str());
            if (frame)
            {
                m_pItemImage->setNormalSpriteFrame(frame);
                m_pItemImage->setSelectedSpriteFrame(frame);
                m_pItemImage->setDisabledSpriteFrame(frame);
            }
        }
        NSGameHelper::setSpriteFrameWithFrameCache(m_pSpriteName, pItem->getNameEnable().c_str());
    }
    m_bEnable = true;
}

void MB_FunctionEntranceWnd::setDisable()
{
    if (m_pDataSource)
    {
        MB_FunctionConfigure::getInstance()->loadResource2SpriteCache();
        MB_FunctionItem* pItem = MB_FunctionConfigure::getInstance()->queryFunctionItemByType(((CCFunctionInterface*)m_pDataSource)->getFunctionType());
        if (pItem && !pItem->getDisableFile().empty())
        {
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pItem->getDisableFile().c_str());
            if (frame)
            {
                m_pItemImage->setNormalSpriteFrame(frame);
                m_pItemImage->setSelectedSpriteFrame(frame);
                m_pItemImage->setDisabledSpriteFrame(frame);
            }
        }
        NSGameHelper::setSpriteFrameWithFrameCache(m_pSpriteName, pItem->getNameDisable().c_str());
    }
    m_bEnable = false;
}
