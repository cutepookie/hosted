

#include "MB_NodeYaoLingDuiWu.h"
#include "MB_LayerGuard.h"
#include "MB_TeamData.h"
#include "MB_LayerGuard.h"
#include "MB_LayerPetEquipment.h"
#include "MB_GuardInterface.h"
MB_NodeYaoLingDuiWu::MB_NodeYaoLingDuiWu(int index){
    m_pRoleIcon = NULL;
    m_pLg = NULL;
    m_pSelectSpr = NULL;
    m_nIndex = index;
}
MB_NodeYaoLingDuiWu::~MB_NodeYaoLingDuiWu(){
    
    CC_SAFE_RELEASE_NULL(m_pRoleIcon);
    CC_SAFE_RELEASE_NULL(m_pSelectSpr);
}

MB_NodeYaoLingDuiWu * MB_NodeYaoLingDuiWu::create(int index){
    
    MB_NodeYaoLingDuiWu *node = new MB_NodeYaoLingDuiWu(index);
    
    if( node && node->init() ){
        
        node->autorelease();
        
        return  node;
    }
    CC_SAFE_DELETE(node);
    return NULL;
}
bool  MB_NodeYaoLingDuiWu::init(){
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/card_node_iconYaoLing.ccbi", this);
    this->addChild(node);
    pCCBReader->release();
    setPetID();
    return true;
}

bool MB_NodeYaoLingDuiWu::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pRoleIcon", CCNode *, m_pRoleIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSelectSpr", CCNode *, m_pSelectSpr);
    
    return  false;
}
SEL_MenuHandler MB_NodeYaoLingDuiWu::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    
    return NULL;
}
SEL_CCControlHandler MB_NodeYaoLingDuiWu::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClickYaoLing",MB_NodeYaoLingDuiWu::onClickYaoLing);
    return NULL;
}

void MB_NodeYaoLingDuiWu::setPetID()
{
    MB_PetGuardData* guardData = MB_GuardInterface::getInstance()->getPetGuardDataByPos(m_nIndex+1);
    if(guardData == NULL)
    {
        m_pRoleIcon->removeAllChildren();
    }else
    {
        uint64_t petId = guardData->getPetUid();
        MB_NodePet * node = MB_NodePet::create(petId);
        node->showLevel(false);
        node->showName(false);
        node->setMenuTouch(false);
        m_pRoleIcon->addChild(node);
    }
}

void MB_NodeYaoLingDuiWu::onClickYaoLing(CCObject * pSender)
{
    if (m_pLg!=NULL) {
        m_pLg->setSelectPetID(m_nIndex);
    }else
    {
        bool isSendZhenxing = false;
        for (int i =0; i<MEMBER_NUM; i++) {
            if ((MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet==NULL&&teamV[i]!=-1) || (MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet!=NULL&&teamV[i] != MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet->getPetID())) {
                isSendZhenxing = true;
                break;
            }
        }
        if (isSendZhenxing) {
            global_layerPetEquipment->isToOnClickGHYSSH = m_nIndex;
            global_layerPetEquipment->sendZhenXing();
            return;
        }
        MB_LayerGuard* layer = MB_LayerGuard::create(m_nIndex);
        if (layer != NULL){
            global_layerPetEquipment->pushWindow(layer, true);
        }
    }
}

