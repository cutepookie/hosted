//
//  MB_LayerGuard.cpp
//  ProjectMB
//
//  Create by wenyong on 3/3/2015.
//
//
#include "MB_LayerGuard.h"
#include "MB_TeamData.h"
#include "MB_PetData.h"
#include "MB_NodePetAid.h"
#include "MB_LayerFunctionRule.h"
#include "MB_GuardInterface.h"
#include "MB_NodePet.h"
#include "MB_NodePetList.h"
#include "MB_NodePetDuiWuFang.h"
#include "MB_ScrollBg.h"
#include "MB_NodeYaoLingDuiWu.h"
#include "MB_NodeYaoLingChoose.h"
#include "MB_LayerPetEquipment.h"
#include "MB_LayerCommand.h"
static const std::string guardAttName[] =
{
    "",
    "攻击",
    "生命",
    "初始能量",
    "能量上限",
    "暴击",   //5
    "韧性",
    "命中",
    "闪避",
    "%吸血",
    "%反弹",  //10
    "击晕",
    "抗晕",
    "破甲",
    "护甲",
    "法穿",   //15
    "法抗",
    "%攻击",
    "%生命",
};

bool compare_lg(CCObject *_petData1,CCObject *_petData2)
{
    MB_PetData* petData1 = (MB_PetData*)_petData1;
    MB_PetData* petData2 = (MB_PetData*)_petData2;
    if (petData1->getTemplateStar() > petData2->getTemplateStar())return true;
    else if (petData1->getTemplateStar() < petData2->getTemplateStar())return false;
    if (petData1->getPetLevel() > petData2->getPetLevel())return true;
    else if (petData1->getPetLevel() < petData2->getPetLevel())return false;
    if (petData1->getPetQuallity() > petData2->getPetQuallity())return true;
    else if (petData1->getPetQuallity() < petData2->getPetQuallity())return false;
    if (petData1->getPetTypeID() > petData2->getPetTypeID())return true;
    else if (petData1->getPetTypeID() < petData2->getPetTypeID())return false;
    return false;
}
MB_LayerGuard::MB_LayerGuard()
{
    m_nListSize = 0;
    m_objUnitSize = MB_NodeYaoLingChoose::create(0)->getCellSize();
    m_pNodeScroller = NULL;
    m_pTTFCost	 = NULL;
    m_pScrollsize = NULL;
    m_pTTFAttribute[0]	 = NULL;
    m_pTTFAttribute[1]	 = NULL;
    m_pTTFAttribute[2] = NULL;
    m_pTTFAttribute[3] = NULL;
    m_bShowRoleInfoPanel = true;
    isHomeButtonShow =  ((MB_LayerCommand*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND))->rootNode->isVisible();
    ((MB_LayerCommand*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND))->rootNode->setVisible(false);
    m_pArray = new CCArray();
    for (int i = 0;i < CARD_IN_GAME;i++)
    {
        m_pTTFAttributeEX[i] = NULL;
        m_pMenuLock[i] = NULL;
        m_bLock[i] = false;
        m_pNodeLock[i] = NULL;
        m_pYlNode[i] = NULL;
    }
    m_nSelectIndex = -1;
    
    SOCKET_MSG_REGIST(SC_PET_GUARD_INFO,MB_LayerGuard);
    SOCKET_MSG_REGIST(SC_PET_GUARD_SET,MB_LayerGuard);
    SOCKET_MSG_REGIST(SC_PET_GUARD_REFRESH,MB_LayerGuard);
}
MB_LayerGuard::~MB_LayerGuard()
{
    CC_SAFE_RELEASE_NULL(m_pNodeScroller);
    CC_SAFE_RELEASE_NULL(m_pTTFCost);
    CC_SAFE_RELEASE_NULL(m_pTTFAttribute[0]);
    CC_SAFE_RELEASE_NULL(m_pTTFAttribute[1]);
    CC_SAFE_RELEASE_NULL(m_pTTFAttribute[2]);
    CC_SAFE_RELEASE_NULL(m_pTTFAttribute[3]);
    CC_SAFE_RELEASE(m_pArray);
    for (int i = 0;i < CARD_IN_GAME;i++)
    {
        CC_SAFE_RELEASE_NULL(m_pTTFAttributeEX[i]);
        CC_SAFE_RELEASE_NULL(m_pMenuLock[i]);
        CC_SAFE_RELEASE_NULL(m_pNodeLock[i]);
        CC_SAFE_RELEASE_NULL(m_pYlNode[i]);
    }
    CC_SAFE_RELEASE_NULL(m_pScrollsize);
    
    SOCKET_MSG_UNREGIST(SC_PET_GUARD_INFO);
    SOCKET_MSG_UNREGIST(SC_PET_GUARD_SET);
    SOCKET_MSG_UNREGIST(SC_PET_GUARD_REFRESH);
}

