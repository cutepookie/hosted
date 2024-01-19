//
//  MB_NodeRewardCard.h
//  ProjectPM
//
//  Create by WenYong on 23/7/2014.
//
//
#ifndef __ProjectMB__MB_NodeRewardCard__
#define __ProjectMB__MB_NodeRewardCard__

#include "MB_ResWindow.h"

/*
 enum kRewardValueType {
 kRewardValueTypeItem = 1,
 kRewardValueTypePet,
 };
 */
class MB_RewardDataDetail:public CCObject
{
public:
    CREATE_FUNC(MB_RewardDataDetail);
    MB_RewardDataDetail()
    {
        m_nTypeID = 0;
        m_nType = 0;
        m_nRank = 0;
        m_nLevel = 1;
    }
    virtual bool init()
    {
        return true;
    }
    uint16_t m_nTypeID;
    uint16_t m_nType;
    uint16_t m_nRank;
    uint32_t m_nLevel;
};
class MB_NodeRewardCard : public MB_ResWindow,public CCBMemberVariableAssigner
{
public:
	MB_NodeRewardCard();
	virtual ~MB_NodeRewardCard();
    static MB_NodeRewardCard* create(MB_RewardDataDetail* pData);
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void setDetail(uint16_t kType,uint16_t nTypeID,uint16_t nRank=0,uint32_t nLevel=1);
    static CCSize& getNodeSize();
protected:
    virtual void updateItem();
    virtual void updatePet();
protected:
    uint16_t    m_nTypeID;
    uint16_t    m_nType;
    uint16_t    m_nRank;
    uint32_t    m_nLevel;
    CCNode*     m_pNodeSize;
    CCNode*     m_pNodeItem;
    CCNode*     m_pNodePet;
};
#endif /* defined(__ProjectMB__MB_NodeRewardCard__) */
