//
//  MB_LayerPetDetail.cpp
//  ProjectMB
//
//  Create by WenYong on 25/9/2014.
//
//
#include "MB_LayerPetEnhance.h"
#include "MB_LayerPetDetail.h"
#include "MB_PetData.h"
#include "MB_FunctionModule.h"
#include "MB_LayerPetAttibutes.h"
#include "MB_LayerPetEquipment.h"
#include "MB_LayerPetRestore.h"
#include "MB_SkillDetail.h"
#include "MB_LayerCommand.h"
#include "MB_LayerPetUpdate.h"
#include "MB_LayerListEquipChange.h"
#include "MB_LayerItemDetail.h"
kListItemType klit[6] = {kListItemTypeWeaponUp,kListItemTypeDefenceUp,kListItemTypeHorseUp,kListItemTypeTreasureUp,kListItemTypeTreasureUp,kListItemTypeTreasureUp};
ItemPosType ipt[6] = {kItemPosEquip1,kItemPosEquip2,kItemPosEquip3,kItemPosTreasure1,kItemPosTreasure2,kItemPosTreasure3};
MB_LayerPetDetail::MB_LayerPetDetail()
{
    for (int i=0; i< EQUIP_MAX; i++) {
        m_pZBBtn[i] = NULL;
    }
    m_pMoveEquipNode = NULL;
    isShowAllBtn = false;
    m_pZDZBBtn= NULL;
    m_pJHBtn= NULL;
    m_pTQBtn= NULL;
    m_pQHBtn= NULL;
    isUpdateUI = false;
    m_pLikeMenu = NULL;
    m_bIsSubLayer = false;
    m_pLeft= NULL;
    m_pRight= NULL;
    isOn = true;
    m_pJusesejianjie= NULL;
    m_pNode1= NULL;
    m_pNode2= NULL;
    m_pNode3= NULL;
    m_pMoveNode1 = NULL;
    m_pTextLevelMax = NULL;
    m_pFightPower = NULL;
    m_pTextTalent2 = NULL;
    m_pNodeTalent = NULL;
    m_pTextAttack	 = NULL;
    m_pTextLife	 = NULL;
    m_pTextTalent	 = NULL;
    m_pStar[0]	 = NULL;
    m_pStar[1]	 = NULL;
    m_pStar[2]	 = NULL;
    m_pStar[3]	 = NULL;
    m_pStar[4]	 = NULL;
    m_pStar[5]	 = NULL;
    m_pStar[6]	 = NULL;
//    m_pExpBar	 = NULL;
    m_pTextPetName	 = NULL;
    m_pTextLevel	 = NULL;
    m_pData = NULL;
    m_pPetCard = NULL;
    m_pTTFDesc = NULL;
    MB_LayerRoleInfoHeader::setMenuEnable(false,"MB_LayerPetDetail");
    m_nShowRank = 0;
    m_bChangeState = false;
    for (uint8_t i=0; i<14; ++i)
    {
        m_pAttribute[i] = NULL;
    }
    
    m_bShowRoleInfoPanel = true;
    isLayerCommandVis = false;
    CCNode* n = CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND);
    if (n) {
        isLayerCommandVis = ((MB_LayerCommand*)n)->rootNode->isVisible();
        if (isLayerCommandVis) {
            ((MB_LayerCommand*)n)->rootNode->setVisible(false);
        }
    }
    
    SOCKET_MSG_REGIST(SC_ROLE_CHANGE_HEAD, MB_LayerPetDetail);
    SOCKET_MSG_REGIST(SC_ITEM_UP_ALL_EQUIP, MB_LayerPetDetail);
    
}
MB_LayerPetDetail::~MB_LayerPetDetail()
{
    
    for (int i=0 ;i< EQUIP_MAX; i++) {
        CC_SAFE_RELEASE_NULL(m_pZBBtn[i]);
    }
    global_layerPetDetail = NULL;
    
    CC_SAFE_RELEASE_NULL(m_pMoveEquipNode);
    CC_SAFE_RELEASE_NULL(m_pZDZBBtn);
    CC_SAFE_RELEASE_NULL(m_pJHBtn);
    CC_SAFE_RELEASE_NULL(m_pTQBtn);
    CC_SAFE_RELEASE_NULL(m_pQHBtn);
    CC_SAFE_RELEASE_NULL(m_pLikeMenu);
    CC_SAFE_RELEASE_NULL(m_pLeft);
    CC_SAFE_RELEASE_NULL(m_pRight);
    CC_SAFE_RELEASE_NULL(m_pJusesejianjie);
    CC_SAFE_RELEASE_NULL(m_pNode1);
    CC_SAFE_RELEASE_NULL(m_pNode2);
    CC_SAFE_RELEASE_NULL(m_pNode3);
    CC_SAFE_RELEASE_NULL(m_pMoveNode1);
    CC_SAFE_RELEASE_NULL(m_pTextLevelMax);
    CC_SAFE_RELEASE_NULL(m_pFightPower);
    CC_SAFE_RELEASE_NULL(m_pTextTalent2);
    CC_SAFE_RELEASE_NULL(m_pNodeTalent);
    CC_SAFE_RELEASE_NULL(m_pTextAttack);
    CC_SAFE_RELEASE_NULL(m_pTextLife);
    CC_SAFE_RELEASE_NULL(m_pTextTalent);
    CC_SAFE_RELEASE_NULL(m_pStar[0]);
    CC_SAFE_RELEASE_NULL(m_pStar[1]);
    CC_SAFE_RELEASE_NULL(m_pStar[2]);
    CC_SAFE_RELEASE_NULL(m_pStar[3]);
    CC_SAFE_RELEASE_NULL(m_pStar[4]);
    CC_SAFE_RELEASE_NULL(m_pStar[5]);
    CC_SAFE_RELEASE_NULL(m_pStar[6]);
//    CC_SAFE_RELEASE_NULL(m_pExpBar);
    CC_SAFE_RELEASE_NULL(m_pTextPetName);
    CC_SAFE_RELEASE_NULL(m_pTextLevel);
    CC_SAFE_RELEASE_NULL(m_pData);
    CC_SAFE_RELEASE_NULL(m_pPetCard);
    CC_SAFE_RELEASE_NULL(m_pTTFDesc);
    MB_LayerRoleInfoHeader::setMenuEnable(true,"MB_LayerPetDetail");
    if (global_layerPetEquipment!=NULL) {
        global_layerPetEquipment->setMyTouchEnable(true);
        global_layerPetEquipment->reloadZhuangbeiIndexVec();
    }
    
    
    for (uint8_t i=0; i<14; ++i)
    {
        CC_SAFE_RELEASE_NULL(m_pAttribute[i]);
    }
    SOCKET_MSG_UNREGIST(SC_ROLE_CHANGE_HEAD);
    SOCKET_MSG_UNREGIST(SC_ITEM_UP_ALL_EQUIP);
    if (isLayerCommandVis) {
        CCNode* n = CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND);
        if (n) ((MB_LayerCommand*)n)->rootNode->setVisible(true);
    }
}
bool MB_LayerPetDetail::init()
{
    global_layerPetDetail = this;
    CCNode* pNode = loadResource("res/card_layer_info.ccbi");
    if(pNode)
	{
        addChild(NSGameHelper::createDisableTouchLayer());
		addChild(pNode);

        leftP = m_pLeft->getPosition();
        rightP = m_pRight->getPosition();
        
        uint32_t HeadID = MB_RoleData::getInstance()->getHead();
        
		return true;
	}
	return false;
}

