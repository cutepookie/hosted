//
//  MB_NodeNoticeActive.cpp
//  ProjectMB
//
//  Created by yuanwugang on 14-12-18.
//
//

#include "MB_NodeNoticeActive.h"
#include "MB_FunctionModule.h"
#include "MB_ActivatyMainLayer.h"
#include "MB_LoginNotice.h"
#include "MB_NodeNoticePic.h"
MB_NodeNoticeActive::MB_NodeNoticeActive()
{
    m_pNodeContent = NULL;
    m_pRichBoxContent = NULL;
    m_pTTFName = NULL;
    m_pTTFTime = NULL;
    m_nActiveID = -1;
//    SOCKET_MSG_REGIST(SC_ACTIVITY_INFO, MB_NodeNoticeActive);
}
MB_NodeNoticeActive::~MB_NodeNoticeActive()
{
    CC_SAFE_RELEASE_NULL(m_pNodeContent);
    CC_SAFE_RELEASE_NULL(m_pTTFName);
    CC_SAFE_RELEASE_NULL(m_pTTFTime);
//    SOCKET_MSG_UNREGIST(SC_ACTIVITY_INFO);

}

bool MB_NodeNoticeActive::onAssignCCBMemberVariable(CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeContent",CCNode*,m_pNodeContent);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFName",CCLabelTTF*,m_pTTFName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFTime",CCLabelTTF*,m_pTTFTime);
    return false;
}
SEL_CCControlHandler MB_NodeNoticeActive::onResolveCCBCCControlSelector(CCObject * pTarget,const char* pSelectorName)
{
    return NULL;
}
cocos2d::SEL_MenuHandler MB_NodeNoticeActive::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}


bool MB_NodeNoticeActive::init()
{
    MB_ResWindow::init();
    CCNode* pNode = loadResource("res/activity_node_show.ccbi");
    if (pNode != NULL)
    {
        this->addChild(pNode);
        return true;
    }
    return false;

}

void MB_NodeNoticeActive::setData(MB_MoneyEevntData * data)
{
    m_pRichBoxContent   = RichText::create(data->getDescription(),20,CCSizeMake(m_pNodeContent->getContentSize().width,0));
    m_nActiveID = data->getActivityID();

    int addHeight = m_pRichBoxContent->getContentSize().height - m_pNodeContent->getContentSize().height;

    if (addHeight > 0)
    {
        m_pNodeContent->setContentSize(CCSize(m_pNodeContent->getContentSize().width,m_pNodeContent->getContentSize().height+addHeight));
        this->setContentSize(CCSize(m_pNodeContent->getContentSize().width,m_pNodeContent->getContentSize().height+addHeight));
    }else
    {
        this->setContentSize(m_pNodeContent->getContentSize());
    }
    m_pRichBoxContent->setAnchorPoint(ccp(0,1));
    m_pRichBoxContent->setPositionY(m_pNodeContent->getContentSize().height);
    m_pNodeContent->addChild(m_pRichBoxContent);
    
    uint32_t closeTime = data->getStopTime();
    if (closeTime > 0) {
        int timelift = closeTime - MB_ClientSocket::getInstance()->getServerTime();
        char databuf[50];
        sprintf(databuf,"剩余时间:%d天%02d时%02d分",timelift/(3600*24),timelift%(3600*24)/3600,timelift%3600/60);
        m_pTTFTime->setString(databuf);
    }
    else
    {
        m_pTTFTime->setString("永久");
    }
    m_pTTFName->setString(data->getActivyName());
    
  
}


void MB_NodeNoticeActive::onResetWnd(void)
{
    
}




MB_NodeNoticeActiveTitle::MB_NodeNoticeActiveTitle()
{
    m_pTTFTitle = NULL;
    m_pNodeSize = NULL;
    m_pTTFTitle2 = NULL;
}
MB_NodeNoticeActiveTitle::~MB_NodeNoticeActiveTitle()
{
    CC_SAFE_RELEASE_NULL(m_pTTFTitle);
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(m_pTTFTitle2);
}


bool MB_NodeNoticeActiveTitle::onAssignCCBMemberVariable(CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFTitle",CCLabelTTF*,m_pTTFTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFTitle2",CCLabelTTF*,m_pTTFTitle2);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize",CCNode*,m_pNodeSize);
    
    return false;
}
bool MB_NodeNoticeActiveTitle::init()
{
    MB_ResWindow::init();
    CCNode* pNode = loadResource("res/activity_node_show_title.ccbi");
    if (pNode != NULL)
    {
        this->addChild(pNode);
        this->setContentSize(m_pNodeSize->getContentSize());
        return true;
    }
    return false;
}



MB_NodeNotice::MB_NodeNotice()
{
    m_pNodeContent = NULL;
    m_pRichBoxContent = NULL;
}
MB_NodeNotice::~MB_NodeNotice()
{
    CC_SAFE_RELEASE_NULL(m_pNodeContent);
}

bool MB_NodeNotice::onAssignCCBMemberVariable(CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeContent", CCNode*, m_pNodeContent);
    return false;
}
bool MB_NodeNotice::init()
{
    MB_ResWindow::init();
    pRootNode = loadResource("res/activity_node_notice.ccbi");
    if (pRootNode != NULL)
    {
        this->addChild(pRootNode);
        return true;
    }
    return false;
}

void MB_NodeNotice::setData(char* des,CCNode* nnp)
{
    float tempFloat = 0;
    if (nnp!=NULL) {
        pRootNode->addChild(nnp);
        tempFloat = ((MB_NodeNoticePic*)nnp)->m_pSpritePic->getContentSize().height+15;
        nnp->setPositionY(m_pNodeContent->getPositionY()+15);
        m_pNodeContent->setPositionY(m_pNodeContent->getPositionY()- tempFloat);
    }
    m_pRichBoxContent   = RichText::create(des,24,CCSizeMake(m_pNodeContent->getContentSize().width - 10, 0));
    m_pRichBoxContent->setAnchorPoint(ccp(0,1));
    m_pRichBoxContent->setColor(ccWHITE);

    m_pNodeContent->addChild(m_pRichBoxContent);
    
    int addHeight = m_pRichBoxContent->getContentSize().height - m_pNodeContent->getContentSize().height;
    if (addHeight > 0)
    {
        m_pNodeContent->setContentSize(CCSizeMake(m_pNodeContent->getContentSize().width, m_pNodeContent->getContentSize().height + addHeight));
    }
    this->setContentSize(CCSizeMake(m_pNodeContent->getContentSize().width, m_pNodeContent->getContentSize().height+tempFloat));
    m_pRichBoxContent->setPositionY(m_pNodeContent->getContentSize().height);
    
}
