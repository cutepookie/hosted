//
//  MB_NodeReportBox.cpp
//  ProjectTK
//
//  Created by crimoon00007 on 13-12-25.
//
//

#include "MB_NodeReportBox.h"
#include "../Common/RichText.h"
static void convertToRbfString(std::string& str)
{
    for (int i = 0; i<str.length(); ++i)
    {
        if (str[i] == '{')
        {
            str[i] = '<';
        }
        else if(str[i] == '}')
        {
            str[i] = '>';
        }
    }
}
MB_NodeReportBox::MB_NodeReportBox()
{
    m_pMenuBeatBack = NULL;
    m_pMenuReplay = NULL;
    m_pTimeText = NULL;
    m_pNodeRichBox = NULL;
    m_pRichBox = NULL;
    m_pNodeSize = NULL;
    m_iReportTime = 0;
    m_iReportUid = 0;
}
MB_NodeReportBox::~MB_NodeReportBox()
{
    CC_SAFE_RELEASE(m_pMenuBeatBack);
    CC_SAFE_RELEASE(m_pMenuReplay);
    CC_SAFE_RELEASE(m_pTimeText);
    CC_SAFE_RELEASE(m_pNodeRichBox);
    CC_SAFE_RELEASE(m_pNodeSize);
    m_iReportTime = 0;
    m_iReportUid = 0;
}

bool MB_NodeReportBox::init()
{
    MB_ResWindow::init();

    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);

    CCNode* pMain = pCCBReader->readNodeGraphFromFile("res/report_node_unit.ccbi",this);
    if (!pMain)
    {
        return false;
    }

    addChild(pMain);

    CC_SAFE_RELEASE(pCCBReader);

    m_pRichBox = RichText::create();
    if (!m_pRichBox)
    {
        m_pRichBox->setAnchorPoint(ccp(0, 1));
        return false;
    }
    m_pRichBox->setContentSize(m_pNodeRichBox->getContentSize());

    m_pNodeRichBox->addChild(m_pRichBox);

    return true;
}

bool MB_NodeReportBox::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"BeatBack",CCNode*,        m_pMenuBeatBack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"Replay",  CCNode*,        m_pMenuReplay);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"Time",    CCLabelTTF*,    m_pTimeText);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"RichBoxPosition", CCNode*,m_pNodeRichBox);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"size", CCNode*,m_pNodeSize);
    return false;
}
SEL_MenuHandler MB_NodeReportBox::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"OnClickBeatBack",MB_NodeReportBox::onBeatBackClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"OnClickReplay",MB_NodeReportBox::onReplayClicked);
    return NULL;
}


SEL_CCControlHandler MB_NodeReportBox::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

void MB_NodeReportBox::onBeatBackClicked(CCObject* obj)
{
    MB_TARGET_PARENT(MB_ReportBoxDelegate, ptr);
    if (ptr)
    {
        ptr->onBeatBackClicked(this);
    }
}
void MB_NodeReportBox::onReplayClicked(CCObject* obj)
{
    MB_TARGET_PARENT(MB_ReportBoxDelegate, ptr);
    if (ptr)
    {
        ptr->onReplayClicked(this);
    }
}
void MB_NodeReportBox::getReportInfo(p_pvp_replay_info& info)const
{
    info.attackerName = m_ReportInfo.attackerName;
    info.attackerNewRank = m_ReportInfo.attackerNewRank;
    info.defenderName = m_ReportInfo.defenderName;
    info.defenderNewRank = m_ReportInfo.defenderNewRank;
    info.replayUid = m_ReportInfo.replayUid;
    info.time = m_ReportInfo.time;
    
}
void MB_NodeReportBox::setReportInfo(const p_pvp_replay_info& info)
{
    char richBoxText[512] = {};
    // 301 is the tid of the rich-text
    std::string richText = GET_CONFIG_VALUE("email_description.xml",
                                            301 ,
                                            "des");
    m_ReportInfo.attackerName = info.attackerName;
    m_ReportInfo.attackerNewRank = info.attackerNewRank;
    m_ReportInfo.defenderName = info.defenderName;
    m_ReportInfo.defenderNewRank = info.defenderNewRank;
    m_ReportInfo.replayUid = info.replayUid;
    m_ReportInfo.time = info.time;

    
    if (!richText.empty())
    {
        convertToRbfString(richText);
        sprintf(richBoxText, richText.c_str(),info.attackerName.c_str(),info.defenderName.c_str(),info.attackerName.c_str(),info.attackerNewRank);
        setRichBoxString(richBoxText);
    }

    setReportUid(info.replayUid);
    setVisible(true);
    setTime(info.time);
}
void MB_NodeReportBox::setTime(uint32_t time)
{
    m_iReportTime = time;
    char buf[64] = {};

    uint16_t day = (MB_ClientSocket::getInstance()->getServerTime()-time)/(24*60*60);
    if (day == 0)
    {
        strcpy(buf,"今日");
    }
    else
    {
        sprintf(buf,"%d天前",day);
    }

    setTimeLable(buf);
}
void MB_NodeReportBox::setTimeLable(const char* pData)
{
    if (pData!=NULL
        && m_pTimeText!=NULL)
    {
        m_pTimeText->setString(pData);
    }
}
uint32_t MB_NodeReportBox::getTime()const
{
    return m_iReportTime;
}
void MB_NodeReportBox::setRichBoxString(const char* pString)
{
    if (m_pRichBox && pString)
    {
//        sRbfContent* pcontent;
//        pcontent = (sRbfContent*)m_pRichBox->getRbContent();
//        pcontent->text = pString;
//        pcontent->IsLockHeight  = false;
//        pcontent->lockWidth     = m_pNodeRichBox->getContentSize().width;
//        pcontent->lockHeight    = m_pNodeRichBox->getContentSize().height;
//        m_pRichBox->reparse();
//        m_pRichBox->setPosition(m_pRichBox->getPosition().x, m_pNodeRichBox->getContentSize().height- m_pRichBox->getContentSize().height);
        m_pRichBox->setString(pString);
    }
}

void MB_NodeReportBox::visableBeatBackMenu(bool bVisable)
{
    CC_ASSERT(m_pMenuBeatBack);
    m_pMenuBeatBack->setVisible(bVisable);
}
bool MB_NodeReportBox::isVisableBeatBackMenu()
{
    CC_ASSERT(m_pMenuBeatBack);
    return m_pMenuBeatBack->isVisible();
}
void MB_NodeReportBox::visableReplayMenu(bool bVisbale)
{
    CC_ASSERT(m_pMenuReplay);
    m_pMenuReplay->setVisible(bVisbale);
}
bool MB_NodeReportBox::isVisableReplayMenu()
{
    CC_ASSERT(m_pMenuReplay);
    return m_pMenuReplay->isVisible();
}

bool MB_NodeReportBox::getNodeSize(CCSize& sz)
{
    if (m_pNodeSize)
    {
        sz = m_pNodeSize->getContentSize();
        return true;
    }
    return false;
}
