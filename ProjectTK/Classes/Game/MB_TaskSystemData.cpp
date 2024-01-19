//
//  MB_TaskSystemData.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-2.
//
//

#include "MB_TaskSystemData.h"
#include <algorithm>
MB_TaskCondition::MB_TaskCondition()
{
    m_nType = 0;
    m_nTarget = 0;
    m_nValue = 0;
}

MB_TaskCondition* MB_TaskCondition::create(MB_XmlNode* pNode)
{
    MB_TaskCondition* pInstance = new MB_TaskCondition;
    if (pInstance && pInstance->init(pNode))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

bool MB_TaskCondition::init(const MB_XmlNode* pNode)
{
    if (pNode == NULL)
    {
        return false;
    }
    
    uint16_t nType = pNode->queryAttributeByName("type")->intValue();
    uint16_t nTarget = pNode->queryAttributeByName("target")->intValue();
    uint64_t nValue = pNode->queryAttributeByName("value")->intValue();
    uint16_t nShowType = pNode->queryAttributeByName("showType")->intValue();
    return init(nType,nTarget,nValue,nShowType);
}

bool MB_TaskCondition::init(uint16_t nType,uint16_t nTarget,uint64_t nValue,uint16_t nShowType)
{
    m_nType = nType;
    m_nTarget = nTarget;
    m_nValue = nValue;
    m_nShowType = nShowType;
    return true;
}

CCNode* MB_TaskReward::createRewardNode()
{
//    CCSprite* pSprite = CCSprite::create();
//    CCLabelTTF* pName = CCLabelTTF::create();
//    if (m_nRewardType == 1)
//    {
//        NSGameHelper::setMonsterIconDetailByTid(m_nTid, 0, pSprite,pName);
//    }
//    else
//    {
//        NSGameHelper::setItemIconDetailByTid(m_nTid, 0, pSprite,pName);
//    }

//    CCSize sz = pSprite->getContentSize();
//    sz.width += pName->getDimensions().width;
//    sz.height += pName->getDimensions().height;
    
//    CCNode* pNode = CCNode::create();
//    pNode->setContentSize(sz);
//    pSprite->setAnchorPoint(ccp(0, 0));
//    pNode->addChild(pSprite);
//    pName->setAnchorPoint(ccp(0, 0));
//    pNode->addChild(pName);
//    pName->setPositionX(pSprite->getContentSize().width*0.25);
//    //pName->setPositionY(pName->getPositionY()-12);
//    
//    pSprite->setScale(0.25);
//    const char *pCString = pName->getString();
//    char buff[64] = {};
//    sprintf(buff, "%s+%d",pCString,m_nValue);
//    pName->setString(buff);
//    pName->setFontSize(22);
    CCNode* pNode = CCNode::create();
    CCLabelTTF* pName = CCLabelTTF::create();
    NSGameHelper::setItemIconDetailByTid(m_nTid, 0, NULL,pName);
    char buff[64] = {};
    sprintf(buff, "%d",m_nValue);
    pName->setColor(ccBLACK);
    pName->setString(buff);
    pName->setFontSize(22);
    pName->setAnchorPoint(ccp(0, 0));
    pNode->addChild(pName);
    
//    pName->setPositionX(pName->getDimensions().width);
//    pName->setPositionY(pName->getPositionY()+12);
    return pNode;
}

void MB_TaskReward::setIcon(CCSprite* sprite)
{
    if (m_nRewardType == 1)
    {
        NSGameHelper::setMonsterIconDetailByTid(m_nTid, 0, sprite,NULL);
    }
    else
    {
        NSGameHelper::setItemIconDetailByTid(m_nTid, 0, sprite,NULL);
    }
//    CCLabelTTF* fNum = CCLabelTTF::create();
//    char buff[40];
//    sprintf(buff,"+%d",m_nValue);
//    fNum->setString(buff);
//    fNum->setAnchorPoint(ccp(0.5,0.5));
//    sprite->addChild(fNum);
//    fNum->setFontSize(28);
//    fNum->setPosition(ccp(sprite->getContentSize().width/2,sprite->getContentSize().height/2));
    sprite->setScale(1);
}
MB_TaskReward::MB_TaskReward()
{
    m_nTid = 0;
    m_nValue = 0;
}

MB_TaskReward* MB_TaskReward::create(MB_XmlNode* pNode)
{
    MB_TaskReward* pInstance = new MB_TaskReward;
    if (pInstance && pInstance->init(pNode))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

bool MB_TaskReward::init(MB_XmlNode* pNode)
{
    if (pNode == NULL)
    {
        return false;
    }
    
    uint16_t nTypeId = pNode->queryAttributeByName("typeid")->intValue();
    uint64_t nValue = pNode->queryAttributeByName("value")->intValue();
    uint16_t nType = pNode->queryAttributeByName("rewardType")->intValue();
    return init(nTypeId,nValue,nType);
}

MB_TaskReward* MB_TaskReward::create(uint16_t nTid,uint32_t nValue,uint16_t nType)
{
    MB_TaskReward* pInstance = new MB_TaskReward();
    if (pInstance && pInstance->init(nTid,nValue,nType))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return pInstance;
}

bool MB_TaskReward::init(uint16_t nTid,uint32_t nValue,uint16_t nType)
{
    m_nTid = nTid;
    m_nValue = nValue;
    m_nRewardType = nType;
    return true;
}

MB_TaskData::MB_TaskData()
{
    m_pReward = new CCArray;
    m_pCondition = new MB_TaskCondition;
}

MB_TaskData::~MB_TaskData()
{
    CC_SAFE_RELEASE_NULL(m_pReward);
    CC_SAFE_RELEASE_NULL(m_pCondition);
}

MB_TaskData* MB_TaskData::create(MB_XmlNode* pNode)
{
    MB_TaskData* pInstance = new MB_TaskData;
    if (pInstance && pInstance->init(pNode))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

bool MB_TaskData::init(MB_XmlNode* pNode)
{
    if (pNode == NULL)
    {
        return false;
    }
    
    m_nTypeId = pNode->queryAttributeByName("id")->intValue();
    m_nType = pNode->queryAttributeByName("type")->intValue();
    m_szName = pNode->queryAttributeByName("name")->getCString();
    m_szDescription = pNode->queryAttributeByName("description")->getCString();
    m_nChangePageID = pNode->queryAttributeByName("changePage")->intValue();
    m_szIcon = pNode->queryAttributeByName("Icon")->getCString();
    
    /*<condition type="200" target="" value="30"/>*/
    const MB_XmlNode* pCondition = &((*pNode)["condition"]);
    m_pCondition->init(pCondition);
    
    CCArray* pRewards = CCArray::create();
    MB_TaskReward* pReward = NULL;
    
    if(pNode->queryNodesByName("rewards|reward", pRewards))
    {
        m_pReward->removeAllObjects();
        CCARRAY_FOREACH_4TYPE(pRewards, MB_XmlNode*, pNode)
        {
            pReward = MB_TaskReward::create(pNode);
            if (pReward)
            {
                m_pReward->addObject(pReward);
            }
        }
    }
    
    return true;
}

CCArray* MB_TaskData::getTaskRewardArray()
{
    return m_pReward;
}


CCNode* MB_TaskData::createRewardNode()
{
    MB_TaskReward* pReward = NULL;
    CCNode* pContainer = CCNode::create();
    pContainer->setAnchorPoint(ccp(0,0));
    CCNode* pUint = NULL;
    CCPoint pt;
    
    CCARRAY_FOREACH_4TYPE(m_pReward, MB_TaskReward*, pReward)
    {
        pUint = pReward->createRewardNode();
        if(pUint)
        {
            pContainer->addChild(pUint);
            pUint->setPositionX(pt.x);
            pt.x += pUint->getContentSize().width;
        }
    }
    
    return pContainer;
}

void MB_TaskData::setRewardIcon(CCSprite* sprite)
{
    MB_TaskReward* pReward = NULL;
    CCARRAY_FOREACH_4TYPE(m_pReward, MB_TaskReward*, pReward)
    {
        pReward->setIcon(sprite);
    }
}

void MB_TaskData::setAchievmentIcon(CCSprite* sprite)
{
    if(sprite)
    {
        NSGameHelper::setSpriteFrame(sprite,getIcon().c_str());
    }
}

MB_TaskCondition* MB_TaskData::getTaskCondition()
{
    return m_pCondition;
}

MB_TaskServerData::MB_TaskServerData()
{
    
}

MB_TaskServerData::~MB_TaskServerData()
{
    
}

/*
 message		p_task[id=20101]{
 required	int32					task_id				=1;			//任务id
 required	int8						status				=2;			//任务状态  1:未接  2：已接  3：已完成 4:已提交（用于每日任务和成就的显示）
 required	int32					trigpet_num	=4;			//触发了的个数（比如当前杀了多少个怪）
 }
 */
bool MB_TaskServerData::read(MB_MsgBuffer* recvPacket)
{
    uint32_t u32 = 0;
    uint8_t u8 = 0;
    
    recvPacket->readU32(&u32);
    m_nTaskId = u32;
    recvPacket->readU8(&u8);
    m_nStatus = u8;
    recvPacket->readU32(&u32);
    m_nValue = u32;
    return true;
}

MB_TaskServerData& MB_TaskServerData::operator=(const MB_TaskServerData& right)
{
    m_nStatus = right.getStatus();
    m_nTaskId = right.getTaskId();
    m_nValue = right.getValue();
    
    return *this;
}


bool MB_TaskServerData::less(const CCObject* in_pCcObj0, const CCObject* in_pCcObj1)
{
    int s0 =  ((MB_TaskServerData*)in_pCcObj0)->getStatus();
    int s1 =  ((MB_TaskServerData*)in_pCcObj1)->getStatus();
    
    if(s0 == TASK_STATUS_COMPLATE && s1 != TASK_STATUS_COMPLATE)
    {
        return false;
    }
    else if(s0 != TASK_STATUS_COMPLATE && s1 == TASK_STATUS_COMPLATE)
    {
        return true;
    }
    
    if(((MB_TaskServerData*)in_pCcObj0)->getTaskId() > ((MB_TaskServerData*)in_pCcObj1)->getTaskId())
    {
        return true;
    }
    
    return false;
}


void MB_TaskServerData::sortTask(CCArray* in_pCcArrTasks)
{
    std::stable_sort(in_pCcArrTasks->data->arr, in_pCcArrTasks->data->arr + in_pCcArrTasks->data->num, MB_TaskServerData::less);
}
