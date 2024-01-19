//
//  MB_NodeFriendInvite.cpp
//  ProjectPM
//
//  Create by WenYong on 11/5/2014.
//
//
#include "MB_NodeFriendInvite.h"
#include "MB_DataFriend.h"
#include "MB_LayerFriend.h"
MB_NodeFriendInvite::MB_NodeFriendInvite()
{
    cellSize	 = NULL;
    roleIcon	 = NULL;
    roleName	 = NULL;
    fightPower	 = NULL;
    m_pNodeLevel	 = NULL;
    status	 = NULL;
    nodeAdd	 = NULL;
    btAdd	 = NULL;
    m_pData = NULL;
    m_pNodeMsg = NULL;
    mode = kModeInvite;
    m_nSelectRoleID = 0;
}
MB_NodeFriendInvite::~MB_NodeFriendInvite()
{
    CC_SAFE_RELEASE_NULL(cellSize);
    CC_SAFE_RELEASE_NULL(roleIcon);
    CC_SAFE_RELEASE_NULL(roleName);
    CC_SAFE_RELEASE_NULL(fightPower);
    CC_SAFE_RELEASE_NULL(m_pNodeLevel);
    CC_SAFE_RELEASE_NULL(status);
    CC_SAFE_RELEASE_NULL(nodeAdd);
    CC_SAFE_RELEASE_NULL(btAdd);
    CC_SAFE_RELEASE_NULL(m_pData);
    CC_SAFE_RELEASE_NULL(m_pNodeMsg);
//    CC_SAFE_RELEASE_NULL(m_pNodeLevel);
}
MB_NodeFriendInvite* MB_NodeFriendInvite::create(MB_DataFriend* pData)
{
    if (pData == NULL)
    {
        return NULL;
    }
    
    MB_NodeFriendInvite* pInstance = new MB_NodeFriendInvite;
    if (pInstance && pInstance->init())
    {
        pInstance->setData(pData);
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return NULL;
}

bool MB_NodeFriendInvite::init()
{
    CCNode* pNode = loadResource("res/friend_node_unit.ccbi");
    if(pNode)
	{
		addChild(pNode);
		return true;
	}
	return false;
}
void MB_NodeFriendInvite::setData(MB_DataFriend *pData)
{
    if (pData == NULL)
    {
        return ;
    }
    
    CC_SAFE_RELEASE_NULL(m_pData);
    m_pData = pData;
    m_pData->retain();
    
    onResetWnd();
}

void MB_NodeFriendInvite::setMode(int md)
{
    mode = md;
    updateMode();
}

CCSize MB_NodeFriendInvite::getNodeSize()
{
    return cellSize->getContentSize();
}
void MB_NodeFriendInvite::onResetWnd()
{
    if (m_pData)
    {
        char buff[128] = {};
        std::string strRoleName =m_pData->getRoleName();
        sprintf(buff, "%llu",m_pData->getFightPower());
        fightPower->setString(buff);
        sprintf(buff, "Lv.%d",m_pData->getLevel());
        m_pNodeLevel->setString(buff);
        
        strRoleName = m_pData->getRoleName();
        roleName->setString(strRoleName.c_str());

        
        NSGameHelper::setRoleIcon(roleIcon, m_pData->getIsMale(), m_pData->getHead(), m_pData->getTitle());
        
        if (m_pData->getLogoutTime() == 0)
        {
            if(mode == kModeInvite)
            {
                status->setString("当前在线");
            }
            else if(mode == kModeMsg)
            {
                status->setString("刚刚");
            }
        }
        else
        {
            int timeFromNow = MB_ClientSocket::getInstance()->getServerTime() - m_pData->getLogoutTime();
            std::string ret = NSGameHelper::convertDeltaTime2Data(timeFromNow);
            status->setString(ret.c_str());
        }
        
        updateMode();
    }
}

void MB_NodeFriendInvite::updateMode()
{
    nodeAdd->setVisible(mode == kModeInvite);
    m_pNodeMsg->setVisible(mode == kModeMsg);
    if (m_pData)
    {
        btAdd->setEnabled(m_pData->getCanAdd()!=0);
    }
}

bool MB_NodeFriendInvite::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"size",CCNode*,cellSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"roleIcon",CCSprite*,roleIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"roleName",CCLabelTTF*,roleName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"fightPower",CCLabelBMFont*,fightPower);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeLevel",CCLabelBMFont*,m_pNodeLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"status",CCLabelTTF*,status);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"nodeAdd",CCNode*,nodeAdd);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"btAdd",CCMenuItemImage*,btAdd);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeMsg",CCNode*,m_pNodeMsg);
	return false;
}
SEL_MenuHandler MB_NodeFriendInvite::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onAddClicked",MB_NodeFriendInvite::onAddClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onAgreeClicked",MB_NodeFriendInvite::onAgreeClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onRefuseClicked",MB_NodeFriendInvite::onRefuseClicked);
	return NULL;
}
SEL_CCControlHandler MB_NodeFriendInvite::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
void MB_NodeFriendInvite::onAddClicked(CCObject* pSender)
{
    if (m_pData)
    {
        if (MB_RoleData::getInstance()->getUID()==m_pData->getRoleID())
        {
            MB_Message::sharedMB_Message()->showMessage("不能添加自己为好友。");
            return;
        }
        
//        int nMaxFriend = 0;
//        CCArray* array = MB_RoleData::getInstance()->getVipConfigArray();
//        MB_VipConfig* pTempData = NULL;
//        CCARRAY_FOREACH_4TYPE(array, MB_VipConfig*, pTempData)
//        {
//            if (pTempData->getlevel() == MB_RoleData::getInstance()->getVipLevel())
//            {
//                nMaxFriend = pTempData->getMaxFriendNum();
//            }
//        }
        if (MB_FriendMgr::getInstance()->getFriendArray()->count() >= 100) {
           MB_Message::sharedMB_Message()->showMessage("好友数量已达到上限");
            return;
        }
        
        MB_Message::sharedMB_Message()->showMessage("",15);
        uint32_t roleID = m_pData->getRoleID();
        MB_FriendMgr::getInstance()->sendfriend_add(1,&roleID);
        btAdd->setEnabled(false);
        m_pData->setCanAdd(0);
    }
}