MB_LayerGuard* MB_LayerGuard::create(int index)
{
    MB_LayerGuard* ptr = new MB_LayerGuard();
    if (ptr && ptr->init(index)) {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE(ptr);
    return NULL;
}
bool MB_LayerGuard::init(int index)
{
    CCNode* pNode = loadResource("res/card_layer_guard.ccbi");
    if(pNode)
    {
        addChild(pNode);
        m_nSelectIndex = index;
        
        m_pNodeScroller->removeAllChildren();
        MB_NodePetDuiWuFang* npdw;
        if(teamV.size()==0)
        {
            for (int i =0; i<MEMBER_NUM; i++) {
                if (MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet == NULL) {
                    teamV[i] = -1;
                }else
                {
                    TeamDataStruct* ts = MB_TeamData::getInstance()->getTeamMemberByIndex(i);
                    teamV[i] = ts->m_pPet->getPetID();
                }
            }
        }
        for (int i = 0; i < CARD_IN_GAME; i++) {
            npdw = MB_NodePetDuiWuFang::create(teamV[i]);
            npdw->setPosition(ccp( 68+100*i,m_pNodeScroller->getContentSize().height/2));
            npdw->setParent(this, i);
            m_pNodeScroller->addChild(npdw);
        }
//        m_pNodeScroller->setContentSize(CCSize( npdw->m_nWidth*6,m_pNodeScroller->getContentSize().height));
        
        m_pTableView = CCTableView::create(this, m_pScrollsize->getContentSize());
        m_pTableView->setDirection(kCCScrollViewDirectionVertical);
        m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        m_pScrollsize->addChild( m_pTableView);
        
        onResetWnd();
        
        pNode->addChild(MB_ScrollBg::create(left_top, 0.5f), -1);
        return true;
    }
    return false;
}
void MB_LayerGuard::onResetWnd()
{
    setSelectPetID(m_nSelectIndex,true);
}

void MB_LayerGuard::onResetShow()
{
    if (teamV[m_nSelectIndex] != -1)
    {
        reloadArray();
        m_pTableView->setVisible(true);
        m_pTableView->reloadData();
    }
    else {
        m_pTableView->setVisible(false);
    }
    bool isSetProp = false;
    for (int i = 0;i < CARD_IN_GAME;i++)
    {
        m_pYlNode[i]->removeAllChildren();
        //重置守护
        MB_NodeYaoLingDuiWu* node = MB_NodeYaoLingDuiWu::create(i);
        node->m_pLg = this;
        m_pYlNode[i]->addChild(node);
        if (i==m_nSelectIndex) {
            node->m_pSelectSpr->setVisible(true);
        }
        MB_PetGuardData* pData = MB_GuardInterface::getInstance()->getPetGuardDataByPos(i+1);
        if (pData != NULL)
        {
            if (i==m_nSelectIndex) {
                isSetProp = true;
                //重置属性
                //基础属性
                CCArray* array = pData->getBaseAttrArray();
                for (int i = 0;i < 4;i++)
                {
                    if (i < array->count())
                    {
                        MB_PetGuardAttr* attr = dynamic_cast<MB_PetGuardAttr*>(array->objectAtIndex(i));
                        char str[128];
                        
                        if(attr->getAttrType() == 17 || attr->getAttrType() == 18 || attr->getAttrType() == 9 ||attr->getAttrType() == 10)  //万分比
                        {
                            if (i >= 2)
                            {
                                sprintf(str,"(+%.2f%s)",attr->getAddValue()/100.f,guardAttName[attr->getAttrType()].c_str());
                            }
                            else
                            {
                                sprintf(str,"+%.2f%s",attr->getAddValue()/100.f,guardAttName[attr->getAttrType()].c_str());
                            }
                            
                        }
                        else
                        {
                            if (i%2  >= 2)
                            {
                                sprintf(str,"(+%d%s)",attr->getAddValue(),guardAttName[attr->getAttrType()].c_str());
                            }
                            else
                            {
                                sprintf(str,"+%d%s",attr->getAddValue(),guardAttName[attr->getAttrType()].c_str());
                            }
                            sprintf(str,"+%d%s",attr->getAddValue(),guardAttName[attr->getAttrType()].c_str());
                        }
                        m_pTTFAttribute[i]->setString(str);
                        if (i < 2)
                        {
                            //设置品级颜色
                            MB_PetTemplate* guardPetTemplate = MB_PetMgr::getInstance()->getPetTemplateByUID(pData->getPetUid());
                            NSGameHelper::setColorByStar(m_pTTFAttribute[i], guardPetTemplate->getPetStar());
                        }
                        else
                        {
                            m_pTTFAttribute[i]->setColor(ccc3(185,230,30));
                        }
                    }
                    else
                    {
                        m_pTTFAttribute[i]->setString("未激活");
                        m_pTTFAttribute[i]->setColor(ccc3(106, 106, 106));
                    }
                    
                }
                //高级属性
                array = pData->getHighAttrArray();
                for (int i = 0;i < GUARD_ATTR_MAX;i++)
                {
                    if (i < array->count())
                    {
                        //显示锁
                        m_pNodeLock[i]->setVisible(true);
                        MB_PetGuardAttr* attr = dynamic_cast<MB_PetGuardAttr*>(array->objectAtIndex(i));
                        char str[128];
                        if(attr->getAttrType() == 17 || attr->getAttrType() == 18 || attr->getAttrType() == 9 ||attr->getAttrType() == 10) //万分比
                        {
                            sprintf(str,"+%.2f%s",attr->getAddValue()/100.f,guardAttName[attr->getAttrType()].c_str());
                        }
                        else
                        {
                            sprintf(str,"+%d%s",attr->getAddValue(),guardAttName[attr->getAttrType()].c_str());
                        }
                        m_pTTFAttributeEX[i]->setString(str);
                        
                        //设置品级颜色
                        NSGameHelper::setColorByStar(m_pTTFAttributeEX[i], MB_GuardInterface::getInstance()->getRankByValAndType(attr->getAddValue(), attr->getAttrType()));
                    }
                    else
                    {
                        //隐藏锁
                        m_pNodeLock[i]->setVisible(false);
                        
                        m_pTTFAttributeEX[i]->setString("未激活");
                        m_pTTFAttributeEX[i]->setColor(ccc3(106, 106, 106));
                    }
                    
                }
            }
        }
    }

    if (!isSetProp)
    {
        m_pTTFAttribute[0]->setString("未激活");
        m_pTTFAttribute[1]->setString("未激活");
        m_pTTFAttribute[0]->setColor(ccc3(106, 106, 106));
        m_pTTFAttribute[1]->setColor(ccc3(106, 106, 106));
        for (int i = 0;i < GUARD_ATTR_MAX;i++)
        {
            m_pTTFAttributeEX[i]->setString("未激活");
            m_pTTFAttributeEX[i]->setColor(ccc3(106, 106, 106));
            //隐藏锁
            m_pNodeLock[i]->setVisible(false);
        }
    }
    
    //显示消耗
    char str[32];
    sprintf(str,"%d",MB_GuardInterface::getInstance()->getCostByLockNum(getLockNum()));
    m_pTTFCost->setString(str);
}

void MB_LayerGuard::setSelectPetID(int index,bool isF)
{
    if (m_nSelectIndex==index && !isF) {
        return;
    }
//    if (teamV[index] != -1)
    {
        m_nSelectIndex = index;
        //重置锁定
        for (int i = 0;i < CARD_IN_GAME;i++)
        {
            m_bLock[i] = false;
            m_pMenuLock[i]->setEnabled(true);
            
        }
        onResetShow();
    }
}


void MB_LayerGuard::onMsgRecv(CCNode* node, SocketResponse* response)
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
    
    MB_Message::sharedMB_Message()->removeALLMessage();
    switch (Msg)
    {
        case SC_PET_GUARD_INFO:
            onResetShow();
            if (global_layerPetEquipment!=NULL) {
                global_layerPetEquipment->isUpdateUI = true;
                global_layerPetEquipment->isUpdateYaoLing = true;
            }
            break;
        case SC_PET_GUARD_SET:
            onResetShow();
            if (global_layerPetEquipment!=NULL) {
                global_layerPetEquipment->isUpdateUI = true;
                global_layerPetEquipment->isUpdateYaoLing = true;
            }
            break;
        case SC_PET_GUARD_REFRESH:
            onResetShow();
            if (global_layerPetEquipment!=NULL) {
                global_layerPetEquipment->isUpdateUI = true;
                global_layerPetEquipment->isUpdateYaoLing = true;
            }
            break;
        default:
            break;
    }
}
bool MB_LayerGuard::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFCost",CCLabelBMFont*,m_pTTFCost);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFAttribute1",CCLabelTTF*,m_pTTFAttribute[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFAttribute2",CCLabelTTF*,m_pTTFAttribute[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFAttribute3",CCLabelTTF*,m_pTTFAttribute[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFAttribute4",CCLabelTTF*,m_pTTFAttribute[3]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFAttributeEX1",CCLabelTTF*,m_pTTFAttributeEX[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFAttributeEX2",CCLabelTTF*,m_pTTFAttributeEX[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFAttributeEX3",CCLabelTTF*,m_pTTFAttributeEX[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFAttributeEX4",CCLabelTTF*,m_pTTFAttributeEX[3]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFAttributeEX5",CCLabelTTF*,m_pTTFAttributeEX[4]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFAttributeEX6",CCLabelTTF*,m_pTTFAttributeEX[5]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMenuLock1",CCMenuItemImage*,m_pMenuLock[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMenuLock2",CCMenuItemImage*,m_pMenuLock[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMenuLock3",CCMenuItemImage*,m_pMenuLock[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMenuLock4",CCMenuItemImage*,m_pMenuLock[3]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMenuLock5",CCMenuItemImage*,m_pMenuLock[4]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMenuLock6",CCMenuItemImage*,m_pMenuLock[5]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeLock1",CCNode*,m_pNodeLock[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeLock2",CCNode*,m_pNodeLock[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeLock3",CCNode*,m_pNodeLock[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeLock4",CCNode*,m_pNodeLock[3]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeLock5",CCNode*,m_pNodeLock[4]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeLock6",CCNode*,m_pNodeLock[5]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeScroller",CCNode*,m_pNodeScroller);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pScrollsize",CCNode*,m_pScrollsize);
    
    for (int i = 0; i < CARD_IN_GAME; i++) {
        char starstr[] = "ylNode0";
        starstr[6] = i + '0';
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, starstr, CCNode *, m_pYlNode[i]);
    }
    return false;
}
SEL_MenuHandler MB_LayerGuard::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerGuard::onCloseClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onLockClicked1",MB_LayerGuard::onLockClicked1);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onLockClicked2",MB_LayerGuard::onLockClicked2);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onLockClicked3",MB_LayerGuard::onLockClicked3);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onLockClicked4",MB_LayerGuard::onLockClicked4);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onLockClicked5",MB_LayerGuard::onLockClicked5);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onLockClicked6",MB_LayerGuard::onLockClicked6);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onRuleClicked",MB_LayerGuard::onRuleClicked);
    return NULL;
}
SEL_CCControlHandler MB_LayerGuard::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onChangeClicked",MB_LayerGuard::onChangeClicked);

    return NULL;
}
void MB_LayerGuard::onCloseClick(CCObject* pSender)
{
    ((MB_LayerCommand*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND))->rootNode->setVisible(isHomeButtonShow);
    popWindow(true);
}
void MB_LayerGuard::onLockClicked1(CCObject* pSender)
{
    setLockCost(0);
}
void MB_LayerGuard::onLockClicked2(CCObject* pSender)
{
    setLockCost(1);
}
void MB_LayerGuard::onLockClicked3(CCObject* pSender)
{
    setLockCost(2);
}
void MB_LayerGuard::onLockClicked4(CCObject* pSender)
{
    setLockCost(3);
}
void MB_LayerGuard::onLockClicked5(CCObject* pSender)
{
    setLockCost(4);
}
void MB_LayerGuard::onLockClicked6(CCObject* pSender)
{
    setLockCost(5);
}
//刷新
void MB_LayerGuard::onChangeClicked(CCObject* pSender)
{
    if(MB_GuardInterface::getInstance()->getCostByLockNum(getLockNum()) > MB_RoleData::getInstance()->getGold()+MB_RoleData::getInstance()->getGoldBoune()) //宝石是否足够
    {
        MB_ResWindow* pWnd = MB_Message::createMessageBox2("提示","您的宝石已不足，是否前往充值", "前往", "取消", this,menu_selector(MB_LayerGuard::goCharge), NULL);
        CCDirector::sharedDirector()->getRunningScene()->addChild(pWnd);
        return;
    }
    
    if (teamV[m_nSelectIndex] != -1)
    {
        //检查是否有高级属性
        MB_PetGuardData* pGuardData = MB_GuardInterface::getInstance()->getPetGuardDataByPos(m_nSelectIndex+1);
        if (pGuardData != NULL) {
            CCArray* array = pGuardData->getHighAttrArray();
            for(int i = 0;i < GUARD_ATTR_MAX && i < array->count();i++)
            {
                MB_PetGuardAttr* attr = dynamic_cast<MB_PetGuardAttr*>(array->objectAtIndex(i));
                if (attr != NULL)
                {
                    if (MB_GuardInterface::getInstance()->getRankByValAndType(attr->getAddValue(),attr->getAttrType()) >= 5  && !m_bLock[i])  //高级属性 且未绑定
                    {
                        MB_Message::sharedMB_Message()->showMessage("提示","有高级属性未绑定，是否确定刷新", "刷新","取消", this, menu_selector(MB_LayerGuard::onConfirmChange), NULL);
                        return;
                    }
                }
            }
        }
 
        MB_Message::sharedMB_Message()->showMessage("",15);
        MB_GuardInterface::getInstance()->send_PetGuardRefresh(m_nSelectIndex+1,m_bLock);
        return;
    }
    MB_Message::sharedMB_Message()->showMessage("没有守护");

}
void MB_LayerGuard::onRuleClicked(CCObject* pSender)
{
    MB_ResWindow* pWnd = MB_LayerFunctionRule::create(kFunctionGuard);
    if (pWnd)
    {
        pushWindow(pWnd);
    }
    
}

