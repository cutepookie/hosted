//
//  MB_LayerWorld.cpp
//  ProjectPM
//
//  Create by WenYong on 18/6/2014.
//
//
#include "MB_LayerWorld.h"
#include "MB_NodeBannerEntry.h"
#include "MB_TutorialMgr.h"
#include "MB_ScrollBg.h"
static float g_offset_height = 10000.0f;
MB_LayerWorld::MB_LayerWorld()
{
    m_pContainer	 = NULL;
    m_pView = NULL;
    m_pNodeTutorial = NULL;
    m_bShowRoleInfoPanel = true;
}
MB_LayerWorld::~MB_LayerWorld()
{
    CC_SAFE_RELEASE_NULL(m_pContainer);
    CC_SAFE_RELEASE_NULL(m_pView);
    CC_SAFE_RELEASE_NULL(m_pNodeTutorial);
    m_nTypes.clear();
}
void MB_LayerWorld::onEnter()
{
    MB_ResWindow::onEnter();
    
    static int lastRoleLevel = MB_RoleData::getInstance()->getLevel();
    if(lastRoleLevel == MB_RoleData::getInstance()->getLevel())
    {
        NSGameFunction::FunctionType funid = MB_TutorialMgr::getInstance()->getFunID();
        if(funid == 0)
        {
            if(g_offset_height<9000.0f)
            {
                m_pView->setContentOffset(ccp(0,g_offset_height));
            }
        }
    }
    else
    {
        lastRoleLevel = MB_RoleData::getInstance()->getLevel();
    }
}
void MB_LayerWorld::onExit()
{
    MB_ResWindow::onExit();
    g_offset_height = m_pView->getContentOffset().y;
}
void MB_LayerWorld::onEnterTransitionDidFinish()
{
    MB_ResWindow::onEnterTransitionDidFinish();
    PlayBackGround(ksSound_ShiLian);
}
bool MB_LayerWorld::init()
{
    CCNode* pNode = loadResource("res/station_layer_main.ccbi");
    if(pNode)
	{
		addChild(pNode);
        
        NSGameHelper::adjustScrollNode(m_pContainer);
        m_pView = CCTableView::create(this,m_pContainer->getContentSize());
        m_pView->retain();
        m_pView->setDirection(kCCScrollViewDirectionVertical);
        m_pView->setSwaller(false);
        m_pContainer->addChild(m_pView);
        ready4Data();
        m_pView->reloadData();
        
        m_pView->setContentOffset(ccp(0,m_pContainer->getContentSize().height-m_pView->getContainer()->getContentSize().height));
        NSGameFunction::FunctionType funid = MB_TutorialMgr::getInstance()->getFunID();
        if(funid != 0)
        {
            bindTutorialPostion(funid);
        }
        
        addChild(MB_ScrollBg::create(right_bottom,.5f,4),-1);
		return true;
	}
	return false;
}


void MB_LayerWorld::onResetWnd()
{
    NSGameHelper::reloadDataWithNoMove(m_pView);
}

/*
 type="201" name="研究所"
 type="202" name="铃铃塔"
 type="203" name="无尽深渊"
 type="204" name="竞技场"
 type="205" name="华丽大赛"
 type="206" name="3v3"
 type="207" name="异星战场"
 */
void MB_LayerWorld::ready4Data()
{
    m_CellSize = MB_NodeBannerEntry::getUnitSize();
    
    pushValidateType(kFunctionResearchInstitute);   // 10 
    pushValidateType(kFunctionBudokan);//道观
    pushValidateType(kFunctionPerfectRace);         // 30
    pushValidateType(kFunctionRuleFight);         // 30
    pushValidateType(kFunctionTrainerTrove); //玩家宝藏
    pushValidateType(kFunctionTrainerRoad);         // 30
    pushValidateType(kFunctionNoRuleFight);         // 50
}

void MB_LayerWorld::pushValidateType(int type)
{
//    if (MB_FunctionConfigure::getInstance()->getFunctionLimitLevel(type)<=MB_RoleData::getInstance()->getLevel())
//    {
        m_nTypes.push_back(type);
//    }
}

bool MB_LayerWorld::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "tutorial", CCNode*, m_pNodeTutorial);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pContainer",CCNode*,m_pContainer);
	return false;
}
SEL_MenuHandler MB_LayerWorld::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerWorld::onCloseClick);
	return NULL;
}
SEL_CCControlHandler MB_LayerWorld::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

bool MB_LayerWorld::bindTutorialPostion(int kFuntionType)
{
    int index = functionIndex(kFuntionType);
    
    if (-1 == index)
    {
        return false;
    }
    
    float top = index * m_CellSize.height;
    float range = m_pContainer->getContentSize().height - m_pView->getContainer()->getContentSize().height;
    
    float dest = range + top;
    
    if (dest > 0 )
    {
        float target = m_pContainer->getContentSize().height;
        float height = (index+1)*m_CellSize.height;
        target = target - height;
        if(target<0)
        {
            dest = 0;
        }
        else
        {
            dest = range;
        }
    }
    
    m_pView->setContentOffset(ccp(0, dest));
    
    CCNode* pCell = m_pView->getContainer()->getChildByTag(kFuntionType);
    
    if (pCell)
    {
        CCPoint pt = pCell->getPosition();
        pt.x += m_CellSize.width/2.0;
        pt.y += m_CellSize.height/2.0;
        pt = pCell->getParent()->convertToWorldSpace(pt);
        pt = m_pNodeTutorial->getParent()->convertToNodeSpace(pt);
        m_pNodeTutorial->setPosition(pt);
        return true;
    }
    
    return false;
}

int MB_LayerWorld::functionIndex(int kFuntionType)
{
    std::vector<int>::iterator it = m_nTypes.begin();
    int index = 0;
    for (; it!=m_nTypes.end(); ++it,++index)
    {
        if (*it == kFuntionType)
        {
            return index;
        }
    }
    
    return -1;
}
void MB_LayerWorld::onCloseClick(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionYeShiJie, this);
}

CCSize MB_LayerWorld::cellSizeForTable(CCTableView *table)
{
    return m_CellSize;
}

CCTableViewCell* MB_LayerWorld::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell = table->dequeueCell();
    if (cell == NULL)
    {
        cell = new CCTableViewCell();
        cell->autorelease();
    }
    else
    {
        cell->removeAllChildren();
    }
    if (idx<2) {
        return cell;
    }
    idx = numberOfCellsInTableView(table) - idx - 1;
    CCFunctionInterface* pInterface = NULL;
    MB_FunctionMgr::getInstance()->queryFunctionByType(m_nTypes[idx], &pInterface);
    if (pInterface)
    {
        MB_NodeBannerEntry* pNode = (MB_NodeBannerEntry*)pInterface->createEntryDialog();
        if (pNode)
        {
            if (MB_FunctionConfigure::getInstance()->getFunctionLimitLevel(m_nTypes[idx])>MB_RoleData::getInstance()->getLevel())
            {
                pNode->showActivities(false);
            }
            cell->addChild(pNode);
            cell->setTag(pInterface->getFunctionType());
            pNode->setPosition(m_CellSize.width/2.0, m_CellSize.height/2.0);
        }
    }
    
    return cell;
}

unsigned int MB_LayerWorld::numberOfCellsInTableView(CCTableView *table)
{
    return m_nTypes.size()+2;
}
