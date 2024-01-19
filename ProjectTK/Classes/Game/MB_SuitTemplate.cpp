//
//  MB_SuitTemplate.cpp
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-14.
//
//

#include "MB_SuitTemplate.h"
#include "MB_SuitActivateData.h"


MB_SuitTemplate::MB_SuitTemplate():m_nId(0),m_nGroupCount(0)
{
    m_pActivateOptions = NULL;
}

MB_SuitTemplate::~MB_SuitTemplate()
{
    CC_SAFE_RELEASE_NULL(m_pActivateOptions);
}
bool MB_SuitTemplate::init(MB_XmlNode* pNode)
{
    if (pNode == NULL)
    {
        return false;
    }

    m_nId = pNode->queryAttributeByName("id")->intValue();
    m_szSuitName = pNode->queryAttributeByName("name")->getCString();
    std::string group = pNode->queryAttributeByName("group")->getCString();

    int groupArray[6];
    uint16_t realCount = 0;

    NSGameHelper::resolvIntValueFromString(group.c_str(), groupArray,realCount, 6);
    m_nGroupCount = realCount;

    for (uint16_t i=0; i<realCount; ++i)
    {
        m_nParts[i] = groupArray[i];
    }

    CCArray* pArray = new CCArray;

    if(pNode->queryNodesByName("activate", pArray))
    {
        CCObject* pObject = NULL;
        MB_SuitActivateData* pData = NULL;
        MB_XmlNode* pChild = NULL;

        CC_SAFE_RELEASE_NULL(m_pActivateOptions);
        m_pActivateOptions = new CCArray;

        CCARRAY_FOREACH(pArray, pObject)
        {
            pChild = dynamic_cast<MB_XmlNode*>(pObject);
            if (pChild)
            {
                pData = MB_SuitActivateData::create(pChild);
                if (pData)
                {
                    m_pActivateOptions->addObject(pData);
                }
            }
        }
    }

    CC_SAFE_RELEASE_NULL(pArray);

    return true;
}

MB_SuitTemplate* MB_SuitTemplate::create(MB_XmlNode* pNode)
{
    MB_SuitTemplate* pInstance = new MB_SuitTemplate;

    if (pInstance && pInstance->init(pNode))
    {
        pInstance->autorelease();
        return pInstance;
    }

    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}

const char* MB_SuitTemplate::getSuitName()const
{
    return m_szSuitName.c_str();
}

uint16_t MB_SuitTemplate::getPartItemIdByType(int nType)const
{
    if (nType >= kPartCount)
    {
        return -1;
    }

    return m_nParts[nType];
}

const uint16_t* MB_SuitTemplate::getParts()const
{
    return m_nParts;
}

bool MB_SuitTemplate::getActivateOptionsByPartCount(CCArray* pOptions,int nCount)
{
    if (pOptions == NULL || m_pActivateOptions == NULL)
    {
        return false;
    }

    CCObject* pObject = NULL;
    MB_SuitActivateData* pData = NULL;

    CCARRAY_FOREACH(m_pActivateOptions, pObject)
    {
        pData = dynamic_cast<MB_SuitActivateData*>(pObject);
        if (pData)
        {
            if (pData->getNeedAmount() <= nCount)
            {
                pOptions->addObject(pData);
            }
        }
    }

    return pOptions->count() != 0;
}

MB_SuitActivateData* MB_SuitTemplate::QueryActivateOptionByPartCount(int nCount)
{
    if (m_pActivateOptions == NULL)
    {
        return NULL;
    }

    CCObject* pObject = NULL;
    MB_SuitActivateData* pData = NULL;

    CCARRAY_FOREACH(m_pActivateOptions, pObject)
    {
        pData = dynamic_cast<MB_SuitActivateData*>(pObject);
        if (pData)
        {
            if (pData->getNeedAmount() == nCount)
            {
                // did not incress reference count,user shouldn't release the object
                return pData;
            }
        }
    }

    return NULL;
}

bool MB_SuitTemplate::isItemInThisSuit(uint16_t nItemId)const
{
    for (uint16_t i=0; i<m_nGroupCount; ++i)
    {
        if (m_nParts[i] == nItemId)
        {
            return true;
        }
    }

    return false;
}

CCNode* MB_SuitTemplate::createActivateAttrPanelByCount(uint16_t nCount,const CCSize& sz)const
{
    MB_SuitActivateData* pTarget = NULL;

    CCNode* pNode = CCNode::create();
    CCNode* pTemp = NULL;

//    pNode->setContentSize(sz);
    float left_height = 0;
    CCSize tempSize = sz;

    int index = 0;
    CCScrollView* pScroll = CCScrollView::create(sz);
    pScroll->setDirection(kCCScrollViewDirectionVertical);
    pScroll->setContainer(pNode);

    CCARRAY_FOREACH_4TYPE(m_pActivateOptions, MB_SuitActivateData*, pTarget)
    {
        pTemp = pTarget->createActivatePanelByCount(nCount, sz.width);
        pNode->addChild(pTemp);
        pTemp->setTag(index++);
        left_height += pTemp->getContentSize().height;
    }

    pNode->setContentSize(CCSize(sz.width,left_height));

    int Count = pNode->getChildrenCount();
    for (int i=0; i<Count; ++i)
    {
        pTemp = pNode->getChildByTag(i);
        pTemp->setPosition(ccp(0,left_height-pTemp->getContentSize().height));
        left_height -= pTemp->getContentSize().height;
    }

    
    pNode->setPosition(ccp(0, sz.height-pNode->getContentSize().height));

    return pScroll;
}

uint8_t MB_SuitTemplate::getSuitStar()
{
    MB_ItemTemplate* pTemplate = MB_ItemMgr::getInstance()->getItemTemplateByID(m_nParts[0]);
    if (pTemplate)
    {
        return pTemplate->getItemStar();
    }
    return 0;
}