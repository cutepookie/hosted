//
//  MB_AchievementComplate.cpp
//  ProjectPM
//
//  Created by crimoon on 14-6-7.
//
//
#include "MB_AchievementComplate.h"
#include "MB_LayerAchievementItem.h"
#include "MB_TaskConfigure.h"
#include "MB_FunctionMgr.h"
#include "MB_TaskSystemInterface.h"
#include "MB_FunctionModule.h"

MB_AchievementComplate::MB_AchievementComplate()
{
    ttf_task_description	 = NULL;
    m_pWCLabel	 = NULL;
    m_pSpriteTaskHead	 = NULL;
    m_pDataSource = NULL;
    ttf_task_title = NULL;
    m_pAnimation = NULL;
    m_pDataSource = NULL;
    m_bRun = false;
}
MB_AchievementComplate::~MB_AchievementComplate()
{
    m_pAnimation->setAnimationCompletedCallback(NULL,NULL);
    CC_SAFE_RELEASE_NULL(ttf_task_description);
    CC_SAFE_RELEASE_NULL(m_pWCLabel);
    CC_SAFE_RELEASE_NULL(m_pSpriteTaskHead);
    CC_SAFE_RELEASE_NULL(ttf_task_title);
    CC_SAFE_RELEASE_NULL(m_pAnimation);
    CC_SAFE_RELEASE_NULL(m_pDataSource);
}

MB_AchievementComplate* MB_AchievementComplate::create(MB_TaskServerData* pData)
{
    MB_AchievementComplate* ptr = new MB_AchievementComplate();
    
    if (ptr && ptr->init(pData))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}
bool MB_AchievementComplate::init(MB_TaskServerData* pData)
{
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/achievement_node_done.ccbi", this);
    if(pNode)
	{
		addChild(pNode);
	}
    else
    {
        CC_SAFE_RELEASE(pCCBReader);
        return false;
    }
    m_pAnimation = pCCBReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pAnimation);
    CC_SAFE_RELEASE(pCCBReader);
    
    
    CC_SAFE_RELEASE_NULL(m_pDataSource);
    m_pDataSource = pData;
    if (m_pDataSource!=NULL) {
        m_pDataSource->retain();
    }
    onResetWnd();
    return true;
}

void MB_AchievementComplate::onEnter()
{
    MB_ResWindow::onEnter();
    if (!m_bRun)
    {
        m_pAnimation->setAnimationCompletedCallback(this, callfunc_selector(MB_AchievementComplate::onAnimationCallback));
        m_pAnimation->runAnimationsForSequenceNamed("Default Timeline");
        m_bRun = true;
    }
}

void MB_AchievementComplate::onExit()
{
    MB_ResWindow::onExit();
    if(m_pAnimation)m_pAnimation->setAnimationCompletedCallback(NULL,NULL);
}
void MB_AchievementComplate::onResetWnd()
{
    if (m_pDataSource == NULL) {
        return;
    }
    MB_TaskData* pData = MB_TaskConfigure::getInstance()->getTaskDataById(m_pDataSource->getTaskId());
    
    if (pData)
    {
        char buff[65] = {};
        ttf_task_title->setString(pData->getName().c_str());
        if (pData->getTaskCondition()->getShowType() == 2)
        {
            char strNum1[30] = {};
            char strNum2[30] = {};
            NSGameHelper::FormatNumber(strNum1,m_pDataSource->getValue());
            NSGameHelper::FormatNumber(strNum2,pData->getTaskCondition()->getValue());
            sprintf(buff, "[%s%s/%s]",pData->getDescription().c_str(),strNum1,strNum2);
        }else
        {
            sprintf(buff, "[%s]",pData->getDescription().c_str());
        }
        ttf_task_description->setString(buff);
        if (m_pSpriteTaskHead) {
            NSGameHelper::setSpriteFrame(m_pSpriteTaskHead,pData->getIcon().c_str());
        }
        
        m_pWCLabel->setPositionX(-8.6f+ttf_task_description->getContentSize().width-98.8f);
    }
}
bool MB_AchievementComplate::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"ttf_task_title",CCLabelTTF*,ttf_task_title);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"ttf_task_description",CCLabelTTF*,ttf_task_description);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"sprite_TaskHead",CCSprite*,m_pSpriteTaskHead);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pWCLabel",CCNode*,m_pWCLabel);
    
	return false;
}




SEL_CCControlHandler MB_AchievementComplate::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}


void MB_AchievementComplate::onAnimationCallback()
{
    NSGameFunction::CCFunctionInterface* pInterface = NULL;
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionTask,&pInterface))
    {
        MB_TaskSystemInterface* pTaskInterface = dynamic_cast<MB_TaskSystemInterface*>(pInterface);
        if (pTaskInterface)
        {
            pTaskInterface->playAchievementMsg();
        }
    }
    if(m_pAnimation)m_pAnimation->setAnimationCompletedCallback(NULL,NULL);
    removeFromParent();
}

