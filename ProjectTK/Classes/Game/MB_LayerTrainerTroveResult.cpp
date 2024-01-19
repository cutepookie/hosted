//
//  MB_LayerTrainerTroveResult.cpp
//  ProjectMB
//
//  Created by yuanwugang on 15-2-27.
//
//

#include "MB_LayerTrainerTroveResult.h"
#include "MB_RoleData.h"


MB_LayerTrainerTroveResult::MB_LayerTrainerTroveResult()
{
    m_pTTFCoin = NULL;
    m_pSpr1 = NULL;
    m_bClickedBack = false;
}
MB_LayerTrainerTroveResult::~MB_LayerTrainerTroveResult()
{
    CC_SAFE_RELEASE_NULL(m_pSpr1);
    CC_SAFE_RELEASE_NULL(m_pTTFCoin);
}
MB_LayerTrainerTroveResult* MB_LayerTrainerTroveResult::create(bool bIsWin,int gold)
{
    MB_LayerTrainerTroveResult* ptr = new MB_LayerTrainerTroveResult();
    if (ptr && ptr->init(bIsWin,gold))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}
bool MB_LayerTrainerTroveResult::init(bool bIsWin,int gold)
{
    CCNode* node = MB_ResWindow::loadResource(bIsWin?"res/pve_layer_goldwin.ccbi":"res/pve_layer_goldlose.ccbi");
    if (node != NULL)
    {
        this->addChild(node);
        char str[64];
        sprintf(str,"%d",gold);
        m_pTTFCoin->setString(str);
        
        m_pSpr1->setPositionX(384+((m_pTTFCoin->getContentSize().width-48)*.4f));
        return true;
    }
    return false;
}

bool MB_LayerTrainerTroveResult::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFCoin",CCLabelBMFont*,m_pTTFCoin);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpr1",CCNode*,m_pSpr1);
    
    return false;
}
SEL_MenuHandler MB_LayerTrainerTroveResult::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onBackClick",MB_LayerTrainerTroveResult::onBackClick);
    return NULL;
}
SEL_CCControlHandler MB_LayerTrainerTroveResult::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

void MB_LayerTrainerTroveResult::onBackClick(CCObject* pSender)
{
    if(m_bClickedBack)return;
    m_bClickedBack = true;
    PlayBackGround(kmBackGround_Normal);
    CCDirector::sharedDirector()->popScene();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

