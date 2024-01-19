
#include "MB_NodeItem.h"
#include "MB_LayerItemDetail.h"
MB_NodeItem::MB_NodeItem ()
{
    isTopZorder = false;
    m_pNodeStar = NULL;
    m_pItem_card = NULL;
    m_pRootNodeLevel = NULL;
    m_pLabelLevel = NULL;
    m_pLabelNum = NULL;
    m_pRootNodeNum = NULL;
    m_pLabelName = NULL;
    m_nItemId = 0;
    m_nItemType = 0;
    m_pNodeSelect = NULL;
    m_pDelegate = NULL;
    m_pSpriteDebris = NULL;
    m_pItemMenu = NULL;
    m_pEquipedStr = NULL;
    for (int i = 0; i < MAX_GER_STAR; i++) {
        m_pStar[i] = NULL;
    }
}

MB_NodeItem::~MB_NodeItem (){
    CC_SAFE_RELEASE_NULL(m_pEquipedStr);
    CC_SAFE_RELEASE_NULL(m_pNodeStar);
    CC_SAFE_RELEASE_NULL(m_pRootNodeLevel);
    CC_SAFE_RELEASE_NULL(m_pItem_card);
    CC_SAFE_RELEASE_NULL(m_pLabelLevel);
    CC_SAFE_RELEASE_NULL(m_pLabelNum);
    CC_SAFE_RELEASE_NULL(m_pRootNodeNum);
    CC_SAFE_RELEASE_NULL(m_pNodeSelect);
    CC_SAFE_RELEASE_NULL(m_pSpriteDebris);
    CC_SAFE_RELEASE_NULL(m_pItemMenu);
    CC_SAFE_RELEASE_NULL(m_pLabelName);
    for (int i = 0; i < MAX_GER_STAR; i++) {
        CC_SAFE_RELEASE_NULL(m_pStar[i]);
    }
}

bool MB_NodeItem::init(uint64_t itemid)
{
    if (!CCLayer::init())return false;
    m_nItemId = itemid;
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/item_node_icon.ccbi", this);
    this->addChild(node);
    if(kNINWNONE == m_eNowWindow)
    {
        m_pItemMenu->removeFromParent();
    }
    CC_SAFE_DELETE(pCCBReader);
    m_pItemMenu->setSwallowsTouches(false);
    if(kNINWNONE == m_eNowWindow)
    {
        m_pItemMenu->removeFromParent();
    }
    if(itemid == 0)
    {
        m_pRootNodeNum->setVisible(false);
        m_pRootNodeLevel->setVisible(false);
        m_pItem_card->setVisible(false);
        return true;
    }
    
     
    MB_ItemData*  data = MB_ItemMgr::getInstance()->getItemDataByUID(itemid);
    if (data == NULL)
    {
        m_pRootNodeNum->setVisible(false);
        m_pRootNodeLevel->setVisible(false);
        return true;
    }
    
    MB_ItemTemplate *itdata = MB_ItemMgr::getInstance()->getItemTemplateByID(data->getItemID());
    if (itdata == NULL)
    {
        m_pRootNodeNum->setVisible(false);
        m_pRootNodeLevel->setVisible(false);
        return true;
    }
    
//    kWEAPON = 1,                                    //兵器
//    kARMOR = 2,										//战甲
//    kHORSE = 3,										//坐骑
//    kITEM_WING = 33,                                //翅膀
//    kITEM_HEADWEAR = 34,                            //头饰
//    kITEM_TOTEM = 35,                               //图腾
//    kITEM_RUNESTONE = 36,                           //符石
    
    char databuf[64];
    bool bShowLvType = false;
    if(itdata->getItemType() == kWEAPON || itdata->getItemType()==kARMOR
       ||itdata->getItemType() == kITEM_HEADWEAR || itdata->getItemType() == kITEM_WING
       ||itdata->getItemType() == kITEM_TOTEM || itdata->getItemType() == kITEM_RUNESTONE)
    {
        bShowLvType = true;
    }
    if( data->getItemLevel() >1 || (bShowLvType && data->getItemLevel() == 1 ))
    {        
        sprintf(databuf , "Lv.%d",data->getItemLevel());
        m_pLabelLevel->setString(databuf);
        m_pRootNodeLevel->setVisible(true);
    }
    else
    {
        m_pRootNodeLevel->setVisible(false);
    }
 
    if (bShowLvType || data->getItemNumber() <= 0 )
    {
        m_pRootNodeNum->setVisible(false);
    }else
    {
        sprintf(databuf,"%d",data->getItemNumber());
        m_pLabelNum->setString(databuf);
        m_pRootNodeNum->setVisible(true);
    }

    CCTexture2D *textrue = CCTextureCache::sharedTextureCache()->addImage(itdata->getItemIcon());
    if(textrue !=NULL)
    {
        CCSpriteFrame * frame  =CCSpriteFrame::createWithTexture(textrue,CCRect(0,0,textrue->getContentSize().width,textrue->getContentSize().height));
        m_pItem_card->setDisplayFrame(frame);
    }
    
    m_pLabelName->setVisible(true);
    if(bShowLvType)
    {
        MB_ItemMgr::getInstance()->realName(databuf, m_nItemId);
        m_pLabelName->setString(databuf);
    }else
    {
        const char* pName = itdata->getItemName();
        sprintf(databuf, "%s",pName);
        m_pLabelName->setString(databuf);
    }
    
    //星级
    int normalStar = itdata->getItemStar();
    for (int i = 0; i < MAX_ITEM_STAR; i++) {
        if (i < normalStar) {
            m_pStar[i]->setVisible(true);
        }
        else
        {
            m_pStar[i]->setVisible(false);
        }
    }
    return true;
}


