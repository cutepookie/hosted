//
//  MB_NodeRankUnit.h
//  ProjectMB
//
//  Create by wenyong on 24/12/2014.
//
//
#ifndef __ProjectMB__MB_NodeRankUnit__
#define __ProjectMB__MB_NodeRankUnit__

#include "MB_ResWindow.h"
class MB_RankData;
class MB_NodeRankUnit : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    CREATE_FUNC(MB_NodeRankUnit);
	MB_NodeRankUnit();
	virtual ~MB_NodeRankUnit();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void setData(MB_RankData* pData);
    const static CCSize& getNodeSize();
    virtual void setDesc(MB_RankData* pData);
protected:
    void onIconClicked(CCObject* pSender);
    void onInfoClicked(CCObject* pSender);
    virtual void setBase(MB_RankData* pData);
protected:
    CCNode*	m_pNodeSize;
    CCLabelBMFont*	m_pNodeRankNum;
    CCSprite*	m_pSpriteFrame;
    CCSprite*	m_pRoleHeader;
    CCSprite*   m_pbgSpr;
    CCLabelTTF* m_pDesc0;
    CCLabelBMFont* m_pDesc1;
    CCLabelTTF* m_pDesc2;
    CCLabelTTF* m_pDesc3;
    CCLabelBMFont*	m_pNodeLv;
    CCNode* m_pStar;
    CCSprite*   m_pPaiMingSpr;
    MB_RankData* m_pRankData;
    CCNode* m_pBg1;
    CCNode* m_pBg2;
};

class MB_NodeRankArena : public MB_NodeRankUnit
{
public:
    CREATE_FUNC(MB_NodeRankArena);
    virtual bool init();
    virtual void setDesc(MB_RankData* pData);
};

class MB_NodeRankPower : public MB_NodeRankUnit
{
public:
    CREATE_FUNC(MB_NodeRankPower);
    virtual bool init();
    virtual void setDesc(MB_RankData* pData);
};

class MB_NodeRankAbsolved : public MB_NodeRankUnit
{
public:
    CREATE_FUNC(MB_NodeRankAbsolved);
    virtual bool init();
    virtual void setDesc(MB_RankData* pData);
};

class MB_NodeRankLevel : public MB_NodeRankUnit
{
public:
    CREATE_FUNC(MB_NodeRankLevel);
    virtual bool init();
    virtual void setDesc(MB_RankData* pData);
};

#endif /* defined(__ProjectMB__MB_NodeRankPvp__) */
