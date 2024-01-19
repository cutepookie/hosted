

#include "MB_NodeItemDebris.h"
#include "../Common/GameLib/GameHelper/CCGameHelper.h"
#include "MB_LayerBackpack.h"
#include "MB_NodeRewardCard.h"
#include "MB_LayerBackpack.h"
#include "MB_LayerItemDetail.h"
MB_NodeItemDebris::MB_NodeItemDebris()
{
    for (int i = 0;i < 7; i++)
    {
        m_pStar[i] = NULL;
    }

    m_pNodeSize = NULL;
    m_pTTFName = NULL;
    m_pTTFDescription = NULL;
    m_pNodeCompose = NULL;
    m_pTTFCount = NULL;
    m_uPetUid = 0;
    m_pSpriteIcon = NULL;
    m_pSpriteFrame = NULL;
    m_uPetTid = 0;
    
}

MB_NodeItemDebris::~MB_NodeItemDebris()
{
    for (int i = 0;i < 7; i++)
    {
        CC_SAFE_RELEASE_NULL(m_pStar[i]);
    }
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(m_pTTFName);
    CC_SAFE_RELEASE_NULL(m_pTTFDescription);
    CC_SAFE_RELEASE_NULL(m_pNodeCompose);
    CC_SAFE_RELEASE_NULL(m_pTTFCount);
    CC_SAFE_RELEASE_NULL(m_pSpriteIcon);
    CC_SAFE_RELEASE_NULL(m_pSpriteFrame);
    
}

MB_NodeItemDebris* MB_NodeItemDebris::create(uint64_t uid)
{
    MB_NodeItemDebris* ptr = new MB_NodeItemDebris;
    if (ptr && ptr->init(uid))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}
bool MB_NodeItemDebris::init(uint64_t uid)
{
    m_uPetUid = uid;
    CCNode* pNode = loadResource("res/item_node_compose.ccbi");
    if(pNode)
	{
		addChild(pNode);
        onResetWnd();
		return true;
	}
	return false;
}

void MB_NodeItemDebris::onResetWnd(void)
{
    MB_ItemData* data = MB_ItemMgr::getInstance()->getItemDataByUID(m_uPetUid);
    MB_ItemTemplate* templete = NULL;
    if (data != NULL) {
        m_uPetTid = data->getItemID();
        templete = MB_ItemMgr::getInstance()->getItemTemplateByID(m_uPetTid);
    }
    if (templete == NULL)
    {
        return;
    }
    
    //星级
    for (int i = 0;i < 7;i++)
    {
        if (i < templete->getItemStar())
        {
            m_pStar[i]->setVisible(true);
        }
        else
        {
            m_pStar[i]->setVisible(false);
        }
    }
    
    //数量
    char str[100];
    sprintf(str,"数量:%d/%d",data->getItemNumber(),templete->getComposeNum());
    m_pTTFCount->setString(str);
    
    
    //合成按钮
    if (data->getItemNumber() >= templete->getComposeNum())
    {
        m_pNodeCompose->setVisible(true);
    }
    else
    {
        m_pNodeCompose->setVisible(false);
    }
    
    //描述
    m_pTTFDescription->setString(templete->getItemDesc());
    
    NSGameHelper::setItemIconDetailByUid(m_uPetUid,m_pSpriteIcon,m_pTTFName,m_pSpriteFrame);
}


cocos2d::SEL_MenuHandler MB_NodeItemDebris::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onComposeClicked",MB_NodeItemDebris::onComposeClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onDetailClicked",MB_NodeItemDebris::onDetailClicked);
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_NodeItemDebris::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName)
{
    return NULL;
}
bool MB_NodeItemDebris::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode)
{
    TutorialAssignLayerWindow
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeSize", CCNode *,m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTTFName", CCLabelTTF *,m_pTTFName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTTFDescription", CCLabelTTF *,m_pTTFDescription);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeCompose", CCNode*,m_pNodeCompose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTTFCount", CCLabelTTF *,m_pTTFCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteIcon", CCSprite *,m_pSpriteIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteFrame", CCSprite *,m_pSpriteFrame);
    
    char str[20] = "m_pStar1";
    for (int i = 0;i < 7; i++)
    {
        str[7] = '1'+i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, str, CCSprite*,m_pStar[i]);
    }
    return false;
}
void MB_NodeItemDebris::onDetailClicked(CCObject* pSender)
{
    MB_ItemData* data = MB_ItemMgr::getInstance()->getItemDataByUID(m_uPetUid);
    MB_ItemTemplate* templete = NULL;
    if (data != NULL) {
        templete = MB_ItemMgr::getInstance()->getItemTemplateByID(data->getItemID());
    }
    if (templete == NULL)
    {
        return;
    }
    uint16_t tid = templete->getComposeItemID();
    
    MB_ResWindow* layer = MB_LayerItemDetail::createByType(tid);
    MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
    if (pScene)
    {
        pScene->addChild(layer,Z_ORDER_Detail);
    }else{
        CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
    }
}
void MB_NodeItemDebris::onComposeClicked(CCObject* pSender)
{
    TutorialTriggerComplete
    MB_ItemData* data = MB_ItemMgr::getInstance()->getItemDataByUID(m_uPetUid);
    MB_ItemTemplate* templete = NULL;
    if (data != NULL) {
        templete = MB_ItemMgr::getInstance()->getItemTemplateByID(data->getItemID());
    }
    if (templete == NULL)
    {
        return;
    }
    uint16_t tid = templete->getItemID();
    
    MB_Message::sharedMB_Message()->showMessage("",30);
    MB_ItemMgr::getInstance()->senditem_compound(tid);

}
const  CCSize & MB_NodeItemDebris::getSize()
{
    static CCSize sz = CCSizeMake(-1, 0);
    
    if (sz.width < 0 )
    {
        MB_NodeItemDebris* pNode = new MB_NodeItemDebris;
        pNode->loadResource("res/item_node_compose.ccbi");
        sz = pNode->m_pNodeSize->getContentSize();
        CC_SAFE_RELEASE_NULL(pNode);
    }
    return sz;
}

void MB_NodeItemDebris::onMsgRecv(CCNode* node, SocketResponse* response)
{
}




