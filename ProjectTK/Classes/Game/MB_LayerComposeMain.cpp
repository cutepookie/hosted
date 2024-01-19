//
//  MB_LayerComposeMain.cpp
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-18.
//
//

#include "MB_LayerComposeMain.h"
#include "MB_LayerFormulaList.h"
#include "MB_NodeFormulaUnit.h"
#include "MB_LayerComposePlatform.h"
//#include "MB_LayerSale.h"
#include "Game.h"
#include "MB_LayerComposeRule.h"
#include "MB_RandomComposePlatformEx.h"
#include "MB_ComposeInterface.h"
#include "MB_FunctionMgr.h"
MB_LayerComposeMain::MB_LayerComposeMain()
{
    m_pNodeDisplay = NULL;
    m_pShowList = NULL;
    m_pNodeContainer = NULL;
    m_bShowRoleInfoPanel = true;
    m_pActiveDesc = NULL;
    m_pLeftTime = NULL;
    m_pNodeActive = NULL;
    m_pComposeInterface = NULL;
}

MB_LayerComposeMain::~MB_LayerComposeMain()
{
    CC_SAFE_RELEASE_NULL(m_pNodeDisplay);
    CC_SAFE_RELEASE_NULL(m_pNodeContainer);
    CC_SAFE_RELEASE_NULL(m_pActiveDesc);
    CC_SAFE_RELEASE_NULL(m_pLeftTime);
    CC_SAFE_RELEASE_NULL(m_pNodeActive);
}

bool MB_LayerComposeMain::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pComposeInterface = dynamic_cast<MB_ComposeInterface*>(pDataSource);
    m_pDataSource = pDataSource;
    
    if (m_pComposeInterface)
    {
        if (m_pComposeInterface->getStopTime()!=0)
        {
            if (MB_ClientSocket::getInstance()->getServerTime()<m_pComposeInterface->getStopTime())
            {
                m_pNodeActive->setVisible(true);
                m_pActiveDesc->setString(m_pComposeInterface->getContent().c_str());
                schedule(schedule_selector(MB_LayerComposeMain::onTickUpdate), 1.0f);
                onTickUpdate(1.0f);
            }
            else
            {
                m_pNodeActive->setVisible(false);
            }
        }
        else
        {
            m_pNodeActive->setVisible(false);
        }
        return true;
    }

    return false;
}

void MB_LayerComposeMain::onTickUpdate(float dt)
{
    if (m_pComposeInterface)
    {
        
        if (m_pComposeInterface->getStopTime() < MB_ClientSocket::getInstance()->getServerTime())
        {
            unschedule(schedule_selector(MB_LayerComposeMain::onTickUpdate));
            m_pNodeActive->setVisible(false);
        }
        else
        {
            long long dlt = static_cast<long long>(m_pComposeInterface->getStopTime()) - static_cast<long long>(MB_ClientSocket::getInstance()->getServerTime());
            char buff[64] = {};
            if (dlt > 315360000) {
                sprintf(buff, "永久");
            }
            else if (dlt > 3600)
            {
                sprintf(buff, "%lld小时",dlt/3600);
            }
            else if(dlt > 60)
            {
                sprintf(buff, "%lld分钟",dlt/60);
            }
            else
            {
                sprintf(buff, "%lld秒",dlt);
            }
            m_pLeftTime->setString(buff);
        }
    }
}

bool MB_LayerComposeMain::init()
{
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/compose_layer_item.ccbi", this);
    CC_SAFE_RELEASE_NULL(pCCBReader);

    if (pNode)
    {
        addChild(pNode);
    }

    //onResetWnd();
    onMonsterComposeClicked(NULL);
    return true;
}

void MB_LayerComposeMain::onResetWnd()
{
    if (m_pShowList == NULL)
    {
        m_pShowList = MB_LayerFormulaList::create(m_pNodeDisplay->getContentSize());
        if (m_pShowList)
        {
//            m_pNodeDisplay->addChild(m_pShowList);配方不在这里显示 2014.5.15
        }
    }
    else
    {
        m_pShowList->onResetWnd();
        if(m_pShowList->getCount()==0)
        {
            CCLabelTTF* pText = CCLabelTTF::create("没有找到可用配方", "", 24);
            m_pNodeDisplay->addChild(pText);
            pText->setPosition(ccp(m_pNodeDisplay->getContentSize().width/2,m_pNodeDisplay->getContentSize().height/2.0));
        }
    }
}

void MB_LayerComposeMain::onFormulaClicked(CCObject* pSender)
{
    MB_NodeFormulaUnit* pUnit = dynamic_cast<MB_NodeFormulaUnit*>(pSender);
    if (pUnit)
    {
        goComposePlatform(pUnit->getComposeID(),3);
    }
}

void MB_LayerComposeMain::goComposePlatform(uint16_t nComposeID,uint16_t nType)
{
    MB_RandomComposePlatformEx* pLayer = MB_RandomComposePlatformEx::create(nType);   //v1.0.5
    m_pNodeContainer->removeAllChildrenWithCleanup(true);
    m_pNodeContainer->addChild(pLayer);
}

bool MB_LayerComposeMain::onAssignCCBMemberVariable(CCObject* pTarget,
                                       const char* pMemberVariableName,
                                       CCNode* pNode)
{

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_display", CCNode*, m_pNodeDisplay);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeContainer", CCNode*, m_pNodeContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pActiveDesc", CCLabelTTF*, m_pActiveDesc);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLeftTime", CCLabelTTF*, m_pLeftTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_active", CCNode*, m_pNodeActive);
    return false;
}

SEL_MenuHandler MB_LayerComposeMain::onResolveCCBCCMenuItemSelector(CCObject * pTarget,
                                                       const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerComposeMain::onCloseClick);
    return NULL;
}

SEL_CCControlHandler MB_LayerComposeMain::onResolveCCBCCControlSelector(CCObject * pTarget,
                                                           const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onRuleClicked", MB_LayerComposeMain::onRuleClicked);

    return NULL;
}

void MB_LayerComposeMain::onMonsterComposeClicked(CCObject* pObject)
{
    goComposeCard();
}

void MB_LayerComposeMain::onSaleClicked(CCObject* pObject)
{
//    MB_LayerSale* pLayer = MB_LayerSale::create();
//    NSGameFunction::CCFunctionInterface::getCurrentFunctionWnd()->replaceLayer(pLayer);
}

void MB_LayerComposeMain::onCardComposeClicked(CCObject* pObject)
{
    goComposeItem();
}

void MB_LayerComposeMain::onCloseClick(CCObject* pObject)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionYeShiJie, this);
}

void MB_LayerComposeMain::goComposeCard()
{
    goComposePlatform(0,1);
}

void MB_LayerComposeMain::goComposeItem()
{
    goComposePlatform(0,2);
}

void MB_LayerComposeMain::onComposeSuccessed(MB_ResWindow* pRewardWnd,MB_ResWindow* pSender)
{
    pSender->replaceLayer(pRewardWnd);
    onResetWnd();
}

void MB_LayerComposeMain::onRuleClicked(CCObject* pObject)
{
    MB_LayerComposeRule* pLayer = MB_LayerComposeRule::create(MB_LayerComposeRule::eRandomRule);
    if (pLayer)
    {
        pushWindow(pLayer);
    }
}
