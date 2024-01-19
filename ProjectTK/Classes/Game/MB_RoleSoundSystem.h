//
//  MB_RoleSoundSystem.h
//  ProjectPM
//
//  Created by WenYong on 14-6-7.
//
//

#ifndef __ProjectMB__MB_RoleSoundSystem__
#define __ProjectMB__MB_RoleSoundSystem__

#include "MB_RoleSoundProtocol.h"
#include "cocos2d.h"
#include <map>
USING_NS_CC;
class MB_ResWindow;
class MB_RoleSoundSystem:public CCObject
{
public:
    ~MB_RoleSoundSystem();
    static MB_RoleSoundSystem* getInstance();
    static void destroyInstance();
    bool playRoleSound(int key);
    bool playRoleSoundByNode(CCNode* pNode);
    bool queryKeyByNode(CCNode* pNode,int& key);
    
    const char* getFilePathByKey(int key);
    void stopLastSound();
protected:
    void lock(int key);
    void unlock();
    bool isTutorialSound(int key);
private:
    static MB_RoleSoundSystem* m_pThisInstance;
    MB_RoleSoundSystem();
    virtual bool init();
    std::map<int,std::string>   m_vSound;
    bool m_bCanPlay;
    int m_nLastSoundID;
};

#define PlayRoleSound(key) MB_RoleSoundSystem::getInstance()->playRoleSound(key)
#define PlayRoleSoundByNode(pNode) MB_RoleSoundSystem::getInstance()->playRoleSoundByNode(pNode)
#endif /* defined(__ProjectMB__MB_RoleSoundSystem__) */