bool MB_NodeItem::init(uint16_t itemtype)
{    
    m_nItemType = itemtype;
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/item_node_icon.ccbi", this);
    this->addChild(node);
    if(kNINWNONE == m_eNowWindow)
    {
        m_pItemMenu->removeFromParent();
    }
    m_pRootNodeLevel->setVisible(false);
    m_pRootNodeNum->setVisible(false);
    CC_SAFE_DELETE(pCCBReader);
    m_pItemMenu->setSwallowsTouches(false);
    MB_ItemTemplate *itdata = MB_ItemMgr::getInstance()->getItemTemplateByID(itemtype);
    if (itdata)
    {
        NSGameHelper::setItemIconDetailByTid(itemtype, 0, m_pItem_card,m_pLabelName,NULL,false);
        MB_ItemTemplate *templete = MB_ItemMgr::getInstance()->getItemTemplateByID(itemtype);
        if(m_pSpriteDebris && templete)m_pSpriteDebris->setVisible(templete->getIsDebris());
        //星级
        int normalStar = itdata->getItemStar();
        for (int i = 0; i < MAX_ITEM_STAR; i++) {
            if (i < normalStar) {
                m_pStar[i]->setVisible(true);
            }
            else
            {
                m_pStar[i]->setVisible(false);
            }
        }
        
        bool bIsEquip = false;
        bIsEquip = itdata->getItemType() == kWEAPON || itdata->getItemType()==kARMOR
        ||itdata->getItemType() == kITEM_HEADWEAR || itdata->getItemType() == kITEM_WING
        ||itdata->getItemType() == kITEM_TOTEM || itdata->getItemType() == kITEM_RUNESTONE;
        m_pRootNodeLevel->setVisible(bIsEquip);
    }
    

    return true;
}
MB_NodeItem * MB_NodeItem::create(const char *iamgeName,uint8_t star,NODEITEMNOWWINDOW nowWindow){
    MB_NodeItem * ptr = new MB_NodeItem();
    ptr->m_eNowWindow = nowWindow;
    if (ptr && ptr->init(iamgeName,star)) {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;

}
bool MB_NodeItem::init(const char *iamgeName,uint8_t star){

    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/item_node_icon.ccbi", this);
    this->addChild(node);
    if(kNINWNONE == m_eNowWindow)
    {
        m_pItemMenu->removeFromParent();
    }
    CC_SAFE_DELETE(pCCBReader);
    m_pRootNodeLevel->setVisible(false);
    m_pRootNodeNum->setVisible(false);
    m_pItemMenu->setSwallowsTouches(false);

    
    m_pRootNodeNum->setVisible(false);

    NSGameHelper::creatMaskSprite(m_pItem_card);
    m_pSpriteDebris->setVisible(false);
    
    //星级
    for (int i = 0; i < MAX_ITEM_STAR; i++) {
        if (i < star) {
            m_pStar[i]->setVisible(true);
        }
        else
        {
            m_pStar[i]->setVisible(false);
        }
    }
    return true;
}

const ccColor3B & MB_NodeItem::getNodeColor(){

    CCLog("旧的获取颜色方法 MB_NodeItem::getNodeColor()");
    static ccColor3B ccgray = ccc3(68,68,68);
    return  ccgray;//
}
void MB_NodeItem::setNum(int num)
{
    char databuf[60];
    sprintf(databuf,"%d",num);
    m_pLabelNum->setString(databuf);
    m_pRootNodeNum->setVisible(true);
//    const char* pName = m_pLabelName->getString();
//    sprintf(databuf, "%s*%d",pName,num);
//    m_pLabelName->setString(databuf);
}

cocos2d::SEL_MenuHandler MB_NodeItem::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClicked",MB_NodeItem::onClicked);
    return NULL;
}

