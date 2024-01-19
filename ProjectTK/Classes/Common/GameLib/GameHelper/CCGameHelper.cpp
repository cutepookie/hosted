//
//  CCGameHelper.cpp
//  ProjectSDS
//
//  Created by crimoon00007 on 14-3-4.
//
//

#include "CCGameHelper.h"
#include "../../../Game/MB_DataExchange.h"
#include "../../../Game/MB_LayerShielding.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "JavaCppHelper.h"
#endif

#include "AppDelegate.h"

#include "RichText.h"


#include "MB_GuardInterface.h"

#define CHECK_RETURN_BOOLEN(CONDITION,BOOLEN)  if((CONDITION))return (BOOLEN);

int NSGameHelper::getSrcType()
{
	int type = ACCOUNT_TYPE_NORMAL;

#ifdef PLATFORM_YJ
	type = ACCOUNT_TYPE_YJ;
#elif defined(YJ_IOS)
	type = ACCOUNT_TYPE_YJ;
#else
	type = ACCOUNT_TYPE_NORMAL;
#endif

	return type;
}
void NSGameHelper::setControlButtonTitleAllState(CCControlButton* pButton, const char* pTitle)
{
	assert(pButton);
	CCString* pString = CCString::create(pTitle);
	for (int i = 0; i < 4; ++i)
	{
		pButton->setTitleForState(pString, 1 << i);
	}
}
void NSGameHelper::setControlButtonTitleBMFontAllState(CCControlButton* pButton, const char* fntFile)
{
    assert(pButton);
    for (int i = 0; i < 4; ++i)
    {
        pButton->setTitleBMFontForState(fntFile, 1 << i);
    }
}
void NSGameHelper::setControlButtonTitleBMFontScale(CCControlButton* pButton,float sx,float sy)
{
    assert(pButton);
    for (int i = 0; i < 4; ++i)
    {
        pButton->getTitleLabelForState(1 << i)->setScale(sx,sy);
    }
}
void NSGameHelper::setMenuItemImage4AllState(CCMenuItemImage* pItemImage, const char* pFile)
{
	if (pItemImage == NULL
		|| pFile == NULL)
	{
		return;
	}
	CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pFile);
	if (frame)
	{
		pItemImage->setNormalSpriteFrame(frame);
		pItemImage->setSelectedSpriteFrame(frame);
		pItemImage->setDisabledSpriteFrame(frame);
	}

}
void NSGameHelper::setQualityColor(CCNodeRGBA* pDest, int star)
{
}
CCSpriteFrame* NSGameHelper::createSpriteFrame(const char* pFile)
{
	CCTexture2D *textrue = CCTextureCache::sharedTextureCache()->addImage(pFile);
	if (textrue != NULL)
	{
		CCSpriteFrame * frame = CCSpriteFrame::createWithTexture(textrue, CCRect(0, 0, textrue->getContentSize().width, textrue->getContentSize().height));
		return frame;
	}
	return NULL;
}

void NSGameHelper::setSpriteFrameWithFrameCache(CCSprite* pSprite, const char* pFile)
{
	CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pFile);
	if (frame != NULL) {

		pSprite->setDisplayFrame(frame);
	}
}

void NSGameHelper::setSpriteFrame(CCSprite* pSprite, const char* pFile)
{
	if (pSprite == NULL)
	{
		return;
	}

	CCSpriteFrame * frame = NSGameHelper::createSpriteFrame(pFile);
	if (frame)
	{
		pSprite->setDisplayFrame(frame);
	}
}


CCLayer* NSGameHelper::createDisableTouchLayer()
{
	return MB_LayerUnTouchable::create();
	//    CCSize sz = CCDirector::sharedDirector()->getWinSize();
	//    CCLayer* message = MB_LayerShielding::create(sz.width, sz.height);
	//    return message;

}

CCLayer* NSGameHelper::createDisableTouchLayer1()
{
	return MB_LayerUnTouchable::create();
	//    CCSize sz = CCDirector::sharedDirector()->getWinSize();
	//    CCLayer* message = MB_LayerShielding::create(sz.width, sz.height-70);
	//    return message;
}
CCLayer* NSGameHelper::createDisableTouchLayer12()
{
	return MB_LayerUnTouchable::create();
	//    CCSize sz = CCDirector::sharedDirector()->getWinSize();
	//    CCLayer* message = MB_LayerShielding::create(sz.width, sz.height-220);
	//    return message;
}
CCLayer* NSGameHelper::createDisableTouchLayerAll()
{
    return MB_LayerUnTouchable2::create();
}
const char* NSGameHelper::formatTimeStringDHM(int iLeftTime)
{
	static char buff[128] = {};
    sprintf(buff,"%d天%02d时%02d分",iLeftTime/(3600*24),iLeftTime%(3600*24)/3600,iLeftTime%3600/60);
	return buff;
}

const char* NSGameHelper::formatTimeStringDHMS(int iLeftTime)
{
	static char buff[128] = {};
    sprintf(buff,"%d天%02d时%02d分%02d秒",iLeftTime/(3600*24),iLeftTime%(3600*24)/3600,iLeftTime%3600/60,iLeftTime%3600%60);
	return buff;
}

const char* NSGameHelper::formatTimeStringHMS(int iLeftTime)
{
	static char buff[128] = {};
    sprintf(buff,"%02d:%02d:%02d",iLeftTime/3600,iLeftTime%3600/60,(iLeftTime%3600)%60);
	return buff;
}

const char* NSGameHelper::formatTimeStringHMS_colon(int iLeftTime)
{
	static char buff[128] = {};
    sprintf(buff,"%02d:%02d:%02d", iLeftTime / 3600, iLeftTime % 3600 / 60, (iLeftTime % 3600) % 60);
	return buff;
}



void NSGameHelper::setQualityFrameByStar(CCSprite* pSprite, int star)
{
	if (pSprite)
	{
		const MB_CardProperty* pty = MB_CardPropertyMgr::getInstance()->getCardPropertyByStar(star);
		if (pty)
		{
			pSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pty->getCardFrame()));
			//NSGameHelper::setSpriteFrame(pSprite, pty->getCardFrame());
		}
	}
}

void NSGameHelper::setColorByStar(CCNodeRGBA* pDest, int star)
{
    //TODODO 不根据品质改变字体颜色
    if (pDest)
    {
        const MB_CardProperty* pty = MB_CardPropertyMgr::getInstance()->getCardPropertyByStar(star);
        if (pty)
        {
            pDest->setColor(pty->getHeadFrameColor());
        }
    }
}
void NSGameHelper::setHeadFrame(CCSprite* pSprite, int star, int type, int rank, bool bCircle)
{
	if (!pSprite)
	{
		MB_LOG("ERROR: NSGameHelper::");
	}
	const MB_CardProperty* pty = MB_CardPropertyMgr::getInstance()->getCardPropertyByStar(star);
	//NSGameHelper::setSpriteFrame(pSprite,pty->getHeadFrame(type));
	if (pty)
	{
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("global.plist");
		CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(bCircle ? pty->getHeadCircleFrame(type) : pty->getHeadFrame(type));
		if (pFrame)
		{
			pSprite->setDisplayFrame(pFrame);
		}
		if (MONSTER_HEADFRAME == type)
		{
			getHeadEffectsByRank(pSprite, rank);
		}
	}
}


bool NSGameHelper::setItemIconDetailByUid(uint64_t uid, CCSprite* pIcon, CCLabelTTF* pName, CCSprite* pFrame, bool bCircle)
{
	MB_ItemData* pData = MB_ItemMgr::getInstance()->getItemDataByUID(uid);
	bool ret = false;
	if (pData)
	{
		ret = NSGameHelper::setItemIconDetailByTid(pData->getItemID(), pData->getItemRank(), pIcon, pName, pFrame, bCircle);
		int nRank = (pData->getItemRank()) % 10;
		if (nRank > 0 && pName != NULL) {
			char buff[64] = {};
			sprintf(buff, "%s+%d", pName->getString(), nRank);
			pName->setString(buff);
		}
	}

	return ret;
}

