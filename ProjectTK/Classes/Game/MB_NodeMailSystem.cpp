//
//  MB_NodeMailSystem.cpp
//  ProjectPM
//
//  Create by WenYong on 9/5/2014.
//
//
#include "MB_NodeMailSystem.h"
#include "MB_MailData.h"
#include "MB_SystemMailData.h"
#include "MB_LayerSystemMailDetail.h"
#include "MB_LayerMailView.h"

MB_NodeMailSystem::MB_NodeMailSystem()
{
    m_pMailTitle	 = NULL;
    m_pTimeText	 = NULL;
    m_nMailUID = 0;
    m_pNodeSize = NULL;
}
MB_NodeMailSystem::~MB_NodeMailSystem()
{
    CC_SAFE_RELEASE_NULL(m_pMailTitle);
    CC_SAFE_RELEASE_NULL(m_pTimeText);
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
}

bool MB_NodeMailSystem::check(uint64_t uid)
{
    sMailCell* p = MailMgr->queryMail(uid);
    
    return p!=NULL;
}

bool MB_NodeMailSystem::init(uint64_t nMailUid)
{
    if (!check(nMailUid))
    {
        return false;
    }
    
    CCNode* pNode = loadResource("res/mail_node_unit.ccbi");
    if(pNode)
	{
		addChild(pNode);
        m_nMailUID = nMailUid;
        onResetWnd();
		return true;
	}
	return false;
}

static void convertToRbfString(std::string& str)
{
    return;
}
/*
 uint64_t            mailUID;        //邮件唯一ID
 kmMailType          mailType;       //邮件类型
 uint32_t            senderID;       //邮件发送者的UID，0=系统发送的
 std::string         senderName;     //发送者名字,如果本邮件是系统邮件，则此字段为空
 std::string         content;        //内容
 uint32_t            time;           //发送时间(Unix时间戳)
 uint16_t            mailTemplateID; //邮件模版ID
 ParamListParser     paramList;      //动态类型参数列表
 sMailReward         mailReward;     //可领取奖励
 uint8_t             hisType;        //战报类型
 uint16_t            arg;            //战报附带参数
 */
void MB_NodeMailSystem::onResetWnd()
{
    sMailCell* pCell = MailMgr->queryMail(m_nMailUID);
    if (pCell)
    {
        const char* time_stamp = NSGameHelper::getDataTimeByUnixStamp(pCell->time);
        m_pTimeText->setString(time_stamp);
        const MB_SystemMailData* pData = MB_SystemDataMgr::getInstance()->queryMailDataByMailTid(pCell->mailTemplateID);
        if (pData)
        {
            m_pMailTitle->removeAllChildren();
            RichText* pRichBox = RichText::create();
            m_pMailTitle->addChild(pRichBox);

            std::string txt = pData->getTitle();
            txt = pCell->paramList.calculateNewRbfStrByOldRbfStr(txt);
            convertToRbfString(txt);
            if (pRichBox)
            {
                pRichBox->setString(txt.c_str());
                pRichBox->setAnchorPoint(CCPointZero);
                pRichBox->setPosition(ccp(pRichBox->getPosition().x,m_pMailTitle->getContentSize().height - pRichBox->getContentSize().height));
            }
        }
        else
        {
            m_pMailTitle->removeAllChildren();
            RichText* pRichBox = RichText::create();
            m_pMailTitle->addChild(pRichBox);
            std::string txt = "";
            if(pCell->mailType == kmMailType_SystemReward)
            {
                txt = "[color=ffffff]系统奖励[/color]";
            }
            else
            {
                txt = "[color=ffffff]系统信息[/color]";
            }
            convertToRbfString(txt);
            if (pRichBox)
            {
                pRichBox->setString(txt.c_str());
                pRichBox->setAnchorPoint(CCPointZero);
                pRichBox->setPosition(ccp(pRichBox->getPosition().x, m_pMailTitle->getContentSize().height- pRichBox->getContentSize().height));
            }

        }
    }
}
bool MB_NodeMailSystem::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    TutorialAssignLayerWindow
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMailTitle",CCNode*,m_pMailTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTimeText",CCLabelTTF*,m_pTimeText);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeSize", CCNode*, m_pNodeSize);
	return false;
}
SEL_MenuHandler MB_NodeMailSystem::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
SEL_CCControlHandler MB_NodeMailSystem::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onViewEmailClicked",MB_NodeMailSystem::onViewEmailClicked);
	return NULL;
}
void MB_NodeMailSystem::onViewEmailClicked(CCObject* pSender)
{
    TutorialTriggerComplete
    MB_LayerSystemMailDetail* pWnd = MB_LayerSystemMailDetail::create(m_nMailUID);
    if (pWnd)
    {
        MB_TARGET_PARENT(MB_LayerMailView, ptr);
        if (ptr)
        {
            ptr->pushWindow(pWnd);
        }
    }
}

MB_NodeMailSystem* MB_NodeMailSystem::create(uint64_t nMailUid)
{
    MB_NodeMailSystem* pInstance = new MB_NodeMailSystem;
    if (pInstance && pInstance->init(nMailUid))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}

CCSize MB_NodeMailSystem::getNodeSize()
{
    MB_NodeMailSystem* pTemp = new MB_NodeMailSystem;
    if (pTemp)
    {
        CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
        CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/mail_node_unit.ccbi",pTemp);
        CC_SAFE_RELEASE_NULL(pCCBReader);
        if (pNode)
        {
            CCSize sz = pTemp->m_pNodeSize->getContentSize();
            CC_SAFE_RELEASE_NULL(pTemp);
            return sz;
        }
    }
    CC_SAFE_RELEASE_NULL(pTemp);
    return CCSize(0,0);
}
