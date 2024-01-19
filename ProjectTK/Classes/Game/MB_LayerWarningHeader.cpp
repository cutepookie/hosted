

#include "Game.h"
#include "MB_LayerWarningHeader.h"
#include "MB_AbsolvedConfigure.h"
#define DATA8_ID 241
#define DATA16_ID 242
#define DATA32_ID 243
#define DATA64_ID 244
#define DATABOOL_ID 245
#define DATASTRING_ID 246

#define DATAGER_ID 10418
#define DATAITEM_ID 10616

#define ROLE_COLOR ccc3(255,99, 0)
#define BATTTLE_COLOR ccc3(0,255, 0)
USING_NS_CC;
USING_NS_CC_EXT;


MB_LayerWarningHeader::MB_LayerWarningHeader()
{
    m_pHeaderInfo = NULL;
    m_pSharedLayer = this;
    m_pScollerNode = NULL;
    m_pBgNode = NULL;
    m_pStringCache = new CCArray();
    m_pNowShowMessage = NULL;
    m_nMessageLength = 0;
    SOCKET_MSG_REGIST(SC_MESSAGE_BC, MB_LayerWarningHeader);
    SOCKET_MSG_REGIST(SC_MESSAGE_BC_ID, MB_LayerWarningHeader);
    SOCKET_MSG_REGIST(SC_MESSAGE_BC_ID2, MB_LayerWarningHeader);
    SOCKET_MSG_REGIST(SC_MESSAGE_GER_UPLEVEL, MB_LayerWarningHeader);
    SOCKET_MSG_REGIST(SC_MESSAGE_ITEM_UPRANK, MB_LayerWarningHeader);
    SOCKET_MSG_REGIST(SC_MESSAGE_BEST_CARD,MB_LayerWarningHeader);
    SOCKET_MSG_REGIST(SC_BATTLE_BROADCAST_GET_ITEM, MB_LayerWarningHeader);
}

MB_LayerWarningHeader::~MB_LayerWarningHeader()
{
    
    SOCKET_MSG_UNREGIST(SC_MESSAGE_BC);
    SOCKET_MSG_UNREGIST(SC_MESSAGE_BC_ID);
    SOCKET_MSG_UNREGIST(SC_MESSAGE_BC_ID2);
    SOCKET_MSG_UNREGIST(SC_MESSAGE_GER_UPLEVEL);
    SOCKET_MSG_UNREGIST(SC_MESSAGE_ITEM_UPRANK);
    SOCKET_MSG_UNREGIST(SC_MESSAGE_BEST_CARD);
    SOCKET_MSG_UNREGIST(SC_BATTLE_BROADCAST_GET_ITEM);
    CC_SAFE_DELETE(m_pStringCache);
    CC_SAFE_RELEASE(m_pScollerNode);
        CC_SAFE_RELEASE(m_pBgNode);
    
    unscheduleAllSelectors();
    m_pSharedLayer = NULL;
    CC_SAFE_RELEASE(m_pHeaderInfo);
}