void MB_LayerPetDetail::setAllBtnShowFalse()
{
    isShowAllBtn = false;
    m_pLikeMenu->setVisible(false);
    m_pZDZBBtn->setVisible(false);
    m_pJHBtn->setVisible(false);
    m_pTQBtn->setVisible(false);
    m_pQHBtn->setVisible(false);
    for (int i=0; i< EQUIP_MAX; i++) {
        m_pZBBtn[i]->setVisible(false);
    }
}
void MB_LayerPetDetail::setZhuangBei()
{
    if (!isShowAllBtn) {
        m_pLikeMenu->setVisible(false);
        m_pZDZBBtn->setVisible(false);
        m_pJHBtn->setVisible(false);
        m_pTQBtn->setVisible(false);
        m_pQHBtn->setVisible(false);
        for (int i=0; i< EQUIP_MAX; i++) {
            m_pZBBtn[i]->setVisible(false);
        }
    }else
    {
        tdata = MB_TeamData::getInstance()->checkInTeamData(m_pData);
        if (tdata!=NULL) {
            setItemShow(tdata->m_pEquip1,0);
            setItemShow(tdata->m_pEquip2,1);
            setItemShow(tdata->m_pEquip3,2);
            setItemShow(tdata->m_pTreasure1,3);
            setItemShow(tdata->m_pTreasure2,4);
            setItemShow(tdata->m_pTreasure3,5);
        }else
        {
            for (int i=0; i< EQUIP_MAX; i++) {
                m_pZBBtn[i]->setVisible(false);
            }
            m_pZDZBBtn->setVisible(false);
        }
    }
}
MB_LayerPetDetail* MB_LayerPetDetail::create(MB_PetData* pData,bool isSubLayer)
{
    MB_LayerPetDetail* pInstance = MB_LayerPetDetail::create();
    pInstance->isShowAllBtn = true;
    if(pInstance && pInstance->setData(pData))
    {
        pInstance->m_bIsSubLayer = isSubLayer;
        return pInstance;
    }
    
    return NULL;
}
MB_ResWindow* MB_LayerPetDetail::createWithPetID(int64_t petId)
{
    MB_PetData* pData = MB_PetMgr::getInstance()->getPetDataByUID(petId);
    return MB_LayerPetDetail::create(pData);
}

