//
//  MB_NodeRuleReportUnit.cpp
//  ProjectMB
//
//  Create by chk on 13/1/2015.
//
//
#include "MB_NodeRuleReportUnit.h"
#include "MB_RuleFightProtocol.h"
#include "RichText.h"
#include "MB_GameInfo.h"
#include "MB_LocalProto.h"
#include "MB_LayerRuleFight.h"
#include "cppjson.h"
#include "MB_ServerList.h"
CCSize MB_NodeRuleReportUnit::getUnitSize()
{
    static CCSize gsize = CCSizeZero;
    if (gsize.width == 0 || gsize.height == 0)
    {
        gsize = MB_NodeRuleReportUnit::create(NULL)->m_pNodeSize->getContentSize();
    }
    return gsize;
}

MB_NodeRuleReportUnit* MB_NodeRuleReportUnit::create(Hist* pHist)
{
    MB_NodeRuleReportUnit* pUnit = new MB_NodeRuleReportUnit;
    if (pUnit)
    {
        pUnit->m_pHist = pHist;
        pUnit->init();
        pUnit->autorelease();
        return pUnit;
    }
    CC_SAFE_DELETE(pUnit);
    return NULL;
}

MB_NodeRuleReportUnit::MB_NodeRuleReportUnit()
{
    m_pNodeSize	 = NULL;
    m_pLabelTime	 = NULL;
    m_pHist = NULL;
    Description         = NULL;
     m_pWin= NULL;
     m_pLose= NULL;
}
MB_NodeRuleReportUnit::~MB_NodeRuleReportUnit()
{
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(m_pLabelTime);
    CC_SAFE_RELEASE(Description);
    CC_SAFE_RELEASE(m_pWin);
    CC_SAFE_RELEASE(m_pLose);
}
bool MB_NodeRuleReportUnit::init()
{
    CCNode* pNode = loadResource("res/report_node_rulefight.ccbi");
    if(pNode)
	{
		addChild(pNode);
        onResetWnd();
		return true;
	}
	return false;
}
void MB_NodeRuleReportUnit::onResetWnd()
{
    if (m_pHist)
    {
        // 第一位：1=别人发起的挑战，0=您发起的挑战
        // 第二位：1=发起者战斗胜利，0=发起者战斗失败
        // 第四位：1=pvp战报，0=秩序战场战报
        std::string richText = "";
        if (((m_pHist->getHistType() >> 6)&0x01) == 1)
        {
            m_pWin->setVisible(true);
            Description->setString(CCString::createWithFormat(GET_CONFIG_VALUE("email_description.xml",1073 ,"des").c_str(),m_pHist->getName().c_str(),m_pHist->getAddRepu())->getCString());
        }
        else
        {
            m_pLose->setVisible(true);
            Description->setString(CCString::createWithFormat(GET_CONFIG_VALUE("email_description.xml",1074 ,"des").c_str(),m_pHist->getName().c_str(),m_pHist->getAddRepu())->getCString());
        }
        
    
        uint16_t day = (MB_ClientSocket::getInstance()->getServerTime()-m_pHist->getTime())/(24*60*60);
        if (day == 0)
        {
            if(m_pLabelTime)m_pLabelTime->setString("今天");
        }
        else
        {
            m_pLabelTime->setString(CCString::createWithFormat("%d天前",day)->getCString());
        }
    }
}
bool MB_NodeRuleReportUnit::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize",CCNode*,m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelTime",CCLabelTTF*,m_pLabelTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Description", CCLabelTTF*, Description);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pWin",CCNode*,m_pWin);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLose",CCNode*,m_pLose);
	return false;
}
SEL_MenuHandler MB_NodeRuleReportUnit::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"OnClickReplay",MB_NodeRuleReportUnit::OnClickReplay);
	return NULL;
}
SEL_CCControlHandler MB_NodeRuleReportUnit::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
void MB_NodeRuleReportUnit::OnClickReplay(CCObject* pSender)
{
    MB_TARGET_PARENT(MB_LayerRuleFight, ptr)
    {
        if(ptr)ptr->onReplayClicked(m_pHist->getHistUID());
    }
}
