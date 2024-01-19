//
//  MB_LayerMonsterSelect.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-28.
//
//

#include "MB_LayerMonsterSelect.h"
#include "MB_NodeMonsterSelect.h"

MB_LayerMonsterSelect::MB_LayerMonsterSelect():m_pTarget(NULL),m_pCallBack(NULL)
{
    
}

void MB_LayerMonsterSelect::onNodeSelected(uint64_t nUid,uint16_t nType)
{
    if (m_pTarget)
    {
        
        (m_pTarget->*m_pCallBack)(nUid);
    }
    popWindow();
}

void MB_LayerMonsterSelect::reloadCellData(CCTableViewCell *cell,int idx)
{
    MB_PetData *data = (MB_PetData *)m_pArray->objectAtIndex(idx);
    MB_NodeMonsterSelect *node = MB_NodeMonsterSelect::create(data->getPetID(), 1);
    
    bool issel = MB_TeamData::getInstance()->checkInTeam(data);
    if (!issel)
    {
        node->setMenuVisable(false);
        node->setMenuText("已上阵");
    }
    cell->addChild(node);
    node->setPositionX(m_pScrollsize->getContentSize().width/2.0f);
}

void MB_LayerMonsterSelect::setSelectCallBack(CCObject* pTarget,SEL_CHOOSE callback)
{
    m_pTarget = pTarget;
    m_pCallBack = callback;
}