CCScene* MB_LayerWarningHeader::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	
	// 'layer' is an autorelease object
	MB_LayerWarningHeader *layer = MB_LayerWarningHeader::create();
    
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MB_LayerWarningHeader::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    
    //init CCBReader
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    m_pNode = pCCBReader->readNodeGraphFromFile("res/message_layer_header.ccbi", this);
    this->addChild(m_pNode);
    //确定用不到了就要释放
    CC_SAFE_RELEASE_NULL(pCCBReader);
    m_pScoller = CCScrollView::create(m_pScollerNode->getContentSize());
    m_pScoller->setDirection(kCCScrollViewDirectionHorizontal);
    m_pScoller->setContentSize(m_pScollerNode->getContentSize());
    m_pScollerNode->addChild(m_pScoller);
    m_pScoller->setContentOffset(ccp(0,0));
    m_nHeaderLeft = 0;
    m_pColor = m_pHeaderInfo->getColor();
    
    //TODODO 屏蔽游戏上方走马灯
    this->setScale(0);
   	return true;
}
void MB_LayerWarningHeader::onMsgRecv(CCNode* node, SocketResponse* response){
    
    assert(response != NULL);
    
    
    //将socket数据读取到序列化结构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    //MB_LOG("scroll notice: %d\n",Msg);
    
    
    switch (Msg) {
        case   SC_MESSAGE_BC:{
            
            if(m_pStringCache->count() >MESSAGE_MAX){
                
                return;
            }            
            MB_HeadMessage *message = new MB_HeadMessage();
            message->setType(Msg);
            m_pStringCache->addObject(message);
            message->release();            
            char * str = recvPacket->ReadString();
            // this->setHeaderString(str);
            if(str)message->setString(str);
            CC_SAFE_FREE(str);
            goShowMessage(message);
            break;
        }
        case   SC_MESSAGE_BC_ID:{
            
            if(m_pStringCache->count() >MESSAGE_MAX){
                
                return;
            }
            MB_HeadMessage *message = new MB_HeadMessage();
            message->setType(Msg);
            m_pStringCache->addObject(message);
            message->release();
            short msgid;
            recvPacket->readU16(&msgid);
            message->setMessageID(msgid);
            goShowMessage(message);
            //  recvmeesage_bc_id(recvPacket);
            break;
        }
        case   SC_MESSAGE_BC_ID2:{
            
            if(m_pStringCache->count() >MESSAGE_MAX){
                
                return;
            }
            MB_HeadMessage *message = new MB_HeadMessage();
            message->setType(Msg);
            m_pStringCache->addObject(message);
            message->release();
            recvmeesage_bc_id2(recvPacket,message);
            goShowMessage(message);
            //  recvmeesage_bc_id2(recvPacket);
        
            break;
        }
        case   SC_MESSAGE_GER_UPLEVEL:{
            
            if(m_pStringCache->count() >MESSAGE_MAX){
                
                return;
            }
            MB_HeadMessage *message = new MB_HeadMessage();
            message->setType(Msg);
            m_pStringCache->addObject(message);
            message->release();
            
            char *rolename = recvPacket->ReadString();
            uint16_t data16;
            recvPacket->readU16(&data16);
            uint16_t rank = data16;
            recvPacket->readU16(&data16);
            recvPacket->readU16(&data16);
            
            if(rolename)message->setRoleName(rolename);
            MB_MessageSpItem *item = new MB_MessageSpItem();
            item->setRewardType(kmCardType_General);
            item->setRewardValue(data16);
            item->setRewardRank(rank);
            item->setRewardLevel(1);
            item->setRewardNum(1);
            message->getArray()->addObject(item);
            item->release();
            CC_SAFE_FREE(rolename);
            goShowMessage(message);
          //  recvmessage_pet_upLevel(recvPacket);
            break;
        }
        case SC_MESSAGE_ITEM_UPRANK:{
            
            if(m_pStringCache->count() >MESSAGE_MAX){
                
                return;
            }
            MB_HeadMessage *message = new MB_HeadMessage();
            message->setType(Msg);
            m_pStringCache->addObject(message);
            message->release();
            
            char *rolename =recvPacket->ReadString();
            uint16_t data16;
            recvPacket->readU16(&data16);
            uint16_t itemType = data16;
            uint8_t data8;
            recvPacket->readU8(&data8);
            recvPacket->readU8(&data8);
            uint8_t rank = data8;
            if(rolename)message->setRoleName(rolename);
            MB_MessageSpItem *item = new MB_MessageSpItem();
            item->setRewardType(kmCardType_Item);
            item->setRewardValue(itemType);
            item->setRewardRank(rank);
            item->setRewardLevel(1);
            item->setRewardNum(1);
            message->getArray()->addObject(item);
            item->release();
            CC_SAFE_FREE(rolename);
            goShowMessage(message);
            //recvmessage_item_uprank(recvPacket);
            break;
        }
        case SC_MESSAGE_BEST_CARD:{
            
            if(m_pStringCache->count() >MESSAGE_MAX){
                
                return;
            }
            MB_HeadMessage *message = new MB_HeadMessage();
            message->setType(Msg);
            m_pStringCache->addObject(message);
            message->release();
            
            uint8_t  data8;
            uint32_t data32;
            char* rolename =  recvPacket->ReadString();
            recvPacket->readU8(&data8);
            recvPacket->readU32(&data32);
            
            if(rolename)message->setRoleName(rolename);
            MB_MessageSpItem *item = new MB_MessageSpItem();
            item->setRewardType(data8);
            item->setRewardNum(data32);
            message->getArray()->addObject(item);
            item->release();
            CC_SAFE_FREE(rolename);
            goShowMessage(message);
            //recvmessage_best_card(recvPacket);
            break;
        }
        case SC_BATTLE_BROADCAST_GET_ITEM:{
            
            if(m_pStringCache->count() >MESSAGE_MAX){
                
                return;
            }
            MB_HeadMessage *message = new MB_HeadMessage();
            message->setType(Msg);
            m_pStringCache->addObject(message);
            message->release();            
            uint8_t  data8;
            uint32_t data32;
            char* rolename =  recvPacket->ReadString();
            recvPacket->readU32(&data32);
            recvPacket->readU8(&data8);
            if(rolename)message->setRoleName(rolename);
            MB_MessageSpItem *item = new MB_MessageSpItem();
            item->setRewardValue(data32);//道具it
            item->setRewardNum(data8);
       
            message->getArray()->addObject(item);
            item->release();
            
            item = new MB_MessageSpItem();
            uint16_t data16;
            recvPacket->readU16(&data16);           
             item->setRewardNum(data16); //关卡id
            recvPacket->readU16(&data16);
            item->setRewardValue(data16);//道具章节id
            message->getArray()->addObject(item);
            item->release();
            
            CC_SAFE_FREE(rolename);
            goShowMessage(message);
            //recvmessage_best_card(recvPacket);
            break;
        }

        default:
            break;
    }
}
void MB_LayerWarningHeader::goShowMessage(MB_HeadMessage *message){

    if(m_pNowShowMessage == NULL){
    
        onPopItem();
    }
}
CCObject *  MB_LayerWarningHeader::getStringBuffer(MB_MsgBuffer* pbuffer){

    uint8_t mesgtype;
    pbuffer->readU8(&mesgtype);
    
    if (mesgtype == DATA8_ID) {
        
        uint8_t data8;
        pbuffer->readU8(&data8);
        CCString *string = new CCString();
        string->initWithFormat("%d",data8);
        string->autorelease();
        return string;
        
    }else  if (mesgtype == DATA16_ID){
        
        uint16_t  data16;
        pbuffer->readU16(&data16);
        CCString *string = new CCString();
        string->initWithFormat("%d",data16);
        string->autorelease();
        return string;
        
    }else  if (mesgtype == DATA32_ID){
        
        uint32_t  data32;
        pbuffer->readU32(&data32);
        CCString *string = new CCString();
        string->initWithFormat("%d",data32);
        string->autorelease();
        return string;
        
    }else  if (mesgtype == DATA64_ID){
        
        uint64_t data64;
        pbuffer->readU64(&data64);
        CCString *string = new CCString();
        string->initWithFormat("%lld",data64);
        string->autorelease();
        return string;
    }
    else  if (mesgtype == DATABOOL_ID){
        
        uint8_t  databool;
        pbuffer->readU8(&databool);        
        CCString *string = new CCString();
        string->initWithFormat( "%s",(databool == 1 ? "是":"否"));
        string->autorelease();
        return string;
        
    } else  if (mesgtype == DATASTRING_ID){
        
        char *datachar = pbuffer->ReadString() ;
        CCString *string = new CCString();
        if(datachar)string->initWithFormat( "%s",datachar);
        string->autorelease();
        CC_SAFE_FREE(datachar);
        return string;
    
    }else{
        
        uint8_t data8;
        pbuffer->readU8(&data8);
        char databuf[3];
        databuf[0] = mesgtype;
        databuf[1] = data8;
        databuf[2] = '\0';
        
        short nowtype;
        memcpy(&nowtype, &databuf[0], 2);
        uint16_t* data = (uint16_t*)(&nowtype);
        *data = NTOH_I16(*data);
        
        if (nowtype == DATAGER_ID) {
            
            uint16_t rank;
            pbuffer->readU16(&rank);
            uint16_t level;
            pbuffer->readU16(&level);
            uint16_t petType;
            pbuffer->readU16(&petType);
            MB_MessageSpItem *item = new MB_MessageSpItem();
            item->setRewardType(kmCardType_General);
            item->setRewardValue(petType);
            item->setRewardNum(1);
            item->setRewardLevel(level);
            item->setRewardRank(rank);
            item->autorelease();
            return item;
            
        }else if (nowtype == DATAITEM_ID) {
            
            uint16_t itemType;
            pbuffer->readU16(&itemType);
            uint8_t level;
            pbuffer->readU8(&level);
            uint8_t rank;
            pbuffer->readU8(&rank);
            uint16_t itemNum;
            pbuffer->readU16(&itemNum);
         
            MB_MessageSpItem *item = new MB_MessageSpItem();
            item->setRewardType( kmCardType_Item);
            item->setRewardValue(itemType);
            item->setRewardNum(itemNum);
            item->setRewardLevel(level);
            item->setRewardRank(rank);
            item->autorelease();
            return item;
        }
        
        
    }
    
  
    return NULL;

}
bool  MB_LayerWarningHeader::recvmeesage_bc_id2(MB_MsgBuffer *recvpacket,MB_HeadMessage *message){

    short msgid;
    recvpacket->readU16(&msgid);
    message->setMessageID(msgid);
    
    uint16_t mesglength = 0;
    recvpacket->readU16(&mesglength);
    for ( int i = 0; i < mesglength; i++) {
        
           message->getArray()->addObject(getStringBuffer(recvpacket));
    }
    return  true;
}
void MB_LayerWarningHeader::onPopItem(){
    
    if( m_pNowShowMessage != NULL){
    
        m_pStringCache->removeObject(m_pNowShowMessage);
        m_pNowShowMessage = NULL;
    }    
    if(m_pStringCache->count() == 0){
    
        m_pNowShowMessage = NULL;
        return ;
    }
    m_pNowShowMessage  =  (MB_HeadMessage *) m_pStringCache->objectAtIndex(0);
    switch (m_pNowShowMessage ->getType()) {
            
        case   SC_MESSAGE_BC:{
          
            this->setHeaderString(m_pNowShowMessage->getString());
          
            break;
        }
        case   SC_MESSAGE_BC_ID:{
          
            recvmeesage_bc_id(m_pNowShowMessage );
            break;
        }
        case   SC_MESSAGE_BC_ID2:{
        
            recvmeesage_bc_id2(m_pNowShowMessage );
            break;
        }
        case   SC_MESSAGE_GER_UPLEVEL:{
        
            recvmessage_pet_upLevel(m_pNowShowMessage );
            break;
        }
        case SC_MESSAGE_ITEM_UPRANK:{
            
            recvmessage_item_uprank(m_pNowShowMessage );
            break;
        }
        case SC_MESSAGE_BEST_CARD:{
            
            recvmessage_best_card(m_pNowShowMessage);
            break;
        }
        case SC_BATTLE_BROADCAST_GET_ITEM:{
        
            recvbattle_broadcaset_get_item(m_pNowShowMessage);
            break;
        }
        default:
            break;
    }
}
bool MB_LayerWarningHeader::recvmeesage_bc_id(MB_HeadMessage *message){
    
    char databuf[500];
    getMessageByID(message->getMessageID(), databuf);
    if(strlen(databuf) != 0){
        
        this->setHeaderString(databuf);
    }
    return true;
}
CCLabelTTF *MB_LayerWarningHeader::getLabel(CCObject *obj){
    if(dynamic_cast<CCString *>(obj) != NULL){
    
        CCLabelTTF *label = new CCLabelTTF();
        label->initWithString(((CCString *)obj)->getCString(),m_pHeaderInfo->getFontName(), m_pHeaderInfo->getFontSize());
        return label;
        
    }else if(dynamic_cast<MB_MessageSpItem *>(obj) != NULL){
    
        CCLabelTTF *label = new CCLabelTTF();
        label->initWithString(" ",m_pHeaderInfo->getFontName(), m_pHeaderInfo->getFontSize());

        MB_MessageSpItem * data = (MB_MessageSpItem *)obj;
        if(data->getRewardType() == kmCardType_General){
        
            MB_PetTemplate *templete = MB_PetMgr::getInstance()->getPetTemplateByID(data->getRewardValue());
            
            if(templete != NULL ){
                
                const char *name =  MB_PetMgr::getInstance()->getPetRealName(data->getRewardValue(), data->getRewardRank());
                label->setString(name);
                CC_SAFE_DELETE_ARRAY(name);
                
            }

        }else {
            
            MB_ItemTemplate  *templete = MB_ItemMgr::getInstance()->getItemTemplateByID(data->getRewardValue());
            int firstcount = data->getRewardRank();
            char buf[60];
            std::string addName = "";
            if (firstcount >= 10 && firstcount <= 19) {
                
                addName = "[完美] " ;
                
            }
            sprintf(buf, "%s%s",addName.c_str(),templete->getItemName());
            int qual =  data->getRewardRank()%10;
            if(qual!=0){
                
                sprintf(buf, "%s +%d",buf,qual);
            }
            
            if(templete != NULL )
            {
                label->setString(buf);
            }
        }
        return label;
        
    }
    
    return NULL;
}
bool MB_LayerWarningHeader::recvmeesage_bc_id2(MB_HeadMessage *message){
   
    char databuf[500];
    getMessageByID(message->getMessageID(), databuf);
    CCObject *obj;
    CCArray *array = CCArray::create();
    CCARRAY_FOREACH(message->getArray(), obj){
        
        CCLabelTTF * tempLabel = getLabel(obj);
        array->addObject(tempLabel);
        tempLabel->release();
    }
    int index = 0;
    char cache[100];
    int j = 0;
    CCLabelTTF *head = NULL;
    CCLabelTTF *next = NULL;
    m_nMessageLength = 0;
    for (int i = 0; databuf[i]  != '\0'; ) {
        
        
        if(databuf[i+j] == '['){
            
            cache[j] = '\0';
            CCLabelTTF *label =  NULL;
            CCLabelTTF *mesg = NULL;
            CCLabelTTF *last = NULL;
            int nowMessage = 0;
            
            if(j != 0){
                
                label = CCLabelTTF::create(cache ,m_pHeaderInfo->getFontName(), m_pHeaderInfo->getFontSize());
                last  = label;
                nowMessage  = label->getContentSize().width;
                label->retain();
                label->setColor(m_pColor);
                
            }
            if(index < array->count()){
                
                mesg = (CCLabelTTF *)array->objectAtIndex(index);
                index ++;
                char mesgtype = databuf[i+j+1] ;
                
                if (mesgtype  == 'r') {
                    
                    mesg->setColor(ROLE_COLOR);
                    
                }else  if (mesgtype  == 's'){
                    
                    mesg->setColor(m_pColor);
                }
                
                nowMessage = nowMessage + mesg->getContentSize().width;
                last = mesg;
                
                if (label != NULL) {
                    
                    label->addChild(mesg);
                    mesg->setPosition(ccp(label->getContentSize().width + mesg->getContentSize().width/2.0f,label->getContentSize().height/2.0f));
                    
                }else {
                    
                    label = mesg;
                    label->retain();
                }
            }
            if (head == NULL) {
                
                head = label;
                next = last;
                m_pScoller->getContainer()->addChild(head);
                head->release();
                
            }else {
                
                next->addChild(label);
                label->setPosition(ccp(next->getContentSize().width + label->getContentSize().width/2.0f,next->getContentSize().height/2.0f));
                next = last;
                label->release();
                
            }
            m_nMessageLength = m_nMessageLength + nowMessage ;
            
            
            i = i+j+3;
            j = 0;
            
        }else if (databuf[i+j] == '\0'){
            
            cache[j] =databuf[i+j];
            int nowMessage = 0;
            if(j != 0){
                
                CCLabelTTF *label = CCLabelTTF::create(cache ,m_pHeaderInfo->getFontName(), m_pHeaderInfo->getFontSize());
                nowMessage  = label ->getContentSize().width;
                
                if (head == NULL) {
                    
                    head = label;
                    next = label;
                    m_pScoller->getContainer()->addChild(head);
                    label->setColor(m_pColor);
                    
                }else {
                    
                    next->addChild(label);
                    label->setPosition(ccp(next->getContentSize().width + label->getContentSize().width/2.0f,next->getContentSize().height/2.0f));
                    next = label;
                    label->setColor(m_pColor);
                }
                m_nMessageLength = m_nMessageLength + nowMessage ;
            }
            break;
            
        }else {
            
            cache[j] =databuf[i+j];
            j++;
            
        }
        
    }
    
    array->removeAllObjects();
    array->release();
    if(head != NULL){
        
        onStartMessageMove(head);
    }

     return true;
}
bool MB_LayerWarningHeader::recvmessage_pet_upLevel(MB_HeadMessage *message){

    MB_MessageSpItem * data = ( MB_MessageSpItem *) message->getArray()->objectAtIndex(0);    
    char *petName = (char *)MB_PetMgr::getInstance()->getPetRealName(data->getRewardValue(), data->getRewardRank());
    CCLabelTTF *m_pTempHead = CCLabelTTF::create("恭喜",m_pHeaderInfo->getFontName(), m_pHeaderInfo->getFontSize());
    CCLabelTTF *m_pRoleName = CCLabelTTF::create(message->getRoleName(),m_pHeaderInfo->getFontName(), m_pHeaderInfo->getFontSize());
    CCLabelTTF *m_pPetName = CCLabelTTF::create(petName,m_pHeaderInfo->getFontName(), m_pHeaderInfo->getFontSize());
    // 恭喜[r]，将卡牌[r]进化到[s]
    CCLabelTTF *m_pTemp = CCLabelTTF::create(",将自己的一只精灵成功进化,获得",m_pHeaderInfo->getFontName(), m_pHeaderInfo->getFontSize());
    m_pTempHead->addChild(m_pRoleName);
    m_pTempHead->addChild(m_pTemp);
    m_pTempHead->addChild(m_pPetName);
    CC_SAFE_DELETE_ARRAY(petName);
    m_nMessageLength = m_pTempHead->getContentSize().width;
    m_pRoleName->setPosition(ccp(m_nMessageLength+m_pRoleName->getContentSize().width/2.0f,m_pTempHead->getContentSize().height/2.0f));
    m_nMessageLength = m_nMessageLength + m_pRoleName->getContentSize().width;
    m_pTemp->setPosition(ccp(m_nMessageLength + m_pTemp->getContentSize().width/2.0f,  m_pRoleName->getPosition().y));
    m_nMessageLength = m_nMessageLength + m_pTemp->getContentSize().width;
    m_pPetName->setPosition(ccp(m_nMessageLength + m_pPetName->getContentSize().width/2.0f,  m_pRoleName->getPosition().y));
    m_nMessageLength = m_nMessageLength +m_pPetName->getContentSize().width;
    
    m_pTempHead->setColor(m_pColor);
    m_pRoleName->setColor(ROLE_COLOR);
    m_pTemp->setColor(m_pColor);
    
    MB_PetTemplate *templete = MB_PetMgr::getInstance()->getPetTemplateByID(data->getRewardValue());
    m_pScoller->getContainer()->addChild(m_pTempHead);
    this->onStartMessageMove(m_pTempHead);

    
    return true;
}
bool MB_LayerWarningHeader::recvmessage_item_uprank(MB_HeadMessage *message){

    MB_MessageSpItem * data = ( MB_MessageSpItem *) message->getArray()->objectAtIndex(0);      
    MB_ItemTemplate  *templete = MB_ItemMgr::getInstance()->getItemTemplateByID(data->getRewardValue());    
    int firstcount= data->getRewardRank();
    char buf[60];
    std::string addName = "";
    if (firstcount >= 10 && firstcount <= 19) {
        
        addName = "[完美] " ;
        
    }
    sprintf(buf, "%s%s",addName.c_str(),templete->getItemName());
    int qual =  data->getRewardRank()%10;
    if(qual!=0){
        
        sprintf(buf, "%s +%d",buf,qual);
    }    
    CCLabelTTF *m_pTempHead = CCLabelTTF::create("恭喜",m_pHeaderInfo->getFontName(), m_pHeaderInfo->getFontSize());
    CCLabelTTF *m_pRoleName = CCLabelTTF::create(message->getRoleName() ,m_pHeaderInfo->getFontName(), m_pHeaderInfo->getFontSize());
    CCLabelTTF *m_pItemName = CCLabelTTF::create(buf,m_pHeaderInfo->getFontName(), m_pHeaderInfo->getFontSize());
    CCLabelTTF *m_pTemp = CCLabelTTF::create(",成功精炼出",m_pHeaderInfo->getFontName(), m_pHeaderInfo->getFontSize());
    m_pTempHead->addChild(m_pRoleName);
    m_pTempHead->addChild(m_pTemp);
    m_pTempHead->addChild(m_pItemName);
    m_nMessageLength = m_pTempHead->getContentSize().width;
    m_pRoleName->setPosition(ccp(m_nMessageLength+m_pRoleName->getContentSize().width/2.0f,m_pTempHead->getContentSize().height/2.0f));
    m_nMessageLength = m_nMessageLength + m_pRoleName->getContentSize().width;
    m_pTemp->setPosition(ccp(m_nMessageLength + m_pTemp->getContentSize().width/2.0f,  m_pRoleName->getPosition().y));
    m_nMessageLength = m_nMessageLength + m_pTemp->getContentSize().width;
    m_pItemName->setPosition(ccp(m_nMessageLength + m_pItemName->getContentSize().width/2.0f,  m_pRoleName->getPosition().y));
    m_nMessageLength = m_nMessageLength + m_pItemName->getContentSize().width;
    
    m_pTempHead->setColor(m_pColor);
    m_pRoleName->setColor(ROLE_COLOR);
    m_pTemp->setColor(m_pColor);
    
    m_pScoller->getContainer()->addChild(m_pTempHead);
    onStartMessageMove(m_pTempHead);
     return true;
}
bool MB_LayerWarningHeader::recvmessage_best_card(MB_HeadMessage *message){

     return true;
}

