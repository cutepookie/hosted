//
//  MB_NodePetTeam.cpp
//  ProjectMB
//
//  Created by yuanwugang on 14-9-24.
//
//

#include "MB_NodePetTeam.h"
#include "MB_petData.h"
#include "../Common/GameLib/GameHelper/CCGameHelper.h"

MB_NodePetTeam::MB_NodePetTeam()
{
    m_pSpriteFrame = NULL;
    m_pSpriteCard = NULL;
    m_pTTFName = NULL;
    m_pTTFLv = NULL;
    for (int i = 0;i < MAX_GER_STAR; i++)
    {
        m_pStar[i] = NULL;
    }
    m_pNodeInfo = NULL;
    m_pSpriteBG1 = NULL;
    m_pSpriteBG2 = NULL;
    m_pData = NULL;
    m_nUID = 0;
}
MB_NodePetTeam::~MB_NodePetTeam()
{
    CC_SAFE_RELEASE_NULL(m_pSpriteFrame);
    CC_SAFE_RELEASE_NULL(m_pSpriteCard);
    CC_SAFE_RELEASE_NULL(m_pTTFName);
    CC_SAFE_RELEASE_NULL(m_pTTFLv);
    for (int i = 0;i < MAX_GER_STAR; i++)
    {
        CC_SAFE_RELEASE_NULL(m_pStar[i]);
    }
    CC_SAFE_RELEASE_NULL(m_pNodeInfo);
    CC_SAFE_RELEASE_NULL(m_pSpriteBG1);
    CC_SAFE_RELEASE_NULL(m_pSpriteBG2);
    
    if (m_nUID == 0)
    {
        CC_SAFE_RELEASE_NULL(m_pData);
    }
}

MB_NodePetTeam* MB_NodePetTeam::create(uint64_t uid)
{
    MB_NodePetTeam* ptr = new MB_NodePetTeam();
    if (ptr && ptr->init(uid))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}
bool MB_NodePetTeam::init(uint64_t uid)
{
    m_nUID = uid;
    m_pData = MB_PetMgr::getInstance()->getPetDataByUID(uid);
    if (m_pData == NULL)
    {
        CCLOG("ERROR: not found uid=%d in MB_NodePetTeam",uid);
        return false;
    }
    CCNode* pNode = loadResource("res/card_node_image_1.ccbi");
    if(pNode)
	{
		addChild(pNode);
        
        
        for (int i = 0; i < MAX_GER_STAR; i++)
        {
            starPt[i] = m_pStar[i]->getPosition();
        }
        
        onResetWnd();
		return true;
	}
	return false;

}

MB_NodePetTeam* MB_NodePetTeam::create(MB_PetData* pData)
{
    MB_NodePetTeam* ptr = new MB_NodePetTeam();
    if (ptr && ptr->init(pData))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}
bool MB_NodePetTeam::init(MB_PetData* pData)
{
    CC_SAFE_RELEASE_NULL(m_pData);
    m_pData = pData;
    CC_SAFE_RETAIN(m_pData);
    CCNode* pNode = loadResource("res/card_node_image_1.ccbi");
    if(pNode)
	{
		addChild(pNode);
        
        
        for (int i = 0; i < MAX_GER_STAR; i++)
        {
            starPt[i] = m_pStar[i]->getPosition();
        }
        
        onResetWnd();
		return true;
	}
	return false;
}
void MB_NodePetTeam::onResetWnd(void)
{
    m_pNodeInfo->setVisible(true);
    if (m_pData == NULL)
    {
        CCLOG("ERROR:in MB_NodePetTeam");
        return;
    }

    MB_PetTemplate* templete = MB_PetMgr::getInstance()->getPetTemplateByID(m_pData->getPetTypeID());
    
    for (int i = 0; i < MAX_GER_STAR; i++)
    {
         m_pStar[i]->setPosition(starPt[i]);
    }
    NSGameHelper::centerStars(m_pStar, MAX_GER_STAR, templete->getPetStar());
    
    NSGameHelper::setMonsterCardDetailByTid(templete->getPetTypeID(),m_pData->getPetQuallity(),m_pSpriteCard,m_pTTFName,m_pSpriteFrame);
    char str[30] = "";
    sprintf(str,"lv.%d",m_pData->getPetLevel());
    m_pTTFLv->setString(str);
    
}
void MB_NodePetTeam::onMsgRecv(CCNode* node, SocketResponse* response)
{
    
}

bool MB_NodePetTeam::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpriteFrame",CCSprite*,m_pSpriteFrame);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpriteCard",CCSprite*,m_pSpriteCard);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFName",CCLabelTTF*,m_pTTFName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFLv",CCLabelTTF*,m_pTTFLv);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeInfo",CCNode*,m_pNodeInfo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpriteBG1",CCSprite*,m_pSpriteBG1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpriteBG2",CCScale9Sprite*,m_pSpriteBG2);
    char str[10] = "m_pStar1";
    for (int i = 0;i < 7; i++)
    {
        str[7] = '1'+i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this,str,CCSprite*,m_pStar[i]);
    }
    return false;
}
SEL_MenuHandler MB_NodePetTeam::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}
SEL_CCControlHandler MB_NodePetTeam::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

void MB_NodePetTeam::setShowInfo(bool bShow)
{
//    m_pNodeInfo->setVisible(bShow);
    int nStar = 0;
    m_pNodeInfo->setVisible(true);
    
    if (m_pData == NULL)
    {
        CCLOG("ERROR:in MB_NodePetTeam");
        return;
    }

    MB_PetTemplate* templete = MB_PetMgr::getInstance()->getPetTemplateByID(m_pData->getPetTypeID());

    nStar = templete->getPetStar();
    if (bShow)
    {
        m_pSpriteBG1->runAction(CCFadeIn::create(1));
        m_pSpriteBG2->runAction(CCFadeIn::create(1));
        for (int i = 0;i < nStar; i++)
        {
            m_pStar[i]->runAction(CCFadeIn::create(1));
        }
        m_pTTFName->runAction(CCFadeIn::create(1));
        m_pTTFLv->runAction(CCFadeIn::create(1));
    }
    else
    {
        m_pSpriteBG1->runAction(CCFadeOut::create(0.8));
        m_pSpriteBG2->runAction(CCFadeOut::create(0.8));
        for (int i = 0;i < nStar; i++)
        {
            m_pStar[i]->runAction(CCFadeOut::create(0.8));
        }
        m_pTTFName->runAction(CCFadeOut::create(0.8));
        m_pTTFLv->runAction(CCFadeOut::create(0.8));
    }
}