//参数petType 10进制的最后位表示宠物形态  除最后位表示宠物ID
MB_ResWindow* MB_LayerPetDetail::create(int32_t petType,uint16_t shape)
{
    MB_PetTemplate* pTemp = MB_PetMgr::getInstance()->getPetTemplateByID(petType);
    if (pTemp)
    {
        MB_PetData* pData = MB_PetMgr::createInstance(pTemp,(shape-1)*10);
        return MB_LayerPetDetail::create(pData);
    }
    return NULL;
}

bool MB_LayerPetDetail::setData(MB_PetData* pData)
{
    if(pData == NULL)
    {
        return false;
    }
    SOCKET_REQUEST_START(CS_GER_DETAIL);
    packet->WriteUINT64(pData->getPetID());
    SOCKET_REQUEST_END(SC_GER_DETAIL,MB_LayerPetDetail::onMsgRecv);
    
    CC_SAFE_RELEASE_NULL(m_pData);
    m_pData = pData;
    m_pData->retain();
    m_nShowRank = m_pData->getPetQuallity();

    resetBaseInfo();
    
    m_nHeadID = m_pData->getTemplete()->getPetTypeID()+SHAPE_1*SHAPE_BASE;
    if (m_nHeadID==MB_RoleData::getInstance()->getHead()) {
        m_pLikeMenu->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tmzz_btn_like_2.png"));
        m_pLikeMenu->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tmzz_btn_like_2.png"));
    }
    
    setZhuangBei();
    return true;
}

void MB_LayerPetDetail::onResetWnd()
{
    if (isUpdateUI) {
        isUpdateUI = false;
        resetBaseInfo();
        setZhuangBei();
    }
}