#include "MB_AbsolvedConfigure.h"
#include "MB_ChapterData.h"
bool MB_LayerWarningHeader::recvbattle_broadcaset_get_item(MB_HeadMessage *message){

    MB_MessageSpItem *data = (MB_MessageSpItem * )message->getArray()->objectAtIndex(0);
    
    MB_ItemTemplate *item = MB_ItemMgr::getInstance()->getItemTemplateByID(data->getRewardValue());
    int num = data->getRewardNum();
    data = ( MB_MessageSpItem * )message->getArray()->objectAtIndex(1);
    
//    MB_ChapterDungeonData* pChapter = MB_AbsolvedConfigure::getInstance()->getChapterDungeonsID(data->getRewardValue());
//    if (pChapter)
//    {
//        pChapter->get
//    }
    
    
    MB_ChapterData *chdata = NULL;
    if(!MB_AbsolvedConfigure::getInstance()->queryChapterDataByID(data->getRewardValue(),&chdata))
    {
        return false;
    }
    
    MB_ChapterDungeonData * p = MB_AbsolvedConfigure::getInstance()->getChapterDungeonsID(chdata->getChapterId());
    if (p == NULL)
    {
        return false;
    }
    
    const MB_DungeonData* pData = p->getDungeonDataByID(data->getRewardNum());
    if (pData == NULL)
    {
        return false;
    }
    
    char databuf[128] = {};
    sprintf(databuf, "%s-%s",chdata->getName().c_str(),pData->getName());
    

    CCLabelTTF *m_pTempHead = CCLabelTTF::create("恭喜 ",m_pHeaderInfo->getFontName(), m_pHeaderInfo->getFontSize());
    CCLabelTTF *m_pRoleName = CCLabelTTF::create(message->getRoleName() ,m_pHeaderInfo->getFontName(), m_pHeaderInfo->getFontSize());
    CCLabelTTF *m_pTemp1 = CCLabelTTF::create("，在远征" ,m_pHeaderInfo->getFontName(), m_pHeaderInfo->getFontSize());
    CCLabelTTF *m_pBattleLevel = CCLabelTTF::create(databuf,m_pHeaderInfo->getFontName(), m_pHeaderInfo->getFontSize());
    CCLabelTTF *m_pTemp2 = CCLabelTTF::create("中，幸运的获得了",m_pHeaderInfo->getFontName(), m_pHeaderInfo->getFontSize());
    sprintf(databuf, "%s * %d",item->getItemName(),num);
    CCLabelTTF *m_pItem = CCLabelTTF::create( databuf ,m_pHeaderInfo->getFontName(), m_pHeaderInfo->getFontSize());
    m_pTempHead->addChild(m_pRoleName);
    m_pTempHead->addChild(m_pTemp1);
    m_pTempHead->addChild(m_pBattleLevel);
    m_pTempHead->addChild(m_pTemp2);
    m_pTempHead->addChild(m_pItem);

    
    m_nMessageLength = m_pTempHead->getContentSize().width;
    m_pRoleName->setPosition(ccp(m_nMessageLength+m_pRoleName->getContentSize().width/2.0f,m_pTempHead->getContentSize().height/2.0f));
    m_nMessageLength = m_nMessageLength + m_pRoleName->getContentSize().width;
   
    m_pTemp1->setPosition(ccp(m_nMessageLength +m_pTemp1->getContentSize().width/2.0f,  m_pRoleName->getPosition().y));
    m_nMessageLength = m_nMessageLength + m_pTemp1->getContentSize().width;

    m_pBattleLevel->setPosition(ccp(m_nMessageLength +m_pBattleLevel->getContentSize().width/2.0f,  m_pRoleName->getPosition().y));
    m_nMessageLength = m_nMessageLength + m_pBattleLevel->getContentSize().width;

    m_pTemp2->setPosition(ccp(m_nMessageLength +m_pTemp2->getContentSize().width/2.0f,  m_pRoleName->getPosition().y));
    m_nMessageLength = m_nMessageLength + m_pTemp2->getContentSize().width;

    m_pItem->setPosition(ccp(m_nMessageLength  +m_pItem->getContentSize().width/2.0f,  m_pRoleName->getPosition().y));
    m_nMessageLength = m_nMessageLength +m_pItem->getContentSize().width;
    
    
    m_pTempHead->setColor(m_pColor);
    m_pRoleName->setColor(ROLE_COLOR);
    m_pTemp1->setColor(m_pColor);
    m_pBattleLevel->setColor(BATTTLE_COLOR);
    m_pTemp2->setColor(m_pColor);
    
    m_pScoller->getContainer()->addChild(m_pTempHead);
    this->onStartMessageMove(m_pTempHead);
    return true;
}
void MB_LayerWarningHeader::getMessageByID(short messgeId,char *strBuf){

    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/head_notice.xml");
    
    if (g_sharedDoc == NULL)
    {
        return ;
    }
    
    xmlNodePtr root;
    root=xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    for (; curNode != NULL ; curNode = curNode->next) {
        
        if (xmlStrcmp(curNode->name,BAD_CAST "message")){
        
            continue;
        }
        for ( struct _xmlAttr * attr = curNode->properties; attr != NULL ; attr = attr->next ) {
            
            if (!xmlStrcmp(attr->name,BAD_CAST "mesid")){
                
                value = (char*)xmlNodeGetContent(attr->children);
                int mesid = atoi(value);
                CC_SAFE_FREE(value);
                if (mesid != messgeId) {
                    
                    break;
                }
            }
            if (!xmlStrcmp(attr->name,BAD_CAST "messtr")){
                
                value = (char*)xmlNodeGetContent(attr->children);
                strcpy(strBuf, value);
                CC_SAFE_FREE(value);
                xmlFreeDoc(g_sharedDoc);
                return;
            }
        }
    }
    
    strcpy(strBuf,"");
    xmlFreeDoc(g_sharedDoc);
}
bool MB_LayerWarningHeader::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "headerInfo", CCLabelTTF*, m_pHeaderInfo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNode", CCNode *, m_pScollerNode);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBgNode", CCNode *, m_pBgNode);
    
    return true;
}

