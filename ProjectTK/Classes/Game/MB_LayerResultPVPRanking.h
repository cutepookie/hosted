

#ifndef __ProjectMB__MB_LayerResultPVPRanking__
#define __ProjectMB__MB_LayerResultPVPRanking__

#include "Game.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MB_LayerResultPVPRanking : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_LayerResultPVPRanking();
    ~MB_LayerResultPVPRanking();
    
    static CCScene* scene(p_result_ranking* fightResult);
    static MB_LayerResultPVPRanking* create(p_result_ranking* fightResult);
    
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(p_result_ranking* fightresult);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    virtual void onResetWnd();
    virtual void onFightClicked(CCObject* pSender);
    virtual void onCompareClicked(CCObject* pSender);
    virtual void onBackClicked(CCObject* pSender);
    virtual void onToyShopClicked(CCObject* pSender);
    virtual void onPowerUpClicked(CCObject* pSender);
    
private:
    CCLabelBMFont* m_pTTFyl;
    CCLabelBMFont* m_pTTFRank;
    CCLabelBMFont* m_pTTFRankUp;
protected:
    p_result_ranking* m_pResult;
    bool m_bIsPopScene;

};





class SResultData:public CCObject
{
    CCArray* pReward;//奖励
public:
    bool bWin;
    FightResultType type;       //类型
    uint32_t roleID;            //对方ID
    std::string attackName;
    std::string defenseName;
    std::string pBg;
    
    uint8_t nOldRank;
    uint8_t nNowRank;
    

public:
    SResultData():pBg("pic_map/map_bat_1.png"),pReward(NULL),roleID(0),nOldRank(0),nNowRank(0) {};
    
    SResultData(bool _bWin,FightResultType _type,CCArray* _pReward)
    {
        pReward = _pReward;
        CC_SAFE_RETAIN(pReward);
        bWin = _bWin;
        type = _type;
    }
    
    ~SResultData()
    {
        CC_SAFE_RELEASE(pReward);
    }

    
    void setRewards(CCArray* pArr)
    {
        CC_SAFE_RELEASE(pReward);
        pReward = pArr;
        CC_SAFE_RETAIN(pReward);
    }
    CCArray* getRewards()
    {
        return pReward;
    }
};

class MB_LayerResultCommonFight:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:

    virtual void onFightClicked(CCObject* pSender);
    virtual void onCompareClicked(CCObject* pSender);
    virtual void onBackClicked(CCObject* pSender);
    virtual void onToyShopClicked(CCObject* pSender);
    virtual void onPowerUpClicked(CCObject* pSender);
    virtual void onResetWnd();
    
    MB_LayerResultCommonFight();
    ~MB_LayerResultCommonFight();
    static MB_LayerResultCommonFight* create(SResultData* data);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual bool init(SResultData* data);
private:
    SResultData* m_Data;
    CCLabelBMFont* m_pLabel[3];
    bool m_bIsPopScene;
    CCNode* m_pSpr1;
};
#endif /* defined(__ProjectMB__MB_LayerResultPVPRanking__) */
