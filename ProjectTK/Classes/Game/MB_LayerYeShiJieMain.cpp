//
//  MB_LayerYeShiJieMain.cpp
//  ProjectPM
//
//  Created by WenYong on 14-5-17.
//
//

#include "MB_LayerYeShiJieMain.h"
#include "MB_YeShiJieInterface.h"
#include "MB_RecoveryEnergyInterface.h"
MB_LayerYeShiJieMain::MB_LayerYeShiJieMain()
{
    m_pHCGBtn = NULL;
    m_pSLNode = NULL;
    m_pTJWQBtn = NULL;
    m_pMXBtn = NULL;
    m_pDXJKBtn = NULL;
    m_pPMJBBtn = NULL;
    m_pSLZSBtn = NULL;
    m_pJJCBtn = NULL;
    m_pLHSCBtn = NULL;
    node_flag_mx= NULL;
    node_flag_wq= NULL;
    flag_mx= NULL;
    node_flag_yljk = NULL;
    flag_yljk = NULL;
    m_bShowRoleInfoPanel = true;
    m_bShowEXP = true;
}
MB_LayerYeShiJieMain::~MB_LayerYeShiJieMain()
{
    CC_SAFE_RELEASE_NULL(m_pHCGBtn);
    CC_SAFE_RELEASE_NULL(m_pTJWQBtn);
    CC_SAFE_RELEASE_NULL(m_pMXBtn);
    CC_SAFE_RELEASE_NULL(m_pDXJKBtn);
    CC_SAFE_RELEASE_NULL(m_pPMJBBtn);
    CC_SAFE_RELEASE_NULL(m_pSLZSBtn);
    CC_SAFE_RELEASE_NULL(m_pJJCBtn);
    CC_SAFE_RELEASE_NULL(m_pLHSCBtn);
    CC_SAFE_RELEASE_NULL(m_pSLNode);
    CC_SAFE_RELEASE_NULL(node_flag_mx);
    CC_SAFE_RELEASE_NULL(node_flag_wq);
    CC_SAFE_RELEASE_NULL(flag_mx);
    CC_SAFE_RELEASE_NULL(node_flag_yljk);
    CC_SAFE_RELEASE_NULL(flag_yljk);
}

bool MB_LayerYeShiJieMain::init()
{
    CCNode* pNode = loadResource("res/yeshijie_layer.ccbi");
    CCNode* pNode2;
    if (pNode)
    {
        addChild(pNode);
        
        pNode2 = loadResource("res/yeshijie_node_hechengguan.ccbi");
        pNode2->setPosition(ccp(81,51));
        m_pHCGBtn->addChild(pNode2);
        
        pNode2 = loadResource("res/yeshijie_node_shangcheng.ccbi");
        pNode2->setPosition(ccp(73,42));
        m_pLHSCBtn->addChild(pNode2);
        
        pNode2 = loadResource("res/yeshijie_node_jingjichang.ccbi");
        pNode2->setPosition(ccp(89.2f,85.8f));
        m_pJJCBtn->addChild(pNode2);
        
        m_pSLNode->setPosition(ccp(89.7f,90.8f));
        NSGameHelper::changeParent(m_pSLZSBtn, m_pSLNode);
        
        pNode2 = loadResource("res/yeshijie_node_tianjiewenquan.ccbi");
        pNode2->setPosition(ccp(115,103));
        m_pTJWQBtn->addChild(pNode2);
        
        pNode2 = loadResource("res/yeshijie_node_dixiajingku.ccbi");
        pNode2->setPosition(ccp(101,24));
        m_pDXJKBtn->addChild(pNode2);
        
        pNode2 = loadResource("res/yeshijie_node_maoxian.ccbi");
        pNode2->setPosition(ccp(86,66));
        m_pMXBtn->addChild(pNode2);
        
        pNode2 = loadResource("res/yeshijie_node_paihangjiuba.ccbi");
        pNode2->setPosition(ccp(82,72));
        m_pPMJBBtn->addChild(pNode2);
        return true;
    }
    return false;
}


void MB_LayerYeShiJieMain::onEnterTransitionDidFinish()
{
    MB_FunctionMainWnd::onEnterTransitionDidFinish();
    PlayBackGround(ksSound_YeShiJie);
    
    MB_FunctionItem* pItem =  MB_FunctionConfigure::getInstance()->queryFunctionItemByType(kFunctionYeShiJie);
    if (pItem)
    {
        if(pItem->getNeedLevel()<=MB_RoleData::getInstance()->getLevel())
        {
            uint16_t iTimes = MB_RoleData::getInstance()->getDiscoveryTimes();
            if (iTimes > 0)
            {
                node_flag_mx->setVisible(true);
                char databuf[20];
                sprintf(databuf,"%d",iTimes);
                flag_mx->setString(databuf);
            }
            else
            {
                node_flag_mx->setVisible(false);
            }
        }
        else
        {
            node_flag_mx->setVisible(false);
        }
    }
    
    int yljkLimit =MB_RoleData::getInstance()->getNowBuyLimit(kBuyTimesTypeCoin)-MB_RoleData::getInstance()->getCoinBuyTimes();
    if (yljkLimit>0) {
        node_flag_yljk->setVisible(true);
        char databuf[20];
        sprintf(databuf,"%d",yljkLimit);
        flag_yljk->setString(databuf);
    }else
    {
        node_flag_yljk->setVisible(false);
    }
}

