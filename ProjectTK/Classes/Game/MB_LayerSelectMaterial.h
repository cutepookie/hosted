//
//  MB_LayerSelectMaterial.h
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-19.
//
//

#ifndef __ProjectMB__MB_LayerSelectMaterial__
#define __ProjectMB__MB_LayerSelectMaterial__

#include "MB_NodeSelect.h"

class MB_LayerSelectMaterial:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
,public CCTableViewDataSource
,public MB_NodeSelectDelegate
{
public:
    MB_LayerSelectMaterial();

    ~MB_LayerSelectMaterial();

    static MB_LayerSelectMaterial* create(uint64_t* uids,uint32_t count,uint64_t nCurrentUid, uint16_t nType);
    static MB_LayerSelectMaterial* create(std::vector<uint64_t>& uids,uint64_t nCurrentUid, uint16_t nType);

    virtual bool init(uint64_t* uids,uint32_t count,uint64_t nCurrentUid,uint16_t nType);

    virtual bool initWithContainer(std::vector<uint64_t>& uids,uint64_t nCurrentUid, uint16_t nType);

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
    
    virtual void check2UpList();
protected:
    void onBackClicked(CCObject* pObject);

protected:
    uint64_t*   m_pItemList;
    uint32_t    m_nCount;
    uint64_t    m_nCurrentUid;
    uint16_t    m_nType;
    CCSize      m_Size;
    std::string m_szGuiName;
    MB_NodeSelectDelegate*      m_pDelegate;
protected:
    CCLabelBMFont* m_pTitle;
    CCNode*     m_pNodeList;
    CCNode*     m_pSelectNode;
    CCTableView*    m_pTableView;
};

#endif /* defined(__ProjectMB__MB_LayerSelectMaterial__) */
