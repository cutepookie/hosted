//
//  MB_LayerSuitDetail.cpp
//  ProjectPM
//
//  Created by WenYong on 14-6-5.
//
//

#include "MB_LayerSuitDetail.h"
#include "MB_ItemData.h"
#include "MB_NodeSuitContainer.h"
#include "MB_NodeSuitName.h"
#include "MB_NodeSuitProperty.h"
#include "MB_NodeItemBook.h"
#include "MB_SuitSystem.h"

MB_LayerSuitDetail::MB_LayerSuitDetail()
{
    m_nSuitUID = 0;
    m_nSuitID = 0;
    m_nSuitTID = 0;
}

MB_LayerSuitDetail* MB_LayerSuitDetail::create(uint64_t uid)
{
    MB_LayerSuitDetail* pInstance = new MB_LayerSuitDetail;
    if (pInstance && pInstance->setUid(uid))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return NULL;
}

MB_LayerSuitDetail* MB_LayerSuitDetail::createByTid(uint16_t tid)
{
    MB_LayerSuitDetail* pInstance = new MB_LayerSuitDetail;
    if (pInstance && pInstance->setTid(tid))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return NULL;
}

bool MB_LayerSuitDetail::setUid(uint64_t uid)
{
    MB_ItemData* pData = MB_ItemMgr::getInstance()->getItemDataByUID(uid);
    if (pData)
    {
        MB_ItemTemplate* pItem = MB_ItemMgr::getInstance()->getItemTemplateByID(pData->getItemID());
        if (pItem && pItem->getSuitID()!=0)
        {
            m_nSuitID = pItem->getSuitID();
            m_nSuitTID = 0;
            m_nSuitUID = uid;
            reset();
            return true;
        }
    }
    
    return false;
}

bool MB_LayerSuitDetail::setTid(uint16_t tid)
{
    MB_ItemTemplate* pItem = MB_ItemMgr::getInstance()->getItemTemplateByID(tid);
    if (pItem && pItem->getSuitID()!=0)
    {
        m_nSuitID = pItem->getSuitID();
        m_nSuitTID = tid;
        m_nSuitUID = 0;
        reset();
        return true;
    }
    
    return false;
}

void MB_LayerSuitDetail::reset()
{
    if (m_nSuitTID)
    {
        resetByTID(m_nSuitTID);
    }
    else if (m_nSuitUID)
    {
        resetByUid();
    }
}

void MB_LayerSuitDetail::resetByUid()
{
    MB_ItemData* pData = MB_ItemMgr::getInstance()->getItemDataByUID(m_nSuitUID);
    if (pData)
    {
        resetByTID(pData->getItemID());
    }
}

bool MB_LayerSuitDetail::itemHasActivated(uint16_t tid)
{
    if (m_nSuitUID!=0)
    {
        MB_ItemData* pData = MB_ItemMgr::getInstance()->getItemDataByUID(m_nSuitUID);
        if (pData)
        {
            uint64_t petID = pData->getItemPetID();
            if (petID == 0)
            {
                return false;
            }
            return NSGameHelper::petHasEquipThisItem(petID, tid);
        }
    }
    
    return false;
}

void MB_LayerSuitDetail::resetByTID(uint16_t tid)
{
    MB_SuitTemplate* pTemplate =  MB_SuitEquipmentMgr::getInstance()->getSuitTemplateBy(m_nSuitID);
    if (pTemplate)
    {
        removeAllChildren();
        
        // 名字
        MB_NodeSuitName* pNode = MB_NodeSuitName::create();
        pNode->setName(pTemplate->getSuitName());
        addChild(pNode);
        
        float width = pNode->getNodeSize().width/2.0;
        pNode->setPosition(ccp(width,642));
        
        const uint16_t* parts = pTemplate->getParts();
        int count = pTemplate->getGroupCount();
        // 图标
        MB_NodeItemBook* pItem = NULL;
        int activated_count = 0;
        MB_NodeSuitContainer* pContainer = MB_NodeSuitContainer::create();
        addChild(pContainer);
        if (count<6) {
            pContainer->setPosition(ccp(width-(count*91/2-91/2.0f-227),564));
        }else
        {
            pContainer->setPosition(ccp(width,564));
        }
        for (uint16_t i=0; i<count;i++)
        {
            pItem = MB_NodeItemBook::create(parts[i],0,true);
            if (pItem)
            {
                if (itemHasActivated(parts[i]))
                {
                    pItem->activateSuitEffective();
                    ++activated_count;
                }
                pContainer->pushSuitItem(pItem, i);
            }
        }
        CCScrollView* srollView = CCScrollView::create(CCSize(640,220));
        srollView->setDirection(kCCScrollViewDirectionVertical);
        srollView->setAnchorPoint(ccp(.5f,.5f));
        // 属性
        srollView->setPositionY(379-110);
        addChild(srollView);
        CCArray* pArray = pTemplate->getActivateOptions();
        MB_SuitActivateData* pData = NULL;
        MB_NodeSuitProperty* pProperty = NULL;
        int index = 0;
        float perHeight = -1;
        float allHeight = -1;
        CCARRAY_FOREACH_4TYPE(pArray, MB_SuitActivateData*, pData)
        {
            pProperty = MB_NodeSuitProperty::create(pData);
            if (pProperty)
            {
                if (perHeight==-1) {
                    perHeight = pProperty->getNodeSize().height;
                    allHeight = pArray->count()*perHeight;
                }
               
                srollView->addChild(pProperty);
                pProperty->setPosition(ccp(width,allHeight-(index+.5f)*perHeight));
                index++;
                if (activated_count>=pData->getNeedAmount())
                {
                    pProperty->activate(true);
                }
                else
                {
                    pProperty->activate(false);
                }
            }
        }
        pProperty->m_pLineSpr->setVisible(false);
        srollView->setContentSize(CCSize(640,allHeight));
        srollView->setContentOffset(ccp(0,220-allHeight));
        if (srollView->getContentSize().height<220) {
            srollView->setBounceable(false);
        }
    }
}
