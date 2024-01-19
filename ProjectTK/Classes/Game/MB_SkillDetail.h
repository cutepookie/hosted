//
//  MB_SkillDetail.h
//  ProjectPM
//
//  Created by crimoon on 14-4-9.
//
//

#ifndef __ProjectMB__MB_SkillDetail__
#define __ProjectMB__MB_SkillDetail__

#include "Game.h"

class MB_SkillDetail : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_SkillDetail(uint64_t petID);
    MB_SkillDetail(uint16_t petTypeID);
    ~MB_SkillDetail();
    static MB_SkillDetail* create(uint64_t petID, int index);
    static MB_SkillDetail* create(uint16_t petTypeID, int index);
    
    virtual bool init(int index);
    virtual void onResetWnd();
    void setContent(int index);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
private:
    void onCloseClick(CCObject* pSender);
    uint64_t m_nPetID;
    uint16_t m_nPetTypeID;
    CCScrollView* m_pScrollView;
    CCNode* m_pContainer;
    CCNode* m_pSpr1;
    CCNode* m_pSpr2;
};
#endif /* defined(__ProjectMB__MB_SkillDetail__) */