const char* equipImageNameA[6] = {"tmzz_equip_weapon.png","tmzz_equip_fang.png","tmzz_equip_hat.png","tmzz_equip_neck.png","tmzz_equip_accessory.png","tmzz_equip_luk.png"};
void MB_LayerPetDetail::setItemShow(MB_ItemData* data, int index)
{
    m_pZBBtn[index]->removeAllChildrenWithCleanup(true);
    if(data == NULL){
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("juesexiangqing.plist");
        CCSprite* spr = CCSprite::createWithSpriteFrameName(equipImageNameA[index]);
        spr->setPosition(m_pZBBtn[index]->getPreferredSize()/2);
        m_pZBBtn[index]->addChild(spr);
        return;
    }
    CCNode* pNode = CCNode::create();
    pNode->setPosition(m_pZBBtn[index]->getPreferredSize()/2);
    pNode->setScale(.72f);
    m_pZBBtn[index]->addChild(pNode);
    MB_NodeItem * node = MB_NodeItem::create(data->getItemUID(),kNINWNONE);
    node->setOnClickEnable(false);
    pNode->addChild(node);
    //如果套装被激活，显示套装效果
    if(MB_TeamData::getInstance()->checkSuitActivate(data,tdata))
    {
        CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
        CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
        CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/eff_node_suit.ccbi");
        pNode->setPosition(m_pZBBtn[index]->getPreferredSize()/2);
        pNode->setScale(.55f);
        m_pZBBtn[index]->addChild(pNode);
        CC_SAFE_RELEASE_NULL(pCCBReader);
    }
}
void MB_LayerPetDetail::setStar(uint8_t nStar)
{
    for (uint8_t i=nStar; i<MAX_GER_STAR; ++i)
    {
        m_pStar[i]->setVisible(false);
    }
}
void MB_LayerPetDetail::resetBaseInfo()
{
    if(m_pData)
    {
        MB_PetTemplate* p = m_pData->getTemplete();
        if (p)
        {
            m_nShowRank = m_pData->getPetQuallity();
            char buff[32] = {};
            const char* pFile = p->getPetCard(NSGameHelper::getShapeTypeByRank(m_nShowRank));
            NSGameHelper::setSpriteFrame(m_pPetCard, pFile);
            
            if (m_pData->getPetQuallity()%10 == 0) {
                 sprintf(buff,"%s",p->getPetName(NSGameHelper::getShapeTypeByRank(m_nShowRank)));
            }
            else
            {
                sprintf(buff,"%s+%d",p->getPetName(NSGameHelper::getShapeTypeByRank(m_nShowRank)),m_nShowRank%10);
            }
            
            m_pTextPetName->setString(buff);
            
            sprintf(buff, "%d",m_pData->getPetLevel());
            m_pTextLevel->setString(buff);
            m_pMoveNode1->setPositionX((NSGameHelper::get_length(m_pData->getPetLevel())-2)*8);
            sprintf(buff, " / %d", MB_RoleData::getInstance()->getLevel()*2);
            m_pTextLevelMax->setString(buff);
            m_pTextPetName->setPositionX(9.2f+(NSGameHelper::get_length(MB_RoleData::getInstance()->getLevel()*2)-2)*6);
            
            setStar(p->getPetStar());
            
            sprintf(buff, "%llu",m_pData->getPetFightPower());
            m_pFightPower->setString(buff);
            sprintf(buff, "%d",m_pData->getPetAttack());
            m_pTextAttack->setString(buff);
            sprintf(buff, "%d",m_pData->getPetHpMax());
            m_pTextLife->setString(buff);
            
            std::string talent = "";
            std::string talent2 = "";
            CCObject * attribute;
            CCARRAY_FOREACH(p->getTalentList(), attribute)
            {
                MB_DestinyAttribute * talentAttribute = (MB_DestinyAttribute *)attribute;
                
                if (talentAttribute->getType() == 1 || talentAttribute->getType() ==2
                    || talentAttribute->getType() == 11
                    || talentAttribute->getType() == 12) {
                    
                    continue;
                }
                char str[40] ;
                sprintf(str,"%s",talentAttribute->getName());
                talent = talent + str;
                if (talentAttribute->getType() == 13 || talentAttribute->getType() == 14)
                {
                    sprintf(str,"%.0f%%",talentAttribute->getValue()/100.0f);
                }
                else
                {
                    sprintf(str,"%.0f",talentAttribute->getValue());
                }
                talent2 = talent2 + str;
            }
            m_pTextTalent->setString(talent.c_str());
            m_pTextTalent2->setString(talent2.c_str());
            m_pNodeTalent->setPositionX((48-m_pTextTalent2->getContentSize().width)*m_pTextTalent2->getScaleX());
            
            
            if (m_pData->getPetID() == 0 || !MB_TeamData::getInstance()->checkInTeam(m_pData))
            {
                installAttribute(m_pData->getTemplete()->getTalentList());
            }
            else
            {

            }
            m_pTTFDesc->setString(p->getPetDescription());
        }
    }
}
void MB_LayerPetDetail::installAttribute(CCArray* pArray)
{
    char buff[64] = {};
    float dataNum = 0;
    MB_DestinyAttribute * obj = NULL;
    for (int i = 0; i < 14 ; i++)
    {
        dataNum = 0;
        CCARRAY_FOREACH_4TYPE(pArray, MB_DestinyAttribute *, obj)
        {
            if(obj->getType() == (i+3))
            {
                dataNum = ((MB_DestinyAttribute *)obj)->getValue();
                break;
            }
        }
        
        if (i == 10 || i == 11)
        {
            sprintf(buff, "%.0f%%",dataNum/100.0f);
        }
        else
        {
            sprintf(buff, "%.0f",dataNum);
        }
        m_pAttribute[i]->setString(buff);
    }
    
}
void MB_LayerPetDetail::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    
    //将socket数据读取到序列化结构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg)
    {
        case SC_GER_DETAIL:
            MB_Message::sharedMB_Message()->removeALLMessage();
            recvpet_detail(recvPacket);
            SOCKET_MSG_UNREGIST(SC_GER_DETAIL);
            break;
        case SC_ROLE_CHANGE_HEAD:
        {
            uint8_t data8 = 0;
            uint32_t data32 = 0;
            recvPacket->readU8(&data8);
            recvPacket->readU32(&data32);
            if (data8 == 1)//換頭像成功
            {
                MB_RoleData::getInstance()->setHead(data32);
                CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("juesexiangqing.plist");
                m_pLikeMenu->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tmzz_btn_like_2.png"));
                m_pLikeMenu->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tmzz_btn_like_2.png"));
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
        }
            break;
        case SC_ITEM_UP_ALL_EQUIP:
        {
            uint8_t result;
            recvPacket->readU8(&result);
            if (result == 0)
            {
                isUpdateUI = true;
                onResetWnd();
            }
            else if(result == 1)
            {
                MB_Message::sharedMB_Message()->showMessage("没有可穿戴装备");
            }
            else if(result == 2)
            {
                MB_Message::sharedMB_Message()->showMessage("装备已佩戴齐全");
            }
        }
            break;
    }

}
void MB_LayerPetDetail::recvpet_detail(MB_MsgBuffer* pRecv)
{
    uint64_t uid = 0;
    pRecv->readU64(&uid);
    if (uid != m_pData->getPetID())
    {
        return;
    }
    
    MB_DestinyAttribute* attr = NULL;
    uint16_t value = 0;
    CCArray* p = m_pData->getOnlineAttribute();
    p->removeAllObjects();
    static const uint8_t types[] = {11,12,7,8,9,10,13,14,15,16,3,4,5,6};
    for (uint8_t i=0; i<14; ++i)
    {
        attr = new MB_DestinyAttribute;
        pRecv->readU16(&value);
        attr->setValue(value);
        attr->setType(types[i]);
        p->addObject(attr);
        CC_SAFE_RELEASE_NULL(attr);
    }
    
    installAttribute(m_pData->getOnlineAttribute());
}

