//
//  MB_NodeEntryUint.cpp
//  ProjectPM
//
//  Created by CRIMOON0073 on 14-7-17.
//
//

#include "MB_NodeEntryUint.h"
#include "MB_TutorialMgr.h"
#include "MB_FunctionMgr.h"
MB_NodeEntryUint::MB_NodeEntryUint()
{
    m_nType = 0;
}
void MB_NodeEntryUint::setFunctionType(int type)
{
    m_nType = type;
}
void MB_NodeEntryUint::onResetWnd()
{
    MB_FunctionItem* pItem =  MB_FunctionConfigure::getInstance()->queryFunctionItemByType(m_nType);
    if (pItem)
    {
        if(pItem->getNeedLevel()<=MB_RoleData::getInstance()->getLevel())
        {
            setEnable();
        }
        else
        {
            setDisable();
        }
    }
    m_pFlagNode2->setVisible(false);

}
void MB_NodeEntryUint::setEnable()
{
    MB_FunctionConfigure::getInstance()->loadResource2SpriteCache();
    MB_FunctionItem* pItem = MB_FunctionConfigure::getInstance()->queryFunctionItemByType(m_nType);
    if (pItem && !pItem->getEnableFile().empty())
    {
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pItem->getEnableFile().c_str());
        if (frame)
        {
            m_pItemImage->setNormalSpriteFrame(frame);
            m_pItemImage->setSelectedSpriteFrame(frame);
            m_pItemImage->setDisabledSpriteFrame(frame);
        }
    }
    NSGameHelper::setSpriteFrameWithFrameCache(m_pSpriteName, pItem->getNameEnable().c_str());
    m_bEnable = true;
}
void MB_NodeEntryUint::setDisable()
{
    MB_FunctionConfigure::getInstance()->loadResource2SpriteCache();
    MB_FunctionItem* pItem = MB_FunctionConfigure::getInstance()->queryFunctionItemByType(m_nType);
    if (pItem && !pItem->getDisableFile().empty())
    {
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pItem->getDisableFile().c_str());
        if (frame)
        {
            m_pItemImage->setNormalSpriteFrame(frame);
            m_pItemImage->setSelectedSpriteFrame(frame);
            m_pItemImage->setDisabledSpriteFrame(frame);
        }
    }
    NSGameHelper::setSpriteFrameWithFrameCache(m_pSpriteName, pItem->getNameDisable().c_str());
    m_bEnable = false;
}

void MB_NodeEntryUint::onEntranceClicked(CCObject* pSender)
{
    TutorialTriggerComplete
    if (m_bEnable)
    {
        goFunction();
    }
    else
    {
        MB_FunctionItem* pItem = MB_FunctionConfigure::getInstance()->queryFunctionItemByType(m_nType);
        if (pItem)
        {
            char buff[64] = {};
            sprintf(buff,"%s将在%d级开放",pItem->getFunctionName().c_str(),pItem->getNeedLevel());
            MB_Message::sharedMB_Message()->showMessage(buff);
        }
    }
}

void MB_NodeEntryUint::goFunction()
{
}
