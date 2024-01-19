//
//  MB_LayerCommand.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-10.
//
//

#include "MB_LayerCommand.h"
#include "MB_FunctionMgr.h"

MB_LayerCommand::MB_LayerCommand()
{
    m_pNodeHome = NULL;
    m_pNodeFriend = NULL;
    m_pNodeFormation = NULL;
    m_pNodeCallCrad = NULL;
    m_pNodeRoom = NULL;
    m_pNodeItem = NULL;
    m_pNodeFunctions = NULL;
    m_pSelectedSpr = NULL;
}

MB_LayerCommand::~MB_LayerCommand()
{
    CC_SAFE_RELEASE_NULL(m_pNodeHome);
    CC_SAFE_RELEASE_NULL(m_pNodeFriend);
    CC_SAFE_RELEASE_NULL(m_pNodeFormation);
    CC_SAFE_RELEASE_NULL(m_pNodeCallCrad);
    CC_SAFE_RELEASE_NULL(m_pNodeRoom);
    CC_SAFE_RELEASE_NULL(m_pNodeItem);
    CC_SAFE_RELEASE_NULL(m_pNodeFunctions);
    CC_SAFE_RELEASE_NULL(m_pSelectedSpr);
    
}

int getDaysInMonth(int y,int m)
{
    int d;
    static int day[]= {31,28,31,30,31,30,31,31,30,31,30,31};
    if (2==m)
    {
        bool b = ((y%4==0)&&(y%100))||((y%400)==0);
        d = b?29:28;
    }
    else
    {
        d=day[m-1];
    }
    return d;
}
bool MB_LayerCommand::init()
{
    rootNode = loadResource("res/main_layer_homebutton.ccbi");
    if (rootNode)
    {
        addChild(rootNode);
    }
    initFunctions();
    
    time_t tt = MB_ClientSocket::getInstance()->getServerTime();
    tm* pTm = localtime(&tt);
    int days = getDaysInMonth(pTm->tm_year+1900, pTm->tm_mon+1);
    int today = pTm->tm_mday;
    std::vector<int> login_record = MB_ItemMgr::getInstance()->getLoginRecordList();
    //    int index = 0;
    for (int i=days; i>0; --i)
    {
        if (today == i)
        {
            for (int j = 0;j < login_record.size(); j++)
            {
                if (i == login_record[j])
                {
                    isAutoTanChuSign = false;
                    break;
                }
            }
            break;
        }
    }
    if(isAutoTanChuSign)
    {
        schedule(schedule_selector(MB_LayerCommand::updateAddSign));
    }
    
    return true;
}
void MB_LayerCommand::updateAddSign(float dt)
{
    if (MB_TutorialMgr::getInstance()->getHasTutorialDilog()) {
        unschedule(schedule_selector(MB_LayerCommand::updateAddSign));
    }else if(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND))
    {
        MB_FunctionMgr::getInstance()->goFunction(kFunctionDaily, this);
        unschedule(schedule_selector(MB_LayerCommand::updateAddSign));
    }
}
bool MB_LayerCommand::onAssignCCBMemberVariable (CCObject* pTarget,
                                                 const char* pMemberVariableName,CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_home", CCNode*, m_pNodeHome);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_friend", CCNode*, m_pNodeFriend);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_formation", CCNode*, m_pNodeFormation);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_callcard", CCNode*, m_pNodeCallCrad);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_room", CCNode*, m_pNodeRoom);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_item", CCNode*, m_pNodeItem);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeFunctions", CCNode*, m_pNodeFunctions);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSelectedSpr", CCNode*, m_pSelectedSpr);
    
    if(MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode))return true;


    return false;
}

void MB_LayerCommand::setSelectedSprPos(int index)
{
    switch (index) {
        case 0:
            m_pSelectedSpr->setPositionX(54);
            break;
        case 1:
            m_pSelectedSpr->setPositionX(161);
            break;
        case 2:
            m_pSelectedSpr->setPositionX(267);
            break;
        case 3:
            m_pSelectedSpr->setPositionX(375);
            break;
        case 4:
            m_pSelectedSpr->setPositionX(481);
            break;
        case 5:
            m_pSelectedSpr->setPositionX(588);
            break;
    }
}
bool MB_LayerCommand::initFunctions()
{
    MB_FunctionMgr* pMgr = MB_FunctionMgr::getInstance();
    
    pMgr->bindEntry2Target(kFunctionHome, m_pNodeHome);
    pMgr->bindEntry2Target(kFunctionFormation, m_pNodeFormation);
    pMgr->bindEntry2Target(kFunctionBackpack, m_pNodeItem);
    pMgr->bindEntry2Target(kFunctionRoom, m_pNodeRoom);
    pMgr->bindEntry2Target(kFunctionToy, m_pNodeCallCrad);
    pMgr->bindEntry2Target(kFunctionFriend, m_pNodeFriend);
    return true;
}