bool MB_LayerPetDetail::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    TutorialAssignLayerWindow
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTextLevelMax",CCLabelBMFont*,m_pTextLevelMax);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTextAttack",CCLabelBMFont*,m_pTextAttack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTextLife",CCLabelBMFont*,m_pTextLife);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTextTalent",CCLabelBMFont*,m_pTextTalent);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTextTalent2",CCLabelBMFont*,m_pTextTalent2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pFightPower",CCLabelBMFont*,m_pFightPower);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pPetCard",CCSprite*,m_pPetCard);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"star0",CCSprite*,m_pStar[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"star1",CCSprite*,m_pStar[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"star2",CCSprite*,m_pStar[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"star3",CCSprite*,m_pStar[3]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"star4",CCSprite*,m_pStar[4]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"star5",CCSprite*,m_pStar[5]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"star6",CCSprite*,m_pStar[6]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMoveEquipNode", CCNode*, m_pMoveEquipNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTextPetName",CCLabelTTF*,m_pTextPetName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTextLevel",CCLabelBMFont*,m_pTextLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTTFDesc",CCLabelTTF*, m_pTTFDesc);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeTalent", CCNode*, m_pNodeTalent);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMoveNode1", CCNode*, m_pMoveNode1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pZDZBBtn", CCNode*, m_pZDZBBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pJHBtn", CCNode*, m_pJHBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTQBtn", CCNode*, m_pTQBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pQHBtn", CCNode*, m_pQHBtn);
    char buff[32] = {};
    for (uint8_t i=0; i<14; ++i)
    {
        sprintf(buff,"attribute%d",i+1);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, buff,CCLabelBMFont*, m_pAttribute[i]);
    }
    for (int i=0 ;i< EQUIP_MAX; i++) {
        sprintf(buff,"m_pZBBtn%d",i+1);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, buff,CCControlButton*, m_pZBBtn[i]);
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pJusesejianjie", CCMenuItemImage*, m_pJusesejianjie);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNode1", CCNode*, m_pNode1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNode2", CCNode*, m_pNode2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNode3", CCNode*, m_pNode3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLeft", CCNode*, m_pLeft);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pRight", CCNode*, m_pRight);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLikeMenu", CCMenuItemImage*, m_pLikeMenu);
    
    
    return false;
}
SEL_MenuHandler MB_LayerPetDetail::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerPetDetail::onCloseClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onLikeClick",MB_LayerPetDetail::onLikeClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onJianShangClick",MB_LayerPetDetail::onJianShangClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onSkillClick",MB_LayerPetDetail::onSkillClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onZuHeSkillClick",MB_LayerPetDetail::onZuHeSkillClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onqianghuaClick",MB_LayerPetDetail::onqianghuaClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"ontiquClick",MB_LayerPetDetail::ontiquClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onjinhuaClick",MB_LayerPetDetail::onjinhuaClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onZidongzhuangbeiClick",MB_LayerPetDetail::onZidongzhuangbeiClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onJuesejianjieClick",MB_LayerPetDetail::onJuesejianjieClick);
    return NULL;
}
SEL_CCControlHandler MB_LayerPetDetail::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onWeaponClick",MB_LayerPetDetail::onWeaponClick);
	return NULL;
}
void MB_LayerPetDetail::onCloseClick(CCObject* pSender)
{
    TutorialTriggerComplete
    if (isOn) {
        if (m_bIsSubLayer) {
            MB_FunctionMgr::getInstance()->goFunction(kFunctionHome, this);
        }else
        {
            popWindow(true);
        }
    }else
    {
        onAndOffBtn();
    }
}

