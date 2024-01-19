

#include "MB_DataShowPic.h"

USING_NS_CC;


static MB_DataShowPic* s_pDataShowPic = NULL; // pointer to singleton

MB_DataShowPic::MB_DataShowPic()
{
    //本地读取數据
    m_pClientMB_PetTemplateArray = new CCArray();
    m_pClientEquipTempleteArray = new CCArray();
    m_pClientTreasureTempleteArray = new CCArray();
    
    //伺服器接受的數据
    m_pServerMB_PetTemplateArray = new CCArray();
    m_pServerEquipTempleteArray = new CCArray();
    m_pServerTreasureTempleteArray = new CCArray();
    
    
    if (!initMB_PetTemplate())
    {
        MB_LOG("initMB_PetTemplate failed.");
    }
    if (!initEquipTemplete())
    {
        MB_LOG("initEquipTemplete failed.");
    }
    if (!initTreasureTemplete())
    {
        MB_LOG("initItemTemplate failed.");
    }
    
    SOCKET_MSG_REGIST(SC_GATHER_GET_LIST, MB_DataShowPic);
    SOCKET_MSG_REGIST(SC_GATHER_NEW, MB_DataShowPic);
}

MB_DataShowPic::~MB_DataShowPic()
{
    SOCKET_MSG_UNREGIST(SC_GATHER_GET_LIST);
    SOCKET_MSG_UNREGIST(SC_GATHER_NEW);
    
    CC_SAFE_RELEASE_NULL(m_pClientMB_PetTemplateArray);
    CC_SAFE_RELEASE_NULL(m_pClientEquipTempleteArray);
    CC_SAFE_RELEASE_NULL(m_pClientTreasureTempleteArray);
    
    CC_SAFE_RELEASE_NULL(m_pServerMB_PetTemplateArray);
    CC_SAFE_RELEASE_NULL(m_pServerEquipTempleteArray);
    CC_SAFE_RELEASE_NULL(m_pServerTreasureTempleteArray);
    
    //為啥要释放两遍
    //    CC_SAFE_RELEASE_NULL(m_pServerMB_PetTemplateArray);
    //    CC_SAFE_RELEASE_NULL(m_pServerEquipTempleteArray);
    //    CC_SAFE_RELEASE_NULL(m_pServerTreasureTempleteArray);
}

MB_DataShowPic* MB_DataShowPic::getInstance()
{
    if (s_pDataShowPic == NULL)
    {
        s_pDataShowPic = new MB_DataShowPic();
    }
    
    return s_pDataShowPic;
}

void MB_DataShowPic::destroyInstance()
{
    CC_SAFE_DELETE(s_pDataShowPic);
    s_pDataShowPic = NULL;
}

bool MB_DataShowPic::initMB_PetTemplate()
{
    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/pic/card_book.xml");
    
    if (!g_sharedDoc)
    {
        return false;
    }
    
    xmlNodePtr root;
    
    root=xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    while(curNode != NULL) {
        
        if (!xmlStrcmp(curNode->name,BAD_CAST "pic"))
        {
            struct _xmlAttr * attr = curNode->properties;
            
            if (attr != NULL) {
                MB_PicShow* pPicShow = new MB_PicShow();
                
                if (attr&&!xmlStrcmp(attr->name,BAD_CAST "id"))
                {
                    value = (char*)xmlNodeGetContent(attr->children);
                    pPicShow->setID(atoi(value));
                    CC_SAFE_FREE(value);
                    attr = attr->next;
                }
                if (attr&&!xmlStrcmp(attr->name,BAD_CAST "Activata"))
                {
                    value = (char*)xmlNodeGetContent(attr->children);
                    pPicShow->setActivata(atoi(value));
                    CC_SAFE_FREE(value);
                    attr = attr->next;
                }
                if (attr&&!xmlStrcmp(attr->name,BAD_CAST "isnew"))
                {
                    value = (char*)xmlNodeGetContent(attr->children);
                    bool bisnew = atoi(value);
                    pPicShow->setIsNew(!bisnew);
                    CC_SAFE_FREE(value);
                }
                pPicShow->setShape(SHAPE_1);
                //加入到模板中
                m_pClientMB_PetTemplateArray->addObject(pPicShow);
                pPicShow->release();
                
            }
            curNode = curNode->next;
            
        }
        else if(!xmlStrcmp(curNode->name,BAD_CAST "pic1"))
        {
            struct _xmlAttr * attr = curNode->properties;
            
            if (attr != NULL) {
                MB_PicShow* pPicShow = new MB_PicShow();
                
                if (attr&&!xmlStrcmp(attr->name,BAD_CAST "id"))
                {
                    value = (char*)xmlNodeGetContent(attr->children);
                    pPicShow->setID(atoi(value));
                    CC_SAFE_FREE(value);
                    attr = attr->next;
                }
                if (attr&&!xmlStrcmp(attr->name,BAD_CAST "Activata"))
                {
                    value = (char*)xmlNodeGetContent(attr->children);
                    pPicShow->setActivata(atoi(value));
                    CC_SAFE_FREE(value);
                    attr = attr->next;
                }
                if (attr&&!xmlStrcmp(attr->name,BAD_CAST "isnew"))
                {
                    value = (char*)xmlNodeGetContent(attr->children);
                    bool bisnew = atoi(value);
                    pPicShow->setIsNew(!bisnew);
                    CC_SAFE_FREE(value);
                }
                pPicShow->setShape(SHAPE_2);
                //加入到模板中
                m_pClientMB_PetTemplateArray->addObject(pPicShow);
                pPicShow->release();
                
            }
            curNode = curNode->next;
        }
        else if(!xmlStrcmp(curNode->name,BAD_CAST "pic2"))
        {
            struct _xmlAttr * attr = curNode->properties;
            
            if (attr != NULL) {
                MB_PicShow* pPicShow = new MB_PicShow();
                
                if (attr&&!xmlStrcmp(attr->name,BAD_CAST "id"))
                {
                    value = (char*)xmlNodeGetContent(attr->children);
                    pPicShow->setID(atoi(value));
                    CC_SAFE_FREE(value);
                    attr = attr->next;
                }
                if (attr&&!xmlStrcmp(attr->name,BAD_CAST "Activata"))
                {
                    value = (char*)xmlNodeGetContent(attr->children);
                    pPicShow->setActivata(atoi(value));
                    CC_SAFE_FREE(value);
                    attr = attr->next;
                }
                if (attr&&!xmlStrcmp(attr->name,BAD_CAST "isnew"))
                {
                    value = (char*)xmlNodeGetContent(attr->children);
                    bool bisnew = atoi(value);
                    pPicShow->setIsNew(!bisnew);
                    CC_SAFE_FREE(value);
                }
                pPicShow->setShape(SHAPE_3);
                //加入到模板中
                m_pClientMB_PetTemplateArray->addObject(pPicShow);
                pPicShow->release();
                
            }
            curNode = curNode->next;
        }
        else
        {
            curNode = curNode->next;
            continue;
        }
        
    }
    xmlFreeDoc(g_sharedDoc);
    
    return true;
}

