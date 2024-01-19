//
//  MB_RoleLayerSelectPartner.cpp
//  ProjectMB
//
//  Create by wenyong on 22/1/2015.
//
//
#include "MB_RoleLayerSelectPartner.h"
#include "../Common/GameLib/GameHelper/CCGameHelper.h"
#include "MB_LayerAnimation.h"
MB_RoleLayerSelectPartner::MB_RoleLayerSelectPartner()
{
    m_pNodePartner1	 = NULL;
    m_pNodePartner2	 = NULL;
    m_pNodePartner3	 = NULL;
    m_pMenuItemImageLeft	 = NULL;
    m_pMenuItemImageRight	 = NULL;
    m_pAnimation = NULL;
    m_pInitMonster[0] = 0;
    m_pInitMonster[1] = 0;
    m_pInitMonster[2] = 0;
}
MB_RoleLayerSelectPartner::~MB_RoleLayerSelectPartner()
{
    CC_SAFE_RELEASE_NULL(m_pAnimation);
    CC_SAFE_RELEASE_NULL(m_pNodePartner1);
    CC_SAFE_RELEASE_NULL(m_pNodePartner2);
    CC_SAFE_RELEASE_NULL(m_pNodePartner3);
    CC_SAFE_RELEASE_NULL(m_pMenuItemImageLeft);
    CC_SAFE_RELEASE_NULL(m_pMenuItemImageRight);
}

CCNode* MB_RoleLayerSelectPartner::loadResource(const char* pName)
{
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile(pName, this);
    m_pAnimation = pCCBReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pAnimation);
    CC_SAFE_RELEASE(pCCBReader);
    
    return pNode;
}

void MB_RoleLayerSelectPartner::runAnimation()
{
    MB_LayerAnimation* p = MB_LayerAnimation::create("res/excessive_layer.ccbi");
    if (p)
    {
        addChild(p);
        p->runAnimationWithCallBack("2", this, callfuncN_selector(MB_RoleLayerSelectPartner::animationCallBack));
    }
}
void MB_RoleLayerSelectPartner::animationCallBack(CCNode* pNode)
{
    if (pNode)
    {
        pNode->removeFromParent();
    }
}
bool MB_RoleLayerSelectPartner::init()
{
    CCNode* pNode = loadResource("res/role_layer_choosepet.ccbi");
    if(pNode)
	{
        addChild(NSGameHelper::createDisableTouchLayer());
		addChild(pNode);
        runAnimation();
        
        char str[10] = "choose1";
        int aid = 0;
        for (int i = 0;i < 3;i++)
        {
            str[6] = '1'+i;
            aid = m_pAnimation->getSequenceId(str);
            m_pAnimation->getSequence(aid)->setChainedSequenceId(aid);
        }
        
        loadConfig();
        m_nSelectType = 2;
        reset();
		return true;
	}
	return false;
}

bool MB_RoleLayerSelectPartner::loadConfig()
{
    MB_XmlFile* pFile = MB_XmlFile::create("config/firstcard.xml");
    if (pFile)
    {
        CCArray* pArray = CCArray::create();
        if(pFile->queryNodesByName("petlist|pet", pArray))
        {
            MB_XmlNode* pTemp = NULL;
            int index = 0;
            CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pTemp)
            {
                m_pInitMonster[index++] = pTemp->queryAttributeByName("typeid")->intValue();
                if (index == 3)
                {
                    break;
                }
            }
            return true;
        }
    }
    return false;
}

void MB_RoleLayerSelectPartner::onResetWnd()
{

}
bool MB_RoleLayerSelectPartner::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodePartner1",CCNode*,m_pNodePartner1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodePartner2",CCNode*,m_pNodePartner2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodePartner3",CCNode*,m_pNodePartner3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMenuItemImageLeft",CCMenuItemImage*,m_pMenuItemImageLeft);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMenuItemImageRight",CCMenuItemImage*,m_pMenuItemImageRight);
	return false;
}
SEL_MenuHandler MB_RoleLayerSelectPartner::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_RoleLayerSelectPartner::onCloseClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onLeftClicked",MB_RoleLayerSelectPartner::onLeftClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onRightClicked",MB_RoleLayerSelectPartner::onRightClicked);
	return NULL;
}
SEL_CCControlHandler MB_RoleLayerSelectPartner::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onEnterClicked", MB_RoleLayerSelectPartner::onEnterClicked);
	return NULL;
}
void MB_RoleLayerSelectPartner::onCloseClick(CCObject* pSender)
{
    popWindow();
}
void MB_RoleLayerSelectPartner::onLeftClicked(CCObject* pSender)
{
    if (m_nSelectType == 0)
    {
        m_nSelectType = 2;
    }
    else
    {
        --m_nSelectType;
    }
    reset();
}
void MB_RoleLayerSelectPartner::onRightClicked(CCObject* pSender)
{
    if (m_nSelectType < 2)
    {
        ++m_nSelectType;
    }
    else
    {
        m_nSelectType = 0;
    }
    
    reset();
}

void MB_RoleLayerSelectPartner::reset()
{
    if (m_nSelectType == 0)
    {
        selectPartner3();
    }
    else if(m_nSelectType == 1)
    {
        selectPartner1();
    }
    else if(m_nSelectType == 2)
    {
        selectPartner2();
    }
}

void MB_RoleLayerSelectPartner::selectPartner1() // 火龙
{
    if (m_pAnimation)
    {
        m_pNodePartner2->setVisible(false);
        m_pNodePartner1->setVisible(true);
        m_pNodePartner3->setVisible(false);
        m_pAnimation->runAnimationsForSequenceNamed("choose1");
    }
}

void MB_RoleLayerSelectPartner::selectPartner2() // 乌龟
{
    if (m_pAnimation)
    {
        m_pNodePartner2->setVisible(true);
        m_pNodePartner1->setVisible(false);
        m_pNodePartner3->setVisible(false);
        m_pAnimation->runAnimationsForSequenceNamed("choose2");
    }
}

void MB_RoleLayerSelectPartner::selectPartner3() // 妙娃
{
    if (m_pAnimation)
    {
        m_pNodePartner2->setVisible(false);
        m_pNodePartner1->setVisible(false);
        m_pNodePartner3->setVisible(true);
        m_pAnimation->runAnimationsForSequenceNamed("choose3");
    }
}

void MB_RoleLayerSelectPartner::onEnterClicked(CCObject* pSender)
{
    MB_TARGET_PARENT(MB_SceneRoleCreate, ptr);
    if (ptr!=NULL)
    {
        ptr->onMonsterSeleted(m_pInitMonster[m_nSelectType]);
    }
}
