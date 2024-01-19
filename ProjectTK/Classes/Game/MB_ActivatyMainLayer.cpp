//
//  MB_ActivatyMainLayer.cpp
//  ProjectPM
//
//  Created by chk on 14-4-30.
//
//

#include "MB_ActivatyMainLayer.h"
#include "MB_FunctionMgr.h"
#include "MB_NodeActivatyEntry.h"
#include "MB_NodeSubActivatyEntry.h"
#include "MB_FunctionMainWnd.h"
#include "MB_ActivatyMgr.h"
#include "MB_MoneyEevntData.h"
#include "MB_ConfigActivatyInterface.h"
#include "MB_FunctionEntery2ActivatyEntery.h"
#include "MB_FestivalProtocol.h"
using namespace NSGameFunction;
#define ACT_PERLINENUM 3
MB_ActivatyMainLayer::MB_ActivatyMainLayer():
m_pNodeNaveigation(NULL),
m_pNodeActivatyContainer(NULL),
m_pScollerView(NULL)
{
    SOCKET_MSG_REGIST(SC_ACTIVITY_GET_LIST, MB_ActivatyMainLayer);
    SOCKET_MSG_REGIST(SC_ACTIVITY_INFO,MB_ActivatyMainLayer);
    SOCKET_MSG_REGIST(RECV_FESTIVAL_INFO, MB_ActivatyMainLayer);
    m_bShowRoleInfoPanel = true;
    m_bShowEXP = true;
    m_nMoveSpeed = 0;
    m_nShowIndex = 0;
}

bool MB_ActivatyMainLayer::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = pDataSource;
    return true;
}

MB_ActivatyMainLayer::~MB_ActivatyMainLayer()
{
    MB_ActivatyMgr::getInstance()->reset();
    MB_ActivatyMgr::getInstance()->setScrollView(NULL);
    CC_SAFE_RELEASE_NULL(m_pNodeNaveigation);
    CC_SAFE_RELEASE_NULL(m_pNodeActivatyContainer);
    
    SOCKET_MSG_UNREGIST(SC_ACTIVITY_GET_LIST);
    SOCKET_MSG_UNREGIST(SC_ACTIVITY_INFO);
    SOCKET_MSG_UNREGIST(RECV_FESTIVAL_INFO);
}


MB_ActivatyMainLayer * MB_ActivatyMainLayer::create()
{
    MB_ActivatyMainLayer *pRet = new MB_ActivatyMainLayer();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
    }
    return NULL;
}

bool MB_ActivatyMainLayer::init()
{
    addChild(NSGameHelper::createDisableTouchLayer());// 防止点穿
    MB_ActivatyMgr::getInstance()->setLastLockedTag(-1);
    CCNode* pNode = loadResource("res/formation_layer_event.ccbi");
    if (pNode)addChild(pNode);
    
    m_pScollerView = CCScrollView::create(m_pNodeNaveigation->getContentSize());
    m_pScollerView->setBounceable(false);
    m_pScollerView ->setDirection(kCCScrollViewDirectionHorizontal);
    m_pNodeNaveigation->addChild(m_pScollerView);
    
    m_pScollerView->setDelegate(this);
    
    initFunctions();
    onResetWnd();
    return true;
}


void MB_ActivatyMainLayer::onResetWnd()
{
}

bool MB_ActivatyMainLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeNaveigation", CCNode*, m_pNodeNaveigation);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeActivatyContainer", CCNode*, m_pNodeActivatyContainer);
    return false;
}

SEL_MenuHandler MB_ActivatyMainLayer::MB_ActivatyMainLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_ActivatyMainLayer::onCloseClick);
    return NULL;
}
void MB_ActivatyMainLayer::onCloseClick(CCObject*)
{
    removeFromParent();
}
SEL_CCControlHandler MB_ActivatyMainLayer::MB_ActivatyMainLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    
    return NULL;
}


void MB_ActivatyMainLayer::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    
    //將socket數据读取到序列化結构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议號
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg)
    {
        case RECV_FESTIVAL_INFO:
//            initFunctions();
            MB_FunctionMgr::getInstance()->goFunction(kFunctionActivaty, this);
            break;
        case SC_ACTIVITY_GET_LIST:
            if(MB_MoneyEevntMgr::getInstance()->gethasChange())
            {
                initFunctions();
            }
            break;
        case SC_ACTIVITY_INFO:
        {
            recvactivity_info(recvPacket);
        }
            break;
    }
}

