//
//  MB_RandomComposePlatformEx.h
//  ProjectPM
//
//  Created by cri-mac on 14-6-8.
//
//

#ifndef __ProjectMB__MB_RandomComposePlatformEx__
#define __ProjectMB__MB_RandomComposePlatformEx__

#include "MB_RandomComposePlatform.h"

class MB_ComposeInterface;
class MB_RandomComposePlatformEx:public MB_RandomComposePlatform
{
public:
    MB_RandomComposePlatformEx();
    ~MB_RandomComposePlatformEx();
    static MB_RandomComposePlatformEx* create(int nType);
protected:
    void goSelectItemRandom(int clickIndex);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    void onEquipAutopickClicked(CCObject*);
    void onPetAutopickClicked(CCObject*);
    virtual void recvcombine_pet(MB_MsgBuffer* pbuff);
    virtual void recvcombine_equip(MB_MsgBuffer* pbuff);
    virtual void resetRandom();
private:
    CCMenuItemImage* m_pBtnEquip;
    CCMenuItemImage* m_pBtnPet;
    MB_ComposeInterface*    m_pComposeInterface;
};

#endif /* defined(__ProjectMB__MB_RandomComposePlatformEx__) */
