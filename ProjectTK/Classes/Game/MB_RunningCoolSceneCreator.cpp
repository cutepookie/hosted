//
//  MB_RunningCoolSceneCreator.cpp
//  ProjectMB
//
//  Created by wenyong on 14-11-26.
//
//

#include "MB_RunningCoolSceneCreator.h"

bool MB_RunningCoolSceneCreator::init()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fishing.plist");
    return true;
}

CCNode* MB_RunningCoolSceneCreator::createGrassLand()
{
    CCSprite* pSprite = NULL;
    float width = 2000;
    CCSize sz = CCDirector::sharedDirector()->getWinSize();
    CCLayer* pContainer = CCLayer::create();
    pSprite = createElementByName();
    pContainer->addChild(pSprite);
    pSprite->setPositionX(0);
    if (pSprite)
    {
        pContainer->setContentSize(CCSizeMake(width, pSprite->getContentSize().width));
    }
    
    return pContainer;
}

CCSprite* MB_RunningCoolSceneCreator::createElementByName()
{
    CCSprite* pSprite = CCSprite::create("bg/bg_cloud_04.png");
    pSprite->setAnchorPoint(ccp(0, 0));
//    CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pName);
//    if (pFrame)
//    {
//        pSprite->setDisplayFrame(pFrame);
//    }
//    else
//    {
//         MB_RunningCoolSceneCreator::init();
//        createElementByName(pName);
//    }
    return pSprite;
}
void MB_RunningCoolSceneCreator::randomProperty(CCSprite* pNode)
{
    bool bFlip = rand()%1;
    pNode->setFlipX(bFlip);
    
    static float scale[] = {0.7,0.8,0.9,1.0};
    pNode->setScale(scale[rand()%4]);
    
}
