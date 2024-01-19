//
//  MB_LayerBudokanSweep.h
//  ProjectMB
//
//  Created by yuanwugang on 15-2-26.
//
//

#ifndef __ProjectMB__MB_LayerBudokanSweep__
#define __ProjectMB__MB_LayerBudokanSweep__

#include "MB_LayerSweep.h"

class MB_LayerBudokanSweep :public MB_LayerSweep
{
public:
    MB_LayerBudokanSweep();
    ~MB_LayerBudokanSweep();
    
    static MB_LayerBudokanSweep * create(p_reward *pReward,uint16_t length);
    virtual bool init(p_reward *pReward,uint16_t length);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
protected:
    virtual void showOver(float);
    virtual void checkSweepLevelUp(){};
private:
    CCLabelTTF* m_pTTFReward;
    CCSprite*   m_pSpriteReward;
};

#endif /* defined(__ProjectMB__MB_LayerBudokanSweep__) */
