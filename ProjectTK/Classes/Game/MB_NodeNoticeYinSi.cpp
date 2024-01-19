//
//  MB_NodeNoticeYinSiYinSi.cpp
//  ProjectMB
//
//  Created by yuanwugang on 14-12-18.
//
//

#include "MB_NodeNoticeYinSi.h"
#include "MB_FunctionModule.h"
#include "MB_ActivatyMainLayer.h"
#include "MB_LoginNotice.h"


MB_NodeNoticeYinSi::MB_NodeNoticeYinSi()
{
    m_pNodeContent = NULL;
    m_pRichBoxContent = NULL;
}
MB_NodeNoticeYinSi::~MB_NodeNoticeYinSi()
{
    CC_SAFE_RELEASE_NULL(m_pNodeContent);
}

bool MB_NodeNoticeYinSi::onAssignCCBMemberVariable(CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeContent", CCNode*, m_pNodeContent);
    return false;
}
bool MB_NodeNoticeYinSi::init()
{
    MB_ResWindow::init();
    pRootNode = loadResource("res/activity_node_yinsi.ccbi");
    if (pRootNode != NULL)
    {
        this->addChild(pRootNode);
        return true;
    }
    return false;
}

void MB_NodeNoticeYinSi::setData(char* des)
{
    RichText*   m_pRichBoxContent2   = RichText::create(des,16,CCSizeMake(m_pNodeContent->getContentSize().width - 10, 0));
    m_pRichBoxContent2->setAnchorPoint(ccp(0,1));
    m_pRichBoxContent2->setColor(ccWHITE);
    
    m_pNodeContent->addChild(m_pRichBoxContent2);
    
    int addHeight = m_pRichBoxContent2->getContentSize().height;
    if (addHeight > 0)
    {
        m_pNodeContent->setContentSize(CCSizeMake(m_pNodeContent->getContentSize().width, m_pNodeContent->getContentSize().height + addHeight));
    }
    this->setContentSize(CCSizeMake(m_pNodeContent->getContentSize().width, m_pNodeContent->getContentSize().height));
    m_pRichBoxContent2->setPositionY(m_pNodeContent->getContentSize().height);
}
