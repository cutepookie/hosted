//
//  MB_SceneRoleDemoFight.cpp
//  ProjectMB
//
//  Created by wenyong on 15-1-22.
//
//

#include "MB_SceneRoleDemoFight.h"
#include "MB_DefineProto.h"
#include "MB_FunctionModule.h"
#include "MB_SceneRoleCreate.h"
#include "MB_SceneGame.h"
MB_SceneRoleDemoFight::MB_SceneRoleDemoFight()
{
    SOCKET_MSG_REGIST(SC_ROLE_DEMO_FIGHT, MB_SceneRoleDemoFight);
}
MB_SceneRoleDemoFight::~MB_SceneRoleDemoFight()
{
    SOCKET_MSG_UNREGIST(SC_ROLE_DEMO_FIGHT);
}

CCScene* MB_SceneRoleDemoFight::scene()
{
    CCScene* p = CCScene::create();
    if (p)
    {
        MB_SceneRoleDemoFight* pInstance = MB_SceneRoleDemoFight::create();
        if (pInstance)
        {
            p->addChild(pInstance);
            pInstance->start();
            return p;
        }
    }
    return NULL;
}

void MB_SceneRoleDemoFight::start()
{
    send_role_demo_fight();
}

void MB_SceneRoleDemoFight::send_role_demo_fight()
{
    SOCKET_REQUEST_START(CS_ROLE_DEMO_FIGHT);
    packet->writeU8(1);
    SOCKET_REQUEST_END(SC_ROLE_DEMO_FIGHT,NULL);
}


void MB_SceneRoleDemoFight::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    
    //将socket数据读取到序列化结构
    MB_MsgBuffer* pRecv = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    pRecv->Reset();
    pRecv->skipU16();
    pRecv->skipU8();
    pRecv->readU16(&Msg);
    
    if (Msg == SC_ROLE_DEMO_FIGHT)
    {
        recv_role_demo_fight(pRecv);
    }
}


/*
 message	sc_role_demo_fight[id=10185]{
 required	int8				type		=1;//演示战斗的序号
 repeated	sc_fight_request	fightInfo=2;//战斗的具体信息
 }
 */
void MB_SceneRoleDemoFight::recv_role_demo_fight(MB_MsgBuffer* pRecv)
{
    uint8_t u8;
    pRecv->readU8(&u8);
    uint16_t count = 0;
    pRecv->readU16(&count);
    if (count == 0)
    {
        CCDirector::sharedDirector()->popToRootScene();
        CCScene* pScene = MB_SceneRoleCreate::scene();
        CCDirector::sharedDirector()->replaceScene(pScene);
        return;
    }
    
    MB_NetStructFight pFight;
    recvfight* pFightStruct = pFight.recvfight_request(pRecv);
    pFightStruct->type = kFightResultTypeDemoFight;
    if (pFightStruct)
    {
        m_bIsDemoFight = true;
        CCScene* pScene = MB_SceneGame::scene(pFightStruct);
        pScene = CCTransitionCrossFade::create(0.3, pScene);
        CCDirector::sharedDirector()->popToRootScene();
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
    else
    {
        CCDirector::sharedDirector()->popToRootScene();
        CCScene* pScene = MB_SceneRoleCreate::scene();
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}