bool MB_ActivatyMainLayer::recvactivity_info(MB_MsgBuffer* recvPacket)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    uint16_t data16;
    recvPacket->readU16(&data16);
    
    NSGameFunction::CCFunctionInterface* pInterface = NULL;
    MB_FunctionMgr::getInstance()->queryFunctionByType(kActivatyConfig, &pInterface);
    if(pInterface)
    {
        MB_ConfigActivatyInterface* pConfigInterface = dynamic_cast<MB_ConfigActivatyInterface*>(pInterface);
        if(pConfigInterface)
        {
            setCurActivaty(pConfigInterface->createFunctionDialog(data16));
        }
    }
    return true;
}


void MB_ActivatyMainLayer::setCurActivaty(MB_ResWindow* player)
{
    if(player)
    {
        m_pNodeActivatyContainer->removeAllChildrenWithCleanup(true);
        m_pNodeActivatyContainer->addChild(player);
    }
}

bool MB_ActivatyMainLayer::initFunctions()
{
    m_pScollerView->getContainer()->removeAllChildren();
    
    CCFunctionInterface* pInterface = NULL;
    
    int nPosX = m_pNodeNaveigation->getContentSize().width*0.5;
    int nPosY = m_pNodeNaveigation->getContentSize().height/2;
    
    int count = 0;
    
    //配置活動
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kActivatyConfig, &pInterface))
    {
        MB_ConfigActivatyInterface* pCongigActionvatyInterface = (MB_ConfigActivatyInterface*)pInterface;
        MB_MoneyEevntData* pTempData = NULL;
        MB_NodeSubActivatyEntry* pWnd = NULL;
        
        //本地活動
        std::vector<NSGameFunction::CCFunctionInterface*> v = MB_MoneyEevntMgr::getInstance()->getFunctionActivity();
        size_t sz = v.size();
        //伺服器活動
        CCArray* pArray = MB_MoneyEevntMgr::getInstance()->getEventList();

        
        //活動排序列表
        std::vector<uint32_t> idList = MB_MoneyEevntMgr::getInstance()->getActivatyIDList();
        if (idList.size() > 0)  //排序
        {
            int maxNumActivaty = sz + pArray->count();
            bool hasActivaty = false;
            
            //按照列表顺序添加活動
            for(int i = 0;i < idList.size();i++)
            {
                hasActivaty = false;
                for (size_t s=0; s<sz; ++s)
                {
                    MB_FunctionEntery2ActivatyEntery* pWnd = dynamic_cast<MB_FunctionEntery2ActivatyEntery*>(v[s]->createEntryDialog());
                    {
                        if(pWnd && pWnd->getActivityID() == idList[i])
                        {
                            m_pScollerView->addChild(pWnd);
                            
                            pWnd->setTag(pWnd->getActivityID());
                            pWnd->setPosition(nPosX,nPosY);
                            pWnd->setMainWnd(this);
                            nPosX += m_pNodeNaveigation->getContentSize().width/ACT_PERLINENUM;
                            ++count;
                            hasActivaty = true;
                        }
                    }
                }
                if (!hasActivaty)
                {
                    CCARRAY_FOREACH_4TYPE(pArray, MB_MoneyEevntData*, pTempData)
                    {
                        if(pTempData && pTempData->getActivityID() == idList[i])
                        {
                            {
                                pWnd = dynamic_cast<MB_NodeSubActivatyEntry*>(pCongigActionvatyInterface->createEntryDialog(pTempData->getActivityID()));
                                if(pWnd)
                                {
                                    m_pScollerView->addChild(pWnd);
                                    
                                    pWnd->setTag(pTempData->getActivityID());
                                    pWnd->setPosition(nPosX,nPosY);
                                    pWnd->setMainWnd(this);
                                    nPosX += m_pNodeNaveigation->getContentSize().width/ACT_PERLINENUM;
                                    ++count;
                                }
                            }
                        }
                    }
                }
            }
            
            //將不在排序列表中的活動添加進去
            if(count < maxNumActivaty)
            {
                for (size_t s=0; s<sz; ++s)
                {
                    MB_FunctionEntery2ActivatyEntery* pWnd = dynamic_cast<MB_FunctionEntery2ActivatyEntery*>(v[s]->createEntryDialog());
                    {
                        bool bHasActivaty = false;
                        for(int i = 0;i < idList.size();i++)
                        {
                        
                            if(pWnd && pWnd->getActivityID() == idList[i])
                            {
                                bHasActivaty = true;
                            }
                        }
                        if (!bHasActivaty)
                        {
                            m_pScollerView->addChild(pWnd);
                            pWnd->setTag(pWnd->getActivityID());
                            pWnd->setPosition(nPosX,nPosY);
                            pWnd->setMainWnd(this);
                            nPosX += m_pNodeNaveigation->getContentSize().width/ACT_PERLINENUM;
                            ++count;
                        }
   
                    }
                }
                CCARRAY_FOREACH_4TYPE(pArray, MB_MoneyEevntData*, pTempData)
                {
                    if (pTempData)
                    {
                        bool bHasActivaty = false;
                        for(int i = 0;i < idList.size();i++)
                        {
                            if(pTempData->getActivityID() == idList[i])
                            {
                                bHasActivaty = true;
                            }
                        }
                        if (!bHasActivaty)
                        {
                            pWnd = dynamic_cast<MB_NodeSubActivatyEntry*>(pCongigActionvatyInterface->createEntryDialog(pTempData->getActivityID()));
                            if(pWnd)
                            {
                                m_pScollerView->addChild(pWnd);
                                
                                pWnd->setTag(pTempData->getActivityID());
                                pWnd->setPosition(nPosX,nPosY);
                                pWnd->setMainWnd(this);
                                nPosX += m_pNodeNaveigation->getContentSize().width/ACT_PERLINENUM;
                                ++count;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            for (size_t s=0; s<sz; ++s)
            {
                MB_FunctionEntery2ActivatyEntery* pWnd = dynamic_cast<MB_FunctionEntery2ActivatyEntery*>(v[s]->createEntryDialog());
                {
                    if(pWnd)
                    {
                        m_pScollerView->addChild(pWnd);
                        
                        pWnd->setTag(pWnd->getActivityID());
                        pWnd->setPosition(nPosX,nPosY);
                        pWnd->setMainWnd(this);
                        nPosX += m_pNodeNaveigation->getContentSize().width/ACT_PERLINENUM;
                        ++count;
                    }
                }
            }
            
            
            CCARRAY_FOREACH_4TYPE(pArray, MB_MoneyEevntData*, pTempData)
            {
                if(pTempData)
                {
                    {
                        pWnd = dynamic_cast<MB_NodeSubActivatyEntry*>(pCongigActionvatyInterface->createEntryDialog(pTempData->getActivityID()));
                        if(pWnd)
                        {
                            m_pScollerView->addChild(pWnd);
                            
                            pWnd->setTag(pTempData->getActivityID());
                            pWnd->setPosition(nPosX,nPosY);
                            pWnd->setMainWnd(this);
                            nPosX += m_pNodeNaveigation->getContentSize().width/ACT_PERLINENUM;
                            ++count;
                        }
                    }
                }
            }

        }
        m_pScollerView->setContentSize(CCSize((count+2)*m_pNodeNaveigation->getContentSize().width/ACT_PERLINENUM,m_pNodeNaveigation->getContentSize().height));
    }

    
    
    resetNodePos();
    return true;
}

void MB_ActivatyMainLayer::setShowActivatyID(int activatyID)
{
    movetoShow(activatyID);
    
    
    if (m_nShowIndex == activatyID && activatyID != 0)
    {
        return;
    }
    
    if (clickedActivatyIcon(activatyID))
    {
        return;
    }
    m_nMoveSpeed = .1f;
    CCArray* array = m_pScollerView->getContainer()->getChildren();
    if(array == NULL)
    {
        return;
    }
    if (array->count() <= 2 && array->count() > 0)
    {
        MB_NodeSubActivatyEntry* temp = dynamic_cast<MB_NodeSubActivatyEntry*>(array->objectAtIndex(0));
        if(temp)
        {
            setShowActivatyID(temp->getTag());
        }
    }
    else if(array->count() == 3)
    {
        MB_NodeSubActivatyEntry* temp = dynamic_cast<MB_NodeSubActivatyEntry*>(array->objectAtIndex(1));
        if(temp)
        {
            setShowActivatyID(temp->getTag());
        }
    }
    else if(array->count() > 3)
    {
        MB_NodeSubActivatyEntry* temp = dynamic_cast<MB_NodeSubActivatyEntry*>(array->objectAtIndex(2));
        if(temp)
        {
            setShowActivatyID(temp->getTag());
        }
    }
    
}

bool MB_ActivatyMainLayer::clickedActivatyIcon(int activatyID)
{
    MB_NodeSubActivatyEntry* node = NULL;
    CCArray* pArray = m_pScollerView->getContainer()->getChildren();
    
    CCARRAY_FOREACH_4TYPE(pArray, MB_NodeSubActivatyEntry*, node)
    {
        if (node->getTag() == activatyID)
        {
            if (m_nShowIndex != node->getTag())
            {
                node->onEntranceClicked(NULL);
                m_nShowIndex = activatyID;
                return true;
            }
        }
    }
    return false;
}
void MB_ActivatyMainLayer::movetoShow(int activatyID)
{
    if (activatyID == 0)
    {
        return;
    }
    CCNode* node = NULL;
    CCPoint p0 =ccp(-9999,-1);
    CCArray* pArray = m_pScollerView->getContainer()->getChildren();
    CCARRAY_FOREACH_4TYPE(pArray, CCNode*, node)
    {
        if (node->getTag() == activatyID)
        {
            p0.x = node->getPositionX();
        }
    }
    if (p0.x == -9999)
    {
        return;
    }
    int offset =m_pNodeNaveigation->getContentSize().width*0.5 - p0.x;
    m_pScollerView->getContainer()->stopAllActions();
    m_pScollerView->unschedule(schedule_selector(CCScrollView::deaccelerateScrolling));
    m_pScollerView->getContainer()->runAction(CCSequence::create(CCMoveTo::create(m_nMoveSpeed, ccp(offset,0)),
                                                                 CCCallFuncN::create(this,callfuncN_selector(MB_ActivatyMainLayer::whenMoveOver)),NULL));
 
    m_bMove = true;

}

void MB_ActivatyMainLayer::scrollViewDidScroll(CCScrollView* view)
{
    if (view->isTouchMoved () == false && !m_bMove) {
        m_pScollerView->getContainer()->stopAllActions();
        m_pScollerView->unschedule(schedule_selector(CCScrollView::deaccelerateScrolling));
        CCNode* node = NULL;
        
        float s = m_pNodeNaveigation->getContentSize().width*0.35;
        float s2 = m_pNodeNaveigation->getContentSize().width*0.65;
        CCPoint p1 = m_pNodeNaveigation->convertToWorldSpace(ccp(0,0));
        CCArray* pArray = m_pScollerView->getContainer()->getChildren();
        CCARRAY_FOREACH_4TYPE(pArray, CCNode*, node)
        {
            CCPoint p0 = node->convertToWorldSpace(ccp(0,0));
      
            int offset = p0.x - p1.x;
            if (offset >= s && offset <= s2)
            {
                setShowActivatyID(node->getTag());
                break;
            }
        }

    }
    resetNodePos();
}
void MB_ActivatyMainLayer::scrollViewDidZoom(CCScrollView* view)
{
    
}

void MB_ActivatyMainLayer::resetNodePos()
{
    CCNode* node = NULL;
    CCArray* pArray = m_pScollerView->getContainer()->getChildren();
    CCARRAY_FOREACH_4TYPE(pArray, CCNode*, node)
    {
        float s = m_pNodeNaveigation->getContentSize().width/2;

        CCPoint p0 = node->convertToWorldSpace(ccp(0,0));
        CCPoint p1 = m_pNodeNaveigation->convertToWorldSpace(ccp(0,0));
        int offset = p0.x - p1.x;
        float f = (offset>s? m_pNodeNaveigation->getContentSize().width-offset:offset)/s;
        node->setScale(f*0.5+0.5);
    }
}

void MB_ActivatyMainLayer::whenMoveOver()
{
    m_bMove = false;
    resetNodePos();
}
