//
//  MB_NodeMonsterSelect.cpp
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-19.
//
//

#include "MB_NodeMonsterSelect.h"
#include "Game.h"

MB_NodeMonsterSelect::MB_NodeMonsterSelect()
{

    m_pAttack = NULL;
    m_pHp = NULL;
    m_bShowTutoril = false;
}

MB_NodeMonsterSelect::~MB_NodeMonsterSelect()
{
    CC_SAFE_RELEASE_NULL(m_pAttack);
    CC_SAFE_RELEASE_NULL(m_pHp);
}


bool MB_NodeMonsterSelect::init(uint64_t nUid,uint16_t nType)
{
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/card_node_select_unit.ccbi", this);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    if (pNode == NULL)
    {
        return false;
    }

    m_nItemUID = nUid;
    m_nType = nType;

    addChild(pNode);

    onResetWnd();

    return true;
}

MB_NodeMonsterSelect* MB_NodeMonsterSelect::create(uint64_t nUid,uint16_t nType,bool showTutoril)
{
    MB_NodeMonsterSelect* pInstance = new MB_NodeMonsterSelect;
    pInstance->m_bShowTutoril = showTutoril;
    if (pInstance && pInstance->init(nUid,nType))
    {
        pInstance->autorelease();
        return pInstance;
    }

    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}

void MB_NodeMonsterSelect::onResetWnd()
{
    MB_NodeSelect::onResetWnd();

    MB_PetData* pData = MB_PetMgr::getInstance()->getPetDataByUID(m_nItemUID);
    if (pData)
    {
        char buff[25] = {};
        sprintf(buff, "%d",pData->getPetHpMax());
        m_pHp->setString(buff);
        sprintf(buff, "%d",pData->getPetAttack());
        m_pAttack->setString(buff);
    }
}

bool MB_NodeMonsterSelect::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    if(m_bShowTutoril)
    {
        if(MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode))
        {
            return true;
        }
    }
    
    if (strcmp(pMemberVariableName, "size") == 0)
    {
        m_nSize = pNode->getContentSize();
        return false;
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btn_1", CCControlButton*, m_pBtn1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_menus", CCNode*, m_pNodeMenu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_buttons", CCNode*, m_pNodeButton);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "name", CCLabelTTF*, m_pName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "text_attack", CCLabelTTF*, m_pAttack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "text_hp", CCLabelTTF*, m_pHp);

    char buff[64] = {};

    for (int i=0; i<7; ++i)
    {
        sprintf(buff,"star%d", i+1);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, buff, CCNode*,m_pStars[i]);
    }

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "IconPos", CCNode*, m_pNodeIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "menu_text", CCLabelTTF*, m_pMenuText);
    return false;
}

SEL_MenuHandler MB_NodeMonsterSelect::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    
    return NULL;
}

SEL_CCControlHandler MB_NodeMonsterSelect::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButton1Clicked", MB_NodeMonsterSelect::onButton1Clicked);
    return NULL;
}

void MB_NodeMonsterSelect::onButton1Clicked(cocos2d::CCObject *pSender)
{
    TutorialTriggerComplete
    
    MB_TARGET_PARENT(MB_NodeSelectDelegate,ptr);
    if (ptr)
    {
        if (getIsInputed())
        {
            ptr->onInputedNodeSelected(m_nItemUID, m_nType);
        }
        else
        {
            ptr->onNodeSelected(m_nItemUID, m_nType);
        }
    }
}