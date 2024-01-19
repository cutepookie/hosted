
#ifndef __ProjectMB__MB_NodeUpdatePetList__
#define __ProjectMB__MB_NodeUpdatePetList__
#include "Game.h"
class MB_NodeUpdatePetList :public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver,
public cocos2d::extension::CCTableViewDataSource,
public cocos2d::extension::CCTableViewDelegate{
    
    private:
    
        CCArray* m_pCheckList;
        CCArray *m_pSoldList;
        CCNode * m_pListSize;
        CCTableView *m_pTableView;
        int m_nListSize;
        CCSize m_pSize;
        uint64_t m_nPetId;
        bool m_bIsEnd;
        
    
    public :
    
        MB_NodeUpdatePetList();
        ~MB_NodeUpdatePetList();
        static MB_NodeUpdatePetList* create(CCArray *list,uint64_t petID);
        virtual bool init(CCArray *list,uint64_t petID);
        virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
        virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
        virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
        void onListCloseClick(CCObject *);
        void onSoldClick(CCObject *);
    
        virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
        virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
        virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
        virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
        virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) ;
        virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);
        void onTouchHead(CCObject *);
        void whenActionOver();
        CCArray *getSoldList();
    
        void setShowNode(uint64_t uid);

};

#endif /* defined(__ProjectMB__MB_NodeUpdatePetList__) */
