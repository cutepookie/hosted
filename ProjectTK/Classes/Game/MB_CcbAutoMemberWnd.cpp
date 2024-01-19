//
//  MB_CcbAutoMemberWnd.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-2.
//
//

#include "MB_CcbAutoMemberWnd.h"
#include "Game.h"


MB_CcbAutoMemberWnd::MB_CcbAutoMemberWnd()
{
    m_pMembers = new CCArray;
}
MB_CcbAutoMemberWnd::~MB_CcbAutoMemberWnd()
{
    removeAllChildren();
    CC_SAFE_RELEASE_NULL(m_pMembers);
    CC_SAFE_RELEASE(m_pMembers);
}
MB_MemberAttribult::MB_MemberAttribult()
{
    m_pNode = NULL;
}

MB_MemberAttribult::~MB_MemberAttribult()
{
    m_pNode->removeFromParent();
//    CC_SAFE_RELEASE(m_pNode);
}
MB_MemberAttribult* MB_MemberAttribult::create(const char* pName,CCNode* pNode)
{
    if (pName == NULL
        || pNode ==NULL)
    {
        return NULL;
    }
    
    MB_MemberAttribult* pInstance = new MB_MemberAttribult;
    if (pInstance)
    {
        pInstance->m_pName = pName;
        pInstance->m_pNode = pNode;
//        pNode->retain();
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

MB_CcbAutoMemberWnd* MB_CcbAutoMemberWnd::create(const char* pCcbFile)
{
    MB_CcbAutoMemberWnd* pInstance = new MB_CcbAutoMemberWnd;
    if (pInstance && pInstance->init(pCcbFile))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

bool MB_CcbAutoMemberWnd::init(const char* pCcbFile)
{
//    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
//    CCNode* pNode = pCCBReader->readNodeGraphFromFile(pCcbFile, this);
//    if (pNode)
//    {
//        addChild(pNode);
//        CC_SAFE_RELEASE_NULL(pCCBReader);
//        return true;
//    }
//    CC_SAFE_RELEASE_NULL(pCCBReader);
    CCNode* pNode = loadResource(pCcbFile);
    if (pNode)
    {
        addChild(pNode);
        return true;
    }
    return false;
}

CCNode* MB_CcbAutoMemberWnd::operator[](const char* pNodeName)
{
    MB_MemberAttribult* pTemp = NULL;
    CCARRAY_FOREACH_4TYPE(m_pMembers, MB_MemberAttribult*, pTemp)
    {
        if (pTemp->m_pName.compare(pNodeName)==0)
        {
            return pTemp->m_pNode;
        }
    }
    return NULL;
}

bool MB_CcbAutoMemberWnd::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    if (pTarget != this)
    {
        return false;
    }
    MB_MemberAttribult* pMember = MB_MemberAttribult::create(pMemberVariableName, pNode);
    if (pMember)
    {
        m_pMembers->addObject(pMember);
        return false;
    }
    return false;
}