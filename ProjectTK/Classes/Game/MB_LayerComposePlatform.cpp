//
//  MB_LayerComposePlatform.cpp
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-18.
//
//

#include "MB_LayerComposePlatform.h"
#include "MB_LayerSelectMaterial.h"
#include "MB_LayerComposeMain.h"
#include "MB_LayerComposeRule.h"
#include "MB_FunctionMgr.h"
#include <algorithm>
#include "Game.h"
#include "MB_FunctionMgr.h"
#include "MB_LayerListOther.h"
#include "MB_LayerChooseMaterial.h"
#include "MB_NodeRewardCard.h"
#include "MB_LayerRewardMoreCard.h"
#include "MB_LayerItemDetail.h"

static bool compareItem(uint64_t uid1,uint64_t uid2)
{
    MB_ItemData* first = MB_ItemMgr::getInstance()->getItemDataByUID(uid1);
    MB_ItemData* second = MB_ItemMgr::getInstance()->getItemDataByUID(uid2);
    
    if(first->getTemplateStar() > second->getTemplateStar())
    {
        return false;
    }
    else if(first->getTemplateStar() < second->getTemplateStar())
    {
        return true;
    }
    
    if (first->getItemLevel() > second->getItemLevel())
    {
        return false;
    }
    else if(first->getItemLevel() == second->getItemLevel())
    {
        if (first->getItemRank() > second->getItemRank())
        {
            return false;
        }
        else if(first->getItemRank() == second->getItemRank())
        {
            if (first->getItemUID() > second->getItemUID())
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            return true;
        }
    }
    else
    {
        return true;
    }
    
    return true;
}

static bool compareMonster(uint64_t uid1,uint64_t uid2)
{
    MB_PetData* first = MB_PetMgr::getInstance()->getPetDataByUID(uid1);
    MB_PetData* second = MB_PetMgr::getInstance()->getPetDataByUID(uid2);
    
    if(first->getTemplateStar() > second->getTemplateStar())
    {
        return false;
    }
    else if(first->getTemplateStar() < second->getTemplateStar())
    {
        return true;
    }
    
    if (first->getPetLevel() > second->getPetLevel())
    {
        return false;
    }
    else if(first->getPetLevel() == second->getPetLevel())
    {
        if (first->getPetQuallity() > second->getPetQuallity())
        {
            return false;
        }
        else if(first->getPetQuallity() == second->getPetQuallity())
        {
            if (first->getPetID() > second->getPetID())
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            return true;
        }
    }
    else
    {
        return true;
    }
    
    return true;
}

static bool sortItem(std::vector<uint64_t>& vContainer)
{
    std::sort(vContainer.begin(), vContainer.end(),compareItem);
    return true;
}

static bool sortMonster(std::vector<uint64_t>& vContainer)
{
    std::sort(vContainer.begin(), vContainer.end(),compareMonster);
    return true;
}

static bool sortContainer(std::vector<uint64_t>& vContainer, uint16_t nType)
{
    if (nType == 1)
    {
        return sortMonster(vContainer);
    }
    else if(nType == 2)
    {
        
        return sortItem(vContainer);
    }
    return false;
}

int ComposeUint::getItemRank()
{
    if (!getIsInput())
    {
        return 0;
    }

    if (m_Type == 1)
    {
        MB_PetData* pData = MB_PetMgr::getInstance()->getPetDataByUID(m_ItemUID);
        if (pData)
        {
            return pData->getPetQuallity();
        }
    }
    else if(m_Type == 2)
    {
        MB_ItemData* pData  = MB_ItemMgr::getInstance()->getItemDataByUID(m_ItemUID);
        if (pData)
        {
            return pData->getItemRank();
        }
    }

    return 0;
}

void ComposeUint::clear()
{
    m_TypeID = 0;
    m_ItemUID = 0;
    reset();
}

void ComposeUint::setUID(uint64_t uid)
{
    m_ItemUID = uid;
    reset();
}

void ComposeUint::setActivated(bool bActivate)
{
    m_pBtn->setVisible(bActivate);
    m_pAddBtn->setVisible(!bActivate);
}
void ComposeUint::setTID(uint16_t tid)
{
    m_TypeID = tid;

    reset();
}

