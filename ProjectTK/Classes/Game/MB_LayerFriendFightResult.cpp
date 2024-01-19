//
//  MB_LayerFriendFightResult.cpp
//  ProjectMB
//
//  Created by yuanwugang on 15-3-17.
//
//

#include "MB_LayerFriendFightResult.h"
#include "MB_CommonType.h"
#include "MB_Audio.h"


MB_LayerFriendFightResult::MB_LayerFriendFightResult()
{
    m_pTTFReputation = NULL;
    m_pTTFCoin = NULL;
    m_pSpr1 = NULL;
    m_pSpr2 = NULL;
    m_nCoin = 0;
    m_nReputation = 0;
}
MB_LayerFriendFightResult::~MB_LayerFriendFightResult()
{
    CC_SAFE_RELEASE_NULL(m_pTTFReputation);
    CC_SAFE_RELEASE_NULL(m_pTTFCoin);
    CC_SAFE_RELEASE_NULL(m_pSpr1);
    CC_SAFE_RELEASE_NULL(m_pSpr2);
}
void MB_LayerFriendFightResult::onResetWnd()
{
    char buf[32];
    sprintf(buf,"%d",m_nReputation);
    m_pTTFReputation->setString(buf);
    sprintf(buf,"%d",m_nCoin);
    m_pTTFCoin->setString(buf);
    m_pSpr1->setPositionX(384+((m_pTTFCoin->getContentSize().width-48)*.4f));
    m_pSpr2->setPositionX(404+((m_pTTFReputation->getContentSize().width-93)*.4f));
}
MB_LayerFriendFightResult* MB_LayerFriendFightResult::create(bool isWin,int coin,int reputation)
{
    MB_LayerFriendFightResult* pInstance = new MB_LayerFriendFightResult;
    if (pInstance && pInstance->init(isWin,coin,reputation))
    {
        pInstance->autorelease();
        return pInstance;
    }
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;

}
bool MB_LayerFriendFightResult::init(bool isWin,int coin,int reputation)
{
    m_nCoin = coin;
    m_nReputation = reputation;
    CCNode* pNode = NULL;
    if(isWin)
    {
       pNode = loadResource("res/pvp_friend_layer_win.ccbi");
    }
    else
    {
       pNode = loadResource("res/pvp_friend_layer_lose.ccbi");
    }
    if(pNode)
    {
        addChild(pNode);
        onResetWnd();
        return true;
    }
    return false;
}
bool MB_LayerFriendFightResult::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFReputation",CCLabelBMFont*,m_pTTFReputation);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFCoin",CCLabelBMFont*,m_pTTFCoin);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpr1",CCNode*,m_pSpr1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpr2",CCNode*,m_pSpr2);
    
    return false;
}
SEL_MenuHandler MB_LayerFriendFightResult::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCompareClicked",MB_LayerFriendFightResult::onCompareClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onBackClicked",MB_LayerFriendFightResult::onBackClicked);
    return NULL;
}
SEL_CCControlHandler MB_LayerFriendFightResult::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{

    return NULL;
}
    

void MB_LayerFriendFightResult::onCompareClicked(CCObject* pSender)
{
    MB_TeamData::getInstance()->sendpet_view_other(MB_FriendMgr::getInstance()->getFightRoleID(),0);
}
void MB_LayerFriendFightResult::onBackClicked(CCObject* pSender)
{
    PlayBackGround(kmBackGround_Normal);
    CCDirector::sharedDirector()->popScene();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}
