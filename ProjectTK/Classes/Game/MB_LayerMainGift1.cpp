//
//  MB_LayerMainGift1.cpp
//  ProjectMB
//
//  Create by wenyong on 17/12/2014.
//
//
#include "MB_LayerMainGift1.h"
#include "MB_GiftsInterface.h"
#include "MB_FunctionModule.h"
#include "MB_LayerChatMain.h"
MB_LayerMainGift1::MB_LayerMainGift1()
{
    m_pContainer     = NULL;
    m_pInterface = NULL;
    m_pDataSource = NULL;
    m_pTableView = NULL;
    m_bShowRoleInfoPanel = false;
    m_nCurType = eGiftNone;
    SOCKET_MSG_REGIST(SC_DAILY_REWARD_GET, MB_LayerMainGift1);
    SOCKET_MSG_REGIST(SC_DAILY_REWARD_LIST, MB_LayerMainGift1);
    SOCKET_MSG_REGIST(SC_ROLE_UPDATE_LEVEL, MB_LayerMainGift1);
    MB_LayerChatMain::SetChatMainVisible(false, "MB_LayerMainGift1");
}
MB_LayerMainGift1::~MB_LayerMainGift1()
{
    CC_SAFE_RELEASE_NULL(m_pContainer);
    SOCKET_MSG_UNREGIST(SC_DAILY_REWARD_GET);
    SOCKET_MSG_UNREGIST(SC_DAILY_REWARD_LIST);
    SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_LEVEL);
}
void MB_LayerMainGift1::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    switch (nMsg) {
        case SC_DAILY_REWARD_GET:
            sc_daily_reward_get(pRecv);
            break;
        case SC_DAILY_REWARD_LIST:
        {
            CCPoint pt = m_pTableView->getContentOffset();
            onResetWnd();
            m_pTableView->setContentOffset(pt);
        }
            break;
        case SC_ROLE_UPDATE_LEVEL:
        {
            if (m_nCurType == eGiftLevel)
            {
                CCPoint pt = m_pTableView->getContentOffset();
                onResetWnd();
                m_pTableView->setContentOffset(pt);
            }
        }
            break;
        default:
            break;
    }
}
bool MB_LayerMainGift1::init()
{
    CCNode* pNode = loadResource("res/gift_layer_main1.ccbi");
    if(pNode)
    {
        addChild(pNode);
        NSGameHelper::adjustScrollNode(m_pContainer);
        go2Page(eGiftTime);
        return true;
    }
    return false;
}
void MB_LayerMainGift1::go2Page(EGiftType e)
{
    if(m_nCurType == e)
    {
        return;
    }
    m_nCurType = e;

    m_pDataSource = m_pInterface->getDataSourceByType(e);
    onResetWnd();
}



bool MB_LayerMainGift1::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pInterface = dynamic_cast<MB_GiftsInterface*>(pDataSource);
    return m_pInterface!=NULL;
}

void MB_LayerMainGift1::onResetWnd()
{
    if(NULL == m_pDataSource)return;
    if (NULL == m_pTableView)
    {
        m_pTableView = CCTableView::create(m_pDataSource, m_pContainer->getContentSize());
        m_pTableView->setDirection(kCCScrollViewDirectionVertical);
        m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        m_pContainer->addChild(m_pTableView);
    }
    m_pTableView->setDataSource(m_pDataSource);
    if(m_nCurType == eGiftTime)((MB_GiftTimeDataSource*)m_pDataSource)->sortData();
    if(m_nCurType == eGiftLevel)((MB_GiftLevelDataSource*)m_pDataSource)->sortData();
    m_pTableView->reloadData();

}
bool MB_LayerMainGift1::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pContainer",CCNode*,m_pContainer);


    return false;
}
SEL_MenuHandler MB_LayerMainGift1::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerMainGift1::onCloseClick);
    return NULL;
}
SEL_CCControlHandler MB_LayerMainGift1::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}
void MB_LayerMainGift1::onCloseClick(CCObject* pSender)
{
    ((MB_ResWindow*)getParent())->dirty();
    removeFromParent();
}


