//
//  MB_NodeItemBook.cpp
//  ProjectPM
//
//  Create by WenYong on 4/5/2014.
//
//
#include "MB_NodeItemBook.h"
#include "MB_ItemData.h"
#include "MB_MailData.h"
#include "MB_ServerRewardData.h"
#include "MB_LayerItemDetail.h"
#include "MB_LayerPetDetail.h"
#define REWARDSPAN 0
#define ITEMBOOKPERLINENUM 5
#define ITEMBOOKPERLINENUMMAOXIAN 3
MB_NodeItemBook::MB_NodeItemBook()
{
    m_pItemFrame = NULL;
    m_bCircle = false;
    m_pItemIcon	 = NULL;
    m_pItemName	 = NULL;
    m_nNum = 0;
    m_pSpriteDebris = NULL;
    m_pNodeMenu = NULL;
    m_pNode = NULL;
}
MB_NodeItemBook::~MB_NodeItemBook()
{
    CC_SAFE_RELEASE_NULL(m_pNode);
    CC_SAFE_RELEASE_NULL(m_pItemFrame);
    CC_SAFE_RELEASE_NULL(m_pNodeMenu);
    CC_SAFE_RELEASE_NULL(m_pItemIcon);
    CC_SAFE_RELEASE_NULL(m_pItemName);
    CC_SAFE_RELEASE_NULL(m_pSpriteDebris);
}

MB_NodeItemBook* MB_NodeItemBook::create(uint16_t nTypeId,uint32_t num,bool bCircle)
{
    MB_NodeItemBook* pInstance = new MB_NodeItemBook;
    if (pInstance && pInstance->init(nTypeId,num,bCircle))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

bool MB_NodeItemBook::init(uint16_t nTypeId,uint32_t num,bool bCircle)
{
    CCNode* pNode = loadResource("res/suit_node_icon.ccbi");
    if(pNode)
	{
        m_bCircle = bCircle;
		addChild(pNode);
        m_nTypeId = nTypeId;
        m_nNum = num;
        enableClick(false);
        onResetWnd();
		return true;
	}
	return false;
}
void MB_NodeItemBook::onResetWnd()
{
    if (m_bCircle) {
        m_pNode->removeAllChildren();
        NSGameHelper::setItemIconDetailByTid(m_nTypeId, 0, NULL,m_pItemName,NULL,false);
        MB_NodeItem* ni = MB_NodeItem::create(m_nTypeId);
        ni->showLevel(false);
        ni->showNameCount(false);
        ni->setOnClickEnable(false);
        ni->setScale(.9f);
        m_pNode->addChild(ni);
    }else
    {
        NSGameHelper::setItemIconDetailByTid(m_nTypeId, 0, m_pItemIcon,m_pItemName,m_pItemFrame,false);
    }

    if (m_nNum!=0)
    {
        const char* pName = m_pItemName->getString();
        if (pName)
        {
            char buff[64] = {};
            sprintf(buff, "%s*%d",pName,m_nNum);
            
            m_pItemName->setString(buff);
        }
    }
    MB_ItemTemplate *templete = MB_ItemMgr::getInstance()->getItemTemplateByID(m_nTypeId);
    if(m_pSpriteDebris && templete)m_pSpriteDebris->setVisible(templete->getIsDebris());
}
bool MB_NodeItemBook::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNode",CCNode*,m_pNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pItemFrame",CCSprite*,m_pItemFrame);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pItemIcon",CCSprite*,m_pItemIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pItemName",CCLabelTTF*,m_pItemName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteDebris", CCNode*, m_pSpriteDebris);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeMenu", CCNode*, m_pNodeMenu);
	return false;
}

void MB_NodeItemBook::onIconClicked(CCObject* pSender)
{
    showItemDetail();
}

void MB_NodeItemBook::enableClick(bool bEnable)
{
    if (m_pNodeMenu)
    {
        m_pNodeMenu->setVisible(bEnable);
    }
}

void MB_NodeItemBook::showPetDetail()
{
    CCNode* pNode = MB_LayerPetDetail::create(m_nTypeId);
    if (pNode)
    {
        CCDirector::sharedDirector()->getRunningScene()->addChild(pNode,Z_ORDER_OUTSHOW);
    }
}

