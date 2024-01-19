//
//  MB_LayerSweep.cpp
//  ProjectMB
//
//  Create by chk on 8/10/2014.
//
//
#include "MB_LayerSweep.h"
#include "MB_NodeItemBook.h"
#include "MB_LayerChapterWnd.h"
MB_LayerSweep * MB_LayerSweep::create(p_reward *pReward,uint16_t length){
    
    MB_LayerSweep *ptr = new MB_LayerSweep();
    if(ptr && ptr->init(pReward,length)){
        
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}

std::string MB_LayerSweep::strCurDungeonName = "";
bool MB_LayerSweep::init(p_reward *pReward,uint16_t length)
{
    if( !MB_ResWindow::init())
    {
        return false;
    }
    
    CCNode* pNode = loadResource("res/Sweep_layer.ccbi");
    if(pNode)
	{
        addChild(NSGameHelper::createDisableTouchLayer());
		addChild(pNode);
        m_pReward = pReward;
        m_nRewardLength = length;
        
        m_pOver->setVisible(false);
        
        m_pProcessLabel->setString("0");
        char buff[10] = {0};
        sprintf(buff, "%d",m_nRewardLength);
        m_pProcessLabel2->setString(buff);
        
        m_pNameLabel->setString(strCurDungeonName.c_str());
        m_pCoinLabel->setString("0");
        m_pExpLabel->setString("0");
        
        m_pScrollView = CCScrollView::create(m_pNodeContainer->getContentSize());
        m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
        m_pNodeContainer->addChild(m_pScrollView);
        
        this->schedule(schedule_selector(MB_LayerSweep::showOver), 1.0f, m_nRewardLength, 1.0f);
        
        
        
		return true;
	}
	return false;
}
MB_LayerSweep::MB_LayerSweep()
{
    m_pOver	 = NULL;
    m_pNameLabel	 = NULL;
    m_pCoinLabel	 = NULL;
    m_pExpLabel	 = NULL;
    m_pNodeContainer	 = NULL;
    m_pProcessLabel = NULL;
    m_pProcessLabel2 = NULL;
    m_pReward = NULL;
    m_pScrollView = NULL;
    m_n = 0;
    m_nCoin = 0;
    m_nExp = 0;
    
    m_pRewards = new  CCArray();
    MB_LayerRoleInfoHeader::setMenuEnable(false,"MB_LayerSweep");
    
}
MB_LayerSweep::~MB_LayerSweep()
{
    CC_SAFE_RELEASE_NULL(m_pOver);
    CC_SAFE_RELEASE_NULL(m_pNameLabel);
    CC_SAFE_RELEASE_NULL(m_pCoinLabel);
    CC_SAFE_RELEASE_NULL(m_pExpLabel);
    CC_SAFE_RELEASE_NULL(m_pNodeContainer);
    CC_SAFE_RELEASE_NULL(m_pRewards);
    MB_LayerRoleInfoHeader::setMenuEnable(true,"MB_LayerSweep");
    
}
void MB_LayerSweep::onResetWnd()
{
    m_pScrollView->getContainer()->removeAllChildren();
    RewardTempleteValue* pTemp = NULL;
    MB_NodeRewardItem* pItem = NULL;
    
    CCSize cellSize = CCSizeZero;
    CCARRAY_FOREACH_4TYPE(m_pRewards, RewardTempleteValue*, pTemp)
    {
        if (pTemp)
        {
            if (pTemp->getType() == kRewardValueTypePet)
            {
                pItem = MB_NodeRewardPet::create(pTemp->getValueID(),pTemp->getNumber(),false);
            }
            else
            {
                pItem = MB_NodeRewardItem::create(pTemp->getValueID(),pTemp->getNumber(),false);
            }
            if (pItem != NULL)
            {
                m_pScrollView->getContainer()->addChild(pItem);
                cellSize = pItem->getSize();
            }
        }
    }

    if(m_pRewards->count())
    {
        int nH = m_pScrollView->getContainer()->getChildrenCount() / 3.0f + 0.5f;
        float fH = nH * cellSize.height - cellSize.height/2;
        
        int nIndex = 0;
        CCARRAY_FOREACH_4TYPE(m_pScrollView->getContainer()->getChildren(), MB_NodeRewardItem*, pItem)
        {
            pItem->setPosition(nIndex%3 * cellSize.width + cellSize.width/2 , fH - int(nIndex/3.0f) * cellSize.height);
            
            ++nIndex;
        }
        
        m_pScrollView->setContentSize(CCSizeMake(m_pScrollView->getViewSize().width, nH * pItem->getSize().height ));
        m_pScrollView->setContentOffset(ccp(0,m_pScrollView->getViewSize().height - nH * cellSize.height));
    }
}

void MB_LayerSweep::onExit()
{
    this->unschedule(schedule_selector(MB_LayerSweep::showOver));
    MB_ResWindow::onExit();
}

void MB_LayerSweep::addReward(RewardTempleteValue* p)
{
    RewardTempleteValue* obj = NULL;
    CCARRAY_FOREACH_4TYPE(m_pRewards, RewardTempleteValue*, obj)
    {
        if(obj->getValueID() == p->getValueID() && obj->getNumber() > 0)
        {
            obj->setNumber(obj->getNumber() + p->getNumber());
            return;
        }
    }
    m_pRewards->addObject(p);
}



void  MB_LayerSweep::showOver(float)
{
    if(m_n < m_nRewardLength)
    {
        m_nCoin += m_pReward[m_n].coin;
        m_nExp += m_pReward[m_n].roleExp;
        
        char buff[50] = {0};
        sprintf(buff, "%d",m_n+1);
        m_pProcessLabel->setString(buff);
        
        sprintf(buff, "%d",m_nCoin);
        m_pCoinLabel->setString(buff);
        
        sprintf(buff, "%d",m_nExp);
        m_pExpLabel->setString(buff);
        
        
        //奖励
        p_item_view *item = m_pReward[m_n].item;
        while ( item!=NULL)
        {
            if(item->itemNum>0)
            {
                RewardTempleteValue* pValue = new RewardTempleteValue;
                
                pValue->setType(1);
                pValue->setValueID(item->itemTypeId);
                pValue->setNumber(item->itemNum);
                
                addReward(pValue);
                CC_SAFE_RELEASE_NULL(pValue);
            }
            else
            {
                RewardTempleteValue* pValue = new RewardTempleteValue;
                
                pValue->setType(2);
                pValue->setValueID(item->itemTypeId);
                pValue->setNumber(item->itemNum);
                addReward(pValue);
                CC_SAFE_RELEASE_NULL(pValue);
            }
            item = item->next;
        }
        if(m_pRewards->count())
        {
            onResetWnd();
        }
    }
    
    if(m_n == m_nRewardLength - 1)
    {
        m_pOver->setVisible(true);
        if(MB_RoleData::getInstance()->getEnergy() <= 0)
        {
            m_pOver->setString("体力不足，扫荡结束");
        }
        else if(m_nRewardLength < 10)
        {
            char databuf[50];
            sprintf(databuf, "此关卡已达到今日远征上限.");
            m_pOver->setString(databuf);
        }
        
        checkSweepLevelUp();
        
    }
    ++m_n;
}

void MB_LayerSweep::setBeforeSweepRoleInfo(int nPreRoleLv,int nPreDis,int nPreEnergy)
{
    m_nPreValue[0] = nPreRoleLv;
    m_nPreValue[1] = nPreDis;
    m_nPreValue[2] = nPreEnergy - m_nRewardLength * 2;
}

void MB_LayerSweep::checkSweepLevelUp()
{
    if(m_nPreValue[0] < MB_RoleData::getInstance()->getLevel())
    {
        MB_LayerRoleLevelUp *pLayer = MB_LayerRoleLevelUp::create(m_nPreValue[0], m_nPreValue[1], m_nPreValue[2]);
        CCDirector::sharedDirector()->getRunningScene()->addChild(pLayer,Z_ORDER_SWEEP);
    }
}

bool MB_LayerSweep::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pOver",CCLabelTTF*,m_pOver);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNameLabel",CCLabelTTF*,m_pNameLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pCoinLabel",CCLabelBMFont*,m_pCoinLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pExpLabel",CCLabelBMFont*,m_pExpLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeContainer",CCNode*,m_pNodeContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pProcessLabel",CCLabelBMFont*,m_pProcessLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pProcessLabel2",CCLabelBMFont*,m_pProcessLabel2);
    
	return false;
}
SEL_MenuHandler MB_LayerSweep::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerSweep::onCloseClick);
	return NULL;
}
SEL_CCControlHandler MB_LayerSweep::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
void MB_LayerSweep::onCloseClick(CCObject* pSender)
{
    layerChapterWnd->resetSweep();
    checkSweepLevelUp();
    popWindow();
}
