
#include "MB_LayerEqCompare.h"
#include "MB_NodePetAid.h"
#include "MB_LayerCommand.h"
#include "MB_LayerRoleInfoHeader.h"
#define LAYER_TAG 50
#define NODE_GER_TAG 50
#define MAX_SHOW_CMD 5
MB_LayerEqCompare::MB_LayerEqCompare(){
    
    m_pTeamData = new  TeamDataStruct[6];
    m_pLiArray = NULL;
    m_pZdlSpr = NULL;
    for (int i = 0 ; i < CARD_IN_GAME; i++) {
        
        
        m_pTeamData[i].m_pPet = NULL;
        m_pTeamData[i].m_pEquip1 = NULL;
        m_pTeamData[i].m_pEquip2 = NULL;
        m_pTeamData[i].m_pEquip3 = NULL;
        m_pTeamData[i].m_pTreasure1 = NULL;
        m_pTeamData[i].m_pTreasure2 = NULL;
        m_pTeamData[i].m_pTreasure3 = NULL;
        m_pTeamData[i].m_pTreasure4 = NULL;
        m_pTeamData[i].m_pTreasure5 = NULL;
        m_pTeamData[i].m_pTreasure6 = NULL;
        m_pTeamData[i].m_pTreasure7 = NULL;
        m_pTeamData[i].m_pTreasure8 = NULL;
    }
    
    m_pScoller = NULL;
    m_pText_tile = NULL;
    m_pText_tile1 = NULL;
    m_pNodeScroller = NULL;
    m_pCmdScroll = NULL;
    m_nIndex = 0;
    
    m_pNodeStar = NULL;
    for(int i=0 ;i < EQUIP_MAX; i++){
        
        m_pitemname[i] = NULL;
        m_pitem[i] = NULL;
    }
    for (int i=0 ; i < DESTINY_MAX; i++) {
        
        m_pDestinyName[i] = NULL;
    }
    m_pFightPower = NULL;
    m_pAttack = NULL;
    m_pLife = NULL;
    m_pLevel = NULL;
    m_pAidAddAtk = NULL;
    m_pAidAddHp = NULL;
    m_pPetName = NULL;
    
    for (int i=0 ; i < 7; i++) {
        
        m_pStar[i] = NULL;
    }
    
    MB_LayerRoleInfoHeader::setMenuEnable(false, "MB_LayerEqCompare");
    
}
MB_LayerEqCompare::~MB_LayerEqCompare(){
    
    for (int i = 0 ; i < CARD_IN_GAME; i++) {
        
        CC_SAFE_DELETE(m_pTeamData[i].m_pPet);
        CC_SAFE_DELETE(m_pTeamData[i].m_pEquip1);
        CC_SAFE_DELETE(m_pTeamData[i].m_pEquip2);
        CC_SAFE_DELETE(m_pTeamData[i].m_pEquip3);
        CC_SAFE_DELETE(m_pTeamData[i].m_pTreasure1);
        CC_SAFE_DELETE(m_pTeamData[i].m_pTreasure2);
        CC_SAFE_DELETE(m_pTeamData[i].m_pTreasure3);
        CC_SAFE_DELETE(m_pTeamData[i].m_pTreasure4);
        CC_SAFE_DELETE(m_pTeamData[i].m_pTreasure5);
        CC_SAFE_DELETE(m_pTeamData[i].m_pTreasure6);
        CC_SAFE_DELETE(m_pTeamData[i].m_pTreasure7);
        CC_SAFE_DELETE(m_pTeamData[i].m_pTreasure8);
    }
    CC_SAFE_DELETE_ARRAY(m_pTeamData);
    CC_SAFE_RELEASE(m_pText_tile);
    CC_SAFE_RELEASE(m_pText_tile1);
    CC_SAFE_RELEASE(m_pScoller);
    CC_SAFE_RELEASE(m_pLiArray);
    CC_SAFE_RELEASE(m_pNodeScroller);
    CC_SAFE_RELEASE(m_pZdlSpr);
    CC_SAFE_RELEASE(m_pLevel);
    for(int i=0 ;i < EQUIP_MAX; i++){
        
        CC_SAFE_RELEASE(m_pitemname[i]);
        CC_SAFE_RELEASE(m_pitem[i]);
    }
    
    for (int i=0 ; i < DESTINY_MAX; i++) {
        
        CC_SAFE_RELEASE(m_pDestinyName[i]);
    }
    
    for (int i=0 ; i < 7; i++) {
        
        CC_SAFE_RELEASE(m_pStar[i]);
    }
    
    CC_SAFE_RELEASE_NULL(m_pNodeStar);
    CC_SAFE_RELEASE( m_pAttack );
    CC_SAFE_RELEASE( m_pLife );
    CC_SAFE_RELEASE( m_pPetName );
    
    CC_SAFE_RELEASE(m_pFightPower);
    
    CC_SAFE_RELEASE(m_pAidAddAtk);
    CC_SAFE_RELEASE(m_pAidAddHp);
    MB_LayerRoleInfoHeader::setMenuEnable(true, "MB_LayerEqCompare");
}



