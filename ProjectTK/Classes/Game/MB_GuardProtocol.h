//
//  MB_GuardProtocol.h
//  ProjectMB
//
//  Created by yuanwugang on 15-3-3.
//
//

#ifndef __ProjectMB__MB_GuardProtocol__
#define __ProjectMB__MB_GuardProtocol__


#define CS_PET_GUARD_INFO   10444
#define SC_PET_GUARD_INFO   10445

#define CS_PET_GUARD_SET    10446
#define SC_PET_GUARD_SET    10447

#define CS_PET_GUARD_REFRESH    10448
#define SC_PET_GUARD_REFRESH    10449

#define GUARD_ATTR_MAX  6

#include "MB_ServerData.h"
#include "MB_ClientData.h"
class MB_PetGuardData : public MB_ServerData
{
public:
    MB_PetGuardData();
    ~MB_PetGuardData();
    
    virtual bool read(MB_MsgBuffer* recvPacket);
    void setBaseAttr(MB_MsgBuffer* recvPacket);
    void setHightAttr(MB_MsgBuffer* recvPacket);
    CCArray* getBaseAttrArray(){return m_pBaseAttrList;};
    CCArray* getHighAttrArray(){return m_pHighAttrList;};
protected:
    CC_SYNTHESIZE(uint8_t, m_uPetPos,PetPos);//守護位置
    CC_SYNTHESIZE(uint64_t, m_uPetUid,PetUid);//守護武將ID
    CC_SYNTHESIZE(uint16_t, m_uPetTypeId,PetTypeId);//守護武將ID
    CC_SYNTHESIZE(uint8_t, m_uRank,Rank);//守護武將品階
    
    CCArray* m_pBaseAttrList;//基础属性信息
    CCArray* m_pHighAttrList;//高級属性信息
    
};

class MB_PetGuardAttr : public MB_ServerData
{
public:
    MB_PetGuardAttr();
    ~MB_PetGuardAttr();
    virtual bool read(MB_MsgBuffer* recvPacket);
protected:
    CC_SYNTHESIZE(uint8_t,m_uAttrType,AttrType);//属性類型编號;
    CC_SYNTHESIZE(uint32_t,m_uAddValue, AddValue);//属性增加值
};


class MB_AttrRange : public MB_ClientData
{
public:
    virtual bool init(MB_XmlNode* pNode);
protected:
    CC_SYNTHESIZE(uint32_t,m_uAttrMin,AttrMin);//属性最小值;
    CC_SYNTHESIZE(uint32_t,m_uAttrMax,AttrMax);//属性最大值;
    CC_SYNTHESIZE(uint8_t,m_uRank,Rank);        //属性品級
};

class MB_AttrRangeRank : public MB_ClientData
{
public:
    MB_AttrRangeRank();
    ~MB_AttrRangeRank();
    virtual bool init(MB_XmlNode* pNode){return true;};
    uint8_t getRankByVal(uint32_t val);
    void readData(MB_XmlNode* pNode,const char* attName,uint8_t type);
protected:
    CC_SYNTHESIZE(uint8_t,m_uAttrType,AttrType);//属性類型编號;
    CCArray* m_pAttrRangeArray;
};

class MB_LockCost : public MB_ClientData
{
public:
    virtual bool init(MB_XmlNode* pNode);
protected:
    CC_SYNTHESIZE(uint32_t,m_uCost,Cost);      //消耗寶石
    CC_SYNTHESIZE(uint32_t,m_uNum,Num);        //锁定
};


class MB_PetGuardRule
{
public:
    MB_PetGuardRule();
    ~MB_PetGuardRule();
    bool init();
    uint32_t getCostByLockNum(int num);
    uint8_t getRankByValAndType(uint32_t val,uint8_t type);
private:
    CCArray* m_pLockCostArray;
    CCArray* m_pRankArray;
};
#endif /* defined(__ProjectMB__MB_GuardProtocol__) */