bool NSGameHelper::setItemIconDetailByTid(uint16_t tid, uint16_t rank, CCSprite* pIcon, CCLabelTTF* pName, CCSprite* pFrame, bool bCircle)
{
	MB_ItemTemplate *templete = MB_ItemMgr::getInstance()->getItemTemplateByID(tid);
	if (templete)
	{
		if (pIcon)
		{
            NSGameHelper::setSpriteFrame(pIcon, templete->getItemIcon());
//            if (bCircle)creatMaskSprite(pIcon);
			pIcon->removeAllChildrenWithCleanup(true);
//            CCNode* pNode = MB_CardPropertyMgr::getInstance()->creatEffectByRank(rank);
//            if (pNode)
//            {
//                pIcon->addChild(pNode);
//            }
		}

		if (pName)
		{
			pName->setString(templete->getItemName());
		}


		if (pFrame)
		{
			setHeadFrame(pFrame, templete->getItemStar(), ITEM_HEADFRAME, rank, bCircle);
		}


		return true;
	}
	else
	{
		return false;
	}
}
bool NSGameHelper::setItemIconDetailByUid2(uint64_t uid,CCSprite* pIcon,CCLabelTTF* pName,CCControlButton* pFrame,bool bCircle)
{
    MB_ItemData* pData = MB_ItemMgr::getInstance()->getItemDataByUID(uid);
    bool ret = false;
    if (pData)
    {
        ret = NSGameHelper::setItemIconDetailByTid2(pData->getItemID(), pData->getItemRank(), pIcon, pName, pFrame, bCircle);
        int nRank = (pData->getItemRank()) % 10;
        if (nRank > 0 && pName != NULL) {
            char buff[64] = {};
            sprintf(buff, "%s+%d", pName->getString(), nRank);
            pName->setString(buff);
        }
    }
    
    return ret;
}
bool NSGameHelper::setItemIconDetailByTid2(uint16_t tid,uint16_t rank,CCSprite* pIcon,CCLabelTTF* pName,CCControlButton* pFrame,bool bCircle)
{
    MB_ItemTemplate *templete = MB_ItemMgr::getInstance()->getItemTemplateByID(tid);
    if (templete)
    {
        if (pIcon)
        {
            NSGameHelper::setSpriteFrame(pIcon, templete->getItemIcon());
            pIcon->removeAllChildrenWithCleanup(true);
            CCNode* pNode = MB_CardPropertyMgr::getInstance()->creatEffectByRank(rank);
            if (pNode)
            {
                pIcon->addChild(pNode);
            }
        }
        
        if (pName)
        {
            pName->setString(templete->getItemName());
        }
        
        
        if (pFrame)
        {
            CCSpriteFrame *pSprFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("slot_type_6.png");
            if (pSprFrame)
            {
                pFrame->setBackgroundSpriteFrameForState(pSprFrame, CCControlStateNormal);
                pFrame->setBackgroundSpriteFrameForState(pSprFrame, CCControlStateHighlighted);
                pFrame->setBackgroundSpriteFrameForState(pSprFrame, CCControlStateSelected);
                pFrame->setBackgroundSpriteFrameForState(pSprFrame, CCControlStateDisabled);
            }
        }
        
        
        return true;
    }
    else
    {
        return false;
    }
}


bool NSGameHelper::setMonsterIconDetailByUid(uint64_t uid, CCSprite* pIcon, CCLabelTTF* pName, CCSprite* pFrame, bool bCircle)
{
	MB_PetData* pData = MB_PetMgr::getInstance()->getPetDataByUID(uid);
	bool ret = false;
	if (pData)
	{
		ret = NSGameHelper::setMonsterIconDetailByTid(pData->getPetTypeID(), pData->getPetQuallity(), pIcon, pName, pFrame, bCircle);

		int nQuallity = (pData->getPetQuallity()) % 10;
		if (nQuallity > 0 && pName != NULL) {
			char buff[64] = {};
			sprintf(buff, "%s+%d", pName->getString(), nQuallity);
			pName->setString(buff);
		}

	}


	return ret;
}
bool NSGameHelper::setMonsterIconDetailByUid2(uint64_t uid,CCSprite* pIcon,CCLabelTTF* pName,CCControlButton* pFrame,bool bCircle)
{
    MB_PetData* pData = MB_PetMgr::getInstance()->getPetDataByUID(uid);
    bool ret = false;
    if (pData)
    {
        ret = NSGameHelper::setMonsterIconDetailByTid2(pData->getPetTypeID(), pData->getPetQuallity(), pIcon, pName, pFrame, bCircle);
        
        int nQuallity = (pData->getPetQuallity()) % 10;
        if (nQuallity > 0 && pName != NULL) {
            char buff[64] = {};
            sprintf(buff, "%s+%d", pName->getString(), nQuallity);
            pName->setString(buff);
        }
    }
    return ret;
}
bool NSGameHelper::setMonsterIconDetailByTid2(uint16_t tid, uint16_t rank, CCSprite* pIcon, CCLabelTTF* pName, CCControlButton* pFrame, bool bCircle)
{
    MB_PetTemplate *templete = MB_PetMgr::getInstance()->getPetTemplateByID(tid);
    if (templete)
    {
        if (pIcon)
        {
            NSGameHelper::setSpriteFrame(pIcon, templete->getPetFace(getShapeTypeByRank(rank)));
            if (bCircle)creatMaskSprite(pIcon);
        }
        
        if (pName)
        {
            pName->setString(templete->getPetName(NSGameHelper::getShapeTypeByRank(rank)));
        }
        
        if (pFrame)
        {
            CCSpriteFrame *pSprFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("slot_type_%d.png",templete->getPetKingdom())->getCString());
            if (pSprFrame)
            {
                pFrame->setBackgroundSpriteFrameForState(pSprFrame, CCControlStateNormal);
                pFrame->setBackgroundSpriteFrameForState(pSprFrame, CCControlStateHighlighted);
                pFrame->setBackgroundSpriteFrameForState(pSprFrame, CCControlStateSelected);
                pFrame->setBackgroundSpriteFrameForState(pSprFrame, CCControlStateDisabled);
            }
        }
        
        return true;
    }
    else
    {
        return false;
    }
}