bool MB_LayerEqCompare::init(TeamDataStruct **teamData,CCArray *liArray,int index,const char * rolename,uint16_t atkadd,uint16_t hpadd){
    
    m_nAtkadd = atkadd;
    m_nHpadd = hpadd;
    if(MB_ResWindow::init() == false){
        
        return false;
    }
    m_pLiArray = liArray;
    CC_SAFE_RETAIN(m_pLiArray);
    int count = 0;
    for (int i = 0 ; i < CARD_IN_GAME; i++) {
        
        if (teamData[i]->m_pPet == NULL) {
            continue;
        }
        m_pTeamData[count].m_pPet = teamData[i]->m_pPet;
        m_pTeamData[count].m_pEquip1 = teamData[i]->m_pEquip1;
        m_pTeamData[count].m_pEquip2 = teamData[i]->m_pEquip2;
        m_pTeamData[count].m_pEquip3 = teamData[i]->m_pEquip3;
        m_pTeamData[count].m_pTreasure1 = teamData[i]->m_pTreasure1;
        m_pTeamData[count].m_pTreasure2 = teamData[i]->m_pTreasure2;
        m_pTeamData[count].m_pTreasure3 = teamData[i]->m_pTreasure3;
        m_pTeamData[count].m_pTreasure4 = teamData[i]->m_pTreasure4;
        m_pTeamData[count].m_pTreasure5 = teamData[i]->m_pTreasure5;
        m_pTeamData[count].m_pTreasure6 = teamData[i]->m_pTreasure6;
        m_pTeamData[count].m_pTreasure7 = teamData[i]->m_pTreasure7;
        m_pTeamData[count].m_pTreasure8 = teamData[i]->m_pTreasure8;
        count++;
    }
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode * node= pCCBReader->readNodeGraphFromFile("res/formation_layer_compare2.ccbi", this);
    pCCBReader->release();
    this->addChild(NSGameHelper::createDisableTouchLayer());
    this->addChild(node);
    m_pText_tile->setString(rolename);
    m_pText_tile1->setString(rolename);
    m_nLength = 0;
    m_nCMDLength = 0;
    m_nIndex = index;
    m_pTableView =CCScrollView::create(m_pScoller->getContentSize());
    m_pTableView->setDirection(kCCScrollViewDirectionHorizontal);
    m_pTableView->setDelegate(this);
    m_pScoller->addChild(m_pTableView);
    
    m_pCmdScroll = CCScrollView::create(m_pNodeScroller->getContentSize());
    m_pCmdScroll->setDirection(kCCScrollViewDirectionHorizontal);
    m_pCmdScroll->setDelegate(this);
    m_pNodeScroller->addChild(m_pCmdScroll);
    m_pNodeScroller->setVisible(true);
    
    
    
    CCSize size = CCSize(m_pNodeScroller->getContentSize().width/(MAX_SHOW_CMD),m_pNodeScroller->getContentSize().height);
    m_nCmdWidth = size.width;
    CCLayer* slayer =  CCLayer::create();
    CCLayer *t_Contener = CCLayer::create();
    t_Contener->setTag(LAYER_TAG);
    
    for(int i = 0 ; i < CARD_IN_GAME ;i++){
        
        if(m_pTeamData[i].m_pPet != NULL){
            
            CCNode * node = CCNode::create();
            node->setPosition(m_nCmdWidth*m_nCMDLength,0);
            node->setTag(m_nCMDLength);
            slayer->addChild(node);
            m_nCMDLength++;
            
            MB_NodePetAid* nodeAid = MB_NodePetAid::createType(m_pTeamData[i].m_pPet, kNodePetTypeOtherMain);
            nodeAid->setIndex(i);
            node->addChild(nodeAid);
            nodeAid->setPosition(ccp(size.width/2.0f,size.height/2.0f));
            nodeAid->setTag(NODE_GER_TAG);
            
            
            CCNode *layer = CCNode::create();
            layer->setContentSize(m_pScoller->getContentSize());
            MB_NodePetCard* card = MB_NodePetCard::create(m_pTeamData[i].m_pPet->getPetTypeID(),m_pTeamData[i].m_pPet->getPetQuallity());
            layer->addChild(card);
            card->setPosition(0,layer->getContentSize().height*0.5);
            
            //            CCLayer *layer = MB_LayerEqOther::create(m_pTeamData,m_pLiArray,i,atkadd,hpadd);
            t_Contener->addChild(layer);
            layer->setTag(m_nLength);
            layer->setPosition((m_nLength+0.5f)*m_pScoller->getContentSize().width,0);
            m_nLength ++;
        }
    }
    slayer->setContentSize(CCSize(m_nCMDLength * m_nCmdWidth ,size.height));
    this->m_pCmdScroll->setContainer(slayer);
    this->m_pCmdScroll->setViewSize(CCSize(640,960));
    slayer->setPosition(ccp(0 ,0));
    
    t_Contener->setContentSize(CCSize(m_pScoller->getContentSize().width*m_nLength,m_pScoller->getContentSize().height));
    m_pTableView->setContainer(t_Contener);
    m_pTableView->getContainer()->setPosition(ccp(0, 0));
    m_pTableView->setTouchEnabled(false);
//    m_pCmdScroll->setTouchEnabled(false);
    
    changeSelect(-1, m_nIndex);
    m_pTableView->getContainer()->setPosition(ccp( - m_nIndex  *m_pScoller->getContentSize().width,0));
    whenMoveOver(m_pTableView->getContainer());
    if((m_nCMDLength - m_nIndex) < 5){
        
        if(m_nCMDLength > MAX_SHOW_CMD){
            
            m_pCmdScroll->getContainer()->runAction(CCSequence::create(CCMoveTo::create(0.1f, ccp((4 - m_nCMDLength)*m_nCmdWidth,0)),NULL));
            
        }else {
            
            m_pCmdScroll->getContainer()->runAction(CCSequence::create(CCMoveTo::create(0.1f, ccp(0,0)),NULL));
            
        }
        
    }else {
        
        if(m_nIndex >0){
            
            m_pCmdScroll->getContainer()->setPosition(ccp( -(m_nIndex-1)*m_nCmdWidth,0));
            
        }else {
            
            m_pCmdScroll->getContainer()->setPosition( ccp(0,0));
        }
    }
    
    

    return true;
    
}
MB_LayerEqCompare * MB_LayerEqCompare::create(TeamDataStruct **teamData,CCArray *liArray,int index,const char * rolename,uint16_t atkadd,uint16_t hpadd){
    
    MB_LayerEqCompare * ptr = new MB_LayerEqCompare();
    if (ptr && ptr->init(teamData,liArray,index,rolename,atkadd,hpadd)) {
        
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
cocos2d::SEL_MenuHandler MB_LayerEqCompare::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    //    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCardClick",MB_LayerEqCompare::onCardClick);
    //    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onWeapon1Click", MB_LayerEqCompare::onWeapon1Click );
    //    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onWeapon2Click", MB_LayerEqCompare::onWeapon2Click );
    //    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onWeapon3Click", MB_LayerEqCompare::onWeapon3Click );
    //    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBao1Click", MB_LayerEqCompare::onBao1Click);
    //    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBao2Click", MB_LayerEqCompare::onBao2Click);
    //    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBao3Click", MB_LayerEqCompare::onBao3Click);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerEqCompare::onBackClicked);
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_LayerEqCompare::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){
    
    
    
    return NULL;
}
bool MB_LayerEqCompare::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){
    
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pText_tile", CCLabelTTF *, m_pText_tile);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pText_tile1", CCLabelTTF *, m_pText_tile1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScoller", CCNode *, m_pScoller);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeScroller", CCNode *,m_pNodeScroller);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pZdlSpr", CCNode *,m_pZdlSpr );
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeStar",CCNode*,m_pNodeStar);
    
    char itemname[] = "itemname1";
    char item[] = "item1";
    for(int i=0 ;i < EQUIP_MAX; i++){
        
        itemname[8]= '1'+i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE( this , itemname ,CCLabelTTF* ,m_pitemname[i]);
        item[4] = '1' + i ;
        CCB_MEMBERVARIABLEASSIGNER_GLUE( this ,item ,CCNode *, m_pitem[i]);
    }
    
    char destiny[]="destinyName1";
    for (int i=0; i < DESTINY_MAX; i++) {
        
        destiny[11] = '1'+i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE( this ,destiny,CCLabelTTF *,m_pDestinyName[i]);
        
    }
    
    char strStar[]="star1";
    for (int i=0; i < 7; i++) {
        
        strStar[4] = '1'+i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE( this ,strStar,CCNode *,m_pStar[i]);
        
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLevel", CCLabelBMFont *,m_pLevel );
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pAttack",CCLabelTTF *, m_pAttack );
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLife",CCLabelTTF *, m_pLife );
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pPetName",CCLabelTTF *, m_pPetName );
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pFightPower", CCLabelBMFont *,  m_pFightPower);
    if(strcmp(pMemberVariableName, "onCard") == 0){
        
        ((CCMenu *)pNode)->setSwallowsTouches(false);
    }
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pAidAddHp",CCLabelTTF *,m_pAidAddHp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pAidAddAtk",CCLabelTTF *,m_pAidAddAtk);
    
    return false;
}
void MB_LayerEqCompare::onBackClicked(CCObject *){
    
    this->removeFromParent();
}
void MB_LayerEqCompare::scrollViewDidScroll(cocos2d::extension::CCScrollView* view)
{
    if(view == m_pCmdScroll)
    {
        return;
    }
    if(view->isTouchMoved () == false)
    {
        int reindex= m_nIndex;
        // nowindex =(int)(-view->getContainer()->getPosition().x /m_pScoller->getContentSize().width);
        
        if(view->getContainer()->getPosition().x < -(m_nIndex + 0.2)*m_pScoller->getContentSize().width)
        {
            if ( fabs(view->getScrollDistance().x) < FLT_EPSILON&& view->getContainer()->getPosition().x > -(m_nIndex + 0.5)*m_pScoller->getContentSize().width)
            {
            }
            else
            {
                m_nIndex  = m_nIndex  + 1;
            }
        }
        else if(view->getContainer()->getPosition().x > -((m_nIndex -0.2f)*m_pScoller->getContentSize().width)){
            
			if (fabs(view->getScrollDistance().x) < FLT_EPSILON && view->getContainer()->getPosition().x < -(m_nIndex - 0.5f)*m_pScoller->getContentSize().width) {
                
            }
            else
            {
                m_nIndex  = m_nIndex  - 1;
            }
        }
        if(m_nIndex <= 0){
            
            m_nIndex  = 0;
            
        }else  if (m_nIndex  >= m_nLength){
            
            m_nIndex  = m_nLength -1;
        }
        view->unscheduleAllSelectors();
        view->getContainer()->stopAllActions();
        view->getContainer()->runAction(CCSequence::create(CCMoveTo::create(0.1f, ccp( - m_nIndex  *m_pScoller->getContentSize().width,0)),
                                                           CCCallFuncN::create(this,callfuncN_selector(MB_LayerEqCompare::whenMoveOver)),NULL));
        
        if((m_nCMDLength - m_nIndex) < MAX_SHOW_CMD){
            
            if(m_nCMDLength > MAX_SHOW_CMD){
                
                m_pCmdScroll->getContainer()->runAction(CCSequence::create(CCMoveTo::create(0.1f, ccp((MAX_SHOW_CMD - m_nCMDLength)*m_nCmdWidth,0)),NULL));
                
            }else {
                
                m_pCmdScroll->getContainer()->runAction(CCSequence::create(CCMoveTo::create(0.1f, ccp(0,0)),NULL));
            }
            
        }else {
            
            if(m_nIndex >0){
                
                m_pCmdScroll->getContainer()->runAction(CCSequence::create(CCMoveTo::create(0.1f, ccp( - (m_nIndex - 1)*m_nCmdWidth,0)),NULL));
                
            }else {
                
                m_pCmdScroll->getContainer()->runAction(CCSequence::create(CCMoveTo::create(0.1f, ccp(0,0)),NULL));
                
            }
            
        }
        changeSelect(reindex, m_nIndex);
        
    }else {
        
        
        for (int i = 0 ; i < m_nLength ; i++) {
            
            CCNode * node = view->getContainer()->getChildByTag(i);
            if(node != NULL){
                
                node->setVisible(true);
            }
            
        }
        return;
    }
    
    
}
void MB_LayerEqCompare::scrollViewDidZoom(cocos2d::extension::CCScrollView* view){
    
}
void MB_LayerEqCompare::whenMoveOver(CCNode *pnode){
    
    
    for (int i = 0 ; i < m_nLength ; i++) {
        
        if (i != m_nIndex ) {
            
            CCNode * node = pnode->getChildByTag(i);
            if(node != NULL){
                
                node->setVisible(false);
            }
            
        }else {
            
            CCNode * node = pnode->getChildByTag(i);
            if(node != NULL){
                
                node->setVisible(true);
            }
        }
    }
    
}

