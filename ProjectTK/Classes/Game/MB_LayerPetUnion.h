

#ifndef __ProjectMB__MB_LayerPetUnion__
#define __ProjectMB__MB_LayerPetUnion__
#include "Game.h"
class MB_LayerPetUnion :public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver
,public cocos2d::extension::CCTableViewDataSource
,public cocos2d::extension::CCTableViewDelegate {
    
private:
    

    CCSize m_objUnitSize;
    CCTableView *m_pTableView;
    CCMenuItemImage *m_pPreson,*m_pUnion;
    CCNode *m_pScrollsize;
    int m_nListSize;
    CCLabelTTF *m_pNow_show_node;
    CCArray* m_pArray;
    CCLabelTTF *m_pComonPetPiece3Num;
    CCLabelTTF *m_pComonPetPiece4Num;
    CCLabelTTF *m_pComonPetPiece5Num;
    CCNode *m_pNodePet;
    CCLabelTTF *m_pPetNumber;
    CCNode* m_pNodePiece;
    
    public :
    
    MB_LayerPetUnion();
    ~MB_LayerPetUnion();
    virtual bool init();
    void onCloseClicked(CCObject* pSender);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    static MB_LayerPetUnion* create();
    void getListAndSort();
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    virtual void onResetWnd(void);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    bool recvitem_compound(MB_MsgBuffer* recvPacket);
};

#endif /* defined(__ProjectMB__MB_LayerIemUnion__) */