bool NSGameHelper::setMonsterIconDetailByTid(uint16_t tid, uint16_t rank, CCSprite* pIcon, CCLabelTTF* pName, CCSprite* pFrame, bool bCircle)
{
    MB_PetTemplate *templete = MB_PetMgr::getInstance()->getPetTemplateByID(tid);
    if (templete)
    {
        if (pIcon)
        {
            NSGameHelper::setSpriteFrame(pIcon, templete->getPetFace(getShapeTypeByRank(rank)));
            if (bCircle)creatMaskSprite(pIcon);
		}

		if (pName)
		{
			pName->setString(templete->getPetName(NSGameHelper::getShapeTypeByRank(rank)));
		}
        
        if (pFrame)
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("global.plist"); pFrame->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("slot_type_%d.png",templete->getPetKingdom())->getCString()));
        }
        
        return true;
    }
    else
    {
        return false;
    }
}
bool NSGameHelper::setMonsterIconDetailWithStarByTid(uint16_t tid, uint16_t rank, CCSprite* pIcon, CCLabelTTF* pName, CCSprite* pFrame, CCNode* pStart, bool bCircle)
{
    MB_PetTemplate *templete = MB_PetMgr::getInstance()->getPetTemplateByID(tid);
    if (templete)
    {
        if (pIcon)
        {
            NSGameHelper::setSpriteFrame(pIcon, templete->getPetFace(getShapeTypeByRank(rank)));
            if (bCircle)creatMaskSprite(pIcon);
        }
        
        if (pName)
        {
            pName->setString(templete->getPetName(NSGameHelper::getShapeTypeByRank(rank)));
        }
        
        if (pFrame)
        {
            pFrame->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("slot_type_%d.png",templete->getPetKingdom())->getCString()));
        }
        
        if (pStart)
        {
            CCObject* child;
            CCArray* children = pStart->getChildren();
            for (int i = 0; i<templete->getPetStar(); i++) {
                CCNode* pNode =dynamic_cast<CCNode*>(children->objectAtIndex(i));
                pNode->setVisible(true);
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}
//卡牌
bool NSGameHelper::setItemCardDetailByUid(uint64_t uid, CCSprite* pIcon, CCLabelTTF* pName, CCSprite* pStarFrame, CCSprite* pQualityFrame)
{
	MB_ItemData* pData = MB_ItemMgr::getInstance()->getItemDataByUID(uid);
	if (!pData)
	{
		setItemCardDetailByTid(pData->getItemID(), pData->getItemRank(), pIcon, pName, pStarFrame, pQualityFrame);
	}
	else
	{
		return false;
	}
	return true;

}
bool NSGameHelper::setItemCardDetailByTid(uint16_t tid, uint16_t rank, CCSprite* pIcon, CCLabelTTF* pName, CCSprite* pStarFrame, CCSprite* pQualityFrame)
{
	MB_ItemTemplate* pTemplete = MB_ItemMgr::getInstance()->getItemTemplateByID(tid);
	if (!pTemplete)
	{
		return  false;
	}

	if (pIcon)
	{
		setSpriteFrame(pIcon, pTemplete->getItemIcon());

	}
	if (pStarFrame)
	{
        pStarFrame->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("slot_type_6.png"));
	}
	if (pQualityFrame)
	{
		setRankFrame(pQualityFrame, pTemplete->getItemStar(), rank);
	}
	if (pName)
	{
		pName->setString(pTemplete->getItemName());
	}
	return true;
}

bool NSGameHelper::setMonsterCardDetailByUid(uint64_t uid, CCSprite* pIcon, CCLabelTTF* pName, CCSprite* pStarFrame, CCSprite* pQualityFrame)
{
	MB_PetData* pData = MB_PetMgr::getInstance()->getPetDataByUID(uid);
	if (pData)
	{
		NSGameHelper::setMonsterCardDetailByTid(pData->getPetTypeID(), pData->getPetQuallity(), pIcon, pName, pStarFrame, pQualityFrame);
	}
	else
	{
		return false;
	}
	return true;
}
bool NSGameHelper::setMonsterCardDetailByTid(uint16_t tid, uint16_t rank, CCSprite* pIcon, CCLabelTTF* pName, CCSprite* pStarFrame, CCSprite* pQualityFrame)
{
	MB_PetTemplate* pTemplete = MB_PetMgr::getInstance()->getPetTemplateByID(tid);
	if (!pTemplete)
	{
		return  false;
	}

	if (pIcon)
	{
		setSpriteFrame(pIcon, pTemplete->getPetCard(getShapeTypeByRank(rank)));

	}
	if (pStarFrame)
	{
		setQualityFrameByStar(pStarFrame, pTemplete->getPetStar());
	}

	if (pQualityFrame)
	{
		setRankFrame(pQualityFrame, pTemplete->getPetStar(), rank);
	}

	if (pName)
	{
		if (rank % 10 > 0) {
			char str[32] = "";
			sprintf(str, "%s+%d", pTemplete->getPetName(getShapeTypeByRank(rank)), rank % 10);
			pName->setString(str);
		}
		else
		{
			pName->setString(pTemplete->getPetName(getShapeTypeByRank(rank)));
		}
	}
	return true;
}

void NSGameHelper::setRankFrame(CCSprite* pSprite, int start, int rank)
{
	const MB_CardProperty* pty = MB_CardPropertyMgr::getInstance()->getCardPropertyByStar(start);
	if (pty)
	{
		const char* pFile = pty->getRankFrameByRank(rank);
		pSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pFile));

	}
}
int NSGameHelper::getShapeTypeByRank(int rank)
{
	return (rank / 10) + 1;
}

const ccColor3B& NSGameHelper::getCorlorByShape(uint16_t nShape)
{
	const static ccColor3B color[4] = { ccc3(195, 200, 206), ccc3(0, 249, 0), ccc3(0, 249, 0), ccc3(0, 249, 0) };
	if (nShape > 3)
	{
		return color[0];
	}

	return color[nShape];
}

bool NSGameHelper::resolvInt16ValueFromString(const char* pStr, uint16_t* pArray, uint16_t& realCount, uint16_t count)
{
	int* pIntArray = new int[count];

	bool ret = resolvIntValueFromString(pStr, pIntArray, realCount, count);
	if (ret)
	{
		for (uint16_t i = 0; i < realCount; ++i)
		{
			pArray[i] = pIntArray[i]; // bad_cast
		}
	}

	delete  pIntArray;

	return ret;
}
bool NSGameHelper::resolvIntValueFromString(const char* pStr, int* pArray, uint16_t& realCount, uint16_t count)
{
	if (pStr == NULL)
	{
		return false;
	}

	int len = strlen(pStr);
	char *pTemp = new char[len + 1];
	strcpy(pTemp, pStr);

	int start = 0;
	int index = 0;

	for (int i = 0; i < len; ++i)
	{
		if (pStr[i] == ',')
		{
			pTemp[i] = 0;
			pArray[index] = atoi(pTemp + start);
			++index;
			if (index == count)
			{
				realCount = count;
				return true;
			}
			start = i + 1;
		}
	}

	if (pStr[len - 1] != ',')
	{
		pArray[index] = atoi(pTemp + start);
	}

	realCount = index + 1;
	delete[] pTemp;
	return true;
}

bool NSGameHelper::getSuitItemsWithTeamDataStruct(TeamDataStruct* ts, int nSuitID, int16_t nCount, uint16_t& nRealCount, uint16_t* result)
{
	if (ts == NULL || result == NULL || nCount == 0)
	{
		return false;
	}

	int index = 0;
	if (ts->m_pEquip1 && ts->m_pEquip1->isSuitPart(nSuitID))
	{
		result[index++] = ts->m_pEquip1->getItemID();
		nRealCount = index;
		CHECK_RETURN_BOOLEN(index >= nCount, true);
	}
	if (ts->m_pEquip2 && ts->m_pEquip2->isSuitPart(nSuitID))
	{
		result[index++] = ts->m_pEquip2->getItemID();
		nRealCount = index;
		CHECK_RETURN_BOOLEN(index >= nCount, true);
	}
	if (ts->m_pEquip3&&ts->m_pEquip3->isSuitPart(nSuitID))
	{
		result[index++] = ts->m_pEquip3->getItemID();
		nRealCount = index;
		CHECK_RETURN_BOOLEN(index >= nCount, true);
	}
	if (ts->m_pTreasure1 && ts->m_pTreasure1->isSuitPart(nSuitID))
	{
		result[index++] = ts->m_pTreasure1->getItemID();
		nRealCount = index;
		CHECK_RETURN_BOOLEN(index >= nCount, true);
	}
	if (ts->m_pTreasure2 && ts->m_pTreasure2->isSuitPart(nSuitID))
	{
		result[index++] = ts->m_pTreasure2->getItemID();
		nRealCount = index;
		CHECK_RETURN_BOOLEN(index >= nCount, true);
	}
	if (ts->m_pTreasure3 && ts->m_pTreasure3->isSuitPart(nSuitID))
	{
		result[index++] = ts->m_pTreasure3->getItemID();
		nRealCount = index;
		CHECK_RETURN_BOOLEN(index >= nCount, true);
	}

	return nRealCount != 0;
}