void ComposeUint::reset()
{
    if (m_ItemUID!=0)
    {
        if (m_Type == 1)
        {
            MB_PetData* pData = MB_PetMgr::getInstance()->getPetDataByUID(m_ItemUID);
            if (pData)
            {
                m_pItemIcon->setScale(0.331f);
                m_pItemFrame->setVisible(true);
                NSGameHelper::setMonsterIconDetailByUid(m_ItemUID, m_pItemIcon,NULL,m_pItemFrame,false);
            }
        }
        else if(m_Type == 2)
        {
            MB_ItemData* pData = MB_ItemMgr::getInstance()->getItemDataByUID(m_ItemUID);
            if (pData != NULL)
            {
                m_pItemIcon->setScale(0.92f);
                m_pItemFrame->setVisible(false);
                NSGameHelper::setItemIconDetailByUid(m_ItemUID, m_pItemIcon,NULL,m_pItemFrame,false);
            }
        }
        setActivated(true);
        return;
    }

    if(m_TypeID != 0 )
    {
        if (m_Type == 1)
        {
            MB_PetTemplate* pTemplate = MB_PetMgr::getInstance()->getPetTemplateByID(m_TypeID);
            if (pTemplate)
            {
                m_pItemIcon->setScale(0.331f);
                m_pItemFrame->setVisible(true);
                NSGameHelper::setMonsterIconDetailByTid(m_TypeID, 0, m_pItemIcon,NULL,m_pItemFrame);
            }
        }
        else if(m_Type == 2)
        {
            MB_ItemTemplate* pTemplate = MB_ItemMgr::getInstance()->getItemTemplateByID(m_TypeID);
            if (pTemplate)
            {
                m_pItemIcon->setScale(0.92f);
                m_pItemFrame->setVisible(false);
                NSGameHelper::setItemIconDetailByTid(m_TypeID, 0, m_pItemIcon,NULL,m_pItemFrame);
            }
        }
        setActivated(false);
        return;
    }

    
    setActivated(false);
}

MB_LayerComposePlatform::MB_LayerComposePlatform()
{
    m_pComposeTemplate = NULL;
    m_pTargetItemCost = NULL;
    m_pUnitRoot = NULL;
    m_nSelected = 0;
    m_nCurrentStar = 1;
    m_nstartStar = 1;
    m_pCCBAnimationMgr = NULL;
    m_bInAnimation = false;
    m_pRewardData = new CCArray;
    m_bShowRoleInfoPanel = true;

    SOCKET_MSG_REGIST(SC_COMBINE_FAIL,MB_LayerComposePlatform);
    SOCKET_MSG_REGIST(SC_COMBINE_GER,MB_LayerComposePlatform);
    SOCKET_MSG_REGIST(SC_COMBINE_EQUIP,MB_LayerComposePlatform);
    
}

MB_LayerComposePlatform::~MB_LayerComposePlatform()
{
    m_pComposeTemplate = NULL;
    CC_SAFE_RELEASE_NULL(m_pTargetItemCost);
    CC_SAFE_RELEASE_NULL(m_pCCBAnimationMgr);
    CC_SAFE_RELEASE_NULL(m_pRewardData);
    
    SOCKET_MSG_UNREGIST(SC_COMBINE_FAIL);
    SOCKET_MSG_UNREGIST(SC_COMBINE_GER);
    SOCKET_MSG_UNREGIST(SC_COMBINE_EQUIP);
}

MB_LayerComposePlatform* MB_LayerComposePlatform::create(uint16_t nComposeID,int nType)
{
    MB_LayerComposePlatform* pInstance = new MB_LayerComposePlatform;
    if (pInstance && pInstance->init(nComposeID,nType))
    {
        pInstance->autorelease();
        return pInstance;
    }

    CC_SAFE_RELEASE_NULL(pInstance);

    return pInstance;
}



bool MB_LayerComposePlatform::init(uint16_t nComposeID,int nType)
{
    m_PlatformType = kPlatformCount;
    m_pComposeTemplate = MB_ComposeMgr::getInstance()->getComposeTemplateByID(nComposeID);
    if (m_pComposeTemplate)
    {
        const int temp[] = {kPlatformCount,kPlatformCount,kPlatform2IN1,kPlatform3IN1,kPlatform4IN1,kPlatform5IN1,kPlatform5IN1Random,kPlatformCount,kPlatformCount};
        m_PlatformType = temp[m_pComposeTemplate->getMaterialCount()];
        m_nType = m_pComposeTemplate->getComposeType();
    }
    else
    {
        m_PlatformType = kPlatform5IN1Random;
        m_nType = nType;
    }

    if (m_nType > 2)
    {
        return false;
    }
    if (m_PlatformType >= kPlatformCount)
    {
        return false;
    }

    
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    m_pUnitRoot = pCCBReader->readNodeGraphFromFile("res/gui_main_compose.ccbi", this);
    if (m_pUnitRoot == NULL)
    {
        CC_SAFE_RELEASE_NULL(pCCBReader);
        return false;
    }
    CC_SAFE_RELEASE_NULL(pCCBReader);
    CC_SAFE_RETAIN(m_pUnitRoot);
    
    
    addChild(NSGameHelper::createDisableTouchLayer12());
    addChild(m_pUnitRoot);

    m_nComposeID = nComposeID;
    for (int i=0; i<5; ++i)
    {
        m_PlatformUint[i].setType(m_nType);
    }

    onResetWnd();
    
    //this->setTouchEnabled(true);

    
    
    return true;
}

