//
//  MB_SuitActivateData.cpp
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-14.
//
//

#include "MB_SuitActivateData.h"
#include "MB_SuitAttribute.h"

MB_SuitActivateData::MB_SuitActivateData()
{
    m_pAttrArray = NULL;
}

MB_SuitActivateData::~MB_SuitActivateData()
{
    CC_SAFE_RELEASE_NULL(m_pAttrArray);
}

bool MB_SuitActivateData::getActivateAttr(CCArray* pArray)
{
    if (m_pAttrArray)
    {
        pArray->addObjectsFromArray(m_pAttrArray);
        return true;
    }
    return false;
}

MB_SuitActivateData* MB_SuitActivateData::create(MB_XmlNode* pNode)
{
    MB_SuitActivateData* pInstance = new MB_SuitActivateData;
    if (pInstance && pInstance->init(pNode))
    {
        pInstance->autorelease();
        return pInstance;
    }
    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}

bool MB_SuitActivateData::init(MB_XmlNode* pNode)
{
    if (pNode == NULL)
    {
        return false;
    }
    
    m_nNeedAmount = pNode->queryAttributeByName("needAmount")->intValue();
    
    CCArray* pAttr = new CCArray;

    
    if(pNode->queryNodesByName("attr", pAttr))
    {
        CCObject* pObj = NULL;
        MB_XmlNode* pChild = NULL;
        MB_SuitAttribute* pSuitAttr = NULL;

        CC_SAFE_RELEASE_NULL(m_pAttrArray);
        m_pAttrArray = new CCArray;

        CCARRAY_FOREACH(pAttr, pObj)
        {
            pChild = dynamic_cast<MB_XmlNode*>(pObj);
            if (pChild)
            {
                pSuitAttr = MB_SuitAttribute::create(pChild);
                if (pSuitAttr)
                {
                    m_pAttrArray->addObject(pSuitAttr);
                }
            }
        }
    }

    CC_SAFE_RELEASE_NULL(pAttr);
    
    return true;
}
CCNode* MB_SuitActivateData::createActivatePanelByCount(uint32_t nCount,float width)
{
    const static ccColor3B color[] = {ccc3(195,200,206),ccc3(0, 250, 124)};
    const float font_size = 24.0f;
    uint16_t activate_status = 0;

    if (nCount >= m_nNeedAmount)
    {
        activate_status = 1;
    }

    MB_SuitAttribute* pAttr = NULL;

    char buff[25] = {};
    sprintf(buff, "   装备%d件:",m_nNeedAmount);

    int tag = 0;
    CCNode* pNode = CCNode::create();
    CCLabelTTF* pLabel = CCLabelTTF::create(buff, "", font_size);
    pLabel->setColor(color[activate_status]);
    pLabel->setTag(0);
    pNode->addChild(pLabel);

    CCARRAY_FOREACH_4TYPE(m_pAttrArray, MB_SuitAttribute*, pAttr)
    {
        ++tag;
        pLabel = pAttr->createAttrPanel(font_size);
        pLabel->setColor(color[activate_status]);
        pLabel->setTag(tag);
        pNode->addChild(pLabel);
    }

    uint32_t count = pNode->getChildrenCount();
    
    float line_space = 0.2 * font_size;
    float height = (count+1)*font_size+count*line_space;
    pNode->setContentSize(CCSize(width,height));

    CCPoint pt;
    CCNode* pTemp = NULL;

    for (int i=0; i<count; ++i)
    {
        pTemp = pNode->getChildByTag(i);
        if (pTemp)
        {
            pt.x = pTemp->getContentSize().width/2.0;
            pt.y = height - ((i+1)*font_size/2.0 + i * (font_size));
            pTemp->setPosition(pt);
        }
    }

    return pNode;
}