bool NSGameHelper::getActivatedSuitPartsByPetPos(uint16_t* result, uint16_t count, uint16_t& realCount, uint16_t petPos, int nSuitID)
{
	if (result == NULL || count == 0)
	{
		return false;
	}

	TeamDataStruct* ts = MB_TeamData::getInstance()->getTeamMemberByIndex(petPos);
	if (ts == NULL)
	{
		return false;
	}

	return NSGameHelper::getSuitItemsWithTeamDataStruct(ts, nSuitID, count, realCount, result);
}

bool NSGameHelper::getItemMaterialComplateStatus(uint16_t nComposeID)
{
	MB_ComposeTemplate* pTemplate = MB_ComposeMgr::getInstance()->getComposeTemplateByID(nComposeID);

	if (pTemplate == NULL)
	{
		return false;
	}

	const uint16_t* pMaterial = pTemplate->getMaterialsArray();
	uint16_t material_count = pTemplate->getMaterialCount();


	std::map<uint16_t, int> mapMaterial;
	for (int i = 0; i < material_count; ++i)
	{
		std::map<uint16_t, int>::iterator it = mapMaterial.find(pMaterial[i]);
		if (it == mapMaterial.end())mapMaterial[pMaterial[i]] = 0;
		mapMaterial[pMaterial[i]]++;
	}

	CCObject* pTemp = NULL;
	CCArray* pArray = MB_ItemMgr::getInstance()->getItemDataArray();
	CCARRAY_FOREACH(pArray, pTemp)
	{
		MB_ItemData* pItem = dynamic_cast<MB_ItemData*>(pTemp);

		if (pItem && !pItem->getUsed())
		{
			if (mapMaterial[pItem->getItemID()] > 0)
			{
				--mapMaterial[pItem->getItemID()];
			}
		}
	}

	for (int i = 0; i < material_count; ++i)
	{
		if (mapMaterial[pMaterial[i]] > 0)
		{
			return false;
		}
	}
	return true;

	//    for (uint16_t i=0; i<material_count; ++i)
	//    {
	//        if (!ItemMgr::getInstance()->getItemInPackage(pMaterial[i]))
	//        {
	//            return false;
	//        }
	//    }
	//
	//    return true;
}

bool NSGameHelper::getPetMaterialComplateStatus(uint16_t nComposeID)
{
	MB_ComposeTemplate* pTemplate = MB_ComposeMgr::getInstance()->getComposeTemplateByID(nComposeID);

	if (pTemplate == NULL)
	{
		return false;
	}


	const uint16_t* pMaterial = pTemplate->getMaterialsArray();
	uint16_t material_count = pTemplate->getMaterialCount();

	std::map<uint16_t, int> mapMaterial;
	for (int i = 0; i < material_count; ++i)
	{
		std::map<uint16_t, int>::iterator it = mapMaterial.find(pMaterial[i]);
		if (it == mapMaterial.end())mapMaterial[pMaterial[i]] = 0;
		mapMaterial[pMaterial[i]]++;
	}

	CCObject* pTemp = NULL;
	CCARRAY_FOREACH(MB_PetMgr::getInstance()->getPetDataArray(), pTemp)
	{
		MB_PetData* pPet = dynamic_cast<MB_PetData*>(pTemp);
		if (pPet && !MB_TeamData::getInstance()->checkInTeam(pPet))
		{
			if (mapMaterial[pPet->getPetTypeID()] > 0)
			{
				--mapMaterial[pPet->getPetTypeID()];
			}
		}
	}

	for (int i = 0; i < material_count; ++i)
	{
		if (mapMaterial[pMaterial[i]] > 0)
		{
			return false;
		}
	}
	return true;
	//    for (uint16_t i=0; i<material_count; ++i)
	//    {
	//        if (!MB_PetMgr::getInstance()->getPetInPackage(pMaterial[i]))
	//        {
	//            return false;
	//        }
	//    }
	//    return true;
}

bool NSGameHelper::getEquipItemsFromItemMgrByTid(std::vector<uint64_t>& vUid, uint16_t tid, int filter)
{
	CCArray* pArray = MB_ItemMgr::getInstance()->getEquipArray();
	if (pArray->count() == 0)
	{
		return false;
	}


	MB_ItemData* pData = NULL;

	CCARRAY_FOREACH_4TYPE(pArray, MB_ItemData*, pData)
	{
		if (pData->getItemID() == tid)
		{
			if (filter == filter_used && pData->getUsed())
			{
				vUid.push_back(pData->getItemUID());
			}
			else if (filter == filter_unused && !pData->getUsed())
			{
				vUid.push_back(pData->getItemUID());
			}
			else if (filter_ignore == filter)
			{
				vUid.push_back(pData->getItemUID());
			}
		}
	}

	return !vUid.empty();
}

bool NSGameHelper::getEquipItemsFromItemMgrByStar(std::vector<uint64_t>& vUid, uint16_t star, int filter)
{

	CCArray* pArray = MB_ItemMgr::getInstance()->getEquipArray();


	MB_ItemData* pData = NULL;
	MB_ItemTemplate* pTemplate = NULL;

	CCARRAY_FOREACH_4TYPE(pArray, MB_ItemData*, pData)
	{
		pTemplate = MB_ItemMgr::getInstance()->getItemTemplateByID(pData->getItemID());
		if (pTemplate)
		{
			if (pTemplate->getItemStar() == star)
			{
				if (filter == filter_used && pData->getUsed())
				{
					vUid.push_back(pData->getItemUID());
				}
				else if (filter == filter_unused && !pData->getUsed())
				{
					vUid.push_back(pData->getItemUID());
				}
				else if (filter_ignore == filter)
				{
					vUid.push_back(pData->getItemUID());
				}
			}
		}
	}

	return !vUid.empty();
}

bool NSGameHelper::getMonstersFromPetMgrByTid(std::vector<uint64_t>& vUid, uint16_t tid, int filter)
{

	CCArray* pArray = MB_PetMgr::getInstance()->getPetDataArray();

	MB_PetData* pData = NULL;

	CCARRAY_FOREACH_4TYPE(pArray, MB_PetData*, pData)
	{
		// 守護神兽過滤
		if (pData->getIsHomelandPet())
		{
			continue;
		}
		//守護精靈過滤
		if (checkIsGuardPet(pData->getPetID()))
		{
			continue;
		}
		//add 經驗卡牌不能合成
		if (pData->getPetTypeID() == tid && !checkIsExperienceCard(pData->getPetTypeID()))
		{
			if (filter == filter_used && MB_TeamData::getInstance()->checkInTeam(pData))
			{
				vUid.push_back(pData->getPetID());
			}
			else if (filter == filter_unused && !MB_TeamData::getInstance()->checkInTeam(pData))
			{
				vUid.push_back(pData->getPetID());
			}
			else if (filter_ignore == filter)
			{
				vUid.push_back(pData->getPetID());
			}
		}
	}

	return !vUid.empty();
}