void MB_NodeItemBook::showItemDetail()
{
    CCNode* layer = MB_LayerItemDetail::createByType(m_nTypeId);
    if (layer)
    {
        MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
        if (pScene)
        {
            pScene->addChild(layer,Z_ORDER_Detail);
        }else{
            CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
        }
    }
}

SEL_MenuHandler MB_NodeItemBook::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onIconClicked", MB_NodeItemBook::onIconClicked);
    return NULL;
}

void MB_NodeItemBook::activateSuitEffective()
{
    CCNode* pNode = m_pNode->getChildByTag(10);
    if (pNode == NULL)
    {
        CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
        CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
        CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/eff_node_suit.ccbi");
        pNode->setScale(.7f);
        m_pNode->addChild(pNode,1,10);
        CC_SAFE_RELEASE_NULL(pCCBReader);
    }
}



MB_NodePetBook* MB_NodePetBook::create(uint16_t nTypeId,uint32_t num)
{
    MB_NodePetBook* pInstance = new MB_NodePetBook;
    if (pInstance && pInstance->init(nTypeId,num))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return NULL;
}

void MB_NodePetBook::onIconClicked(CCObject* pSender)
{
    showPetDetail();
}

void MB_NodePetBook::onResetWnd()
{
    m_pItemFrame->setVisible(true);
    m_pItemIcon->setScale(.327f);
    NSGameHelper::setMonsterIconDetailByTid(m_nTypeId, 0, m_pItemIcon,m_pItemName,m_pItemFrame);
    if (m_nNum!=0)
    {
        const char* pName = m_pItemName->getString();
        if (pName)
        {
            char buff[64] = {};
            sprintf(buff, "%s*%d",pName,m_nNum);
        }
    }
}

MB_NodePetView::MB_NodePetView()
{
    m_nPetRank = 0;
    m_nPetLevel = 1;
    m_nPetTypeID = 0;
}

MB_NodePetView::~MB_NodePetView()
{
    m_nPetRank = 0;
    m_nPetLevel = 1;
    m_nPetTypeID = 0;
}