void MB_LayerEqCompare::moveToIndex(uint8_t index){
    
    changeSelect(m_nIndex, index);
    m_nIndex = index;
    
    m_pTableView->getContainer()->runAction(CCSequence::create(CCMoveTo::create(0.1f, ccp( - m_nIndex  *m_pScoller->getContentSize().width,0)),
                                                               CCCallFuncN::create(this,callfuncN_selector(MB_LayerEqCompare::whenMoveOver)),NULL));
    if((m_nCMDLength - m_nIndex) < 5){
        
        if(m_nCMDLength > MAX_SHOW_CMD){
            
            m_pCmdScroll->getContainer()->runAction(CCSequence::create(CCMoveTo::create(0.1f, ccp((5 - m_nCMDLength)*m_nCmdWidth,0)),NULL));
            
        }else {//m_nIndex
            
            m_pCmdScroll->getContainer()->runAction(CCSequence::create(CCMoveTo::create(0.1f, ccp(0,0)),NULL));
            
        }
        
    }else {
        
        if(m_nIndex >0){
            
            m_pCmdScroll->getContainer()->runAction(CCSequence::create(CCMoveTo::create(0.1f, ccp( -(m_nIndex-1)*m_nCmdWidth,0)), NULL));
            
        }else {
            
            m_pCmdScroll->getContainer()->runAction(CCSequence::create(CCMoveTo::create(0.1f, ccp(0,0)), NULL));
        }
    }
}
void MB_LayerEqCompare::changeSelect(int reIndex,int nowindex){
    
    if(reIndex != -1 && reIndex != nowindex){
        m_nIndex = nowindex;
        MB_NodePetAid *node = (MB_NodePetAid *)(m_pCmdScroll->getContainer()->getChildByTag(reIndex)->getChildByTag(NODE_GER_TAG));
        node->setIsSelect(false);
    }
    
    MB_NodePetAid * node = (MB_NodePetAid *)(m_pCmdScroll->getContainer()->getChildByTag(nowindex)->getChildByTag(NODE_GER_TAG));
    node->setIsSelect(true);
    onResetShow();
}


