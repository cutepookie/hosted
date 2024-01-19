//
//  MB_LayerShowPic.cpp
//  ProjectTK
//
//  Created by ywg on 13-5-30.
//
//

#include "MB_LayerShowPic.h"
#include "MB_FunctionMainWnd.h"
#include "MB_LayerItemDetail.h"
#include "CCTableView.h"
#include "MB_LayerPicDeploy.h"
#include "MB_NodePicIcon.h"
#include "MB_ScrollBg.h"
//#include "CCFunctionEntryInterface.h"
USING_NS_CC;
USING_NS_CC_EXT;

//pvp排行逻辑功能类
MB_LayerShowPic::MB_LayerShowPic()
{
    m_pContainer = NULL;  
    m_pButtonPagePet = NULL;
    m_pButtonPageEquip = NULL;
    m_pButtonPageTreasure = NULL;
    
//    m_pActiveNode = NULL;
    m_kShowPicType = kShowPicTypePet;
    
    m_pTableView = NULL;
    m_pItemArray = new CCArray();
}

MB_LayerShowPic::~MB_LayerShowPic()
{
    CC_SAFE_RELEASE_NULL(m_pContainer);
    
    CC_SAFE_RELEASE_NULL(m_pButtonPagePet);
    CC_SAFE_RELEASE_NULL(m_pButtonPageEquip);
    CC_SAFE_RELEASE_NULL(m_pButtonPageTreasure);
    
    CC_SAFE_RELEASE_NULL(m_pItemArray);
}

MB_LayerShowPic* MB_LayerShowPic::create(kShowPicType type)
{
    MB_LayerShowPic* layer = new MB_LayerShowPic();
    if (layer != NULL && layer->init(type)) {
        layer->autorelease();
        return layer;
    }
    delete layer;
    return NULL;
}

bool MB_LayerShowPic::init(kShowPicType type)
{
	if ( !CCLayer::init() )return false;
    
    m_kShowPicType = type;
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode *pScene = pCCBReader->readNodeGraphFromFile("res/main_layer_handbook.ccbi", this);
    this->addChild(pScene);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    NSGameHelper::adjustScrollNode(m_pContainer);
    m_pButtonPagePet->setIsScale(false);
    m_pButtonPageEquip->setIsScale(false);
    m_pButtonPageTreasure->setIsScale(false);
    
//    m_pButtonPageTreasure->getNormalImage()->setAnchorPoint(ccp(0.5,0));
//    m_pButtonPageTreasure->getSelectedImage()->setAnchorPoint(ccp(0.5,0));
    
    m_szCell = CCSize(MB_NodePicIcon::getNodeSize().width*5,MB_NodePicIcon::getNodeSize().height);
    CCArray* pArrayClientAll = NULL;
    CCArray* pArrayServerAll = NULL;
    MB_PicShow* pPicShow = NULL;
    pArrayClientAll = MB_DataShowPic::getInstance()->getClientTreasureTempleteArray();
    pArrayServerAll = MB_DataShowPic::getInstance()->getServerTreasureTempleteArray();
    CCARRAY_FOREACH_4TYPE(pArrayClientAll, MB_PicShow*, pPicShow)
    {
        bool bIsActivata = false;
        for (int j = 0; j < pArrayServerAll->count(); j++)
        {
            MB_PicShow* data = (MB_PicShow*)pArrayServerAll->objectAtIndex(j);
            if (data->getID() == pPicShow->getID())
            {
                bIsActivata = true;
                break;
            }
        }
        if (!bIsActivata && pPicShow->getActivata()) //没激活 也没默认激活  不显示
        {
            continue;
        }
        MB_PicShow* showData = new MB_PicShow();
        showData->setID(pPicShow->getID());
        showData->setShape(pPicShow->getShape());
        showData->setActivata(bIsActivata);
        showData->setIsNew(pPicShow->getIsNew());
        m_pItemArray->addObject(showData);
        CC_SAFE_RELEASE_NULL(showData);
    }
    
    onPetClicked(NULL);
    
    m_pButtonPagePet->setIsScale(false);
    m_pButtonPageEquip->setIsScale(false);
    m_pButtonPageTreasure->setIsScale(false);
    
    pScene->addChild(MB_ScrollBg::create(left_top,0),-1);
	return true;
}

CCSize MB_LayerShowPic::cellSizeForTable(CCTableView *table)
{
    return m_szCell;
}
CCTableViewCell* MB_LayerShowPic::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell = table->dequeueCell();
    if (cell == NULL)
    {
        cell = new CCTableViewCell();
        cell->autorelease();
    }
    else
    {
        cell->removeAllChildren();
    }
    
    CCLayer* layer = CCLayer::create();
    layer->setContentSize(m_szCell);

    int index = m_pItemArray->count()/5 + ((m_pItemArray->count()%5) == 0? 0:1) -idx -1;
    for (int i = index*5;i < (index+1)*5 && i < m_pItemArray->count();i++)
    {
        MB_PicShow* showData = dynamic_cast<MB_PicShow*>(m_pItemArray->objectAtIndex(i));
        if (showData == NULL)
        {
            return cell;
        }

        if (kShowPicTypeTreasure == m_kShowPicType)
        {
            MB_NodePicIcon* icon =  MB_NodePicIcon::create();
            if (icon != NULL)
            {
                icon->setData(showData, kTypeEquipPic);
                layer->addChild(icon);
            }
            
            icon->setPosition(ccp(m_szCell.width/5*(0.5 + i%5) + 30, m_szCell.height/2));
        }
        else
        {
            CCLOG("ERROR: pic ");
            return cell;
        }
        
    }
    cell->addChild(layer);
    return cell;

}
unsigned int MB_LayerShowPic::numberOfCellsInTableView(CCTableView *table)
{
    if (m_kShowPicType == kShowPicTypeTreasure)
    {
        return m_pItemArray->count()/5 + ((m_pItemArray->count()%5) == 0? 0:1);
    }
    return 0;
}
void MB_LayerShowPic::onResetWnd()
{
    //更新按钮高亮
    updateButtonSelect();
    
    //更新scrollview
    if (m_kShowPicType == kShowPicTypePet)
    {
        enterPet();
    }
    else if (m_kShowPicType == kShowPicTypeEquip)
    {
        enterEquip();
    }
    else if (m_kShowPicType == kShowPicTypeTreasure)
    {
        enterTreasure();
    }
    else
    {
        MB_LOG("unkown type: %d", m_kShowPicType);
    }
}