MB_NodePetView* MB_NodePetView::create(uint16_t nTypeId,uint16_t nLevel,uint16_t nRank)
{
    MB_NodePetView* pInstance = new MB_NodePetView;
    if (pInstance && pInstance->init(nTypeId))
    {
        pInstance->setData(nTypeId, nLevel, nRank);
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

void MB_NodePetView::setData(uint16_t nTypeId,uint16_t nLevel,uint16_t nRank)
{
    m_nPetRank = nRank;
    m_nPetLevel = nLevel;
    m_nPetTypeID = nTypeId;
    
    onResetWnd();
}

void MB_NodePetView::onResetWnd()
{
    m_pItemFrame->setVisible(true);
    m_pItemIcon->setScale(.327f);
    NSGameHelper::setMonsterIconDetailByTid(m_nPetTypeID, m_nPetRank, m_pItemIcon,m_pItemName,m_pItemFrame,true);
    
    char buff[64] = {};
    sprintf(buff, "Lv.%d %s+%d",m_nPetLevel,m_pItemName->getString(),m_nPetRank);
    m_pItemName->setString(buff);
}


MB_NodeRewardItem::MB_NodeRewardItem()
{
    m_pNodeSize = NULL;
}

MB_NodeRewardItem::~MB_NodeRewardItem()
{
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
}
MB_NodeRewardItem* MB_NodeRewardItem::create(uint16_t nTypeId,uint32_t num,bool bCircle)
{
    MB_NodeRewardItem* pInstance = new MB_NodeRewardItem;
    if (pInstance && pInstance->init(nTypeId,num,bCircle))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

bool MB_NodeRewardItem::init(uint16_t nTypeId,uint32_t num,bool bCircle)
{
    CCNode* pNode = loadResource("res/suit_node_icon.ccbi");
    if(pNode)
	{
		addChild(pNode);
        m_nTypeId = nTypeId;
        m_nNum = num;
        enableClick(false);
        onResetWnd();
		return true;
	}
	return false;
}
bool MB_NodeRewardItem::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    if (MB_NodeItemBook::onAssignCCBMemberVariable(pTarget,pMemberVariableName,pNode))
    {
        return true;
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"size",CCNode*,m_pNodeSize);
    return true;
}

void MB_NodeRewardItem::onResetWnd()
{
    MB_NodeItemBook::onResetWnd();
}

MB_NodeRewardPet* MB_NodeRewardPet::create(uint16_t nTypeId,uint32_t num,bool bCircle)
{
    MB_NodeRewardPet* pInstance = new MB_NodeRewardPet;
    if (pInstance && pInstance->init(nTypeId,num,bCircle))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

void MB_NodeRewardPet::onResetWnd()
{
    m_pItemFrame->setVisible(true);
    m_pItemIcon->setScale(.327f);
    NSGameHelper::setMonsterIconDetailByTid(m_nTypeId, 0, m_pItemIcon,m_pItemName,m_pItemFrame,false);
    if (m_nNum!=0)
    {
        const char* pName = m_pItemName->getString();
        if (pName)
        {
            char buff[64] = {};
            sprintf(buff, "%s*%d",pName,m_nNum);
        }
    }
}

MB_LayerRewardContainer::MB_LayerRewardContainer()
{
	isB = false;
}
MB_LayerRewardContainer::~MB_LayerRewardContainer()
{
    
}


MB_LayerRewardContainer* MB_LayerRewardContainer::create(CCArray* valueArray)
{
    MB_LayerRewardContainer* ptr = new MB_LayerRewardContainer();
    if (ptr && ptr->init(valueArray))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}

MB_LayerRewardContainer* MB_LayerRewardContainer::create(CCArray* valueArray, bool b)
{
	MB_LayerRewardContainer* ptr = new MB_LayerRewardContainer();
	if (ptr && ptr->init(valueArray,b))
	{
		ptr->autorelease();
		return ptr;
	}
	CC_SAFE_RELEASE_NULL(ptr);
	return NULL;
}

MB_LayerRewardContainer* MB_LayerRewardContainer::createWithMailReward(sMailReward* pMailReward)
{
    CCArray* pArray = new CCArray;
    if (!NSGameHelper::mailRewardConvert2ValueTemplateArray(pMailReward, pArray))
    {
        pArray->release();
        return NULL;
    }
    
    MB_LayerRewardContainer* pInstance = create(pArray);
    
    pArray->release();
    
    return pInstance;
}

bool MB_LayerRewardContainer::init(CCArray* valueArray, bool b)
{
	isB = b;
	return init(valueArray);
}


bool MB_LayerRewardContainer::init(CCArray* valueArray)
{
    CCLayer::init();
    if(valueArray==NULL || valueArray->count() < 1)
    {
        return false;
    }
    setAnchorPoint(ccp(0.5,0.5));
    
    m_ItemSize = CCSize(122,122);
    CCSize constent_size ;
    constent_size = CCSize(m_ItemSize.width * valueArray->count(),m_ItemSize.height);

    
    RewardTempleteValue* pTemp = NULL;
    CCNode* pItem = NULL;
    MB_PetView* pPetView = NULL;
    CCObject* pObject = NULL;
    removeAllChildren();
    
    CCARRAY_FOREACH(valueArray, pObject)
    {
        pTemp = dynamic_cast<RewardTempleteValue*>(pObject);
        if (pTemp)
        {
            if (pTemp->getType() == kRewardValueTypePet)
            {
                pItem = MB_NodePet::create(pTemp->getValueID());
                if (isB) {
                    ((MB_NodePet*)pItem)->isTopZorder = true;
                }
            }
            else
            {
                pItem = MB_NodeItem::create(pTemp->getValueID());
                ((MB_NodeItem*)pItem)->setNum(pTemp->getNumber());
                if (isB) {
                    ((MB_NodeItem*)pItem)->isTopZorder = true;
                }
            }
            if (pItem != NULL)
            {
                addChild(pItem);
                pItem->setContentSize(m_ItemSize*pItem->getScale());
            }
            continue;
        }
        
        pPetView = dynamic_cast<MB_PetView*>(pObject);
        if(pPetView)
        {
            pItem = MB_NodePet::create(pPetView->getTypeID(),pPetView->getLevel(), pPetView->getRank());
            if (pItem != NULL)
            {
                if (isB) {
                    ((MB_NodePet*)pItem)->isTopZorder = true;
                }
                addChild(pItem);
                pItem->setContentSize(m_ItemSize*pItem->getScale());
            }
            continue;
        }
    }
    
    this->setContentSize(constent_size);
    
    return true;
}
void MB_LayerRewardContainer::setContentSize(const CCSize& contentSize)
{
    float width = getChildrenCount() * m_ItemSize.width * m_fScaleX;
    CCSize sz = contentSize;
    if (sz.width < width)
    {
        sz.width = width;
    }
    CCLayer::setContentSize(sz);
    float offset = (contentSize.width-width) / 2.0;
    setPostionOffset(offset);
}
void MB_LayerRewardContainer::setPostionOffset(float offset)
{
    CCArray* pArray = getChildren();
    if (pArray!=NULL) {
        CCNode* pNode = NULL;
        int i;
        for (i=0; i<pArray->count(); i++) {
            pNode = (CCNode*)pArray->objectAtIndex(i);
            pNode->setPosition(offset + m_ItemSize.width*(i+.5f ), getContentSize().height*.5f);
        }
    }
}

void MB_LayerRewardContainer::setPosLeft()
{
    m_ItemSize = CCSize(94,122);
    CCArray* pArray = getChildren();
    if (pArray!=NULL) {
        CCNode* pNode = NULL;
        int i;
        for (i=0; i<pArray->count(); i++) {
            pNode = (CCNode*)pArray->objectAtIndex(i);
            pNode->setPosition(m_ItemSize.width*(i+.5f ), m_ItemSize.height*.5f);
        }
    }
}
void MB_LayerRewardContainer::setScale(float scale)
{
    m_fScaleX = scale;
    m_fScaleY = scale;
    
    CCSize sz = getContentSize();
    sz.width *= m_fScaleX;
    sz.height *= m_fRotationY;
    setContentSize(sz);
}





MB_LayerRewardContainerEx* MB_LayerRewardContainerEx::create(CCArray* valueArray)
{
    MB_LayerRewardContainerEx* ptr = new MB_LayerRewardContainerEx();
    if (ptr && ptr->init(valueArray))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}


bool MB_LayerRewardContainerEx::init(CCArray* valueArray)
{
    if(valueArray==NULL || valueArray->count() < 1)
    {
        return false;
    }
    setAnchorPoint(ccp(0.5,0.5));
    
    MB_NodeRewardItem* temp = MB_NodeRewardItem::create(0);
    m_ItemSize = temp->getSize();
    RewardTempleteValue* pTemp = NULL;
    MB_NodeItemBook* pItem = NULL;
    MB_PetView* pPetView = NULL;
    CCObject* pObject = NULL;
    removeAllChildren();
    
    
    //计算size和坐标
    int countAll = valueArray->count();
    std::vector<CCPoint> pt;
    pt.reserve(countAll);
    CCSize size;
    if(countAll<ITEMBOOKPERLINENUM)size.width = m_ItemSize.width*countAll;
    else size.width = m_ItemSize.width*ITEMBOOKPERLINENUM;
    size.height = (countAll/ITEMBOOKPERLINENUM)*m_ItemSize.height + ((countAll%ITEMBOOKPERLINENUM) > 0?1:0 )*m_ItemSize.height;
    CCLayer::setContentSize(size);
    
    
    for(int i = 0;i <countAll;i++)
    {
        pt[i].x = (0.5f + i%ITEMBOOKPERLINENUM)* m_ItemSize.width;
        pt[i].y = size.height - (0.5f + i/ITEMBOOKPERLINENUM)*m_ItemSize.height;
    }
    
    int index = 0;
    CCARRAY_FOREACH(valueArray, pObject)
    {
        pTemp = dynamic_cast<RewardTempleteValue*>(pObject);
        if (pTemp)
        {
            if (pTemp->getType() == kRewardValueTypePet)
            {
                pItem = MB_NodeRewardPet::create(pTemp->getValueID(),pTemp->getNumber(),true);
            }
            else
            {
                pItem = MB_NodeRewardItem::create(pTemp->getValueID(),pTemp->getNumber(),false);
            }
            if (pItem != NULL)
            {
                addChild(pItem);
                pItem->setContentSize(m_ItemSize);
                pItem->setPosition(pt[index]);
                index++;
            }
            continue;
        }
        
        pPetView = dynamic_cast<MB_PetView*>(pObject);
        if(pPetView)
        {
            pItem = MB_NodePetView::create(pPetView->getTypeID(), pPetView->getLevel(), pPetView->getRank());
            if (pItem != NULL)
            {
                addChild(pItem);
                pItem->setContentSize(m_ItemSize);
                pItem->setPosition(pt[index]);
                index++;
            }
            continue;
        }
    }
    
    return true;
}

void MB_LayerRewardContainerEx::setCenter(CCSize contanerSize)
{
    float tempFloat = (contanerSize.width-getContentSize().width)/2;
    float tempFloat2 = 0;
    if (getChildrenCount()<ITEMBOOKPERLINENUM) {
        tempFloat2 = (getContentSize().height-contanerSize.height)/2;
    }
    CCArray *pChildren = getChildren();
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(pChildren, pObject)
    {
        CCNode* pChild = (CCNode*) pObject;
        pChild->setPosition(pChild->getPosition()+ccp(tempFloat,tempFloat2));
    }
}

MB_LayerRewardContainerMaoXian* MB_LayerRewardContainerMaoXian::create(CCArray* valueArray)
{
    MB_LayerRewardContainerMaoXian* ptr = new MB_LayerRewardContainerMaoXian();
    if (ptr && ptr->init(valueArray))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}


bool MB_LayerRewardContainerMaoXian::init(CCArray* valueArray)
{
    if(valueArray==NULL || valueArray->count() < 1)
    {
        return false;
    }
    setAnchorPoint(ccp(0.5,0.5));
    
    MB_NodeRewardItem* temp = MB_NodeRewardItem::create(0);
    m_ItemSize = temp->getSize();
    RewardTempleteValue* pTemp = NULL;
    MB_NodeItemBook* pItem = NULL;
    MB_PetView* pPetView = NULL;
    CCObject* pObject = NULL;
    removeAllChildren();
    
    
    //计算size和坐标
    int countAll = valueArray->count();
    std::vector<CCPoint> pt;
    pt.reserve(countAll);
    CCSize size;
    size.width = m_ItemSize.width*ITEMBOOKPERLINENUMMAOXIAN;
    size.height = (countAll/ITEMBOOKPERLINENUMMAOXIAN)*m_ItemSize.height + ((countAll%ITEMBOOKPERLINENUMMAOXIAN) > 0?1:0 )*m_ItemSize.height;
    CCLayer::setContentSize(size);
    
    
    for(int i = 0;i <countAll;i++)
    {
        pt[i].x = (-i%ITEMBOOKPERLINENUMMAOXIAN)* m_ItemSize.width;
        pt[i].y = size.height - (1 + i/ITEMBOOKPERLINENUMMAOXIAN)*m_ItemSize.height;
    }
    
    int index = 0;
    CCARRAY_FOREACH(valueArray, pObject)
    {
        pTemp = dynamic_cast<RewardTempleteValue*>(pObject);
        if (pTemp)
        {
            if (pTemp->getType() == kRewardValueTypePet)
            {
                pItem = MB_NodeRewardPet::create(pTemp->getValueID(),pTemp->getNumber(),true);
            }
            else
            {
                pItem = MB_NodeRewardItem::create(pTemp->getValueID(),pTemp->getNumber(),false);
            }
            if (pItem != NULL)
            {
                addChild(pItem);
                pItem->setContentSize(m_ItemSize);
                pItem->setPosition(pt[index]);
                index++;
            }
            continue;
        }
        
        pPetView = dynamic_cast<MB_PetView*>(pObject);
        if(pPetView)
        {
            pItem = MB_NodePetView::create(pPetView->getTypeID(), pPetView->getLevel(), pPetView->getRank());
            if (pItem != NULL)
            {
                addChild(pItem);
                pItem->setContentSize(m_ItemSize);
                pItem->setPosition(pt[index]);
                index++;
            }
            continue;
        }
    }
    
    return true;
}

