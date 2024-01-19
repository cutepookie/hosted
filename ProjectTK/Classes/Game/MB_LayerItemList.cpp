//
//  MB_LayerItemList.cpp
//  ProjectPM
//
//  Create by WenYong on 6/5/2014.
//
//
#include "MB_LayerItemList.h"
#include "MB_FunctionModule.h"

MB_LayerItemList::MB_LayerItemList()
{
    m_pTitleSpr = NULL;
    m_pNodeContainer = NULL;
    m_bShowRoleInfoPanel = true;
}
MB_LayerItemList::~MB_LayerItemList()
{
    CC_SAFE_RELEASE_NULL(m_pTitleSpr);
    CC_SAFE_RELEASE_NULL(m_pNodeContainer);
    m_vContainer.clear();
}
bool MB_LayerItemList::init()
{
    CCNode* pNode = loadResource("res/item_layer_back.ccbi");
    if(pNode)
	{
        addChild(NSGameHelper::createDisableTouchLayer12());
		addChild(pNode);
		return true;
	}
	return false;
}
void MB_LayerItemList::onResetWnd()
{
    
}
void MB_LayerItemList::onItemUsed(MB_ItemData* itemUID)
{
    std::vector<uint64_t>::iterator it = m_vContainer.begin();
    for (; it!=m_vContainer.end();)
    {
        if (*it == itemUID->getItemUID())
        {
            if(MB_ItemMgr::getInstance()->getItemEntityCount(itemUID->getItemID())==1)
            {
                it = m_vContainer.erase(it);
                continue;
            }
        }
        ++it;
    }
}
bool MB_LayerItemList::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTitleSpr",CCSprite*,m_pTitleSpr);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"node_list",CCNode*,m_pNodeContainer);
	return false;
}
SEL_MenuHandler MB_LayerItemList::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerItemList::onCloseClick);
	return NULL;
}
SEL_CCControlHandler MB_LayerItemList::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    
	return NULL;
}
void MB_LayerItemList::onCloseClick(CCObject* pSender)
{
    popWindow();
}

void MB_LayerItemList::setItems(std::vector<uint64_t>& items)
{
    m_vContainer.clear();
    m_vContainer.assign(items.begin(), items.end());
    onResetWnd();
}
const char* titleName[3] = {"txt_buchong_tili.png","txt_buchong_maoxian.png","txt_buchong_tiaozhan.png"};
void MB_LayerItemList::setTitle(int index)
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("commontmzz.plist"); m_pTitleSpr->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(titleName[index-1]));
}