void MB_LayerEqCompare::setItemShow(MB_ItemData* data, int index){
    
    if(data == NULL){
        
        switch (index) {
            case 0:
                m_pitemname[index]->setString("武器");
                break;
            case 1:
                m_pitemname[index]->setString("头饰");
                break;
            case 2:
                m_pitemname[index]->setString("战甲");
                break;
            case 3:
                m_pitemname[index]->setString("幸运物");
                break;
            case 4:
                m_pitemname[index]->setString("项链");
                break;
            case 5:
                m_pitemname[index]->setString("项链");
                break;
            default:
                m_pitemname[index]->setString("");
                break;
        }
        m_pitem[index]->removeAllChildrenWithCleanup(true);
        //        m_pitem[index]->addChild(MB_NodeItem::create((uint64_t)0));
        m_pitemname[index]->setColor(ccc3(255,255,255));
        return;
    }
    m_pitem[index]->removeAllChildrenWithCleanup(true);
    MB_NodeItem * node = MB_NodeItem::create(data);
    m_pitem[index]->addChild(node);
    MB_ItemTemplate * templete = MB_ItemMgr::getInstance()->getItemTemplateByID(data->getItemID());
    std::string addName = "";
    char buf[60];
    if(data->getItemRank() >= 10){
        
        addName = "[完美] " ;
    }
    sprintf(buf, "%s%s",addName.c_str(),templete->getItemName());
    m_pitemname[index]->setString(buf);
    
    //    CCNodeRGBA pDest;
    //    NSGameHelper::setQualityColor(&pDest,templete->getItemStar());
    //    m_pitemname[index]->setColor(pDest.getColor());
    
    //如果套装被激活，显示套装效果
    if(MB_TeamData::getInstance()->checkSuitActivate(data,&(m_pTeamData[m_nIndex])))
    {
        CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
        CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
        CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/eff_node_suit.ccbi");
        //        pCCBReader->getAnimationManager()->runAnimationsForSequenceNamed("Default Timeline");
        m_pitem [index]->addChild(pNode);
        CC_SAFE_RELEASE_NULL(pCCBReader);
    }
    
}

