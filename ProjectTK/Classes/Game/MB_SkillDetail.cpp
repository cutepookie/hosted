//
//  MB_SkillDetail.cpp
//  ProjectPM
//
//  Created by crimoon on 14-4-9.
//
//

#include "MB_SkillDetail.h"
#include "MB_NodeDestiny.h"
#include "MB_NodeSkillContainer.h"
static const uint8_t activateRank[] = {0,0,2,5,10,15,20};
MB_SkillDetail::MB_SkillDetail(uint64_t petID)
{
    m_nPetTypeID = 0;
    m_nPetID = petID;
    m_pContainer = NULL;
    m_pSpr1 = NULL;
    m_pSpr2 = NULL;
}
MB_SkillDetail::MB_SkillDetail(uint16_t petTypeID)
{
    m_nPetID = 0;
    m_nPetTypeID = petTypeID;
    m_pContainer = NULL;
    m_pSpr1 = NULL;
    m_pSpr2 = NULL;
}
MB_SkillDetail::~MB_SkillDetail()
{
    CC_SAFE_RELEASE_NULL(m_pContainer);
    CC_SAFE_RELEASE_NULL(m_pSpr1);
    CC_SAFE_RELEASE_NULL(m_pSpr2);
}
MB_SkillDetail* MB_SkillDetail::create(uint16_t petTypeID, int index)
{
    MB_SkillDetail* ptr = new MB_SkillDetail(petTypeID);
    if (ptr && ptr->init(index))
    {
        ptr->autorelease();
        return ptr;
    }
    else
    {
        delete ptr;
        return NULL;
    }
}
MB_SkillDetail* MB_SkillDetail::create(uint64_t petID,int index)
{
    MB_SkillDetail* ptr = new MB_SkillDetail(petID);
    if (ptr && ptr->init(index))
    {
        ptr->autorelease();
        return ptr;
    }
    else
    {
        delete ptr;
        return NULL;
    }
}
bool MB_SkillDetail::init(int index)
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->addChild(NSGameHelper::createDisableTouchLayer());
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode *pScene = pCCBReader->readNodeGraphFromFile("res/card_layer_skilldetail.ccbi", this);
    this->addChild(pScene);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    if (index==2) {
        m_pSpr1->setVisible(false);
        m_pSpr2->setVisible(true);
    }
    
    m_pScrollView = CCScrollView::create(m_pContainer->getContentSize());
    m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
    m_pContainer->addChild(m_pScrollView);
    
    setContent(index);
    return true;
}
void MB_SkillDetail::setContent(int index)
{
    uint16_t PetQuallity;
    MB_PetTemplate *pTemplate;
    if (m_nPetID == 0) {
        PetQuallity = 1;
        pTemplate = MB_PetMgr::getInstance()->getPetTemplateByID(m_nPetTypeID);
    }else
    {
        MB_PetData* pData = MB_PetMgr::getInstance()->getPetDataByUID(m_nPetID);
        if (pData)
        {
            PetQuallity = pData->getPetQuallity();
        }
        pTemplate = pData->getTemplete();
    }
    if (pTemplate)
    {
        const char* petName = pTemplate->getPetFace(NSGameHelper::getShapeTypeByRank(PetQuallity));
        CCSize sz = CCSize(0,0);
        CCNode* node = CCNode::create();
        node->setAnchorPoint(ccp(0.5,1));
        int tempIndex = 0;
        if (index==1) {
            
            int num = 0;
            for (int i = 2;i < 7;i++) {
                int skillid = pTemplate->getSkillIDByIndex(i);
                MB_SkillData *data = MB_SkillMgr::getInstance()->getSkillDataByID(skillid);
                if (data != NULL)
                {
                    num++;
                }
            }
            for (int i = 2;i < 7;i++) {
                int skillid = pTemplate->getSkillIDByIndex(i);
                MB_SkillData *data = MB_SkillMgr::getInstance()->getSkillDataByID(skillid);
                if (data != NULL)
                {
                    MB_NodeSkillUint* nodeSkills = MB_NodeSkillUint::create(petName, data,i,PetQuallity >= activateRank[i]);
                    if (sz.width==0) {
                        sz = nodeSkills->getContentSize();
                    }
                    node->addChild(nodeSkills);
                    nodeSkills->setPosition(m_pScrollView->getContentSize().width/2,(tempIndex+.5f)*sz.height);
                    tempIndex++;
                }
            }
            
            MB_NodeSkillContainer2* nodeSkill1 = NULL;
            MB_NodeSkillContainer2* nodeSkill2 = NULL;
            MB_SkillData *data = MB_SkillMgr::getInstance()->getSkillDataByID(pTemplate->getSkillIDByIndex(1));
            if (data != NULL)
            {
                nodeSkill1 = MB_NodeSkillContainer2::create(petName,data,MB_NodeSkillContainer2::kTypeSkillBig);
                if (nodeSkill1 != NULL)
                {
                    sz = nodeSkill1->getContentSize();
                    nodeSkill1->setPosition(m_pScrollView->getContentSize().width/2,(tempIndex+.5f)*sz.height);
                    node->addChild(nodeSkill1);
                    tempIndex++;
                }
            }
            data = NULL;
            data = MB_SkillMgr::getInstance()->getSkillDataByID(pTemplate->getSkillIDByIndex(0));
            if (data != NULL)
            {
                nodeSkill2 = MB_NodeSkillContainer2::create(petName,data,MB_NodeSkillContainer2::kTypeSkillNormal);
                if (nodeSkill2 != NULL)
                {
                    nodeSkill2->setPosition(m_pScrollView->getContentSize().width/2,(tempIndex+.5f)*sz.height);
                    node->addChild(nodeSkill2);
                    tempIndex++;
                }
            }
        }else
        {
            MB_NodeDestiny* pNode = NULL;
            float allHeight = 0;
            
            for (int i=0; i<5; ++i)
            {
                MB_DestinyData* data = MB_DestinyMgr::getInstance()->getDestinyDataByID(pTemplate->getDestinyByIndex(i));
                if (data)
                {
                    pNode = MB_NodeDestiny::create(data,MB_TeamData::getInstance()->IsFindInTeam(data->getDestinyNeed1()));
                    if (pNode)
                    {
                        if (i==0) {
                            sz = pNode->getContentSize();
                        }
                        node->addChild(pNode);
                        allHeight = (i+.5f)*sz.height;
                        pNode->setPosition(m_pScrollView->getContentSize().width/2,(i+.5f)*sz.height);
                        ++tempIndex;
                    }
                }
            }
        }
        
        m_pScrollView->setContentSize(CCSize(640,tempIndex*sz.height));
        m_pScrollView->setContentOffset(ccp(0,m_pContainer->getContentSize().height-m_pScrollView->getContentSize().height));
        m_pScrollView->addChild(node);
    }
}
void MB_SkillDetail::onResetWnd()
{

}
bool MB_SkillDetail::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pContainer", CCNode *, m_pContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpr1", CCNode *, m_pSpr1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpr2", CCNode *, m_pSpr2);
    return true;
}
SEL_MenuHandler MB_SkillDetail::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_SkillDetail::onCloseClick);
    return NULL;
}
SEL_CCControlHandler MB_SkillDetail::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}
void MB_SkillDetail::onCloseClick(CCObject* pSender)
{
    removeFromParent();
}
