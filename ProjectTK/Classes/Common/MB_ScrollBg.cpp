#include "MB_ScrollBg.h"


MB_ScrollBg::MB_ScrollBg(ScrollBgDiction _sbd, float _speed,int index)
{
    sbd = _sbd;
    speed = _speed;
    bgIndex = index;
}


MB_ScrollBg* MB_ScrollBg::create(ScrollBgDiction _sbd, float _speed,int index){
    MB_ScrollBg *ptr = new MB_ScrollBg(_sbd, _speed,index);
    if (ptr && ptr->init()){
        
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}

bool MB_ScrollBg::init(){
    winSize = CCDirector::sharedDirector()->getWinSize();
    CCRect rect;
    if (bgIndex==0) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("mail.plist");
        rect = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("pattern_bg_large.png")->getRect();
    }else if (bgIndex==1)
    {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("xuanguan.plist");
        rect = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bg_battle_ready.png")->getRect();
    }
    else if (bgIndex==2) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("battle2.plist");
        rect = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tmzz_bg_result.png")->getRect();
    }
    else if (bgIndex==3) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("jueseqianghua.plist");
        rect = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bg_cha_qianghua.png")->getRect();
    }
    else if (bgIndex==4) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("functions.plist");
        rect = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bg_shilian.png")->getRect();
    }
    
    sprSize = rect.size - CCSize(2,2);
    int tag = 0;
    int num = winSize.height/sprSize.height+1;
    int num2  =num*num;
    for (int i = 0; i < num2; i++) {
        switch (sbd) {
            case left_top:
                createSpr(ccp(i % num * sprSize.width, winSize.height - (i / num + 1)*sprSize.height));
                break;
            case left_bottom:
                createSpr(ccp(i % num * sprSize.width, i / num * sprSize.height));
                break;
            case right_top:
                createSpr(ccp(winSize.width - (i % num + 1)*sprSize.width, winSize.height - (i / num + 1)*sprSize.height));
                break;
            case right_bottom:
                createSpr(ccp(winSize.width - (i % num + 1)*sprSize.width, i / num * sprSize.height));
                break;
        }
    }
    if (speed > 0) {
        scheduleUpdate();
    }
    return true;
}

void MB_ScrollBg::createSpr(CCPoint p)
{
    CCSprite* bgspr;
    if (bgIndex==0) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("mail.plist");
        bgspr = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("pattern_bg_large.png"));
    }
    else if (bgIndex==1) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("xuanguan.plist");
        bgspr = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bg_battle_ready.png"));
    }
    else if (bgIndex==2) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("battle2.plist");
        bgspr = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tmzz_bg_result.png"));
    }
    else if (bgIndex==3) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("jueseqianghua.plist");
        bgspr = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bg_cha_qianghua.png"));
    }
    else if (bgIndex==4) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("functions.plist");
        bgspr = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bg_shilian.png"));
    }
    
    bgspr->setAnchorPoint(ccp(0, 0));
    bgspr->setTag(0);
    
    switch (sbd) {
        case left_top:
            if (p.x + sprSize.width<winSize.width + 10) {
                bgspr->setTag(bgspr->getTag() + 1);
            }
            if (p.y>-10) {
                bgspr->setTag(bgspr->getTag() + 10);
            }
            break;
        case left_bottom:
            if (p.x + sprSize.width < winSize.width + 10) {
                bgspr->setTag(bgspr->getTag() + 1);
            }
            if (p.y + sprSize.height<winSize.height + 10) {
                bgspr->setTag(bgspr->getTag() + 10);
            }
            break;
        case right_top:
            if (p.x>-10) {
                bgspr->setTag(bgspr->getTag() + 1);
            }
            if (p.y > -10) {
                bgspr->setTag(bgspr->getTag() + 10);
            }
            break;
        case right_bottom:
            if (p.x > -10) {
                bgspr->setTag(bgspr->getTag() + 1);
            }
            if (p.y + sprSize.height < winSize.height + 10) {
                bgspr->setTag(bgspr->getTag() + 10);
            }
            break;
    }
    bgspr->setPosition(p);
    addChild(bgspr);
}