bool MB_LayerEqCompare::IsUnLockDestiny(MB_DestinyData *data,TeamDataStruct *tdata){
    
    if (data->getDestinyType() == 1) {
        
        if ( IsFindInTeam(data->getDestinyNeed1())&&
            IsFindInTeam(data->getDestinyNeed2())&&
            IsFindInTeam(data->getDestinyNeed3())&&
            IsFindInTeam(data->getDestinyNeed4()) ) {
            
            return true;
        }
        
    }else {
        
        if ( IsFindInItem(data->getDestinyNeed1(),tdata)&&
            IsFindInItem(data->getDestinyNeed2(),tdata)&&
            IsFindInItem(data->getDestinyNeed3(),tdata)&&
            IsFindInItem(data->getDestinyNeed4(),tdata ) ) {
            
            return true;
        }
    }
    
    return false;
}

bool MB_LayerEqCompare::IsFindInItem(int ItemType,TeamDataStruct* tdata){
    
    MB_ItemTemplate *item =MB_ItemMgr::getInstance()->getItemTemplateByID(ItemType);
    
    if (item == NULL) {
        
        return true;
    }
    if (tdata->m_pEquip1 != NULL ) {
        
        if (tdata->m_pEquip1->getItemID() == ItemType) {
            
            return true;
            
        }
        
    }
    if (tdata->m_pEquip2 != NULL){
        
        if (tdata->m_pEquip2->getItemID()== ItemType ) {
            
            return true;
        }
        
    }
    if (tdata->m_pEquip3 != NULL){
        
        if (tdata->m_pEquip3->getItemID()== ItemType ) {
            
            return true;
        }
        
    }
    if (tdata->m_pEquip1 != NULL){
        
        if (tdata->m_pEquip1->getItemID()== ItemType ) {
            
            return true;
        }
        
    }
    if (tdata->m_pTreasure1 != NULL){
        
        if (tdata->m_pTreasure1->getItemID()== ItemType ) {
            
            return true;
        }
    }
    if (tdata->m_pTreasure2 != NULL){
        
        if (tdata->m_pTreasure2->getItemID()== ItemType ) {
            
            return true;
        }
    }
    if (tdata->m_pTreasure3 != NULL){
        
        if (tdata->m_pTreasure3->getItemID()== ItemType ) {
            
            return true;
        }
    }
    if (tdata->m_pTreasure4 != NULL){
        
        if (tdata->m_pTreasure4->getItemID()== ItemType ) {
            
            return true;
        }
    }
    if (tdata->m_pTreasure5 != NULL){
        
        if (tdata->m_pTreasure5->getItemID()== ItemType ) {
            
            return true;
        }
    }
    if (tdata->m_pTreasure6 != NULL){
        
        if (tdata->m_pTreasure6->getItemID()== ItemType ) {
            
            return true;
        }
    }
    if (tdata->m_pTreasure7 != NULL){
        
        if (tdata->m_pTreasure7->getItemID()== ItemType ) {
            
            return true;
        }
    }
    if (tdata->m_pTreasure8 != NULL){
        
        if (tdata->m_pTreasure8->getItemID()== ItemType ) {
            
            return true;
        }
    }
    
    
    return false;
}
bool MB_LayerEqCompare::IsFindInTeam(int petType){
    
    MB_PetTemplate *pet = MB_PetMgr::getInstance()->getPetTemplateByID(petType);
    
    if (pet == NULL) {
        
        return true;
    }
    for (int i = 0 ; i < MEMBER_NUM; i++) {
        
        TeamDataStruct*  data = &(m_pTeamData[i]);
        if (data->m_pPet != NULL) {
            
            if(data->m_pPet->getPetTypeID() == petType ){
                
                return true;
            }
        }
    }
    
    return false ;
}