void MB_LayerComposePlatform::reloadComposeUnit(CCNode* pParent)
{
    m_nCurrentStar = 1;
    if(m_pCCBAnimationMgr)
    {
        m_pCCBAnimationMgr->setAnimationCompletedCallback(NULL, NULL);
    }
    CC_SAFE_RELEASE_NULL(m_pCCBAnimationMgr);
    
    const char* name = "res/compose_layer_main.ccbi";
    CCBReader* pCCBReader = NULL;
    pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile(name, this);
    if (pNode && pParent)
    {
        pParent->removeChildByTag(100, true);
        pParent->addChild(pNode,0,100);
    }
    m_pCCBAnimationMgr = pCCBReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pCCBAnimationMgr);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    
    for (int i=0; i<5; ++i)
    {
        NSGameHelper::changeParent(m_PlatformUint[i].m_pBtn, m_PlatformUint[i].m_pItemFrame);
        NSGameHelper::changeParent(m_PlatformUint[i].m_pBtn, m_PlatformUint[i].m_pItemIcon);
        m_PlatformUint[i].m_pItemFrame->setPosition(m_PlatformUint[i].m_pBtn->getContentSize()/2);
        m_PlatformUint[i].m_pItemIcon->setPosition(m_PlatformUint[i].m_pBtn->getContentSize()/2);
    }
}

void MB_LayerComposePlatform::destroyUnit()
{
    cleanAll();
}
void MB_LayerComposePlatform::cleanAll()
{
    for (int i = 0;i < getNeedCount(); i++) {
        m_PlatformUint[i].clear();
    }
    NSGameHelper::LabelFormatNumber(m_pTargetItemCost,0,false);
}


void MB_LayerComposePlatform::resetNormal()
{
    NSGameHelper::LabelFormatNumber(m_pTargetItemCost, m_pComposeTemplate->getCostCoin(),false);

    int count = m_pComposeTemplate->getMaterialCount();
    const uint16_t* pMatrail = m_pComposeTemplate->getMaterialsArray();
    for (int i=0; i<count; ++i)
    {
        //如果已放入精灵 不再自动放入
        if (m_PlatformUint[i].getUID() != 0) {
            continue;
        }
        uint16_t tid = pMatrail[i];
        bool ret = false;
        std::vector<uint64_t> vContainer;

        if (m_nType == 1) // pet
        {
            // 选择精灵列表
            ret = NSGameHelper::getMonstersFromPetMgrByTid(vContainer, tid,NSGameHelper::filter_unused);
        }
        else if(m_nType == 2) // item
        {
            // 选择物品列表
            ret = NSGameHelper::getEquipItemsFromItemMgrByTid(vContainer, tid,NSGameHelper::filter_unused);
        }
        if (!ret)
        {
            m_PlatformUint[i].setTID(pMatrail[i]);
            continue;
        }
        removeInputedUidFromContainer(vContainer);
        sortContainer(vContainer,m_nType);
        if (vContainer.size() > 0)
        {
            uint64_t uID = vContainer[0];
            m_PlatformUint[i].setUID(uID);
        }
        else
        {
            m_PlatformUint[i].setTID(pMatrail[i]);
        }
        
    }
    
    char buff[100] = {0};
    
    uint16_t id = m_pComposeTemplate->getTargetID();
}

static int getPetStar(uint64_t uid)
{
    MB_PetData* tp = MB_PetMgr::getInstance()->getPetDataByUID(uid);
    if (tp)
    {
        MB_PetTemplate* pGT = tp->getTemplete();
        return pGT->getPetStar();
    }
    return 0;
}
static int getItemStar(uint64_t uid)
{
    MB_ItemData* pid = MB_ItemMgr::getInstance()->getItemDataByUID(uid);
    if (pid)
    {
        MB_ItemTemplate* pit = MB_ItemMgr::getInstance()->getItemTemplateByID(pid->getItemID());
        return pit->getItemStar();
    }
    return 0;
}

int MB_LayerComposePlatform::getRandomInputComplate()
{
    int star = 0;
    for (int i=0; i<5; ++i)
    {
        if (m_PlatformUint[i].getIsInput())
        {
            if (m_nType == 1)
            {
                star = getPetStar(m_PlatformUint[i].getUID());
            }
            else if (m_nType == 2)
            {
                star = getItemStar(m_PlatformUint[i].getUID());
            }
        }
        else
        {
            star = 0;
            break;
        }
    }

    return star;
}
int MB_LayerComposePlatform::getOneStarForRandom()
{
    if (m_PlatformType!=kPlatform5IN1Random)
    {
        return 0;
    }
    int star = 0;
    for (int i=0; i<5; ++i)
    {
        if (m_PlatformUint[i].getIsInput())
        {
            if (m_nType == 1)
            {
                star = getPetStar(m_PlatformUint[i].getUID());
                return star;
            }
            else if (m_nType == 2)
            {
                star = getItemStar(m_PlatformUint[i].getUID());
                return star;
            }
        }
    }
    return star;
}
void MB_LayerComposePlatform::resetRandom()
{
    for (uint16_t i=0; i<5; ++i)
    {
        m_PlatformUint[i].reset();
    }

    char buff[64] = {};
    int star = getOneStarForRandom();
    if (star > 0)
    {
        uint64_t cost = MB_ComposeMgr::getInstance()->getRandomCombine(star, m_nType);
        NSGameHelper::LabelFormatNumber(m_pTargetItemCost, cost);
    }
    else
    {
        sprintf(buff, "0");
        m_pTargetItemCost->setString(buff);
    }
}

