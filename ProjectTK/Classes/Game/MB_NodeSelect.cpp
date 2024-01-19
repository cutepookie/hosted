//
//  MB_NodeSelect.cpp
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-19.
//
//

#include "Game.h"
#include "MB_NodeSelect.h"
#include "MB_NodeMonsterSelect.h"
#include "MB_NodeItemsSelect.h"

MB_NodeSelect::MB_NodeSelect()
{
    m_nItemUID = 0;
    m_pName = NULL;
    m_pNodeIcon = NULL;
    m_pMenuText = NULL;
    m_pNodeMenu = NULL;
    m_pNodeButton = NULL;
    m_pBtn1 = NULL;
    m_bInputed = false;
    for (int i=0; i<7; ++i)
    {
        m_pStars[i] = NULL;
    }
}

MB_NodeSelect::~MB_NodeSelect()
{
    m_nItemUID = 0;
    CC_SAFE_RELEASE_NULL(m_pBtn1);
    CC_SAFE_RELEASE_NULL(m_pName);
    CC_SAFE_RELEASE_NULL(m_pNodeIcon);
    CC_SAFE_RELEASE_NULL(m_pNodeMenu);
    CC_SAFE_RELEASE_NULL(m_pNodeButton);
    CC_SAFE_RELEASE_NULL(m_pMenuText);
    for (int i=0; i<7; ++i)
    {
        CC_SAFE_RELEASE_NULL(m_pStars[i]);
    }
}
void AttrPair::show()
{
    m_pIcon->setVisible(true);
    m_pValue->setVisible(true);
}

void AttrPair::hide()
{
    m_pIcon->setVisible(false);
    m_pValue->setVisible(false);
}

MB_NodeSelect* MB_NodeSelect::create(uint16_t nType,uint64_t nItem,bool showTutoril)
{
    if (nType == kSelectPet)
    {
        MB_NodeMonsterSelect* pNode = MB_NodeMonsterSelect::create(nItem, nType,showTutoril);
        return pNode;
    }
    else if(nType == kSelectItem)
    {
        MB_NodeItemsSelect* pNode = MB_NodeItemsSelect::create(nItem, nType);
        return pNode;
    }
    return NULL;
}

CCSize MB_NodeSelect::getUintSize(uint16_t nType)
{
    CCSize sz;
    MB_NodeSelect* p = NULL;
    if (nType == kSelectPet)
    {
        p = new MB_NodeMonsterSelect;
        p->loadResource("res/card_node_select_unit.ccbi");
        sz = p->getNodeSize();
    }
    else if(nType == kSelectItem)
    {
        p = new MB_NodeItemsSelect;
        p->loadResource("res/item_node_select.ccbi");
        sz = p->getNodeSize();
    }
    CC_SAFE_RELEASE(p);
    return sz;
}
const CCSize& MB_NodeSelect::getNodeSize()const
{
    return m_nSize;
}

uint64_t MB_NodeSelect::getSelectUID()const
{
    return m_nItemUID;
}

void MB_NodeSelect::setStar(int star)
{
    int index = 0;

    for (index=0; index<star; ++index)
    {
        m_pStars[index]->setVisible(true);
    }
    for (; index<7; ++index)
    {
        m_pStars[index]->setVisible(false);
    }
}

void MB_NodeSelect::onResetWnd()
{
    int star = 0;

    char buff[64] = {};

    if (m_nType == kSelectPet)
    {
        MB_PetData* pData = MB_PetMgr::getInstance()->getPetDataByUID(m_nItemUID);
        if (pData)
        {
            MB_PetTemplate* pTemplate = pData->getTemplete();
            if (pTemplate)
            {
                star = pTemplate->getPetStar();
                setStar(star);
                int shape = NSGameHelper::getShapeTypeByRank(pData->getPetQuallity());
                int rank = pData->getPetQuallity()%10;
                if (rank == 0) {
                    sprintf(buff, "%s",pTemplate->getPetName(shape));
                }
                else
                {
                    sprintf(buff, "%s+%d",pTemplate->getPetName(shape),rank);
                }
                m_pName->setString(buff);
                m_pNodeIcon->removeAllChildren();
                m_pNodeIcon->addChild(MB_NodePet::create(m_nItemUID));
                
//                CCNodeRGBA pDest;
//                NSGameHelper::setQualityColor(&pDest,star);
//                m_pName->setColor(pDest.getColor());
            }
        }
    }
    else if(m_nType == kSelectItem)
    {
        MB_ItemData* pData = MB_ItemMgr::getInstance()->getItemDataByUID(m_nItemUID);
        if (pData)
        {
            MB_ItemTemplate* pTemplate = MB_ItemMgr::getInstance()->getItemTemplateByID(pData->getItemID());
            if (pTemplate)
            {
                star = pTemplate->getItemStar();
                setStar(star);

                sprintf(buff, "%s+%d",pTemplate->getItemName(),pData->getItemRank());;
                m_pName->setString(buff);
                m_pNodeIcon->removeAllChildren();
                MB_NodeItem* pNode = MB_NodeItem::create(m_nItemUID);
                if(pNode)
                {
                    pNode->setOnClickEnable(false);
                    m_pNodeIcon->addChild(pNode);
                }
//                CCNodeRGBA pDest;
//                NSGameHelper::setQualityColor(&pDest,star);
//                m_pName->setColor(pDest.getColor());
            }
        }

    }
}

void MB_NodeSelect::setMenuVisable(bool bVisable)
{
    if(m_pNodeMenu)
    {
        CCArray* pMenus = m_pNodeMenu->getChildren();
        CCMenu* pMenu = NULL;
        
        CCARRAY_FOREACH_4TYPE(pMenus, CCMenu*, pMenu)
        {
            pMenu->setVisible(bVisable);
        }
    }

}

void MB_NodeSelect::setButtonVisable(bool bVisable)
{
    CCArray* pMenus = m_pNodeButton->getChildren();
    CCControlButton* pButton = NULL;

    CCARRAY_FOREACH_4TYPE(pMenus, CCControlButton*, pButton)
    {
        pButton->setVisible(bVisable);
    }
}

void MB_NodeSelect::setMenuVisableByTag(bool bVisable,int nTag)
{
    CCNode* pNode = m_pNodeMenu->getChildByTag(nTag);
    if (pNode)
    {
        pNode->setVisible(bVisable);
    }
}

void MB_NodeSelect::setButtonVisableByTag(bool bVisable,int nTag)
{
    CCNode* pNode = m_pNodeButton->getChildByTag(nTag);
    if (pNode)
    {
        pNode->setVisible(bVisable);
    }
}

void MB_NodeSelect::setButtonEnableByTag(bool bEnable,int nTag)
{
    CCControlButton* pNode = dynamic_cast<CCControlButton*>(m_pNodeButton->getChildByTag(nTag));
    if (pNode)
    {
        pNode->setEnabled(bEnable);
    }
}

void MB_NodeSelect::setMenuText(const char *pText)
{
    if (m_pMenuText)
    {
        m_pMenuText->setString(pText);
    }
}
