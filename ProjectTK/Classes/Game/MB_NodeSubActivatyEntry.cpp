//
//  MB_NodeSubActivatyEntry.cpp
//  ProjectPM
//
//  Created by chk on 14-4-30.
//
//

#include "MB_NodeSubActivatyEntry.h"
#include "MB_CommandActivaty.h"
#include "Game.h"
#include "MB_FunctionModule.h"
#include "MB_ActivatyMainLayer.h"
#include "MB_ActivatyMgr.h"
#include "MB_FunctionConfig.h"

bool MB_NodeSubActivatyEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_CommandActivaty*>(pDataSource);
    
    return m_pDataSource != NULL;
}


MB_NodeSubActivatyEntry::MB_NodeSubActivatyEntry()
{
    m_pChoose = NULL;
    m_pName = NULL ;
    m_pIcon = NULL;
    m_pMenuItem = NULL;
    m_pNodeTre = NULL;
    m_pTreNumber = NULL;
    m_pNodeEffect = NULL;
    m_pMainWnd = NULL;
}

MB_NodeSubActivatyEntry::~MB_NodeSubActivatyEntry()
{
    CC_SAFE_RELEASE(m_pChoose);
    CC_SAFE_RELEASE(m_pName);
    CC_SAFE_RELEASE(m_pIcon);
    CC_SAFE_RELEASE(m_pMenuItem);
    CC_SAFE_RELEASE(m_pNodeTre);
    CC_SAFE_RELEASE(m_pTreNumber);
    CC_SAFE_RELEASE(m_pNodeEffect);
}
void MB_NodeSubActivatyEntry::setMainWnd(MB_ActivatyMainLayer* wnd)
{
    m_pMainWnd = wnd;
}
void MB_NodeSubActivatyEntry::onEntranceClicked(CCObject* pSender)
{
//    MB_TARGET_PARENT(MB_ActivatyMainLayer, ptr)
//    if (ptr)
//    {
//        ptr->movetoShow(this->getTag());
//    }
}

bool MB_NodeSubActivatyEntry::init()
{
    MB_ResWindow::init();
    CCFunctionInterface* pInterface = dynamic_cast<CCFunctionInterface*>(m_pDataSource);
    MB_FunctionItem* pItem = NULL;
    if(pInterface)pItem = MB_FunctionConfigure::getInstance()->queryFunctionItemByType(pInterface->getFunctionType());
    
    if(pItem)
    {
        CCNode * node= loadResource(pItem->getActivateCcbi().c_str());
        if(node) this->addChild(node);
    }
    else
    {
        CCNode * node= loadResource("res/activity_node_btn.ccbi");
        if(node) this->addChild(node);
    }
    
    if(m_pNodeEffect)m_pNodeEffect ->setVisible(false);
    return true;
}


void MB_NodeSubActivatyEntry::onResetWnd()
{
    onInitializedWnd();
}

void MB_NodeSubActivatyEntry::onMsgRecv(CCNode* node, SocketResponse* response)
{
}

cocos2d::SEL_MenuHandler MB_NodeSubActivatyEntry::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onEventClick", MB_NodeSubActivatyEntry::onEntranceClicked);
    return NULL;
}

cocos2d::extension::SEL_CCControlHandler MB_NodeSubActivatyEntry::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName)
{
    return NULL;
}

void MB_NodeSubActivatyEntry::onInitializedWnd()
{
}


bool MB_NodeSubActivatyEntry::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pName", CCLabelBMFont *,m_pName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pIcon", CCSprite *,m_pIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMenuItem", CCMenuItemImage *, m_pMenuItem);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeTre", CCNode *,m_pNodeTre);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTreNumber", CCLabelTTF *,m_pTreNumber);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeEffect", CCNode *, m_pNodeEffect);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pChoose", CCNode *, m_pChoose);

    if(strcmp("menu",pMemberVariableName) == 0 && this == pTarget)
    {
        if(dynamic_cast<CCMenu *>(pNode) != NULL)
        {
            ((CCMenu *)pNode)->setSwallowsTouches(false);
        }
    }
    return false;
}


void MB_NodeSubActivatyEntry::setSelect(bool select)
{
    m_pMenuItem->setEnabled(!select);
    if(m_pChoose)m_pChoose->setVisible(select);
//    m_pName->setVisible(!select);

}