void MB_LayerComposePlatform::onResetWnd()
{
    if (NULL == m_pComposeTemplate)
    {
        resetRandom();
    }
    else
    {
        resetNormal();
    }
}

bool MB_LayerComposePlatform::getIsInputComplate()
{
    if (m_PlatformType != kPlatform5IN1Random)
    {
        return m_pComposeTemplate->getMaterialCount() == getInputedCount();
    }
    else
    {
        return getInputedCount() == 5;
    }

    return false;
}

int MB_LayerComposePlatform::calcTargetComposedRank()
{
    int count = getNeedCount();
    int rank = 0;
    for (int i=0; i<count; ++i)
    {
        rank += m_PlatformUint[i].getItemRank();
    }
    return rank/5;
}
bool MB_LayerComposePlatform::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
//    CCLOG(pMemberVariableName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "target_item_cost", CCLabelBMFont*, m_pTargetItemCost);
    
    char buff[15] = {};
    for (int i=0; i<5; ++i)
    {
        sprintf(buff, "frame%d",i+1);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, buff, CCSprite*, m_PlatformUint[i].m_pItemFrame);
        sprintf(buff, "icon%d",i+1);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, buff, CCSprite*, m_PlatformUint[i].m_pItemIcon);
        sprintf(buff, "m_pAddBtn%d",i+1);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, buff, CCControlButton*, m_PlatformUint[i].m_pAddBtn);
        sprintf(buff, "m_pBtn%d",i+1);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, buff, CCControlButton*, m_PlatformUint[i].m_pBtn);
        
    }
    return false;
}

SEL_MenuHandler MB_LayerComposePlatform::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{

    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerComposePlatform::onCloseClicked);

    return NULL;
}


void MB_LayerComposePlatform::onRuleClicked(CCObject*)
{
    if(m_bInAnimation)return;
    
    MB_LayerComposeRule* pLayer = MB_LayerComposeRule::create();
    if (pLayer)
    {
        pushWindow(pLayer);
    }
}
SEL_CCControlHandler MB_LayerComposePlatform::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onAutoInputClicked", MB_LayerComposePlatform::onAutoInputClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onComposeClicked", MB_LayerComposePlatform::onComposeClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onRuleClicked", MB_LayerComposePlatform::onRuleClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSelectItemClicked", MB_LayerComposePlatform::onSelectItemClicked);
    
    return NULL;
}

int MB_LayerComposePlatform::getInputItemStar()
{
    int count = getNeedCount();
    for (int i=0; i<count; ++i)
    {
        if (m_PlatformUint[i].getIsInput())
        {
            if (m_nType == 1)
            {
                MB_PetData* tp = MB_PetMgr::getInstance()->getPetDataByUID(m_PlatformUint[i].getUID());
                if(tp)
                {
                    MB_PetTemplate* pGT = tp->getTemplete();
                    return pGT->getPetStar();
                }
            }
            else if (m_nType == 2)
            {
                MB_ItemData* pid = MB_ItemMgr::getInstance()->getItemDataByUID(m_PlatformUint[i].getUID());
                if(pid)
                {
                    MB_ItemTemplate* pit = MB_ItemMgr::getInstance()->getItemTemplateByID(pid->getItemID());
                    return pit->getItemStar();
                }
            }
        }
    }
    return -1;
}

void MB_LayerComposePlatform::onExit()
{
    m_pCCBAnimationMgr->setAnimationCompletedCallback(NULL, NULL);
    MB_ResWindow::onExit();
}

