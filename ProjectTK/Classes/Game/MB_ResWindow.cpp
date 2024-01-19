

#include "MB_ResWindow.h"
#include "MB_LayerTutorialDialog.h"
#include "MB_LayerTutorial.h"
#include "Game.h"

//static int g_TestCount = 0;

MB_ResWindow::MB_ResWindow()
{
	m_pSubLayer = NULL;
	m_pLayerParent = NULL;
	m_pLayerParentDelete = NULL;
	m_pTutorialNodeArray = new CCArray();
	m_bIgnoreParent = false;
	m_propertyDirty = false;
	m_uTutorialTag = 0;
	m_bShowRoleInfoPanel = false;
    m_bShowHomeButton = false;
    m_bShowEXP = false;
	m_bTutorial = false;
	//    g_TestCount++;
	//    MB_LOG("                    layerwindow create to: %d", g_TestCount);
}
MB_ResWindow* MB_ResWindow::getSubLayer()
{
	return m_pSubLayer;
}
MB_ResWindow::~MB_ResWindow()
{
	if (m_bIgnoreParent)
	{
		releaseLogicParentAndSubLayer(this);
	}

	releaseSubLayerPtr(this);

	CC_SAFE_RELEASE(m_pLayerParentDelete);
	CC_SAFE_RELEASE(m_pTutorialNodeArray);
	m_pLayerParent = NULL;
	m_pSubLayer = NULL;
	//    g_TestCount--;
	//    MB_LOG("                    layerwindow destroy to: %d", g_TestCount);

}

void MB_ResWindow::releaseLogicParentAndSubLayer(MB_ResWindow* layer)
{
	//递归
	if (layer->m_pSubLayer != NULL) {
		releaseLogicParentAndSubLayer(layer->m_pSubLayer);
	}

	MB_ResWindow* layerNeedClean = layer->m_pLayerParent;
	while (layerNeedClean != NULL)
	{
		if (layerNeedClean->m_pLayerParentDelete == NULL)
		{
			layerNeedClean->m_pLayerParentDelete = layerNeedClean->m_pLayerParent;
		}

		layerNeedClean->cleanup();
		layerNeedClean = layerNeedClean->m_pLayerParent;
	}
}

void MB_ResWindow::releaseSubLayerPtr(MB_ResWindow *layer)
{
	MB_ResWindow* logicParent = layer->m_pLayerParent;
	if (logicParent != NULL)
	{
		if (logicParent->m_pSubLayer == layer)
		{
			logicParent->m_pSubLayer = NULL;
		}
	}

	MB_ResWindow* layerParent = dynamic_cast<MB_ResWindow*>(layer->m_pParent);
	if (layerParent != NULL && layerParent->m_pSubLayer == layer)
	{
		layerParent->m_pSubLayer = NULL;
	}
}


void MB_ResWindow::onEnter()
{
	CCLayer::onEnter();

	if (m_bTutorial)
	{
		//检查是否有引导
        onCheckTutorial();

		//开启计时器
		this->schedule(schedule_selector(MB_ResWindow::tick));
	}

	setTouchMode(kCCTouchesAllAtOnce); // 2014.5.12 wy
}
void MB_ResWindow::dirty()
{
	if (m_bTutorial)
	{
		m_propertyDirty = true;
	}
	else
	{
		onResetWnd();
	}
}
bool MB_ResWindow::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){

	return true;
}
void MB_ResWindow::replaceLayer(MB_ResWindow *layer, bool ignoreParent)
{
	//用于析构
	m_bIgnoreParent = ignoreParent;

	if (m_pParent != NULL)
	{
		m_pParent->addChild(layer);
		m_pParent->getChildren()->exchangeObject(this, layer);

		//当前隐藏的父层转交给新的layer
		if (m_pLayerParent != NULL)
		{
			//保存逻辑父节点
			if (!ignoreParent)
			{
				layer->setLogicParent(m_pLayerParent);
			}

			// null 证明不是poplayer
			if (m_pLayerParentDelete == NULL)
			{
				m_pLayerParentDelete = m_pLayerParent;
			}
		}

		//更新父节点的sublayer
		MB_ResWindow* tkParent = dynamic_cast<MB_ResWindow*>(this->getParent());
		if (tkParent != NULL) {
			tkParent->setSubLayer(layer);
		}
		//删除关联
		releaseSubLayerPtr(this);
		//删除自身
		removeFromParentAndCleanup(true);
		MB_LayerRoleInfoHeader::showRoleInfoHeader(layer->getShowRoleInfoPanel());
	}
	else
	{
		MB_LOG("error: rootNode can't replace!");
	}
}

