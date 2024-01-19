//
//  MB_TrainerRoadConfigure.h
//  ProjectMB
//
//  Created by wenyong on 15-1-16.
//
//

#ifndef __ProjectMB__MB_TrainerRoadConfigure__
#define __ProjectMB__MB_TrainerRoadConfigure__

#include "MB_ClientData.h"
#include "MB_SingletonClass.h"

class MB_TrainerRoadDungeon : public MB_ClientData
{
public:
    virtual bool init(MB_XmlNode* pNode);
    MB_TrainerRoadDungeon();
private:
    CC_SYNTHESIZE_READONLY(uint16_t, m_nId, Id);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(std::string, m_nHid, Hid);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(std::string, m_szName, Name);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(CCPoint,m_pLocation,Location);
};

class MB_TrainerRoadRewardBox : public MB_ClientData
{
public:
    virtual bool init(MB_XmlNode* pNode);
    MB_TrainerRoadRewardBox();
private:
    CC_SYNTHESIZE_READONLY(uint16_t, m_nId, Id);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(CCPoint,m_pLocation,Location);
};


//class MB_TrainerRoadPage : public MB_ClientData
//{
//public:
//    MB_TrainerRoadPage();
//    virtual ~MB_TrainerRoadPage();
//    virtual bool init(MB_XmlNode* pNode);
//private:
//    CC_SYNTHESIZE_PASS_BY_REF(std::string, m_szFile, File);
//    int         m_nIndex;
//    CC_SYNTHESIZE_READONLY(CCArray*, m_pDungeons, Dungeons);
//    CC_SYNTHESIZE_READONLY(CCArray*, m_pRewardBoxes, RewardBoxes);
//};

class MB_TrainerRoadConfigure : public MB_ClientData
{
public:
    friend class MB_Singleton<MB_TrainerRoadConfigure>;
    virtual ~MB_TrainerRoadConfigure();
    virtual bool init(MB_XmlNode* pNode);
protected:
    bool load();
private:
    MB_TrainerRoadConfigure();
private:
    CC_SYNTHESIZE_READONLY(CCArray*, m_pDungeons,Dungeons);
    CC_SYNTHESIZE_READONLY(CCArray*, m_pBoxs,Box);
};
typedef MB_Singleton<MB_TrainerRoadConfigure> MB_TrainerRoadConfig;
#endif /* defined(__ProjectMB__MB_TrainerRoadConfigure__) */
