//
//  MB_NodeFriendFight.cpp
//  ProjectMB
//
//  Create by wenyong on 17/3/2015.
//
//
#include "MB_NodeFriendFight.h"
#include "MB_DataFriend.h"

MB_NodeFriendFight::MB_NodeFriendFight()
{
    status = NULL;
    size	 = NULL;
    roleIcon	 = NULL;
    m_pNodeLevel	 = NULL;
    roleName	 = NULL;
    fightPower	 = NULL;
    m_pBtFight	 = NULL;
    m_pData = NULL;
}
MB_NodeFriendFight::~MB_NodeFriendFight()
{
    CC_SAFE_RELEASE_NULL(status);
    CC_SAFE_RELEASE_NULL(size);
    CC_SAFE_RELEASE_NULL(roleIcon);
    CC_SAFE_RELEASE_NULL(m_pNodeLevel);
    CC_SAFE_RELEASE_NULL(roleName);
    CC_SAFE_RELEASE_NULL(fightPower);
    CC_SAFE_RELEASE_NULL(m_pBtFight);
    CC_SAFE_RELEASE_NULL(m_pData);
}
bool MB_NodeFriendFight::init()
{
    CCNode* pNode = loadResource("res/friend_node_battle.ccbi");
    if(pNode)
	{
		addChild(pNode);
		return true;
	}
	return false;
}

MB_NodeFriendFight* MB_NodeFriendFight::create(MB_DataFriend* pData)
{
    if (pData == NULL)
    {
        return NULL;
    }
    
    MB_NodeFriendFight* pInstance = new MB_NodeFriendFight;
    if (pInstance && pInstance->init())
    {
        pInstance->setData(pData);
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;

}
void MB_NodeFriendFight::onResetWnd()
{
    if (m_pData)
    {
        m_pBtFight->setEnabled(m_pData->getCanFight());
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
bool MB_NodeFriendFight::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"size",CCNode*,size);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"roleIcon",CCSprite*,roleIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeLevel",CCLabelBMFont*,m_pNodeLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"roleName",CCLabelTTF*,roleName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"fightPower",CCLabelBMFont*,fightPower);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtFight",CCMenuItemImage*,m_pBtFight);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"status",CCLabelTTF*,status);
    
	return false;
}
SEL_MenuHandler MB_NodeFriendFight::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onRoleInfoClicked",MB_NodeFriendFight::onRoleInfoClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onFightClick",MB_NodeFriendFight::onFightClick);
	return NULL;
}
SEL_CCControlHandler MB_NodeFriendFight::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
void MB_NodeFriendFight::onRoleInfoClicked(CCObject* pSender)
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
void MB_NodeFriendFight::onFightClick(CCObject* pSender)
{
    if (m_pData)
    {
        if(m_pData->getCanFight())
        {
            MB_Message::sharedMB_Message()->showMessage("",15);
            MB_FriendMgr::getInstance()->sendfriend_fight(m_pData->getRoleID());
        }
        
    }
}

void MB_NodeFriendFight::setData(MB_DataFriend* pData)
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
CCSize MB_NodeFriendFight::getNodeSize()
{
    return size->getContentSize();
}

const CCSize& MB_NodeFriendFight::getUISize()
{
    static CCSize  sz = CCSize(-1,-1);
    
    if (sz.width < 0)
    {
        MB_NodeFriendFight* pNode = new MB_NodeFriendFight;
        if (pNode->init())
        {
            sz = pNode->getNodeSize();
        }
        pNode->release();
    }
    return sz;
}