void MB_LayerComposePlatform::onAutoInputClicked(CCObject*)
{
//    if (getIsInputComplate())
//    {
//        MB_Message::sharedMB_Message()->showMessage("材料已经准备就绪");
//        return;
//    }
    if(m_bInAnimation)return;
        
    //如果手动放入部分材料，从已放入材料星级开始查找
     m_nstartStar = getInputItemStar();
     m_nstartStar = (m_nstartStar == -1)? 1:m_nstartStar;
    
    int nCurrenStar = -2;
    
    std::vector<uint64_t> uids;
    bool ret = false;

    if (getInputedCount() > 0 )
    {
        if (getIsInputComplate())
        {
            nCurrenStar = m_nstartStar;
            m_nstartStar =(m_nstartStar+1)%7;
            m_nstartStar = (m_nstartStar == 0)? 1:m_nstartStar;
            for (int j = 0; j < 5; j++)
            {
                if (m_PlatformUint[j].getIsInput())
                {
                    m_OldData.oldUID.push_back(m_PlatformUint[j].getUID());
                    m_PlatformUint[j].setUID(0);
                }
            }
        }
        if (-1 == m_OldData.star)
        {
            m_OldData.star = m_nstartStar;

        }
        else if(m_OldData.star != m_nstartStar)
        {
            m_OldData.clean();
            m_OldData.star = m_nstartStar;
        }

    }
    else
    {
//        m_nstartStar = m_nCurrentStar;
        m_nstartStar = (m_nstartStar == 0)? 1:m_nstartStar;
    }

    
    int i = 0;
    for (i=0; i<7; ++i)
    {
        ret = autoPick4RandomSelected(uids,m_nstartStar);        
        getLastData(uids,m_OldData.oldUID);
        if(ret && uids.size() + getInputedCount() >= 5)
        {
            m_OldData.star = m_nstartStar;
            break;
        }
        else   
        {
            uids.clear();
            m_OldData.clean();
            if(getInputedCount() > 0 && !getIsInputComplate())
            {
                char str[30];
                sprintf(str, "%d星材料不足",getInputItemStar());
                MB_Message::sharedMB_Message()->showMessage(str);
            }
            for (int j = 0; j < 5; j++)
            {
                if (m_PlatformUint[j].getIsInput())
                {
                    m_PlatformUint[j].setUID(0);
                }
            }
            m_nstartStar =(m_nstartStar+1)%7;
            m_nstartStar = (m_nstartStar == 0)? 1:m_nstartStar;
            continue;
        }
    }
    
    if (i == 6)
    {
        MB_Message::sharedMB_Message()->showMessage("找不到相同星级的卡牌");
        resetRandom();
        return ;
    }
    
    if((uids.size() + getInputedCount()) < 5)
    {
        MB_Message::sharedMB_Message()->showMessage("材料不足");
        resetRandom();
        return ;
    }
    if (ret)
    {
//      destroyUnit();
        removeInputedUidFromContainer(uids);
        int index = 0;
        for (int i=0; i<5; ++i)
        {
            //已经放入了的材料
            if (m_PlatformUint[i].getUID() != 0) {
                continue;
            }
            
            if (!m_PlatformUint[i].getIsInput())
            {
                m_PlatformUint[i].setUID(uids[index++]);
                if (index >= uids.size())
                {
                    break;
                }
            }
        }
    }
    
    if (getIsInputComplate())
    {
        resetRandom();
    }
    
    if (nCurrenStar == m_nstartStar)
    {
        MB_Message::sharedMB_Message()->showMessage("其他星级材料不足");
    }
    
}

void MB_LayerComposePlatform::onComposeClicked(CCObject*)
{
    if(m_bInAnimation)return;
    
    int count = getNeedCount();
    uint64_t uid[10] = {};

    for (int i=0; i<count; ++i)
    {
        if(!m_PlatformUint[i].getIsInput())
        {
            MB_Message::sharedMB_Message()->showMessage("合成材料不足, 请放入足够的合成材料");
            return;
        }
        uid[i] = m_PlatformUint[i].getUID();
    }

    int combineType = 1;
    if (m_PlatformType == kPlatform5IN1Random)
    {
        combineType = 2;//random
    }

    m_nCurrentStar = 1;
    MB_Message::sharedMB_Message()->showMessage("",15);
    MB_ComposeMgr::getInstance()->sendcombine_do(combineType, m_nComposeID, m_nType, uid, count);
    
    for (int i = 0;i < getNeedCount(); i++)
    {
        if(m_nType == 1)
        {
            MB_PetTemplate* pTemplete = MB_PetMgr::getInstance()->getPetTemplateByUID(m_PlatformUint[i].getUID());
            if(pTemplete)m_nCurItemType[i] = pTemplete->getPetTypeID();
        }
        else
        {
            MB_ItemData* pData = MB_ItemMgr::getInstance()->getItemDataByUID(m_PlatformUint[i].getUID());
            if(pData)m_nCurItemType[i] = pData->getItemID();
        }
    }
    
}

void MB_LayerComposePlatform::onCloseClicked(CCObject*)
{
    if(m_bInAnimation)return;
    popWindow();
}

void MB_LayerComposePlatform::onSelectItemClicked(CCObject* pSender)
{
    if(m_bInAnimation)return;
    
    CCNode* pNode = dynamic_cast<CCNode*>(pSender);
    int index = 0;
    if (pNode)
    {
        index = pNode->getTag();
        if (index < 1)
        {
            return;
        }
        else
        {
            if (m_PlatformType != kPlatform5IN1Random)
            {
                goSelectItem(index-1);
            }
            else
            {
                goSelectItemRandom(index-1);
            }
        }
    }
}
int MB_LayerComposePlatform::getNeedCount()
{
    if (m_PlatformType != kPlatform5IN1Random)
    {
        return m_pComposeTemplate->getMaterialCount();
    }
    return 5;
}

