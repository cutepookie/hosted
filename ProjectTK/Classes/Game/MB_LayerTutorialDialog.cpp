

#include "MB_LayerTutorialDialog.h"
#include "MB_RoleSoundSystem.h"
//static int g_nCount = 0;

MB_LayerTutorialDialog::MB_LayerTutorialDialog()
{
    m_bAnimationOver = false;
    m_nDialogPos = 0;
    m_nDialogUnicodePos = 0;
    m_nDialogLength = 0;
    m_pDialog = new char[1024];
    memset(m_pDialog, 0, sizeof(char)*1024);
    m_pDialogUnicode = NULL;
    m_pLeft = NULL;
    m_pRight = NULL;
    m_pLabelText = NULL;
    m_pTarget = NULL;
    m_pmenu = NULL;
}

MB_LayerTutorialDialog::~MB_LayerTutorialDialog()
{
    unscheduleAllSelectors();
    CC_SAFE_RELEASE_NULL(m_pLeft);
    CC_SAFE_RELEASE_NULL(m_pRight);
    CC_SAFE_RELEASE_NULL(m_pLabelText);
    CC_SAFE_DELETE_ARRAY(m_pDialog);
    CC_SAFE_DELETE_ARRAY(m_pDialogUnicode);
    CC_SAFE_RELEASE_NULL(m_pmenu);
}

MB_LayerTutorialDialog * MB_LayerTutorialDialog::create()
{
    
    MB_LayerTutorialDialog * ptr = new MB_LayerTutorialDialog();
    
    if( ptr != NULL && ptr->init())
    {
        ptr->autorelease();
        return  ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}


MB_LayerTutorialDialog * MB_LayerTutorialDialog::create(const char* dialog, bool isLeft)
{
    MB_LayerTutorialDialog * ptr = new MB_LayerTutorialDialog();
    
    if( ptr != NULL && ptr->init(dialog, isLeft))
    {
        ptr->autorelease();
        return  ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}

bool MB_LayerTutorialDialog::init()
{
    if( CCLayer::init() == false){
        
        return false;
    }
    
    m_pTutorialTemplete = MB_TutorialMgr::getInstance()->getCurTemplete();
    
    strcpy(m_pDialog, m_pTutorialTemplete->getText());
    m_pDialogUnicode = cc_utf8_to_utf16(m_pDialog);

    this->addChild(NSGameHelper::createDisableTouchLayer());
    m_nDialogUnicodeLength = cc_wcslen(m_pDialogUnicode);
    m_nDialogLength = strlen(m_pDialog);
    this->addChild(NSGameHelper::createDisableTouchLayer());
    CCNode *node = loadResource("res/story_layer_texture.ccbi");
    this->addChild(node);
    
    
    m_pLeft->setVisible(true);
    m_pRight->setVisible(false);
    
    m_pmenu->setTouchPriority(kCCMenuHandlerPriorityTutorial);
    schedule(schedule_selector(MB_LayerTutorialDialog::tickShowText));


    return  true;
}

void MB_LayerTutorialDialog::tick(float dt)
{
    MB_ResWindow::tick(dt);
    if(m_bAnimationOver)
    {
        static float time = 0.0f;
        time+=dt;
        
        if (time >= 5.0f)
        {
            m_bAnimationOver = false;
            onCloseClicked(NULL);
        }
    }
}

void MB_LayerTutorialDialog::OnAnimationOver()
{
    m_bAnimationOver = true;
}



bool MB_LayerTutorialDialog::init(const char* dialog, bool isLeft)
{
    if( CCLayer::init() == false){
        
        return false;
    }
    
    
    strcpy(m_pDialog, dialog);
    m_nDialogLength = strlen(dialog);
    m_pDialogUnicode = cc_utf8_to_utf16(m_pDialog);
    m_nDialogUnicodeLength = cc_wcslen(m_pDialogUnicode);
    m_nDialogLength = strlen(m_pDialog);
    this->addChild(NSGameHelper::createDisableTouchLayer());
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);

    CCNode *node = ccbReader->readNodeGraphFromFile("res/story_layer_texture.ccbi", this);
    this->addChild(NSGameHelper::createDisableTouchLayer());
    this->addChild(node);
    ccbReader->getAnimationManager()->setAnimationCompletedCallback(this, callfunc_selector(MB_LayerTutorialDialog::OnAnimationOver));
    
    CC_SAFE_RELEASE_NULL(ccbReader);
    m_pmenu->setTouchPriority(kCCMenuHandlerPriorityTutorial);
//    setTouchPriority(kCCMenuHandlerPriorityTutorial);
    
    if (isLeft)
    {
        m_pLeft->setVisible(true);
        m_pRight->setVisible(false);
    }
    else
    {
        m_pLeft->setVisible(false);
        m_pRight->setVisible(true);
    }
    
    schedule(schedule_selector(MB_LayerTutorialDialog::tickShowText));
    
    return  true;
}

SEL_MenuHandler MB_LayerTutorialDialog::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClicked", MB_LayerTutorialDialog::onCloseClicked);
    return NULL;
}

SEL_CCControlHandler MB_LayerTutorialDialog::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName) {
    
    return NULL;
    
}

bool MB_LayerTutorialDialog::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "left", CCNode*, m_pLeft);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "right", CCNode*, m_pRight);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "text", CCLabelTTF*, m_pLabelText);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "menu", CCMenu*, m_pmenu);
    
    return true;
}


void MB_LayerTutorialDialog::tickShowText(float dt)
{
    if (m_pDialog[m_nDialogPos] != '\0' && m_nDialogPos < m_nDialogLength && m_nDialogUnicodePos < m_nDialogUnicodeLength)
    {
        char* str = new char[1024];
        
        int charLen = UTF8_LENGTH(m_pDialogUnicode[m_nDialogUnicodePos]);
        memset(str, 0, sizeof(char) * 1024);
        strncpy(str, m_pDialog, m_nDialogPos + charLen);
        m_pLabelText->setString(str);
        CC_SAFE_DELETE_ARRAY(str);
        m_nDialogPos += charLen;
        m_nDialogUnicodePos++;
    }
    else
    {
//        unscheduleAllSelectors();
    }
}

void MB_LayerTutorialDialog::onCloseClicked(cocos2d::CCObject *pSender)
{
    
    if (m_nDialogPos < m_nDialogLength) {
        m_nDialogPos = m_nDialogLength;
        m_pLabelText->setString(m_pDialog);
        unscheduleAllSelectors();
        return;
    }
    if(m_pTarget){
    
        (m_pTarget->*m_pCallBack)();
        removeFromParent();
        return;
    }
    m_bClicked = true;
    TutorialTriggerComplete
}
void MB_LayerTutorialDialog::setCallBack(CCObject *target,SEL_CallFunc backFunc){

    m_pTarget = target;
    m_pCallBack = backFunc;
}
