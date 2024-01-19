//
//  MB_NodeHoverEntry.cpp
//  ProjectPM
//
//  Create by WenYong on 18/6/2014.
//
//
#include "MB_NodeHoverEntry.h"
#include "MB_LayerHome.h"
#include "MB_LoginNotice.h"
MB_NodeHoverEntry::MB_NodeHoverEntry()
{
    scroller	 = NULL;
    m_pMenuItemImage	 = NULL;
    m_pNameLabel	 = NULL;
    m_pFlagNode2	 = NULL;
    m_pFlag2	 = NULL;
    m_pAnimation = NULL;
    m_nType = 0;
}
MB_NodeHoverEntry::~MB_NodeHoverEntry()
{
    CC_SAFE_RELEASE_NULL(scroller);
    CC_SAFE_RELEASE_NULL(m_pMenuItemImage);
    CC_SAFE_RELEASE_NULL(m_pNameLabel);
    CC_SAFE_RELEASE_NULL(m_pFlagNode2);
    CC_SAFE_RELEASE_NULL(m_pFlag2);
    CC_SAFE_RELEASE_NULL(m_pAnimation);
}
bool MB_NodeHoverEntry::init()
{
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/main_node_hangicon.ccbi", this);
    if(pNode)
	{
		addChild(pNode);
        m_pAnimation = pCCBReader->getAnimationManager();
        CC_SAFE_RETAIN(m_pAnimation);
        CC_SAFE_RELEASE(pCCBReader);
		return true;
	}
    CC_SAFE_RELEASE(pCCBReader);
	return false;
}

void MB_NodeHoverEntry::setType(int type)
{
    m_nType = type;
    onResetWnd();
}
void MB_NodeHoverEntry::onResetWnd()
{
    MB_FunctionItem* pItem = MB_FunctionConfigure::getInstance()->queryFunctionItemByType(m_nType);
    if (pItem)
    {
        MB_FunctionConfigure::getInstance()->loadResource2SpriteCache();
        NSGameHelper::setSpriteFrameWithFrameCache(m_pNameLabel, pItem->getNameEnable().c_str());
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pItem->getEnableFile().c_str());
        if (frame)
        {
            m_pMenuItemImage->setBackgroundSpriteFrameForState(frame, CCControlStateNormal);
            m_pMenuItemImage->setBackgroundSpriteFrameForState(frame, CCControlStateHighlighted);
            m_pMenuItemImage->setBackgroundSpriteFrameForState(frame, CCControlStateSelected);
            m_pMenuItemImage->setBackgroundSpriteFrameForState(frame, CCControlStateDisabled);
            m_pMenuItemImage->setPreferredSize(frame->getOriginalSize());
        }
    }
}
bool MB_NodeHoverEntry::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"scroller",CCMenu*,scroller);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMenuItemImage",CCControlButton*,m_pMenuItemImage);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNameLabel",CCSprite*,m_pNameLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeFlag2",CCNode*,m_pFlagNode2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTxtFlag2",CCLabelBMFont*,m_pFlag2);
	return false;
}
SEL_MenuHandler MB_NodeHoverEntry::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
SEL_CCControlHandler MB_NodeHoverEntry::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onEntranceClicked", MB_NodeHoverEntry::onEntranceClicked);
	return NULL;
}
void MB_NodeHoverEntry::onEntranceClicked(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(m_nType, this);
}

void MB_NodeHoverEntry2::onEntranceClicked(CCObject* pSender)
{
    switch (m_nType) {
        case kFunctionGongGao:
            ((MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene())->addChild(MB_LoginNotice::create(), Z_ORDER_OUTSHOW);
            break;
        case kFunctionJianShang:
            MB_LayerHome* layerHome = (MB_LayerHome*)getParent()->getParent()->getParent()->getParent()->getParent();
            layerHome->onAndOffBtn();
            break;
    }
}