////message sc_daily_reward_get[id=11012]{
////    required        int8            type            =1;//1在线时长礼包，2等级礼包，3连续登陆礼包
////    required        int32           needValue       =2;//用需要条件标记要领取哪个档位的礼包，type=1，在线累计分钟数，type=2，当前等级，type=3，累计连续登陆天数
////    required        int8            result          =3;//0成功，1已领取，   2不满足条件，根据type决定，type=1在线时长不足，type=2等级不足，type=3连续登陆天数不足， 3无此礼包配置
////}
const char* szResult[]={"","在线时长不足","等级不足","连续登陆天数不足"};
void MB_LayerMainGift1::sc_daily_reward_get(MB_MsgBuffer* pRecv)
{
    uint8_t type;
    uint32_t needValue;
    uint8_t result;
    pRecv->readU8(&type);
    pRecv->readU32(&needValue);
    pRecv->readU8(&result);

    switch (result)
    {
        case 0:
        {
            MB_Message::sharedMB_Message()->removeALLMessage();
            MB_DailyRewrdInfo* pInfo = m_pInterface->getInfoByType((EGiftType)type);
            if(pInfo)
            {
                MB_DailyRewrd* pReward = pInfo->getRewardByNeedValue(needValue);
                if(pReward)
                {
                    pReward->setIsGet(true);
                    CCPoint pt = m_pTableView->getContentOffset();
                    onResetWnd();
                    m_pTableView->setContentOffset(pt);
                }

                MB_LayerRewardMore* p = MB_LayerRewardMore::create(pReward->getMailRewards()->converIDNUM2RewardTempleteValue());
                if (p)
                {
                    p->setShowRoleInfoPanel(false);
                    pushWindow(p);
                }
            }
        }
            break;
        case 1:
            MB_Message::sharedMB_Message()->showMessage("已领取");
            break;
        case 2:
            MB_Message::sharedMB_Message()->showMessage(szResult[type]);
            break;
        case 3:
            MB_Message::sharedMB_Message()->showMessage("无此礼包配置");
            break;
        default:
            break;
    }
}

void MB_LayerMainGift1::cs_daily_reward_get(uint8_t type,uint32_t needValue)
{
    MB_Message::sharedMB_Message()->showMessage(10);
    m_pInterface->cs_daily_reward_get(type, needValue);
}




MB_LayerMainGift2::MB_LayerMainGift2()
{
    m_pContainer     = NULL;
    m_pInterface = NULL;
    m_pDataSource = NULL;
    m_pTableView = NULL;
    m_bShowRoleInfoPanel = false;
    m_nCurType = eGiftNone;
    SOCKET_MSG_REGIST(SC_DAILY_REWARD_GET, MB_LayerMainGift2);
    SOCKET_MSG_REGIST(SC_DAILY_REWARD_LIST, MB_LayerMainGift2);
    SOCKET_MSG_REGIST(SC_ROLE_UPDATE_LEVEL, MB_LayerMainGift2);
    MB_LayerChatMain::SetChatMainVisible(false, "MB_LayerMainGift2");
}
MB_LayerMainGift2::~MB_LayerMainGift2()
{
    CC_SAFE_RELEASE_NULL(m_pContainer);
    SOCKET_MSG_UNREGIST(SC_DAILY_REWARD_GET);
    SOCKET_MSG_UNREGIST(SC_DAILY_REWARD_LIST);
    SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_LEVEL);
}
void MB_LayerMainGift2::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    switch (nMsg) {
        case SC_DAILY_REWARD_GET:
            sc_daily_reward_get(pRecv);
            break;
        case SC_DAILY_REWARD_LIST:
        {
            CCPoint pt = m_pTableView->getContentOffset();
            onResetWnd();
            m_pTableView->setContentOffset(pt);
        }
            break;
        case SC_ROLE_UPDATE_LEVEL:
        {
            if (m_nCurType == eGiftLevel)
            {
                CCPoint pt = m_pTableView->getContentOffset();
                onResetWnd();
                m_pTableView->setContentOffset(pt);
            }
        }
            break;
        default:
            break;
    }
}
bool MB_LayerMainGift2::init()
{
    CCNode* pNode = loadResource("res/gift_layer_main2.ccbi");
    if(pNode)
    {
        addChild(pNode);
        NSGameHelper::adjustScrollNode(m_pContainer);
        go2Page(eGiftLevel);
        return true;
    }
    return false;
}
void MB_LayerMainGift2::go2Page(EGiftType e)
{
    if(m_nCurType == e)
    {
        return;
    }
    m_nCurType = e;
    
    m_pDataSource = m_pInterface->getDataSourceByType(e);
    onResetWnd();
}



bool MB_LayerMainGift2::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pInterface = dynamic_cast<MB_GiftsInterface*>(pDataSource);
    return m_pInterface!=NULL;
}

