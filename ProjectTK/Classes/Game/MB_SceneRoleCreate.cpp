

#include "MB_SceneRoleCreate.h"
#include "MB_RoleLayerSelectPartner.h"
#include "MB_LayerAnimation.h"
#ifdef PLATFORM_YJ
#include "MB_YJMgr.h"
#endif

#ifdef YJ_IOS
#include "MB_YJMgr_IOS.h"
#endif
USING_NS_CC;
USING_NS_CC_EXT;

MB_SceneRoleCreate::MB_SceneRoleCreate()
{
	m_iSex = 2;
	m_pButtonMale = NULL;
	m_pButtonFemale = NULL;
	m_pRoleName = NULL;
	m_iActionMark = 2;
	m_pAnimation = NULL;
	SOCKET_MSG_REGIST(SC_ACCOUNT_CREATE, MB_SceneRoleCreate);
	SOCKET_MSG_REGIST(SC_ROLE_SELECT_GER, MB_SceneRoleCreate);
	if (!initNameTemplete()) {
		MB_LOG("init name templete failed.");
	}
}

MB_SceneRoleCreate::~MB_SceneRoleCreate()
{
	SOCKET_MSG_UNREGIST(SC_ACCOUNT_CREATE);
	SOCKET_MSG_UNREGIST(SC_ROLE_SELECT_GER);
	CC_SAFE_RELEASE_NULL(m_pButtonMale);
	CC_SAFE_RELEASE_NULL(m_pButtonFemale);
	CC_SAFE_RELEASE_NULL(m_pRoleName);
}

CCScene* MB_SceneRoleCreate::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	MB_SceneRoleCreate *layer = MB_SceneRoleCreate::create();

	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

void MB_SceneRoleCreate::onAnimationCallBack(CCNode* pNode)
{
	pNode->removeFromParent();
	if (pNode == m_pAnimation)
	{
		m_pAnimation = NULL;
	}
}
// on "init" you need to initialize your instance
bool MB_SceneRoleCreate::init()
{
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}

	m_pAnimation = MB_LayerAnimation::create("res/excessive_layer.ccbi");

	// 创建了角色，但是没有选择宠物，则直接进入宠物选择几面
	if (!MB_ServerList::getInstance()->getIsSelectParnter() && MB_ServerList::getInstance()->getisCreateRole())
	{
		MB_RoleLayerSelectPartner* pWnd = MB_RoleLayerSelectPartner::create();
		if (pWnd)
		{
			pushWindow(pWnd);
		}
		return true;
	}

	//init CCBReader
	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
//    if (MB_ServerList::getInstance()->getIsShowCode() == 1){
//
//        CCNode *pScene = pCCBReader->readNodeGraphFromFile("res/role_layer_create.ccbi", this);
//        this->addChild(pScene);
//        CC_SAFE_RELEASE_NULL(pCCBReader);
//
//    }
//    else{

		CCNode *pScene = pCCBReader->readNodeGraphFromFile("res/role_layer_create.ccbi", this);
		this->addChild(pScene);
		CC_SAFE_RELEASE_NULL(pCCBReader);
//    }


	//初始化一个名字
	randomName();

	m_pButtonFemale->setIsScale(false);
	m_pButtonMale->setIsScale(false);

	onFemaleClicked(NULL);

	if (m_pAnimation)
	{
		addChild(m_pAnimation);
		m_pAnimation->runAnimationWithCallBack("1", this, callfuncN_selector(MB_SceneRoleCreate::onAnimationCallBack));
	}
	return true;
}



bool MB_SceneRoleCreate::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Male", CCMenuItemImage*, m_pButtonMale);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Female", CCMenuItemImage*, m_pButtonFemale);
	if (0 == strcmp(pMemberVariableName, "Account") && pTarget == this)
	{
		initRoleEditBox((CCEditBox*)pNode);
		return true;
	}


	return true;
}

SEL_MenuHandler MB_SceneRoleCreate::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMaleClicked", MB_SceneRoleCreate::onMaleClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onFemaleClicked", MB_SceneRoleCreate::onFemaleClicked);
	return NULL;
}
SEL_CCControlHandler MB_SceneRoleCreate::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onRandomClicked", MB_SceneRoleCreate::onRandomClicked);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onNextStepClicked", MB_SceneRoleCreate::onNextStepClicked);
	return NULL;
}

