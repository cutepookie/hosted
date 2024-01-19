//
//  MB_LayerScrollMessage.cpp
//  ProjectMB
//
//  Create by wenyong on 10/12/2014.
//
//
#include "MB_LayerScrollMessage.h"

MB_LayerScrollMessage::MB_LayerScrollMessage()
{
    text_message	 = NULL;
    m_onOk	 = NULL;
    m_onCancel	 = NULL;
    m_onOk2	 = NULL;
    m_pScrollNotice	 = NULL;
    m_pTarget = NULL;
    m_pHandler = NULL;
    m_pScrollTTF = NULL;
    m_pView = NULL;
}
MB_LayerScrollMessage::~MB_LayerScrollMessage()
{
    CC_SAFE_RELEASE_NULL(text_message);
    CC_SAFE_RELEASE_NULL(m_onOk);
    CC_SAFE_RELEASE_NULL(m_onCancel);
    CC_SAFE_RELEASE_NULL(m_onOk2);
    CC_SAFE_RELEASE_NULL(m_pScrollNotice);
    m_pTarget = NULL;
    m_pHandler = NULL;
}
bool MB_LayerScrollMessage::init()
{
    CCNode* pNode = loadResource("res/message_layer_popupmessage.ccbi");
    if(pNode)
	{
		addChild(pNode);
        onInitialized();
		return true;
	}
	return false;
}

void MB_LayerScrollMessage::onInitialized()
{
    m_onOk->setVisible(false);
    m_onCancel->setVisible(false);
    
    m_pView = CCScrollView::create(m_pScrollNotice->getContentSize());
    m_pView->setDirection(kCCScrollViewDirectionVertical);
    m_pScrollTTF = CCLabelTTF::create("", text_message->getFontName(), text_message->getFontSize());
    m_pView->setContainer(m_pScrollTTF);
}
void MB_LayerScrollMessage::onResetWnd()
{

}
bool MB_LayerScrollMessage::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"text_message",CCLabelTTF*,text_message);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_onOk",CCControlButton*,m_onOk);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_onCancel",CCControlButton*,m_onCancel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_onOk2",CCControlButton*,m_onOk2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pScrollNotice",CCNode*,m_pScrollNotice);
	return false;
}
SEL_MenuHandler MB_LayerScrollMessage::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
SEL_CCControlHandler MB_LayerScrollMessage::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onConfirmClicked",MB_LayerScrollMessage::onConfirmClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onBackClicked",MB_LayerScrollMessage::onBackClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onConfirmClicked2",MB_LayerScrollMessage::onConfirmClicked2);
	return NULL;
}
void MB_LayerScrollMessage::onConfirmClicked(CCObject* pSender)
{
}
void MB_LayerScrollMessage::onBackClicked(CCObject* pSender)
{
}
void MB_LayerScrollMessage::onConfirmClicked2(CCObject* pSender)
{
    if (m_pTarget)
    {
        (m_pTarget->*m_pHandler)(pSender);
    }
    removeFromParent();
}

void MB_LayerScrollMessage::setCallBack(CCObject* pTarget,SEL_MenuHandler hander)
{
    m_pTarget = pTarget;
    m_pHandler = hander;
}

void MB_LayerScrollMessage::setMessage(const char* p)
{
    if (p)
    {
        m_pScrollTTF->setString(p);
        m_pView->setContentOffset(ccp(0, m_pView->getContentSize().height-m_pScrollTTF->getContentSize().width));
    }
}
