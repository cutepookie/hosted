//
//  MB_LayerScale9Sprite.cpp
//  ProjectPM
//
//  Created by WenYong on 14-5-6.
//
//
#include "MB_FunctionModule.h"
#include "MB_LayerScale9Sprite.h"
#include "MB_LayerShielding.h"
MB_LayerScale9SpriteTest::MB_LayerScale9SpriteTest()
{
    m_pSprite0=NULL;
    m_pSprite1=NULL;
}
MB_LayerScale9SpriteTest::~MB_LayerScale9SpriteTest()
{
    CC_SAFE_RELEASE_NULL(m_pSprite0);
    CC_SAFE_RELEASE_NULL(m_pSprite1);
}


bool MB_LayerScale9SpriteTest::init()
{
    CCNode* pNode = loadResource("res/testlist.ccbi");
    if (pNode)
    {
        addChild(pNode);
        //onResetWnd(); // called only once
        return true;
    }
    return false;
}



void MB_LayerScale9SpriteTest::onResetWnd()
{
    NSGameHelper::AutoScale9Sprite(m_pSprite0);
    NSGameHelper::AutoScale9Sprite(m_pSprite1);
}

bool MB_LayerScale9SpriteTest::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "test_sprite0", CCScale9Sprite*, m_pSprite0);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "test_sprite1", CCScale9Sprite*, m_pSprite1);
    return false;
}