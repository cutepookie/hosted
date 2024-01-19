//
//  MB_RoleSoundSystem.cpp
//  ProjectPM
//
//  Created by WenYong on 14-6-7.
//
//

#include "MB_RoleSoundSystem.h"
#include "MB_FunctionModule.h"

MB_RoleSoundSystem::~MB_RoleSoundSystem()
{
    m_vSound.clear();
}

MB_RoleSoundSystem* MB_RoleSoundSystem::getInstance()
{
    if (m_pThisInstance == NULL)
    {
        m_pThisInstance = new MB_RoleSoundSystem;
        if (!m_pThisInstance->init())
        {
            CCLOG("[Error]:Init RoleSound failed");
        }
        
    }
    return m_pThisInstance;
}

void MB_RoleSoundSystem::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(m_pThisInstance);
}

MB_RoleSoundSystem* MB_RoleSoundSystem::m_pThisInstance = NULL;

MB_RoleSoundSystem::MB_RoleSoundSystem()
{
    m_bCanPlay = true;
    m_nLastSoundID = 0xFEEDBAB;
}

bool MB_RoleSoundSystem::init()
{
    MB_XmlFile* pFile = MB_XmlFile::create("config/UI_music.xml");
    
    if (pFile)
    {
        CCArray* pArray = CCArray::create();
        int key = 0;
        std::string res;
        if(pFile->queryNodesByName("sounds|sound", pArray))
        {
            MB_XmlNode* pNode = NULL;
            CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pNode)
            {
                key = pNode->queryAttributeByName("type")->intValue();
                res = pNode->queryAttributeByName("filepath")->getCString();
                m_vSound.insert(std::make_pair(key, res));
            }
        }
        return true;
    }

    return false;
}
bool MB_RoleSoundSystem::isTutorialSound(int key)
{
    return key > 10000 && key  < 20000;
}
void MB_RoleSoundSystem::lock(int key)
{
    m_bCanPlay = false;
    CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
    pScheduler->scheduleSelector(schedule_selector(MB_RoleSoundSystem::unlock), this, 3.0, false);
}
void MB_RoleSoundSystem::unlock()
{
    CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
    pScheduler->unscheduleSelector(schedule_selector(MB_RoleSoundSystem::unlock), this);
    m_bCanPlay = true;
}

const char* MB_RoleSoundSystem::getFilePathByKey(int key)
{
    std::map<int, std::string>::iterator it = m_vSound.find(key);
    if (it != m_vSound.end())
    {
        return it->second.c_str();
    }
    return "";
}

void MB_RoleSoundSystem::stopLastSound()
{
    MB_Audio::getInstance()->stopEffect(m_nLastSoundID);
}

bool MB_RoleSoundSystem::playRoleSound(int key)
{
    if(!MB_TutorialMgr::getInstance()->HasRoleSound())return true;
    
    std::map<int, std::string>::iterator it = m_vSound.find(key);
    if (it != m_vSound.end())
    {
//        if (isTutorialSound(key))
//        {
//            MB_Audio::getInstance()->playEffect(it->second.c_str());
//            lock(key);
//            return true;
//        }
//        else
        {
            if (m_bCanPlay)
            {
                MB_Audio::getInstance()->stopEffect(m_nLastSoundID);
                m_nLastSoundID = MB_Audio::getInstance()->playEffect(it->second.c_str());
//                lock(key);
                return true;
            }
        }
        return false;
    }
    return false;
}

#define BIND_NODE2KEY(TYPE,NODE,DEST,KEY)     \
if(dynamic_cast<TYPE>(NODE))\
{\
    (DEST) = (KEY);\
    return true;\
}

#include "MB_LayerWorldBossMain.h"
#include "MB_LayerPetCommand.h"
#include "MB_LayerFriend.h"
#include "MB_LayerItemEnhance.h"
#include "MB_LayerTaskMain.h"
#include "MB_ChampionshipFunctionDialog.h"
#include "MB_LayerPerfectRaceMain.h"
#include "MB_LayerToyShopMain.h"
#include "MB_LayerAbsolvedPage.h"
#include "MB_LayerComposeMain.h"
#include "MB_ShopPoints.h"
#include "MB_ShopMystery.h"
#include "MB_LayerRuningCool.h"
#include "MB_LayerWorldBossMain.h"
#include "MB_LayerRegistration.h"
#include "MB_LayerBudokan.h"


bool MB_RoleSoundSystem::queryKeyByNode(CCNode* pNode,int& key)
{
    // 一级界面在此绑定
//    BIND_NODE2KEY(MB_LayerWorldBossMain*, pNode, key, kSoundEnterResearchInstitute);
    BIND_NODE2KEY(MB_LayerWorldBossMain*, pNode, key, kSoundEnterLLTower);
    BIND_NODE2KEY(MB_LayerBudokan*, pNode, key, kSoundEnterAbssy);
    
    BIND_NODE2KEY(MB_LayerTaskMain*, pNode, key, kSoundEnterTask);
    BIND_NODE2KEY(MB_ChampionshipFunctionDialog*, pNode, key, kSoundEnterChampionship);
    //BIND_NODE2KEY(MB_LayerPerfectRaceMain*, pNode, key, kSoundEnterRace);  特殊处理，在MB_PerfaceRaceInterface::goNormalLayer();
//    BIND_NODE2KEY(MB_LayerHomeLandMain*, pNode, key, kSoundEnterHomeLand);
    BIND_NODE2KEY(MB_LayerToyShopMain*, pNode, key, kSoundEnterToy);
//    BIND_NODE2KEY(MB_LayerEventEmperor*, pNode, key, kSoundEnterKing);
    BIND_NODE2KEY(MB_LayerPetCommand*, pNode, key, kSoundEnterFormation);
    BIND_NODE2KEY(MB_LayerRuningCool*, pNode, key, kSoundEnterAdventure);
    BIND_NODE2KEY(MB_LayerFriend*, pNode, key, kSoundEnterFriend);
//    BIND_NODE2KEY(MB_LayerDailyReward*, pNode, key, kSoundEnterLoginReward);
    BIND_NODE2KEY(MB_LayerComposeMain*, pNode, key, kSoundEnterCompose);
    BIND_NODE2KEY(MB_LayerAbsolvedPage*, pNode, key, kSoundEnterPve);
    BIND_NODE2KEY(MB_ShopMystery*, pNode, key, kSoundEnterMysteriousShop);
    BIND_NODE2KEY(MB_ShopPoints*, pNode, key, kSoundEnterShop_3);
    BIND_NODE2KEY(MB_LayerRegistration*, pNode, key, kSoundEnterLoginReward);
    
    
    return false;
}

bool MB_RoleSoundSystem::playRoleSoundByNode(CCNode* pNode)
{
    int key = 0;
    if (queryKeyByNode(pNode, key))
    {
        return playRoleSound(key);
    }
    
    return false;
}
