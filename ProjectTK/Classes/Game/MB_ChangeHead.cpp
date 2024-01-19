//
//  MB_ChangeHead.cpp
//  ProjectPM
//
//  Created by crimoon on 14-4-9.
//
//

#include "MB_ChangeHead.h"
#include "MB_LayerRoleDetail.h"

MB_ChangeHead::MB_ChangeHead()
{
    m_pContainer = NULL;
    m_pHead = NULL;
    m_pScrollView = NULL;
    isReset = false;
    //cell控件
    m_pItemIcon = NULL;
    m_pIconFrame = NULL;
    m_pDetailButton = NULL;
    m_pIconArray = new CCArray();
    SOCKET_MSG_REGIST(SC_ROLE_CHANGE_HEAD, MB_ChangeHead);
}
MB_ChangeHead::~MB_ChangeHead()
{
    CC_SAFE_RELEASE_NULL(m_pIconArray);
    CC_SAFE_RELEASE_NULL(m_pContainer);
    CC_SAFE_RELEASE_NULL(m_pHead);
    
    SOCKET_MSG_UNREGIST(SC_ROLE_CHANGE_HEAD);
}
MB_ChangeHead* MB_ChangeHead::create()
{
    MB_ChangeHead* ptr = new MB_ChangeHead();
    if (ptr && ptr->init())
    {
        ptr->autorelease();
        return ptr;
    }
    else
    {
        delete ptr;
        return NULL;
    }
}
bool MB_ChangeHead::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->addChild(NSGameHelper::createDisableTouchLayer());
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode *pScene = pCCBReader->readNodeGraphFromFile("res/role_layer_headportrait.ccbi", this);
    this->addChild(pScene);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    //列表
    //清理scrollview
    if (m_pScrollView != NULL)
    {
        m_pScrollView->removeFromParent();
        m_pScrollView = NULL;
    }
    
    //NSGameHelper::adjustScrollNode(m_pContainer);
    m_pScrollView = CCScrollView::create(m_pContainer->getContentSize());
    m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
    m_pScrollView->setAnchorPoint(CCPointZero);
    
    //獲取cell大小
    sortArray();
    CCArray* pArrayShow = NULL;   //激活卡牌組
    
    //獲取激活卡牌
    pArrayShow = MB_DataShowPic::getInstance()->getServerMB_PetTemplateArray();
    
    if (!m_pIconArray)
    {
        return true;
    }
    
    
    MB_PicShow* pPicShow = NULL;
    MB_PetTemplate* petTemplete = NULL;
    
    //獲取所有卡牌數量
    int nCount = m_pIconArray->count();
    //  CCLOG("总數%d jihuo量%d",nCount,pArrayShow->count());
    
    //計算显示的卡牌數量，用於設置ScrollView大小
    int nShowCount = 0;
    for(int i = 0;i < nCount;i++)
    {
        //是否激活
        bool bIsActivata = false;
        pPicShow = (MB_PicShow*)m_pIconArray->objectAtIndex(i);
        for (int j = 0; j < pArrayShow->count(); j++)
        {
            MB_PicShow* data = (MB_PicShow*)pArrayShow->objectAtIndex(j);
            if (data->getID() == pPicShow->getID() && data->getShape() == pPicShow->getShape())
            {
                bIsActivata = true;
                break;
            }
        }
        if (!bIsActivata) //沒激活不显示
        {
            continue;
        }
        nShowCount++;
    }
    pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/role_node_headportrait.ccbi", this);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    CCSize containSize = CCSizeMake(m_pContainer->getContentSize().width, m_cellSize.height * (nShowCount/5 + (nShowCount%5 != 0)));
    m_pScrollView->setContentSize(containSize);
    m_pScrollView->setContentOffset(CCPointMake(0, m_pContainer->getContentSize().height - containSize.height));
    
    int nTotal = 0;
    for (int i = 0; i < nCount; i++)
    {
        pPicShow = (MB_PicShow*)m_pIconArray->objectAtIndex(i);
        
        //是否激活
        bool bIsActivata = false;
        for (int j = 0; j < pArrayShow->count(); j++)
        {
            MB_PicShow* data = (MB_PicShow*)pArrayShow->objectAtIndex(j);
            if (data->getID() == pPicShow->getID() && data->getShape() == pPicShow->getShape())
            {
                bIsActivata = true;
                break;
            }
        }
        
        //如果沒激活  则不显示該卡片
        if (!bIsActivata)
        {
            continue;
        }
        
        petTemplete = MB_PetMgr::getInstance()->getPetTemplateByID(pPicShow->getID());
        if (petTemplete == NULL)
        {
            MB_LOG("unkown petTemplete: %d", pPicShow->getID());
            continue;
        }
        
        pCCBReader = new CCBReader(ccNodeLoaderLibrary);
        CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/role_node_headportrait.ccbi", this);
        CC_SAFE_RELEASE_NULL(pCCBReader);
        //設置icon
        CCTexture2D *textrue = CCTextureCache::sharedTextureCache()->addImage(petTemplete->getPetFace(pPicShow->getShape()));
        if(textrue !=NULL){
            CCSpriteFrame *frame  =CCSpriteFrame::createWithTexture(textrue,CCRect(0,0,textrue->getContentSize().width,textrue->getContentSize().height));
            m_pItemIcon->setDisplayFrame(frame);
        }
        m_pIconFrame->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("slot_type_%d.png",petTemplete->getPetKingdom())->getCString()));
        //        NSGameHelper::creatMaskSprite(m_pItemIcon);
        //設置button
        m_pDetailButton->setTag(petTemplete->getPetTypeID()+pPicShow->getShape()*SHAPE_BASE);
        m_pDetailButton->addTargetWithActionForControlEvents(this, cccontrol_selector(MB_ChangeHead::EventTouchDown), CCControlEventTouchDown);
        m_pDetailButton->addTargetWithActionForControlEvents(this, cccontrol_selector(MB_ChangeHead::EventTouchDragEnter), CCControlEventTouchDragInside);
        //設置node坐标
        pNode->setPosition((1.2f + (nTotal %5)) * m_cellSize.width, containSize.height - (nTotal/5 +.5f) * m_cellSize.height);
        nTotal++;
        m_pScrollView->addChild(pNode);

    }
    m_pScrollView->setSwaller(false);
    m_pContainer->addChild(m_pScrollView);
    
    onResetWnd();
    return true;
}
void MB_ChangeHead::EventTouchDown(CCObject * sender, CCControlEvent controlEvent){
    isChangeIcon = true;
}
void MB_ChangeHead::EventTouchDragEnter(CCObject * sender, CCControlEvent controlEvent){
    isChangeIcon = false;
}
void MB_ChangeHead::onDetailClicked(cocos2d::CCObject *sender)
{
    if (!isChangeIcon) {
        return;
    }
    int tag = ((CCMenuItemImage*)sender)->getTag();
    if(tag != MB_RoleData::getInstance()->getHead())
    {
        sendrole_change_head(tag);
    }
}
void MB_ChangeHead::onResetWnd()
{
    //頭像
    uint32_t HeadID = MB_RoleData::getInstance()->getHead();
    MB_TitleTemplete *title = MB_TitleMgr::getInstance()->getTitleByID(MB_RoleData::getInstance()->getTitle());
    CCTexture2D *textrue;
    if (HeadID == 0)
    {
        textrue  =  CCTextureCache::sharedTextureCache()->addImage(MB_RoleData::getInstance()->getSex()==1?title->getMCardFrame(): title->getFCardFrame());
    }
    else
    {
        uint16_t tID = HeadID%SHAPE_BASE;
        uint16_t shape = HeadID/SHAPE_BASE;
        MB_PetTemplate* petTemplete = MB_PetMgr::getInstance()->getPetTemplateByID(tID);
        textrue = CCTextureCache::sharedTextureCache()->addImage(petTemplete->getPetFace(shape));
    }
    
    if (textrue != NULL) {
        
        m_pHead->setDisplayFrame(CCSpriteFrame::createWithTexture(textrue, CCRectMake(0,0,textrue->getContentSize().width,textrue->getContentSize().height)));
        
    }else {
        
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(MB_RoleData::getInstance()->getSex()==1?title->getMCardFrame(): title->getFCardFrame());
        if (frame != NULL) {
            
            m_pHead->setDisplayFrame(frame);
        }
    }
    NSGameHelper::creatMaskSprite(m_pHead);
}
bool MB_ChangeHead::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    if (pTarget == this && strcmp(pMemberVariableName, "cellSize") == 0) {
        m_cellSize = pNode->getContentSize();
        return true;
    }
    if (pTarget == this && strcmp(pMemberVariableName, "ItemIcon") == 0) {
        m_pItemIcon = (CCSprite*)pNode;
        return true;
    }
    if (pTarget == this && strcmp(pMemberVariableName, "IconFrame") == 0) {
        m_pIconFrame = (CCSprite*)pNode;
        return true;
    }
    if (pTarget == this && strcmp(pMemberVariableName, "scrollmenu") == 0) {
        m_pDetailButton = dynamic_cast<CCControlButton*>(pNode);
        if (m_pDetailButton != NULL) {
            m_pDetailButton->setSwallowsTouches(false);
            //            m_pDetailButton->setTouchPriority(1);
        }
        return true;
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ListPic", CCNode *, m_pContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "head", CCSprite *, m_pHead);
    return true;
}
SEL_MenuHandler MB_ChangeHead::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBreakClicked", MB_ChangeHead::onBreakClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onDefClicked", MB_ChangeHead::onDefClicked);
    return NULL;
}
SEL_CCControlHandler MB_ChangeHead::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onDetailClicked", MB_ChangeHead::onDetailClicked);
    return NULL;
}