void MB_LayerMainGift2::onResetWnd()
{
    if(NULL == m_pDataSource)return;
    if (NULL == m_pTableView)
    {
        m_pTableView = CCTableView::create(m_pDataSource, m_pContainer->getContentSize());
        m_pTableView->setDirection(kCCScrollViewDirectionVertical);
        m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        m_pContainer->addChild(m_pTableView);
    }
    m_pTableView->setDataSource(m_pDataSource);
    if(m_nCurType == eGiftTime)((MB_GiftTimeDataSource*)m_pDataSource)->sortData();
    if(m_nCurType == eGiftLevel)((MB_GiftLevelDataSource*)m_pDataSource)->sortData();
    m_pTableView->reloadData();
    
}
bool MB_LayerMainGift2::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pContainer",CCNode*,m_pContainer);
    
    
    return false;
}
SEL_MenuHandler MB_LayerMainGift2::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerMainGift2::onCloseClick);
    return NULL;
}
SEL_CCControlHandler MB_LayerMainGift2::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}
void MB_LayerMainGift2::onCloseClick(CCObject* pSender)
{
    ((MB_ResWindow*)getParent())->dirty();
    removeFromParent();
}


////message sc_daily_reward_get[id=11012]{
////    required        int8            type            =1;//1在线时长礼包，2等级礼包，3连续登陆礼包
////    required        int32           needValue       =2;//用需要条件标记要领取哪个档位的礼包，type=1，在线累计分钟数，type=2，当前等级，type=3，累计连续登陆天数
////    required        int8            result          =3;//0成功，1已领取，   2不满足条件，根据type决定，type=1在线时长不足，type=2等级不足，type=3连续登陆天数不足， 3无此礼包配置
////}
void MB_LayerMainGift2::sc_daily_reward_get(MB_MsgBuffer* pRecv)
{
    uint8_t type;
    uint32_t needValue;
    uint8_t result;
    pRecv->readU8(&type);
    pRecv->readU32(&needValue);
    pRecv->readU8(&result);
    
    switch (result)
    {
        case 0:
        {
            MB_Message::sharedMB_Message()->removeALLMessage();
            MB_DailyRewrdInfo* pInfo = m_pInterface->getInfoByType((EGiftType)type);
            if(pInfo)
            {
                MB_DailyRewrd* pReward = pInfo->getRewardByNeedValue(needValue);
                if(pReward)
                {
                    pReward->setIsGet(true);
                    CCPoint pt = m_pTableView->getContentOffset();
                    onResetWnd();
                    m_pTableView->setContentOffset(pt);
                }
                
                MB_LayerRewardMore* p = MB_LayerRewardMore::create(pReward->getMailRewards()->converIDNUM2RewardTempleteValue());
                if (p)
                {
                    p->setShowRoleInfoPanel(false);
                    pushWindow(p);
                }
            }
        }
            break;
        case 1:
            MB_Message::sharedMB_Message()->showMessage("已领取");
            break;
        case 2:
            MB_Message::sharedMB_Message()->showMessage(szResult[type]);
            break;
        case 3:
            MB_Message::sharedMB_Message()->showMessage("无此礼包配置");
            break;
        default:
            break;
    }
}

void MB_LayerMainGift2::cs_daily_reward_get(uint8_t type,uint32_t needValue)
{
    MB_Message::sharedMB_Message()->showMessage(10);
    m_pInterface->cs_daily_reward_get(type, needValue);
}



MB_LayerMainGift3::MB_LayerMainGift3()
{
    m_pContainer     = NULL;
    m_pInterface = NULL;
    m_pDataSource = NULL;
    m_pTableView = NULL;
    m_bShowRoleInfoPanel = false;
    m_nCurType = eGiftNone;
    SOCKET_MSG_REGIST(SC_DAILY_REWARD_GET, MB_LayerMainGift3);
    SOCKET_MSG_REGIST(SC_DAILY_REWARD_LIST, MB_LayerMainGift3);
    SOCKET_MSG_REGIST(SC_ROLE_UPDATE_LEVEL, MB_LayerMainGift3);
    MB_LayerChatMain::SetChatMainVisible(false, "MB_LayerMainGift3");
}
MB_LayerMainGift3::~MB_LayerMainGift3()
{
    CC_SAFE_RELEASE_NULL(m_pContainer);
    SOCKET_MSG_UNREGIST(SC_DAILY_REWARD_GET);
    SOCKET_MSG_UNREGIST(SC_DAILY_REWARD_LIST);
    SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_LEVEL);
}
void MB_LayerMainGift3::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    switch (nMsg) {
        case SC_DAILY_REWARD_GET:
            sc_daily_reward_get(pRecv);
            break;
        case SC_DAILY_REWARD_LIST:
        {
            CCPoint pt = m_pTableView->getContentOffset();
            onResetWnd();
            m_pTableView->setContentOffset(pt);
        }
            break;
        case SC_ROLE_UPDATE_LEVEL:
        {
            if (m_nCurType == eGiftLevel)
            {
                CCPoint pt = m_pTableView->getContentOffset();
                onResetWnd();
                m_pTableView->setContentOffset(pt);
            }
        }
            break;
        default:
            break;
    }
}
bool MB_LayerMainGift3::init()
{
    CCNode* pNode = loadResource("res/gift_layer_main3.ccbi");
    if(pNode)
    {
        addChild(pNode);
        NSGameHelper::adjustScrollNode(m_pContainer);
        go2Page(eGiftMLogin);
        return true;
    }
    return false;
}
void MB_LayerMainGift3::go2Page(EGiftType e)
{
    if(m_nCurType == e)
    {
        return;
    }
    m_nCurType = e;
    
    m_pDataSource = m_pInterface->getDataSourceByType(e);
    onResetWnd();
}



