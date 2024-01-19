//
//  MB_NodeRecoveryEnergyEntry.cpp
//  ProjectPM
//
//  Created by chk on 14-4-29.
//
//


#include "MB_NodeRecoveryEnergyEntry.h"
#include "MB_RecoveryEnergyInterface.h"
#include "Game.h"

bool MB_NodeRecoveryEnergyEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_RecoveryEnergyInterface*>(pDataSource);
    
    return m_pDataSource != NULL;
}

void MB_NodeRecoveryEnergyEntry::onEntranceClicked(CCObject* pSender)
{
    MB_CommandActivaty* pInterface = dynamic_cast<MB_CommandActivaty*>(m_pDataSource);
    if(pInterface)
    {
        MB_ResWindow* pLayer = pInterface->createFunctionDialog();
        if(pLayer)
        {
            NSGameFunction::CCFunctionInterface::getCurrentFunctionWnd()->replaceLayer(pLayer);
        }
    }
}

void MB_NodeRecoveryEnergyEntry::tick(float dt)
{
    MB_NodeHoverEntry::tick(dt);
    
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
            
            m_pFlagNode2->setVisible(bIsCanGive);
            if (pEvnet1->getIsGet() == 2 && pEvnet2->getIsGet() == 2 && pEvnet3->getIsGet() == 2)
            {
                this->unschedule(schedule_selector(MB_ResWindow::tick));
            }
        }
    }
}

