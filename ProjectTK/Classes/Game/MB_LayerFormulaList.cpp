//
//  MB_LayerFormulaList.cpp
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-18.
//
//

#include "MB_LayerFormulaList.h"
#include "MB_NodeFormulaUnit.h"
#include <algorithm>

MB_LayerFormulaList::MB_LayerFormulaList()
{
    m_pListLayer = NULL;
}

MB_LayerFormulaList::~MB_LayerFormulaList()
{
    m_pListLayer = NULL;
}

/*星级升序>品阶升序>ID升序*/
bool MB_LayerFormulaList::sortFunction(MB_ItemData* first,MB_ItemData* second)
{
    //星级降序
    if(first->getTemplateStar() > second->getTemplateStar())
    {
        return true;
    }
    else if(first->getTemplateStar() < second->getTemplateStar())
    {
        return false;
    }
    
    //等级降序
    if (first->getItemLevel() > second->getItemLevel())
    {
        return true;
    }
    else if(first->getItemLevel() < second->getItemLevel())
    {
        return false;
    }
    
    //品阶降序
    if (first->getItemRank() > second->getItemRank())
    {
        return true;
    }
    else if(first->getItemRank() < second->getItemRank())
    {
        return false;
    }
    
    if (first->getItemUID() > second->getItemUID())
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}

bool MB_LayerFormulaList::sortFormulaArray(const CCArray* pArray,std::vector<MB_ItemData*>& result)
{
    CCArray* pTemp = const_cast<CCArray*>(pArray);

    if (pTemp == NULL)
    {
        return true;
    }

    int count = pTemp->count();
    MB_ItemData* pItem = NULL;
    for (int i=0; i<count; ++i)
    {
        pItem = dynamic_cast<MB_ItemData*>(pTemp->objectAtIndex(i));
        result.push_back(pItem);
    }

    std::sort(result.begin(), result.end(),sortFunction);

    return true;
}

MB_LayerFormulaList* MB_LayerFormulaList::create(const CCSize& sz)
{
    MB_LayerFormulaList* pInstance = new MB_LayerFormulaList();

    if (pInstance && pInstance->init(sz))
    {
        pInstance->autorelease();
        return pInstance;
    }

    CC_SAFE_RELEASE_NULL(pInstance);
    return  pInstance;
}

bool MB_LayerFormulaList::init(const CCSize& sz)
{
    CCArray* pArray = MB_ItemMgr::getInstance()->getItemFormulaArray();
    if (pArray->count() == 0)
    {
        return false;
    }

    m_szListSize = sz;

    onResetWnd();
    return true;
}

void MB_LayerFormulaList::resetList()
{
    if (m_pListLayer)
    {
        m_pListLayer->removeAllChildren();
        CCArray* pArray = MB_ItemMgr::getInstance()->getItemFormulaArray();
        m_nCount = pArray->count();
        if (m_nCount == 0)
        {
            return ;
        }
        
        std::vector<MB_ItemData*> container;
        sortFormulaArray(pArray, container);
        
        std::vector<MB_ItemData*>::iterator it = container.begin();
        MB_NodeFormulaUnit* pNode = NULL;
        uint16_t item_id = 0;
        int index = 0;
        
        size_t sz = container.size();
        
        float space_width = m_szListSize.width / 4;
        float space_height = space_width * 1.2;
        float height = space_height + sz / 4 * space_height;
        if ((sz % 4) == 0)
        {
            height -= space_width;
        }
        
        m_pListLayer->setContentSize(CCSize(m_szListSize.width,height));
        
        for (; it != container.end(); ++it)
        {
            item_id = (*it)->getItemID();
            pNode = MB_NodeFormulaUnit::create(item_id);
            if (pNode)
            {
                m_pListLayer->addChild(pNode);
                pNode->setTag(index);
                pNode->setPositionX(space_width*0.5f+(index%4)*space_width);
                pNode->setPositionY(height-(space_height*0.5f+index/4*space_height));
                ++index;
            }
        }

        m_pListLayer->setPositionY(m_szListSize.height-m_pListLayer->getContentSize().height);
    }
}

void MB_LayerFormulaList::onResetWnd()
{
    if (m_pListLayer == NULL)
    {
        m_pListLayer = CCLayer::create();
        CCScrollView* pScrollView = CCScrollView::create(m_szListSize);
        pScrollView->setDirection(kCCScrollViewDirectionVertical);
        pScrollView->setContainer(m_pListLayer);
        resetList();
        addChild(pScrollView);
    }
    else
    {
        resetList();
    }
}