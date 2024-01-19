//
//  MB_LayerSystemMailDetail.cpp
//  ProjectPM
//
//  Create by WenYong on 10/5/2014.
//
//
#include "MB_LayerSystemMailDetail.h"
#include "MB_SystemMailData.h"
#include "MB_NodeItemBook.h"
#include "MB_MailData.h"
#include "MB_LayerMailView.h"

#include "MB_ItemData.h"
MB_LayerSystemMailDetail* MB_LayerSystemMailDetail::create(uint64_t uid)
{
    MB_LayerSystemMailDetail* pInstance = new MB_LayerSystemMailDetail;
    if (pInstance && pInstance->init(uid))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

MB_LayerSystemMailDetail::MB_LayerSystemMailDetail()
{
    m_pScal9Sprite	 = NULL;
    m_pNodeContent	 = NULL;
    m_pMailTitle	 = NULL;
    m_pBtnCommit	 = NULL;
    m_pRichText = NULL;
    m_pNodeRewardList	 = NULL;
    m_bTensiled = true;
    m_bRewardMail = false;
    m_pTemplateValueArray = new CCArray;
    m_bShowRoleInfoPanel = true;
}
MB_LayerSystemMailDetail::~MB_LayerSystemMailDetail()
{
    CC_SAFE_RELEASE_NULL(m_pScal9Sprite);
    CC_SAFE_RELEASE_NULL(m_pNodeContent);
    CC_SAFE_RELEASE_NULL(m_pMailTitle);
    CC_SAFE_RELEASE_NULL(m_pBtnCommit);
    CC_SAFE_RELEASE_NULL(m_pNodeRewardList);
    CC_SAFE_RELEASE_NULL(m_pTemplateValueArray);
}
bool MB_LayerSystemMailDetail::init(uint64_t uid)
{
    CCNode* pNode = loadResource("res/mail_layer_reward.ccbi");
    if(pNode)
	{
        addChild(NSGameHelper::createDisableTouchLayer12());
		addChild(pNode);
        setMailUid(uid);
		return true;
	}
	return false;
}

void MB_LayerSystemMailDetail::setMailUid(uint64_t uid)
{
    m_nMailUID = uid;
    onResetWnd();
}
void MB_LayerSystemMailDetail::preProcessTitleText(std::string& text,sMailCell* ret)
{
    text = ret->paramList.calculateNewRbfStrByOldRbfStr(text);
}
void MB_LayerSystemMailDetail::onResetWnd()
{
    sMailCell* pCell = MailMgr->queryMail(m_nMailUID);
    m_bHasReward = false;
    if (pCell)
    {
        const MB_SystemMailData* pData = MB_SystemDataMgr::getInstance()->queryMailDataByMailTid(pCell->mailTemplateID);
        if (pData)
        {
            std::string text = pData->getTitle();
            NSGameHelper::convertToRbfString(text);
            preProcessTitleText(text,pCell);
            setTitle(text.c_str());
            text = pData->getContent();
            preProcessText(text,pCell);
            NSGameHelper::convertToRbfString(text);
            setContent(text.c_str());
        }
        else
        {
            if (pCell->senderID == 0)
            {
                std::string text = "";
                if(pCell->mailType == kmMailType_SystemReward)
                {
                    text = "[color=ffffff]系统奖励[/color]";
                }
                else
                {
                    text = "[color=ffffff]系统信息[/color]";
                }
                
                NSGameHelper::convertToRbfString(text);
                setTitle(text.c_str());
                text = "[color=ffffff]" + pCell->content;
                preProcessText(text,pCell);
                text += "[/color]";
//                NSGameHelper::convertToRbfString(text);
                setContent(text.c_str());
            }
        }
        
        m_bRewardMail = pCell->mailType == kmMailType_SystemReward;
        
        updateRewardNode(pCell);
    }
}

/*
 struct sMailReward
 {
 KeyValue_Map    ItemRewards;
 KeyValue_Map    PetRewards;
 };
 */
void MB_LayerSystemMailDetail::updateRewardNode(sMailCell* pCell)
{
    if (pCell)
    {
        if (pCell->mailReward.PetRewards.empty() && pCell->mailReward.ItemRewards.empty())
        {
            // if no reward here,the ui should be tensiled
            if (m_bTensiled)
            {
                if(m_pScal9Sprite)
                {
                    CCSize sz = m_pScal9Sprite->getContentSize();
                    sz.height = sz.height-m_pNodeRewardList->getContentSize().height;
                    m_pScal9Sprite->setContentSize(sz);
                }
                m_pNodeRewardList->removeAllChildren();
                m_bTensiled = false;
            }
            m_bHasReward = false;
        }
        else
        {
            if (!m_bTensiled)
            {
                CCSize sz = m_pScal9Sprite->getContentSize();
                sz.height = sz.height+m_pNodeRewardList->getContentSize().height;
                m_pScal9Sprite->setContentSize(sz);
                m_bTensiled = true;
            }
            
            m_pNodeRewardList->removeAllChildren();
            m_pTemplateValueArray->removeAllObjects();
            
            NSGameHelper::mailRewardConvert2ValueTemplateArray(&(pCell->mailReward), m_pTemplateValueArray);
            
            MB_LayerRewardContainer* pReward = MB_LayerRewardContainer::create(m_pTemplateValueArray);
            m_bHasReward = true;
            if (pReward)
            {
                CCScrollView* pScroll = CCScrollView::create(m_pNodeRewardList->getContentSize());
                pScroll->setDirection(kCCScrollViewDirectionHorizontal);
                pReward->setContentSize(m_pNodeRewardList->getContentSize());
                pScroll->setContainer(pReward);
                m_pNodeRewardList->addChild(pScroll);
                CCSize sz = pScroll->getContentSize();
                if (sz.width<pReward->getContentSize().width)
                {
                    sz.width = pReward->getContentSize().width;
                }
                pReward->setContentSize(sz);
            }
        }
    }
}
void MB_LayerSystemMailDetail::preProcessText(std::string& str, sMailCell* ret)
{
    if (ret == NULL)
    {
        return;
    }
    str = ret->paramList.calculateNewRbfStrByOldRbfStr(str);
    std::string temp;
    char tempChar[512] = {};
    if(kmMailType_PresonMail == ret->mailType)
    {
        temp = "[color=ffffff]" + ret->senderName + "[/color]";
        temp += "[br][color=ffffff]"+str + "[/color]";
        str  = temp;
    }
    
    if (ret->mailType == kmMailType_Pvp)
    {
        sprintf(tempChar,str.c_str(),
                ret->senderName.c_str(),ret->arg);
        str = tempChar;
    }
    else if(ret->mailType == kmMailType_TreasureRob)
    {
        sprintf(tempChar,str.c_str(),
                ret->senderName.c_str(),
                MB_ItemMgr::getInstance()->getItemNameByTid(ret->arg).c_str());
        str = tempChar;
    }
    
    if (!ret->mailReward.ItemRewards.empty() || !ret->mailReward.PetRewards.empty())
    {
        str += "[color=ffffff][br]获得:[br][/color]";
    }
    KeyValue_It it;
    it = ret->mailReward.ItemRewards.begin();
    while (it != ret->mailReward.ItemRewards.end())
    {
        str += MB_ItemMgr::getInstance()->getItemNameByTid(it->first);
        str += ":";
        sprintf(tempChar, "%d",it->second);
        str += tempChar;
        str += ";";
        it++;
    }
    
    it = ret->mailReward.PetRewards.begin();
    while (it != ret->mailReward.PetRewards.end())
    {
        MB_PetTemplate* pgt;
        pgt = MB_PetMgr::getInstance()->getPetTemplateByID(it->first);
        str += pgt?pgt->getPetName():"";
        str += ":";
        sprintf(tempChar, "%d",it->second);
        str += tempChar;
        str += ";";
        it++;
    }
}
void MB_LayerSystemMailDetail::setTitle(const char* pTitle)
{
    if (pTitle == NULL)
    {
        return;
    }
    
    RichText* pRichBox = RichText::create(pTitle,20);
    m_pMailTitle->removeAllChildren();
    m_pMailTitle->addChild(pRichBox);
    pRichBox->setString(pTitle);
    pRichBox->cocos2d::CCNode::setAnchorPoint(CCPointZero);
//    pRichBox->setPosition(ccp(pRichBox->getPositionX()+m_pMailTitle->getContentSize().width/2.0-pRichBox->getContentSize().width/2.0, m_pMailTitle->getContentSize().height- pRichBox->getContentSize().height));
}
void MB_LayerSystemMailDetail::setContent(const char* pContent)
{
    if (pContent == NULL)
    {
        return;
    }
    if (m_pRichText==NULL)
    {
        
        m_pRichText = RichText::create(pContent,20,CCSizeMake(m_pNodeContent->getContentSize().width, 0),kCCTextAlignmentLeft);
        CCScrollView* pScrollView = CCScrollView::create(m_pNodeContent->getContentSize());
        pScrollView->setDirection(kCCScrollViewDirectionVertical);
        m_pNodeContent->addChild(pScrollView);
        pScrollView->setContainer(m_pRichText);
        float h1 = m_pRichText->getTextureRect().size.height;
        float h2 = m_pNodeContent->getContentSize().height;
        pScrollView->setContentOffset(ccp(0, h2-h1));
    }
    else
    {
        m_pRichText->setString(pContent);
    }
}
bool MB_LayerSystemMailDetail::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    TutorialAssignLayerWindow
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pScal9Sprite",CCScale9Sprite*,m_pScal9Sprite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeContent",CCNode*,m_pNodeContent);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMailTitle",CCNode*,m_pMailTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtnCommit",CCControlButton*,m_pBtnCommit);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeRewardList",CCNode*,m_pNodeRewardList);
	return false;
}
SEL_MenuHandler MB_LayerSystemMailDetail::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerSystemMailDetail::onCloseClicked);
	return NULL;
}
SEL_CCControlHandler MB_LayerSystemMailDetail::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onComitClicked",MB_LayerSystemMailDetail::onComitClicked);
	return NULL;
}