bool NSGameHelper::getMonstersFromPetMgrByStar(std::vector<uint64_t>& vUid, uint16_t star, int filter)
{
	CCArray* pArray = MB_PetMgr::getInstance()->getPetDataArray();

	MB_PetData* pData = NULL;
	MB_PetTemplate* pTemplate = NULL;

	CCARRAY_FOREACH_4TYPE(pArray, MB_PetData*, pData)
	{
		pTemplate = pData->getTemplete();

		if (pTemplate)
		{
			// 守護神兽過滤
			if (pData->getIsHomelandPet())
			{
				continue;
			}
			//守護精靈過滤
			if (checkIsGuardPet(pData->getPetID()))
			{
				continue;
			}
			//add 經驗卡牌不能合成
			if (checkIsExperienceCard(pTemplate->getPetTypeID()))
			{
				continue;
			}

			if (pTemplate->getPetStar() == star)
			{
				if (filter == filter_used && MB_TeamData::getInstance()->checkInTeam(pData))
				{
					vUid.push_back(pData->getPetID());
				}
				else if (filter == filter_unused && !MB_TeamData::getInstance()->checkInTeam(pData))
				{
					vUid.push_back(pData->getPetID());
				}
				else if (filter_ignore == filter)
				{
					vUid.push_back(pData->getPetID());
				}
			}
		}
	}

	return !vUid.empty();
}

bool NSGameHelper::getAllEquipItemsFromItemMgr(std::vector<uint64_t>& vUid, uint16_t maxStar, int filter)
{
	CCArray* pArray = MB_ItemMgr::getInstance()->getEquipArray();

	MB_ItemData* pData = NULL;

	CCARRAY_FOREACH_4TYPE(pArray, MB_ItemData*, pData)
	{
		if (pData->getTemplateStar() > maxStar)
		{
			continue;
		}
		if (filter == filter_used && pData->getUsed())
		{
			vUid.push_back(pData->getItemUID());
		}
		else if (filter == filter_unused && !pData->getUsed())
		{
			vUid.push_back(pData->getItemUID());
		}
		else if (filter_ignore == filter)
		{
			vUid.push_back(pData->getItemUID());
		}
	}

	return !vUid.empty();
}

bool NSGameHelper::getAllMonstersUidFromPetMgr(std::vector<uint64_t>& vUid, uint16_t maxStar, int filter)
{
	CCArray* pArray = MB_PetMgr::getInstance()->getPetDataArray();

	MB_PetData* pData = NULL;

	CCARRAY_FOREACH_4TYPE(pArray, MB_PetData*, pData)
	{
		if (pData->getTemplateStar() > maxStar)
		{
			continue;
		}
		// 守護神兽過滤
		if (pData->getIsHomelandPet())
		{
			continue;
		}
		//守護精靈過滤
		if (checkIsGuardPet(pData->getPetID()))
		{
			continue;
		}

		//add 經驗卡牌不能合成
		if (checkIsExperienceCard(pData->getPetTypeID()))
		{
			continue;
		}
		if (filter == filter_used && MB_TeamData::getInstance()->checkInTeam(pData))
		{
			vUid.push_back(pData->getPetID());
		}
		else if (filter == filter_unused && !MB_TeamData::getInstance()->checkInTeam(pData))
		{
			vUid.push_back(pData->getPetID());
		}
		else if (filter_ignore == filter)
		{
			vUid.push_back(pData->getPetID());
		}
	}

	return !vUid.empty();
}
bool NSGameHelper::getAllValideMonstersUidFromPetMgr(std::vector<uint64_t>& vUid)
{
	CCArray* pArray = MB_PetMgr::getInstance()->getPetDataArray();

	MB_PetData* pData = NULL;

	CCARRAY_FOREACH_4TYPE(pArray, MB_PetData*, pData)
	{
		if (checkIsExperienceCard(pData->getPetTypeID()))
		{
			continue;
		}



		if (pData->getIsHomelandPet())
		{
			continue;
		}
		vUid.push_back(pData->getPetID());
	}

	return !vUid.empty();
}



//根据品階獲取头像特效
void NSGameHelper::getHeadEffectsByRank(CCSprite* node, int rank)
{
	if (NULL == node) {
		return;
	}
	node->removeAllChildrenWithCleanup(true);
	if (1 == rank / 10)
	{
		CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
		CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
		CCNode *pNode = pCCBReader->readNodeGraphFromFile("res/eff_node_1stbreakthrough.ccbi");
		node->addChild(pNode);
		pNode->setPosition(node->getContentSize().width / 2.0f, node->getContentSize().height / 2.0f);
		CC_SAFE_RELEASE_NULL(pCCBReader);
		return;
	}
	else if (2 <= rank / 10)
	{
		CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
		CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
		CCNode *pNode = pCCBReader->readNodeGraphFromFile("res/eff_node_2ndbreakthrough.ccbi");
		node->addChild(pNode);
		pNode->setPosition(node->getContentSize().width / 2.0f, node->getContentSize().height / 2.0f);
		CC_SAFE_RELEASE_NULL(pCCBReader);
		return;

	}
	else if (0 == rank / 10)
	{
		return;
	}
}

//检查是否經驗卡牌  是返回true，不是返回false
bool NSGameHelper::checkIsExperienceCard(uint16_t tID)
{
	if (tID > 1 && tID < 7) {
		return true;
	}
	return false;
}

bool NSGameHelper::checkIsExperienceCard(uint64_t uID)
{
	MB_PetData* data = MB_PetMgr::getInstance()->getPetDataByUID(uID);
	return NSGameHelper::checkIsExperienceCard(data->getPetTypeID());
}

//检查是否守護精靈
bool NSGameHelper::checkIsGuardPet(uint64_t uid)
{
	return MB_GuardInterface::getInstance()->checkIsGuardPet(uid);
}
bool NSGameHelper::checkIsGuardPetType(uint16_t tid)
{
	return MB_GuardInterface::getInstance()->checkIsGuardPetType(tid);
}



bool NSGameHelper::FormatNumber(char* strNumber, uint64_t value, bool showTitle, const char* title)
{
	if (value >= 100000000)
	{
		int n = value / 100000000;
		int n2 = (value % 100000000) / 10000;
		if (showTitle)
		{
			if (n2 > 0)
			{
				sprintf(strNumber, "%s%d亿%d万", title, n, n2);
			}
			else
			{
				sprintf(strNumber, "%s%d亿", title, n);
			}

		}
		else
		{
			if (n2 > 0)
			{
				sprintf(strNumber, "%d亿%d万", n, n2);
			}
			else
			{
				sprintf(strNumber, "%d亿", n);
			}
		}
	}
	else if (value >= 100000)
	{
		value /= 10000;
		if (showTitle)
		{
			sprintf(strNumber, "%s%llu万", title, value);
		}
		else
		{
			sprintf(strNumber, "%llu万", value);
		}
	}
	else
	{
		if (showTitle)
		{
			sprintf(strNumber, "%s%llu", title, value);
		}
		else
		{
			sprintf(strNumber, "%llu", value);
		}
	}
	return true;
}

int NSGameHelper::FormatNumber2(char* strNumber, uint64_t value, bool showTitle, const char* title)
{
    if (value >= 100000000)
    {
        int n = value / 100000000;
        int n2 = (value % 100000000) / 10000;
        if (showTitle)
        {
            if (n2 > 0)
            {
                sprintf(strNumber, "%s%d亿%d万", title, n, n2);
                return get_length(n)+get_length(n2)+2;
            }
            else
            {
                sprintf(strNumber, "%s%d亿", title, n);
                return get_length(n)+1;
            }
        }
        else
        {
            if (n2 > 0)
            {
                sprintf(strNumber, "%d亿%d万", n, n2);
                return get_length(n)+get_length(n2)+2;
            }
            else
            {
                sprintf(strNumber, "%d亿", n);
                return get_length(n)+1;
            }
        }
    }
    else if (value >= 100000)
    {
        value /= 10000;
        if (showTitle)
        {
            sprintf(strNumber, "%s%llu万", title, value);
            return get_length(value)+1;
        }
        else
        {
            sprintf(strNumber, "%llu万", value);
            return get_length(value)+1;
        }
    }
    else
    {
        if (showTitle)
        {
            sprintf(strNumber, "%s%llu", title, value);
            return get_length(value);
        }
        else
        {
            sprintf(strNumber, "%llu", value);
            return get_length(value);
        }
    }
    return 0;
}

