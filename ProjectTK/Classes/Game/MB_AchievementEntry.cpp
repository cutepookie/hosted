//
//  MB_AchievementEntry.cpp
//  ProjectPM
//
//  Created by crimoon on 14-6-6.
//
//

#include "MB_AchievementEntry.h"




//#include "MB_VipPackEntry.h"
#include "MB_AchievementInterface.h"
#include "MB_FunctionConfig.h"
#include "MB_RoleData.h"
#include "MB_TaskSystemInterface.h"
#include "MB_FunctionModule.h"
using namespace NSGameFunction;


bool MB_AchievementEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_AchievementInterface*>(pDataSource);
    
    return m_pDataSource != NULL;
}


void MB_AchievementEntry::onResetWnd()
{    
    MB_NodeHoverEntry::onResetWnd();

    //可領取任務數量
    uint32_t nCount = 0;
    NSGameFunction::CCFunctionInterface *pInterface = NULL;
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionTask ,&pInterface))
    {
        MB_TaskSystemInterface* pInterfaceTemp = dynamic_cast<MB_TaskSystemInterface*>(pInterface);
        nCount = pInterfaceTemp->getAchievementCompleteCount();
    }
    
    if (0!=nCount)
    {
        m_pFlagNode2->setVisible(true);
        if (nCount>99) {
            m_pFlag2->setString("!");
        }else
        {
            char buff[25] = {};
            sprintf(buff, "%d",nCount);
            m_pFlag2->setString(buff);
        }
    }
    else
    {
        m_pFlagNode2->setVisible(false);
    }
}
