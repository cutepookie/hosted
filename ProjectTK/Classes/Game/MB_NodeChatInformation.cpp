
#include "MB_NodeChatInformation.h"
#include "MB_LayerChatList.h"
#include "MB_LayerChatBoard.h"


#include "MB_ChatData.h"
MB_NodeChatInformation::MB_NodeChatInformation(){
    
    m_pNodeSize = NULL;
    m_nChatData = NULL;
    m_pRoleName = NULL;
    m_pContent = NULL;
    m_pContentSprite = NULL;
    m_pRoleIcon = NULL;
    m_pRoleNameRichText = NULL;
    m_pContentRichText = NULL;
}
MB_NodeChatInformation::~MB_NodeChatInformation()
{
    CC_SAFE_RELEASE(m_nChatData);
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(m_pRoleName);
    CC_SAFE_RELEASE_NULL(m_pContent);
    CC_SAFE_RELEASE_NULL(m_pContentSprite);
    CC_SAFE_RELEASE_NULL(m_pRoleIcon);
}
bool MB_NodeChatInformation::init(MB_ChatData *chatData){

    MB_ResWindow::init();
    
    bool bLeft = false;
    CCNode* pNode = NULL;
    std::string filename = "";
    if(chatData->getChannelType() == kChannelWorld)
    {
        if(chatData->getRoleID() == MB_RoleData::getInstance()->getUID())
        {
            filename = "res/chat_node_unit2.ccbi";
            bLeft = false;
        }
        else
        {
            filename = "res/chat_node_unit1.ccbi";
            bLeft = true;
        }
    }
    else if(chatData->getChannelType() == kChannelPrivate)
    {
        if(chatData->getRoleID() == MB_RoleData::getInstance()->getUID())
        {
            filename = "res/chat_node_unit2.ccbi";
            bLeft = false;
        }
        else
        {
            filename = "res/chat_node_unit1.ccbi";
            bLeft = true;
        }
    }
    pNode = loadResource(filename.c_str());
    this->addChild(pNode);
    
    if(chatData == NULL)
    {
        return true;
    }
    m_nChatData = chatData;
    CC_SAFE_RETAIN(m_nChatData);
    
    
    char namebuff[1024] = {0};
    
    if(m_pRoleName)
    {
        if(chatData->getChannelType() == kChannelPrivate)
        {
            if(chatData->getRoleID() == MB_RoleData::getInstance()->getUID())
                sprintf(namebuff, "[color=debea9]您悄悄的对[/color] [link=90ff80=01][color=90ff80]%s[/color][/link] [color=debea9]说[/color]",chatData->getRoleTarget().c_str());
            else
                sprintf(namebuff, "[link=90ff80=00][color=90ff80]%s[/color][/link] [color=debea9]悄悄的对您说[/color]",chatData->getRoleName());
        }
        else
        {
            sprintf(namebuff, "[color=ffffff]%s[/color]",chatData->getRoleName());//"[link=ffff00=02][color=65ff00]%s[/color][/link]"
        }
        
        m_pRoleNameRichText = new RichText();
        m_pRoleNameRichText->autorelease();
        m_pRoleName->getParent()->addChild(m_pRoleNameRichText);
        m_pRoleNameRichText->initWithString(namebuff, "", 24, CCSizeMake(0, 0), bLeft?kCCTextAlignmentLeft:kCCTextAlignmentRight, kCCVerticalTextAlignmentTop);
        m_pRoleNameRichText->setPosition(m_pRoleName->getPosition());
        m_pRoleNameRichText->setAnchorPoint(m_pRoleName->getAnchorPoint());
        m_pRoleName->removeFromParentAndCleanup(true);
        m_pRoleNameRichText->setDelegate(this);
    }
    
    if(m_pContent)
    {
        std::string strContent = "[color=000000]";
        strContent += chatData->getMessage();
        strContent += "[/color]";
        m_pContentRichText = new RichText();
        m_pContentRichText->autorelease();
        m_pContent->getParent()->addChild(m_pContentRichText);
        m_pContentRichText->initWithString(strContent.c_str(), m_pContent->getFontName(), m_pContent->getFontSize(), CCSizeMake(340, 0), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
        m_pContentRichText->setPosition(m_pContent->getPosition());
        m_pContentRichText->setAnchorPoint(m_pContent->getAnchorPoint());
        m_pContent->removeFromParentAndCleanup(true);
    }
    
    if(m_pContentSprite)
    {
        CCSize size = CCSizeMake(m_pContentRichText->getContentSize().width + 51, m_pContentRichText->getContentSize().height + 45);
        if(size.width < 61)size.width = 61;
        m_pContentSprite->setContentSize(size);
    }
    
    NSGameHelper::setRoleIcon(m_pRoleIcon,chatData->getIsMale(),chatData->getHead(),chatData->getTitle());
    return true;
}
MB_NodeChatInformation * MB_NodeChatInformation::create(MB_ChatData *chatData){
    
    MB_NodeChatInformation * ptr = new MB_NodeChatInformation();
    if(ptr && ptr->init(chatData)){
    
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;

}
void MB_NodeChatInformation::onClickedTextTTF(RichText * obj,int id,CCTouch *pTouch)
{
    MB_TARGET_PARENT(MB_LayerChatList,ptr)
    if(ptr)
    {
        if(id == 0)
        {
            ptr->personChat(m_nChatData->getRoleID(), m_nChatData->getRoleName(),false);
        }
        else if(id == 1)
        {
            ptr->personChat(m_nChatData->getTargetUID(), m_nChatData->getRoleTarget().c_str(),false);
        }
        else if(id == 2)
        {
            ptr->personChat(m_nChatData->getRoleID(), m_nChatData->getRoleName());
        }
    }
}

cocos2d::SEL_MenuHandler MB_NodeChatInformation::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClickRole", MB_NodeChatInformation::onClickRole);
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_NodeChatInformation::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

        return NULL;
}
bool MB_NodeChatInformation::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"size",CCNode*,m_pNodeSize);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pRoleName",CCLabelTTF*,m_pRoleName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pContent",CCLabelTTF*,m_pContent);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pContentSprite",CCScale9Sprite*,m_pContentSprite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "roleIcon", CCSprite*, m_pRoleIcon);
    
    if (strcmp("menu", pMemberVariableName)==0)
    {
        CCMenu* pMenu = dynamic_cast<CCMenu*>(pNode);
        if (pMenu)
        {
            pMenu->setSwallowsTouches(false);
        }
    }
    return false;
}
CCSize MB_NodeChatInformation::getNodeSize()
{
    if(m_pContentRichText)
    {
        float fh = m_pNodeSize->getContentSize().height;
        if(fh <= m_pContentRichText->getContentSize().height + 80)
        {
            fh = m_pContentRichText->getContentSize().height + 80;
        }
        return CCSizeMake(m_pNodeSize->getContentSize().width, fh);
    }
    return m_pNodeSize->getContentSize();
}