void MB_ScrollBg::update(float dt)
{
    std::vector<CCPoint> vp;
    std::vector<CCNode*> vn;
    CCObject* pObj = NULL;
    CCArray* pChildren = this->getChildren();
    CCARRAY_FOREACH(pChildren, pObj)
    {
        CCNode* pChild = (CCNode*)pObj;
        switch (sbd) {
            case left_top:
                pChild->setPosition(pChild->getPosition() + ccp(-speed, speed));
                if (pChild->getTag() % 10 != 1 && pChild->getPositionX() + sprSize.width<winSize.width + 10) {
                    pChild->setTag(pChild->getTag() + 1);
                    vp.push_back(ccp(pChild->getPositionX() + sprSize.width, pChild->getPositionY()));
                }
                else if (pChild->getTag() / 10 != 1 && pChild->getPositionY()>-10) {
                    pChild->setTag(pChild->getTag() + 10);
                    vp.push_back(ccp(pChild->getPositionX(), pChild->getPositionY() - sprSize.height));
                }
                if (pChild->getPositionX() + sprSize.width<0 || pChild->getPositionY()>winSize.height) {
                    vn.push_back(pChild);
                }
                break;
            case left_bottom:
                pChild->setPosition(pChild->getPosition() + ccp(-speed, -speed));
                if (pChild->getTag() % 10 != 1 && pChild->getPositionX() + sprSize.width < winSize.width + 10) {
                    pChild->setTag(pChild->getTag() + 1);
                    vp.push_back(ccp(pChild->getPositionX() + sprSize.width, pChild->getPositionY()));
                }
                else if (pChild->getTag() / 10 != 1 && pChild->getPositionY() + sprSize.height < winSize.height + 10) {
                    pChild->setTag(pChild->getTag() + 10);
                    vp.push_back(ccp(pChild->getPositionX(), pChild->getPositionY() + sprSize.height));
                }
                if (pChild->getPositionX() + sprSize.width<0 || pChild->getPositionY() + sprSize.width<0) {
                    vn.push_back(pChild);
                }
                break;
            case right_top:
                pChild->setPosition(pChild->getPosition() + ccp(speed, speed));
                if (pChild->getTag() % 10 != 1 && pChild->getPositionX()>-10) {
                    pChild->setTag(pChild->getTag() + 1);
                    vp.push_back(ccp(pChild->getPositionX() - sprSize.width, pChild->getPositionY()));
                }
                else if (pChild->getTag() / 10 != 1 && pChild->getPositionY()>-10) {
                    pChild->setTag(pChild->getTag() + 10);
                    vp.push_back(ccp(pChild->getPositionX(), pChild->getPositionY() - sprSize.height));
                }
                if (pChild->getPositionX() > winSize.width || pChild->getPositionY() > winSize.height) {
                    vn.push_back(pChild);
                }
                break;
            case right_bottom:
                pChild->setPosition(pChild->getPosition() + ccp(speed, -speed));
                if (pChild->getTag() % 10 != 1 && pChild->getPositionX() > -10) {
                    pChild->setTag(pChild->getTag() + 1);
                    vp.push_back(ccp(pChild->getPositionX() - sprSize.width, pChild->getPositionY()));
                }
                else if (pChild->getTag() / 10 != 1 && pChild->getPositionY() + sprSize.height<winSize.height + 10) {
                    pChild->setTag(pChild->getTag() + 10);
                    vp.push_back(ccp(pChild->getPositionX(), pChild->getPositionY() + sprSize.height));
                }
                if (pChild->getPositionX()>winSize.width || pChild->getPositionY() + sprSize.width < 0) {
                    vn.push_back(pChild);
                }
                break;
        }
    }
    
    for (int i = 0; i < vp.size(); i++)
    {
        createSpr(vp[i]);
    }
    for (int i = 0; i < vn.size(); i++)
    {
        removeChild(vn[i]);
    }
}
