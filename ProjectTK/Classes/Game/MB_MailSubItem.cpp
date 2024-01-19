//
//  MB_MailSubItem
//  ProjectTK
//
//  Created by lic
//
//

#include "MB_MailSubItem.h"
#include "MB_MailData.h"
#include "MB_MailMainView.h"
#include "MB_DataPVP.h"
#include "MB_GameInfoEnum.h"
MB_MailSubItem::MB_MailSubItem()
{
    m_pResultSpr_victory= NULL;
    m_pResultSpr_lose   = NULL;
    m_pAgree            = NULL;
    m_pDelete           = NULL;
    m_pRefuse           = NULL;
    m_pReply            = NULL;
    m_pTake             = NULL;
    m_pTime             = NULL;
    m_pmenu             = NULL;
    m_mailUid           = 0;
    m_pReplay           = NULL;
    m_pSizeNode         = NULL;
    m_pLabelTitle       = NULL;
    Description         = NULL;
    m_pMenu             = NULL;
}

MB_MailSubItem::~MB_MailSubItem()
{
    CC_SAFE_RELEASE(m_pResultSpr_victory);
    CC_SAFE_RELEASE(m_pResultSpr_lose);
    CC_SAFE_RELEASE(m_pAgree);
    CC_SAFE_RELEASE(m_pDelete);
    CC_SAFE_RELEASE(m_pRefuse);
    CC_SAFE_RELEASE(m_pReply);
    CC_SAFE_RELEASE(m_pTake);
    CC_SAFE_RELEASE(m_pTime);
    CC_SAFE_RELEASE(m_pmenu);
    CC_SAFE_RELEASE(m_pReplay);
    CC_SAFE_RELEASE(m_pSizeNode);
    CC_SAFE_RELEASE(m_pLabelTitle);
    CC_SAFE_RELEASE(Description);
    CC_SAFE_RELEASE(m_pMenu);
}


bool MB_MailSubItem::onAssignCCBMemberVariable(CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Agree", CCNode*, m_pAgree);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Delete", CCNode*, m_pDelete);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Refuse", CCNode*, m_pRefuse);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Reply", CCNode*, m_pReply);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Replay", CCNode*, m_pReplay);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pResultSpr_victory", CCSprite*, m_pResultSpr_victory);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pResultSpr_lose", CCSprite*, m_pResultSpr_lose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Take", CCNode*, m_pTake);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Time", CCLabelTTF*, m_pTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "menu", CCMenu*, m_pmenu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "size", CCNode*, m_pSizeNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTitle", CCLabelTTF*, m_pLabelTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Description", CCLabelTTF*, Description);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMenu", CCMenu*, m_pMenu);
    return false;
}

CCSize MB_MailSubItem::getUiDesignSize()
{
    return m_pSizeNode->getContentSize();
}

SEL_MenuHandler MB_MailSubItem::onResolveCCBCCMenuItemSelector(CCObject * pTarget,const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnClickReplay",MB_MailSubItem::OnClickReplay);
    return NULL;
}

bool MB_MailSubItem::init()
{
    MB_ResWindow::init();
    CCNode* pNode = loadResource("res/report_node_unit.ccbi");
    this->addChild(pNode);
    onInitDidFinish();
    return true;
}

void MB_MailSubItem::onInitDidFinish()
{
    m_uiDesignSize = m_pSizeNode->getContentSize();
    onSetRbfText("没有初始化我啊 ！！！！");
}

void MB_MailSubItem::OnClickReplay(CCObject* pSender)
{
    MailMgr->sendhist_replay(MailMgr->queryMailTabel(m_mailUid),m_mailUid);
}

void MB_MailSubItem::onSetRbfText(std::string str)
{
    Description->setString(str.c_str());
}

void MB_MailSubItem::onResetWnd(void)
{
    if(m_pAgree)
        m_pAgree->setVisible(false);
    if(m_pDelete)
        m_pDelete->setVisible(false);
    if(m_pRefuse)
        m_pRefuse->setVisible(false);
    if(m_pReply)
        m_pReply->setVisible(false);
    if(m_pTake)
        m_pTake->setVisible(false);
    if(m_pReplay)
        m_pReplay->setVisible(false);
    
    sMailCell* pmc;
    pmc = MailMgr->queryMail(m_mailUid);
    if (pmc)
    {
        switch (pmc->mailType)
        {
            case kmMailType_SystemHint://系统提示消息邮件
                m_pDelete->setVisible(true);
                break;
                
            case kmMailType_SystemReward://系统奖励邮件
                m_pTake->setVisible(true);
                break;
                
            case kmMailType_SystemAppendFriend://系统好友添加提示
            case kmMailType_SystemJoinUnion://系统加盟提示
                m_pRefuse->setVisible(true);
                m_pAgree->setVisible(true);
                break;
                
            case kmMailType_PresonMail://个人邮件
                m_pReply->setVisible(true);
                m_pDelete->setVisible(true);
                break;
                
            case kmMailType_UnionMail://联盟邮件
                m_pReply->setVisible(true);
                m_pDelete->setVisible(true);
                break;
            case kmMailType_Pvp:            //精灵榜战报
                m_pReplay->setVisible(true);
                break;
            case kmMailType_TreasureRob:        //夺宝战报
                m_pReplay->setVisible(true);
                break;
            case kmMailType_None:
                break;
                
            default:
                break;
        }
        
        //描述富文本
        onSetRbfText(MailMgr->queryMailRbfContent(m_mailUid));
        if(pmc->mailType==kmMailType_Pvp){
            std::string  str =MailMgr->queryMailTitle(m_mailUid);
            m_pLabelTitle->setString(str.c_str());
        }
        uint16_t tempID = MailMgr->queryMail(m_mailUid)->mailTemplateID;
        if (tempID==80||tempID==128||tempID==144)//挑战成功
        {
            m_pResultSpr_victory->setVisible(true);
            m_pResultSpr_lose->setVisible(false);
        }else
        {
            m_pResultSpr_victory->setVisible(false);
            m_pResultSpr_lose->setVisible(true);
        }
        
        //日期
        int days;
        char temp[1024];
        int  passhour = MB_ClientSocket::getInstance()->getServerTime();
        passhour = (passhour- pmc->time)/3600;
        if(passhour < 0){
            
            passhour = 0;
        }
        days = passhour/24;
        int lasthour = passhour %24;
        time_t nowtime = MB_ClientSocket::getInstance()->getServerTime();
        struct tm *now= localtime(&nowtime);
        lasthour = now->tm_hour - lasthour;
        if(lasthour < 0){
            
            days +=1;
        }
        if(days > 0)
        {
            sprintf(temp,
                    GET_GAMEINFO(kmGameInfo_Mail_Last).c_str(),
                    days);
        }
        else
        {
            sprintf(temp,"%s",GET_GAMEINFO(kmGameInfo_Mail_Today).c_str());
        }
        m_pTime->setString(temp);
    }
    
    //to do sth. here.
}