void MB_NodeChatInformation::onClickRole(CCObject *){

    if(strcmp(MB_RoleData::getInstance()->getName(), m_nChatData->getRoleName() ) == 0)
    {
        return ;
    }
    MB_TARGET_PARENT(MB_LayerChatList, ptr)
    if(ptr)
    {
        if(m_nChatData->getChannelType() == kChannelPrivate)
        {
            ptr->sendpet_view_other_dtl(m_nChatData->getRoleID(), 0);
        }
        else
        {
            ptr->addChild(MB_LayerChatBoard::create(m_nChatData->getRoleName(),m_nChatData->getRoleID()));
        }
    }

}





MB_NodeChatTime::MB_NodeChatTime()
{
    m_pTime = NULL;
    m_pNodeSize = NULL;
}
MB_NodeChatTime::~MB_NodeChatTime()
{
    CC_SAFE_RELEASE_NULL(m_pTime);
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
}

const char* wdays[] = {"日","一","二","三","四","五","六"};

bool MB_NodeChatTime::init(time_t t)
{
    MB_ResWindow::init();
    
    CCNode* pNode = loadResource("res/chat_node_time.ccbi");
    this->addChild(pNode);
    
    struct tm *pTemp = localtime(&t);
    
    char szbuff[100] = {0};
    
    time_t tdis = MB_ClientSocket::getInstance()->getServerTime() - t;
    float fDay = tdis / (3600.0 * 24);
    if(fDay > 14.0f)
    {
        m_pTime->setString("2周前");
    }
    else if(fDay > 7.0f)
    {
        m_pTime->setString("1周前");
    }
    else if(fDay > 1.0f)
    {
        sprintf(szbuff,"星期%s %02d:%02d",wdays[pTemp->tm_wday],pTemp->tm_hour,pTemp->tm_min);
        m_pTime->setString(szbuff);
    }
    else
    {
        sprintf(szbuff, "%02d:%02d",pTemp->tm_hour,pTemp->tm_min);
        m_pTime->setString(szbuff);
    }
    m_pTime->setColor(ccc3(202, 170, 149));
    return true;
}
MB_NodeChatTime * MB_NodeChatTime::create(time_t t)
{
    MB_NodeChatTime * ptr = new MB_NodeChatTime();
    if(ptr && ptr->init(t)){
        
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
CCSize MB_NodeChatTime::getNodeSize()
{
    return m_pNodeSize->getContentSize();
}
bool MB_NodeChatTime::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTime",CCLabelTTF*,m_pTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"size",CCNode*,m_pNodeSize);
    return false;
}
