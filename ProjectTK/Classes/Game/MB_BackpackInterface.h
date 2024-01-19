//
//  MB_BackpackInterface.h
//  ProjectMB
//
//  Created by chenhongkun on 14-9-2.
//
//

#ifndef __ProjectMB__MB_BackpackInterface__
#define __ProjectMB__MB_BackpackInterface__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"

#include "MB_ItemBackpackDataSource.h"
#include "MB_EquipBackpackDataSource.h"
#include "MB_ItemDebrisDataSource.h"
class MB_BackpackInterface:public NSGameFunction::CCFunctionInterface
{
public:
    MB_BackpackInterface();
    ~MB_BackpackInterface();
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual void onLoadingScene();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    
    CCTableViewDataSource* getMB_ItemDataSource(){return m_pMB_ItemDataSource;}
    CCTableViewDataSource* getEquipDataSource(){return m_pEquipDataSource;}
    CCTableViewDataSource* getDebrisDataSource(){return m_pDebrisDataSource;}
private:
    MB_ItemBackpackDataSource * m_pMB_ItemDataSource;
    MB_EquipBackpackDataSource * m_pEquipDataSource;
    MB_ItemDebrisDataSource * m_pDebrisDataSource;
};

#endif /* defined(__ProjectMB__MB_BackpackInterface__) */