void MB_ChangeHead::onBreakClicked(CCObject *)
{
    if (isReset) {
        MB_LayerRoleDetail* lrd = (MB_LayerRoleDetail*)getParent();
        lrd->resetCard();
    }
    removeFromParent();
}

void MB_ChangeHead::onDefClicked(CCObject *)
{
    int nHead = MB_RoleData::getInstance()->getHead();
    if(nHead != 0)sendrole_change_head(0);
}



void MB_ChangeHead::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    
    //將socket數据读取到序列化結构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议號
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg) {
        case  SC_ROLE_CHANGE_HEAD:
            isReset = true;
            recvrole_change_head(recvPacket);
            break;
        default:
            break;
    }
    
    
}

bool MB_ChangeHead::sendrole_change_head(uint32_t headID)
{
    SOCKET_REQUEST_START(CS_ROLE_CHANGE_HEAD);
    packet->writeU32(headID);
    SOCKET_REQUEST_END(SC_ROLE_CHANGE_HEAD, MB_ChangeHead::onMsgRecv);
    return true;
}

bool MB_ChangeHead::recvrole_change_head(MB_MsgBuffer *recvPacket)
{
    uint8_t data8 = 0;
    uint32_t data32 = 0;
    recvPacket->readU8(&data8);
    recvPacket->readU32(&data32);
    if (data8 == 1)//換頭像成功
    {
        MB_RoleData::getInstance()->setHead(data32);
        onResetWnd();
    }
    else if(data8 == 2)//頭像不存在
    {
        MB_Message::sharedMB_Message()->showMessage("头像不存在");
    }
    else if(data8 == 3)//頭像低於4星
    {
        MB_Message::sharedMB_Message()->showMessage("请选择4星以上精灵头像");
    }
    else
    {
        MB_Message::sharedMB_Message()->showMessage("未知错误");
    }
    return true;
}



void MB_ChangeHead::sortArray()
{
    CCArray* pArrayAllPet = NULL; //所有卡牌
    //獲取所有卡牌列表
    pArrayAllPet = MB_DataShowPic::getInstance()->getClientMB_PetTemplateArray();
    MB_PicShow* pPicShow = NULL;
    for (int j = 3; j > 0; j--)
    {
        for (int i = 0; i <  pArrayAllPet->count(); i++)
        {
            pPicShow = (MB_PicShow*)pArrayAllPet->objectAtIndex(i);
            MB_PetTemplate* temp = MB_PetMgr::getInstance()->getPetTemplateByID(pPicShow->getID());
            if (temp->getPetStar() < 4)
            {
                //4星以下屏蔽
                break;
            }
            if (pPicShow->getShape() == j) {
                m_pIconArray->addObject(pPicShow);
            }
        }
    }
    
    
}
