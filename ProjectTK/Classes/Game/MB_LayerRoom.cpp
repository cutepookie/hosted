#include "MB_LayerRoom.h"
#include "MB_TutorialMgr.h"
#include "MB_TaskSystemInterface.h"
#include "MB_FunctionMgr.h"
#include "MB_AchievementInterface.h"
#include "MB_GiftsInterface.h"
MB_LayerRoom::MB_LayerRoom()
{
    for (int i=0; i<5; i++) {
        m_pTxtFlag[i] = NULL;
        m_pNodeFlag[i] = NULL;
    }
    
    CCUserDefault::sharedUserDefault()->setBoolForKey("MB_LayerRoom",true);
    m_bShowRoleInfoPanel = true;
    m_bShowHomeButton = true;
        this->schedule(schedule_selector(MB_LayerRoom::tick),5);
}

MB_LayerRoom::~MB_LayerRoom()
{
    for (int i=0; i<5; i++) {
        CC_SAFE_RELEASE_NULL(m_pTxtFlag[i]);
        CC_SAFE_RELEASE_NULL(m_pNodeFlag[i]);
    }
    CCUserDefault::sharedUserDefault()->setBoolForKey("MB_LayerRoom",false);
}
bool MB_LayerRoom::init()
{
    CCNode* pNode = loadResource("res/room_layer.ccbi");
    if(pNode)
	{
		addChild(pNode);
        onResetWnd();
		return true;
	}
	return false;
}
void MB_LayerRoom::onExit()
{
    PlayBackGround(kmBackGround_Normal);
    MB_FunctionMainWnd::onExit();
}

void MB_LayerRoom::onEnterTransitionDidFinish()
{
    MB_FunctionMainWnd::onEnterTransitionDidFinish();
    PlayBackGround(ksSound_MyRoom);
}
void MB_LayerRoom::onCloseClick(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionHome, this);
}

void MB_LayerRoom::onResetWnd()
{
    int nCount = 0;
    char buff[25] = {};
    NSGameFunction::CCFunctionInterface *pInterface = NULL;
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionTask ,&pInterface))
    {
        MB_TaskSystemInterface* pInterfaceTemp = dynamic_cast<MB_TaskSystemInterface*>(pInterface);
        nCount = pInterfaceTemp->getComplateTaskCount();
        if (nCount>0) {
            m_pNodeFlag[0]->setVisible(true);
            if (nCount>99) {
                m_pTxtFlag[0]->setString("!");
            }else
            {
                sprintf(buff, "%d",nCount);
                m_pTxtFlag[0]->setString(buff);
            }
        }else
        {
            m_pNodeFlag[0]->setVisible(false);
        }
    }
    
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionTask ,&pInterface))
    {
        MB_TaskSystemInterface* pInterfaceTemp = dynamic_cast<MB_TaskSystemInterface*>(pInterface);
        nCount = pInterfaceTemp->getAchievementCompleteCount();
        if (nCount>0) {
            m_pNodeFlag[1]->setVisible(true);
            if (nCount>99) {
                m_pTxtFlag[1]->setString("!");
            }else
            {
                sprintf(buff, "%d",nCount);
                m_pTxtFlag[1]->setString(buff);
            }
        }else
        {
            m_pNodeFlag[1]->setVisible(false);
        }
    }
    
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kActivatyGifts ,&pInterface))
    {
        MB_GiftsInterface* pInterfaceTemp = dynamic_cast<MB_GiftsInterface*>(pInterface);
        MB_DailyRewrdInfo* info = NULL;
        info = pInterfaceTemp->getInfoByType(eGiftTime);
        if (info) {
            nCount = info->getEnableCount();
            if (nCount>0) {
                m_pNodeFlag[4]->setVisible(true);
                if (nCount>99) {
                    m_pTxtFlag[4]->setString("!");
                }else
                {
                    sprintf(buff, "%d",nCount);
                    m_pTxtFlag[4]->setString(buff);
                }
            }else
            {
                m_pNodeFlag[4]->setVisible(false);
            }
        }
        info = pInterfaceTemp->getInfoByType(eGiftLevel);
        if (info) {
            nCount = info->getEnableCount();
            if (nCount>0) {
                m_pNodeFlag[2]->setVisible(true);
                if (nCount>99) {
                    m_pTxtFlag[2]->setString("!");
                }else
                {
                    sprintf(buff, "%d",nCount);
                    m_pTxtFlag[2]->setString(buff);
                }
            }else
            {
                m_pNodeFlag[2]->setVisible(false);
            }
        }
        info = pInterfaceTemp->getInfoByType(eGiftMLogin);
        if (info) {
            nCount = info->getEnableCount();
            if (nCount>0) {
                m_pNodeFlag[3]->setVisible(true);
                if (nCount>99) {
                    m_pTxtFlag[3]->setString("!");
                }else
                {
                    sprintf(buff, "%d",nCount);
                    m_pTxtFlag[3]->setString(buff);
                }
            }else
            {
                m_pNodeFlag[3]->setVisible(false);
            }
        }
    }
}

