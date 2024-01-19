//
//  MB_NodePicIcon.cpp
//  ProjectMB
//
//  Created by yuanwugang on 14-11-23.
//
//

#include "MB_NodePicIcon.h"
#include "MB_LayerPicDeploy.h"
#include "MB_LayerPetDetail.h"
#include "MB_LayerItemDetail.h"
#include "../Common/GameLib/GameHelper/CCGameHelper.h"
MB_NodePicIcon::MB_NodePicIcon()
{
    m_pNodeSize = NULL;
    m_pSpriteItemIcon = NULL;
    m_pTTFName = NULL;
    m_nType = 0;
    m_pAnimation = NULL;
    m_pSpriteItemKuang = NULL;
}
MB_NodePicIcon::~MB_NodePicIcon()
{
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(m_pSpriteItemIcon);
    CC_SAFE_RELEASE_NULL(m_pTTFName);
    CC_SAFE_RELEASE_NULL(m_pAnimation);
    CC_SAFE_RELEASE_NULL(m_pSpriteItemKuang);
    
    
}

void MB_NodePicIcon::setData(MB_PicShow* data,int type)
{
    m_nType = type;
    
    if (m_nType == kTypePetPic)
    {
        MB_PetTemplate* petTemplete = MB_PetMgr::getInstance()->getPetTemplateByID(data->getID());
        //设置icon
        CCTexture2D *textrue = CCTextureCache::sharedTextureCache()->addImage(petTemplete->getPetFace(data->getShape()));
        if(textrue !=NULL){
            CCSpriteFrame *frame  =CCSpriteFrame::createWithTexture(textrue,CCRect(0,0,textrue->getContentSize().width,textrue->getContentSize().height));
            m_pSpriteItemIcon->setDisplayFrame(frame);
        }
                   CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("global.plist"); m_pSpriteItemKuang->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("slot_type_%d.png",petTemplete->getPetKingdom())->getCString()));
        NSGameHelper::creatMaskSprite(m_pSpriteItemIcon);
        
        //设置是否激活
        if(!data->getActivata())
        {
            NSGameHelper::setColorGray(m_pSpriteItemKuang,true);
            NSGameHelper::setColorGray(m_pSpriteItemIcon,true);
        }
        

        if (m_pTTFName) {
            //设置名字
            m_pTTFName->setString(petTemplete->getPetName(data->getShape()));
        }
        //设置button
        this->setTag(petTemplete->getPetTypeID()*10+data->getShape());
    }
    else if(m_nType == kTypeEquipPic)
    {
        MB_ItemTemplate* itemTemplete = MB_ItemMgr::getInstance()->getItemTemplateByID(data->getID());
        
        //设置icon
        CCTexture2D *textrue = CCTextureCache::sharedTextureCache()->addImage(itemTemplete->getItemIcon());
        if(textrue !=NULL){
            
            CCSpriteFrame *frame  =CCSpriteFrame::createWithTexture(textrue,CCRect(0,0,textrue->getContentSize().width,textrue->getContentSize().height));
            m_pSpriteItemIcon->setDisplayFrame(frame);
            m_pSpriteItemIcon->setScale(.89772f);
            m_pSpriteItemKuang->setVisible(false);
        }
        //设置是否激活
        if(!data->getActivata())
        {
            NSGameHelper::setColorGray(m_pSpriteItemIcon,true);
        }
        
        if (m_pTTFName) {
            //设置名字
            m_pTTFName->setString(itemTemplete->getItemName());
        }
        //设置button
        this->setTag(itemTemplete->getItemID());
    }
}
void MB_NodePicIcon::onExit(){
    
    MB_ResWindow::onExit();
    if (m_pAnimation) {
        m_pAnimation->setAnimationCompletedCallback(NULL, NULL);
    }
}
MB_NodePicIcon* MB_NodePicIcon::create2(){
    MB_NodePicIcon *ptr = new MB_NodePicIcon();
    if (ptr && ptr->init2()){
        
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}


bool MB_NodePicIcon::init()
{
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode *pNode = pCCBReader->readNodeGraphFromFile("res/main_node_handbook_icon.ccbi", this);
    addChild(pNode);
    m_pAnimation =pCCBReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pAnimation);
    
    return true;
}

bool MB_NodePicIcon::init2()
{
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode *pNode = pCCBReader->readNodeGraphFromFile("res/main_node_handbook_icon2.ccbi", this);
    addChild(pNode);
    return true;
}
bool MB_NodePicIcon::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize",CCNode*,m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpriteItemIcon",CCSprite*,m_pSpriteItemIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFName",CCLabelTTF*,m_pTTFName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpriteItemKuang",CCSprite*,m_pSpriteItemKuang);
    
    if (pTarget == this && strcmp(pMemberVariableName, "scrollmenu") == 0) {
        CCMenu* menu = dynamic_cast<CCMenu*>(pNode);
        if (menu != NULL) {
//            menu->setSwallowsTouches(false);
            menu->setTouchPriority(99);
//            menu->setTouchEnabled(false);
        }
        return true;
    }
    
    return false;
    
}

SEL_MenuHandler MB_NodePicIcon::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onDetailClicked",MB_NodePicIcon::onDetailClicked);
    return NULL;
}


SEL_CCControlHandler MB_NodePicIcon::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

void MB_NodePicIcon::runAnimation()
{
    m_pAnimation->runAnimationsForSequenceNamed("texiao");
}
void MB_NodePicIcon::onDetailClicked(CCObject* pSender)
{
    if (m_nType == kTypePetPic)
    {
        int tag = this->getTag();
        MB_LayerPetDetail* layer = NULL;
        MB_PetTemplate* pTemp = MB_PetMgr::getInstance()->getPetTemplateByID(tag/10);
        if (pTemp)
        {
            MB_PetData* pData = MB_PetMgr::createInstance(pTemp,(tag%10-1)*10);
            layer =  MB_LayerPetDetail::create(pData);
            layer->setAllBtnShowFalse();
            if (layer)
            {
                layer->setChangeState(true);
                CCDirector::sharedDirector()->getRunningScene()->addChild(layer,Z_ORDER_OUTSHOW);
            }
            
        }
        
    }
    else if (m_nType == kTypeEquipPic)
        
    {
        MB_ResWindow* layer = MB_LayerItemDetail::createByType(this->getTag());
        MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
        if (pScene)
        {
            pScene->addChild(layer,Z_ORDER_Detail);
        }else{
            CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
        }
    }
}

CCSize MB_NodePicIcon::getNodeSize()
{
    static CCSize sz = CCSizeMake(-1, 0);
    
    if (sz.width < 0 )
    {
        MB_NodePicIcon* pNode = MB_NodePicIcon::create();
        sz = pNode->m_pNodeSize->getContentSize();
        CC_SAFE_RELEASE_NULL(pNode);
    }
    return sz;
}