void MB_LayerEqCompare::onResetShow()
{
    m_pArray = m_pLiArray;
    
    TeamDataStruct* tdata = &(m_pTeamData[m_nIndex]);
    
    MB_PetTemplate *gtdata = MB_PetMgr::getInstance()->getPetTemplateByID(tdata->m_pPet->getPetTypeID());
    const char *realname = MB_PetMgr::getInstance()->getPetRealName(tdata->m_pPet->getPetTypeID(),tdata->m_pPet->getPetQuallity());
    m_pPetName ->setString(realname);
    CC_SAFE_DELETE_ARRAY(realname);
    
    char databuf[50];
    sprintf(databuf, "%d",tdata->m_pPet->getPetAttack());
    m_pAttack->setString(databuf);
    sprintf(databuf, "%d",tdata->m_pPet->getPetHpMax());
    m_pLife->setString(databuf);
    sprintf(databuf, "%llu",tdata->m_pPet->getPetFightPower());
    m_pFightPower->setString(databuf);
    m_pZdlSpr->setPosition(ccp((12-NSGameHelper::get_length(tdata->m_pPet->getPetFightPower()))*60/9.0f,m_pZdlSpr->getPositionY()));
    
    sprintf(databuf, "%d",tdata->m_pPet->getPetLevel());
    m_pLevel->setString(databuf);
    
    int rank = gtdata->getPetStar();
    for(int i = 0;i < 7;i++)
    {
        if (i < rank)
        {
            m_pStar[i]->setVisible(true);
        }
        else
        {
            m_pStar[i]->setVisible(false);
        }
    }
    m_pNodeStar->setPositionX(320 + (MAX_GER_STAR-gtdata->getPetStar())*0.5/MAX_GER_STAR*m_pNodeStar->getContentSize().width);
    for(int i = 0;i<DESTINY_MAX;++i)
    {
        MB_DestinyData *destiny = MB_DestinyMgr::getInstance()->getDestinyDataByID( gtdata->getDestinyByIndex(i));
        if (destiny != NULL)
        {
            
            m_pDestinyName[i]->setVisible(true);
            char databuf[40];
            sprintf(databuf, "[%s]",destiny->getDestinyName());
            m_pDestinyName[i]->setString(databuf);
            
            if (IsUnLockDestiny(destiny, tdata))
            {
                m_pDestinyName[i]->setColor(ccc3(108, 29, 35));
            }
            else if(destiny->getDestinyType() == 1 )
            {
                m_pDestinyName[i]->setColor(ccc3(127, 127, 127));
                //                bool bIsActive = false;
                //                if(isActiveDestinyInLiteam(destiny->getDestinyNeed1()))
                //                {
                //                    if(isActiveDestinyInLiteam(destiny->getDestinyNeed2()))
                //                    {
                //                        if(isActiveDestinyInLiteam(destiny->getDestinyNeed3()))
                //                        {
                //                            if(isActiveDestinyInLiteam(destiny->getDestinyNeed4()))
                //                            {
                //                                bIsActive = true;
                //                            }
                //                        }
                //                    }
                //                }
                //                if (bIsActive)
                //                {
                //                    m_pDestinyName[i]->setColor(ccc3(108 , 29, 35));
                //                }
                //                else
                //                {
                //                    m_pDestinyName[i]->setColor(ccc3(127, 127, 127));
                //                }
                //
                //            }
                //            else
                //            {
                //                m_pDestinyName[i]->setColor(ccc3(127, 127, 127));
                //            }
            }
        }
        else
        {
            m_pDestinyName[i]->setVisible(false);
        }
        
    }
    
    setItemShow(tdata->m_pEquip1,0);
    setItemShow(tdata->m_pEquip2,1);
    setItemShow(tdata->m_pEquip3,2);
    setItemShow(tdata->m_pTreasure1,3);
    setItemShow(tdata->m_pTreasure2,4);
    setItemShow(tdata->m_pTreasure3,5);
    
    sprintf(databuf, "(+%0.1f%%)",m_nAtkadd/100.0f);
    m_pAidAddAtk->setString(databuf);
    sprintf(databuf, "(+%0.1f%%)",m_nHpadd/100.0f);
    m_pAidAddHp->setString(databuf);
}


/*
 bool MB_LayerEqCompare::isActiveDestinyInLiteam(uint16_t type)
 {
 
 MB_PetTemplate *pet = MB_PetMgr::getInstance()->getPetTemplateByID(type);
 if (pet == NULL)
 {
 
 return true;
 }
 CCObject *obj;
 CCARRAY_FOREACH(m_pArray, obj)
 {
 
 Lieu_ViewData * data = (Lieu_ViewData *)obj;
 
 if(type == data->getPetType())
 {
 
 return true;
 
 }
 
 }
 return  false;
 
 }*/
