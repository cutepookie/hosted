//
//  MB_NodeSignItemView.cpp
//  ProjectMB
//
//  Create by ChenHongkun on 17/11/2014.
//
//
#include "MB_NodeSignItemView.h"
#include "MB_NodeItemBook.h"
#include "MB_LocalProto.h"
#include "MB_ItemData.h"
#include "MB_LayerItemDetail.h"
MB_NodeSignItemView::MB_NodeSignItemView()
{
    m_pLabelDay = NULL;
    m_pNodeSize = NULL;
    m_pNodeItem = NULL;
    m_pTodayBg = NULL;
}
MB_NodeSignItemView::~MB_NodeSignItemView()
{
    CC_SAFE_RELEASE_NULL(m_pLabelDay);
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(m_pNodeItem);
    CC_SAFE_RELEASE_NULL(m_pTodayBg);
    
}

MB_NodeSignItemView* MB_NodeSignItemView::create(CCArray* pReward,int n)
{
    MB_NodeSignItemView* pItem = new MB_NodeSignItemView();
    if(pItem && pItem->init(pReward,n))
    {
        
        pItem->autorelease();
        return pItem;
    }
    
    CC_SAFE_RELEASE_NULL(pItem);
    return NULL;
}

bool MB_NodeSignItemView::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelDay",CCLabelBMFont*,m_pLabelDay);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize",CCNode*,m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeItem",CCNode*,m_pNodeItem);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTodayBg",CCNode*,m_pTodayBg);
    
    return false;
}

void MB_NodeSignItemView::onClicked(MB_NodeItem* pItem)
{
    MB_ResWindow* layerDetail = MB_LayerItemDetail::createByType(pItem->getItemType());
    MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
    if (pScene)
    {
        pScene->addChild(layerDetail,Z_ORDER_Detail);
    }else{
        CCDirector::sharedDirector()->getRunningScene()->addChild(layerDetail, Z_ORDER_OUTSHOW);
    }
}

bool MB_NodeSignItemView::init(CCArray* pReward,int n)
{
    CCNode* pNode = loadResource("res/item_node_view.ccbi");
    if(pNode)
    {
        addChild(pNode);
        
        RewardTempleteValue* pObj = NULL;
        int indxe = 0;
        CCSize size = CCSizeMake(150, 190);
        if(pReward)
        {
            CCARRAY_FOREACH_4TYPE(pReward,RewardTempleteValue*,pObj)
            {
                if(pObj->getType() == 1)
                {
                    MB_NodeItem* pItem = MB_NodeItem::create(pObj->getValueID());
                    pItem->setNum(pObj->getNumber());
                    pItem->showNameCount(true);
                    pItem->setDelegate(this);
                    m_pNodeItem->addChild(pItem);
                    pItem->m_pItemMenu->setTouchPriority(99);
                    pItem->setPosition(indxe * size.width + size.width/2,size.height/2);
                }
                else
                {
                    MB_NodePet * pPet = MB_NodePet::create(pObj->getValueID());
                    m_pNodeItem->addChild(pPet);
                    pPet->showName(true);
                    pPet->setPosition(indxe * size.width + size.width/2,size.height/2-8);
                }
                
                ++indxe;
            }
        }
        
        if(n==0)
        {
            m_pLabelDay->setString("今");
        }else if(n==1)
        {
            m_pLabelDay->setString("明");
        }
        else{
            char buff[50] = {0};
            sprintf(buff, "%d",n+1);
            m_pLabelDay->setString(buff);
        }
        
        setContentSize(m_pNodeSize->getContentSize());
        
        if (n==0) {
            m_pTodayBg->setVisible(true);
        }
        return true;
    }
    return false;
}

void MB_NodeSignItemView::onResetWnd()
{
    
}

CCSize MB_NodeSignItemView::getNodeSize()
{
    static CCSize sz = CCSize(-1,0);
    if (sz.width < 0)
    {
        MB_NodeSignItemView* pNode = MB_NodeSignItemView::create(NULL,0);
        if (pNode)
        {
            sz = pNode->getContentSize();
        }
    }
    return sz;
}
