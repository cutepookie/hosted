

#ifndef __ProjectMB__MB_LayerPetSell__
#define __ProjectMB__MB_LayerPetSell__

#include "Game.h"

class MB_LayerPetSell:public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver
,public cocos2d::extension::CCTableViewDataSource
,public cocos2d::extension::CCTableViewDelegate
{
    
private:
    
    //  CCLabelFX *m_pText_Money;
    CCLabelTTF *m_pText_pet;
    CCNode* m_pScrollSize;
    CCTableView *m_pTableView;
    CCSize m_cellSize;
    CCArray* m_pPetArray;
    int m_nCout;
    
public :
    
    MB_LayerPetSell();    
    ~MB_LayerPetSell();
    static MB_LayerPetSell* create();
    virtual bool init();    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    
    void onCommitClicked(CCObject *);
    void onBackClicked(CCObject *);
    void onAutoClicked(CCObject *);
    void addToSell(int64_t petid);
    void removeFromSell(int64_t petid);    
    void reloadArray();
    void reloadCellData(CCTableViewCell *cell,int idx);    
    bool sendpet_sell();
    bool recvpet_sell(MB_MsgBuffer *recvPacket);    
    void onMsgRecv(CCNode* node, SocketResponse* response);
    
};


#endif /* defined(__ProjectMB__MB_LayerPetSell__) */
