

#include "MB_LoginNotice.h"
#include "MB_PublicNoticeData.h"

#include "MB_NodeNoticeActive.h"
#include "MB_NodeNoticePic.h"
//---------------------------------------------//
//======    构造|析构
//---------------------------------------------//
MB_LoginNotice::MB_LoginNotice()
{
    tanchuTimes = 1;
    m_pContent          = NULL;
    MB_TutorialMgr::getInstance()->SetModelDilogState("MB_LoginNotice", true);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(MB_LoginNotice::refresh), "notice_received", this);
}

MB_LoginNotice::~MB_LoginNotice()
{
    CC_SAFE_RELEASE(m_pContent);
    MB_TutorialMgr::getInstance()->SetModelDilogState("MB_LoginNotice", false);
    MB_LayerRoleInfoHeader::setMenuEnable(true,"MB_LoginNotice");
    
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,"notice_received");
}
bool MB_LoginNotice::init()
{
    MB_ResWindow::init();
    this->addChild(NSGameHelper::createDisableTouchLayer());
    pRootNode = loadResource("res/message_layer_announcement.ccbi");
    this->addChild(pRootNode);
    
    onInitDidFinish();
    
    lc = CCLayerColor::create(ccc4(0,0,0,150), 640, 1136);
    addChild(lc,-1);
    
    runEnterAction();
    return true;
}
void MB_LoginNotice::onInitDidFinish()
{
    onResetWnd();
}

//---------------------------------------------//
//======    事件|成员 指派
//---------------------------------------------//
bool MB_LoginNotice::onAssignCCBMemberVariable(CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Content", CCNode*, m_pContent);
    return false;
}

SEL_CCControlHandler MB_LoginNotice::onResolveCCBCCControlSelector(CCObject * pTarget,const char* pSelectorName)
{
    return NULL;
}
cocos2d::SEL_MenuHandler MB_LoginNotice::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LoginNotice::onCloseClick)
    return NULL;
}

