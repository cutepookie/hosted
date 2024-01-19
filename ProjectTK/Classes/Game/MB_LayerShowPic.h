//
//  MB_LayerShowPic.h
//  ProjectTK
//
//  Created by ywg on 13-5-30.
//
//  Description: 图鉴

#ifndef __ProjectMB__MB_LayerShowPic__
#define __ProjectMB__MB_LayerShowPic__

#include "Game.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum kShowPicType {
    kShowPicTypePet = 0,
    kShowPicTypeEquip,
    kShowPicTypeTreasure,
};

class MB_LayerShowPic : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
,public CCTableViewDataSource
{
    
public:
    MB_LayerShowPic();
    ~MB_LayerShowPic();
    
    static MB_LayerShowPic* create(kShowPicType type = kShowPicTypePet);
    
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(kShowPicType type);
    virtual void onResetWnd();
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    void onPetClicked(CCObject* sender);
    void onEquipClicked(CCObject* sender);
    void onTreasureClicked(CCObject* sender);
    
    void onDetailClicked(CCObject *sender);
    void onCloseClicked(CCObject* sender);
    
    void enterPet();
    void enterEquip();
    void enterTreasure();
    
    void updateButtonSelect();
    
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
private:
    CCNode* m_pContainer;
    CCSize m_cellSize;
    CCMenuItemImage* m_pButtonPagePet;
    CCMenuItemImage* m_pButtonPageEquip;
    CCMenuItemImage* m_pButtonPageTreasure;
    
    kShowPicType m_kShowPicType;
    
    CCTableView* m_pTableView;
    CCSize m_szCell;
    CCArray* m_pItemArray;
};

#endif /* defined(__ProjectMB__MB_LayerShowPic__) */
