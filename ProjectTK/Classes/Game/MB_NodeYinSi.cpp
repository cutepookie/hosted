

#include "MB_NodeYinSi.h"
#include "MB_PublicNoticeData.h"

#include "MB_NodeNoticeActive.h"
#include "MB_NodeNoticePic.h"
#include "MB_NodeNoticeYinSi.h"
//---------------------------------------------//
//======    构造|析构
//---------------------------------------------//
MB_NodeYinSi::MB_NodeYinSi()
{
    tanchuTimes = 1;
    m_pContent          = NULL;
    MB_TutorialMgr::getInstance()->SetModelDilogState("MB_NodeYinSi", true);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(MB_NodeYinSi::refresh), "notice_received", this);
}

MB_NodeYinSi::~MB_NodeYinSi()
{
    CC_SAFE_RELEASE(m_pContent);
    MB_TutorialMgr::getInstance()->SetModelDilogState("MB_NodeYinSi", false);
    MB_LayerRoleInfoHeader::setMenuEnable(true,"MB_NodeYinSi");
    
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,"notice_received");
}
bool MB_NodeYinSi::init()
{
    MB_ResWindow::init();
    this->addChild(NSGameHelper::createDisableTouchLayer());
    pRootNode = loadResource("res/message_layer_yinsi.ccbi");
    this->addChild(pRootNode);
    
    onInitDidFinish();
    
    lc = CCLayerColor::create(ccc4(0,0,0,150), 640, 1136);
    addChild(lc,-1);
    
    runEnterAction();
    return true;
}
void MB_NodeYinSi::onInitDidFinish()
{
    onResetWnd();
}

//---------------------------------------------//
//======    事件|成员 指派
//---------------------------------------------//
bool MB_NodeYinSi::onAssignCCBMemberVariable(CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Content", CCNode*, m_pContent);
    return false;
}

SEL_CCControlHandler MB_NodeYinSi::onResolveCCBCCControlSelector(CCObject * pTarget,const char* pSelectorName)
{
    return NULL;
}
cocos2d::SEL_MenuHandler MB_NodeYinSi::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_NodeYinSi::onCloseClick)
    return NULL;
}

void MB_NodeYinSi::onCloseClick(CCObject* pSender)
{
    CCUserDefault::sharedUserDefault()->setBoolForKey("querenyinsi", true);
    removeFromParent();
}
void MB_NodeYinSi::setClose()
{
    onCloseClick(NULL);
}
void MB_NodeYinSi::runEnterAction()
{
    lc->setOpacity(0);
    lc->runAction(CCFadeTo::create(.15f,150));
    NSGameHelper::setAllOpacity(pRootNode, 0);
    NSGameHelper::runOptActionIn(pRootNode, .15f, true);
    pRootNode->setPositionY(pRootNode->getPositionY()+50);
    pRootNode->runAction(CCMoveBy::create(.15f, ccp(0,-50)));
}
//---------------------------------------------//
//======    界面刷新
//---------------------------------------------//
void MB_NodeYinSi::onResetWnd(void)
{
    m_pContent->removeAllChildren();
    pScrollview = CCScrollView::create(m_pContent->getContentSize());
    pScrollview->setDirection(kCCScrollViewDirectionVertical);
    m_pContent->addChild(pScrollview);
    CCLayer* layer = CCLayer::create();
    //公告图片
    
    //公告内容
    int height = 0;
    for(int i = 16;i>0;i--){
        char str[32] = "";
        sprintf(str,"yinsi%d.txt" ,i);
        string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(str);
        unsigned char* pBuffer = NULL;
        unsigned long bufferSize = 0;
        pBuffer = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(),"r",&bufferSize);
        CCLabelTTF* m_label = CCLabelTTF::create((const char*)pBuffer, "", 16);
        m_label->setDimensions(CCSize(540,0));//设置label的尺寸
        m_label->setHorizontalAlignment(kCCTextAlignmentLeft);
        m_label->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
        layer->addChild(m_label);
        if (i==1) {
            height += m_label->getContentSize().height+270;
        }else
        {
            height += m_label->getContentSize().height+60;
        }
        
        m_label->setPosition(ccp(m_pContent->getContentSize().width/2,height-185) );
        if (pBuffer) {
            delete [] pBuffer;
            pBuffer = NULL;
        }
    }
    //位置调整
    CCArray* childers = layer->getChildren();
    CCNode* node = NULL;
    pScrollview->setContainer(layer);
    pScrollview->setContentSize(CCSize(m_pContent->getContentSize().width,height+15));
    pScrollview->setContentOffset(CCPoint(0,m_pContent->getContentSize().height - height-15));
    
}

void MB_NodeYinSi::refresh(CCObject*)
{
    dirty();
}
