//
//  MB_LayerFishingReward.h
//  ProjectMB
//
//  Created by yuanwugang on 14-10-8.
//
//

#ifndef __ProjectMB__MB_LayerFishingReward__
#define __ProjectMB__MB_LayerFishingReward__

#include "MB_FunctionMainWnd.h"

class MB_FishingRewardData;
class MB_LayerFishingReward : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_LayerFishingReward();
    ~MB_LayerFishingReward();
    static MB_LayerFishingReward* create(MB_FishingRewardData* data);
    virtual bool init(MB_FishingRewardData* data);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    
    virtual void onResetWnd();
    virtual void onExit();
    
    void onAnimationOver();
    
private:
    CCNode*     m_pNodeItem;
    CCLabelTTF* m_pTTFExp;
    CCLabelTTF* m_pTTFCoin;
    CCNode*     m_pNodeCrit1;
    CCNode*     m_pNodeCrit2;
    CCNode*     m_pNodeCrit3;
    CCNode*     m_pNodeGotItem;
    CCBAnimationManager* m_pAnimationMgr;
};
#endif /* defined(__ProjectMB__MB_LayerFishingReward__) */
