//
//  MB_LayerPetAttibutes.cpp
//  ProjectMB
//
//  Create by WenYong on 25/9/2014.
//
//
#include "MB_LayerPetAttibutes.h"
#include "MB_petData.h"

MB_LayerPetAttibutes::MB_LayerPetAttibutes()
{
    for (int i=0; i<16; ++i)
    {
        m_pAttribute[i] = NULL;
    }
    m_pNodeSize = NULL;
}
MB_LayerPetAttibutes::~MB_LayerPetAttibutes()
{
    for (int i=0; i<16; ++i)
    {
        CC_SAFE_RELEASE_NULL(m_pAttribute[i]);
    }
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
}
bool MB_LayerPetAttibutes::init()
{
    CCNode* pNode = loadResource("res/cart_attribute_layer.ccbi");
    if(pNode)
	{
		addChild(pNode);
        this->setContentSize(m_pNodeSize->getContentSize());
		return true;
	}
	return false;
}

MB_LayerPetAttibutes* MB_LayerPetAttibutes::create(MB_PetData* pData)
{
    MB_LayerPetAttibutes* pInstance = new MB_LayerPetAttibutes;
    if (pInstance && pInstance->init())
    {
        pInstance->autorelease();
        pInstance->m_pData = pData;
        pInstance->onResetWnd();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

void MB_LayerPetAttibutes::onResetWnd()
{
    if (m_pData)
    {
        char buff[64] = {};
        sprintf(buff, "%s%d",m_pAttribute[0]->getString(),m_pData->getPetAttack());
        m_pAttribute[0]->setString(buff);
        
        sprintf(buff, "%s%d",m_pAttribute[1]->getString(),m_pData->getPetHpMax());
        m_pAttribute[1]->setString(buff);
        if (m_pData->getPetID() == 0 || !MB_TeamData::getInstance()->checkInTeam(m_pData))
        {
            installAttribute(m_pData->getTemplete()->getTalentList());
        }
        else
        {
            installAttribute(m_pData->getOnlineAttribute());
        }
    }
}

void MB_LayerPetAttibutes::installAttribute(CCArray* pArray)
{
    char buff[64] = {};
    float dataNum = 0;
    MB_DestinyAttribute * obj = NULL;
    for (int i = 2; i < 16 ; i++)
    {
        dataNum = 0;
        CCARRAY_FOREACH_4TYPE(pArray, MB_DestinyAttribute *, obj)
        {
            if(obj->getType() == (i+1))
            {
                dataNum = ((MB_DestinyAttribute *)obj)->getValue();
                break;
            }
        }
        
        if (i == 12 || i == 13)
        {
            sprintf(buff, "%s%.0f%%",m_pAttribute[i]->getString(),dataNum/100.0f);
        }
        else
        {
            sprintf(buff, "%s%.0f",m_pAttribute[i]->getString(),dataNum);
        }
        m_pAttribute[i]->setString(buff);
    }

}

bool MB_LayerPetAttibutes::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"attribute3",CCLabelTTF*,m_pAttribute[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"attribute1",CCLabelTTF*,m_pAttribute[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"attribute5",CCLabelTTF*,m_pAttribute[4]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"attribute7",CCLabelTTF*,m_pAttribute[6]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"attribute9",CCLabelTTF*,m_pAttribute[8]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"attribute11",CCLabelTTF*,m_pAttribute[10]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"attribute15",CCLabelTTF*,m_pAttribute[14]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"attribute13",CCLabelTTF*,m_pAttribute[12]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"attribute2",CCLabelTTF*,m_pAttribute[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"attribute4",CCLabelTTF*,m_pAttribute[3]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"attribute6",CCLabelTTF*,m_pAttribute[5]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"attribute8",CCLabelTTF*,m_pAttribute[7]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"attribute10",CCLabelTTF*,m_pAttribute[9]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"attribute14",CCLabelTTF*,m_pAttribute[13]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"attribute16",CCLabelTTF*,m_pAttribute[15]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"attribute12",CCLabelTTF*,m_pAttribute[11]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize",CCNode*,m_pNodeSize);
	return false;
}
