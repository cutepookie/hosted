//
//  MB_GuardProtocol.cpp
//  ProjectMB
//
//  Created by yuanwugang on 15-3-3.
//
//

#include "MB_GuardProtocol.h"
#include "MB_MsgBuffer.h"
#include "../Common/GameLib/UnityXml/MB_XmlItems.h"

MB_PetGuardData::MB_PetGuardData()
{
    m_uPetPos = 0;
    m_uPetUid = 0;
    m_uPetTypeId = 0;
    m_uRank = 0;
    m_pBaseAttrList = new CCArray();//基础属性信息
    m_pHighAttrList = new CCArray();//高級属性信息
    
}

MB_PetGuardData::~MB_PetGuardData()
{
    CC_SAFE_RELEASE_NULL(m_pBaseAttrList);
    CC_SAFE_RELEASE_NULL(m_pHighAttrList);
}


bool MB_PetGuardData::read(MB_MsgBuffer* recvPacket)
{
    recvPacket->readU8(&m_uPetPos);
    recvPacket->readU64(&m_uPetUid);
    recvPacket->readU16(&m_uPetTypeId);
    recvPacket->readU8(&m_uRank);
    setBaseAttr(recvPacket);
    setHightAttr(recvPacket);
    return true;
}

void MB_PetGuardData::setBaseAttr(MB_MsgBuffer* recvPacket)
{
    m_pBaseAttrList->removeAllObjects();
    uint16_t len = 0;
    recvPacket->readU16(&len);
    for (int i = 0;i < len;i++)
    {
        MB_PetGuardAttr* attr = new MB_PetGuardAttr();
        attr->read(recvPacket);
        m_pBaseAttrList->addObject(attr);
        attr->release();
    }
}
void MB_PetGuardData::setHightAttr(MB_MsgBuffer* recvPacket)
{
    m_pHighAttrList->removeAllObjects();
    uint16_t len = 0;
    recvPacket->readU16(&len);
    for (int i = 0;i < len;i++)
    {
        MB_PetGuardAttr* attr = new MB_PetGuardAttr();
        attr->read(recvPacket);
        m_pHighAttrList->addObject(attr);
        attr->release();
    }
}

MB_PetGuardAttr::MB_PetGuardAttr()
{
    m_uAttrType = 0;
    m_uAddValue = 0;
}
MB_PetGuardAttr::~MB_PetGuardAttr()
{
    
}

bool MB_PetGuardAttr::read(MB_MsgBuffer* recvPacket)
{
    recvPacket->readU8(&m_uAttrType);
    recvPacket->readU32(&m_uAddValue);
    return true;
}

bool MB_AttrRange::init(MB_XmlNode* pNode)
{
    m_uAttrMin = pNode->queryAttributeByName("min")->intValue();
    m_uAttrMax = pNode->queryAttributeByName("max")->intValue();
    m_uRank = pNode->queryAttributeByName("star")->intValue();
    return true;
}

MB_AttrRangeRank::MB_AttrRangeRank()
{
    m_pAttrRangeArray = new CCArray();
}

MB_AttrRangeRank::~MB_AttrRangeRank()
{
    CC_SAFE_RELEASE(m_pAttrRangeArray);
}

uint8_t MB_AttrRangeRank::getRankByVal(uint32_t val)
{
    MB_AttrRange* data = NULL;
    CCARRAY_FOREACH_4TYPE(m_pAttrRangeArray, MB_AttrRange*, data)
    {
        if (data->getAttrMin() <= val && val <= data->getAttrMax())
        {
            return data->getRank();
        }
    }
    return 1;
}

