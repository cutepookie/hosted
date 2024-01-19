//
//  MB_RunningCoolSceneCreator.h
//  ProjectMB
//
//  Created by wenyong on 14-11-26.
//
//

#ifndef __ProjectMB__MB_RunningCoolSceneCreator__
#define __ProjectMB__MB_RunningCoolSceneCreator__

#include <cocos2d.h>
USING_NS_CC;

class MB_RunningCoolSceneCreator
{
public:
    static bool init();
    static CCNode* createGrassLand();
private:
    static void randomProperty(CCSprite* pNode);
    static CCSprite* createElementByName();
};

#endif /* defined(__ProjectMB__MB_RunningCoolSceneCreator__) */
