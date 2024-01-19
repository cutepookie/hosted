//
//  MB_NodePerfectReward.cpp
//  ProjectMB
//
//  Created by yuanwugang on 14-9-26.
//
//

#include "MB_NodePerfectReward.h"
#include "MB_LayerChapterWnd.h"
#include "MB_NodeItemBook.h"
#include "MB_LocalProto.h"
#include "MB_FunctionMgr.h"
#include "MB_LayerChatMain.h"
MB_NodePerfectReward::MB_NodePerfectReward()
{
    m_pNodeReward = NULL;
    m_pScrollView = NULL;
    m_pBtGive = NULL;
    m_pBtCanNotGive = NULL;
    m_pChapterLayer = NULL;
    m_nState = kCanNotReceive;
    m_bShowRoleInfoPanel = true;
    SOCKET_MSG_REGIST(SC_BATTLE_PERFECT_REWARD, MB_NodePerfectReward);
    MB_LayerRoleInfoHeader::setMenuEnable(false,"MB_NodePerfectReward");
    MB_LayerChatMain::SetChatMainVisible(false,"MB_NodePerfectReward");
}
MB_NodePerfectReward::~MB_NodePerfectReward()
{
    CC_SAFE_RELEASE_NULL(m_pBtGive);
    CC_SAFE_RELEASE_NULL(m_pBtCanNotGive);
    CC_SAFE_RELEASE_NULL(m_pNodeReward);
    CC_SAFE_RELEASE_NULL(m_pScrollView);
    
    
    SOCKET_MSG_UNREGIST(SC_BATTLE_PERFECT_REWARD)
    MB_LayerRoleInfoHeader::setMenuEnable(true,"MB_NodePerfectReward");
//    MB_LayerChatMain::SetChatMainVisible(true,"MB_NodePerfectReward");
}
MB_NodePerfectReward* MB_NodePerfectReward::create(CCArray* array,int state)
{
    MB_NodePerfectReward* ptr = new MB_NodePerfectReward();
    if (ptr && ptr->init(array,state))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}
bool MB_NodePerfectReward::init(CCArray* array,int state)
{
    m_nState = state;
    
    CCNode* pNode = loadResource("res/pve_layer_perfectreward.ccbi");
    if(pNode)
	{
        addChild(NSGameHelper::createDisableTouchLayer());
		addChild(pNode);
        m_pScrollView = CCScrollView::create(m_pNodeReward->getContentSize());
        m_pScrollView->retain();
        m_pScrollView->setDirection(kCCScrollViewDirectionHorizontal);
        m_pNodeReward->removeAllChildren();
        m_pNodeReward->addChild(m_pScrollView);
        
        MB_LayerRoleInfoHeader::showRoleInfoHeader(true);
        MB_LayerRewardContainer* pContainer = MB_LayerRewardContainer::create(array,true);
        if (pContainer)
        {
            pContainer->setContentSize(m_pNodeReward->getContentSize());
            m_pScrollView->setContainer(pContainer);
        }
        onResetWnd();

		return true;
	}
	return false;
    
}
void MB_NodePerfectReward::onEnter()
{
    MB_ResWindow::onEnter();
    MB_TutorialMgr::getInstance()->SetModelDilogState("MB_LayerChapterWnd",false);
}
void MB_NodePerfectReward::onResetWnd()
{
    m_pBtGive->setVisible(true);
    if (m_nState == kCanNotReceive)
    {
        m_pBtGive->setVisible(false);
        m_pBtCanNotGive->setVisible(true);
    }
    else if (m_nState == kNoReceive)
    {
        m_pBtGive->setVisible(true);
        m_pBtCanNotGive->setVisible(false);
        m_pBtGive->setEnabled(true);
    }
    else if (m_nState == kHasReceive)
    {
        m_pBtGive->setVisible(true);
        m_pBtCanNotGive->setVisible(false);
        m_pBtGive->setEnabled(false);
    }
    
}
bool MB_NodePerfectReward::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    TutorialAssignLayerWindow
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeReward", CCNode*,m_pNodeReward);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtGive", CCMenuItemImage*,m_pBtGive);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtCanNotGive", CCMenuItemImage*,m_pBtCanNotGive);
    return false;
}
SEL_MenuHandler MB_NodePerfectReward::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_NodePerfectReward::onCloseClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCommitClicked",MB_NodePerfectReward::onCommitClicked);
    return NULL;
}
SEL_CCControlHandler MB_NodePerfectReward::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

void MB_NodePerfectReward::onCloseClick(CCObject* pSender)
{
    removeFromParent();
//    popWindow();
    if (m_pChapterLayer != NULL) {
        m_pChapterLayer->goMessageShow();
    }

}
void MB_NodePerfectReward::onCommitClicked(CCObject* pSender)
{
    TutorialTriggerComplete
    if (m_pChapterLayer != NULL) {
        m_pChapterLayer->onGetRewardClicked(this);
    }
//    MB_TARGET_PARENT(MB_LayerChapterWnd, ptr);
//    {
//        if(ptr)ptr->onGetRewardClicked(this);
//    }
}


void MB_NodePerfectReward::onMsgRecv(CCNode* node, SocketResponse* response)
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
    
    switch (Msg)
    {
        case SC_BATTLE_PERFECT_REWARD:
        {
            removeFromParent();
        }
        break;

        default:
            break;
    }
    
}
