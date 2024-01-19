//
//  CCFunctionInterface.cpp
//  ProjectTK
//
//  Created by crimoon00007 on 14-2-28.
//
//

#include "CCFunctionEntryInterface.h"
#include "Game.h"
#include "MB_FunctionConfig.h"
#include "MB_FunctionActivatedTip.h"
#include "MB_FunctionEntranceWnd.h"
#include "MB_TutorialMgr.h"
using namespace NSGameFunction;

void CCFunctionInterface::onEntryClicked(CCObject* pSender)
{
    TutorialTriggerComplete;
    
    MB_FunctionItem* pFunctionItem = MB_FunctionConfigure::getInstance()->queryFunctionItemByType(getFunctionType());
    if(pFunctionItem)
    {
        if(pFunctionItem->getNeedLevel()>MB_RoleData::getInstance()->getLevel())
        {
            char databuf[40];
            sprintf(databuf, "该功能将在%d级开放",pFunctionItem->getNeedLevel());
            MB_Message::sharedMB_Message()->showMessage(databuf);
        }
        else
        {
            MB_ResWindow* pWnd = createFunctionDialog();
            if (pWnd)
            {
                replaceMainSceneSubLayer(pWnd);
            }
        }
    }
    
//    pWnd = dynamic_cast<MB_FunctionEntranceWnd*>(pSender);
//    if (pWnd)
//    {
//        pWnd->onResetWnd();
//    }
}

void CCFunctionInterface::replaceMainSceneLayer(MB_ResWindow* pWnd)
{
    MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
    if (pScene)
    {
        pScene->replaceMainLayer(pWnd);
    }
}

void CCFunctionInterface::replaceMainSceneSubLayer(MB_ResWindow* pWnd)
{
    MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
    if (pScene)//
    {
        pScene->replaceSubLayer(pWnd);
    }
}

void CCFunctionInterface::goFunctionHome()
{
    MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
    if (pScene)//
    {
        pScene->goLayerHome();
    }
}
void CCFunctionInterface::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    
    //將socket數据读取到序列化結构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议號
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    onMsgDeliver(Msg,recvPacket);
}

void CCFunctionInterface::onCloseMainDialog(CCObject* pSender)
{
    MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
    if (pScene)
    {
        pScene->goLayerHome();
    }
}

MB_ResWindow* CCFunctionInterface::getCurrentFunctionWnd()
{
    MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
    if (pScene)
    {
        return pScene->getSubLayer();//pScene->getFunctionWindow();//
    }
    
    return NULL;
}
MB_FunctionActivatedTip* CCFunctionInterface::createFunctionTipsByLevel(int nRoleLevel)
{
    MB_FunctionItem* pItem = MB_FunctionConfigure::getInstance()->queryFunctionItemByType(getFunctionType());
    if (pItem)
    {
        if(pItem->getNeedLevel() == nRoleLevel && pItem->getActivateCcbi().length()!=0)
        {
             MB_FunctionActivatedTip* pWnd = MB_FunctionActivatedTip::create(pItem->getActivateCcbi().c_str());
            if (pWnd)
            {
                pWnd->setFunctionInterface(this);
                return pWnd;
            }
        }
    }
    return NULL;
}
bool CCFunctionInterface::onRoleLevelUp(int nRoleLevel)
{
    MB_FunctionActivatedTip* pWnd = createFunctionTipsByLevel(nRoleLevel);
    if (pWnd)
    {
        pWnd->setFunctionInterface(this);
        CCDirector::sharedDirector()->getRunningScene()->addChild(pWnd,Z_ORDER_OUTSHOW);
        return true;
    }
    return false;
}
void CCFunctionInterface::onEnterThisFunction(CCObject* pSender)
{
    onEntryClicked(pSender);
}

void CCFunctionInterface::removeUnusedResource()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void CCActivityInterface::onEntryClicked(CCObject* pSender)
{
    
}

void CCFunctionWnd::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    
    //將socket數据读取到序列化結构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议號
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    onMsgDeliver(Msg,recvPacket);
}