void MB_LayerComposePlatform::removeInputedUidFromContainer(std::vector<uint64_t>& vContainer)
{
    uint16_t nCount = getNeedCount();
    std::vector<uint64_t>::iterator it = vContainer.end();

    for (uint16_t i=0; i<nCount; ++i)
    {
        if (m_PlatformUint[i].getIsInput())
        {
            it = std::find(vContainer.begin(), vContainer.end(), m_PlatformUint[i].getUID());
            if (it != vContainer.end())
            {
                vContainer.erase(it);
            }
        }
    }
}

void MB_LayerComposePlatform::goSelectItem(int clickedIndex)
{
    uint16_t tid = m_pComposeTemplate->getMaterialsArray()[clickedIndex];
    bool ret = false;
    std::vector<uint64_t> vContainer;
    uint64_t nCurrent = m_PlatformUint[clickedIndex].getUID();

    if (m_nType == 1) // pet
    {
        // 选择精灵列表
        ret = NSGameHelper::getMonstersFromPetMgrByTid(vContainer, tid,NSGameHelper::filter_unused);
    }
    else if(m_nType == 2) // item
    {
        // 选择物品列表
        ret = NSGameHelper::getEquipItemsFromItemMgrByTid(vContainer, tid,NSGameHelper::filter_unused);
    }
    if (!ret)
    {
        MB_Message::sharedMB_Message()->showMessage("没有找到对应的材料");
        return;
    }

    removeInputedUidFromContainer(vContainer);
    sortContainer(vContainer,m_nType);

    MB_LayerSelectMaterial * pLayer = MB_LayerSelectMaterial::create(vContainer,nCurrent, m_nType);
    if (pLayer)
    {
        if (m_nType == 1)
        {
            pLayer->setTitle("请选择材料");
        }
        else if(m_nType == 2)
        {
            pLayer->setTitle("请选择材料");
        }
        m_nSelected = clickedIndex;
        pLayer->setDelegate(this);
        pushWindow(pLayer);

    }
    else
    {
        MB_Message::sharedMB_Message()->showMessage("没有找到对应的材料");
        return;
    }
}

int MB_LayerComposePlatform::getInputedCount()
{
    int count = getNeedCount();

    int result = 0;
    for (int i=0; i<count; ++i)
    {
        if (m_PlatformUint[i].getIsInput())
        {
            ++result;
        }
    }

    return result;
}

bool MB_LayerComposePlatform::autoPick4RandomSelected(std::vector<uint64_t>& vContainer,int nStar)
{
    if (m_PlatformType != kPlatform5IN1Random)
    {
        return false;
    }

    if (m_nType == 1)
    {
        int star = getInputItemStar();
        if (star > 0 && getNeedCount()!=5)
        {
            NSGameHelper::getMonstersFromPetMgrByStar(vContainer, star,NSGameHelper::filter_unused);
            removeInputedUidFromContainer(vContainer);
            sortContainer(vContainer,m_nType);
        }
        else
        {
            if(nStar == 0)
            {
                NSGameHelper::getAllMonstersUidFromPetMgr(vContainer,6,NSGameHelper::filter_unused);
            }
            else
            {
                NSGameHelper::getMonstersFromPetMgrByStar(vContainer,nStar,NSGameHelper::filter_unused);
            }
            removeInputedUidFromContainer(vContainer);
            sortContainer(vContainer,m_nType);
        }
        return !vContainer.empty();
    }
    else if(m_nType == 2)
    {
        int star = getInputItemStar();
        if (star > 0 && getNeedCount()!=5)
        {
            NSGameHelper::getEquipItemsFromItemMgrByStar(vContainer, star,NSGameHelper::filter_unused);
            removeInputedUidFromContainer(vContainer);
            sortContainer(vContainer,m_nType);
        }
        else
        {
            if (nStar == 0)
            {
                NSGameHelper::getAllEquipItemsFromItemMgr(vContainer,6,NSGameHelper::filter_unused);
            }
            else
            {
                NSGameHelper::getEquipItemsFromItemMgrByStar(vContainer,nStar,NSGameHelper::filter_unused);
            }
            removeInputedUidFromContainer(vContainer);
            sortContainer(vContainer,m_nType);
        }
        return !vContainer.empty();
    }

    return false;
}