bool NSGameHelper::LabelFormatNumber(CCLabelProtocol* label, uint64_t value, bool showTitle, const char* title)
{
	if (label)
	{
		char buff[40] = { 0 };
		FormatNumber(buff, value, showTitle, title);
		label->setString(buff);
	}

	return false;
}



//返回城市名字保持在
//void NSGameHelper::RequestCityName()
//{
//#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
////    CCLOG("RequestCityName ANDROID");
//    JniMethodInfo jmi;
//    if(JniHelper::getStaticMethodInfo(jmi , "com/crimoon/common/ProjectTK" , "RequestCityName" , "()V"))
//    {
//        jmi.env->CallStaticVoidMethod(jmi.classID , jmi.methodID );
////        CCLOG("RequestCityName CallStaticVoidMethod");
//    }
//    
//#endif
//    
//#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
////    CCLOG("RequestCityName ISO");
//    OCandCppHelper::RequestCityName();
//#endif
//}


bool NSGameHelper::getRoleNameWithLocation(std::string& result)
{
	result = MB_RoleData::getInstance()->getName();
	//    std::string cityName = NSDataExchange::g_LocationName;
	//    CCLOG("g_LocationName:%s",cityName.c_str());
	//    char buff[100] = {0};
	//    sprintf(buff, "%s[%s]",MB_RoleData::getInstance()->getName(),(cityName.empty()?"中国":cityName.c_str()));
	//    CCLOG("getRoleNameWithLocation:%s",buff);
	//    result = buff;
	return true;
}

bool NSGameHelper::AutoScale9Sprite(CCScale9Sprite* sp)
{
	return adjustScrollNode(sp);
}

bool NSGameHelper::PreProcessNode(CCNode* pNode, const char* pName)
{
	if (strncmp(pName, "scale9sprite", 12) == 0)
	{
		return AutoScale9Sprite(dynamic_cast<CCScale9Sprite*>(pNode));
	}
	return false;
}

bool PreReadScale9Sprite(CCNode* pNode, const char* pName)
{
	return NSGameHelper::PreProcessNode(pNode, pName);
}

bool NSGameHelper::adjustScrollNode(CCNode* pNode)
{
	if (pNode == NULL)
	{
		return false;
	}
	float height = CCDirector::sharedDirector()->getWinSize().height;
	height = height - 960;
	CCSize sz = pNode->getContentSize();
	sz.height += height;
	pNode->setContentSize(sz);

	return true;
}




void NSGameHelper::GotoCreateRole()
{
	//    CCLog("GotoCreateRole1");
	AppDelegate::goLogin();

	//    CCLog("GotoCreateRole2");
	//    return;
	//    CCLog("GotoCreateRole");
	//    CCScene* pScene = MB_SceneRoleCreate::scene();
	//    CCDirector::sharedDirector()->replaceScene(pScene);
}


bool NSGameHelper::petHasEquipThisItem(uint64_t petId, uint16_t nTypeId)
{
	uint16_t pos = MB_TeamData::getInstance()->getPetPosByPetID(petId);
	TeamDataStruct* ts = MB_TeamData::getInstance()->getTeamMemberByIndex(pos);
	if (ts)
	{
		if (ts->m_pEquip1 && ts->m_pEquip1->getItemID() == nTypeId)
		{
			return true;
		}
		if (ts->m_pEquip2 && ts->m_pEquip2->getItemID() == nTypeId)
		{
			return true;
		}
		if (ts->m_pEquip3 && ts->m_pEquip3->getItemID() == nTypeId)
		{
			return true;
		}
		if (ts->m_pTreasure1 && ts->m_pTreasure1->getItemID() == nTypeId)
		{
			return true;
		}
		if (ts->m_pTreasure2 && ts->m_pTreasure2->getItemID() == nTypeId)
		{
			return true;
		}
		if (ts->m_pTreasure3 && ts->m_pTreasure3->getItemID() == nTypeId)
		{
			return true;
		}
	}
	return false;
}

void NSGameHelper::centerStars(CCSprite* pStars[], uint8_t nCount, uint8_t nShowCount)
{
	if (nShowCount >= nCount || nCount <= 1)return;

	float uint_width = pStars[1]->getPositionX() - pStars[0]->getPositionX();//pStars[0]->getContentSize().width*pStars[0]->getScaleX();
	float width = uint_width * nCount; // 总長
	float newwith = nShowCount * uint_width;
	float offset = (width - newwith) / 2.0f;// + uint_width/2.0f;
	uint8_t i = 0;
	for (; i < nShowCount; ++i)
	{
		pStars[i]->setPositionX(pStars[i]->getPositionX() + offset);
	}
	for (int i = 0; i < nCount; i++)
	{
		if (i < nShowCount)
		{
			pStars[i]->setVisible(true);
		}
		else
		{
			pStars[i]->setVisible(false);
		}
	}
}

void NSGameHelper::getItemUseByType(uint8_t type, std::vector<uint64_t>& vContainer)
{
	CCArray* pArray = MB_ItemMgr::getInstance()->getUseItemRuleArray();

	MB_UseItemRule* pRule = NULL;

	std::vector<uint16_t> tid;

	CCARRAY_FOREACH_4TYPE(pArray, MB_UseItemRule*, pRule)
	{
		if (pRule->getType() == type)
		{
			tid.push_back(pRule->getItemTID());
		}
	}

	std::vector<uint16_t>::iterator it = tid.begin();
	for (; it != tid.end(); ++it)
	{
		getOtherItemByTypeID(*it, vContainer);
	}
}

void NSGameHelper::getOtherItemByTypeID(uint16_t tid, std::vector<uint64_t>& vContainer)
{
	CCArray* pArray = MB_ItemMgr::getInstance()->getOtherArray();

	MB_ItemData* pData = NULL;

	CCARRAY_FOREACH_4TYPE(pArray, MB_ItemData*, pData)
	{
		if (pData->getItemID() == tid)
		{
			vContainer.push_back(pData->getItemUID());
		}
	}
}
const char*  NSGameHelper::getDataTimeByUnixStamp(uint32_t t)
{
	static char buff[128] = {};
	buff[0] = 0;
	time_t tt = t;
	tm* ptm = localtime(&tt);
	if (ptm)
	{
		sprintf(buff, "%d/%d/%d %2d:%2d:%2d", ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
	}

	return buff;
}

void NSGameHelper::convertToRbfString(std::string& str)
{
	for (int i = 0; i < str.length(); ++i)
	{
		if (str[i] == '{')
		{
			str[i] = '<';
		}
		else if (str[i] == '}')
		{
			str[i] = '>';
		}
	}
}

bool NSGameHelper::mailRewardConvert2ValueTemplateArray(sMailReward* pMail, CCArray* pArray)
{
	if (pMail == NULL || pArray == NULL)
	{
		return false;
	}
	if (pMail->PetRewards.empty() && pMail->ItemRewards.empty())
	{
		return false;
	}

	KeyValue_It it = pMail->ItemRewards.begin();
	RewardTempleteValue* pValue = NULL;

	for (; it != pMail->ItemRewards.end(); ++it)
	{
		pValue = new RewardTempleteValue;
		pValue->setType(kRewardValueTypeItem);
		pValue->setNumber(it->second);
		pValue->setValueID(it->first);
		pArray->addObject(pValue);
		pValue->release();
	}

	it = pMail->PetRewards.begin();

	for (; it != pMail->PetRewards.end(); ++it)
	{
		pValue = new RewardTempleteValue;
		pValue->setType(kRewardValueTypePet);
		pValue->setNumber(it->second);
		pValue->setValueID(it->first);
		pArray->addObject(pValue);
		pValue->release();
	}

	return pArray->count() != 0;

}

bool NSGameHelper::setRoleIcon(cocos2d::CCSprite *pIcon, bool bMail, uint32_t nHeadID, uint8_t nTitle,CCSprite *pIconFrame)
{
	CCTexture2D *textrue = NULL;
	if (nHeadID == 0)
	{
		MB_TitleTemplete *title = MB_TitleMgr::getInstance()->getTitleByID(nTitle);
		if (title == NULL)return false;
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("global.plist");
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(bMail ? title->getMCardFrame() : title->getFCardFrame());
		if (frame != NULL)
		{
			pIcon->setDisplayFrame(frame);
			NSGameHelper::creatMaskSprite(pIcon);
		}
		else
		{
			textrue = CCTextureCache::sharedTextureCache()->addImage(bMail ? title->getMCardFrame() : title->getFCardFrame());
			if (textrue)
			{
				pIcon->setDisplayFrame(CCSpriteFrame::createWithTexture(textrue, CCRectMake(0, 0, textrue->getContentSize().width, textrue->getContentSize().height)));
				NSGameHelper::creatMaskSprite(pIcon);
			}
		}
	}
	else
	{
		uint16_t tID = nHeadID%SHAPE_BASE;
		uint16_t shape = nHeadID / SHAPE_BASE;
		MB_PetTemplate* petTemplete = MB_PetMgr::getInstance()->getPetTemplateByID(tID);
		if (petTemplete)
		{
			textrue = CCTextureCache::sharedTextureCache()->addImage(petTemplete->getPetFace(shape));
			if (textrue)
			{
				pIcon->setDisplayFrame(CCSpriteFrame::createWithTexture(textrue, CCRectMake(0, 0, textrue->getContentSize().width, textrue->getContentSize().height)));
				NSGameHelper::creatMaskSprite(pIcon);
			}
            
            if (pIconFrame!=NULL) {
                CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("global.plist"); pIconFrame->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("slot_type_%d.png",petTemplete->getPetKingdom())->getCString()));
            }
		}
		else
		{
            MB_LOG("玩家自定义头像获取ID错误 %d",tID);
			return false;
		}
	}
	return true;
}