//点击选择后设置守护
void MB_LayerGuard::setPetGuard(uint64_t uid)
{
    if (teamV[m_nSelectIndex] != -1)
    {
        MB_Message::sharedMB_Message()->showMessage("",15);
        MB_GuardInterface::getInstance()->send_PetGuardSet(uid,m_nSelectIndex+1);
        return;
    }
    CCLOG("ERROR: MB_LayerGuard not find Team member by pos  %d ",m_nSelectIndex+1);
}
int MB_LayerGuard::getLockNum()
{
    int locknum = 0;
    for (int i = 0;i < GUARD_ATTR_MAX; i++)
    {
        if (m_bLock[i])
        {
            locknum++;
        }
    }
    return locknum;
}
bool MB_LayerGuard::setLockCost(int index)
{
    m_bLock[index] = !m_bLock[index];
    m_pMenuLock[index]->setEnabled(!m_bLock[index]);
    
    int locknum = getLockNum();
    if (locknum > 5) //是否全锁
    {
        m_bLock[index] = !m_bLock[index];
        m_pMenuLock[index]->setEnabled(!m_bLock[index]);
        MB_Message::sharedMB_Message()->showMessage("不能锁定全部属性");
        return false;
    }
    
    if(MB_GuardInterface::getInstance()->getCostByLockNum(locknum) > MB_RoleData::getInstance()->getGold()+MB_RoleData::getInstance()->getGoldBoune()) //宝石是否足够
    {
        m_bLock[index] = !m_bLock[index];
        m_pMenuLock[index]->setEnabled(!m_bLock[index]);
        MB_Message::sharedMB_Message()->showMessage("宝石不足");
        return false;
    }
    
    //刷新消耗
    char str[32];
    sprintf(str,"%d",MB_GuardInterface::getInstance()->getCostByLockNum(locknum));
    m_pTTFCost->setString(str);
    
    return true;
}

