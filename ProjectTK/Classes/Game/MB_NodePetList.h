
#ifndef __ProjectMB__MB_NodePetList__
#define __ProjectMB__MB_NodePetList__

#include "Game.h"
#include "MB_LayerRoleInfoHeader.h"

class MB_LayerPetSell;

class MB_NodePetList: public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
,public cocos2d::extension::CCTableViewDataSource
,public cocos2d::extension::CCTableViewDelegate
{
private:
    
    CCTableView *m_pTableView;
    int m_nListSize;
    int m_nPerPage;
    CCLabelTTF *m_pNow_show_node;
//    CCLabelTTF *m_pNow_show_page;
    CCNode* m_pNodePiece;
    CCNode* m_pNodePet;
    CCLabelTTF *m_pPetNumber;
    
    CCLabelBMFont* m_pTTFTitleName1;
    
    CCPoint m_nStartpos;
    bool m_bIsEnd;
    float m_bscrollerWidth;
//    bool m_bIsInit;
    CCSize m_objUnitSize;
    int m_pNowPage;
    int m_pALlPage;
    int m_pPageHeight;
    float  m_nAllSize;
    CCNode* m_pScrollsize2;
    uint16_t m_uPetTypeID;
    uint64_t m_uPetID;
     
protected:
    CCNode *m_pScrollsize;
    CCArray *m_pArray;
public :

    CC_SYNTHESIZE(int , m_nType, Type);
    CC_SYNTHESIZE(int ,m_pLayerType, LayerType);
    CC_SYNTHESIZE(int ,m_nPos, Pos);
    CC_SYNTHESIZE(bool, m_nCanTouch, CanTouch);
    
    MB_NodePetList();
    ~MB_NodePetList();
    
    static MB_NodePetList * create(int layerType);
    static MB_NodePetList * create(int layerType, uint16_t petTypeID, uint64_t petID);
    static MB_NodePetList * create(int layerType, int pos,int type);
    
    virtual bool init(int layerType, int pos,int type, uint16_t petTypeID, uint64_t petID);
    
    void onSoldClick(CCObject *);
    void onLevelUpClicked(CCObject *);
    void onQualityUpClicked(CCObject *);
    void onListCloseClick(CCObject *);
    
    virtual void onResetWnd();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);    
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);    
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) ;
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);    
  
    void onMsgRecv(CCNode* node, SocketResponse* response);
    bool sendpet_standup(uint64_t petID);
    void reloadPet();
    virtual void reloadCellData(CCTableViewCell *cell,int idx);
    void setTableTouch(bool istouch);
    void reloadArray();
    //材料排序，Id相同优先 其次品阶升序  等级升序 ID升序
    void sortArray();
    
private:
    bool m_bRoleInfoHeaderShow;
};


#endif /* defined(__ProjectMB__MB_NodePetList__) */