void MB_LayerRoom::tick(float dt)
{
    MB_FunctionMainWnd::tick(dt);
    onResetWnd();
}
bool MB_LayerRoom::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    TutorialAssignLayerWindow
    char str1[] = "m_pTxtFlag1";
    char str2[] = "m_pNodeFlag1";
    for (int i = 0; i < 5; i++) {
        str1[10] = i + '1';
        str2[11] = i + '1';
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, str1, CCLabelBMFont *, m_pTxtFlag[i]);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, str2, CCNode *, m_pNodeFlag[i]);
    }
	return false;
}


SEL_MenuHandler MB_LayerRoom::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerRoom::onCloseClick);
    return NULL;
}

SEL_CCControlHandler MB_LayerRoom::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBSXSClicked", MB_LayerRoom::onBSXSClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSLRWClicked", MB_LayerRoom::onSLRWClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onLXDLLBClicked", MB_LayerRoom::onLXDLLBClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onDJLBClicked", MB_LayerRoom::onDJLBClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onZXJLClicked", MB_LayerRoom::onZXJLClicked);
    return NULL;
}
void MB_LayerRoom::onSLRWClicked(CCObject* pSender)
{
    TutorialTriggerComplete
    NSGameFunction::CCFunctionInterface *pInterface = NULL;
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionTask ,&pInterface))
    {
        MB_TaskSystemInterface* pInterfaceTemp = dynamic_cast<MB_TaskSystemInterface*>(pInterface);
        MB_ResWindow* pResWindow = pInterfaceTemp->createFunctionDialog();
        if (pResWindow)
        {
            addChild(pResWindow);
        }
    }
}

void MB_LayerRoom::onBSXSClicked(CCObject* pSender)
{
    NSGameFunction::CCFunctionInterface *pInterface = NULL;
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionAchievement ,&pInterface))
    {
        MB_AchievementInterface* pInterfaceTemp = dynamic_cast<MB_AchievementInterface*>(pInterface);
        MB_ResWindow* pResWindow = pInterfaceTemp->createFunctionDialog();
        if (pResWindow)
        {
            addChild(pResWindow);
        }
    }
}

void MB_LayerRoom::onZXJLClicked(CCObject* pSender)
{
    NSGameFunction::CCFunctionInterface *pInterface = NULL;
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kActivatyGifts ,&pInterface))
    {
        MB_GiftsInterface* pInterfaceTemp = dynamic_cast<MB_GiftsInterface*>(pInterface);
        MB_ResWindow* pResWindow = pInterfaceTemp->createFunctionDialogSelf(eGiftTime);
        if (pResWindow)
        {
            addChild(pResWindow);
        }
    }
}
void MB_LayerRoom::onDJLBClicked(CCObject* pSender)
{
    NSGameFunction::CCFunctionInterface *pInterface = NULL;
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kActivatyGifts ,&pInterface))
    {
        MB_GiftsInterface* pInterfaceTemp = dynamic_cast<MB_GiftsInterface*>(pInterface);
        MB_ResWindow* pResWindow = pInterfaceTemp->createFunctionDialogSelf(eGiftLevel);
        if (pResWindow)
        {
            addChild(pResWindow);
        }
    }
}
void MB_LayerRoom::onLXDLLBClicked(CCObject* pSender)
{
    NSGameFunction::CCFunctionInterface *pInterface = NULL;
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kActivatyGifts ,&pInterface))
    {
        MB_GiftsInterface* pInterfaceTemp = dynamic_cast<MB_GiftsInterface*>(pInterface);
        MB_ResWindow* pResWindow = pInterfaceTemp->createFunctionDialogSelf(eGiftMLogin);
        if (pResWindow)
        {
            addChild(pResWindow);
        }
    }
}