void MB_LayerComposePlatform::goSelectItemRandom(int clickIndex)
{
    std::vector<uint64_t> uids;
    int star = 0;
    uint64_t nCurrent = m_PlatformUint[clickIndex].getUID();
  
    if (m_nType == 1) // pet
    {
        if(getInputItemStar() == -1)
            star = MB_PetMgr::getInstance()->getPetTemplateStarByUID(nCurrent);
        else
            star = getInputItemStar();// MB_PetMgr::getInstance()->getPetTemplateStarByUID(nCurrent);
        if (autoPick4RandomSelected(uids,star))
        {
            MB_LayerSelectMaterial * pLayer = MB_LayerSelectMaterial::create(uids,nCurrent, m_nType);
            if (pLayer)
            {
                if (m_nType == 1)
                {
                    pLayer->setTitle("请选择材料");
                }
                else if(m_nType == 2)
                {
                    pLayer->setTitle("请选择材料");
                }

                m_nSelected = clickIndex;
                pLayer->setDelegate(this);
                pushWindow(pLayer);
            }
        }
        else
        {
            MB_Message::sharedMB_Message()->showMessage("添加失败, 没有足够的材料！");
        }
    }
    else if(m_nType == 2) // item
    {
        //如果没有放入材料 不做星级筛选
        if(getInputItemStar() == -1)
            star = MB_ItemMgr::getInstance()->getItemQualityByUid(nCurrent);
        else
            star = getInputItemStar();// MB_ItemMgr::getInstance()->getItemQualityByUid(nCurrent);
        
        
        if (autoPick4RandomSelected(uids,star))
        {

            MB_LayerSelectMaterial * pLayer = MB_LayerSelectMaterial::create(uids,nCurrent, m_nType);
            if (pLayer)
            {
                if (m_nType == 1)
                {
                    pLayer->setTitle("请选择材料");
                }
                else if(m_nType == 2)
                {
                    pLayer->setTitle("请选择材料");
                }

                m_nSelected = clickIndex;
                pLayer->setDelegate(this);
                pushWindow(pLayer);
            }

        }
        else
        {
            MB_Message::sharedMB_Message()->showMessage("添加失败, 没有足够的材料！");
        }
    }
    else
    {
        MB_Message::sharedMB_Message()->showMessage("错误的合成类型");
        return ;
    }

}

void MB_LayerComposePlatform::onNodeSelected(uint64_t nUid,uint16_t nType)
{
    if (m_nSelected >= 5)
    {
        CCLOG("[Error]:Invalid select");
        return;
    }

    m_nType = nType;
    m_PlatformUint[m_nSelected].setType(nType);
    m_PlatformUint[m_nSelected].setUID(nUid);
    //if (getIsInputComplate())
    {
        onResetWnd();
    }
}

void MB_LayerComposePlatform::onMsgRecv(CCNode* node, SocketResponse* response)
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

    MB_Message::sharedMB_Message()->removeALLMessage();

    switch (Msg)
    {
        case SC_COMBINE_GER:
            recvcombine_pet(recvPacket);
            break;
        case SC_COMBINE_EQUIP:
            recvcombine_equip(recvPacket);
            break;
        case SC_COMBINE_FAIL:
            recvcombine_fail(recvPacket);
            break;
        default:
            break;
    }

}
//message		recvcombine_fail[id=13202]{
//	required		int8			result				=1;//合成结果
// 0=> 合成成功
// 1=> 合成失败，错误的配方ID
// 2=> 合成失败，材料不足
// 3=> 合成失败，合成的材料组合与配方不一致
// 4=> 合成失败，缺少配方道具
// 5=> 合成失败，coin不足
// 6=> 合成失败，合成所需的材料数量不对
// 7=> 合成失败，参与合成的材料星等不一致
// 8=> 合成失败，参与合成的材料超过最大星等限制
// 9=> 合成失败，经验卡牌不能参与合成
// 10=>合成失败，家园守护神不能参与合成
void MB_LayerComposePlatform::recvcombine_fail(MB_MsgBuffer* pbuff)
{
    uint8_t result = 0;
    pbuff->readU8(&result);
    switch (result)
    {
        case 0:
            MB_Message::sharedMB_Message()->showMessage("合成成功");
            break;
        case 1:
            MB_Message::sharedMB_Message()->showMessage("合成失败, 错误的配方ID");
            break;
        case 2:
            MB_Message::sharedMB_Message()->showMessage("合成失败, 材料不足");
            break;
        case 3:
            MB_Message::sharedMB_Message()->showMessage("合成失败, 合成的材料组合与配方不一致");
            break;
        case 4:
            MB_Message::sharedMB_Message()->showMessage("合成失败, 缺少配方道具");
            break;
        case 5:
            MB_Message::sharedMB_Message()->showMessage("合成失败, 金币不足");
            break;
        case 6:
            MB_Message::sharedMB_Message()->showMessage("合成失败, 合成所需的材料数量不对");
            break;
        case 7:
            MB_Message::sharedMB_Message()->showMessage("合成失败, 参与合成的材料星等不一致");
            break;
        case 8:
            MB_Message::sharedMB_Message()->showMessage("合成失败, 参与合成的材料超过最大星级限制");
            break;
        case 9:
            MB_Message::sharedMB_Message()->showMessage("合成失败, 经验卡牌不能参与合成");
            break;
        case 10:
            MB_Message::sharedMB_Message()->showMessage("合成失败, 炼金工厂守护神不能参与合成");
            break;
        default:
            MB_LOG("ERROR: MB_ComposeMgr::recvcombine_fail");
            break;
    }
}

