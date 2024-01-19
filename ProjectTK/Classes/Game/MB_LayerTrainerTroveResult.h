//
//  MB_LayerTrainerTroveResult.h
//  ProjectMB
//
//  Created by yuanwugang on 15-2-27.
//
//

#ifndef __ProjectMB__MB_LayerTrainerTroveResult__
#define __ProjectMB__MB_LayerTrainerTroveResult__

#include "MB_ResWindow.h"


class MB_LayerTrainerTroveResult : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    MB_LayerTrainerTroveResult();
    ~MB_LayerTrainerTroveResult();
    static MB_LayerTrainerTroveResult* create(bool bIsWin,int gold);
    virtual bool init(bool bIsWin,int gold);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
protected:
    void onBackClick(CCObject* pSender);
    
private:
    CCLabelBMFont* m_pTTFCoin;
    bool    m_bClickedBack;
    CCNode* m_pSpr1;
};

#endif /* defined(__ProjectMB__MB_LayerTrainerTroveResult__) */
