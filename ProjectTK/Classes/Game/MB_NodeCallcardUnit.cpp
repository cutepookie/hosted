//
//  MB_NodeCallcardUnit.cpp
//  ProjectMB
//
//  Create by chk on 5/9/2014.
//
//
#include "MB_NodeCallcardUnit.h"
#include "MB_RefreshShopProtocol.h"
#include "MB_ItemData.h"
#include "MB_LayerRefreshShop.h"
#include "MB_RefreshShopInterface.h"
#include "MB_LayerItemDetail.h"
#include "MB_LayerToyShopMain.h"
MB_NodeCallcardUnit::MB_NodeCallcardUnit()
{
    layerToyShopMain = NULL;
    m_pNeedCallTimesLabel	 = NULL;
    m_pslfCallBallCountLabel= NULL;
    m_pShielding = NULL;
    for (int i = 0; i < 3; ++i)m_pCostLabels[i] = NULL;
}
MB_NodeCallcardUnit::~MB_NodeCallcardUnit()
{
    CC_SAFE_RELEASE_NULL(m_pNeedCallTimesLabel);
    CC_SAFE_RELEASE_NULL(m_pslfCallBallCountLabel);
        CC_SAFE_RELEASE_NULL(m_pShielding);
    
    for (int i = 0; i < 3; ++i)CC_SAFE_RELEASE_NULL(m_pCostLabels[i]);
}
MB_NodeCallcardUnit* MB_NodeCallcardUnit::create()
{
    MB_NodeCallcardUnit* layer = new MB_NodeCallcardUnit();
    if(layer)
    {
        layer->init();
        layer->autorelease();
        return layer;
    }
    CC_SAFE_RELEASE_NULL(layer);
    return NULL;
}
bool MB_NodeCallcardUnit::init()
{
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/shop_layer_callcard_unit.ccbi", this);
    CC_SAFE_RELEASE(pCCBReader);
    
    addChild(pNode);
    return true;
}
bool MB_NodeCallcardUnit::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    TutorialAssignLayerWindow
    char buff[20] = { 0 };
    
    for (int i = 0; i < 3; ++i)
    {
        sprintf(buff, "callelfCost%d", i);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, buff, CCLabelBMFont*, m_pCostLabels[i]);
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "NeedCallTimesLabel", CCLabelBMFont*, m_pNeedCallTimesLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "slfCallBallCount", CCLabelBMFont*, m_pslfCallBallCountLabel);
    return false;
}
SEL_CCControlHandler MB_NodeCallcardUnit::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCallElfClicked", MB_NodeCallcardUnit::onCallElfClicked);
    return NULL;
}
void MB_NodeCallcardUnit::onCallElfClicked(CCObject* pSender)
{
    layerToyShopMain->onCallElfClicked(pSender);
}

