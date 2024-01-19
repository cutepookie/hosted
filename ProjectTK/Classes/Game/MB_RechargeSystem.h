//
//  MB_RechargeSystem.h
//  ProjectPM
//
//  Created by WenYong on 14-6-6.
//
//

#ifndef __ProjectMB__MB_RechargeSystem__
#define __ProjectMB__MB_RechargeSystem__

#include "cocos2d.h"
USING_NS_CC;



class MB_ResWindow;
class MB_RechargeSystem:public CCObject
{
public:
    static MB_RechargeSystem* getInstance();
    static void destroyInstance();
    
    ~MB_RechargeSystem();
    bool showRechargeWndByType(int RechargeType,MB_ResWindow* pParent);
private:
    MB_RechargeSystem();
    static MB_RechargeSystem* m_pThisInstance;
private:
    
};

#endif /* defined(__ProjectMB__MB_RechargeSystem__) */
