//
//  MB_LayerSelectMonster.cpp
//  ProjectPM
//
//  Created by WenYong on 14-3-25.
//
//

#include "MB_LayerSelectMonster.h"
#include "MB_LayerSelectPetConfirm.h"
#include "Game.h"
#include "MB_ResWindow.h"
#include "MB_SceneLoading.h"
#include "MB_SceneGame.h"
MB_LayerSelectMonster::MB_LayerSelectMonster():m_nCount(0)
{
    m_pInitMonster = NULL;
    m_nSelectIndex = 0;
    m_pAnimation = NULL;
    for (int i = 0;i < 3;i++)
    {
        m_pSpriteNameBG[i] = NULL;
        m_pSpriteBG[i] = NULL;
        m_pSpriteCard3[i] = NULL;
    }
}

MB_LayerSelectMonster::~MB_LayerSelectMonster()
{
    CC_SAFE_RELEASE_NULL(m_pAnimation);
    CC_SAFE_DELETE_ARRAY(m_pInitMonster);
    for (int i = 0;i < 3;i++)
    {
        CC_SAFE_RELEASE_NULL(m_pSpriteNameBG[i]);
        CC_SAFE_RELEASE_NULL(m_pSpriteBG[i]);
        CC_SAFE_RELEASE_NULL(m_pSpriteCard3[i]);
    }
}

bool MB_LayerSelectMonster::init()
{
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/role_layer_selectcard.ccbi", this);
    if (pNode)
    {
        m_pAnimation = pCCBReader->getAnimationManager();
        CC_SAFE_RETAIN(m_pAnimation);
        char str[10] = "choose1";
        for (int i = 0;i < 3;i++)
        {
            str[6] = '1'+i;
            m_nAnimationID[i] = m_pAnimation->getSequenceId(str);
            m_pAnimation->getSequence(m_nAnimationID[i])->setChainedSequenceId(m_nAnimationID[i]);
            
        }

        CCLayer* pUntouch = NSGameHelper::createDisableTouchLayer();
        addChild(pUntouch);
        addChild(pNode);
    }
    
    CC_SAFE_RELEASE(pCCBReader);
    onMonsterOneClicked(NULL);
    return initConfig();
}
bool MB_LayerSelectMonster::initConfig()
{
    MB_XmlFile* pFile = MB_XmlFile::create("config/firstcard.xml");
    if (pFile)
    {
        CCArray* pArray = CCArray::create();
        if(pFile->queryNodesByName("petlist|pet", pArray))
        {
            MB_XmlNode* pTemp = NULL;
            CC_SAFE_DELETE_ARRAY(m_pInitMonster);
            m_nCount = pArray->count();
            m_pInitMonster = new int[m_nCount];
            int index = 0;
            CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pTemp)
            {
                m_pInitMonster[index++] = pTemp->queryAttributeByName("typeid")->intValue();
            }
            return true;
        }
    }
    
    return false;
}

CCScene* MB_LayerSelectMonster::scene()
{
    CCScene* pScene = CCScene::create();
    
    CCNode* pNode = MB_LayerSelectMonster::create();
    if (pNode)
    {
        pScene->addChild(pNode);
    }
    return pScene;
}

void MB_LayerSelectMonster::onMonsterSelectConfirmed(uint16_t index)
{
    if (index >= m_nCount)
    {
        return;
    }
    
    MB_TARGET_PARENT(MB_SceneRoleCreate, ptr);
    if (ptr!=NULL)
    {
        if(!MB_ServerList::getInstance()->getisCreateRole())
        {
            ptr->onMonsterSeleted(m_pInitMonster[index]);
        }
        else
        {
            sendrole_select_pet(m_pInitMonster[index]);
        }
    }
    else
    {
        sendrole_select_pet(m_pInitMonster[index]);
    }
}
void MB_LayerSelectMonster::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    
    //将socket数据读取到序列化结构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg)
    {
        case SC_ROLE_SELECT_GER:
            recvrole_select_pet(recvPacket);
            break;
        case SC_ROLE_DEMO_FIGHT:
            recv_role_demo_fight(recvPacket);
            break;
        default:
            break;
    }
    
}

/*
 message	sc_role_demo_fight[id=10185]{
 required	int8				type		=1;//演示战斗的序号
 required	sc_fight_request	fightInfo=2;//战斗的具体信息
 }
 */