void MB_SceneRoleCreate::onNextStepClicked(CCObject* pSender)
{
	std::string pName = m_pRoleName->getText();
	if (checkUserName(pName.c_str()))
	{
		MB_RoleData::getInstance()->setName(pName.c_str());
		MB_Message::sharedMB_Message()->showMessage("", 15);
		sendrolename_check(pName.c_str());
	}
}

void MB_SceneRoleCreate::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox)
{
	MB_LOG("editBox %p DidBegin !", editBox);
	editBox->setPosition(editBox->getPosition());
}

void MB_SceneRoleCreate::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox)
{
	MB_LOG("editBox %p DidEnd !", editBox);
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

void MB_SceneRoleCreate::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{
	MB_LOG("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void MB_SceneRoleCreate::editBoxReturn(CCEditBox* editBox)
{
	MB_LOG("editBox %p was returned !");

}

void MB_SceneRoleCreate::onMaleClicked(CCObject *pSender)
{
	m_pButtonMale->selected();
	m_pButtonFemale->unselected();
	if (m_iSex == 1) {
		return;
	}

	m_iSex = 1;
	randomName();
}

void MB_SceneRoleCreate::onFemaleClicked(CCObject *pSender)
{
	m_pButtonFemale->selected();
	m_pButtonMale->unselected();
	if (m_iSex == 2) {
		return;
	}

	m_iSex = 2;
	randomName();
}


static bool checkName(const unsigned short* pName)
{
	size_t nUnicodeLength = cc_wcslen(pName);

	for (int i = 0; i < nUnicodeLength; ++i)
	{
		if (pName[i] >= 0x4e00 && pName[i] <= 0x9fff)
		{
			continue;
		}
		else
		{
			if ((pName[i] >= 'A' && pName[i] <= 'Z') || (pName[i] >= 'a' && pName[i] <= 'z') || (pName[i] >= '0' && pName[i] <= '9'))
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



bool MB_SceneRoleCreate::checkUserName(const char* pName)
{
	if (pName == NULL)
	{
		return false;
	}
	if (strcmp("", pName) == 0)
	{
		MB_Message::sharedMB_Message()->showMessage("名字不能为空");
		return false;
	}
	unsigned short* pUnicode16 = cc_utf8_to_utf16(pName);

	int len = cc_wcslen(pUnicode16);
	if (len > 8)
	{
		MB_Message::sharedMB_Message()->showMessage("错误", "您的名字太长了", "确定");
		return false;
	}

	if (MB_DirtyWordsCheck::getInstance()->checkDatabuf(pName))
	{
		MB_Message::sharedMB_Message()->showMessage("错误", "含有非法字符, 请修改您的名字", "确定");
		return false;
	}

	if (!checkName(pUnicode16))
	{
		MB_Message::sharedMB_Message()->showMessage("错误", "含有非法字符, 请修改您的名字", "确定");
		return false;
	}
	CC_SAFE_DELETE_ARRAY(pUnicode16);
	return true;
}

void MB_SceneRoleCreate::onRandomClicked(cocos2d::CCObject *pSender)
{
	randomName();
}

void MB_SceneRoleCreate::initRoleEditBox(CCEditBox* editBox)
{
	editBox->setColor(ccWHITE);
	editBox->setDelegate(this);
	m_pRoleName = editBox;
	m_pRoleName->retain();
}

void MB_SceneRoleCreate::sendrolename_check(const char* pName)
{
	SOCKET_MSG_REGIST(SC_ROLENAME_CHECK, MB_SceneRoleCreate);
	SOCKET_REQUEST_START(CS_ROLENAME_CHECK);
	packet->Write(pName, strlen(pName));
	SOCKET_REQUEST_END(SC_ROLENAME_CHECK, NULL);
}

/*
 message recvaccount_check_rolename[id=10017]{
 required	int8			result		=1;
 //1=>可以创建
 //3 => 角色名称已经被使用
 //4 => 非法字符
 //5 => 角色名称长度为1~5个汉字
 }
 */
void MB_SceneRoleCreate::recvrolename_check(MB_MsgBuffer* recvPacket)
{
	uint8_t u8 = 0;
	recvPacket->readU8(&u8);
	MB_Message::sharedMB_Message()->removeALLMessage();
	SOCKET_MSG_UNREGIST(SC_ROLENAME_CHECK);
	if (u8 == 1)
	{
		MB_RoleLayerSelectPartner* pWnd = MB_RoleLayerSelectPartner::create();
		if (pWnd)
		{
			pushWindow(pWnd);
		}
	}
	else if (u8 == 3)
	{
		MB_Message::sharedMB_Message()->showMessage("角色名称已经被使用");
	}
	else if (u8 == 4)
	{
		MB_Message::sharedMB_Message()->showMessage("非法字符");
	}
	else if (u8 == 5)
	{
		MB_Message::sharedMB_Message()->showMessage("角色名称长度为1~8个汉字");
	}
}
void MB_SceneRoleCreate::sendaccount_create()
{
	MB_Message::sharedMB_Message()->showMessage("", 30);
	std::string  accName = m_pRoleName->getText();
	uint8_t sex = m_iSex;

	SOCKET_REQUEST_START(CS_ACCOUNT_CREATE);
	//冒险家名字
	packet->Write(accName.c_str(), accName.length());
	//性别
	packet->writeU8(sex);
	SOCKET_REQUEST_END(SC_ACCOUNT_CREATE, MB_SceneRoleCreate);
}

void MB_SceneRoleCreate::recvaccount_create(MB_MsgBuffer *recvPacket)
{
	uint8_t Data;
	recvPacket->readU8(&Data);
	MB_Message::sharedMB_Message()->removeALLMessage();
	switch (Data) {
	case 1:
	{
			  sendrole_select_pet();
			  MB_Message::sharedMB_Message()->showMessage("", 15);

#ifdef PLATFORM_YJ
			  if( MB_RoleData::getInstance()->getUID() > 0 )
				  MB_YJMgr::getInstance()->creatRole();
			  else
				  MB_RoleData::getInstance()->IsCheckSetRoleData = true;
#endif
#ifdef YJ_IOS
			  if( MB_RoleData::getInstance()->getUID() > 0 )
				  MB_YJMgr_IOS::getInstance()->creatRole();
			  else
				  MB_YJMgr_IOS::getInstance()->IsCheckSetRoleData = true;
#endif
			  break;
	}
	case 0:
		MB_Message::sharedMB_Message()->showMessage("创建失败");
		break;
	case 2:
		MB_Message::sharedMB_Message()->showMessage("未知错误");
		break;
	case 3:
		MB_Message::sharedMB_Message()->showMessage("角色名称已经被使用");
		break;
	case 4:
		MB_Message::sharedMB_Message()->showMessage("非法字符");
		break;
	case 5:
		MB_Message::sharedMB_Message()->showMessage("角色名称长度为1~8个汉字");
		break;
	case 6:
		MB_Message::sharedMB_Message()->showMessage("用户已经创建角色");
		break;

	default:
		MB_Message::sharedMB_Message()->showMessage("玩家创建错误号：%d", Data);
		break;
	}
}
bool MB_SceneRoleCreate::sendrole_select_pet()
{
	MB_Message::sharedMB_Message()->showMessage("", 5);
	SOCKET_REQUEST_START(CS_ROLE_SELECT_GER);
	packet->writeU16(m_nSelectPet);
	SOCKET_REQUEST_END(SC_ROLE_SELECT_GER, MB_SceneRoleCreate);
	return true;
}


bool MB_SceneRoleCreate::recvrole_select_pet(MB_MsgBuffer *recvPacket)
{
	uint8_t result;
	MB_Message::sharedMB_Message()->removeALLMessage();
	if (recvPacket->readU8(&result)) {
		if (result == 1)
		{
			CCScene* pScene = MB_SceneLoading::scene();
			CCDirector::sharedDirector()->replaceScene(pScene);
			return true;
		}
		else
		{
			MB_LOG("pet select failed. errcode:%d", result);

			if (result == 2) {
				MB_Message::sharedMB_Message()->showMessage("已经领取过了.");
			}
			else if (result == 3)
			{
				MB_Message::sharedMB_Message()->showMessage("该精灵不能领取.");
			}
			else if (result == 4)
			{
				MB_Message::sharedMB_Message()->showMessage("未知错误.");
			}
		}
	}
	return false;
}
void MB_SceneRoleCreate::onMsgRecv(CCNode* node, SocketResponse* response)
{
	assert(response != NULL);

	//将socket数据读取到序列化结构
	MB_MsgBuffer* recvPacket = response->getResponseData();

	//协议号
	uint16_t Msg = 0;
	recvPacket->Reset();
	recvPacket->skipU16();
	recvPacket->skipU8();
	recvPacket->readU16(&Msg);

	switch (Msg) {
	case SC_ACCOUNT_CREATE://冒险家创建信息反馈
		recvaccount_create(recvPacket);
		break;
	case SC_ROLE_SELECT_GER:
		recvrole_select_pet(recvPacket);
		break;
	case SC_ROLENAME_CHECK:
		recvrolename_check(recvPacket);
		break;
	default:
		break;
	}

}

bool MB_SceneRoleCreate::initNameTemplete()
{
	xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/role_name.xml");

	if (!g_sharedDoc)
	{
		return false;
	}

	xmlNodePtr root;

	root = xmlDocGetRootElement(g_sharedDoc);
	xmlNodePtr curNode = root->xmlChildrenNode;
	char* value;
	int type = 1;
	while (curNode != NULL) {

		if (xmlStrcmp(curNode->name, BAD_CAST "name")) {
			curNode = curNode->next;
			continue;
		}

		struct _xmlAttr * attr = curNode->properties;

		if (attr != NULL) {

			if (attr&&!xmlStrcmp(attr->name, BAD_CAST "type"))
			{
				value = (char*)xmlNodeGetContent(attr->children);
				type = atoi(value);
				CC_SAFE_FREE(value);
				attr = attr->next;
			}

			if (attr&&!xmlStrcmp(attr->name, BAD_CAST "name"))
			{
				value = (char*)xmlNodeGetContent(attr->children);
				if (type == 0)
				{
					m_vecMaleFirstName.push_back(value);
				}
				else if (type == 1)
				{
					m_vecFemaleFirstName.push_back(value);

				}
				else if (type == 2)
				{
					m_vecMaleName.push_back(value);
				}
				else if (type == 3)
				{
					m_vecFemaleName.push_back(value);
				}
				CC_SAFE_FREE(value);
			}
		}
		curNode = curNode->next;
	}

	xmlFreeDoc(g_sharedDoc);

	return true;
}

void MB_SceneRoleCreate::randomName()
{
	if (m_iSex == 1) {
		int firstCount = m_vecMaleFirstName.size();
		int lastCount = m_vecMaleName.size();
		assert(firstCount > 0 && lastCount > 0);

		std::string tempName;
		tempName = m_vecMaleFirstName.at(rand() % firstCount);
		tempName += m_vecMaleName.at(rand() % lastCount);
		m_pRoleName->setText(tempName.c_str());
	}
	else
	{
		int firstCount = m_vecFemaleFirstName.size();
		int lastCount = m_vecFemaleName.size();
		assert(firstCount > 0 && lastCount > 0);

		std::string tempName;
		tempName = m_vecFemaleFirstName.at(rand() % firstCount);
		tempName += m_vecFemaleName.at(rand() % lastCount);
		m_pRoleName->setText(tempName.c_str());
	}

}

void MB_SceneRoleCreate::onMonsterSeleted(uint16_t tid)
{
	// 现走创建角色流程，再发送选择的精灵TID
	m_nSelectPet = tid;
	if (MB_ServerList::getInstance()->getisCreateRole())
	{
		sendrole_select_pet();
	}
	else
	{
		sendaccount_create();
	}
}

void MB_SceneRoleCreate::onFlipLeft()
{
	if (m_iSex == 2)
	{
		onMaleClicked(NULL);
		return;
	}
	if (m_iSex == 1)
	{
		onFemaleClicked(NULL);
		return;
	}

}
void MB_SceneRoleCreate::onFlipRight()
{
	onFlipLeft();
}
