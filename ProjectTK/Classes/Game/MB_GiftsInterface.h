//
//  MB_GiftsInterface.h
//  ProjectMB
//
//  Created by chenhongkun on 14/12/17.
//
//


#ifndef __ProjectMB__MB_GiftsInterface__
#define __ProjectMB__MB_GiftsInterface__

#include "MB_CommandActivaty.h"
#include "MB_GiftsProtocol.h"
#include "CCTableViewCell.h"
#include "MB_GiftDataSource.h"

class MB_GiftsInterface:public MB_CommandActivaty
{
public:
    MB_GiftsInterface();
    ~MB_GiftsInterface();
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog(){return NULL;};
    MB_ResWindow* createFunctionDialogSelf(EGiftType e);
    virtual void onLoadingScene();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual uint16_t getFunctionType();
    
    static uint32_t m_LoginTime;
public:
    MB_DailyRewrdInfo* getInfoByType(EGiftType type);
    CCTableViewDataSource* getDataSourceByType(EGiftType type);
public:
    void cs_daily_reward_list();
    void sc_daily_reward_list(MB_MsgBuffer* pRecv);
    void cs_daily_reward_get(uint8_t type,uint32_t needValue);
private:
    CCArray* m_pList;
    MB_GiftLevelDataSource* m_pLevelDataSource;
    MB_GiftTimeDataSource* m_pTimeDataSource;
    MB_GiftMLoginDataSource* m_pMLoginDataSource;
};

#endif /* defined(__ProjectMB__MB_GiftsInterface__) */
