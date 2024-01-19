//
//  MB_NodeShowCard.cpp
//  ProjectMB
//
//  Created by yuanwugang on 14-10-24.
//
//

#include "MB_NodeShowCard.h"
#include "MB_petData.h"

MB_NodeShowCard::MB_NodeShowCard()
{
    m_pNodeSize = NULL;
}
MB_NodeShowCard::~MB_NodeShowCard()
{
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
}
MB_NodeShowCard* MB_NodeShowCard::create(MB_PetData* pData)
{
    MB_NodeShowCard* ptr = new MB_NodeShowCard();
    if (ptr && ptr->init(pData))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}
bool MB_NodeShowCard::init(MB_PetData* pData)
{
    CC_SAFE_RELEASE_NULL(m_pData);
    m_pData = pData;
    CC_SAFE_RETAIN(m_pData);
    CCNode* pNode = loadResource("res/card_node_image_3.ccbi");
    if(pNode)
	{
		addChild(pNode);
        for (int i = 0; i < MAX_GER_STAR; i++)
        {
            starPt[i] = m_pStar[i]->getPosition();
        }
        this->setContentSize(m_pNodeSize->getContentSize());
        onResetWnd();
		return true;
	}
	return false;

}

bool MB_NodeShowCard::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    MB_NodePetTeam::onAssignCCBMemberVariable(pTarget,pMemberVariableName,pNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize",CCNode*,m_pNodeSize);
    return false;
}
void MB_NodeShowCard::onResetWnd(void)
{
    MB_NodePetTeam::onResetWnd();
    m_pTTFLv->setVisible(false);
}