void MB_LayerGuard::onConfirmChange(CCObject *pSender)
{
    MB_Message::sharedMB_Message()->showMessage("",15);
    MB_GuardInterface::getInstance()->send_PetGuardRefresh(m_nSelectIndex+1,m_bLock);
}

void MB_LayerGuard::goCharge(CCObject*)
{
    NSGameFunction::CCFunctionInterface *pInterface = NULL;
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionPayShop ,&pInterface))
    {
        pInterface->onEntryClicked(this);
    }
}

void MB_LayerGuard::reloadArray(){
    
    m_pArray->removeAllObjects();
    MB_PetData* selectPetData = MB_PetMgr::getInstance()->getPetDataByUID(teamV[m_nSelectIndex]);
    uint16_t selectPetTypeID = selectPetData->getPetTypeID();
    MB_PetData* pd1;
    MB_PetGuardData* pData;
    vector<uint16_t> shanzhenPetTypeIDVec;
    vector<uint16_t> shouhuPetTypeIDVec;
    for (int i = 0; i<CARD_IN_GAME; i++) {
        if (teamV[i]!=-1) {
            pd1 = MB_PetMgr::getInstance()->getPetDataByUID(teamV[i]);
            shanzhenPetTypeIDVec.push_back(pd1->getPetTypeID());
            pData = MB_GuardInterface::getInstance()->getPetGuardDataByPos(i+1);
            if (pData!=NULL) {
                shouhuPetTypeIDVec.push_back(pData->getPetTypeId());
            }
        }
    }
    
    CCObject *_petData;
    MB_PetTemplate* petTemp = NULL;
    uint8_t uPetStar = 0;
    CCArray* pArray = MB_PetMgr::getInstance()->getPetDataArray();
    CCARRAY_FOREACH(pArray, _petData){
        MB_PetData* petData = (MB_PetData*)_petData;
        if (NSGameHelper::checkIsExperienceCard(((MB_PetData*)petData)->getPetTypeID())) {
            continue;
        }
        if (MB_TeamData::getInstance()->checkInTeam((MB_PetData*)petData))
        {
            continue;
        }
        if (petData->getPetTypeID()== selectPetTypeID)
        {
            continue;
        }
        bool b = false;
        for (int i =0; i<shanzhenPetTypeIDVec.size(); i++) {
            if (petData->getPetTypeID()==shanzhenPetTypeIDVec[i]) {
                b = true;
                break;
            }
        }
        if (b) continue;
        for (int i =0; i<shouhuPetTypeIDVec.size(); i++) {
            if (petData->getPetTypeID()==shouhuPetTypeIDVec[i]) {
                b = true;
                break;
            }
        }
        if (b) continue;
        m_pArray->addObject(petData);
    }
    m_nListSize = m_pArray->count();
    if (m_nListSize > 1) {
        m_pArray->sortArray(compare_lg);
    }
}

cocos2d::CCSize MB_LayerGuard::cellSizeForTable(cocos2d::extension::CCTableView *table){
    
    return  m_objUnitSize;
    
}
cocos2d::extension::CCTableViewCell* MB_LayerGuard::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    
    CCTableViewCell *cell = table->dequeueCell();
    if (cell == NULL)
    {
        cell = new CCTableViewCell();
        cell->autorelease();
    }
    else
    {
        cell->removeAllChildren();
    }
    
    MB_LOG("table index %d",idx);
    MB_PetData *data = (MB_PetData *)m_pArray->objectAtIndex(idx);
    MB_NodeYaoLingChoose *node = MB_NodeYaoLingChoose::create(data->getPetID());
    node->m_pLg = this;
    node->setPosition(ccp(m_pScrollsize->getContentSize().width/2.0f,m_objUnitSize.height/2.0f));
    cell->addChild(node);
    node->setTag(1);
    return cell ;
}
unsigned int MB_LayerGuard::numberOfCellsInTableView(cocos2d::extension::CCTableView *table){
    return m_nListSize;
}
