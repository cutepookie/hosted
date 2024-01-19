//
//  MB_RefreshShopInterface.h
//  ProjectMB
//
//  Created by chenhongkun on 14-9-5.
//
//

#ifndef __ProjectMB__MB_RefreshShopInterface__
#define __ProjectMB__MB_RefreshShopInterface__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"
#include "Game.h"
class MB_RefreshShopInterface;
class MB_TreasureInfo;
class MB_RefreshShopDataSource:public CCTableViewDataSource
{
public:
    MB_RefreshShopDataSource(MB_RefreshShopInterface*);
    ~MB_RefreshShopDataSource();
    
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
private:
//    CCArray*    m_pArray;
    MB_RefreshShopInterface* m_pInterface;
};



class MB_RefreshShopInterface:public NSGameFunction::CCFunctionInterface
{
public:
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    MB_RefreshShopInterface();
    virtual ~MB_RefreshShopInterface();
    virtual void onLoadingScene();
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    
    CCTableViewDataSource* getDataSource(){return m_pDataSource;}
    
    MB_TreasureInfo* getTreasureInfo(){return m_pTreasureInfo;}
public:
    void sendshop_treasure_info();
    void recvshop_treasure_info(MB_MsgBuffer* recvPacket);
    void sendshop_treasure_buy(int16_t index);
    void recvshop_treasure_new_shop(MB_MsgBuffer* recvPacket);
    void recvshop_treasure_new_activity(MB_MsgBuffer* recvPacket);
    void sendshop_refresh2();
    void recvshop_refresh2(MB_MsgBuffer* recvPacket);
private:
    MB_RefreshShopDataSource* m_pDataSource;
    MB_TreasureInfo* m_pTreasureInfo;
};






#endif /* defined(__ProjectMB__MB_RefreshShopInterface__) */
