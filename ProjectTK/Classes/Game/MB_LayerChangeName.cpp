//
//  MB_LayerChangeName.cpp
//  ProjectMB
//
//  Created by yuanwugang on 15-1-14.
//
//

#include "MB_LayerChangeName.h"
#include "MB_FunctionModule.h"
#include "MB_RoleData.h"
#include "MB_ItemData.h"

MB_LayerChangeName::MB_LayerChangeName()
{
    m_pTTFItemNum = NULL;
    m_pEditBox = NULL;
    SOCKET_MSG_REGIST(RECV_ROLE_CHANGE_NAME, MB_LayerChangeName);
}
MB_LayerChangeName::~MB_LayerChangeName()
{
    SOCKET_MSG_UNREGIST(RECV_ROLE_CHANGE_NAME);
    CC_SAFE_RELEASE_NULL(m_pTTFItemNum);
    CC_SAFE_RELEASE_NULL(m_pEditBox);
}
bool MB_LayerChangeName::init()
{
    CCNode* node = loadResource("res/changename_layer");
    if (node) {
        this->addChild(NSGameHelper::createDisableTouchLayer());
        this->addChild(node);
        
        m_pEditBox->setDelegate(this);
//        m_pEditBox->setFontColor(ccBLACK);
        onResetWnd();
        return true;
    }
    return false;
}
void MB_LayerChangeName::onResetWnd()
{
    char buf[128] = {};
    sprintf(buf,"%d",MB_ItemMgr::getInstance()->getRenameCardCount());
    m_pTTFItemNum->setString(buf);
}
MB_LayerChangeName* MB_LayerChangeName::create()
{
    MB_LayerChangeName* ptr = new MB_LayerChangeName;
    if (ptr && ptr->init())
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}
bool MB_LayerChangeName::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFItemNum",CCLabelBMFont*,m_pTTFItemNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pEditBox",CCEditBox*,m_pEditBox);
    
    return false;
}
SEL_MenuHandler MB_LayerChangeName::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onConfirmClicked",MB_LayerChangeName::onConfirmClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onBreakClicked",MB_LayerChangeName::onBreakClicked);
    return NULL;
}
SEL_CCControlHandler MB_LayerChangeName::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{

    return NULL;
}

void MB_LayerChangeName::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox)
{
    editBox->setPosition(editBox->getPosition());
}
void MB_LayerChangeName::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox)
{
    std::string str = editBox->getText();
    int pos;
    do {
        pos = str.find("\xe2\x80\x86");
        if (pos != std::string::npos) {
            str.replace(pos, 3, "");
        }
        else
        {
            break;
        }
    } while (1);
    editBox->setText(str.c_str());

}
void MB_LayerChangeName::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{
    
}
void MB_LayerChangeName::editBoxReturn(cocos2d::extension::CCEditBox* editBox)
{
    
}
static bool checkName(const unsigned short* pName)
{
    size_t nUnicodeLength = cc_wcslen(pName);
    
    for (int i =0; i<nUnicodeLength; ++i)
    {
        if (pName[i]>= 0x4e00 && pName[i] <= 0x9fff)
        {
            continue;
        }
        else
        {
            if( (pName[i] >='A' && pName[i] <='Z') || (pName[i]>='a' && pName[i]<='z') || (pName[i]>='0' && pName[i]<='9') )
            {
                continue;
			}
            else
            {
                return false;
            }
        }
    }
    return true;
}
void MB_LayerChangeName::onConfirmClicked(CCObject *)
{
    const char * pName = m_pEditBox->getText();
    if (pName==NULL)
    {
        MB_Message::sharedMB_Message()->showMessage("错误","名字不能为空","确定");
        return;
    }
    
    unsigned short* pUnicode16 = cc_utf8_to_utf16(pName);
    
    if (MB_DirtyWordsCheck::getInstance()->checkDatabuf(pName))
    {
        MB_Message::sharedMB_Message()->showMessage("错误","含有非法字符, 请修改您的名字","确定");
        return ;
    }
    
    if(!checkName(pUnicode16))
    {
        MB_Message::sharedMB_Message()->showMessage("错误","含有非法字符, 请修改您的名字","确定");
        return ;
    }
    CC_SAFE_DELETE_ARRAY(pUnicode16);
    if(strcmp(pName, "") == 0)
    {
        MB_Message::sharedMB_Message()->showMessage("昵称不能为空");
        return;
    }
    MB_Message::sharedMB_Message()->showMessage("",15);
    MB_RoleData::getInstance()->send_role_change_name(pName);
}
void MB_LayerChangeName::onBreakClicked(CCObject *)
{
    this->removeFromParent();
}

/*required    int8                result          =1;//0成功,1宝石不足,3名字已被使用,4非法字符,5名字超长
 */
void MB_LayerChangeName::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    MB_MsgBuffer* pRecv = response->getResponseData();
    uint16_t Msg = 0;
    pRecv->Reset();
    pRecv->skipU16();
    pRecv->skipU8();
    pRecv->readU16(&Msg);
    MB_Message::sharedMB_Message()->removeALLMessage();
    switch (Msg)
    {
        case RECV_ROLE_CHANGE_NAME:
        {
            uint8_t u8;
            pRecv->readU8(&u8);
            if (u8 == 0)
            {
                MB_Message::sharedMB_Message()->showMessage("改名成功");
                removeFromParent();
            }
            else if(u8 == 1)
            {
                MB_Message::sharedMB_Message()->showMessage("宝石不足");
            }
            else if(u8 == 3)
            {
                MB_Message::sharedMB_Message()->showMessage("名字已被使用");
            }
            else if(u8 == 5)
            {
                MB_Message::sharedMB_Message()->showMessage("名字超长");
            }
            else if(u8 == 4)
            {
                MB_Message::sharedMB_Message()->showMessage("名字超长");
            }
        }
            
            break;

        default:
            break;
    }
}
