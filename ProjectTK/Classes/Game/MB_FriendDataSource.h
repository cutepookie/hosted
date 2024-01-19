//
//  MB_FriendDataSource.h
//  ProjectPM
//
//  Created by WenYong on 14-6-12.
//
//

#ifndef __ProjectMB__MB_FriendDataSource__
#define __ProjectMB__MB_FriendDataSource__

#include "CCTableView.h"
USING_NS_CC;
USING_NS_CC_EXT;

class MB_FriendDataSouce : public CCTableViewDataSource
{
public:
    void setIsMail(bool bMail);
    void setTablePage(int kTablePage);
    virtual void preReloadData(){};
    void setItemSize(const CCSize& sz);
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual int getIndexByRoleId(uint32_t id){return 0;}
protected:
    CCSize      m_ItemSize;
    int         m_nTablePage;
    bool        m_bMail;
};

class MB_OwenFriendDataSource : public MB_FriendDataSouce
{
public:
    MB_OwenFriendDataSource();
    ~MB_OwenFriendDataSource();
    virtual void preReloadData();
    static bool sort(CCObject*,CCObject*);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual int getIndexByRoleId(uint32_t id);
private:
    CCArray*    m_pArray;
};

class MB_AddFriendDataSource : public MB_FriendDataSouce
{
public:
    MB_AddFriendDataSource();
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
};

class MB_RPSFriendDataSource : public MB_FriendDataSouce
{
public:
    MB_RPSFriendDataSource();
    ~MB_RPSFriendDataSource();
    virtual void preReloadData();
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
protected:
    CCArray* m_pArray;
};

class MB_MsgFriendDataSource : public MB_OwenFriendDataSource
{
public:
    MB_MsgFriendDataSource();
    ~MB_MsgFriendDataSource();
    virtual void preReloadData();
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    void sort();
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
private:
    CCArray* m_pArray;
};

class MB_FightFriendDataSource : public MB_FriendDataSouce
{
public:
    MB_FightFriendDataSource();
    ~MB_FightFriendDataSource();
    virtual void preReloadData();
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    static bool sort(CCObject*,CCObject*);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
private:
    CCArray* m_pArray;
};


#endif /* defined(__ProjectMB__MB_FriendDataSource__) */