std::string NSGameHelper::convertDeltaTime2Data(int deltaTime)
{
	int day = deltaTime / (60 * 60 * 24);
	std::string ret = "";
	char temp[64] = {};
	if (day > 0)
	{
		sprintf(temp, "%d天前", day);
		ret = temp;
	}
	else
	{
		int hour = deltaTime / (60 * 60);
		if (hour > 0)
		{
            sprintf(temp, "%d小时前", hour);
			ret = temp;
		}
		else
		{
			int min = deltaTime / 60;
			if (min > 0)
			{
                sprintf(temp, "%d分钟前", min);
				ret = temp;
			}
			else
			{
                ret = "1分钟前";
			}
		}
	}
	return ret;
}

std::string NSGameHelper::convertDeltaTime2String(int deltaTime)
{

	std::string ret = "";
	char temp[64] = {};
	int hour = deltaTime / (60 * 60);
	if (hour > 0)
	{
        sprintf(temp, "%d小时", hour);
		ret += temp;
	}

	int min = (deltaTime / 60) % 60;
	if (min > 0)
	{
        sprintf(temp, "%d分钟", min);
		ret += temp;
	}

	int second = deltaTime % 60;
	if (second) {
		sprintf(temp, "%d秒", second);
		ret += temp;
	}

	return ret;
}

//粒子特效控制
//void NSGameHelper::stopAllParticle(CCParticleSystemQuad* particle)
//{
//    if (particle == NULL)
//    {
//        return;
//    }
//    particle->stopSystem();
//}
//void NSGameHelper::BeginAllParticle(CCParticleSystemQuad* particle)
//{
//    if (particle == NULL)
//    {
//        return;
//    }
//
//    particle->resetSystem();
//}

void NSGameHelper::reloadDataWithNoMove(CCTableView* pView)
{
	if (pView == NULL)
	{
		return;
	}

	CCPoint pt = pView->getContentOffset();

	pView->reloadData();
	CCSize container_size = pView->getContainer()->getContentSize();
	CCSize node_size = pView->getViewSize();
	if (container_size.height > node_size.height)
	{
		if (pt.y < -container_size.height + node_size.height - 1)
		{
			pt.y = container_size.height - node_size.height;
		}
		else if (pt.y > 0)
		{
			pt.y = 0;
			pView->setContentOffset(pt);
		}
		else
		{
			pView->setContentOffset(pt);
		}
	}
}

CCNode* NSGameHelper::createRichBox(const std::string& szContent, const CCSize& sz, bool bLockHeight)
{
	RichText* pBox = RichText::create(szContent.c_str(), 24, sz);
	return pBox;
}

CCNode* NSGameHelper::createLabelText(const std::string& szContent, const CCSize& sz)
{
	CCLabelTTF* pLabel = CCLabelTTF::create("", "", 26);
    pLabel->setColor(ccBLACK);
	pLabel->setContentSize(sz);
	pLabel->setDimensions(sz);
	pLabel->setString(szContent.c_str());
	return pLabel;
}

int zw[] = { 0x3002, 0xff0c, 0x3001, 0xff1f, 0xff01, 0xff1a, 0xff1b, 0xff08, 0xff09, 0x40, 0x201c, 0x201d };
bool checkChineseFH(int k)
{
	for (int i = 0; i < sizeof(zw) / sizeof(int); ++i)
	{
		if (zw[i] == k)return true;
	}
	return false;
}

bool NSGameHelper::safeContentChect(const std::string& constent)
{
	unsigned short* pUnicode16 = cc_utf8_to_utf16(constent.c_str());
	size_t nUnicodeLength = cc_wcslen(pUnicode16);

	for (int i = 0; i < nUnicodeLength; ++i)
	{
		if (pUnicode16[i] >= 0x4e00 && pUnicode16[i] <= 0x9fff)
		{
			continue;
		}
		else
		{
			if ((pUnicode16[i] <= 0x2bff && pUnicode16[i] >= 0x2000) || (pUnicode16[i] < 0x036f) || checkChineseFH(pUnicode16[i]))
			{
				continue;
			}
			else
			{
				return false;
			}
		}
	}
	return true;

}

std::vector<std::string> NSGameHelper::splitEx(const std::string& src, std::string separate_character)
{
	std::vector<std::string> strs;

	int separate_characterLen = separate_character.size();
	int lastPosition = 0, index = -1;
	while (-1 != (index = src.find(separate_character, lastPosition)))
	{
		strs.push_back(src.substr(lastPosition, index - lastPosition));
		lastPosition = index + separate_characterLen;
	}
	std::string lastString = src.substr(lastPosition);
	if (!lastString.empty())
		strs.push_back(lastString);
	return strs;
}


CCRenderTexture* NSGameHelper::creatMaskSprite(CCSprite * pFlower, CCSprite* pMask, bool bUse)
{
	if (!bUse) {
		return NULL;
	}
	static const int TAG_RT = 3210;
	pFlower->setVisible(true);

	CCSize size = pFlower->getContentSize();
	CCRenderTexture *pRt = CCRenderTexture::create(size.width, size.height);
	pFlower->setPosition(ccp(size.width / 2, size.height / 2));
	if (pMask == NULL)
	{
		CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("header_passage.png");
		if (pFrame == NULL)CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("global.plist");
		pMask = CCSprite::createWithSpriteFrameName("header_passage.png");
	}

	pMask->setPosition(ccp(size.width / 2, size.height / 2));
	ccBlendFunc maskBlend = { GL_ONE, GL_ZERO };
	ccBlendFunc flowerBlend = { GL_ONE_MINUS_DST_ALPHA, GL_ZERO };
	pMask->setBlendFunc(maskBlend);
	pFlower->setBlendFunc(flowerBlend);
	pRt->begin();
	pMask->visit();
	pFlower->visit();
	pRt->end();

	pFlower->setVisible(false);
	pMask->setVisible(false);

	CCNode* pChild = pFlower->getParent()->getChildByTag(TAG_RT);
	if (pChild)pChild->removeFromParent();
	pRt->setTag(TAG_RT);
	pFlower->getParent()->addChild(pRt, pFlower->getZOrder());
	return pRt;
}

