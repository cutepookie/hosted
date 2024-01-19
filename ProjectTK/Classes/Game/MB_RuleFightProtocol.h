#ifndef __ProjectMB__MB_RuleFightProtocol__
#define __ProjectMB__MB_RuleFightProtocol__

#include "MB_ServerData.h"
#include "MB_MsgBuffer.h"
#include <string>
#include "MB_NodeRuleRankUnit.h"
#include "../Common/GameLib/UnityXml/MB_XmlItems.h"
#define SC_HIST_NEW 11504
#define SC_ROLE_UPDATE_RULETIMES 10117
#define CS_RULE_INFO 13801
#define SC_RULE_INFO 13802
#define CS_RULE_RANK 13803
#define SC_RULE_RANK 13804
#define CS_RULE_LAST_RANK 13805
#define SC_RULE_LAST_RANK 13806
#define CS_RULE_FIGHT 13807
#define SC_RULE_FIGHT 13808
#define P_RULE_FIGHTER 13809
#define CS_HIST_REPLAY 11520
#define SC_HIST_REPLAY 11521
#define CS_RULE_LEAVE 13810

class Hist:public MB_ServerData
{
    CC_SYNTHESIZE(uint64_t, m_nHistUID, HistUID);
    // 第一位：1=别人发起的挑战，0=您发起的挑战
    // 第二位：1=发起者战斗胜利，0=发起者战斗失败
    // 第四位：1=pvp战报，0=秩序战场战报
    CC_SYNTHESIZE(uint8_t, m_nHistType, HistType);
    CC_SYNTHESIZE(std::string, m_strName, Name);
    CC_SYNTHESIZE(uint32_t, m_nRoleID, RoleID);
    CC_SYNTHESIZE(uint32_t, m_nTime, Time);
    // type=pvp战报时，此字段表示 战斗有一方胜利时，您的新排位
    // type=秩序战场战报时，此字段待定
    CC_SYNTHESIZE(uint16_t, m_nArg, Arg);       //秩序战场战报时，增加分数
    CC_SYNTHESIZE(uint32_t, m_nAddRepu, AddRepu);//秩序战场战报时，新的分数
public:
    Hist():m_nHistUID(0),m_nHistType(0),m_nRoleID(0),m_nTime(0),m_nArg(0),m_nAddRepu(0),m_pUnit(0){}
    ~Hist()
    {
        CC_SAFE_RELEASE_NULL(m_pUnit);
    }
    virtual bool read(MB_MsgBuffer* recvPacket)
    {
        recvPacket->readU64(&m_nHistUID);
        recvPacket->readU8(&m_nHistType);
        char *str = NULL;
        str = recvPacket->ReadString();
        if(str)m_strName = str;
        CC_SAFE_FREE(str);
        recvPacket->readU32(&m_nRoleID);
        recvPacket->readU32(&m_nTime);
        recvPacket->readU16(&m_nArg);
        recvPacket->readU32(&m_nAddRepu);
        return true;
    }
    
    MB_NodeHistoryUnit* getUnit()
    {
        if(m_pUnit == NULL)
        {
            m_pUnit = MB_NodeHistoryUnit::create(this);
            CC_SAFE_RETAIN(m_pUnit);
        }
        return m_pUnit;
    }
private:
    MB_NodeHistoryUnit* m_pUnit;
};

class RuleFighter:public MB_ServerData
{
public:
    RuleFighter():m_nRoleID(0),m_nFightPower(0),m_bIsMale(0),m_nTitle(0),m_nHead(0),m_nLevel(0),m_nScore(0),m_nRank(0),m_nWinTimes(0)
    ,m_nFightTimes(0),m_nWinConTimes(0),m_nWinConMaxTimes(0){};
    ~RuleFighter(){};
    
    CC_SYNTHESIZE(uint32_t,m_nRoleID,RoleID);//角色ID
    CC_SYNTHESIZE(uint64_t,m_nFightPower,FightPower);//战斗力
    CC_SYNTHESIZE(bool, m_bIsMale,IsMale);//性别
    CC_SYNTHESIZE(uint8_t, m_nTitle,Title);//称号
    CC_SYNTHESIZE(uint32_t,m_nHead,Head);//头像
    CC_SYNTHESIZE(uint16_t,m_nLevel,Level);//等级
    CC_SYNTHESIZE(std::string,m_strRoleName,RoleName);//名字
    CC_SYNTHESIZE(uint32_t,m_nScore,Score);//积分
    CC_SYNTHESIZE(uint32_t,m_nRank,Rank);//排名
    CC_SYNTHESIZE(uint16_t,m_nWinTimes,WinTimes);//胜利场数
    CC_SYNTHESIZE(uint16_t,m_nFightTimes,FightTimes);//战斗场数
    CC_SYNTHESIZE(uint16_t,m_nWinConTimes,WinConTimes);//连胜场数
    CC_SYNTHESIZE(uint16_t,m_nWinConMaxTimes,WinConMaxTimes);//最大连胜场数
    
    virtual bool read(MB_MsgBuffer* recvPacket)
    {
        recvPacket->readU32(&m_nRoleID);
        recvPacket->readU64(&m_nFightPower);
        recvPacket->readU8(&m_bIsMale);
        recvPacket->readU8(&m_nTitle);
        recvPacket->readU32(&m_nHead);
        recvPacket->readU16(&m_nLevel);
        
        char* pName = recvPacket->ReadString();
        if(pName)m_strRoleName=pName;
        CC_SAFE_FREE(pName);
        
        recvPacket->readU32(&m_nScore);
        recvPacket->readU32(&m_nRank);
        recvPacket->readU16(&m_nWinTimes);
        recvPacket->readU16(&m_nFightTimes);
        recvPacket->readU16(&m_nWinConTimes);
        recvPacket->readU16(&m_nWinConMaxTimes);
        return true;
    }
};

