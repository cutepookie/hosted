//
//  MB_LayerResultChangeCoin.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14-9-29.
//
//

#include "MB_LayerResultChangeCoin.h"

MB_LayerResultChangeCoin::MB_LayerResultChangeCoin()
{
    m_pAddCoinLabel = NULL;
    m_pCoinLabel = NULL;
    m_bClickedBack = false;
}

MB_LayerResultChangeCoin::~MB_LayerResultChangeCoin()
{
    CC_SAFE_RELEASE_NULL(m_pAddCoinLabel);
    CC_SAFE_RELEASE_NULL(m_pCoinLabel);
}

void MB_LayerResultChangeCoin::onResetWnd()
{
}
bool MB_LayerResultChangeCoin::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pAddCoinLabel",CCLabelBMFont*,m_pAddCoinLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pCoinLabel",CCLabelBMFont*,m_pCoinLabel);
    return false;
}
SEL_MenuHandler MB_LayerResultChangeCoin::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}
SEL_CCControlHandler MB_LayerResultChangeCoin::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onBackClicked",MB_LayerResultChangeCoin::onBackClick);
    return NULL;
}

void MB_LayerResultChangeCoin::onBackClick(CCObject* pSender)
{
    if(m_bClickedBack)return;
    m_bClickedBack = true;
    PlayBackGround(kmBackGround_Normal);
    CCDirector::sharedDirector()->popScene();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}


MB_LayerResultChangeCoin  * MB_LayerResultChangeCoin::create(int rewardCoin,int addCoin)
{
    MB_LayerResultChangeCoin * ptr = new MB_LayerResultChangeCoin();
    if(ptr && ptr->init(rewardCoin, addCoin))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}

bool MB_LayerResultChangeCoin::init(int rewardCoin,int addCoin)
{
    MB_ResWindow::init();
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    CCNode * node = ccbReader->readNodeGraphFromFile("res/pve_layer_change_coin.ccbi",this);
    this->addChild(node);
    
    ccbReader->release();
    
    char databuf[50];
    sprintf(databuf, "%d",rewardCoin);
    m_pCoinLabel->setString(databuf);
    sprintf(databuf, "%d",addCoin);
    m_pAddCoinLabel->setString(databuf);
    return true;
}

