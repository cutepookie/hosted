
#include "MB_DrawEquip.h"
#include "MB_ItemData.h"
#include "MB_LayerToyShopMain.h"
#include "MB_DrawEquipmentProtocol.h"
#include "MB_LayerItemDetail.h"
#include "MB_ToyShopInterface.h"
#include "MB_FunctionModule.h"
MB_DrawEquip::MB_DrawEquip()
{
    m_pSpriteIcon  = NULL;
    m_pNameCount    = NULL;
    m_pMB_DrawCardData = NULL;
    m_pAnimation = NULL;
    m_bFont = true;
    m_pNodeDrawed = NULL;
    for (int i = 0 ; i < MAX_GER_STAR; i++) {
        m_pStar[i] = NULL;
    }
}

MB_DrawEquip::~MB_DrawEquip()
{
    m_pAnimation->setAnimationCompletedCallback(NULL, NULL);
    CC_SAFE_RELEASE(m_pSpriteIcon);
    CC_SAFE_RELEASE(m_pNameCount);
    CC_SAFE_RELEASE(m_pAnimation);
    CC_SAFE_RELEASE(m_pNodeDrawed);
    for (int i = 0 ; i < MAX_GER_STAR; i++) {
        CC_SAFE_RELEASE(m_pStar[i]);
    }
}

void MB_DrawEquip::FlipFont(bool force)
{
    if(!m_bFont || force)
    {
        m_pAnimation->setAnimationCompletedCallback(NULL, NULL);
        m_pAnimation->runAnimationsForSequenceNamed("FlipFont");
        m_bFont = true;
        onResetWnd();
    }
}

void MB_DrawEquip::FlipBack(bool force)
{
    if(m_bFont || force)
    {
        m_pAnimation->setAnimationCompletedCallback(NULL, NULL);
        m_pAnimation->runAnimationsForSequenceNamed("FlipBack");
        m_bFont = false;
        onResetWnd();
    }
}

void MB_DrawEquip::FlipFontCallBack()
{
    FlipFont(true);
}
void MB_DrawEquip::FlipBackFont()
{
    FlipBack(true);
    m_pAnimation->setAnimationCompletedCallback(this, callfunc_selector(MB_DrawEquip::FlipFontCallBack));
}

bool MB_DrawEquip::getisDraw()
{
    return m_pMB_DrawCardData?m_pMB_DrawCardData->getisDraw():false;
}


MB_DrawEquip* MB_DrawEquip::create(MB_DrawCardData* data)
{
    MB_DrawEquip* layer = new MB_DrawEquip();
    if (layer != NULL && layer->init(data)) {
        layer->autorelease();
        return layer;
    }
    delete layer;
    return NULL;
}

bool MB_DrawEquip::init(MB_DrawCardData* data)
{
    CCLayer::init();
    m_pMB_DrawCardData = data;
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/item_node_equipget.ccbi", this);
    this->addChild(node);
    m_pAnimation = pCCBReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pAnimation);
    CC_SAFE_DELETE(pCCBReader);
    
    onResetWnd();
    return true;
}


bool MB_DrawEquip::onAssignCCBMemberVariable(CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteIcon", CCSprite *, m_pSpriteIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNameCount", CCLabelTTF *, m_pNameCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeDrawed", CCNode *, m_pNodeDrawed);
    char star[]= "star0";
    for (int i = 0 ; i < MAX_GER_STAR; i++) {
        
        star[4] = '0' +i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this,star,CCNode *,m_pStar[i]);
    }
    
    return false;
}

cocos2d::SEL_MenuHandler MB_DrawEquip::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClicked", MB_DrawEquip::onClicked);
    return NULL;
}

void MB_DrawEquip::onClicked(CCObject*)
{
    if(m_bFont || m_pMB_DrawCardData->getisDraw())
    {
        RewardTempleteValue* templete = m_pMB_DrawCardData->convertTemplateValue();
        if(templete->getType() == 1)
        {
            MB_ResWindow* layer= MB_LayerItemDetail::createByType(templete->getValueID());
            MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
            if (pScene)
            {
                pScene->addChild(layer,Z_ORDER_Detail);
            }else{
                CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
            }
        }
        else
        {
            MB_PetTemplate* pTemplate = MB_PetMgr::getInstance()->getPetTemplateByID(m_pMB_DrawCardData->getValue());
            MB_PetData* pData = MB_PetMgr::createInstance(pTemplate);
            MB_ResWindow* layer= MB_LayerPetDetail::create(pData);
            if(layer)CCDirector::sharedDirector()->getRunningScene()->addChild(layer,Z_ORDER_OUTSHOW);
        }
    }
    else
    {
        MB_TARGET_PARENT(MB_LayerToyShopMain, ptr)
        {
            if(ptr)ptr->onChooseEquip(this->getTag());
        }
    }
}

cocos2d::extension::SEL_CCControlHandler MB_DrawEquip::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){
    
    return NULL;
}

void MB_DrawEquip::setDrawCardData(MB_DrawCardData* pData)
{
    m_pMB_DrawCardData = pData;
}

void MB_DrawEquip::onResetWnd(void)
{
    m_pNameCount->setString("");
    if(m_bFont)
    {
        if(m_pMB_DrawCardData)
        {
            RewardTempleteValue* templete = m_pMB_DrawCardData->convertTemplateValue();
            if(templete == NULL)return;
            if(templete->getType() == 1)
            {
                MB_ItemTemplate* pTemplate = MB_ItemMgr::getInstance()->getItemTemplateByID(templete->getValueID());
                if (pTemplate)
                    NSGameHelper::setItemIconDetailByTid(templete->getValueID(), 0, m_pSpriteIcon,m_pNameCount,NULL);
                
                for (int i = 0 ; i < MAX_GER_STAR; i++) {
                    if (i >= pTemplate->getItemStar()) {
                        m_pStar[i]->setVisible(false);
                    }
                    else
                    {
                        m_pStar[i]->setVisible(true);
                    }
                }
            }
            else
            {
                MB_PetTemplate* pTemplate = MB_PetMgr::getInstance()->getPetTemplateByID(m_pMB_DrawCardData->getValue());
                if (pTemplate)
                    NSGameHelper::setMonsterIconDetailByTid(templete->getValueID(), 0, m_pSpriteIcon,m_pNameCount,NULL);
            }
            m_pNameCount->setString(CCString::createWithFormat("%s*%d",m_pNameCount->getString(),templete->getNumber())->getCString());
        }
    }
    else
    {
        QUERY_FUNCTION_BEGIN(MB_ToyShopInterface, kFunctionToy, pInterface);
        if(pInterface)
        {
            m_pNameCount->setString(CCString::createWithFormat("%s*%d",ItemMgr->getItemTemplateByID(30002)->getItemName(),pInterface->getNeedItemNums())->getCString());
        }
        else
        {
            m_pNameCount->setString("");
        }
        QUERY_FUNCTION_END;
    }
    
    if(m_pNodeDrawed && m_pMB_DrawCardData)m_pNodeDrawed->setVisible(m_pMB_DrawCardData->getisDraw());
}
