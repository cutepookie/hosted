//
//  MB_NodeRuleRankUnit.cpp
//  ProjectMB
//
//  Create by chk on 12/1/2015.
//
//
#include "MB_NodeRuleRankUnit.h"
#include "MB_RuleFightProtocol.h"
#include "cppjson.h"
#include "MB_ServerList.h"
#include "MB_LayerRuleFight.h"
#include "RichText.h"
static void setTime(time_t time,CCLabelProtocol* pLabel,std::string& out)
{
    const char* wdays[] = {"日","一","二","三","四","五","六"};
    struct tm *pTemp = localtime(&time);
    char szbuff[100] = {0};
    time_t tdis = MB_ClientSocket::getInstance()->getServerTime() - time;
    float fDay = tdis / (3600.0 * 24);
    if(fDay > 14.0f)
    {
        out = "2周前";
    }
    else if(fDay > 7.0f)
    {
        out = "1周前";
    }
    else if(fDay > 1.0f)
    {
        
        sprintf(szbuff,"星期%s %02d:%02d",wdays[pTemp->tm_wday],pTemp->tm_hour,pTemp->tm_min);
        out = szbuff;
    }
    else
    {
        sprintf(szbuff, "%02d:%02d",pTemp->tm_hour,pTemp->tm_min);
        out = szbuff;
    }
    
    if(pLabel)pLabel->setString(out.c_str());
}


MB_NodeRuleRankUnit* MB_NodeRuleRankUnit::create(RuleFighter* pFighter)
{
    MB_NodeRuleRankUnit* pEntry = new MB_NodeRuleRankUnit;
    if (pEntry)
    {
        pEntry->m_pFighter = pFighter;
        pEntry->init();
        pEntry->autorelease();
        return pEntry;
    }
    return NULL;
}

CCSize MB_NodeRuleRankUnit::getUnitSize()
{
    static CCSize gSize = CCSizeZero;
    if (gSize.width == 0 || gSize.height == 0)
    {
        gSize = MB_NodeRuleRankUnit::create(NULL)->m_pNodeSize->getContentSize();
    }
    return gSize;
}

