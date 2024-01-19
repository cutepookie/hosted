//
//  MB_NodeRolePKQ.cpp
//  ProjectMB
//
//  Create by wenyong on 26/11/2014.
//
//
#include "MB_NodeRolePKQ.h"
MB_NodeRolePKQ* MB_NodeRolePKQ::create(int index)
{
    MB_NodeRolePKQ* ptr = new MB_NodeRolePKQ();
    if (ptr && ptr->init(index))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}
MB_NodeRolePKQ::MB_NodeRolePKQ()
{
    m_pNodeSize	 = NULL;
    m_pSpr = NULL;
    m_bCanJump = true;
    m_pAnimationMgr = NULL;
}
MB_NodeRolePKQ::~MB_NodeRolePKQ()
{
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
        CC_SAFE_RELEASE_NULL(m_pSpr);

    CC_SAFE_RELEASE_NULL(m_pAnimationMgr);
}
bool MB_NodeRolePKQ::init(int index)
{
    CCNode* pNode;
    if (index==1) {
        pNode = loadResource("res/pkq_tiao.ccbi");
    }else
    {
        pNode = loadResource("res/pkq_tiao.ccbi");
    }
    
    if(pNode)
    {
        addChild(pNode);
        setContentSize(m_pNodeSize->getContentSize());
        m_pAnimationMgr->setAnimationCompletedCallback(this, callfunc_selector(MB_NodeRolePKQ::onAnimationFinished));
        return true;
    }
    return false;
}

void MB_NodeRolePKQ::onAnimationFinished()
{
    if (m_pAnimationMgr->getLastCompletedSequenceName().compare("jump")==0)
    {
        runAction(CCSequence::create(CCDelayTime::create(0.5f),CCCallFunc::create(this, callfunc_selector(MB_NodeRolePKQ::recoveryJump)),NULL));
    }
}

void MB_NodeRolePKQ::recoveryJump()
{
    m_bCanJump = true;
}
void MB_NodeRolePKQ::onResetWnd()
{
    
}
bool MB_NodeRolePKQ::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize",CCNode*,m_pNodeSize);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpr",CCSprite*,m_pSpr);
    
    return false;
}

CCNode* MB_NodeRolePKQ::loadResource(const char* pName)
{
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile(pName, this);
    m_pAnimationMgr = pCCBReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pAnimationMgr);
    CC_SAFE_RELEASE(pCCBReader);
    
    return pNode;
}
void MB_NodeRolePKQ::setSprFilpX(bool b)
{
    m_pSpr->setFlipX(b);
}
bool MB_NodeRolePKQ::isSprFlipX()
{
    m_pSpr->isFlipX();
}
void MB_NodeRolePKQ::run()
{
    if (m_pAnimationMgr)
    {
        m_pAnimationMgr->runAnimationsForSequenceNamed("run");
    }
}

void MB_NodeRolePKQ::jump()
{
    if (m_pAnimationMgr && m_bCanJump)
    {
        m_bCanJump = false;
        m_pAnimationMgr->runAnimationsForSequenceNamed("jump");
    }
}

void MB_NodeRolePKQ::onExit()
{
    m_pAnimationMgr->setAnimationCompletedCallback(NULL, NULL);
    MB_ResWindow::onExit();
}