SEL_MenuHandler MB_LayerWarningHeader::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCommitClicked", MB_LayerWarningHeader::onCommitClicked);
    return NULL;
}
SEL_CCControlHandler MB_LayerWarningHeader::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
  
    return NULL;
}
void MB_LayerWarningHeader::onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader)
{
    MB_LOG("onNodeLoaded succeed!");
}

void MB_LayerWarningHeader::onCommitClicked(cocos2d::CCObject *pSender)
{
    MB_LOG("warning clicked!");
    this->setVisible(false);

}
void MB_LayerWarningHeader::setHeaderString(const char *message){
   
    CCLabelTTF *tempLaebl = CCLabelTTF::create(message ,m_pHeaderInfo->getFontName(), m_pHeaderInfo->getFontSize());
    tempLaebl ->setColor(m_pColor);   
    m_pScoller->getContainer()->addChild(tempLaebl);    
    onStartMessageMove(tempLaebl);
    
}
void MB_LayerWarningHeader::onStartMessageMove(CCLabelTTF *tempLabel){
    m_pBgNode->setVisible(true);
    m_pNode->setVisible(true);
    float winwidth = m_pScoller->getViewSize().width;
    tempLabel->setPosition(ccp(winwidth + tempLabel->getContentSize().width/2.0f,m_pScoller->getContentSize().height/2.0f));
    float speed = winwidth /10.0f;
    CCPoint endpos = ccp(- m_nMessageLength-tempLabel->getContentSize().width/2.0f,tempLabel->getContentSize().height/2.0f);
    float time  = ( tempLabel->getPosition().x - endpos.x) /speed;
    tempLabel->runAction(CCSequence::create(CCMoveTo::create(time ,endpos ),
                                            CCCallFuncN::create(this, callfuncN_selector(MB_LayerWarningHeader::onMoevMessageOver)),
                                            NULL));
}
void MB_LayerWarningHeader::onMoevMessageOver(CCNode *node){
    m_pBgNode->setVisible(false);
    node->removeFromParentAndCleanup(true);
    onPopItem();
}
MB_LayerWarningHeader * MB_LayerWarningHeader::m_pSharedLayer = NULL;
MB_LayerWarningHeader * MB_LayerWarningHeader::getSharedLayerWarningHeader(){
    
    return m_pSharedLayer;

}