void MB_LayerComposePlatform::onAniComplete(CCObject*)
{
//    MB_FunctionMgr::getInstance()->goFunction(kFunctionPackage,this);
}

/*
 message     recvcombine_pet[id=13203]{
 repeated        p_newPet           newPet              =1;
 }
 
 message p_newPet[id=13205]{
 required        int16           petTypeID               =1;
 required        int8            petLevel                =2;
 required        int8            petQuality              =3;
 }
 */
void MB_LayerComposePlatform::recvcombine_pet(MB_MsgBuffer* pbuff)
{
    uint16_t count = 0;
    pbuff->readU16(&count);
    
    MB_RewardDataDetail* pData = NULL;
    uint8_t u8 = 0;
    m_pRewardData->removeAllObjects();
    for(uint16_t i=0;i<count;++i)
    {
        pData = new MB_RewardDataDetail;
        pbuff->readU16(&pData->m_nTypeID);
        pbuff->readU8(&u8);
        pData->m_nLevel = u8;
        pbuff->readU8(&u8);
        pData->m_nRank = u8;
        pData->m_nType = kRewardValueTypePet;
        m_pRewardData->addObject(pData);
        
        CC_SAFE_RELEASE_NULL(pData);
    }
    
    
    m_pCCBAnimationMgr->setAnimationCompletedCallback(this, callfunc_selector(MB_LayerComposePlatform::onCallbackAnimation));
    m_pCCBAnimationMgr->runAnimationsForSequenceNamed("Default");
    m_bInAnimation = true;
    MB_Audio::getInstance()->playEffect(GET_BACKGROUND(ksSound_Star_Up).c_str());
}

/*
 message     recvcombine_equip[id=13204]{
 repeated        p_newEquip          newEquip            =2;
 }
 message p_newEquip[id=13206]{
 required        int16           itemTypeID              =1;
 required        int16           itemNum                 =2;
 required        int8            itemLevel               =3;
 required        int8            itemRank                =4;
 }
 */
void MB_LayerComposePlatform::recvcombine_equip(MB_MsgBuffer* pbuff)
{
    uint16_t count = 0;
    pbuff->readU16(&count);
    
    MB_RewardDataDetail* pData = NULL;
    uint8_t u8 = 0;
    uint16_t n = 0;
    m_pRewardData->removeAllObjects();
    for(uint16_t i=0;i<count;++i)
    {
        pData = new MB_RewardDataDetail;
        pbuff->readU16(&n);
        pData->m_nTypeID = n;
        pbuff->readU16(&n);
        pbuff->readU8(&u8);
        pData->m_nLevel = u8;
        pbuff->readU8(&u8);
        pData->m_nRank = u8;
        pData->m_nType = kRewardValueTypeItem;
        m_pRewardData->addObject(pData);
        
        CC_SAFE_RELEASE_NULL(pData);
    }

    m_pCCBAnimationMgr->setAnimationCompletedCallback(this, callfunc_selector(MB_LayerComposePlatform::onCallbackAnimation));
    m_pCCBAnimationMgr->runAnimationsForSequenceNamed("Default");
    m_bInAnimation = true;
    MB_Audio::getInstance()->playEffect(GET_BACKGROUND(ksSound_Star_Up).c_str());
}


void MB_LayerComposePlatform::onCallbackAnimation()
{

    m_pCCBAnimationMgr->setAnimationCompletedCallback(NULL,NULL);
    
    MB_LayerRewardMoreCard* pReward = NULL;

    if(m_pRewardData->count()!=0)
    {
        pReward = MB_LayerRewardMoreCard::create(m_pRewardData);
    }
    m_bInAnimation = false;
    if (pReward)
    {
        if(m_PlatformType == kPlatform5IN1Random)
        {
            cleanAll();
            addChild(pReward);
        }
        else
        {
            cleanAll();
            MB_TARGET_PARENT(MB_LayerListOther, ptr);
            if (ptr)
            {
                ptr->onComposeSuccessed(pReward,this);
                return ;
            }
            else
            {
                addChild(pReward);
            }
        }
    }
    onResetWnd();
}

void MB_LayerComposePlatform::getLastData(std::vector<uint64_t>& vContainer,std::vector<uint64_t>& vClear)
{
    if (vContainer.empty() || vClear.empty())
    {
        return;
    }
    std::vector<uint64_t>::iterator it = vClear.begin();
    for (; it != vClear.end(); it++)
    {
        std::vector<uint64_t>::iterator it2 = std::find(vContainer.begin(),vContainer.end(),*it);
        if (it2 != vContainer.end())
        {
            vContainer.erase(it2);
        }
    }
}