class RuleFightInfo:public MB_ServerData
{
public:
    RuleFightInfo()
    {
        m_pList = new CCArray;
        m_TarFighter = new RuleFighter;
    }
    ~RuleFightInfo()
    {
        CC_SAFE_RELEASE(m_pList);
        CC_SAFE_RELEASE_NULL(m_TarFighter);
    }
    
    CC_SYNTHESIZE(uint32_t,m_nScore,Score);//我的分数
    CC_SYNTHESIZE(uint32_t,m_nRank,Rank);//我的排名
    CC_SYNTHESIZE(uint16_t,m_nWinTimes,WinTimes);//胜利场数
    CC_SYNTHESIZE(uint16_t,m_nFightTimes,FightTimes);//战斗场数
    CC_SYNTHESIZE(uint16_t,m_nWinConTimes,WinConTimes);//连胜场数
    CC_SYNTHESIZE(uint16_t,m_nWinConMaxTimes,WinConMaxTimes);//最大连胜场数
    CC_SYNTHESIZE(RuleFighter*,m_TarFighter,TarFighter);//对手信息
    CC_SYNTHESIZE(CCArray*, m_pList, List);
    
    Hist* queryRuleFighterByUID(uint64_t uid)
    {
        Hist* obj = NULL;
        CCARRAY_FOREACH_4TYPE(m_pList, Hist*, obj)
        {
            if(obj->getHistUID() == uid)return obj;
        }
        return NULL;
    }
    
    virtual bool sc_hist_new(MB_MsgBuffer* recvPacket,uint64_t& uid)
    {
        int len = 0;
        recvPacket->readU16(&len);
        for (int i =0; i<len; ++i)
        {
            Hist* pHist = new Hist();
            if(pHist)
            {
                pHist->read(recvPacket);
                uid = pHist->getHistUID();
                m_pList->insertObject(pHist, 0);
                
            }
            CC_SAFE_RELEASE_NULL(pHist);
        }
        
        while (m_pList->count() > 20)
        {
            m_pList->removeObjectAtIndex(m_pList->count()-1);
        }
        
        return true;
    }
    
    virtual bool read(MB_MsgBuffer* recvPacket)
    {
        recvPacket->readU32(&m_nScore);
        recvPacket->readU32(&m_nRank);
        recvPacket->readU16(&m_nWinTimes);
        recvPacket->readU16(&m_nFightTimes);
        recvPacket->readU16(&m_nWinConTimes);
        recvPacket->readU16(&m_nWinConMaxTimes);
        m_TarFighter->read(recvPacket);
        
        m_pList->removeAllObjects();
        int len = 0;
        recvPacket->readU16(&len);
        for (int i =0; i<len; ++i)
        {
            Hist* pHist = new Hist();
            if(pHist)
            {
                pHist->read(recvPacket);
                m_pList->addObject(pHist);
            }
            CC_SAFE_RELEASE_NULL(pHist);
        }
        
        return true;
    }
};

class MB_RuleFightConfig:public MB_ClientData
{
public:
    virtual bool init(MB_XmlNode* pNode)
    {
        m_nMin = pNode->queryAttributeByName("minscore")->intValue();
        m_nMax = pNode->queryAttributeByName("maxscore")->intValue();
        m_strTitle = pNode->queryAttributeByName("title")->getCString();
        return true;
    }
private:
    CC_SYNTHESIZE(int, m_nMin, MinScore);
    CC_SYNTHESIZE(int, m_nMax, MaxScore);
    CC_SYNTHESIZE(std::string, m_strTitle, Title);
};


class MB_RuleConfigMgr:public CCObject
{
public:
    MB_RuleConfigMgr()
    {
        m_pArray = new CCArray;
    }
    ~MB_RuleConfigMgr()
    {
        CC_SAFE_RELEASE_NULL(m_pArray);
    }
    static MB_RuleConfigMgr* getInstance()
    {
        static MB_RuleConfigMgr* instance = NULL;
        if(NULL == instance)
        {
            instance = new MB_RuleConfigMgr;
            instance->loadData();
        }
        return instance;
    }
    void loadData()
    {
        m_pArray->removeAllObjects();
        
        MB_XmlFile* pFile = MB_XmlFile::create("config/rulefight.xml");
        CCArray* pArray = CCArray::create();
        
        if(pFile->queryNodesByName("rulefight|item", pArray))
        {
            MB_XmlNode* pTemp = NULL;
            std::string text;
            CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pTemp)
            {
                MB_RuleFightConfig* p = new MB_RuleFightConfig;
                p->init(pTemp);
                m_pArray->addObject(p);
                CC_SAFE_RELEASE_NULL(p);
            }
        }
    }
    
    MB_RuleFightConfig* queryByScore(int score)
    {
        MB_RuleFightConfig* obj = NULL;
        CCARRAY_FOREACH_4TYPE(m_pArray, MB_RuleFightConfig*, obj)
        {
            if(obj->getMinScore() <= score && obj->getMaxScore() > score)return obj;
        }
        
        //特殊处理
        if(score)
        {
            return (MB_RuleFightConfig*)m_pArray->objectAtIndex(m_pArray->count()-1);
        }
        return NULL;
    }
private:
    CCArray* m_pArray;
};

#endif /* defined(__ProjectMB__MB_RuleFightProtocol__) */










