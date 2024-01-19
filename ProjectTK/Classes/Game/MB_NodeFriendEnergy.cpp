//
//  MB_NodeFriendEnergy.cpp
//  ProjectPM
//
//  Create by WenYong on 11/5/2014.
//
//
#include "MB_NodeFriendEnergy.h"
#include "MB_DataFriend.h"

MB_NodeFriendEnergy::MB_NodeFriendEnergy()
{
    size	 = NULL;
    roleIcon	 = NULL;
    m_pNodeLevel	 = NULL;
    roleName	 = NULL;
    fightPower	 = NULL;
    status	 = NULL;
    m_pBtSendEnergy	 = NULL;
    m_pBtGiveEnergy	 = NULL;
    m_pData = NULL;
}
MB_NodeFriendEnergy::~MB_NodeFriendEnergy()
{
    CC_SAFE_RELEASE_NULL(size);
    CC_SAFE_RELEASE_NULL(roleIcon);
    CC_SAFE_RELEASE_NULL(roleName);
    CC_SAFE_RELEASE_NULL(fightPower);
    CC_SAFE_RELEASE_NULL(status);
    CC_SAFE_RELEASE_NULL(m_pBtSendEnergy);
    CC_SAFE_RELEASE_NULL(m_pBtGiveEnergy);
    CC_SAFE_RELEASE_NULL(m_pData);
    CC_SAFE_RELEASE_NULL(m_pNodeLevel);
}
bool MB_NodeFriendEnergy::init()
{
    CCNode* pNode = loadResource("res/friend_node_energy.ccbi");
    if(pNode)
	{
		addChild(pNode);        
		return true;
	}
	return false;
}

void MB_NodeFriendEnergy::setData(MB_DataFriend* pData)
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

MB_NodeFriendEnergy* MB_NodeFriendEnergy::create(MB_DataFriend* pData)
{
    if (pData == NULL)
    {
        return NULL;
    }
    
    MB_NodeFriendEnergy* pInstance = new MB_NodeFriendEnergy;
    if (pInstance && pInstance->init())
    {
        pInstance->setData(pData);
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

CCSize MB_NodeFriendEnergy::getNodeSize()
{
    return size->getContentSize();
}

void MB_NodeFriendEnergy::onResetWnd()
{
    if (m_pData)
    {
        
        if (m_pData->getCanSendEnergy() == 1)
        {
            m_pBtSendEnergy->setEnabled(true);
        }
        else if (m_pData->getCanSendEnergy() == 0)
        {
            m_pBtSendEnergy->setEnabled(false);
        }
        else if (m_pData->getCanSendEnergy() == 2)
        {
            m_pBtSendEnergy->setEnabled(false);
        }
        
        m_pBtGiveEnergy->setEnabled(m_pData->getCanGiveEnergy());
        
        NSGameHelper::setRoleIcon(roleIcon, m_pData->getIsMale(), m_pData->getHead(), m_pData->getTitle());
        
        char buff[128] = {};
        std::string strRoleName =m_pData->getRoleName();
        sprintf(buff, "%llu",m_pData->getFightPower());
        fightPower->setString(buff);
        sprintf(buff, "Lv.%d",m_pData->getLevel());
        m_pNodeLevel->setString(buff);
        
        strRoleName = m_pData->getRoleName();
        if(!m_pData->getLocation().empty())
        {
            strRoleName += "["+m_pData->getLocation()+"]";
        }
        roleName->setString(strRoleName.c_str());
        
        if (m_pData->getLogoutTime() == 0) {
            status->setString("当前在线");
        }
        else
        {
            int timeFromNow = MB_ClientSocket::getInstance()->getServerTime() - m_pData->getLogoutTime();
            std::string ret = NSGameHelper::convertDeltaTime2Data(timeFromNow);
            status->setString(CCString::createWithFormat("%s",ret.c_str())->getCString());
        }

    }
}

bool MB_NodeFriendEnergy::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"size",CCNode*,size);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"roleIcon",CCSprite*,roleIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeLevel",CCLabelBMFont*,m_pNodeLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"roleName",CCLabelTTF*,roleName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"fightPower",CCLabelBMFont*,fightPower);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"status",CCLabelTTF*,status);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtSendEnergy",CCMenuItemImage*,m_pBtSendEnergy);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtGiveEnergy",CCMenuItemImage*,m_pBtGiveEnergy);
    
	return false;
}
SEL_MenuHandler MB_NodeFriendEnergy::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onRoleInfoClicked",MB_NodeFriendEnergy::onRoleInfoClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onGiveEnergyClicked",MB_NodeFriendEnergy::onGiveEnergyClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onSendEnergyClicked",MB_NodeFriendEnergy::onSendEnergyClicked);
	return NULL;
}
SEL_CCControlHandler MB_NodeFriendEnergy::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
void MB_NodeFriendEnergy::onRoleInfoClicked(CCObject* pSender)
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
void MB_NodeFriendEnergy::onGiveEnergyClicked(CCObject* pSender)
{
    if (m_pData)
    {
        if(MB_RoleData::getInstance()->getEnergyMax() <= MB_RoleData::getInstance()->getEnergy())
        {
            MB_Message::sharedMB_Message()->showMessage("体力已满, 无法领取");
            return;
        }
        if (MB_FriendMgr::getInstance()->getGetEnergyLastTimes() <= 0)
        {
            MB_Message::sharedMB_Message()->showMessage("没有体力领取剩余次数了,请明天再来");
            return;
        }
        
        MB_Message::sharedMB_Message()->showMessage("", 15);
        uint32_t id = m_pData->getRoleID();
        MB_FriendMgr::getInstance()->sendfriend_give_energy(1, &id);
    }
}
void MB_NodeFriendEnergy::onSendEnergyClicked(CCObject* pSender)
{
    if (m_pData && m_pData->getCanSendEnergy())
    {
        MB_Message::sharedMB_Message()->showMessage("", 15);
        uint32_t uid = m_pData->getRoleID();
        MB_FriendMgr::getInstance()->sendfriend_send_energy(1,&uid);
        m_pBtSendEnergy->setEnabled(false);
    }
    else
    {
        MB_Message::sharedMB_Message()->showMessage("当前不可赠送体力");
    }
}
const CCSize& MB_NodeFriendEnergy::getUISize()
{
    static CCSize  sz = CCSize(-1,-1);
    
    if (sz.width < 0)
    {
        MB_NodeFriendEnergy* pNode = new MB_NodeFriendEnergy;
        if (pNode->init())
        {
            sz = pNode->getNodeSize();
        }
        pNode->release();
    }
    return sz;
}
