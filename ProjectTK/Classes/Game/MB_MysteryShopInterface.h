//
//  MB_MysteryShopInterface.h
//  ProjectMB
//
//  Created by chenhongkun on 14-9-1.
//
//

#ifndef __ProjectMB__MB_MysteryShopInterface__
#define __ProjectMB__MB_MysteryShopInterface__
#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"

class MB_MysteryShopInterface;
class MB_MysteryShopDataSource:public CCTableViewDataSource
{
public:
    MB_MysteryShopDataSource(MB_MysteryShopInterface*);
    ~MB_MysteryShopDataSource();
    
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
private:
    MB_MysteryShopInterface* m_pInterface;
};


//神秘商店
class MB_MysteryShopInterface:public NSGameFunction::CCFunctionInterface
{
public:
    MB_MysteryShopInterface();
    ~MB_MysteryShopInterface();
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual void onLoadingScene();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    virtual void onDayPassed();
    virtual void onEntryClicked(CCObject* pSender);
    MB_MysteryShopDataSource* getDataSource(){return m_pMysteryDataSource;}
private:
    MB_MysteryShopDataSource* m_pMysteryDataSource;
};

#endif /* defined(__ProjectMB__MB_MysteryShopInterface__) */
