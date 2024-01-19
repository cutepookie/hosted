//
//  MB_LayerReportTop8.cpp
//  ProjectTK
//
//  Created by crimoon00007 on 13-12-25.
//
//

#include "MB_LayerReportTop8.h"

static const uint16_t max_report = 10;

MB_LyaerReportTop8::MB_LyaerReportTop8()
{
    m_pLayout = NULL;
    m_pScrollView = NULL;
    m_pBoxLayer = NULL;
}

MB_LyaerReportTop8::~MB_LyaerReportTop8()
{
    CC_SAFE_RELEASE(m_pLayout);
    CC_SAFE_RELEASE(m_pBoxLayer);
}

static void convertNodeSpace(CCNode* node)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCPoint posheight = ccp(0,size.height- 480);
    posheight = node->getParent()->convertToNodeSpace(posheight);
    node->setContentSize(CCSize(node->getContentSize().width,node->getContentSize().height + posheight.y/node->getScaleY()));
    node->setPosition(ccp(node->getPosition().x, node->getPosition().y  + 0.5*(node->getAnchorPoint().y -1)*posheight.y/node->getScaleY()));
}


bool MB_LyaerReportTop8::init()
{
    MB_ResWindow::init();

    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);

    CCNode* pMain = pCCBReader->readNodeGraphFromFile("res/pvp_node_list.ccbi",this);
    if (!pMain)
    {
        CC_SAFE_RELEASE(pCCBReader);
        return false;
    }

    addChild(pMain);

    //convertNodeSpace(m_pLayout);
    CC_SAFE_RELEASE(pCCBReader);

    return true;
}

bool MB_LyaerReportTop8::initScrollView(uint16_t iBoxCount)
{
    if (m_pLayout->getChildrenCount()!=0)
    {
        m_pLayout->removeAllChildren();
    }

    MB_NodeReportBox* pBox = NULL;
    CCSize sz;
    CCPoint pos;

    m_pBoxLayer = CCLayer::create();
    m_pBoxLayer->retain();


    m_pScrollView = CCScrollView::create(m_pLayout->getContentSize());

    m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
    bool bSetLayoutSize = false;
    for (uint16_t i = 0; i < iBoxCount; ++i)
    {
        pBox = MB_NodeReportBox::create();
        if (pBox)
        {
            pBox->getNodeSize(sz);
            if (!bSetLayoutSize)
            {
                CCSize csz;
                csz.width = sz.width;
                csz.height = sz.height * iBoxCount;
                bSetLayoutSize = true;
                m_pBoxLayer->setContentSize(csz);
                pos.x = sz.width/2.0;
            }

            pos.y = sz.height*(iBoxCount-1-(i)+0.5f);
            pBox->setTag(i);
            pBox->setPosition(pos);
            pBox->visableBeatBackMenu(false);
            pBox->setVisible(false);
            m_pBoxLayer->addChild(pBox);
        }
    }
    m_pScrollView->setContainer(m_pBoxLayer);
    m_pLayout->addChild(m_pScrollView);

    m_pScrollView->setContentOffset(ccp(0,m_pScrollView->getViewSize().height - (iBoxCount) * sz.height));

    return true;
}
void MB_LyaerReportTop8::setScrollSize(const CCSize& sz)
{
    if (m_pScrollView)
    {
        m_pScrollView->setViewSize(sz);
        m_pScrollView->setContentOffset(ccp(0,m_pScrollView->getViewSize().height-m_pScrollView->getContainer()->getContentSize().height));
    }
}
/*
message		recvpvp_get_first_eight_replays[id=10807]{
	repeated	p_pvp_replay_info		infoList		=1;
}
 */
void MB_LyaerReportTop8::setData(MB_MsgBuffer *pResultBuffer)
{
    CC_ASSERT(pResultBuffer!=NULL);
    uint16_t count = 0;

    pResultBuffer->readU16(&count);

    count = count > max_report ? max_report : count;

    initScrollView(count);

    uint16_t i = 0;
    for (; i<count; ++i)
    {
        installSingleData(pResultBuffer,i);
    }

    //MB_NodeReportBox* pBox = NULL;
    //for (;i<max_report; ++i)
    //{
    //    pBox = dynamic_cast<MB_NodeReportBox*>(m_pBoxLayer->getChildByTag(i));
    //    if (pBox!=NULL)
     //   {
     //       pBox->setVisible(false);
     //   }
    //}
}

/*
 message		p_pvp_replay_info[id=10808]{
 required	string				attackerName		=1;
 required	string				defenderName		=2;
 required	int16				attackerNewRank		=3;//决斗者新排名（一定是上升~~打赢了才显示）
 required	int16				defenderNewRank		=4;//被决斗者新排名
 required	int64				replayUID			=5;
 required	int32				time				=6;//战斗发生的时间戳
 }
 */
bool MB_LyaerReportTop8::installSingleData(MB_MsgBuffer* pSingleData,uint16_t index)
{
    MB_NodeReportBox* pBox = dynamic_cast<MB_NodeReportBox*>(m_pBoxLayer->getChildByTag(index));
    if (pBox==NULL)
    {
        return false;
    }
    else
    {
        p_pvp_replay_info info;
        char* pReadString = NULL;
        pReadString = pSingleData->ReadString();
        if(pReadString != NULL ) {
       
            info.attackerName = pReadString;
        
        }else {
        
            info.attackerName = "";
        }
        CC_SAFE_FREE(pReadString);
        pReadString = pSingleData->ReadString();
        if(pReadString != NULL){
        
            info.defenderName = pReadString;
        }else {
           info.defenderName = "";
        }
        CC_SAFE_FREE(pReadString);
        info.attackerNewRank = 0;
        info.defenderNewRank = 0;
        info.replayUid       = 0;
        info.time            = 0;

        pSingleData->readU16(&info.attackerNewRank);
        pSingleData->readU16(&info.defenderNewRank);
        pSingleData->readU64(&info.replayUid);
        pSingleData->readU32(&info.time);

        pBox->setReportInfo(info);
        
    }

    return true;
}

bool MB_LyaerReportTop8::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"layout",CCNode*,m_pLayout);
    return false;
}

SEL_MenuHandler MB_LyaerReportTop8::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler MB_LyaerReportTop8::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}