void MB_ResWindow::popWindow(bool isUpdate)
{
	//pop后是否需要刷新parent数据
	if (m_pLayerParent == NULL)
	{
		if (isUpdate)
		{
			//更新父节点的sublayer
			MB_ResWindow* tkParent = dynamic_cast<MB_ResWindow*>(this->getParent());
			if (tkParent != NULL)
			{
				tkParent->dirty();
				tkParent->setSubLayer(NULL);
			}
		}
		MB_ResWindow* tkParent = dynamic_cast<MB_ResWindow*>(this->getParent());
		if (tkParent)MB_LayerRoleInfoHeader::showRoleInfoHeader(tkParent->getShowRoleInfoPanel());
		//删除关联
		releaseSubLayerPtr(this);
		//删除自身
		removeFromParentAndCleanup(true);
	}
	else
	{
		MB_LayerRoleInfoHeader::showRoleInfoHeader(m_pLayerParent->getShowRoleInfoPanel());
		if (isUpdate)
		{
			if (m_pLayerParent != NULL)
			{
				m_pLayerParent->dirty();
			}
		}
		MB_ResWindow* tempLayer = m_pLayerParent;
		m_pLayerParentDelete = m_pLayerParent;
		m_pLayerParent = m_pLayerParent->m_pLayerParent;

		if (m_pParent)
		{
			m_pParent->addChild(tempLayer);
			m_pParent->getChildren()->exchangeObject(this, tempLayer);
		}


		//更新父节点的sublayer
		MB_ResWindow* tkParent = dynamic_cast<MB_ResWindow*>(this->getParent());
		if (tkParent != NULL) {
			tkParent->setSubLayer(tempLayer);
		}
		//删除关联
		releaseSubLayerPtr(this);
		//删除自身
		removeFromParentAndCleanup(true);
	}

}

void MB_ResWindow::pushWindow(MB_ResWindow *layer, bool hideParent)
{
	//如果要隐藏,则实际是兄弟节点
	if (hideParent) {

		if (m_pParent != NULL) {
			m_pParent->addChild(layer);
			m_pParent->getChildren()->exchangeObject(this, layer);
			layer->setLogicParent(this);

			//更新父节点的sublayer
			MB_ResWindow* tkParent = dynamic_cast<MB_ResWindow*>(m_pParent);
			if (tkParent != NULL) {
				tkParent->setSubLayer(layer);
			}

			removeFromParentAndCleanup(false);
		}
		else
		{
			MB_LOG("error: rootNode can't replace!");
		}
	}
	else
	{
		//更新当前节点的sublayer
		MB_ResWindow* curLayer = dynamic_cast<MB_ResWindow*>(this);
		if (curLayer != NULL) {
			curLayer->setSubLayer(layer);
		}

		addChild(layer);
	}

	MB_LayerRoleInfoHeader::showRoleInfoHeader(layer->getShowRoleInfoPanel());
}

void MB_ResWindow::setLogicParent(MB_ResWindow *layer)
{
	m_pLayerParent = layer;
	m_pLayerParentDelete = layer;
	CC_SAFE_RETAIN(m_pLayerParent);
}

void MB_ResWindow::replaceSubLayer(MB_ResWindow* pWnd)
{
	if (m_pSubLayer && pWnd)
	{
		m_pSubLayer->replaceLayer(pWnd);
	}
}

void MB_ResWindow::setSubLayer(MB_ResWindow *layer)
{
	m_pSubLayer = layer;
}

MB_ResWindow* MB_ResWindow::getLogicParent()
{
	if (m_pLayerParent != NULL) {
		return m_pLayerParent;
	}
	else
	{
		MB_ResWindow* layerParent = dynamic_cast<MB_ResWindow*>(m_pParent);
		if (layerParent != NULL) {
			return layerParent;
		}
		else
		{
			MB_LOG("need a tk_layerwindow parent.");
			return NULL;
		}
	}
}

void MB_ResWindow::onResetWnd(void)
{
}

bool MB_ResWindow::canResetWnd(void)
{
	return true;
}

void MB_ResWindow::onCheckTutorial()
{

//    if (NULL == CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN))return;

	CCNode* pNode = NULL;
	//m_pTutorialNodeArray 当前界面所有需要引导的Node
	for (int i = 0; i < m_pTutorialNodeArray->count(); ++i)
	{
		pNode = (CCNode*)m_pTutorialNodeArray->objectAtIndex(i);
		if (pNode != NULL)
		{
			if (MB_TutorialMgr::getInstance()->canTrigpetByTagID(pNode->getTag()))
			{
				int skipCount = MB_TutorialMgr::getInstance()->GataOpenSkip();
				if (skipCount != 0)
				{
					for (int i = 0; i < skipCount; ++i)
					{
						TutorialForcedTrigpetComplete
					}
				}
				else
				{
					//开始引导
					MB_TutorialTemplete* pCurTemplete = MB_TutorialMgr::getInstance()->getCurTemplete();
					if (pCurTemplete)
					{
						MB_ResWindow* layer = NULL;
						if (pCurTemplete->getType() == 2)
						{
                            layer = MB_LayerTutorialDialog::create();
						}
						else
						{
                            layer = MB_LayerTutorial::create(pNode);
						}

						if (layer)
						{
                            global_tutorialNode = layer;
							layer->setTag(pNode->getTag());
							CCDirector::sharedDirector()->getRunningScene()->addChild(layer, 1999);
							MB_TutorialMgr::getInstance()->setHasTutorialDilog(true);
						}
					}
				}
			}
		}
	}
}

void MB_ResWindow::tick(float dt)
{
	onCheckTutorial();

	if (m_propertyDirty)
	{
		onResetWnd();
		m_propertyDirty = false;
	}
}

bool MB_ResWindow::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{

	if (pTarget == this && strncmp(pMemberVariableName, "tutorial", 8) == 0)
	{
        //TODODO 直接跳过引导
        m_bTutorial = true;
		pNode->setZOrder(100);
		m_pTutorialNodeArray->addObject(pNode);
		return true;
	}
	return false;
}
CCNode* MB_ResWindow::loadResource(const char* pName)
{
	CCLOG("pName=========+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++%s", pName);
	CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
	CCNode* pNode = pCCBReader->readNodeGraphFromFile(pName, this);

	CC_SAFE_RELEASE(pCCBReader);

	return pNode;
}

