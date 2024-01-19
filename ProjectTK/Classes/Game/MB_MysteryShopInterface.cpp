//
//  MB_MysteryShopInterface.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14-9-1.
//
//
#include "MB_MysteryShopInterface.h"
#include "MB_FunctionMgr.h"
#include "MB_ShopMystery.h"
#include "MB_MysteryShopEntry.h"
#include "MB_NodeMysteryShopUnit.h"
#include "MB_ChampionshipFunctionDialog.h"
#include "MB_ShopMystery.h"
#include "MB_LayerShopMain.h"

MB_MysteryShopDataSource::MB_MysteryShopDataSource(MB_MysteryShopInterface*)
{
    
}
MB_MysteryShopDataSource::~MB_MysteryShopDataSource()
{
    
}

CCSize MB_MysteryShopDataSource::cellSizeForTable(CCTableView *table)
{
    return MB_NodeRefreshShopUnit::getUnitSize();
}

CCTableViewCell* MB_MysteryShopDataSource::tableCellAtIndex(CCTableView *table, unsigned int i)
{
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
    
    CCNode* pNode = NULL;
    MB_ShopInfo* pShopInfo = MB_ShopMgr::getInstance()->getShopInfoByID(MYSTERY_SHOP_ID);
    if(pShopInfo)
    {
        CCObject* pObj = pShopInfo->getShopGoodsArray()->objectAtIndex(i);
        MB_ShopGoodsItem* pMB_ItemData = dynamic_cast<MB_ShopGoodsItem*>(pObj);
        
        if(i<4)
        {
            pNode = MB_NodeMysteryShopUnit::create(pMB_ItemData, MB_NodeMysteryShopUnit::kPet);
        }
        else
        {
            pNode = MB_NodeMysteryShopUnit::create(pMB_ItemData, MB_NodeMysteryShopUnit::kItem,i==4);
        }
    }
    
    if(pNode)
    {
        pNode->setPosition( CCPointMake(MB_NodeRefreshShopUnit::getUnitSize().width/2, MB_NodeRefreshShopUnit::getUnitSize().height/2));
        cell->addChild(pNode);
    }
    
    return cell;
}

unsigned int MB_MysteryShopDataSource::numberOfCellsInTableView(CCTableView *table)
{
    return 8;
}






/////////////////
MB_MysteryShopInterface::MB_MysteryShopInterface()
{
    m_pMysteryDataSource = new MB_MysteryShopDataSource(this);
}

MB_MysteryShopInterface::~MB_MysteryShopInterface()
{
    CC_SAFE_DELETE(m_pMysteryDataSource);
}

MB_ResWindow* MB_MysteryShopInterface::createEntryDialog()
{
    MB_MysteryShopEntry* pInstance = new MB_MysteryShopEntry;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->onResetWnd();
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return NULL;
}

MB_ResWindow* MB_MysteryShopInterface::createFunctionDialog()
{
    return MB_LayerShopMain::createBerryShop();
}

void MB_MysteryShopInterface::onLoadingScene()
{
    
}
void MB_MysteryShopInterface::onEntryClicked(CCObject* pSender)
{
    TutorialTriggerComplete
    
    MB_FunctionItem* pFunctionItem = MB_FunctionConfigure::getInstance()->queryFunctionItemByType(getFunctionType());
    if(pFunctionItem)
    {
        if(pFunctionItem->getNeedLevel()>MB_RoleData::getInstance()->getLevel())
        {
            char databuf[40];
            sprintf(databuf, "此功能%d级开放",pFunctionItem->getNeedLevel());
            MB_Message::sharedMB_Message()->showMessage(databuf);
        }
        else
        {
            MB_ResWindow* pWnd = createFunctionDialog();
            if (pWnd)
            {
                if(dynamic_cast<MB_ChampionshipFunctionDialog*>(pSender))
                {
                    MB_ShopMystery* p = dynamic_cast<MB_ShopMystery*>(pWnd);
                    if(p)
                    {
                        p->setBackFunction(kFunctionArena);
                    }
                }
                replaceMainSceneSubLayer(pWnd);
            }
        }
    }
}
void MB_MysteryShopInterface::onMsgRecv(CCNode* node, SocketResponse* response)
{
}

bool MB_MysteryShopInterface::allowShow()
{
    return true;
}

uint16_t MB_MysteryShopInterface::getFunctionType()
{
    return kFunctionMysteryShop;
}

void MB_MysteryShopInterface::onDayPassed()
{
}