void MB_LayerSystemMailDetail::onCloseClicked(CCObject* pSender)
{
    popWindow();
}

void MB_LayerSystemMailDetail::deleteEmail()
{
    MB_Message::sharedMB_Message()->showMessage("",15);
    SOCKET_MSG_REGIST(SC_MAIL_DELETE, MB_LayerSystemMailDetail);
    MailMgr->sendmail_delete(m_nMailUID);
}
void MB_LayerSystemMailDetail::onComitClicked(CCObject* pSender)
{
    if (m_bHasReward || m_bRewardMail)
    {
        MB_Message::sharedMB_Message()->showMessage("",15);
        SOCKET_MSG_REGIST(SC_MAIL_DRAW_REWARD, MB_LayerSystemMailDetail);
        TutorialTriggerComplete
        MailMgr->sendmail_draw_reward(m_nMailUID);
    }
    else
    {
        deleteEmail();
    }
}

void MB_LayerSystemMailDetail::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    
    //将socket数据读取到序列化结构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    if (Msg == SC_MAIL_DRAW_REWARD)
    {
        MB_Message::sharedMB_Message()->removeALLMessage();
        SOCKET_MSG_UNREGIST(SC_MAIL_DRAW_REWARD);
        if(m_bHasReward)
        {
            MB_LayerRewardMore* pWnd = MB_LayerRewardMore::create(m_pTemplateValueArray);
            if (pWnd)
            {
                MB_TARGET_PARENT(MB_LayerMailView, ptr)
                {
                    if (ptr)
                    {
                        ptr->pushWindow(pWnd);
                    }
                }
            }
        }
        NSGameHelper::setControlButtonTitleAllState(m_pBtnCommit, "关闭");
        m_bHasReward = false;
        onCloseClicked(NULL);
    }
    if (Msg == SC_MAIL_DELETE)
    {
        MB_Message::sharedMB_Message()->removeALLMessage();
        SOCKET_MSG_UNREGIST(SC_MAIL_DELETE);
        onCloseClicked(NULL);
    }
}
