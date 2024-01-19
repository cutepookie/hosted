//
//  MB_LayerSelectPetConfirm.h
//  ProjectPM
//
//  Created by WenYong on 14-3-25.
//
//

#ifndef __ProjectMB__MB_LayerSelectPetConfirm__
#define __ProjectMB__MB_LayerSelectPetConfirm__

#include "MB_ResWindow.h"
class MB_LayerSelectPetConfirm:public MB_ResWindow,
public CCBSelectorResolver
{
public:
    MB_LayerSelectPetConfirm();
    virtual bool init(uint16_t nSelectIndex);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    static MB_LayerSelectPetConfirm* create(uint16_t index);
    virtual void goGeneralStep(uint16_t index);
protected:
    void onCancelClicked(CCObject* pSender);
    void onConfirmClicked(CCObject* pSender);
    
    uint16_t  m_nSelectIndex;
};


#endif /* defined(__ProjectMB__MB_LayerSelectPetConfirm__) */
