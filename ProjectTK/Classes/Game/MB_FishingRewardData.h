//
//  MB_LayerFishing.h
//  ProjectMB
//
//  Created by yuanwugang on 14-10-8.
//
//

#ifndef __ProjectMB__MB_LayerFishing__
#define __ProjectMB__MB_LayerFishing__

#include "MB_FunctionMainWnd.h"
class MB_AdventureEntry;

class RewardTempleteValue;
class MB_FishingRewardData : public CCObject
{
public:
    MB_FishingRewardData(){m_pArray = new CCArray();};
    ~MB_FishingRewardData(){CC_SAFE_RELEASE_NULL(m_pArray);};
    CCArray* getRewardArray(){return m_pArray;};
    void addRewardItem(CCObject* item)
    {
        if(m_pArray != NULL && item != NULL)
        {
            m_pArray->addObject(item);
        }
            
    };
    CC_SYNTHESIZE(uint32_t,m_uRoleExp,RoleExp);
    CC_SYNTHESIZE(uint32_t,m_uCoin,Coin);
    CC_SYNTHESIZE(uint8_t,m_uCrit,Crit);
private:
    CCArray*    m_pArray;
};


#endif /* defined(__ProjectMB__MB_LayerFishing__) */