void MB_NodeFriendInvite::onAgreeClicked(CCObject* pSender)
{
    if (m_pData)
    {
        uint32_t roleID = m_pData->getRoleID();
        MB_Message::sharedMB_Message()->showMessage("",15);
        MB_FriendMgr::getInstance()->sendfriend_agree(1,&roleID);
        
        CCArray* array =  MB_FriendMgr::getInstance()->getFriendMsgArray();
       array->removeObject(m_pData);
//        MB_TARGET_PARENT(MB_LayerFriend, ptr);
//        if(ptr)
//        {
//            ptr->dirty();
//        }
        
    }

}
void MB_NodeFriendInvite::onRefuseClicked(CCObject* pSender)
{
    if (m_pData)
    {
        uint32_t roleID = m_pData->getRoleID();
        MB_Message::sharedMB_Message()->showMessage("",15);
        MB_FriendMgr::getInstance()->sendfriend_refuse(1,&roleID);
        
        MB_FriendMgr::getInstance()->getFriendMsgArray()->removeObject(m_pData);
//        MB_TARGET_PARENT(MB_LayerFriend, ptr);
//        if(ptr)
//        {
//            ptr->dirty();
//        }
    }
}

const CCSize& MB_NodeFriendInvite::getUISize()
{
    static CCSize  sz = CCSize(-1,-1);
    
    if (sz.width < 0)
    {
        MB_NodeFriendInvite* pNode = new MB_NodeFriendInvite;
        if (pNode->init())
        {
            sz = pNode->getNodeSize();
        }
        pNode->release();
    }
    return sz;
}
