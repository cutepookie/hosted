//
//  MB_NodeSuitProperty.cpp
//  ProjectPM
//
//  Create by WenYong on 4/5/2014.
//
//
#include "MB_NodeSuitProperty.h"
#include "MB_SuitActivateData.h"
#include "MB_SuitAttribute.h"

MB_NodeSuitProperty::MB_NodeSuitProperty()
{
    m_pLineSpr = NULL;
    m_pNodeSize	 = NULL;
    m_pSpActivated	 = NULL;
    m_pSpUnActivated	 = NULL;
    m_pTTFPropertys[0]	 = NULL;
    m_pTTFPropertys[1]	 = NULL;
    m_pTTFPropertys[2]	 = NULL;
    m_pTTFPropertys[3]	 = NULL;
    m_pActivateData = NULL;
}
MB_NodeSuitProperty::~MB_NodeSuitProperty()
{
    CC_SAFE_RELEASE_NULL(m_pLineSpr);
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(m_pSpActivated);
    CC_SAFE_RELEASE_NULL(m_pSpUnActivated);
    CC_SAFE_RELEASE_NULL(m_pTTFPropertys[0]);
    CC_SAFE_RELEASE_NULL(m_pTTFPropertys[1]);
    CC_SAFE_RELEASE_NULL(m_pTTFPropertys[2]);
    CC_SAFE_RELEASE_NULL(m_pTTFPropertys[3]);
    CC_SAFE_RELEASE_NULL(m_pActivateData);
}

MB_NodeSuitProperty* MB_NodeSuitProperty::create(MB_SuitActivateData* pData)
{
    MB_NodeSuitProperty* pInstance = new MB_NodeSuitProperty;
    if (pInstance && pInstance->init(pData))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return NULL;
}

bool MB_NodeSuitProperty::init(MB_SuitActivateData* pData)
{
    if (pData==NULL || pData->getNeedAmount()<2 || pData->getNeedAmount() > 6)
    {
        return false;
    }
    const char* pFile[] = \
    {\
        "",
        "",
        "res/suit_node_2.ccbi",
        "res/suit_node_3.ccbi",
        "res/suit_node_4.ccbi",
        "res/suit_node_5.ccbi",
        "res/suit_node_6.ccbi",
    };
    CCNode* pNode = loadResource(pFile[pData->getNeedAmount()]);
    if(pNode)
	{
        CC_SAFE_RELEASE_NULL(m_pActivateData);
        m_pActivateData = pData;
        m_pActivateData->retain();
		addChild(pNode);
        onResetWnd();
		return true;
	}
	return false;
}
void MB_NodeSuitProperty::onResetWnd()
{
    if (m_pActivateData)
    {
        int index = 0;
        CCArray* pArray = CCArray::create();
        m_pActivateData->getActivateAttr(pArray);
        
        MB_SuitAttribute* pTemp = NULL;
        CCARRAY_FOREACH_4TYPE(pArray, MB_SuitAttribute*, pTemp)
        {
            m_pTTFPropertys[index]->setVisible(true);
            m_pTTFPropertys[index]->setString(pTemp->getAttrDescribe());
            ++index;
        }
        
        if(index < 2)
        {
            for (int i = 0; i<index; ++i)
            {
                m_pTTFPropertys[i]->setPositionY( m_pTTFPropertys[i]->getPositionY() - 15);
            }
        }
        
        for (; index<4; ++index)
        {
            m_pTTFPropertys[index]->setVisible(false);
        }
        
        activate(m_bActivated);
    }
}

CCSize MB_NodeSuitProperty::getNodeSize()const
{
    return m_pNodeSize->getContentSize();
}

void MB_NodeSuitProperty::activate(bool bActivate)
{
    m_bActivated = bActivate;
    
    m_pSpUnActivated->setVisible(!m_bActivated);
    
    if (!m_bActivated)
    {
        m_pTTFPropertys[0]->setColor(ccc3(200, 200, 200));
        m_pTTFPropertys[1]->setColor(ccc3(200, 200, 200));
        m_pTTFPropertys[2]->setColor(ccc3(200, 200, 200));
        m_pTTFPropertys[3]->setColor(ccc3(200, 200, 200));
    }
}
bool MB_NodeSuitProperty::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLineSpr",CCNode*,m_pLineSpr);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize",CCNode*,m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpActivated",CCSprite*,m_pSpActivated);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpUnActivated",CCSprite*,m_pSpUnActivated);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFProperty1",CCLabelTTF*,m_pTTFPropertys[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFProperty3",CCLabelTTF*,m_pTTFPropertys[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFProperty2",CCLabelTTF*,m_pTTFPropertys[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFProperty4",CCLabelTTF*,m_pTTFPropertys[3]);
	return false;
}
