

#include "MB_LayerVipInfo.h"
#include "RichText.h"
#include "MB_LayerRoleDetail.h"
USING_NS_CC;
USING_NS_CC_EXT;

MB_LayerVipInfo::MB_LayerVipInfo(bool dealwithheadinfomenu)
{
	m_pVipContainer = NULL;
	m_pCellSize = NULL;
	m_strVipLevel = NULL;
	m_nCurrentPage = 0;
	m_pBtnLeft = NULL;
	m_pBtnRight = NULL;
	m_pVipLevel = NULL;
	m_bDealWithHeadInfoMenu = dealwithheadinfomenu;
	if (m_bDealWithHeadInfoMenu)
		MB_LayerRoleInfoHeader::setMenuEnable(false, "MB_LayerVipInfo");
}

MB_LayerVipInfo::~MB_LayerVipInfo()
{
	CC_SAFE_RELEASE_NULL(m_pVipContainer);
	CC_SAFE_RELEASE_NULL(m_pCellSize);
	CC_SAFE_DELETE_ARRAY(m_strVipLevel);
	CC_SAFE_RELEASE_NULL(m_pBtnLeft);
	CC_SAFE_RELEASE_NULL(m_pBtnRight);
	CC_SAFE_RELEASE_NULL(m_pVipLevel);
	m_VipContent.clear();
	m_nCurrentPage = 0;

	if (m_bDealWithHeadInfoMenu)
		MB_LayerRoleInfoHeader::setMenuEnable(true, "MB_LayerVipInfo");
}

MB_LayerVipInfo* MB_LayerVipInfo::create(CCObject* p)
{
	bool b = dynamic_cast<MB_LayerRoleDetail*>(p);
	MB_LayerVipInfo* layer = new MB_LayerVipInfo(!b);
	if (layer != NULL && layer->init()) {
		layer->autorelease();
		return layer;
	}
	delete layer;
	return NULL;
}

bool MB_LayerVipInfo::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	m_strVipLevel = new char[8];
	sprintf(m_strVipLevel, "%d", MB_RoleData::getInstance()->getVipLevel());

	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
	CCNode *pScene = pCCBReader->readNodeGraphFromFile("res/vip_layer_description.ccbi", this);
	addChild(NSGameHelper::createDisableTouchLayer());
	this->addChild(pScene);
	CC_SAFE_RELEASE_NULL(pCCBReader);
	NSGameHelper::adjustScrollNode(m_pVipContainer);
	loadDetail();
	m_nCurrentPage = MB_RoleData::getInstance()->getVipLevel() - 1;
	if (m_nCurrentPage < 0) {
		m_nCurrentPage = 0;
	}
	onResetWnd();
	setTouchEnabled(true);
	return true;
}

void MB_LayerVipInfo::onTurnleftClicked(CCObject* pSender)
{
	if (detailExist(m_nCurrentPage - 1))
	{
		m_nCurrentPage -= 1;
		onResetWnd();
	}
}

void MB_LayerVipInfo::onTurnRightClicked(CCObject* pSender)
{
	if (detailExist(m_nCurrentPage + 1))
	{
		m_nCurrentPage += 1;
		onResetWnd();
	}
}

void MB_LayerVipInfo::onResetWnd()
{
	if (!detailExist(m_nCurrentPage))
	{
		return;
	}

	m_pBtnLeft->setVisible(detailExist(m_nCurrentPage - 1));
	m_pBtnRight->setVisible(detailExist(m_nCurrentPage + 1));

	m_pVipContainer->removeAllChildren();

	CCNode* pNode = createVipUnit(m_nCurrentPage);
	if (pNode)
	{
		m_pVipContainer->addChild(pNode);
		pNode->setPositionY(pNode->getPositionY() + m_pVipContainer->getContentSize().height - pNode->getContentSize().height);
	}

	char buff[64] = {};
	if (m_nCurrentPage + 1 < 16)
	{
		sprintf(buff, "VIP%d", m_nCurrentPage + 1);
	}
	else
	{
		sprintf(buff, "GM %d", m_nCurrentPage + 1 - 15);
	}

	m_pVipLevel->setString(buff);
}
static void convertToRbfString(std::string& str)
{
	for (int i = 0; i < str.length(); ++i)
	{
		if (str[i] == '{')
		{
			str[i] = '<';
		}
		else if (str[i] == '}')
		{
			str[i] = '>';
		}
	}
}

bool MB_LayerVipInfo::detailExist(int index)
{
	return index < m_VipContent.size() && index >= 0;
}

CCNode* MB_LayerVipInfo::createVipUnit(int index)
{
	if (!detailExist(index))
	{
		return NULL;
	}

	RichText* m_pRBDetail = RichText::create(m_VipContent[index].c_str(), 20, m_pVipContainer->getContentSize());
	m_pRBDetail->setAnchorPoint(CCPointZero);
	return m_pRBDetail;
}
bool MB_LayerVipInfo::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pVipContainer", CCNode*, m_pVipContainer);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cellSize", CCNode*, m_pCellSize);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBtnLeft", CCNode*, m_pBtnLeft);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBtnRight", CCNode*, m_pBtnRight);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pVipTitle", CCLabelBMFont*, m_pVipLevel);
	if (pTarget == this && strcmp(pMemberVariableName, m_strVipLevel) == 0)
	{
		pNode->setVisible(true);
		return true;
	}

	return true;
}

SEL_MenuHandler MB_LayerVipInfo::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerVipInfo::onCloseClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onTurnleftClicked", MB_LayerVipInfo::onTurnleftClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onTurnRightClicked", MB_LayerVipInfo::onTurnRightClicked);
	return NULL;
}

SEL_CCControlHandler MB_LayerVipInfo::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

void MB_LayerVipInfo::onCloseClicked(CCObject* sender)
{
	this->removeFromParent();
}

void MB_LayerVipInfo::loadDetail()
{
	m_VipContent.clear();
	MB_XmlFile* pFile = MB_XmlFile::create("config/vip_description.xml");
	CCArray* pArray = CCArray::create();

	if (pFile->queryNodesByName("helps|help", pArray))
	{
		MB_XmlNode* pTemp = NULL;
		std::string text;
		CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pTemp)
		{
			text = pTemp->queryAttributeByName("vip")->getCString();
			convertToRbfString(text);
			m_VipContent.push_back(text);
		}
	}
}

bool MB_LayerVipInfo::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{

	CCPoint point = pTouch->getLocation();
	CCPoint  des = m_pVipContainer->convertToNodeSpace(point);
	if (des.x > 0 && des.x < m_pVipContainer->getContentSize().width && des.y > 0 && des.y < m_pVipContainer->getContentSize().height)
	{
		m_pPoint = pTouch->getLocation();
		return  true;
	}
	return false;
}

void MB_LayerVipInfo::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	float x = pTouch->getLocation().x - m_pPoint.x;
	if (x < -50.0)
	{
		onTurnRightClicked(this);
	}
	else if (x > 50)
	{
		onTurnleftClicked(this);
	}
}
