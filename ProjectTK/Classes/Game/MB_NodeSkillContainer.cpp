//
//  MB_NodeSkillContainer.cpp
//  ProjectMB
//
//  Create by WenYong on 25/9/2014.
//
//
#include "MB_NodeSkillContainer.h"
#include "MB_petData.h"
static const std::string skillLimit[] =
{
    "",
    "",
    "[进化+2激活]",
    "[进化+5激活]",
    "[完成\"一转\"激活]",
    "[\"一转\"+5激活]",
    "[完成\"二转\"激活]",
    "",
};


MB_NodeSkillContainer2::MB_NodeSkillContainer2()
{
    m_pTTFSkillDes1 = NULL;
    m_pTTFSkillName1 = NULL;
    m_pSpriteSkillNormal = NULL;
    m_pSpriteSkillBig = NULL;
    m_pNodeSize = NULL;
    m_pData = NULL;
    m_pIcon = NULL;
}
MB_NodeSkillContainer2::~MB_NodeSkillContainer2()
{
    CC_SAFE_RELEASE_NULL(m_pTTFSkillDes1);
    CC_SAFE_RELEASE_NULL(m_pSpriteSkillNormal);
    CC_SAFE_RELEASE_NULL(m_pTTFSkillName1);
    CC_SAFE_RELEASE_NULL(m_pSpriteSkillBig);
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(m_pData);
    CC_SAFE_RELEASE_NULL(m_pIcon);
}
MB_NodeSkillContainer2* MB_NodeSkillContainer2::create(const char* petName,MB_SkillData* pData,int type)
{
    MB_NodeSkillContainer2* ptr = new MB_NodeSkillContainer2();
    if (ptr && ptr->init(petName,pData,type))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}
bool MB_NodeSkillContainer2::init(const char* petName,MB_SkillData* pData,int type)
{
    CCNode* pNode = loadResource("res/skill_unit_0.ccbi");
    if(pNode)
	{
        m_pData = pData;
        m_pData->retain();
		addChild(pNode);
        m_pSpriteSkillNormal->setVisible(type == kTypeSkillNormal);
        m_pSpriteSkillBig->setVisible(type == kTypeSkillBig);
        this->setContentSize(m_pNodeSize->getContentSize());
        m_pIcon->setTexture(CCTextureCache::sharedTextureCache()->addImage(petName));
        
        onRestWnd();
		return true;
	}
	return false;
}
void MB_NodeSkillContainer2::onRestWnd()
{
    if (m_pData == NULL)
    {
        return;
    }
    
    if (m_pData)
    {
        m_pTTFSkillName1->setString(m_pData->getSkillName());
        m_pTTFSkillDes1->setString(m_pData->getSkillDescription());
    }
    
}
bool MB_NodeSkillContainer2::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFSkillDes1",CCLabelTTF*,m_pTTFSkillDes1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFSkillName1",CCLabelTTF*,m_pTTFSkillName1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize",CCNode*,m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpriteSkillNormal",CCSprite*,m_pSpriteSkillNormal);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpriteSkillBig",CCSprite*,m_pSpriteSkillBig);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pIcon",CCSprite*,m_pIcon);
    return false;
}



MB_NodeSkillUint::MB_NodeSkillUint()
{
    m_pNodeSize = NULL;
    m_pTTFSkillName = NULL;
    m_pTTFLimit = NULL;
    m_pTTFSkillDes = NULL;
    m_pData = NULL;
    m_nIndex = 0;
    m_bActive = false;
    m_pLocked = NULL;
    m_pIcon = NULL;
}
MB_NodeSkillUint::~MB_NodeSkillUint()
{
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(m_pTTFSkillName);
    CC_SAFE_RELEASE_NULL(m_pTTFLimit);
    CC_SAFE_RELEASE_NULL(m_pTTFSkillDes);
    CC_SAFE_RELEASE_NULL(m_pData);
    CC_SAFE_RELEASE_NULL(m_pLocked);
    CC_SAFE_RELEASE_NULL(m_pIcon);
    
}
MB_NodeSkillUint* MB_NodeSkillUint::create(const char* petName,MB_SkillData* pData,int index,bool bActive)
{
    MB_NodeSkillUint* ptr = new MB_NodeSkillUint();
    if (ptr && ptr->init(petName,pData,index,bActive))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}
bool MB_NodeSkillUint::init(const char* petName,MB_SkillData* pData,int index,bool bActive)
{
    CCNode* pNode = loadResource("res/skill_unit_1.ccbi");
    if(pNode)
	{
        m_nIndex = index;
        m_pData = pData;
        m_bActive = bActive;
        CC_SAFE_RETAIN(m_pData);
		addChild(pNode);
        this->setContentSize(m_pNodeSize->getContentSize());
        m_pIcon->setTexture(CCTextureCache::sharedTextureCache()->addImage(petName));
        onRestWnd();
		return true;
	}
	return false;
}


void MB_NodeSkillUint::onRestWnd()
{
    if (m_pData == NULL)
    {
        return;
    }
    m_pTTFSkillName->setString(m_pData->getSkillName());
    m_pTTFSkillDes->setString(m_pData->getSkillDescription());
    m_pTTFLimit->setString(skillLimit[m_nIndex].c_str());
    
    if (m_bActive)
    {
        m_pLocked->setVisible(false);
    }
    else
    {
        m_pTTFLimit->setColor(ccRED);
        NSGameHelper::setColorGray(m_pIcon, true);
    }
}
bool MB_NodeSkillUint::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize",CCNode*,m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFSkillName",CCLabelTTF*,m_pTTFSkillName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFLimit",CCLabelTTF*,m_pTTFLimit);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFSkillDes",CCLabelTTF*,m_pTTFSkillDes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLocked",CCNode*,m_pLocked);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pIcon",CCSprite*,m_pIcon);
    
    return false;
}
