////
////  MB_LayerPetProperty.cpp
////  ProjectMB
////
////  Created by yuanwugang on 14-11-22.
////
////
//
//#include "MB_LayerPetProperty.h"
//#include "MB_LayerPetAttibutes.h"
//#include "MB_petData.h"
//#include "MB_LayerPetAttibutes.h"
//#include "MB_NodeDestiny.h"
//#include "MB_NodeSkillContainer.h"
//static const uint8_t activateRank[] = {0,0,2,5,10,15,20};
//static const std::string skillLimit[] =
//{
//    "",
//    "",
//    "[进化+2激活]",
//    "[进化+5激活]",
//    "[完成\"一转\"激活]",
//    "[\"一转\"+5激活]",
//    "[完成\"二转\"激活]",
//    "",
//};
//
//MB_LayerPetProperty::MB_LayerPetProperty()
//{
////    m_pScrollView = NULL;
//}
//MB_LayerPetProperty::~MB_LayerPetProperty()
//{
//
//}
//MB_LayerPetProperty* MB_LayerPetProperty::create(CCSize size,MB_PetData* petData)
//{
//    MB_LayerPetProperty* ptr = new MB_LayerPetProperty();
//    if (ptr && ptr->init(size,petData))
//    {
//        ptr->autorelease();
//        return ptr;
//    }
//    CC_SAFE_RELEASE_NULL(ptr);
//    return NULL;
//}
//bool MB_LayerPetProperty::init(CCSize size,MB_PetData* petData)
//{
//    m_pData = petData;
////    m_pScrollView = CCScrollView::create(size);
////    m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
////    this->addChild(m_pScrollView);
////
////    CCLayer* layer = CCLayer::create();
////
////    MB_NodeRankSkills* node4 = MB_NodeRankSkills::create();
////    node4->setMB_PetData(m_pData);
////    layer->addChild(node4);
////    node4->setTag(kTypeRanSkills);
////
////    MB_NodeSkills* node3 = MB_NodeSkills::create();
////    node3->setMB_PetData(m_pData);
////    layer->addChild(node3);
////    node3->setTag(kTypeSkills);
////
////    MB_NodeEnterSkills* node2 = MB_NodeEnterSkills::create();
////    node2->setMB_PetData(m_pData);
////    layer->addChild(node2);
////    node2->setTag(kTypeEnterSkills);
////
////    MB_NodePetAttibutes* node1 = MB_NodePetAttibutes::create();
////    node1->setMB_PetData(m_pData);
////    layer->addChild(node1);
////    node1->setTag(kTypeAttibutes);
////
////    layer->setContentSize(CCSizeMake(640, 1024));
////    m_pScrollView->setContainer(layer);
////    onClickNode();
////    resetOffset();
//    return true;
//
//
//
//}
//void MB_LayerPetProperty::onResetWnd()
//{
////    CCArray* pChildren = m_pScrollView->getContainer()->getChildren();
////    MB_NodeDeploy* pChild = NULL;
////
////    CCARRAY_FOREACH_4TYPE(pChildren, MB_NodeDeploy*, pChild)
////    {
////        pChild->setDeploy();
////    }
////    sort();
//}
////void MB_LayerPetProperty::onClickNode()
////{
////    CCPoint point = m_pScrollView->getContentOffset();
////    int height = m_pScrollView->getContentSize().height;
////    onResetWnd();
////
////    m_pScrollView->setContentOffset(ccp(0,point.y + height - m_pScrollView->getContentSize().height));
////}
//
////void MB_LayerPetProperty::sort()
////{
//////    int offsetHeight = m_pScrollView->getContentOffset().y;
////    CCArray* pChildren = m_pScrollView->getContainer()->getChildren();
////
////    getChildren();
////    float y = 0;
////    float maxHeight = 0;
////
////
////    CCObject* pObj = NULL;
////    CCNode* pChild = NULL;
////    float max_width = 0;
////    CCSize content_size = CCSizeZero;
////
////    CCARRAY_FOREACH_REVERSE(pChildren, pObj)
////    {
////        pChild = (CCNode*)pObj;
////        maxHeight += pChild->getContentSize().height;
////    }
////
////    CCARRAY_FOREACH_REVERSE(pChildren, pObj)
////    {
////        pChild = (CCNode*)pObj;
////        pChild->setPosition(m_pScrollView->getContentSize().width/2,maxHeight - y);
////        content_size = pChild->getContentSize();
////        y+=content_size.height;
////        max_width = (content_size.width > max_width) ? content_size.width : max_width;
////    }
////
////    m_pScrollView->setContentSize(CCSizeMake(m_pScrollView->getContentSize().width, y));
////}
////void MB_LayerPetProperty::resetOffset()
////{
////    m_pScrollView->setContentOffset(ccp(0,m_pScrollView->getViewSize().height - m_pScrollView->getContentSize().height));
////}
//
//
//MB_NodePetAttibutes::MB_NodePetAttibutes()
//{
//    m_bShowBackground = true;
//    m_pMB_PetData = NULL;
//    SOCKET_MSG_REGIST(SC_GER_DETAIL, MB_NodePetAttibutes);
//}
//MB_NodePetAttibutes::~MB_NodePetAttibutes()
//{
//    SOCKET_MSG_UNREGIST(SC_GER_DETAIL);
//}
//void MB_NodePetAttibutes::setMB_PetData(MB_PetData* data)
//{
//    m_pMB_PetData = data;
//    setTitle("详细属性");
//}
//void MB_NodePetAttibutes::setDeploy()
//{
//    if (m_pNodeContainer->getChildrenCount() == 0)
//    {
//        if (m_pMB_PetData->getPetID() == 0)
//        {
//            MB_LayerPetAttibutes* node = MB_LayerPetAttibutes::create(m_pMB_PetData);
//            node->setAnchorPoint(ccp(0.5,1));
//            if (node)
//            {
//                m_pNodeContainer->addChild(node);
//            }
//        }
//        else
//        {
//            if(MB_TeamData::getInstance()->checkInTeam(m_pMB_PetData))
//            {
//                MB_Message::sharedMB_Message()->showMessage("",15);
//
//                SOCKET_REQUEST_START(CS_GER_DETAIL);
//                packet->WriteUINT64(m_pMB_PetData->getPetID());
//                SOCKET_REQUEST_END(SC_GER_DETAIL,MB_LayerPetDetail::onMsgRecv);
//                return;
//            }
//            else
//            {
//                MB_LayerPetAttibutes* node = MB_LayerPetAttibutes::create(m_pMB_PetData);
//                if (node)
//                {
//                    node->setAnchorPoint(ccp(0.5,1));
//                    m_pNodeContainer->addChild(node);
//                }
//            }
//
//        }
//    }
//    onResetWnd();
//}
//
//void MB_NodePetAttibutes::recvpet_detail(MB_MsgBuffer* pRecv)
//{
//    uint64_t uid = 0;
//    pRecv->readU64(&uid);
//    if (uid != m_pMB_PetData->getPetID())
//    {
//        return;
//    }
//
//    MB_DestinyAttribute* attr = NULL;
//    uint16_t value = 0;
//    CCArray* p = m_pMB_PetData->getOnlineAttribute();
//    p->removeAllObjects();
//    static const uint8_t types[] = {11,12,7,8,9,10,13,14,15,16,3,4,5,6};
//    for (uint8_t i=0; i<14; ++i)
//    {
//        attr = new MB_DestinyAttribute;
//        pRecv->readU16(&value);
//        attr->setValue(value);
//        attr->setType(types[i]);
//        p->addObject(attr);
//        CC_SAFE_RELEASE_NULL(attr);
//    }
//
//    if (m_pNodeContainer->getChildrenCount() == 0)
//    {
//        MB_LayerPetAttibutes* node = MB_LayerPetAttibutes::create(m_pMB_PetData);
//        if (node)
//        {
//            node->setAnchorPoint(ccp(0.5,1));
//            m_pNodeContainer->addChild(node);
//        }
//    }
//    onResetWnd();
////    MB_TARGET_PARENT(MB_LayerPetProperty,ptr)
////    if (ptr)
////    {
////        ptr->sort();
////        ptr->resetOffset();
////    }
//}
//
//void MB_NodePetAttibutes::onMsgRecv(CCNode* node, SocketResponse* response)
//{
//    assert(response != NULL);
//
//    //将socket数据读取到序列化结构
//    MB_MsgBuffer* recvPacket = response->getResponseData();
//
//    //协议号
//    uint16_t Msg = 0;
//    recvPacket->Reset();
//    recvPacket->skipU16();
//    recvPacket->skipU8();
//    recvPacket->readU16(&Msg);
//
//    switch (Msg)
//    {
//        case SC_GER_DETAIL:
//            MB_Message::sharedMB_Message()->removeALLMessage();
//            recvpet_detail(recvPacket);
//            break;
//        default:
//            break;
//    }
//}
//
//
//
//MB_NodeSkills::MB_NodeSkills()
//{
//    m_bShowBackground = true;
//    m_pMB_PetData = NULL;
//}
//MB_NodeSkills::~MB_NodeSkills()
//{
//
//}
//
//void MB_NodeSkills::setMB_PetData(MB_PetData* data)
//{
//    m_pMB_PetData = data;
//    setTitle("组合技");
//}
//void MB_NodeSkills::setDeploy()
//{
//    if ( m_pNodeContainer->getChildrenCount() == 0)
//    {
//        MB_PetTemplate* pTemplate = m_pMB_PetData->getTemplete();
//        if (pTemplate)
//        {
//            MB_NodeDestiny* pNode = NULL;
//            int index = 0;
//            CCNode* node = CCNode::create();
//            node->setAnchorPoint(ccp(0.5,1));
//            CCSize sz;
//            for (int i=0; i<5; ++i)
//            {
//                MB_DestinyData* data = MB_DestinyMgr::getInstance()->getDestinyDataByID(pTemplate->getDestinyByIndex(i));
//                if (data)
//                {
//                    pNode = MB_NodeDestiny::create(data,m_pMB_PetData->getPetID() != 0 && MB_TeamData::getInstance()->IsFindInTeam(data->getDestinyNeed1()));
//                    if (pNode)
//                    {
//                        sz = pNode->getContentSize();
//                        node->addChild(pNode);
//                        pNode->setPosition((i%2 + 0.5)*sz.width,(i/2 + 0.5)*sz.height);
//                        ++index;
//                    }
//                }
//            }
//            node->setContentSize(CCSize((index>1?2:index)*sz.width,(index/2+ (index%2==0?0:1))*sz.height));
//            m_pNodeContainer->addChild(node);
//        }
//    }
//    onResetWnd();
//}
//
//
//
//MB_NodeEnterSkills::MB_NodeEnterSkills()
//{
//    m_bShowBackground = true;
//    m_pMB_PetData = NULL;
//}
//MB_NodeEnterSkills::~MB_NodeEnterSkills()
//{
//
//}
//void MB_NodeEnterSkills::MB_NodeEnterSkills::setMB_PetData(MB_PetData* data)
//{
//    m_pMB_PetData = data;
//    setTitle("技能");
//}
//void MB_NodeEnterSkills::MB_NodeEnterSkills::setDeploy()
//{
//    if (m_pNodeContainer->getChildrenCount() == 0)
//    {
//        MB_PetTemplate* pTemplate = m_pMB_PetData->getTemplete();
//        if (pTemplate)
//        {
//            int index = 0;
//            CCSize sz;
//            CCNode* node = CCNode::create();
//            node->setAnchorPoint(ccp(0.5,1));
//            MB_NodeSkillContainer2* nodeSkill1 = NULL;
//            MB_NodeSkillContainer2* nodeSkill2 = NULL;
//            MB_SkillData *data = MB_SkillMgr::getInstance()->getSkillDataByID(pTemplate->getSkillIDByIndex(0));
//            if (data != NULL)
//            {
//                nodeSkill1 = MB_NodeSkillContainer2::create(data,MB_NodeSkillContainer2::kTypeSkillNormal);
//                if (nodeSkill1 != NULL)
//                {
//                    sz = nodeSkill1->getContentSize();
//                    index++;
//                }
//            }
//            data = NULL;
//            data = MB_SkillMgr::getInstance()->getSkillDataByID(pTemplate->getSkillIDByIndex(1));
//            if (data != NULL)
//            {
//                nodeSkill2 = MB_NodeSkillContainer2::create(data,MB_NodeSkillContainer2::kTypeSkillBig);
//                if (nodeSkill2 != NULL)
//                {
//                    sz = nodeSkill2->getContentSize();
//                    index++;
//                }
//            }
//            if (nodeSkill1 != NULL)
//            {
//                node->addChild(nodeSkill1);
//            }
//            if (nodeSkill2 != NULL)
//            {
//                node->addChild(nodeSkill2);
//            }
//            if (index == 2)
//            {
//                nodeSkill2->setPosition(sz.width/2 + 5,sz.height*0.8f);
//                nodeSkill1->setPosition(sz.width/2 + 5,sz.height*1.8f);
//            }
//            node->setContentSize(CCSize(sz.width,sz.height*index+20));
//            m_pNodeContainer->addChild(node);
//        }
//    }
//    onResetWnd();
//}
//
//
//MB_NodeRankSkills::MB_NodeRankSkills()
//{
//    m_bShowBackground = true;
//    m_pMB_PetData = NULL;
//}
//MB_NodeRankSkills::~MB_NodeRankSkills()
//{
//
//}
//void MB_NodeRankSkills::setMB_PetData(MB_PetData* data)
//{
//    m_pMB_PetData = data;
//    setTitle("进化技能");
//}
//void MB_NodeRankSkills::setDeploy()
//{
//    if (m_pNodeContainer->getChildrenCount() == 0)
//    {
//        MB_PetTemplate* pTemplate = m_pMB_PetData->getTemplete();
//        if (pTemplate)
//        {
//            int num = 0;
//            for (int i = 2;i < 7;i++) {
//                int skillid = pTemplate->getSkillIDByIndex(i);
//                MB_SkillData *data = MB_SkillMgr::getInstance()->getSkillDataByID(skillid);
//                if (data != NULL)
//                {
//                    num++;
//                }
//            }
//            CCNode* node = CCNode::create();
//            node->setAnchorPoint(ccp(0.5,1));
//            CCSize unitSize = MB_NodeSkillUint::create(NULL,0,false)->getContentSize();
//            node->setContentSize(CCSize(unitSize.width,unitSize.height*num));
//            int index = 0;
//            for (int i = 2;i < 7;i++) {
//                int skillid = pTemplate->getSkillIDByIndex(i);
//                MB_SkillData *data = MB_SkillMgr::getInstance()->getSkillDataByID(skillid);
//                if (data != NULL)
//                {
//                    MB_NodeSkillUint* nodeSkills = MB_NodeSkillUint::create(data,i,m_pMB_PetData->getPetQuallity() >= activateRank[i]);
//                    node->addChild(nodeSkills);
//                    nodeSkills->setPosition(unitSize.width/2 + 5,unitSize.height*(num - index - 0.5));
//                    index++;
//                }
//            }
//
//            m_pNodeContainer->addChild(node);
//        }
//    }
//    onResetWnd();
//}