void MB_NodeItem::onClicked(CCObject*)
{
    TutorialTriggerComplete
    if (m_pDelegate) {
        m_pDelegate->onClicked(this);
    }else
    {
        MB_ResWindow* layer;
        if (m_nItemId==0) {
            layer = MB_LayerItemDetail::createByType(m_nItemType,m_eNowWindow);
        }else
        {
            layer = MB_LayerItemDetail::create(m_nItemId,m_eNowWindow);
        }
        if (isTopZorder) {
            CCDirector::sharedDirector()->getRunningScene()->addChild(layer,Z_ORDER_Detail+999);
        }else if (global_sceneGame!=NULL) {
            CCDirector::sharedDirector()->getRunningScene()->addChild(layer,Z_ORDER_Detail);
        }else
        {
            MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
            if (pScene)
            {
                pScene->addChild(layer,Z_ORDER_Detail);
            }
        }

    }
}
cocos2d::extension::SEL_CCControlHandler MB_NodeItem::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

    return NULL;
}

bool MB_NodeItem::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ItemIcon", CCSprite *,m_pItem_card);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelLevel", CCLabelBMFont *,m_pLabelLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelNum", CCLabelBMFont *,m_pLabelNum);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeLevel", CCNode *,m_pNodeLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pRootNodeNum", CCNode *,m_pRootNodeNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pRootNodeLevel", CCNode *,m_pRootNodeLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeStar", CCNode *,m_pNodeStar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pEquipedStr", CCNode *,m_pEquipedStr);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeSelect", CCNode*, m_pNodeSelect);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteDebris", CCNode*, m_pSpriteDebris);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "itemMenu", CCMenu*, m_pItemMenu)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelName", CCLabelTTF*, m_pLabelName);
    for (int i = 0; i < MAX_GER_STAR; i++) {
        char starstr[] = "star0";
        starstr[4] = i + '0';
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, starstr, CCSprite *, m_pStar[i]);
    }
    return false ;
}

void MB_NodeItem::setSelected(bool b)
{
    m_pNodeSelect->setVisible(b);
}

void MB_NodeItem::setLevelNum(int level)
{
    char databuf[64] = {0};
    sprintf(databuf , "Lv.%d",level);
    m_pLabelLevel->setString(databuf);
    m_pRootNodeLevel->setVisible(true);
}
void MB_NodeItem::showLevel(bool b)
{
    m_pRootNodeLevel->setVisible(false);
}
void MB_NodeItem::showNameCount(bool b)
{
    m_pLabelName->setVisible(b);
}