void MB_LayerPetDetail::onJuesejianjieClick(CCObject * pTarget)
{
    if (m_pNode3->isVisible()) {
        m_pNode1->setPositionY(661.1f);
        m_pNode2->setVisible(true);
        m_pNode3->setVisible(false);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("juesexiangqing.plist");
        m_pJusesejianjie->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tmzz_btn_info_char.png"));
        m_pJusesejianjie->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tmzz_btn_info_char.png"));
    }else
    {
        m_pNode1->setPositionY(477.1f);
        m_pNode2->setVisible(false);
        m_pNode3->setVisible(true);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("juesexiangqing.plist");
        m_pJusesejianjie->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tmzz_btn_profile.png"));
        m_pJusesejianjie->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tmzz_btn_profile.png"));
    }
}
void MB_LayerPetDetail::onJianShangClick(CCObject * pTarget)
{
    onAndOffBtn();
}
void MB_LayerPetDetail::onAndOffBtn()
{
    isOn = !isOn;
    MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
    CCNode* lrih =pScene->m_pLayerRoleInfoHeader;
    if (isOn) {
        m_pLeft->runAction(CCMoveTo::create(.3f, leftP));
        m_pRight->runAction(CCMoveTo::create(.3f, rightP));
        lrih->runAction(CCMoveTo::create(.3f, ccp(0,0)));
        m_pMoveEquipNode->runAction(CCMoveTo::create(.3f, ccp(0,0)));
    }else
    {
        m_pLeft->setPositionX(leftP.x-450);
        m_pRight->setPositionX(rightP.x+200);
        lrih->setPositionY(200);
        m_pMoveEquipNode->setPositionX(-500);
    }
}
void MB_LayerPetDetail::onLikeClick(CCObject * pTarget)
{
    nowHomeShowPetTypeID = m_pData->getPetTypeID();
    CCUserDefault::sharedUserDefault()->setIntegerForKey("HomeShowPetTypeID", nowHomeShowPetTypeID);
    sendrole_change_head(m_nHeadID);
}
bool MB_LayerPetDetail::sendrole_change_head(uint32_t headID)
{
    SOCKET_REQUEST_START(CS_ROLE_CHANGE_HEAD);
    packet->writeU32(headID);
    SOCKET_REQUEST_END(SC_ROLE_CHANGE_HEAD, MB_LayerPetDetail::onMsgRecv);
    return true;
}

