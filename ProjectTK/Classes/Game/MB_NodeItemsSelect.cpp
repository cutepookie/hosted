//
//  MB_NodeItemsSelect.cpp
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-19.
//
//

#include "MB_NodeItemsSelect.h"
#include "Game.h"

MB_NodeItemsSelect::MB_NodeItemsSelect()
{

}

MB_NodeItemsSelect::~MB_NodeItemsSelect()
{

}

MB_NodeItemsSelect* MB_NodeItemsSelect::create(uint64_t nUid,uint16_t nType)
{
    MB_NodeItemsSelect* pInstance = new MB_NodeItemsSelect;
    if (pInstance && pInstance->init(nUid,nType))
    {
        pInstance->autorelease();
        return pInstance;
    }

    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}
bool MB_NodeItemsSelect::init(uint64_t nUid,uint16_t nType)
{
    m_nType = nType;
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/item_node_select.ccbi", this);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    if (pNode == NULL)
    {
        return false;
    }

    m_nItemUID = nUid;

    addChild(pNode);

    onResetWnd();

    return true;
}

bool MB_NodeItemsSelect::setItemAttrPair(MB_ItemData* pMB_ItemData,int nAttrType,AttrPair& attrPair)
{
    if (pMB_ItemData == NULL)
    {
        return false;
    }

    MB_ItemTemplate* pTemplate = MB_ItemMgr::getInstance()->getItemTemplateByID(pMB_ItemData->getItemID());
    if (!pTemplate->containsAtrribute((eItem_Attribute_Type)nAttrType))
    {
        return false;
    }

    sDesCommon* pItemCommon = MB_ItemMgr::getInstance()->getItemAttributeCommon(nAttrType);
    if(pItemCommon)
    {
        MB_ItemMgr::getInstance()->setSpriteFrame(attrPair.m_pIcon, pItemCommon->queryValue("Icon").toString().c_str());
    }

    char buff[25] = {};
    
    
    int value = pTemplate->getAtrribute((eItem_Attribute_Type)nAttrType, pMB_ItemData);
    if(nAttrType == eItem_Attribute_Type_Absorb || nAttrType == eItem_Attribute_Type_DamageBack){
        
        
        sprintf(buff,"%.2f%%",value/100.0f);
        
    }else {
        
        sprintf(buff, "%d",value);
    }

    attrPair.m_pValue->setString(buff);
    attrPair.show();
    return true;
}

void MB_NodeItemsSelect::onResetWnd()
{
    MB_NodeSelect::onResetWnd();

    MB_ItemData* pData = MB_ItemMgr::getInstance()->getItemDataByUID(m_nItemUID);
    if (pData)
    {
        int index = 0;
        for (int i=1; i<eItem_Attribute_Type_Count; ++i)
        {
            if(setItemAttrPair(pData, i, m_AttrPair[index]))
            {
                index++;
                if (index==4)
                {
                    break;
                }
            }
        }
        for (; index<4; ++index)
        {
            m_AttrPair[index].hide();
        }
    }
}

bool MB_NodeItemsSelect::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    if (strcmp(pMemberVariableName, "size") == 0)
    {
        m_nSize = pNode->getContentSize();
        return false;
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btn_1", CCControlButton*, m_pBtn1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "name", CCLabelTTF*, m_pName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_menus", CCNode*, m_pNodeMenu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_buttons", CCNode*, m_pNodeButton);
    char buff[64] = {};
    for (int i=0; i<4; ++i)
    {
        sprintf(buff,"EffetType%dDes", i+1);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, buff, CCLabelTTF*, m_AttrPair[i].m_pValue);
        sprintf(buff,"EffetType%d", i+1);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, buff, CCSprite*, m_AttrPair[i].m_pIcon);
    }

    for (int i=0; i<7; ++i)
    {
        sprintf(buff,"star%d", i+1);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, buff, CCNode*,m_pStars[i]);
    }

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "IconPos", CCNode*, m_pNodeIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "menu_text", CCLabelTTF*, m_pMenuText);

    if(strcasecmp("equip_attribute_board", pMemberVariableName) == 0 && pTarget == this)
    {
        pNode->setVisible(m_nType == 2);
    }
    return false;
}

SEL_MenuHandler MB_NodeItemsSelect::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{

    return NULL;
}

SEL_CCControlHandler MB_NodeItemsSelect::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onTreChooseClicked", MB_NodeItemsSelect::onButton1Clicked);
    return NULL;
}

void MB_NodeItemsSelect::onButton1Clicked(CCObject* pSender)
{
    MB_TARGET_PARENT(MB_NodeSelectDelegate,ptr);
    if (ptr)
    {
        if (getIsInputed())
        {
            ptr->onInputedNodeSelected(m_nItemUID, m_nType);
        }
        else
        {
            ptr->onNodeSelected(m_nItemUID, m_nType);
        }
    }
}