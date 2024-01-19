//
//  MB_NodeBannerEntry.cpp
//  ProjectPM
//
//  Create by WenYong on 18/6/2014.
//
//
#include "MB_NodeBannerEntry.h"

MB_NodeBannerEntry::MB_NodeBannerEntry()
{
    m_pNoAcitveSpr = NULL;
    m_pNodeSize	 = NULL;
    scroller	 = NULL;
    m_pMenuItemImage	 = NULL;
    m_pAnimation = NULL;
    m_nType = 0;
    m_bEnable = false;
}
MB_NodeBannerEntry::~MB_NodeBannerEntry()
{
    CC_SAFE_RELEASE_NULL(m_pNoAcitveSpr);
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(scroller);
    CC_SAFE_RELEASE_NULL(m_pMenuItemImage);
    CC_SAFE_RELEASE_NULL(m_pAnimation);
}
bool MB_NodeBannerEntry::init()
{
    CCNode* pNode = loadResource("res/station_node_unit.ccbi");
    if(pNode)
	{
		addChild(pNode);
        scroller->setSwallowsTouches(false);
        m_pMenuItemImage->setIsScale(false);
		return true;
	}
	return false;
}

CCNode* MB_NodeBannerEntry::loadResource(const char* pName)
{
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile(pName, this);
    m_pAnimation = pCCBReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pAnimation);
    CC_SAFE_RELEASE(pCCBReader);
    
    return pNode;
}
void MB_NodeBannerEntry::setType(int type)
{
    m_nType = type;
    onResetWnd();
}
void MB_NodeBannerEntry::onResetWnd()
{
    if (m_nType != 0)
    {
        MB_FunctionItem* pItem = MB_FunctionConfigure::getInstance()->queryFunctionItemByType(m_nType);
        if (pItem)
        {
            MB_FunctionConfigure::getInstance()->loadResource2SpriteCache();
            if (MB_FunctionConfigure::getInstance()->getFunctionLimitLevel(m_nType))
            {
                setItemImage(pItem->getEnableFile().c_str());
                setEnable();
            }
            else
            {
                setItemImage(pItem->getDisableFile().c_str());
                setDisable();
            }
        }
    }
}

void MB_NodeBannerEntry::showActivities(bool bShow,bool isLevelLimit)
{
    m_bisLevelLimit = isLevelLimit;
    if (!bShow)
    {
        m_pNoAcitveSpr->setVisible(true);
    }
}

bool MB_NodeBannerEntry::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNoAcitveSpr",CCNode*,m_pNoAcitveSpr);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize",CCNode*,m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"scroller",CCMenu*,scroller);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMenuItemImage",CCMenuItemImage*,m_pMenuItemImage);
	return false;
}
SEL_MenuHandler MB_NodeBannerEntry::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onChapterClicked",MB_NodeBannerEntry::onChapterClicked);
	return NULL;
}
SEL_CCControlHandler MB_NodeBannerEntry::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
void MB_NodeBannerEntry::onChapterClicked(CCObject* pSender)
{
    if (m_bEnable)
    {
        runAction(CCCallFuncO::create(this, callfuncO_selector(MB_NodeBannerEntry::goFunction), pSender));
    }
}
void MB_NodeBannerEntry::goFunction(CCObject* pSender)
{
    TutorialTriggerComplete
    MB_FunctionMgr::getInstance()->goFunction(m_nType, this);
}
bool MB_NodeBannerEntry::setItemImage(const char* pFile)
{
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pFile);
    if (frame)
    {
        m_pMenuItemImage->setNormalSpriteFrame(frame);
        m_pMenuItemImage->setSelectedSpriteFrame(frame);
        m_pMenuItemImage->setDisabledSpriteFrame(frame);
        return true;
    }
    return false;
}
void MB_NodeBannerEntry::setEnable()
{
    m_bEnable = true;
}
void MB_NodeBannerEntry::setDisable()
{
    m_bEnable = false;
}

const CCSize& MB_NodeBannerEntry::getUnitSize()
{
    static CCSize sz = CCSizeMake(-1, -1);
    if (sz.width<0)
    {
        MB_NodeBannerEntry* pNode = new MB_NodeBannerEntry;
        if (pNode && pNode->init())
        {
            sz = pNode->m_pNodeSize->getContentSize();
        }
        CC_SAFE_RELEASE_NULL(pNode);
    }
    
    return sz;
}

MB_NodeBannerEntry* MB_NodeBannerEntry::create(int Type)
{
    MB_NodeBannerEntry* pNode = new MB_NodeBannerEntry;
    if (pNode && pNode->init())
    {
        pNode->autorelease();
        pNode->setType(Type);
        return pNode;
    }
    
    CC_SAFE_RELEASE_NULL(pNode);
    return NULL;
}