void MB_LoginNotice::onCloseClick(CCObject* pSender)
{
    if (tanchuTimes==0) {
        removeFromParent();
        return;
    }

    int tempIndex = 0;
    CCNode* layer = pScrollview->getContainer();
    layer->removeAllChildren();
    //活动入口
    //活动排序列表
    CCArray* m_pActivaty = MB_MoneyEevntMgr::getInstance()->getEventList();
    CCArray* m_pNoticeActivaty = MB_MoneyEevntMgr::getInstance()->getNativeEventList();
    int maxActivatyNum = m_pActivaty->count() + m_pNoticeActivaty->count();
    MB_MoneyEevntData * data = NULL;
    bool bHasActivaty = false;
    std::vector<uint32_t> idList = MB_MoneyEevntMgr::getInstance()->getActivatyIDList();
    if (idList.size() > 0)
    {
        //将在排序列表中的活动添加进去
        for(int i = 0;i < idList.size();i++)
        {
            bHasActivaty = false;
            CCARRAY_FOREACH_4TYPE(m_pActivaty, MB_MoneyEevntData *, data)
            {
                if (data->getActivityID() == idList[i])
                {
                    MB_NodeNoticeActive* node = MB_NodeNoticeActive::create();
                    node->setData(data);
                    if (node != NULL)
                    {
                        layer->addChild(node);
                        tempIndex++;
                    }
                    bHasActivaty = true;
                }
                
            }
            
            if (!bHasActivaty)
            {
                CCARRAY_FOREACH_4TYPE(m_pNoticeActivaty, MB_MoneyEevntData *, data)
                {
                    if (data->getActivityID() == idList[i])
                    {
                        MB_NodeNoticeActive* node = MB_NodeNoticeActive::create();
                        node->setData(data);
                        if (node != NULL)
                        {
                            layer->addChild(node);
                            tempIndex++;
                        }
                        bHasActivaty = true;
                    }
                }
            }
        }
        
        //将不在排序列表中的活动添加进去
        if(tempIndex < maxActivatyNum)
        {
            CCARRAY_FOREACH_4TYPE(m_pActivaty, MB_MoneyEevntData *, data)
            {
                bool bHasActivaty = false;
                for(int i = 0;i < idList.size();i++)
                {
                    if (data->getActivityID() == idList[i])
                    {
                        bHasActivaty = true;
                    }
                }
                if (!bHasActivaty)
                {
                    MB_NodeNoticeActive* node = MB_NodeNoticeActive::create();
                    node->setData(data);
                    if (node != NULL)
                    {
                        layer->addChild(node);
                        tempIndex++;
                    }
                }
            }
            CCARRAY_FOREACH_4TYPE(m_pNoticeActivaty, MB_MoneyEevntData *, data)
            {
                bool bHasActivaty = false;
                for(int i = 0;i < idList.size();i++)
                {
                    if (data->getActivityID() == idList[i])
                    {
                        bHasActivaty = true;
                    }
                }
                if (!bHasActivaty)
                {
                    MB_NodeNoticeActive* node = MB_NodeNoticeActive::create();
                    node->setData(data);
                    if (node != NULL)
                    {
                        layer->addChild(node);
                        tempIndex++;
                    }
                }
            }
        }
    } else
    {
        CCARRAY_FOREACH_4TYPE(m_pActivaty, MB_MoneyEevntData *, data)
        {
            MB_NodeNoticeActive* node = MB_NodeNoticeActive::create();
            node->setData(data);
            if (node != NULL)
            {
                layer->addChild(node);
                tempIndex++;
            }
        }
        
        CCARRAY_FOREACH_4TYPE(m_pNoticeActivaty, MB_MoneyEevntData *, data)
        {
            MB_NodeNoticeActive* node = MB_NodeNoticeActive::create();
            node->setData(data);
            if (node != NULL)
            {
                layer->addChild(node);
                tempIndex++;
            }
        }
    }
    
    if (tempIndex>0) {
        tanchuTimes--;
        runEnterAction();
        
        
        //位置调整
        CCArray* childers = layer->getChildren();
        CCNode* node = NULL;
        int height = 0;
        if (childers) {
            CCARRAY_FOREACH_4TYPE(childers,CCNode*,node)
            {
                CCSize size = node->getContentSize();
                height += size.height;
            }
        }
        pScrollview->setContentSize(CCSize(m_pContent->getContentSize().width,height+15));
        pScrollview->setContentOffset(CCPoint(0,m_pContent->getContentSize().height - height-15));
        
        CCARRAY_FOREACH_4TYPE(childers,CCNode*,node)
        {
            CCSize size = node->getContentSize();
            node->setAnchorPoint(ccp(0.5,0.5));
            node->setPosition(m_pContent->getContentSize().width/2,height);
            height -= size.height;
        }

    }else
    {
        removeFromParent();
    }
}
void MB_LoginNotice::setClose()
{
    onCloseClick(NULL);
}
void MB_LoginNotice::runEnterAction()
{
    lc->setOpacity(0);
    lc->runAction(CCFadeTo::create(.15f,150));
    NSGameHelper::setAllOpacity(pRootNode, 0);
    NSGameHelper::runOptActionIn(pRootNode, .15f, true);
    pRootNode->setPositionY(pRootNode->getPositionY()+50);
    pRootNode->runAction(CCMoveBy::create(.15f, ccp(0,-50)));
}
//---------------------------------------------//
//======    界面刷新
//---------------------------------------------//
void MB_LoginNotice::onResetWnd(void)
{
    m_pContent->removeAllChildren();
    pScrollview = CCScrollView::create(m_pContent->getContentSize());
    pScrollview->setDirection(kCCScrollViewDirectionVertical);
    m_pContent->addChild(pScrollview);
    CCLayer* layer = CCLayer::create();
    //公告图片
    
    //公告内容
    if (PublicNoticeData->getContentNotice().length() > 0)
    {
        MB_NodeNotice* node = MB_NodeNotice::create();
        int pic_id = MB_PublicNoticeData::getInstance()->getNoticePicID();
        if (pic_id != 0)
        {
            MB_NodeNoticePic* nodePic = MB_NodeNoticePic::create();
            if (nodePic && nodePic->setPic(pic_id))
            {
                node->setData(const_cast<char*>(PublicNoticeData->getContentNotice().c_str()),nodePic);
            }
        }else
        {
            node->setData(const_cast<char*>(PublicNoticeData->getContentNotice().c_str()));
        }

        layer->addChild(node);
    }
   
    //位置调整
    CCArray* childers = layer->getChildren();
    CCNode* node = NULL;
    int height = 0;
    if (childers) {
        CCARRAY_FOREACH_4TYPE(childers,CCNode*,node)
        {
            CCSize size = node->getContentSize();
            height += size.height;
        }
    }
    pScrollview->setContainer(layer);
    pScrollview->setContentSize(CCSize(m_pContent->getContentSize().width,height+15));
    pScrollview->setContentOffset(CCPoint(0,m_pContent->getContentSize().height - height-15));
    
    CCARRAY_FOREACH_4TYPE(childers,CCNode*,node)
    {
        CCSize size = node->getContentSize();
        node->setAnchorPoint(ccp(0.5,0.5));
        node->setPosition(m_pContent->getContentSize().width/2,height);
        height -= size.height;
    }
}

void MB_LoginNotice::refresh(CCObject*)
{
    dirty();
}