void MB_LayerShowPic::enterPet()
{
    m_pContainer->removeAllChildren();
    MB_LayerPicDeploy* layer = MB_LayerPicDeploy::create(m_pContainer->getContentSize(),kTypePetPic);
    if (layer != NULL)
    {
        m_pContainer->addChild(layer);
    }
}

void MB_LayerShowPic::enterEquip()
{
    m_pContainer->removeAllChildren();
    MB_LayerPicDeploy* layer = MB_LayerPicDeploy::create(m_pContainer->getContentSize(),kTypeEquipPic);
    if (layer != NULL)
    {
        m_pContainer->addChild(layer);
    }
}

void MB_LayerShowPic::enterTreasure()
{
    m_pContainer->removeAllChildren();
    MB_LayerPicDeploy* layer = MB_LayerPicDeploy::create(m_pContainer->getContentSize(),kTypeTreasurePic);
    if (layer != NULL)
    {
        m_pContainer->addChild(layer);
    }
    
    
//    m_pContainer->removeAllChildren();
//    m_pTableView = CCTableView::create(this, m_pContainer->getContentSize());
//    m_pTableView->setDirection(kCCScrollViewDirectionVertical);
//    //    m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
//    m_pContainer->addChild(m_pTableView);
//    m_pTableView->reloadData();
}

bool MB_LayerShowPic::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pContainer", CCNode*, m_pContainer);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btPet", CCMenuItemImage*, m_pButtonPagePet);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btEquip", CCMenuItemImage*, m_pButtonPageEquip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btTreasure", CCMenuItemImage*, m_pButtonPageTreasure);
    
    return true;
}

SEL_MenuHandler MB_LayerShowPic::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPetClicked", MB_LayerShowPic::onPetClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onEquipClicked", MB_LayerShowPic::onEquipClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onTreasureClicked", MB_LayerShowPic::onTreasureClicked);
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClicked", MB_LayerShowPic::onCloseClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onDetailClicked", MB_LayerShowPic::onDetailClicked);
    
    return NULL;
}

SEL_CCControlHandler MB_LayerShowPic::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

void MB_LayerShowPic::updateButtonSelect()
{
    m_pButtonPagePet->setEnabled(m_kShowPicType != kShowPicTypePet);
    m_pButtonPageEquip->setEnabled(m_kShowPicType != kShowPicTypeEquip);
    m_pButtonPageTreasure->setEnabled(m_kShowPicType != kShowPicTypeTreasure);
}

void MB_LayerShowPic::onPetClicked(cocos2d::CCObject *sender)
{
    MB_LOG("onPetClicked");
    m_kShowPicType = kShowPicTypePet;
    updateButtonSelect();
    dirty();
}

void MB_LayerShowPic::onEquipClicked(cocos2d::CCObject *sender)
{
    MB_LOG("onEquipClicked");
    m_kShowPicType = kShowPicTypeEquip;
    updateButtonSelect();
    dirty();
}

void MB_LayerShowPic::onTreasureClicked(cocos2d::CCObject *sender)
{
    m_kShowPicType = kShowPicTypeTreasure;
    MB_LOG("onTreasureClicked");
    updateButtonSelect();
    dirty();
}


void MB_LayerShowPic::onDetailClicked(cocos2d::CCObject *sender)
{
    MB_LOG("onDetailClicked");
    if (m_kShowPicType == kShowPicTypePet)
    {
        int tag = ((CCMenuItemImage*)sender)->getTag();
        MB_ResWindow* layer = MB_LayerPetDetail::create(tag/10,tag%10);
        if(layer)CCDirector::sharedDirector()->getRunningScene()->addChild(layer,Z_ORDER_OUTSHOW);
    }
    else if (m_kShowPicType == kShowPicTypeEquip
             || m_kShowPicType == kShowPicTypeTreasure)
        
    {
        MB_ResWindow* layer = MB_LayerItemDetail::createByType(((CCMenuItemImage*)sender)->getTag());
        MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
        if (pScene)
        {
            pScene->addChild(layer,Z_ORDER_Detail);
        }else{
            CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
        }
    }
}

void MB_LayerShowPic::onCloseClicked(CCObject* sender)
{
    MB_LOG("onCloseClicked");
//    popWindow();
    NSGameFunction::CCFunctionInterface::goFunctionHome();
}
