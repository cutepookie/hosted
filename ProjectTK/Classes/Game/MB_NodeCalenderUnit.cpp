//
//  MB_NodeCalenderUnit.cpp
//  ProjectMB
//
//  Create by WenYong on 28/8/2014.
//
//
#include "MB_NodeCalenderUnit.h"

MB_NodeCalenderUnit::MB_NodeCalenderUnit()
{
    size	 = NULL;
    m_nDataNumber = 1;
    m_bIsToday = false;
    m_nState = kNext;
    m_pNodeData = NULL;

    m_pNodeRegister = NULL;
    m_pNodeMiss = NULL;
    m_pNodeToday = NULL;
}
MB_NodeCalenderUnit::~MB_NodeCalenderUnit()
{
    CC_SAFE_RELEASE_NULL(size);
    CC_SAFE_RELEASE_NULL(m_pNodeData);
    CC_SAFE_RELEASE_NULL(m_pNodeRegister);
    CC_SAFE_RELEASE_NULL(m_pNodeMiss);
    CC_SAFE_RELEASE_NULL(m_pNodeToday);
}
MB_NodeCalenderUnit* MB_NodeCalenderUnit::create(uint16_t num,int state,bool bIsToday)
{
    MB_NodeCalenderUnit* pInstance = MB_NodeCalenderUnit::create();
    if (pInstance)
    {
        pInstance->setDataNumber(num, state,bIsToday);
    }
    
    return pInstance;
}
bool MB_NodeCalenderUnit::init()
{
    CCNode* pNode = loadResource("res/Registration_unit_1.ccbi");
    if(pNode)
	{
		addChild(pNode);
		return true;
	}
	return false;
}

void MB_NodeCalenderUnit::setDataNumber(uint16_t num,int state,bool bIsToday)
{
    m_nDataNumber = num;
    m_nState = state;
    m_bIsToday = bIsToday;
    onResetWnd();
}

void MB_NodeCalenderUnit::onResetWnd()
{
    char str[30];
    sprintf(str,"%d",m_nDataNumber);
    m_pNodeData->setString(str);
    
    if(m_nState == kNext)
    {
        m_pNodeRegister->setVisible(false);
        m_pNodeMiss->setVisible(false);
    }
    else if (m_nState == kRegister)
    {
        m_pNodeRegister->setVisible(true);
        m_pNodeMiss->setVisible(false);
    }
    else if(m_nState == kMiss)
    {
        m_pNodeRegister->setVisible(false);
        m_pNodeMiss->setVisible(true);
    }
    
    if (m_nState == kRegister) {
        m_pNodeToday->setVisible(false);
    }else{
        m_pNodeToday->setVisible(m_bIsToday);
    }
}
bool MB_NodeCalenderUnit::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"size",CCNode*,size);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeData",CCLabelBMFont*,m_pNodeData);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeRegister",CCNode*,m_pNodeRegister);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeMiss", CCNode*, m_pNodeMiss);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeToday", CCNode*, m_pNodeToday);
	return false;
}

const CCSize& MB_NodeCalenderUnit::getWndSize()
{
    static CCSize sz = CCSizeMake(-1,-1);
    if (sz.width < 0)
    {
        MB_NodeCalenderUnit* pTemp = MB_NodeCalenderUnit::create();
        
        if (pTemp)
        {
            sz = pTemp->size->getContentSize();
        }
    }
    
    return sz;
}
void MB_NodeCalenderUnit::setState(int state)
{
    m_nState = state;
    if(m_nState == kNext)
    {
        m_pNodeRegister->setVisible(false);
        m_pNodeMiss->setVisible(false);
    }
    else if (m_nState == kRegister)
    {
        m_pNodeRegister->setVisible(true);
        m_pNodeMiss->setVisible(false);
        m_pNodeToday->setVisible(false);
    }
    else if(m_nState == kMiss)
    {
        m_pNodeRegister->setVisible(false);
        m_pNodeMiss->setVisible(true);
    }
}
void MB_NodeCalenderUnit::setFlag(bool b)
{
    m_bIsToday = b;
    m_pNodeToday->setVisible(m_bIsToday);
}