void MB_LayerSelectMonster::recv_role_demo_fight(MB_MsgBuffer* pRecv)
{
    uint8_t u8;
    pRecv->readU8(&u8);
    MB_NetStructFight pFight;
    recvfight* pFightStruct = pFight.recvfight_request(pRecv);
    if (pFightStruct)
    {
        CCScene* pScene = MB_SceneGame::scene(pFightStruct);
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
    else
    {
        CCScene* pScene = MB_SceneLoading::scene();
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}

bool MB_LayerSelectMonster::sendrole_select_pet(uint16_t uid)
{
    SOCKET_MSG_REGIST(SC_ROLE_SELECT_GER, MB_LayerSelectMonster);
    MB_Message::sharedMB_Message()->showMessage("",5);
    SOCKET_REQUEST_START(CS_ROLE_SELECT_GER);
    packet->writeU16(uid);
    SOCKET_REQUEST_END(SC_ROLE_SELECT_GER, MB_LayerSelectMonster);
    return true;
}

bool MB_LayerSelectMonster::recvrole_select_pet(MB_MsgBuffer *recvPacket)
{
    uint8_t result;
    SOCKET_MSG_UNREGIST(SC_ROLE_SELECT_GER);
    MB_Message::sharedMB_Message()->removeALLMessage();
    if (recvPacket->readU8(&result)) {
        if (result == 1) {
            MB_LOG("pet select succeed.");
            //获取主公和精灵信息
            //MB_RoleData::getInstance()->sendrole_info();
            MB_PetMgr::getInstance();
            //MB_TeamData::getInstance()->sendpet_pos_list();
            //播放下一段剧情
            //CCScene* pScene = MB_SceneStory::scene(kStoryPartLogin3);
            //CCDirector::sharedDirector()->replaceScene(pScene);
            CCScene* layer = MB_SceneLoading::scene();
            CCDirector::sharedDirector()->popToRootScene();
            CCDirector::sharedDirector()->replaceScene(layer);
            return true;
        }
        else
        {
            MB_LOG("pet select failed. errcode:%d",result);
            
            if (result == 2) {
                MB_Message::sharedMB_Message()->showMessage("已经领取过了.");
            }
            else if (result == 3)
            {
                MB_Message::sharedMB_Message()->showMessage("该精灵不能领取.");
            }
            else if (result == 4)
            {
                MB_Message::sharedMB_Message()->showMessage("未知错误.");
            }
        }
    }
    return false;
}
bool MB_LayerSelectMonster::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    char str1[20] = "m_pSpriteNameBG1";
    char str2[20] = "m_pSpriteBG1";
    char str3[20] = "m_pSpriteCard1";
    for (int i = 0;i < 3;i++)
    {
        str1[15] = '1'+i;
        str2[11] = '1'+i;
        str3[13] = '1'+i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, str1, CCScale9Sprite*, m_pSpriteNameBG[i]);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, str2, CCScale9Sprite*, m_pSpriteBG[i]);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, str3, CCSprite*, m_pSpriteCard3[i]);
    }
    return false;
}

SEL_MenuHandler MB_LayerSelectMonster::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClickOne", MB_LayerSelectMonster::onMonsterOneClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClickTwo", MB_LayerSelectMonster::onMonsterTwoClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClickThree", MB_LayerSelectMonster::onMonsterThreeClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerSelectMonster::onCloseClick);
    return NULL;
}

SEL_CCControlHandler MB_LayerSelectMonster::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onEnterClicked", MB_LayerSelectMonster::onEnterClicked);
    return NULL;
}

void MB_LayerSelectMonster::goConfirm(uint16_t nSelectIndex)
{
    if (nSelectIndex > 3)
    {
        return;
    }
    
    onMonsterSelectConfirmed(nSelectIndex);
//    MB_LayerSelectPetConfirm* pWnd = MB_LayerSelectPetConfirm::create(nSelectIndex);
//    if (pWnd)
//    {
//        pushWindow(pWnd);
//    }
//    else
//    {
//        CCLog("[Error]::Can not create confirm window");
//    }
}

void MB_LayerSelectMonster::onEnterClicked(CCObject* pSender)
{
    goConfirm(m_nSelectIndex);
}

void MB_LayerSelectMonster::onCloseClick(CCObject* pSender)
{
    if(MB_ServerList::getInstance()->getisCreateRole())
    {
        MB_Message::sharedMB_Message()->showMessage("请带上一个精灵吧");
    }
    else
    {
        popWindow();
    }
}
void MB_LayerSelectMonster::onMonsterOneClicked(CCObject* pSender)
{
    m_nSelectIndex = 0;
    setShow();
    m_pAnimation->runAnimationsForSequenceNamed("choose1");
    
}

void MB_LayerSelectMonster::onMonsterTwoClicked(CCObject* pSender)
{
    m_nSelectIndex = 1;
    setShow();
    m_pAnimation->runAnimationsForSequenceNamed("choose2");
}

void MB_LayerSelectMonster::onMonsterThreeClicked(CCObject* pSender)
{
    m_nSelectIndex = 2;
    setShow();
    m_pAnimation->runAnimationsForSequenceNamed("choose3");
}

void MB_LayerSelectMonster::setShow()
{
    for (int i = 0;i < 3;i++)
    {
        m_pSpriteNameBG[i]->setOpacity(m_nSelectIndex == i? 255:100);
        m_pSpriteBG[i]->setOpacity(m_nSelectIndex == i? 255:100);
        m_pSpriteCard3[i]->setOpacity(m_nSelectIndex == i? 255:100);
    }
}