void MB_LayerPetDetail::onSkillClick(CCObject * pTarget)
{
    MB_SkillDetail* layer;
    if (m_pData->getPetID()==0) {
        layer = MB_SkillDetail::create(m_pData->getPetTypeID(),1);
    }else
    {
        layer = MB_SkillDetail::create(m_pData->getPetID(),1);
    }
    if (layer != NULL)
    {
        this->addChild(layer);
    }
}
void MB_LayerPetDetail::onZuHeSkillClick(CCObject * pTarget)
{
    MB_SkillDetail* layer;
    if (m_pData->getPetID()==0) {
        layer = MB_SkillDetail::create(m_pData->getPetTypeID(),2);
    }else
    {
        layer = MB_SkillDetail::create(m_pData->getPetID(),2);
    }
    if (layer != NULL)
    {
        this->addChild(layer);
    }
}
void MB_LayerPetDetail::onqianghuaClick(CCObject * pTarget)
{
    MB_LayerPetUpdate* layer = MB_LayerPetUpdate::create(m_pData->getPetID());
    if (layer != NULL) {
        
        this->pushWindow(layer, true);
    }
}
void MB_LayerPetDetail::ontiquClick(CCObject * pTarget)
{
    if (m_pData->getPetQuallity() == 0) {
        MB_Message::sharedMB_Message()->showMessage("该卡牌进化等级为0，无法提取");
    }else
    {
        MB_LayerPetRestore* layer = MB_LayerPetRestore::create(m_pData->getPetID());
        if (layer)
        {
            this->pushWindow(layer,true);
        }
    }
}
void MB_LayerPetDetail::onjinhuaClick(CCObject * pTarget)
{
    MB_LayerPetEnhance* layer = MB_LayerPetEnhance::create(kPetEnhanceEntrDetail, m_pData->getPetID());
    if (layer != NULL){
        
        this->pushWindow(layer,true);
    }
}
void MB_LayerPetDetail::onZidongzhuangbeiClick(CCObject * pTarget)
{
    uint8_t index = MB_TeamData::getInstance()->getPetPosByPetID(m_pData->getPetID());
    TeamDataStruct* teamStruct = MB_TeamData::getInstance()->getTeamMemberByIndex(index);
    if (tdata != NULL && tdata->m_pPet != NULL)
    {
        MB_Message::sharedMB_Message()->showMessage("",10);
        MB_TeamData::getInstance()->senditem_up_all_equip(tdata->m_pPet->getPetID());
    }
}


void MB_LayerPetDetail::onWeaponClick(CCObject * pTarget)
{
    TutorialTriggerComplete
    CCNode* node = (CCNode*)pTarget;
    int tag = node->getTag();
    
    uint8_t index = MB_TeamData::getInstance()->getPetPosByPetID(m_pData->getPetID());
    TeamDataStruct* teamStruct = MB_TeamData::getInstance()->getTeamMemberByIndex(index);
    MB_LayerListEquipChange* layer = NULL;
    uint64_t ItemUID;
    switch (tag) {
        case 1:
            ItemUID = teamStruct->m_pEquip1==NULL?0:teamStruct->m_pEquip1->getItemUID();
            break;
        case 2:
            ItemUID = teamStruct->m_pEquip2==NULL?0:teamStruct->m_pEquip2->getItemUID();
            break;
        case 3:
            ItemUID = teamStruct->m_pEquip3==NULL?0:teamStruct->m_pEquip3->getItemUID();
            break;
        case 4:
            ItemUID = teamStruct->m_pTreasure1==NULL?0:teamStruct->m_pTreasure1->getItemUID();
            break;
        case 5:
            ItemUID = teamStruct->m_pTreasure2==NULL?0:teamStruct->m_pTreasure2->getItemUID();
            break;
        case 6:
            ItemUID = teamStruct->m_pTreasure3==NULL?0:teamStruct->m_pTreasure3->getItemUID();
            break;
    }
    m_nZBItemPos = ipt[tag-1];
    if (ItemUID == 0) {
        layer = MB_LayerListEquipChange::create(klit[tag-1], ipt[tag-1], ItemUID, teamStruct->m_pPet->getPetID());
        this->pushWindow(layer, true);
    }else
    {
        MB_LayerItemDetail* layer = MB_LayerItemDetail::create(ItemUID,KRENWUXIANGQING);
        layer->detail_type = klit[tag-1];
        layer->detail_itemPos = ipt[tag-1];
        layer->detail_petID = teamStruct->m_pPet->getPetID();
        MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
        if (pScene)
        {
            pScene->addChild(layer,Z_ORDER_Detail);
        }else
        {
            CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
        }
    }

}
