//
//  MB_LayerMonsterSelect.h
//  ProjectPM
//
//  Created by WenYong on 14-4-28.
//
//

#ifndef __ProjectMB__MB_LayerMonsterSelect__
#define __ProjectMB__MB_LayerMonsterSelect__

#include "MB_NodePetList.h"
#include "MB_NodeSelect.h"

class MB_LayerMonsterSelect:public MB_NodePetList
,public MB_NodeSelectDelegate
{
public:
    MB_LayerMonsterSelect();
    virtual void onNodeSelected(uint64_t nUid,uint16_t nType);
    virtual void reloadCellData(CCTableViewCell *cell,int idx);
    void setSelectCallBack(CCObject* pTarget,SEL_CHOOSE callback);
private:
    CCObject *          m_pTarget;
    SEL_CHOOSE          m_pCallBack;
};
#endif /* defined(__ProjectMB__MB_LayerMonsterSelect__) */