bool MB_DataShowPic::initEquipTemplete()
{
    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/pic/equipment.xml");
    
    if (!g_sharedDoc)
    {
        return false;
    }
    
    xmlNodePtr root;
    
    root=xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    while(curNode != NULL) {
        
        if (xmlStrcmp(curNode->name,BAD_CAST "pic"))
        {
            curNode = curNode->next;
            continue;
        }
        
        struct _xmlAttr * attr = curNode->properties;
        
        if (attr != NULL) {
            
            MB_PicShow* pPicShow = new MB_PicShow();
            
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "id"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                pPicShow->setID(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "Activata"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                pPicShow->setActivata(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "isnew"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                bool bisnew = atoi(value);
                pPicShow->setIsNew(!bisnew);
                CC_SAFE_FREE(value);
            }
            //加入到模板中
            m_pClientEquipTempleteArray->addObject(pPicShow);
            pPicShow->release();
            
        }
        
        curNode = curNode->next;
    }
    
    xmlFreeDoc(g_sharedDoc);
    
    return true;
}

bool MB_DataShowPic::initTreasureTemplete()
{
    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/pic/item_book.xml");
    
    if (!g_sharedDoc)
    {
        return false;
    }
    
    xmlNodePtr root;
    
    root=xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    while(curNode != NULL) {
        
        if (xmlStrcmp(curNode->name,BAD_CAST "pic"))
        {
            curNode = curNode->next;
            continue;
        }
        
        struct _xmlAttr * attr = curNode->properties;
        
        if (attr != NULL) {
            
            MB_PicShow* pPicShow = new MB_PicShow();
            
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "id"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                pPicShow->setID(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "Activata"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                pPicShow->setActivata(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "isnew"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                bool bisnew = atoi(value);
                pPicShow->setIsNew(!bisnew);
                CC_SAFE_FREE(value);
            }
            //加入到模板中
            m_pClientTreasureTempleteArray->addObject(pPicShow);
            pPicShow->release();
            
        }
        
        curNode = curNode->next;
    }
    
    xmlFreeDoc(g_sharedDoc);
    
    return true;
}

bool MB_DataShowPic::sendgather_get_list(uint8_t type)
{
    SOCKET_REQUEST_START(CS_GATHER_GET_LIST);
    packet->writeU8(type);
    SOCKET_REQUEST_END(SC_GATHER_GET_LIST, MB_DataShowPic::onMsgRecv);
    return true;
}

bool MB_DataShowPic::recvgather_get_list(MB_MsgBuffer *recvPacket)
{
    uint8_t type = 0;
    uint16_t  count = 0;
    uint32_t data32 = 0;
    recvPacket->readU8(&type);
    if (type == PIC_SHOW_TYPE_GER)//精靈
    {
        //清理數据
        m_pServerMB_PetTemplateArray->removeAllObjects();
        if (recvPacket->readU16(&count)) {
            for (int i = 0; i < count; i++) {
                if (recvPacket->readU32(&data32)) {
                    MB_PicShow* pShowPic = new MB_PicShow();
                    pShowPic->setID(data32%SHAPE_BASE);
                    pShowPic->setShape(data32/SHAPE_BASE);
                    pShowPic->setActivata(false);
                    m_pServerMB_PetTemplateArray->addObject(pShowPic);
                    pShowPic->release();
                    //MB_LOG("精靈ID %d  階段 %d",data32%SHAPE_BASE,data32/SHAPE_BASE);
                }
            }
        }
    }
    if (type == PIC_SHOW_TYPE_TREASURE)   //杂物
    {
        m_pServerTreasureTempleteArray->removeAllObjects();
        if (recvPacket->readU16(&count)) {
            for (int i = 0; i < count; i++) {
                if (recvPacket->readU32(&data32)) {
                    MB_PicShow* pShowPic = new MB_PicShow();
                    pShowPic->setID(data32%SHAPE_BASE);
                    pShowPic->setActivata(false);
                    m_pServerTreasureTempleteArray->addObject(pShowPic);
                    pShowPic->release();
                }
            }
        }
    }
    else if (type == PIC_SHOW_TYPE_EQUIP)//裝備
    {
        //清理數据
        m_pServerEquipTempleteArray->removeAllObjects();
        
        if (recvPacket->readU16(&count)) {
            for (int i = 0; i < count; i++) {
                if (recvPacket->readU32(&data32)) {
                    MB_PicShow* pShowPic = new MB_PicShow();
                    pShowPic->setID(data32%SHAPE_BASE);
                    pShowPic->setActivata(false);
                    m_pServerEquipTempleteArray->addObject(pShowPic);
                    pShowPic->release();
                }
            }
        }
    }
    else
    {
//        MB_LOG("recvgather_get_list unkown type");
    }
    return true;
}

bool MB_DataShowPic::recvgather_new(MB_MsgBuffer *recvPacket)
{
    uint8_t type = 0;
    uint16_t count = 0;
    uint32_t data32 = 0;
    recvPacket->readU8(&type);
    if (type == PIC_SHOW_TYPE_GER)//精靈
    {
        if (recvPacket->readU16(&count)) {
            for (int i = 0; i < count; i++) {
                if (recvPacket->readU32(&data32)) {
                    MB_PicShow* pShowPic = new MB_PicShow();
                    pShowPic->setID(data32%SHAPE_BASE);
                    pShowPic->setShape(data32/SHAPE_BASE);
                    pShowPic->setActivata(false);
                    m_pServerMB_PetTemplateArray->addObject(pShowPic);
                    pShowPic->release();
                }
            }
        }
    }
    if (type == PIC_SHOW_TYPE_TREASURE)   //杂物
    {
        if (recvPacket->readU16(&count)) {
            for (int i = 0; i < count; i++) {
                if (recvPacket->readU32(&data32)) {
                    MB_PicShow* pShowPic = new MB_PicShow();
                    pShowPic->setID(data32%SHAPE_BASE);
                    pShowPic->setActivata(false);
                    m_pServerTreasureTempleteArray->addObject(pShowPic);
                    pShowPic->release();
                }
            }
        }
    }
    else if (type == PIC_SHOW_TYPE_EQUIP)//裝備
    {
        if (recvPacket->readU16(&count)) {
            for (int i = 0; i < count; i++) {
                if (recvPacket->readU32(&data32)) {
                    MB_PicShow* pShowPic = new MB_PicShow();
                    pShowPic->setID(data32%SHAPE_BASE);
                    pShowPic->setActivata(false);
                    m_pServerEquipTempleteArray->addObject(pShowPic);
                    pShowPic->release();
                }
            }
        }
    }
    else
    {
//        MB_LOG("recvgather_get_list unkown type");
    }
    
    return true;
}

void MB_DataShowPic::onMsgRecv(CCNode* node, SocketResponse* response)
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
            
        case SC_GATHER_GET_LIST:
            recvgather_get_list(recvPacket);
            break;
            
        case SC_GATHER_NEW:
            recvgather_new(recvPacket);
            break;
            
        default:
            break;
    }
    
}

void MB_DataShowPic::getClientMB_PetTemplateArrayByStar(CCArray* array,int star)
{
    if (array == NULL)
    {
        return;
    }
    array->removeAllObjects();
    MB_PicShow* data = NULL;
    CCARRAY_FOREACH_4TYPE(m_pClientMB_PetTemplateArray, MB_PicShow*, data)
    {
        int nstar = MB_PetMgr::getInstance()->getPetTemplateByID(data->getID())->getPetStar();
        if (nstar == star)
        {
            array->addObject(data);
        }
    }
    
}
void MB_DataShowPic::getClientEquipTempleteArrayByStar(CCArray* array,int star)
{
    if (array == NULL)
    {
        return;
    }
    array->removeAllObjects();
    MB_PicShow* data = NULL;
    CCARRAY_FOREACH_4TYPE(m_pClientEquipTempleteArray, MB_PicShow*, data)
    {
        int nstar = MB_ItemMgr::getInstance()->getItemTemplateByID(data->getID())->getItemStar();
        if (nstar == star)
        {
            array->addObject(data);
        }
    }
}