CCProgressTimer* NSGameHelper::makeProgressBar(CCSprite* pTexture)
{
	if (pTexture == NULL || pTexture->getParent() == NULL)
	{
		return NULL;
	}
	CCNode *barpa = pTexture->getParent();
	CCPoint pos = pTexture->getPosition();
	float scalex = pTexture->getScaleX();
	float scaley = pTexture->getScaleY();
	pTexture->removeFromParentAndCleanup(true);
	pTexture->setPosition(ccp(0, 0));
	CCProgressTimer* m_pBloodTimer = CCProgressTimer::create(pTexture);
	m_pBloodTimer->setType(kCCProgressTimerTypeBar);
	m_pBloodTimer->setScaleX(scalex);
	m_pBloodTimer->setScaleY(scaley);

	m_pBloodTimer->setMidpoint(ccp(0, 1));
	m_pBloodTimer->setBarChangeRate(ccp(1, 0));
	m_pBloodTimer->setPosition(pos);
	barpa->addChild(m_pBloodTimer);
	return m_pBloodTimer;
}

int NSGameHelper::getServerByRoleID(uint32_t uid)
{
	return int(uid / 1000000) - 1;
}



void NSGameHelper::runMoveAndOptAction(CCNode* node,float delayTime,float moveTime,bool isDoMove,bool isContainsChild)
{
    if (node->getTag()==-999)return;
    CCSprite* spr = dynamic_cast<CCSprite*>(node);
    CCPoint toP = node->getPosition();
    if (isContainsChild) {
        if (spr) {
            runMoveAndOptAction(spr,delayTime,moveTime,true,false);
        }
        CCObject* pObj = NULL;
        CCArray* pChildren = node->getChildren();
        CCARRAY_FOREACH(pChildren, pObj)
        {
            CCNode* pChild = (CCNode*)pObj;
            if (spr) {
                runMoveAndOptAction(pChild,delayTime,moveTime,false,true);
            }else
            {
                runMoveAndOptAction(pChild,delayTime,moveTime,true,true);
            }
        }
    }else{
        spr->setOpacity(0);
        if (isDoMove) {
            spr->setPositionY(toP.y-1200);
            spr->runAction(CCSequence::create(CCDelayTime::create(delayTime),CCSpawn::create(CCMoveTo::create(moveTime, toP),CCSequence::create(CCDelayTime::create(moveTime*2/3),CCFadeIn::create(moveTime/2), NULL)  ,NULL)  ,NULL ));
        }else
        {
            spr->runAction(CCSequence::create(CCDelayTime::create(delayTime+moveTime*2/3),CCFadeIn::create(moveTime/2),NULL ));
        }
    }
}
void NSGameHelper::runOptActionIn(CCNode* node,float fadeTime,bool isContainsChild)
{
    CCSprite* spr = dynamic_cast<CCSprite*>(node);
    if(isContainsChild)
    {
        if (spr) {
            runOptActionIn(spr,fadeTime,false);
        }
        CCObject* pObj = NULL;
        CCArray* pChildren = node->getChildren();
        CCARRAY_FOREACH(pChildren, pObj)
        {
            CCNode* pChild = (CCNode*)pObj;
            runOptActionIn(pChild,fadeTime,true);
        }
    }else
    {
        spr->setOpacity(0);
        spr->runAction(CCFadeIn::create(fadeTime));
    }
}
void NSGameHelper::runOptActionOut(CCNode* node,float fadeTime,bool isContainsChild)
{
    CCSprite* spr = dynamic_cast<CCSprite*>(node);
    if(isContainsChild)
    {
        if (spr) {
            runOptActionOut(spr,fadeTime,false);
        }
        CCObject* pObj = NULL;
        CCArray* pChildren = node->getChildren();
        CCARRAY_FOREACH(pChildren, pObj)
        {
            CCNode* pChild = (CCNode*)pObj;
            runOptActionOut(pChild,fadeTime,true);
        }
    }else
    {
//        spr->setOpacity(0);
        spr->runAction(CCFadeOut::create(fadeTime));
    }
}
int NSGameHelper::get_length(int x)
{
    if (x==0) {
        return 1;
    }
    using namespace std;
    int leng=0;
    while(x)
    {
        x/=10;
        leng++;
    }
    return leng;
}

void NSGameHelper::setColorGray(CCSprite* spr,bool isGray)
{
    if (isGray) {
        spr->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureGray));
    }else
    {
        spr->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
    }
}

void NSGameHelper::setAllOpacity(CCNode* node,int o)
{
    CCSprite* spr = dynamic_cast<CCSprite*>(node);
    if (spr) {
        spr->setOpacity(o);
    }
    CCObject* pObj = NULL;
    CCArray* pChildren = node->getChildren();
    CCARRAY_FOREACH(pChildren, pObj)
    {
        CCNode* pChild = (CCNode*)pObj;
        setAllOpacity(pChild,o);
    }
}
void NSGameHelper::changeParent(CCNode* parent,CCNode* child)
{
    child->retain();
    child->removeFromParentAndCleanup(false);
    parent->addChild(child);
    child->release();
}
void NSGameHelper::setStar(CCSprite ** Stars, uint8_t star)
{
    int index;
    for (index=0; index<star; ++index)
    {
        if (Stars[0]!=NULL) {
            Stars[index]->setVisible(true);
        }
    }
    for (; index<MAX_GER_STAR; ++index)
    {
        if (Stars[0]!=NULL) {
            Stars[index]->setVisible(false);
        }
    }
}


void NSGameHelper::setBtnFrame(CCControlButton* btn, const char* atlasName,const char* frameName1)
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(atlasName);
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName1);
    if (frame)
    {
        btn->setBackgroundSpriteFrameForState(frame, CCControlStateNormal);
        btn->setBackgroundSpriteFrameForState(frame, CCControlStateHighlighted);
        btn->setBackgroundSpriteFrameForState(frame, CCControlStateSelected);
        btn->setBackgroundSpriteFrameForState(frame, CCControlStateDisabled);
    }
}
void NSGameHelper::setBtnFrame(CCControlButton* btn, const char* atlasName,const char* frameName1,const char* frameName2,const char* frameName3)
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(atlasName);
    btn->setBackgroundSpriteFrameForState(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName1), CCControlStateNormal);
    btn->setBackgroundSpriteFrameForState(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName2), CCControlStateHighlighted);
    btn->setBackgroundSpriteFrameForState(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName2), CCControlStateSelected);
    btn->setBackgroundSpriteFrameForState(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName3), CCControlStateDisabled);
}
bool NSGameHelper::isOneDay()
{
    struct timeval now;  // 秒/毫秒
    gettimeofday(&now, NULL);
    struct tm * tm;
    time_t timep = time(NULL);
    tm = localtime(&timep);
    int year = tm->tm_year + 1900;
    int month = tm->tm_mon + 1;
    int day = tm->tm_mday;
    
    int _year = CCUserDefault::sharedUserDefault()->getIntegerForKey("last_year");
    int _month = CCUserDefault::sharedUserDefault()->getIntegerForKey("last_month");
    int _day = CCUserDefault::sharedUserDefault()->getIntegerForKey("last_day");
    
    if (year == _year&&month == _month&&day == _day)
    {
        return true;
    }
    return false;
}
