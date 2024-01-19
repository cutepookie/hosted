
#include "MB_NodeYaoLingChoose.h"
#include "Game.h"
#include "MB_RechargeSystem.h"
#include "MB_NodePet.h"
#include "MB_GuardProtocol.h"
#include "MB_GuardInterface.h"
#include "MB_LayerGuard.h"
USING_NS_CC;
USING_NS_CC_EXT;

MB_NodeYaoLingChoose::MB_NodeYaoLingChoose()
{
    m_pScrollmenu = NULL;
    m_pLg = NULL;
    m_pRoleName = NULL;
    m_pAttack = NULL;
    m_pRoleIcon = NULL;
    m_pLabelLevel = NULL;
    m_pHp = NULL;
    m_pNodeSize = NULL;
    m_pTTFGuard = NULL;
}

MB_NodeYaoLingChoose::~MB_NodeYaoLingChoose()
{
    CC_SAFE_RELEASE_NULL(m_pScrollmenu);
    CC_SAFE_RELEASE_NULL(m_pRoleIcon);
    CC_SAFE_RELEASE_NULL(m_pLabelLevel);
    CC_SAFE_RELEASE_NULL(m_pAttack);
    CC_SAFE_RELEASE_NULL(m_pRoleName);
    CC_SAFE_RELEASE_NULL(m_pHp);
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(m_pTTFGuard);
}
CCSize MB_NodeYaoLingChoose::getCellSize(){
    
    return  m_pNodeSize->getContentSize();
}
MB_NodeYaoLingChoose* MB_NodeYaoLingChoose::create(uint64_t petUID)
{
    MB_NodeYaoLingChoose* pNode = new MB_NodeYaoLingChoose();
    pNode->m_nPetUID = petUID;
    if (pNode != NULL && pNode->init()) {
        pNode->autorelease();
        return pNode;
    }
    delete pNode;
    return NULL;
}

bool MB_NodeYaoLingChoose::init()
{
    MB_ResWindow::init();
    
    //init CCBReader
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
 
    char databuf[100];
    sprintf( databuf, "res/yaoling_node_unit.ccbi");
    CCNode *pNode = pCCBReader->readNodeGraphFromFile(databuf, this);
    this->addChild(pNode);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    m_pScrollmenu->setSwallowsTouches(false);
    onResetWnd();
    
    return true;
}

void MB_NodeYaoLingChoose::onResetWnd()
{
    MB_PetData* pData = MB_PetMgr::getInstance()->getPetDataByUID(m_nPetUID);
    if (pData)
    {
        char buff[25] = {};
        sprintf(buff, "%d",pData->getPetAttack());
        m_pAttack->setString(buff);
        sprintf(buff, "%d",pData->getPetHpMax());
        m_pHp->setString(buff);
        sprintf(buff, "Lv.%d",pData->getPetLevel());
        m_pLabelLevel->setString(buff);
        sprintf(buff, "%s",pData->getTemplete()->getPetName());
        m_pRoleName->setString(buff);
        m_pRoleIcon->removeAllChildren();
        MB_NodePet* np = MB_NodePet::create(m_nPetUID);
        np->showLevel(false);
        np->showName(false);
        m_pRoleIcon->addChild(np);
        
        
        MB_PetGuardData* data = MB_GuardInterface::getInstance()->getPetGuardDataByUid(m_nPetUID);
        if(data != NULL)
        {
            m_pTTFGuard->setVisible(true);
            m_pScrollmenu->setVisible(false);
            char str[128];
            TeamDataStruct* teamData = MB_TeamData::getInstance()->getTeamMemberByIndex(data->getPetPos()-1);
            if (teamData != NULL && teamData->m_pPet != NULL)
            {
                MB_PetTemplate* petTemplate =  MB_PetMgr::getInstance()->getPetTemplateByUID(teamData->m_pPet->getPetID());
                if (petTemplate != NULL)
                {
                    char str[128];
                    sprintf(str,"%s的守护",petTemplate->getPetName(NSGameHelper::getShapeTypeByRank(teamData->m_pPet->getPetQuallity())));
                    m_pTTFGuard->setString(str);
                }
            }
        }
    }
}

bool MB_NodeYaoLingChoose::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"roleIcon", CCNode *, m_pRoleIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelLevel", CCLabelBMFont *, m_pLabelLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"text_attack", CCLabelBMFont *, m_pAttack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"text_hp", CCLabelBMFont *, m_pHp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"roleName", CCLabelTTF *, m_pRoleName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize", CCNode *, m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFGuard", CCLabelTTF *, m_pTTFGuard);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"scrollmenu", CCMenu *, m_pScrollmenu);
    return true;
}

SEL_MenuHandler MB_NodeYaoLingChoose::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onChooseClicked",MB_NodeYaoLingChoose::onChooseClicked);
    return NULL;
}
SEL_CCControlHandler MB_NodeYaoLingChoose::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

void MB_NodeYaoLingChoose::onChooseClicked(cocos2d::CCObject *pSender)
{
    m_pLg->setPetGuard(m_nPetUID);
}