bool MB_LayerYeShiJieMain::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    TutorialAssignLayerWindow
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pHCGBtn",CCNode*,m_pHCGBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTJWQBtn",CCNode*,m_pTJWQBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMXBtn",CCNode*,m_pMXBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pDXJKBtn",CCNode*,m_pDXJKBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pPMJBBtn",CCNode*,m_pPMJBBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSLZSBtn",CCNode*,m_pSLZSBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLHSCBtn",CCNode*,m_pLHSCBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pJJCBtn",CCNode*,m_pJJCBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSLNode",CCNode*,m_pSLNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_flag_mx",CCNode*,node_flag_mx);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_flag_wq",CCNode*,node_flag_wq);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "flag_mx",CCLabelBMFont*,flag_mx);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_flag_yljk",CCNode*,node_flag_yljk);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "flag_yljk",CCLabelBMFont*,flag_yljk);
    return false;
}

SEL_MenuHandler MB_LayerYeShiJieMain::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerYeShiJieMain::onCloseClick);
    return NULL;
}
SEL_CCControlHandler MB_LayerYeShiJieMain::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onHEGClicked", MB_LayerYeShiJieMain::onHEGClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onLHSCClicked", MB_LayerYeShiJieMain::onLHSCClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onJJCClicked", MB_LayerYeShiJieMain::onJJCClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSLZSClicked", MB_LayerYeShiJieMain::onSLZSClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onTJWQClicked", MB_LayerYeShiJieMain::onTJWQClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onDXJKClicked", MB_LayerYeShiJieMain::onDXJKClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onMXClicked", MB_LayerYeShiJieMain::onMXClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPMJBClicked", MB_LayerYeShiJieMain::onPMJBClicked);
    return NULL;
}
void MB_LayerYeShiJieMain::onCloseClick(CCObject* pSender)
{
    TutorialTriggerComplete
    MB_FunctionMgr::getInstance()->goFunction(kFunctionHome, this);
}

void MB_LayerYeShiJieMain::onHEGClicked(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionCompose, this);
}

void MB_LayerYeShiJieMain::onLHSCClicked(CCObject* pSender)
{
    global_isYeShiJieToShop = true;
    MB_FunctionMgr::getInstance()->goFunction(kFunctionPayShop, this);
}
void MB_LayerYeShiJieMain::onJJCClicked(CCObject* pSender)
{
    TutorialTriggerComplete
    MB_FunctionMgr::getInstance()->goFunction(kFunctionArena, this);
}
void MB_LayerYeShiJieMain::onSLZSClicked(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionBigWorld, this);
}
void MB_LayerYeShiJieMain::onTJWQClicked(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kActivatyRecoverEnergy, this);
}
void MB_LayerYeShiJieMain::onDXJKClicked(CCObject* pSender)
{
    TutorialTriggerComplete 
    MB_FunctionMgr::getInstance()->goFunction(kActivatyChangeCoin, this);
}
void MB_LayerYeShiJieMain::onMXClicked(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionMaoXian, this);
}
void MB_LayerYeShiJieMain::onPMJBClicked(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionRanking, this);
}
    


void MB_LayerYeShiJieMain::tick(float dt)
{
    MB_FunctionMainWnd::tick(dt);
    
    //领取体力
    {
        static float fTemp = 0;
        fTemp += dt;
        if(fTemp >= 1)
        {
            fTemp = 0;
            bool bIsCanGive = false;
            time_t nowtime = MB_ClientSocket::getInstance()->getServerTime();
            MB_MoneyEventEnergy*  pEvnet1 =  MB_MoneyEevntMgr::getInstance()->getEventEnergyByIndex(0);
            MB_MoneyEventEnergy*  pEvnet2 =  MB_MoneyEevntMgr::getInstance()->getEventEnergyByIndex(1);
            MB_MoneyEventEnergy*  pEvnet3 =  MB_MoneyEevntMgr::getInstance()->getEventEnergyByIndex(2);
            if (nowtime  >= pEvnet1->getStartTime() && nowtime  < pEvnet1->getEnTime()) {
                
                if(pEvnet1->getIsGet() != 2 && CCUserDefault::sharedUserDefault()->getBoolForKey("isClickEnergy1_2") == false){
                    bIsCanGive = true;
                }
                
            }
            else if(nowtime >= pEvnet2->getStartTime() && nowtime  <  pEvnet2->getEnTime() && CCUserDefault::sharedUserDefault()->getBoolForKey("isClickEnergy2_2") == false){
                
                if(pEvnet2->getIsGet() != 2 && CCUserDefault::sharedUserDefault()->getBoolForKey("isClickEnergy2_2") == false)
                {
                    bIsCanGive = true;
                }
            }
            else if(nowtime >= pEvnet3->getStartTime() && nowtime  <  pEvnet3->getEnTime() && CCUserDefault::sharedUserDefault()->getBoolForKey("isClickEnergy3_2") == false){
                
                if(pEvnet3->getIsGet() != 2 && CCUserDefault::sharedUserDefault()->getBoolForKey("isClickEnergy3_2") == false)
                {
                    bIsCanGive = true;
                }
            }
            
            node_flag_wq->setVisible(bIsCanGive);
            if (pEvnet1->getIsGet() == 2 && pEvnet2->getIsGet() == 2 && pEvnet3->getIsGet() == 2)
            {
                this->unschedule(schedule_selector(MB_ResWindow::tick));
            }
        }
    }
}
