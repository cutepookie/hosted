//
//  MB_NodeItemsSelect.h
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-19.
//
//

#ifndef __ProjectMB__MB_NodeItemsSelect__
#define __ProjectMB__MB_NodeItemsSelect__

#include "MB_NodeSelect.h"

class MB_ItemData;

class MB_NodeItemsSelect:public MB_NodeSelect
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:

    MB_NodeItemsSelect();
    virtual ~MB_NodeItemsSelect();

    static MB_NodeItemsSelect* create(uint64_t nUid,uint16_t nType);

    virtual bool init(uint64_t nUid,uint16_t nType);
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);

    static bool setItemAttrPair(MB_ItemData* pMB_ItemData,int nAttrType,AttrPair& attrPair);
protected:
    void onButton1Clicked(CCObject* pSender);
private:
    AttrPair        m_AttrPair[4];
};
#endif /* defined(__ProjectMB__MB_NodeItemsSelect__) */
