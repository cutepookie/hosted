//
//  MB_NodeTaskItem.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-2.
//
//

#include "MB_NodeTaskItem.h"
#include "MB_TaskConfigure.h"
#include "../Common/GameLib/CCGameLib.h"
#include "MB_LayerTaskMain.h"
#include "MB_FunctionMgr.h"
#include "Game.h"
#include "MB_TutorialMgr.h"
#include "MB_AbsolvedConfigure.h"
//#include "MB_TaskSystemData.h"
MB_NodeTaskItem::MB_NodeTaskItem()
{
    m_pNodeRewardCount = NULL;
    m_pState = NULL;
    m_pDataSource = NULL;
    m_pTitle = NULL;
    m_pDescription = NULL;
    m_pNodeComplate = NULL;
    m_pBtnStatus = NULL;
    m_pSchedule = NULL;
    m_pNodeChangePage = NULL;
    m_pNodeSize = NULL;
    m_bIsLastObj = false;
    m_pAllCount = NULL;
    m_pLine = NULL;
}

MB_NodeTaskItem::~MB_NodeTaskItem()
{
    CC_SAFE_RELEASE_NULL(m_pNodeRewardCount);
    CC_SAFE_RELEASE_NULL(m_pState);
    CC_SAFE_RELEASE_NULL(m_pDataSource);
    CC_SAFE_RELEASE_NULL(m_pTitle);
    CC_SAFE_RELEASE_NULL(m_pDescription);
    CC_SAFE_RELEASE_NULL(m_pNodeComplate);
    CC_SAFE_RELEASE_NULL(m_pBtnStatus);
    CC_SAFE_RELEASE_NULL(m_pSchedule);
    CC_SAFE_RELEASE_NULL(m_pNodeChangePage);
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(m_pAllCount);
    CC_SAFE_RELEASE_NULL(m_pLine);
    
}

MB_NodeTaskItem* MB_NodeTaskItem::create(MB_TaskServerData* pData,bool bIsLastObj)
{
    MB_NodeTaskItem* pInstance = new MB_NodeTaskItem();
    pInstance->m_bIsLastObj = bIsLastObj;
    if (pInstance && pInstance->init(pData))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return NULL;
}
void MB_NodeTaskItem::setPosition(float x, float y)
{
    CCNode::setPosition(x, y);
    
}
CCSize g_szItemSize = CCSizeZero;
CCSize MB_NodeTaskItem::getItemSize()
{
    if(g_szItemSize.width == 0 || g_szItemSize.height == 0)
    {
        g_szItemSize = MB_NodeTaskItem::create(NULL,false)->m_pNodeSize->getContentSize();
    }
    return g_szItemSize;
}

bool MB_NodeTaskItem::init(MB_TaskServerData* pData)
{

    CC_SAFE_RELEASE_NULL(m_pDataSource);
    m_pDataSource = pData;
    CC_SAFE_RETAIN(m_pDataSource);
    
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/task_node_unit.ccbi", this);
    if (pNode)
    {
        addChild(pNode);
    }
    
    CC_SAFE_RELEASE_NULL(pCCBReader);

    onResetWnd();
    if(m_bIsLastObj)
    {
        m_pLine->setVisible(false);
    }
    return true;
}

/*
任务状态  1:未接  2：已接  3：已完成 4:已提交（用于每日任务和成就的显示）
#define TASK_STATUS_UNACCEPT    1
#define TASK_STATUS_ACCEPTED    2
#define TASK_STATUS_COMPLATE    3
#define TASK_STATUS_COMITED     4
 */
