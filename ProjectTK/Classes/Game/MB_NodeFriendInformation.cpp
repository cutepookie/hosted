//
//  MB_NodeFriendInformation.cpp
//  ProjectPM
//
//  Create by WenYong on 11/5/2014.
//
//
#include "MB_NodeFriendInformation.h"
#include "MB_DataFriend.h"
#include "MB_FunctionModule.h"
//#include "MB_HomeLandInterface.h"
//#include "MB_HomeLandConfigure.h"
#include "MB_LayerChatList.h"

MB_NodeFriendInformation::MB_NodeFriendInformation()
{
    status = NULL;
    size	 = NULL;
    roleIcon	 = NULL;
    m_pNodeLevel	 = NULL;
    m_pBtHeadInfo	 = NULL;
    roleName	 = NULL;
    fightPower	 = NULL;
    m_pData = NULL;
    
    m_nSelectRoleID = 0;
}
MB_NodeFriendInformation::~MB_NodeFriendInformation()
{
    CC_SAFE_RELEASE_NULL(status);
    CC_SAFE_RELEASE_NULL(size);
    CC_SAFE_RELEASE_NULL(roleIcon);
    CC_SAFE_RELEASE_NULL(m_pNodeLevel);
    CC_SAFE_RELEASE_NULL(m_pBtHeadInfo);
    CC_SAFE_RELEASE_NULL(roleName);
    CC_SAFE_RELEASE_NULL(fightPower);

    CC_SAFE_RELEASE_NULL(m_pData);
}

CCSize MB_NodeFriendInformation::getNodeSize()
{
    return size->getContentSize();
}
void MB_NodeFriendInformation::setIsMail(bool bMail)
{
    
}
bool MB_NodeFriendInformation::init()
{
    CCNode* pNode = loadResource("res/friend_node_list.ccbi");
    if(pNode)
	{
		addChild(pNode);
        
		return true;
	}
	return false;
}



void MB_NodeFriendInformation::onResetWnd()
{
    if (m_pData)
    {
        NSGameHelper::setRoleIcon(roleIcon, m_pData->getIsMale(), m_pData->getHead(), m_pData->getTitle());
        
        
        char buff[128] = {};
        std::string strRoleName =m_pData->getRoleName();
        sprintf(buff, "%llu",m_pData->getFightPower());
        fightPower->setString(buff);
        sprintf(buff, "Lv.%d",m_pData->getLevel());
        m_pNodeLevel->setString(buff);
        strRoleName = m_pData->getRoleName();
        roleName->setString(strRoleName.c_str());
        //在线情况  不在线玩家置灰色
        if (m_pData->getLogoutTime() != 0)
        {
            roleIcon->setColor(ccc3(68,68,68));
        }
        
        if (m_pData->getLogoutTime() == 0)
        {
            status->setString("当前在线");
        }
        else
        {
            int timeFromNow = MB_ClientSocket::getInstance()->getServerTime() - m_pData->getLogoutTime();
            std::string ret = NSGameHelper::convertDeltaTime2Data(timeFromNow);
            status->setString(ret.c_str());
        }
    }
    
}
bool MB_NodeFriendInformation::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"size",CCNode*,size);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"roleIcon",CCSprite*,roleIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeLevel",CCLabelBMFont*,m_pNodeLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtHeadInfo",CCMenuItemImage*,m_pBtHeadInfo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"roleName",CCLabelTTF*,roleName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"fightPower",CCLabelBMFont*,fightPower);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"status",CCLabelTTF*,status);
	return false;
}
SEL_MenuHandler MB_NodeFriendInformation::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onRoleInfoClicked",MB_NodeFriendInformation::onRoleInfoClicked);
	return NULL;
}
SEL_CCControlHandler MB_NodeFriendInformation::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onDelClicked",MB_NodeFriendInformation::onDelClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onChatClicked",MB_NodeFriendInformation::onChatClicked);
	return NULL;
}
void MB_NodeFriendInformation::onRoleInfoClicked(CCObject* pSender)
{
    if (m_pData)
    {
        if(m_pData->getRoleID() == MB_RoleData::getInstance()->getUID()){
            
            MB_Message::sharedMB_Message()->showMessage("不能对比自己");
            return ;
        }
        MB_TeamData::getInstance()->sendpet_view_other(m_pData->getRoleID(),0);
    }
}
void MB_NodeFriendInformation::onDelClicked(CCObject* pSender)
{
    if (m_pData)
    {
        char temp[128] = {};
        sprintf(temp, "请确认是否删除好友%s？",m_pData->getRoleName());
        m_nSelectRoleID = m_pData->getRoleID();
        MB_Message::sharedMB_Message()->showMessage("删除好友", temp, "确定", "取消", this, menu_selector(MB_NodeFriendInformation::tryDeleteFriend), NULL);
    }
}

void MB_NodeFriendInformation::tryDeleteFriend()
{
    if (m_nSelectRoleID!=0)
    {
        MB_Message::sharedMB_Message()->showMessage("",15);
        MB_FriendMgr::getInstance()->sendfriend_delete(1, m_nSelectRoleID);
        m_nSelectRoleID = 0;
    }
}

void MB_NodeFriendInformation::onChatClicked(CCObject* pSender)
{
    if (m_pData)
    {
        MB_LayerChatList::PersonChatSence(m_pData->getRoleID(), m_pData->getRoleName());
    }
}

void MB_NodeFriendInformation::setData(MB_DataFriend* pData)
{
    if (pData == NULL)
    {
        return;
    }
    
    CC_SAFE_RELEASE_NULL(m_pData);
    m_pData = pData;
    m_pData->retain();
    
    onResetWnd();
}

MB_NodeFriendInformation* MB_NodeFriendInformation::create(MB_DataFriend* pData)
{
    if (pData == NULL)
    {
        return NULL;
    }
    
    MB_NodeFriendInformation* pInstance = new MB_NodeFriendInformation;
    if (pInstance && pInstance->init())
    {
        pInstance->setData(pData);
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

const CCSize& MB_NodeFriendInformation::getUISize()
{
    static CCSize  sz = CCSize(-1,-1);
    
    if (sz.width < 0)
    {
        MB_NodeFriendInformation* pNode = new MB_NodeFriendInformation;
        if (pNode->init())
        {
            sz = pNode->getNodeSize();
        }
        pNode->release();
    }
    return sz;
}
