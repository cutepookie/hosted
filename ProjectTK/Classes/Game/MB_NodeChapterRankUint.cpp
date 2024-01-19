//
//  MB_NodeChapterRankUint.cpp
//  ProjectMB
//
//  Created by yuanwugang on 14-9-27.
//
//

#include "MB_NodeChapterRankUint.h"
#include "MB_ChapterData.h"
#include "../Common/GameLib/GameHelper/CCGameHelper.h"
#include "MB_TeamData.h"

MB_NodeChapterRankUint::MB_NodeChapterRankUint()
{
    m_pSpriteFrame = NULL;
    m_pSpriteHead = NULL;
    m_pTTFName = NULL;
    m_pNodeLv = NULL;
    m_pTTFChapter = NULL;
    m_pData = NULL;
    m_pNodeSize = NULL;
    m_pNodeRankNum = NULL;
    for(int i = 0;i < 5;i++)
    {
        m_pNodeBG[i] = NULL;
    }

}
MB_NodeChapterRankUint::~MB_NodeChapterRankUint()
{
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(m_pSpriteFrame);
    CC_SAFE_RELEASE_NULL(m_pSpriteHead);
    CC_SAFE_RELEASE_NULL(m_pTTFName);
    CC_SAFE_RELEASE_NULL(m_pNodeLv);
    CC_SAFE_RELEASE_NULL(m_pTTFChapter);
    CC_SAFE_RELEASE_NULL(m_pData);
    
    CC_SAFE_RELEASE_NULL(m_pNodeRankNum);
    for(int i = 0;i < 5;i++)
    {
        CC_SAFE_RELEASE_NULL(m_pNodeBG[i]);
    }
}
MB_NodeChapterRankUint* MB_NodeChapterRankUint::create(MB_ChapterRankData* data)
{
    MB_NodeChapterRankUint* ptr = new MB_NodeChapterRankUint();
    if (ptr && ptr->init(data))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}
bool MB_NodeChapterRankUint::init(MB_ChapterRankData* data)
{
    CC_SAFE_RELEASE_NULL(m_pData);
    m_pData = data;
    CC_SAFE_RETAIN(m_pData);
    CCNode* pNode = loadResource("res/pve_layer_billboard_unit.ccbi");
    if(pNode)
	{
		addChild(pNode);
        onResetWnd();
		return true;
	}
	return false;
}
void MB_NodeChapterRankUint::onResetWnd()
{
    if (m_pData == NULL)
    {
        return;
    }
    m_pTTFName->setString(m_pData->getName().c_str());
    char str[32] = "";
    sprintf(str,"%d",m_pData->getLv());

    
    m_pNodeLv->setString(str);
    
    NSGameHelper::setRoleIcon(m_pSpriteHead, m_pData->getIsMale(), m_pData->getHead(), m_pData->getTitle());
    
    
    
//    MB_ChapterData* pChapterData = NULL;
//    MB_AbsolvedConfigure::getInstance()->queryChapterDataByChapterID(m_pData->getChapterID(), &pChapterData);
//    if (pChapterData != NULL)
//    {
////        m_pTTFChapter->setString(pPage->getName().c_str());
//    }
    m_pTTFChapter->setString(m_pData->getDungeonName().c_str());
    
    if (m_pData->getRank() == 1)
    {
        m_pNodeBG[0]->setVisible(true);
    }
    else if(m_pData->getRank() == 2)
    {
        m_pNodeBG[1]->setVisible(true);
    }
    else if(m_pData->getRank() == 3)
    {
        m_pNodeBG[1]->setVisible(true);
    }
    else if(m_pData->getRank() <= 10)
    {
        m_pNodeBG[3]->setVisible(true);
    }
    else
    {
        m_pNodeBG[4]->setVisible(true);
    }
    
    char buff[30];
    sprintf(buff,"%d",m_pData->getRank());
    m_pNodeRankNum->setString(buff);
    
}
bool MB_NodeChapterRankUint::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpriteFrame",CCSprite*,m_pSpriteFrame);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpriteHead",CCSprite*,m_pSpriteHead);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFName",CCLabelTTF*,m_pTTFName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeLv",CCLabelBMFont*,m_pNodeLv);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFChapter",CCLabelTTF*,m_pTTFChapter);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize",CCNode*,m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeRankNum",CCLabelBMFont*,m_pNodeRankNum);
    
    char str[32] = "m_pNodeBG1";
    for(int i = 0;i < 5;i++)
    {
        str[9] = '1' + i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this,str,CCNode*,m_pNodeBG[i]);
    }
    return false;
}
SEL_MenuHandler MB_NodeChapterRankUint::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onInfoClicked",MB_NodeChapterRankUint::onInfoClicked);
    return NULL;
}
SEL_CCControlHandler MB_NodeChapterRankUint::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}
void MB_NodeChapterRankUint::onInfoClicked(CCObject* pSender)
{
    if(MB_RoleData::getInstance()->getUID() == m_pData->getRoleID())
    {
        return;
    }
    MB_TeamData::getInstance()->sendpet_view_other(m_pData->getRoleID(),0);
}
CCSize MB_NodeChapterRankUint::getSize()
{
    static CCSize sz = CCSizeMake(-1, 0);
    
    if (sz.width < 0 )
    {
        MB_NodeChapterRankUint* pNode = new MB_NodeChapterRankUint;
        pNode->loadResource("res/pve_layer_billboard_unit.ccbi");
        sz = pNode->m_pNodeSize->getContentSize();
        CC_SAFE_RELEASE_NULL(pNode);
    }
    return sz;
}

