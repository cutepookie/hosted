
#include "MB_LayerItemUnionUnit.h"
#include "MB_LayerItemDetail.h"
MB_LayerItemUnionUnit::MB_LayerItemUnionUnit(){
    
    m_pNodeSize = NULL;
    m_pItemName = NULL;
    m_pNum = NULL;
    for (int i = 0; i < MAX_ITEM_STAR; i++) {
    
        m_pStar[i] = NULL;
    }
    m_pNodeIcon = NULL;
    m_pNodeEnough = NULL;
    m_pData = NULL;
    m_pPieceNeed = NULL;
}
MB_LayerItemUnionUnit::~MB_LayerItemUnionUnit(){

   CC_SAFE_RELEASE(m_pNodeSize);
   CC_SAFE_RELEASE(m_pItemName);
   CC_SAFE_RELEASE(m_pNum);
    for (int i = 0; i < MAX_ITEM_STAR; i++) {
        
           CC_SAFE_RELEASE(m_pStar[i]);
    }
   CC_SAFE_RELEASE(m_pNodeIcon);
   CC_SAFE_RELEASE(m_pNodeEnough);
    CC_SAFE_RELEASE(m_pPieceNeed);

}
bool MB_LayerItemUnionUnit::init(){

    if( MB_ResWindow::init() == false){
        
        return false;
    }
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode * node = pCCBReader->readNodeGraphFromFile("res/obj_item_patch.ccbi", this);
    this->addChild(node);
    pCCBReader->release();
    this->setContentSize(m_pNodeSize->getContentSize());

    return true;
}
void MB_LayerItemUnionUnit::onResetWnd(void){

    MB_ResWindow::onResetWnd();
    if(m_pData == NULL){
    
        return;
    }

    m_pNodeIcon->removeAllChildren();
    MB_ItemTemplate * templete = MB_ItemMgr::getInstance()->getItemTemplateByID(m_pData->getItemID());
    
    //精灵碎片
    if(templete->getItemType() == KMATERRIAL_PATCH_GENERAL){
        
        MB_NodePet *pet = MB_NodePet::create(templete->getComposeItemID(),0,0);
        MB_PetTemplate * petTemplete = MB_PetMgr::getInstance()->getPetTemplateByID(templete->getComposeItemID());
        m_pNodeIcon->addChild(pet);
        
        m_pItemName->setString(   MB_ItemMgr::getInstance()->getItemNameByTid(m_pData->getItemID()).c_str());
        
        char databuf[50];
        sprintf(databuf, "%d/%d",m_pData->getItemNumber(),templete->getComposeNum());
        m_pNum->setString(databuf);
        for(int i = 0 ; i <  MAX_ITEM_STAR; i++ ){
        
            if(i >= petTemplete->getPetStar()){
            
                m_pStar[i]->setVisible(false);
            }
            else
            {
                m_pStar[i]->setVisible(true);
            }
        }
   
        int count = 0;
        MB_ItemTemplate * item  =  MB_ItemMgr::getInstance()->getItemTemplateByID(m_pData->getItemID());
        count += (m_pData->getItemNumber()/item->getComposeNum());
        if(count > 0){
            
            m_pNodeEnough->setVisible(true);
            m_pPieceNeed->setVisible(false);
        
        }else{
            
            int left = m_pData->getItemNumber() % item->getComposeNum();
            std::string itemName;
            int itemStar =  item->getItemStar()+1;
            if (itemStar == 3)
            {
                itemName = MB_ItemMgr::getInstance()->getItemNameByTid(COMPOS_GER3_ID);
            }
            else if (itemStar == 4)
            {
                itemName = MB_ItemMgr::getInstance()->getItemNameByTid(COMPOS_GER4_ID);
            }
            else if (itemStar == 5)
            {
                itemName = MB_ItemMgr::getInstance()->getItemNameByTid(COMPOS_GER5_ID);
            }

            
            if(left >= (item->getComposeNum() - item->getComposeCommonMaxNum())){
                
                MB_PetTemplate * itemTo = MB_PetMgr::getInstance()->getPetTemplateByID(item->getComposeItemID());
                int compos = 0;
                switch (itemTo->getPetStar()) {
                    case 3:
                        compos = MB_ItemMgr::getInstance()->getItemEntityCount(COMPOS_GER3_ID);
                        break;
                    case 4:
                        compos = MB_ItemMgr::getInstance()->getItemEntityCount(COMPOS_GER4_ID);
                        break;
                    case 5:
                        compos = MB_ItemMgr::getInstance()->getItemEntityCount(COMPOS_GER5_ID);
                        break;
                    default:
                        break;
                }
                if((left + compos) >= item->getComposeNum()){
                    
                    count += 1;
                }
            }
            if(count > 0){
            
                 m_pNodeEnough->setVisible(true);
                 m_pPieceNeed->setVisible(true);
                char pieceMsg[150];
                sprintf(pieceMsg,
                        "额外消耗%d个%s可以合成",
                        templete->getComposeNum() -left,
                        itemName.c_str());
                m_pPieceNeed->setString(pieceMsg);
                m_pPieceNeed->setVisible(true);
            
            }else {
            
                m_pNodeEnough->setVisible(false);
                char pieceMsg[150];
                sprintf(pieceMsg,
                        "最多只能使用%d个%s",
                        item->getComposeCommonMaxNum(),
                        itemName.c_str());
                m_pPieceNeed->setString(pieceMsg);
                m_pPieceNeed->setVisible(true);
            }
        
        }
        
        
        
    }
    //道具碎片
    else {
    
        MB_NodeItem *itemx=  MB_NodeItem::create(templete->getComposeItemID());
        MB_ItemTemplate * comItem = MB_ItemMgr::getInstance()->getItemTemplateByID(templete->getComposeItemID());
        m_pNodeIcon->addChild(itemx);
        m_pItemName->setString(MB_ItemMgr::getInstance()->getItemNameByTid(templete->getItemID()).c_str());

        char databuf[50];
        sprintf(databuf, "%d/%d",m_pData->getItemNumber(),templete->getComposeNum());
        m_pNum->setString(databuf);
        for(int i = 0 ; i <  MAX_ITEM_STAR; i++ ){
            
            if(i >= comItem ->getItemStar()){
                
                m_pStar[i]->setVisible(false);
            }
            else
            {
                m_pStar[i]->setVisible(true);
            }
        }
        int count = 0;
        MB_ItemTemplate * item  =  MB_ItemMgr::getInstance()->getItemTemplateByID(m_pData->getItemID());
        count += (m_pData->getItemNumber()/item->getComposeNum());
        if(count > 0){
            
            m_pNodeEnough->setVisible(true);
            m_pPieceNeed->setVisible(false);
            
        }else{
            
            int left = m_pData->getItemNumber() % item->getComposeNum();
            std::string itemName;
            int itemStar =  item->getItemStar()+1;
            if (itemStar == 3)
            {
                itemName = MB_ItemMgr::getInstance()->getItemNameByTid(COMPOS_ITEM3_ID);
            }
            else if (itemStar == 4)
            {
                itemName = MB_ItemMgr::getInstance()->getItemNameByTid(COMPOS_ITEM4_ID);
            }
            else if (itemStar == 5)
            {
                itemName = MB_ItemMgr::getInstance()->getItemNameByTid(COMPOS_ITEM5_ID);
            }
            
            
            if(left >= (item->getComposeNum() - item->getComposeCommonMaxNum())){
                
                int compos = 0;
                switch ((item->getItemStar()+1)) {
                    case 3:
                        compos = MB_ItemMgr::getInstance()->getItemEntityCount(COMPOS_ITEM3_ID);
                        break;
                    case 4:
                        compos = MB_ItemMgr::getInstance()->getItemEntityCount(COMPOS_ITEM4_ID);
                        break;
                    case 5:
                        compos = MB_ItemMgr::getInstance()->getItemEntityCount(COMPOS_ITEM5_ID);
                        break;
                    default:
                        break;
                }
                if((left + compos) >= item->getComposeNum()){
                    
                    count += 1;
                }
            }
            if(count > 0){
                
                m_pNodeEnough->setVisible(true);
                m_pPieceNeed->setVisible(true);
                char pieceMsg[150];
                sprintf(pieceMsg,
                        "额外消耗%d个%s可以合成",
                        templete->getComposeNum() -left,
                        itemName.c_str());
                m_pPieceNeed->setString(pieceMsg);
                m_pPieceNeed->setVisible(true);
                
            }else {
                
                m_pNodeEnough->setVisible(false);
                char pieceMsg[150];
                sprintf(pieceMsg,
                        "最多只能使用%d个%s",
                        item->getComposeCommonMaxNum(),
                        itemName.c_str());
                m_pPieceNeed->setString(pieceMsg);
                m_pPieceNeed->setVisible(true);
            }
            
        }
        

    }
}