MB_NodeItem * MB_NodeItem::create(uint64_t itemid,NODEITEMNOWWINDOW nowWindow)
{
    MB_NodeItem * ptr = new MB_NodeItem();
    ptr->m_eNowWindow = nowWindow;
    if (ptr && ptr->init(itemid)) {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;

}
MB_NodeItem * MB_NodeItem::create(uint16_t itemType,NODEITEMNOWWINDOW nowWindow){
    
    MB_NodeItem * ptr = new MB_NodeItem();
    ptr->m_eNowWindow = nowWindow;
    if (ptr && ptr->init(itemType))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;

}
bool MB_NodeItem::init(MB_ItemData *data){
    m_nItemId = data->getItemUID();
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/item_node_icon.ccbi", this);
    this->addChild(node);
    if(kNINWNONE == m_eNowWindow)
    {
        m_pItemMenu->removeFromParent();
    }
    CC_SAFE_DELETE(pCCBReader);
    m_pItemMenu->setSwallowsTouches(false);
    
    m_pRootNodeLevel->setVisible(false);
    m_pRootNodeNum->setVisible(false);

    
    MB_ItemTemplate *itdata = MB_ItemMgr::getInstance()->getItemTemplateByID(data->getItemID());
    if (itdata == NULL) {
        m_pRootNodeLevel->setVisible(false);
        return true;
    }    
    char databuf[64];
    bool bIsEquip = false;
    bIsEquip = itdata->getItemType() == kWEAPON || itdata->getItemType()==kARMOR
                ||itdata->getItemType() == kITEM_HEADWEAR || itdata->getItemType() == kITEM_WING
                ||itdata->getItemType() == kITEM_TOTEM || itdata->getItemType() == kITEM_RUNESTONE;
    
    if( data->getItemLevel() >1 || (bIsEquip && data->getItemLevel() == 1 ))
    {
        sprintf(databuf , "Lv.%d",data->getItemLevel());
        m_pLabelLevel->setString(databuf);
        m_pRootNodeLevel->setVisible(true);
    }
    else
    {
        m_pRootNodeLevel->setVisible(false);
    }
    

    if(bIsEquip)
    {
        m_pRootNodeNum->setVisible(false);
    }else {
        
        sprintf(databuf,"%d",data->getItemNumber());
        m_pLabelNum->setString(databuf);
        m_pRootNodeNum->setVisible(true);
    }
    
    CCTexture2D *textrue = CCTextureCache::sharedTextureCache()->addImage(itdata->getItemIcon());
    if(textrue !=NULL)
    {
        CCSpriteFrame * frame  =CCSpriteFrame::createWithTexture(textrue,CCRect(0,0,textrue->getContentSize().width,textrue->getContentSize().height));
        m_pItem_card->setDisplayFrame(frame);
    }
    
    //星级
    int normalStar = itdata->getItemStar();
    for (int i = 0; i < MAX_ITEM_STAR; i++) {
        if (i < normalStar) {
            m_pStar[i]->setVisible(true);
        }
        else
        {
            m_pStar[i]->setVisible(false);
        }
    }
    return true;
}

void MB_NodeItem::setOnClickEnable(bool b)
{
    m_pItemMenu->setEnabled(b);
}

MB_NodeItem * MB_NodeItem::create(MB_ItemData *data,NODEITEMNOWWINDOW nowWindow){

    MB_NodeItem * ptr = new MB_NodeItem();
    ptr->m_eNowWindow = nowWindow;
    if (ptr && ptr->init(data))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;

}
void MB_NodeItem::showNameStar(bool b)
{
    m_pNodeStar->setVisible(b);
}
void MB_NodeItem::setIsEquiped()
{
    if (m_nItemId!=0) {
        MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_nItemId);
        if (itemData->getItemPetID() != 0)
        {
            m_pEquipedStr->setVisible(true);
        }
    }
}
