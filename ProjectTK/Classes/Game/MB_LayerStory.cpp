//
//  MB_LayerStory.cpp
//  ProjectPM
//
//  Created by crimoon on 14-5-14.
//
//

#include "MB_LayerStory.h"
#include "MB_SynopsisConfig.h"
#include "MB_Audio.h"
#include "MB_FunctionModule.h"
#include "MB_LayerChatMain.h"
MB_LayerStoryPlayer::MB_LayerStoryPlayer()
{
    m_pNodeLeftRole = NULL;
    m_pNodeRightRole = NULL;
    m_pTTFShow = NULL;
    m_pDialogUnicode = NULL;
    m_pText = new char[1024];
    m_nMaxLength = 0;
    m_nNowLength = 0;
    m_nNowIndx = 0;
    m_nDialogUnicodePos = 0;
    m_nDialogUnicodeLength = 0;
    effectId = -1;
    m_pTarget = NULL;
    m_pMenuCall = NULL;
    m_pArrayStory = NULL;
    m_IsCanRetryGame = false;
}
MB_LayerStoryPlayer::~MB_LayerStoryPlayer()
{
    CC_SAFE_RELEASE_NULL(m_pNodeLeftRole);
    CC_SAFE_RELEASE_NULL(m_pNodeRightRole);
    CC_SAFE_RELEASE_NULL(m_pTTFShow);
    CC_SAFE_DELETE_ARRAY(m_pText);
    CC_SAFE_DELETE_ARRAY(m_pDialogUnicode);
    CC_SAFE_RELEASE_NULL(m_pArrayStory);
    CC_SAFE_RELEASE_NULL(m_pTarget);
    m_IsCanRetryGame = true;
}
void MB_LayerStoryPlayer::onEnter()
{
    MB_ResWindow::onEnter();
    MB_LayerChatMain::SetChatMainVisible(false,"MB_LayerStoryPlayer");
}

bool MB_LayerStoryPlayer::init(CCArray* array)
{
    if ( !CCLayer::init() || array == NULL)
	{
		return false;
	}
    CC_SAFE_RELEASE_NULL(m_pArrayStory);
    m_pArrayStory = array;
    m_pArrayStory->retain();
    
    this->addChild(NSGameHelper::createDisableTouchLayer());
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode *pScene = pCCBReader->readNodeGraphFromFile("res/story_layer_textpopup.ccbi", this);
    this->addChild(pScene);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    setNextDialogue();
    return true;
}
MB_LayerStoryPlayer* MB_LayerStoryPlayer::create(CCArray* array)
{
    MB_LayerStoryPlayer* ptr = new MB_LayerStoryPlayer;
    if (ptr && ptr->init(array))
    {
        ptr->autorelease();
        return ptr;
    }
    delete ptr;
    return NULL;
}

bool MB_LayerStoryPlayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "left", CCNode*, m_pNodeLeftRole);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "right", CCNode*, m_pNodeRightRole);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "text", CCLabelTTF*, m_pTTFShow);
    return true;
}
SEL_MenuHandler MB_LayerStoryPlayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onNextStepClicked", MB_LayerStoryPlayer::onNextStepClicked);
    return NULL;
}
SEL_CCControlHandler MB_LayerStoryPlayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

void MB_LayerStoryPlayer::onNextStepClicked(CCObject *)
{
    if(m_pText[m_nNowLength] != '\0' && m_nNowLength < m_nMaxLength
       && m_nDialogUnicodePos < m_nDialogUnicodeLength)
    {
        m_nNowLength =  m_nMaxLength;
        m_nDialogUnicodePos = m_nDialogUnicodeLength;
        m_pTTFShow->setString(m_pText);
        unschedule(schedule_selector(MB_LayerStoryPlayer::tickShowText));
    }
    else
    {
        setNextDialogue();
    }
}

void MB_LayerStoryPlayer::tickShowText(float dt)
{
    if(m_pText[m_nNowLength] != '\0' && m_nNowLength < m_nMaxLength
       && m_nDialogUnicodePos < m_nDialogUnicodeLength)
    {
        char* str = new char[1024];
        memset(str, 0, sizeof(char) * 1024);
        
        int charLen = UTF8_LENGTH(m_pDialogUnicode[m_nDialogUnicodePos]);
        strncpy(str, m_pText, m_nNowLength+charLen);
        m_pTTFShow->setString(str);
        CC_SAFE_DELETE_ARRAY(str);
        m_nNowLength += charLen;
        m_nDialogUnicodePos++;
    }
    else
    {
        unschedule(schedule_selector(MB_LayerStoryPlayer::tickShowText));
    }
}

void MB_LayerStoryPlayer::setNextDialogue()
{
    if (m_pArrayStory != NULL && m_nNowIndx < m_pArrayStory->count())
    {
    }
    else
    {
        //关闭
        over();
        return;
    }
    
    MB_Plot* data = (MB_Plot*)(m_pArrayStory->objectAtIndex(m_nNowIndx));
    m_nNowIndx++;
    memset(m_pText,0,1024);
    strcpy(m_pText,data->getText().c_str());
    m_nNowLength = 0;
    m_nMaxLength = data->getText().length();
    
    CC_SAFE_DELETE_ARRAY(m_pDialogUnicode);
    m_pDialogUnicode = cc_utf8_to_utf16(m_pText);
    m_nDialogUnicodePos = 0;
    m_nDialogUnicodeLength = cc_wcslen(m_pDialogUnicode);
    
    CCSprite* spriteIcon = CCSprite::create();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("story.plist");
    
    bool bIsPNG = false;
    char str[50];
    strcpy(str,data->getHeadIcon().c_str());
    sprintf(str,"full_card/%s.png",data->getHeadIcon().c_str());
    NSGameHelper::setSpriteFrame(spriteIcon,str);
    
    m_pNodeLeftRole->removeAllChildren();
    m_pNodeRightRole->removeAllChildren();
    if(data->getHeadPos() == 1)
    {
        m_pNodeLeftRole->addChild(spriteIcon);
    }
    else if(data->getHeadPos() == 2)
    {
        m_pNodeRightRole->addChild(spriteIcon);
    }
    
    if (effectId!=-1)
    {
        MB_Audio::getInstance()->stopEffect(effectId);
    }
    //音效
    effectId = MB_Audio::getInstance()->playEffect(data->getSound().c_str());
    
    if (m_nNowLength < m_nMaxLength)
    {
        schedule(schedule_selector(MB_LayerStoryPlayer::tickShowText));
    }
    
}


void MB_LayerStoryPlayer::setTarget(CCObject* target,SEL_MenuHandler callback)
{
    CC_SAFE_RELEASE_NULL(m_pTarget);
    m_pTarget = target;
    m_pMenuCall = callback;
    CC_SAFE_RETAIN(m_pTarget);
}

void MB_LayerStoryPlayer::over()
{
    if (m_pTarget)
    {
        (m_pTarget->*m_pMenuCall)(this);
    }
    removeFromParent();
}