void MB_NodeTaskItem::onResetWnd()
{
    if (m_pDataSource == NULL)return;
    
    MB_TaskData* pData = MB_TaskConfigure::getInstance()->getTaskDataById(m_pDataSource->getTaskId());
    
    if (pData)
    {
        char strNum1[10] = {};
        sprintf(strNum1, "%d",((MB_TaskReward*)pData->getTaskRewardArray()->objectAtIndex(0))->getValue());
        m_pNodeRewardCount->setString(strNum1);
        m_pNodeChangePage->setVisible(false);
        m_pTitle->setString(pData->getName().c_str());
        m_pDescription->setString(pData->getDescription().c_str());
        uint8_t status = m_pDataSource->getStatus();
//        CCLog("status===========%d==========%s",status,pData->getName().c_str());
//        m_pSpriteComplate->setVisible(status == TASK_STATUS_COMPLATE);
        m_pNodeComplate->setVisible(true);
        m_pSchedule->setString("");
        if (status == TASK_STATUS_UNACCEPT)
        {
            m_pBtnStatus->setEnabled(true);
            //NSGameHelper::setControlButtonTitleAllState(m_pBtnStatus, "可接受");
        }
        else{
            if (pData->getTaskCondition()->getShowType() == 2)
            {
                char buff[65] = {};
                char strNum1[30] = {};
                char strNum2[30] = {};
                int tempInt = NSGameHelper::FormatNumber2(strNum1,m_pDataSource->getValue());
                NSGameHelper::FormatNumber(strNum2,pData->getTaskCondition()->getValue());
                sprintf(buff, "%s",strNum1);
                m_pSchedule->setString(buff);
                sprintf(buff, "/  %s",strNum2);
                m_pAllCount->setString(buff);
                m_pAllCount->setPositionX((-145.6f+(tempInt-1)*10));
            }
            if(status  == TASK_STATUS_ACCEPTED)
            {
                m_pNodeComplate->setVisible(false);
                m_pBtnStatus->setEnabled(false);
                if (pData->getChangePageID() != 0) {
                    m_pNodeChangePage->setVisible(true);
                }
            }
            else if(status == TASK_STATUS_COMPLATE)
            {
                m_pNodeChangePage->setVisible(true);
                m_pBtnStatus->setEnabled(true);
            }
            else if(status == TASK_STATUS_COMITED)
            {
                m_pBtnStatus->setEnabled(false);
                m_pNodeComplate->setVisible(false);
                m_pNodeChangePage->setVisible(false);
                m_pState->setVisible(true);
            }
        }
    }
}

bool MB_NodeTaskItem::onAssignCCBMemberVariable(CCObject* pTarget,
                                                const char* pMemberVariableName,
                                                CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeRewardCount", CCLabelBMFont*, m_pNodeRewardCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pState", CCSprite*, m_pState);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_task_title", CCLabelTTF*, m_pTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_task_description", CCLabelTTF*,m_pDescription);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_complate", CCNode*,m_pNodeComplate);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btn_status", CCControlButton*,m_pBtnStatus);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "schedule", CCLabelBMFont*, m_pSchedule);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_changePage", CCNode*, m_pNodeChangePage);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "size", CCNode*, m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pAllCount", CCLabelBMFont*, m_pAllCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLine", CCNode*, m_pLine);
    
    
    return false;
}

SEL_MenuHandler MB_NodeTaskItem::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    
    return NULL;
}

SEL_CCControlHandler MB_NodeTaskItem::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onStatusClicked", MB_NodeTaskItem::onStatusClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onChangePageClicked",MB_NodeTaskItem::onChangePageClicked);
    return NULL;
}

void MB_NodeTaskItem::onStatusClicked(CCObject* pSender)
{
    TutorialTriggerComplete
    MB_TARGET_PARENT(MB_LayerTaskMain, ptr);
    if (ptr)
    {
        if (TASK_STATUS_UNACCEPT == m_pDataSource->getStatus())
        {
            ptr->onStatusClicked(TASK_OPERATE_ACCEPTE, m_pDataSource->getTaskId());
//            m_pBtnStatus->setEnabled(false);
        }
        else if(TASK_STATUS_COMPLATE == m_pDataSource->getStatus())
        {
            ptr->onStatusClicked(TASK_OPERATE_COMMIT, m_pDataSource->getTaskId());
//            m_pBtnStatus->setEnabled(false);
        }
        else
        {
            MB_Message::sharedMB_Message()->showMessage("错误的操作");
        }
    }
}

void MB_NodeTaskItem::onChangePageClicked(CCObject* pSender)
{
    bool hasTutorialDilog = MB_TutorialMgr::getInstance()->getHasTutorialDilog();
    TutorialTriggerComplete
    MB_TaskData* pData = MB_TaskConfigure::getInstance()->getTaskDataById(m_pDataSource->getTaskId());
    if (pData->getChangePageID() == 0)
    {
        return;
    }
    
    if (pData->getChangePageID() == kFunctionAbsolved) {
        m_bToPageID = -1;
    }
    if (hasTutorialDilog) {
        MB_FunctionMgr::getInstance()->goFunction(kFunctionHome,this);
        
    }else
    {
        MB_FunctionMgr::getInstance()->goFunction(pData->getChangePageID(),this);
    }
}