cocos2d::SEL_MenuHandler MB_LayerItemUnionUnit::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCheckClick", MB_LayerItemUnionUnit::onCheckClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSoldClick", MB_LayerItemUnionUnit::onSoldClick);
    
    return   NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_LayerItemUnionUnit::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

    return  NULL;
}
bool MB_LayerItemUnionUnit::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeEnough", CCNode *, m_pNodeEnough);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "size", CCNode *, m_pNodeSize );
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pItemName", CCLabelTTF *, m_pItemName );
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_icon", CCNode *, m_pNodeIcon );
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNum", CCLabelTTF *,m_pNum );
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNeedPiece", CCLabelTTF *, m_pPieceNeed);
    char star[]= "star1";
    for (int i = 0; i < MAX_ITEM_STAR; i++) {
        
        star[4] = '1' + i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, star, CCSprite *,m_pStar[i] );
    }
    return false;
}
MB_LayerItemUnionUnit* MB_LayerItemUnionUnit::create(){
    
    MB_LayerItemUnionUnit *ptr = new MB_LayerItemUnionUnit();
    if(ptr && ptr->init()){
    
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}

void MB_LayerItemUnionUnit::setData(MB_ItemData * data){

        m_pData = data;
        onResetWnd();
}
void MB_LayerItemUnionUnit::onCheckClick(CCObject *){

    MB_ItemTemplate * templete = MB_ItemMgr::getInstance()->getItemTemplateByID(m_pData->getItemID());
    if(templete->getItemType() == KMATERRIAL_PATCH_GENERAL){
    
        MB_ItemTemplate * templete = MB_ItemMgr::getInstance()->getItemTemplateByID(m_pData->getItemID());
        MB_ResWindow *layer = MB_LayerPetDetail::create(templete->getComposeItemID());
        if(layer)CCDirector::sharedDirector()->getRunningScene()->addChild(layer,Z_ORDER_OUTSHOW);
        
    }else {
        
        MB_ItemTemplate * templete = MB_ItemMgr::getInstance()->getItemTemplateByID(m_pData->getItemID());
        MB_ResWindow *layer = MB_LayerItemDetail::createByType(templete->getComposeItemID());
        MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
        if (pScene)
        {
            pScene->addChild(layer,Z_ORDER_Detail);
        }else{
            CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
        }
    }
}
void MB_LayerItemUnionUnit::onSoldClick(CCObject *){
    
    MB_Message::sharedMB_Message()->showMessage(" ",15);
    SOCKET_REQUEST_START(CS_ITEM_COMPOUND);
    packet->writeU16(m_pData->getItemID());
    SOCKET_REQUEST_END(SC_ITEM_COMPOUND, MB_LayerItemUnionUnit::onMsgRecv);
}