bool MB_LayerMainGift3::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pInterface = dynamic_cast<MB_GiftsInterface*>(pDataSource);
    return m_pInterface!=NULL;
}

void MB_LayerMainGift3::onResetWnd()
{
    if(NULL == m_pDataSource)return;
    if (NULL == m_pTableView)
    {
        m_pTableView = CCTableView::create(m_pDataSource, m_pContainer->getContentSize());
        m_pTableView->setDirection(kCCScrollViewDirectionVertical);
        m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        m_pContainer->addChild(m_pTableView);
    }
    m_pTableView->setDataSource(m_pDataSource);
    if(m_nCurType == eGiftTime)((MB_GiftTimeDataSource*)m_pDataSource)->sortData();
    if(m_nCurType == eGiftLevel)((MB_GiftLevelDataSource*)m_pDataSource)->sortData();
    m_pTableView->reloadData();
    
}
bool MB_LayerMainGift3::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pContainer",CCNode*,m_pContainer);
    
    
    return false;
}
SEL_MenuHandler MB_LayerMainGift3::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerMainGift3::onCloseClick);
    return NULL;
}
SEL_CCControlHandler MB_LayerMainGift3::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}
void MB_LayerMainGift3::onCloseClick(CCObject* pSender)
{
    ((MB_ResWindow*)getParent())->dirty();
    removeFromParent();
}


////message sc_daily_reward_get[id=11012]{
////    required        int8            type            =1;//1在线时长礼包，2等级礼包，3连续登陆礼包
////    required        int32           needValue       =2;//用需要条件标记要领取哪个档位的礼包，type=1，在线累计分钟数，type=2，当前等级，type=3，累计连续登陆天数
////    required        int8            result          =3;//0成功，1已领取，   2不满足条件，根据type决定，type=1在线时长不足，type=2等级不足，type=3连续登陆天数不足， 3无此礼包配置
////}
void MB_LayerMainGift3::sc_daily_reward_get(MB_MsgBuffer* pRecv)
{
    uint8_t type;
    uint32_t needValue;
    uint8_t result;
    pRecv->readU8(&type);
    pRecv->readU32(&needValue);
    pRecv->readU8(&result);
    
    switch (result)
    {
        case 0:
        {
            MB_Message::sharedMB_Message()->removeALLMessage();
            MB_DailyRewrdInfo* pInfo = m_pInterface->getInfoByType((EGiftType)type);
            if(pInfo)
            {
                MB_DailyRewrd* pReward = pInfo->getRewardByNeedValue(needValue);
                if(pReward)
                {
                    pReward->setIsGet(true);
                    CCPoint pt = m_pTableView->getContentOffset();
                    onResetWnd();
                    m_pTableView->setContentOffset(pt);
                }
                
                MB_LayerRewardMore* p = MB_LayerRewardMore::create(pReward->getMailRewards()->converIDNUM2RewardTempleteValue());
                if (p)
                {
                    p->setShowRoleInfoPanel(false);
                    pushWindow(p);
                }
            }
        }
            break;
        case 1:
            MB_Message::sharedMB_Message()->showMessage("已领取");
            break;
        case 2:
            MB_Message::sharedMB_Message()->showMessage(szResult[type]);
            break;
        case 3:
            MB_Message::sharedMB_Message()->showMessage("无此礼包配置");
            break;
        default:
            break;
    }
}

void MB_LayerMainGift3::cs_daily_reward_get(uint8_t type,uint32_t needValue)
{
    MB_Message::sharedMB_Message()->showMessage(10);
    m_pInterface->cs_daily_reward_get(type, needValue);
}