void MB_AttrRangeRank::readData(MB_XmlNode* pNode,const char* attName,uint8_t type)
{
    m_uAttrType = type;
    CCArray* pArray = CCArray::create();
    m_pAttrRangeArray->removeAllObjects();
    MB_XmlNode* pTemp = NULL;
    MB_AttrRange *pData = NULL;
    if(pNode->queryNodesByName(attName, pArray))
    {
        CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pTemp)
        {
            pData = new MB_AttrRange;
            if (pData->init(pTemp))
            {
                m_pAttrRangeArray->addObject(pData);
            }
            CC_SAFE_RELEASE_NULL(pData);
        }
    }

}




bool MB_LockCost::init(MB_XmlNode* pNode)
{
    m_uNum = pNode->queryAttributeByName("num")->intValue();
    m_uCost = pNode->queryAttributeByName("gold")->intValue();
    return true;
}






MB_PetGuardRule::MB_PetGuardRule()
{
    m_pLockCostArray = new CCArray();
    m_pRankArray = new CCArray();
}
MB_PetGuardRule::~MB_PetGuardRule()
{
    CC_SAFE_RELEASE(m_pLockCostArray);
    CC_SAFE_RELEASE(m_pRankArray);
}

bool MB_PetGuardRule::init()
{
    MB_XmlFile* pXml = MB_XmlFile::create("config/partner.xml");
    if (pXml == NULL)
    {
        return false;
    }
    
    CCArray* pArray = CCArray::create();
    if(!pXml->queryNodesByName("partner", pArray))
    {
        return false;
    }
    
    
    MB_XmlNode* pRoot = dynamic_cast<MB_XmlNode*>(pArray->objectAtIndex(0));
    pArray->removeAllObjects();

    m_pLockCostArray->removeAllObjects();
    MB_XmlNode* pTemp = NULL;
    MB_LockCost *pLockCost = NULL;
    if(pRoot->queryNodesByName("lock|lock", pArray))
    {
        CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pTemp)
        {
            pLockCost = new MB_LockCost;
            if (pLockCost->init(pTemp))
            {
                m_pLockCostArray->addObject(pLockCost);
            }
            CC_SAFE_RELEASE_NULL(pLockCost);
        }
    }

    m_pRankArray->removeAllObjects();
    std::string str[18] =
    {
        "gerAttack|gerAttack",
        "gerHpMax|gerHpMax",
        "",
        "",
        "gerCritic|gerCritic",
        "gerCriticReduce|gerCriticReduce",
        "gerDoom|gerDoom",
        "gerMiss|gerMiss",   //8
        "gerAbsorb|gerAbsorb",
        "gerDamageBack|gerDamageBack",
        "gerReel|gerReel",
        "gerReelReduce|gerReelReduce",
        "gerPhyDefBite|gerPhyDefBite",//13
        "gerPhyDef|gerPhyDef",
        "gerMagDefBite|gerMagDefBite",
        "gerMagDef|gerMagDef",
        "gerAttackAddtion|gerAttackAddtion",
        "gerHpMaxAddtion|gerHpMaxAddtion"
    };
    
    for (int i = 0;i < 18;i++)
    {
        MB_AttrRangeRank* pRangeRank = new MB_AttrRangeRank();
        pRangeRank->readData(pRoot,str[i].c_str(),i+1);
        m_pRankArray->addObject(pRangeRank);
        CC_SAFE_RELEASE(pRangeRank);
    }
    return true;
}
uint32_t MB_PetGuardRule::getCostByLockNum(int num)
{
    MB_LockCost* lockData = NULL;
    CCARRAY_FOREACH_4TYPE(m_pLockCostArray, MB_LockCost*,lockData)
    {
        if (lockData->getNum() == num)
        {
            return lockData->getCost();
        }
    }
    return 0;
}
uint8_t MB_PetGuardRule::getRankByValAndType(uint32_t val,uint8_t type)
{
    MB_AttrRangeRank* pRangeRank = NULL;
    CCARRAY_FOREACH_4TYPE(m_pRankArray, MB_AttrRangeRank*,pRangeRank)
    {
        if (pRangeRank->getAttrType() == type)
        {
            return pRangeRank->getRankByVal(val);
        }
    }
    return 1;
}