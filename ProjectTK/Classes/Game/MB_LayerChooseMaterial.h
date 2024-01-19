//
//  MB_LayerChooseMaterial.h
//  ProjectPM
//
//  Created by cri-mac on 14-6-8.
//
//

#ifndef __ProjectMB__MB_LayerChooseMaterial__
#define __ProjectMB__MB_LayerChooseMaterial__


#include "MB_NodeSelect.h"

class MB_LayerChooseMaterial:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
,public CCTableViewDataSource
,public MB_NodeSelectDelegate
{
public:
    MB_LayerChooseMaterial();
    
    ~MB_LayerChooseMaterial();
    
    static MB_LayerChooseMaterial* create(int nType = kSelectPet);
    
    virtual bool init(int nType);
    
    virtual void onResetWnd();
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual CCSize cellSizeForTable(CCTableView *table);
    
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    
    void setTitle(const char* pTitle);
    
    virtual void onNodeSelected(uint64_t nUid,uint16_t nType);
    
    
    void setDelegate(MB_NodeSelectDelegate* pDelegate){m_pDelegate=pDelegate;}
    
protected:
    void onBackClicked(CCObject* pObject);
    
    void onPetClicked(CCObject* pObject);
    
    void onEquipClicked(CCObject* pObject);
    
protected:
    std::vector<uint64_t>   m_pItemList;
    uint16_t    m_nType;
    CCSize      m_Size;
    std::string m_szGuiName;
    MB_NodeSelectDelegate*      m_pDelegate;
protected:
    CCLabelBMFont* m_pTitle;
    CCNode*     m_pNodeList;
    CCNode*     m_pSelectNode;
    CCTableView*    m_pTableView;
    
    CCMenuItemImage* m_pPetButton;
    CCMenuItemImage* m_pEquipButton;
};



#endif /* defined(__ProjectMB__MB_LayerChooseMaterial__) */
