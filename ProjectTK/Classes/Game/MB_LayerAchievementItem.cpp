//
//  MB_LayerAchievementItem.cpp
//  ProjectPM
//
//  Create by WenYong on 6/5/2014.
//
//
#include "MB_LayerAchievementItem.h"
#include "MB_TaskConfigure.h"
#include "MB_TaskSystemInterface.h"
#include "MB_FunctionModule.h"
MB_LayerAchievementItem::MB_LayerAchievementItem()
{
    m_pLine =NULL;
    m_pState2 = NULL;
    m_pState = NULL;
    size	 = NULL;
    m_pTTFTaskDescription	 = NULL;
    m_pTTFSchedule	 = NULL;
    m_pSpriteTaskFrame	 = NULL;
    m_pSpriteTaskHead	 = NULL;
    m_pNodeReaward_start	 = NULL;
    m_pSpriteRewardHead	 = NULL;
    m_pSpriteRewardFrame	 = NULL;
    m_pDataSource = NULL;
    m_pTTFTaskTitle = NULL;
    m_pAllCount = NULL;
    m_pAnimation = NULL;
    m_pNodeComplate = NULL;
}
MB_LayerAchievementItem::~MB_LayerAchievementItem()
{
    CC_SAFE_RELEASE_NULL(m_pLine);
    CC_SAFE_RELEASE_NULL(m_pState2);
    CC_SAFE_RELEASE_NULL(m_pState);
    CC_SAFE_RELEASE_NULL(size);
    CC_SAFE_RELEASE_NULL(m_pTTFTaskDescription);
    CC_SAFE_RELEASE_NULL(m_pTTFSchedule);
    CC_SAFE_RELEASE_NULL(m_pSpriteTaskFrame);
    CC_SAFE_RELEASE_NULL(m_pSpriteTaskHead);
    CC_SAFE_RELEASE_NULL(m_pNodeReaward_start);
    CC_SAFE_RELEASE_NULL(m_pSpriteRewardHead);
    CC_SAFE_RELEASE_NULL(m_pSpriteRewardFrame);
    CC_SAFE_RELEASE_NULL(m_pTTFTaskTitle);
    CC_SAFE_RELEASE_NULL(m_pAllCount);
    CC_SAFE_RELEASE_NULL(m_pAnimation);
    CC_SAFE_RELEASE_NULL(m_pNodeComplate);
    
}

MB_LayerAchievementItem* MB_LayerAchievementItem::create(MB_TaskServerData* data)
{
    MB_LayerAchievementItem* ptr = new MB_LayerAchievementItem();
    
    if (ptr && ptr->init(data))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}
bool MB_LayerAchievementItem::init(MB_TaskServerData* data)
{
    m_pDataSource = data;
    
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/achievement_node_unit.ccbi", this);
    m_pAnimation = pCCBReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pAnimation);
    CC_SAFE_RELEASE(pCCBReader);
    
    
    if(pNode)
    {
        addChild(pNode);
    }
    else
    {
        return false;
    }
    
    onResetWnd();
    return true;
}


void MB_LayerAchievementItem::onResetWnd()
{
    if(!m_pDataSource)return;
    
    MB_TaskData* pData = MB_TaskConfigure::getInstance()->getTaskDataById(m_pDataSource->getTaskId());
    
    if (pData)
    {
        
        m_pTTFTaskTitle->setString(pData->getName().c_str());
        m_pTTFTaskDescription->setString(pData->getDescription().c_str());
        uint8_t status = m_pDataSource->getStatus();
//        m_pTTFSchedule->setString("");

        
        char buff[65] = {};
        char strNum1[30] = {};
        char strNum2[30] = {};
        int tempInt = NSGameHelper::FormatNumber2(strNum1,m_pDataSource->getValue());
        NSGameHelper::FormatNumber(strNum2,pData->getTaskCondition()->getValue());
        sprintf(buff, "%s",strNum1);
        m_pTTFSchedule->setString(buff);
        sprintf(buff, "/ %s",strNum2);
        m_pAllCount->setString(buff);
        m_pAllCount->setPositionX((-145.6f+(tempInt-1)*10));
        
        if (status == TASK_STATUS_UNACCEPT)
        {
            m_pNodeComplate->setVisible(false);
        }
        else if(status  == TASK_STATUS_ACCEPTED)
        {
            m_pState2->setVisible(true);
            m_pNodeComplate->setVisible(false);
        }
        else if(status == TASK_STATUS_COMPLATE)
        {
            m_pNodeComplate->setVisible(true);
        }
        else if(status == TASK_STATUS_COMITED)
        {
            m_pState->setVisible(true);
            m_pNodeComplate->setVisible(false);
        }
        else
        {
            m_pNodeComplate->setVisible(false);
        }
//
        if (m_pSpriteTaskHead)
        {
            pData->setAchievmentIcon(m_pSpriteTaskHead);
        }
        
        if (m_pSpriteTaskHead) {
            NSGameHelper::setSpriteFrame(m_pSpriteTaskHead,pData->getIcon().c_str());
            NSGameHelper::creatMaskSprite(m_pSpriteTaskHead,NULL,true);
        }
        //奖励
        if(pData->getTaskRewardArray()->count() == 0)return;
        MB_TaskReward* pReward = dynamic_cast<MB_TaskReward*>(pData->getTaskRewardArray()->objectAtIndex(0));
        if(pReward)
        {
            char buff[100] = {0};
            sprintf(buff, "%d",pReward->getValue());
            m_pNodeReaward_start->setString(buff);
        }
    }
}
bool MB_LayerAchievementItem::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"size",CCNode*,size);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"ttf_task_title",CCLabelTTF*,m_pTTFTaskTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"ttf_task_description",CCLabelTTF*,m_pTTFTaskDescription);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"schedule",CCLabelBMFont*,m_pTTFSchedule);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"sprite_TaskFrame",CCSprite*,m_pSpriteTaskFrame);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"sprite_TaskHead",CCSprite*,m_pSpriteTaskHead);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeRewardCount",CCLabelBMFont*,m_pNodeReaward_start);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"sprite_RewardHead",CCSprite*,m_pSpriteRewardHead);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"sprite_RewardFrame",CCSprite*,m_pSpriteRewardFrame);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pAllCount",CCLabelBMFont*,m_pAllCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pState",CCNode*,m_pState);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pState2",CCNode*,m_pState2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLine", CCNode*, m_pLine);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_complate", CCNode*, m_pNodeComplate);
    
    return false;
}


void MB_LayerAchievementItem::onStatusClicked(CCObject* pSender)
{
    NSGameFunction::CCFunctionInterface *pInterface = NULL;
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionTask ,&pInterface))
    {
        MB_TaskSystemInterface* pInterfaceTemp = dynamic_cast<MB_TaskSystemInterface*>(pInterface);
        if (pInterfaceTemp)
        {
            MB_Message::sharedMB_Message()->showMessage("",15);
            pInterfaceTemp->sendtask_operate(TASK_OPERATE_COMMIT, m_pDataSource->getTaskId());
        }
    }
}

SEL_MenuHandler MB_LayerAchievementItem::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}
SEL_CCControlHandler MB_LayerAchievementItem::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onStatusClicked", MB_LayerAchievementItem::onStatusClicked);
    return NULL;
}

