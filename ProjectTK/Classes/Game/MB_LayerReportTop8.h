//
//  MB_LayerReportTop8.h
//  ProjectTK
//
//  Created by crimoon00007 on 13-12-25.
//
//

#ifndef __ProjectMB__MB_LayerReportTop8__
#define __ProjectMB__MB_LayerReportTop8__

#include "Game.h"

class MB_LyaerReportTop8:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_LyaerReportTop8();
    ~MB_LyaerReportTop8();

    virtual bool init();

    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void setData(MB_MsgBuffer* pResultBuffer);
    CREATE_FUNC(MB_LyaerReportTop8);
    void setScrollSize(const CCSize& sz);
protected:
    virtual bool initScrollView(uint16_t iBoxCount);
    virtual bool installSingleData(MB_MsgBuffer* pSingleData,uint16_t index);
private:
    CCScrollView*   m_pScrollView;
    CCNode*         m_pLayout;
    CCLayer*        m_pBoxLayer;
};

#endif /* defined(__ProjectMB__MB_LayerReportTop8__) */
