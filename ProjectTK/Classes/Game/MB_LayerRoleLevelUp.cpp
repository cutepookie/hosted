
#include "MB_LayerRoleLevelUp.h"

#include "MB_FishingRewardData.h"
#include "MB_FunctionMgr.h"

MB_LayerRoleLevelUp::MB_LayerRoleLevelUp(){
    m_pConfirmBtn = NULL;
    m_pPreLevel  = NULL;
    m_pNowLevel  = NULL;
    m_pPreEnpety = NULL;
    m_pNextEnpety = NULL;
    m_pPreDistime = NULL;
    m_pNowDistime = NULL;
    m_pRegest = NULL;
    m_pNode = NULL;
    m_pHasCheckLevel = false;
    MB_LayerRoleInfoHeader::setMenuEnable(false,"MB_LayerRoleLevelUp");
    MB_TutorialMgr::getInstance()->SetModelDilogState("MB_LayerRoleLevelUp", true);
}
MB_LayerRoleLevelUp::~MB_LayerRoleLevelUp(){
    CC_SAFE_RELEASE(m_pConfirmBtn);
    CC_SAFE_RELEASE(m_pPreLevel);
    CC_SAFE_RELEASE(m_pNowLevel);
    CC_SAFE_RELEASE(m_pPreEnpety);
    CC_SAFE_RELEASE(m_pNextEnpety);
    CC_SAFE_RELEASE(m_pPreDistime);
    CC_SAFE_RELEASE(m_pNowDistime);
    MB_LayerRoleInfoHeader::setMenuEnable(true,"MB_LayerRoleLevelUp");
    MB_TutorialMgr::getInstance()->SetModelDilogState("MB_LayerRoleLevelUp", false);
}


MB_LayerRoleLevelUp * MB_LayerRoleLevelUp::create(int preLevel,int predis,int preenergy){

    MB_LayerRoleLevelUp * ptr = new MB_LayerRoleLevelUp();
    if(ptr && ptr->init(preLevel ,predis,preenergy)){
    
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return ptr;
}
bool MB_LayerRoleLevelUp::init(int preLevel,int predis,int preenergy){

    if (MB_ResWindow::init() == false) {
        
        return false;
    }
    this->addChild(NSGameHelper::createDisableTouchLayer());
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    
    m_pNode = pCCBReader->readNodeGraphFromFile("res/gui_result_rolelvup.ccbi", this);
    pCCBReader->release();
    this->addChild(m_pNode);
    char databuf[50];
    
    sprintf(databuf, "%d",preLevel);
    m_pPreLevel->setString(databuf);
    sprintf(databuf, "%d",MB_RoleData::getInstance()->getLevel());
    m_pNowLevel->setString(databuf);
    sprintf(databuf, "%d",preenergy);
    m_pPreEnpety->setString(databuf);
    sprintf(databuf, "%d",predis);
    m_pPreDistime->setString(databuf);
    
    sprintf(databuf, "%d",MB_RoleData::getInstance()->getDiscoveryTimes());
    m_pNowDistime->setString(databuf);
    sprintf(databuf, "%d",MB_RoleData::getInstance()->getEnergy());
    m_pNextEnpety->setString(databuf);
    buttonIsGo[0] = false;
    buttonIsGo[1] = false;
    if (global_tutorialNode!=NULL) {
        m_pConfirmBtn->setTouchPriority(-128);
    }
    return true;
}

void MB_LayerRoleLevelUp::onEnter(){

    MB_ResWindow::onEnter();
    MB_TutorialMgr::getInstance()->SetModelDilogState("MB_LayerRoleLevelUp", true);
    onResetWnd();
}

void MB_LayerRoleLevelUp::onExit()
{
    MB_ResWindow::onExit();
    MB_TutorialMgr::getInstance()->SetModelDilogState("MB_LayerRoleLevelUp",false);
}
bool MB_LayerRoleLevelUp::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){

    

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pPreLevel",CCLabelBMFont *, m_pPreLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNowLevel",CCLabelBMFont *,m_pNowLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pPreEngery",CCLabelBMFont *,m_pPreEnpety);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNextEngery",CCLabelBMFont *,m_pNextEnpety);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pPreDistime",CCLabelBMFont *,m_pPreDistime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNowDistime",CCLabelBMFont *,m_pNowDistime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pConfirmBtn",CCControlButton *, m_pConfirmBtn);
    return false;
}
SEL_MenuHandler MB_LayerRoleLevelUp::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

    return NULL;
}
SEL_CCControlHandler MB_LayerRoleLevelUp::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){

    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onConfirmClicked", MB_LayerRoleLevelUp::onConfirmClicked);

      return NULL;
}
void MB_LayerRoleLevelUp::onConfirmClicked(CCObject *)
{
    this->goClose(this);
}
void MB_LayerRoleLevelUp::goClose(CCObject *){

    if(!m_pHasCheckLevel){
     
        this->goCheck();
        return;
    }
    removeFromParent();
}
void MB_LayerRoleLevelUp::goCheck()
{
    m_pHasCheckLevel = true;
    int nowLevel = MB_RoleData::getInstance()->getLevel();
    
    popWindow();
    
    CCNode * node = CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
    if(node)
    {
        MB_FunctionMgr::getInstance()->onRoleLevelUp(nowLevel);
    }
}

void MB_LayerRoleLevelUp::goReguest(CCObject *)
{
    MB_SceneRegist *layer = MB_SceneRegist::create(LAYER_TAG_BIND_GUEST);
    CCDirector::sharedDirector()->getRunningScene()->addChild(layer,Z_ORDER_OUTSHOW);
    goClose(NULL);
}

void MB_LayerRoleLevelUp::goCancel(CCObject *){
    
    this->goClose(this);

}