MB_NodeRuleRankUnit::MB_NodeRuleRankUnit()
{
    m_pPaiMingNode = NULL;
    m_pNumOneLine = NULL;
    m_NumOne = NULL;
    m_pNodeSize	 = NULL;
    m_pNodeRankNum	 = NULL;
    m_pSpriteFrame	 = NULL;
    m_pRoleHeader	 = NULL;
    m_pNodeLv	 = NULL;
    m_pLabelName	 = NULL;
    m_pLabelServer	 = NULL;
    m_pLabelWinRate	 = NULL;
    m_pLabelScore	 = NULL;
    m_pFighter = NULL;
}
MB_NodeRuleRankUnit::~MB_NodeRuleRankUnit()
{
    CC_SAFE_RELEASE_NULL(m_pPaiMingNode);
    CC_SAFE_RELEASE_NULL(m_pNumOneLine);
    CC_SAFE_RELEASE_NULL(m_NumOne);
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(m_pNodeRankNum);
    CC_SAFE_RELEASE_NULL(m_pSpriteFrame);
    CC_SAFE_RELEASE_NULL(m_pRoleHeader);
    CC_SAFE_RELEASE_NULL(m_pNodeLv);
    CC_SAFE_RELEASE_NULL(m_pLabelName);
    CC_SAFE_RELEASE_NULL(m_pLabelServer);
    CC_SAFE_RELEASE_NULL(m_pLabelWinRate);
    CC_SAFE_RELEASE_NULL(m_pLabelScore);
}
bool MB_NodeRuleRankUnit::init()
{
    CCNode* pNode = loadResource("res/worldwar_node_rank.ccbi");
    if(pNode)
    {
        addChild(pNode);
        onResetWnd();
        return true;
    }
    return false;
}
void MB_NodeRuleRankUnit::onResetWnd()
{
    if(!m_pFighter)return;
    
    m_pLabelName->setString(m_pFighter->getRoleName().c_str());
    if(m_pFighter->getFightTimes() == 0)
    {
        m_pLabelWinRate->setString("0%");
    }
    else
    {
        m_pLabelWinRate->setString(CCString::createWithFormat("%d%%",int((float)m_pFighter->getWinTimes()/(float)m_pFighter->getFightTimes()*100))->getCString());
    }
    m_pLabelScore->setString(CCString::createWithFormat("%d",m_pFighter->getScore())->getCString());
    
    if (m_pFighter->getRank()>1) {
        m_pNodeRankNum->setString(CCString::createWithFormat("%d",m_pFighter->getRank())->getCString());
    }
    else{
        m_pNumOneLine->setVisible(true);
        m_pPaiMingNode->setVisible(false);
        m_NumOne->setVisible(true);
    }
    
    m_pNodeLv->setString(CCString::createWithFormat("Lv.%d",m_pFighter->getLevel())->getCString());
    
    ServerList* pList = MB_ServerList::getInstance()->getServerListByID(int(m_pFighter->getRoleID()/1000000)-1);
    if(pList)m_pLabelServer->setString(pList->name.c_str());
    
    NSGameHelper::setRoleIcon(m_pRoleHeader, m_pFighter->getIsMale(), m_pFighter->getHead(), m_pFighter->getTitle());
}
bool MB_NodeRuleRankUnit::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_NumOne",CCNode*,m_NumOne);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize",CCNode*,m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeRankNum",CCLabelBMFont*,m_pNodeRankNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpriteFrame",CCSprite*,m_pSpriteFrame);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pRoleHeader",CCSprite*,m_pRoleHeader);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeLv",CCLabelBMFont*,m_pNodeLv);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelName",CCLabelTTF*,m_pLabelName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelServer",CCLabelTTF*,m_pLabelServer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelWinRate",CCLabelBMFont*,m_pLabelWinRate);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelScore",CCLabelBMFont*,m_pLabelScore);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNumOneLine",CCNode*,m_pNumOneLine);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pPaiMingNode",CCNode*,m_pPaiMingNode);
    
    
    return false;
}
SEL_MenuHandler MB_NodeRuleRankUnit::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onIconClicked",MB_NodeRuleRankUnit::onIconClicked);
    return NULL;
}
SEL_CCControlHandler MB_NodeRuleRankUnit::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}
void MB_NodeRuleRankUnit::onIconClicked(CCObject* pSender)
{
    MB_TARGET_PARENT(MB_LayerRuleFight, ptr)
    {
        if(ptr)ptr->sendpet_view_other(m_pFighter->getRoleID(),0);
    }
}


//////
MB_NodeHistoryUnit::MB_NodeHistoryUnit()
{
    m_pHist = NULL;
    m_pRichText = NULL;
}

MB_NodeHistoryUnit* MB_NodeHistoryUnit::create(Hist* pHist)
{
    MB_NodeHistoryUnit* pUnit = new MB_NodeHistoryUnit;
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

bool MB_NodeHistoryUnit::init()
{
    onResetWnd();
    return true;
}

void MB_NodeHistoryUnit::onResetWnd()
{
    if (m_pHist)
    {
        m_pRichText = new RichText();
        m_pRichText->autorelease();
        char buff[512] = {0};
        std::string strTime = "";
        setTime(m_pHist->getTime(),NULL,strTime);
        
        std::string richText = "";
        if (((m_pHist->getHistType() >> 6)&0x01) == 1)
        {
            richText = GET_CONFIG_VALUE("email_description.xml",1073 ,"des");
        }
        else
        {
            richText = GET_CONFIG_VALUE("email_description.xml",1074 ,"des");
        }
        
        sprintf(buff, "[color=65ff00]%s[/color]%s",strTime.c_str(),CCString::createWithFormat(richText.c_str(),m_pHist->getName().c_str(),m_pHist->getAddRepu())->getCString());
        
        m_pRichText->initWithString(buff, "", 22, CCSizeMake(600, 0), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
        this->addChild(m_pRichText);
        m_pRichText->setAnchorPoint(CCPointZero);
    }
}

CCSize MB_NodeHistoryUnit::getShowSize()
{
    return m_pRichText->getContentSize();
}



