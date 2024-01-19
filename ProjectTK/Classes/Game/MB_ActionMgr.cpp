
#include "MB_ActionMgr.h"
#include "MB_SceneGame.h"
#include "../Common/MB_RenderLayer.h"
#include "MB_NodeShow.h"
//#include "MB_FightData.h"
#define STATE_ABSORB 0x8
#define STATE_DEAD   0x10
#define STATE_CRIT 0x40
#define STATE_REEL 0x20
#define STATE_DAMAGE_BACK 0x4
#define ACTION_MISS 0x1
#define UN_REEL 0x5
#define ACTION_REBORN 9


std::map<std::string, CCData *> MB_ActionMgr::m_pCCBiCache;

MB_ActionMgr::MB_ActionMgr(MB_NodeShow *role, CCNode *rootNode) :m_pList(NULL){

	m_pNowactionNode = role;
	m_pRootNode = rootNode;
	isActionDead = false;
	effectdead = false;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	m_Point = CCPoint(size.width / 2.0f, size.height / 2.0f);
	m_pSprite = NULL;
    m_bIsScaleAction = false;
}
MB_ActionMgr::~MB_ActionMgr(){

	CC_SAFE_RELEASE_NULL(m_pSprite);

}
void MB_ActionMgr::puargeCache(){

	std::map<std::string, CCData *>::iterator it = m_pCCBiCache.begin();
	std::map<std::string, CCData *>::iterator  end = m_pCCBiCache.begin();
	for (; it != end; it++) {

		delete  it->second;
	}
	m_pCCBiCache.clear();

}
CCData * MB_ActionMgr::readFileNode(const char *filename){
	//    CCLOG("pName=========+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++%s", filename);
	std::map<std::string, CCData *> ::iterator actionIterator = m_pCCBiCache.find(filename);
	if (actionIterator != m_pCCBiCache.end()) {

		return actionIterator->second;
	}
	else
	{

		if (NULL == filename || strlen(filename) == 0)
		{
			return NULL;
		}

		std::string strCCBFileName(filename);
		std::string strSuffix(".ccbi");
		// Add ccbi suffix
		if (!CCBReader::endsWith(strCCBFileName.c_str(), strSuffix.c_str()))
		{
			strCCBFileName += strSuffix;
		}
		std::string strPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(strCCBFileName.c_str());
		unsigned long size = 0;
		unsigned char * pBytes = CCFileUtils::sharedFileUtils()->getFileData(strPath.c_str(), "rb", &size);
		CCData *data = new CCData(pBytes, size);
		CC_SAFE_DELETE_ARRAY(pBytes);
		m_pCCBiCache.insert(std::pair<std::string, CCData *>(filename, data));

		return  data;
	}

}

void MB_ActionMgr::playKillTheAnimation(p_action *list){

	this->m_pList = list;
	if (m_pList->addSp < 0)
	{
		uint16_t i = m_pNowactionNode->getFighter()->petTypeID;
		if (i < 10000)
		{
			MB_SceneGame* pNode = dynamic_cast<MB_SceneGame*>(m_pRootNode);
			if (pNode)
			{
				pNode->actionAddDelayTime(1.0f);
			}

			MB_PetTemplate* pTemplate = MB_PetMgr::getInstance()->getPetTemplateByID(i);
			if (pTemplate)
			{
				MB_SkillData *data = MB_SkillMgr::getInstance()->getSkillDataByID(pTemplate->getSkillIDByIndex(1));
				if (data != NULL)
				{
					const char* str = data->getSkillName();
                    m_bIsScaleAction = list->petPos>0&&list->targetPos[1]!='/0';
                    m_bGlobalIsScaleAction = m_bIsScaleAction;
                    playSkillsRead(i, m_pNowactionNode->getFighter()->petQuality, const_cast<char*>(str),m_bIsScaleAction);
				}
			}
			return;
		}
	}
	playKillAnimation();
}

void MB_ActionMgr::playKillAnimation()
{
	if (this->m_pList->action->speffect != NULL){

		int prerand = rand() % 100;
		if (prerand < this->m_pList->action->speffect->effectType){

			CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
			cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
			char filepath[100];
			sprintf(filepath, "res/%s", this->m_pList->action->speffect->effectName);
			CCData * data = readFileNode(filepath);
			if (data == NULL){

				goPlay();
				return;
			}
			// CCNode * node =  ccbReader->readNodeGraphFromFile(filepath);
			CCNode * node = ccbReader->readNodeGraphFromData(data, this, CCDirector::sharedDirector()->getWinSize());
			node = MB_NodeSkill::create(node);
			ccbReader->release();
			if (node == NULL){

				goPlay();
				return;
			}

			m_pRootNode->addChild(node, 8);
			node->runAction(CCSequence::create(CCDelayTime::create(this->m_pList->action->speffect->effectTime),
				CCCallFunc::create(this, callfunc_selector(MB_ActionMgr::goReStart)),
				CCCallFuncN::create(this, callfuncN_selector(MB_ActionMgr::removeNodeAndCleanUp)), NULL));

			((MB_SceneGame *)m_pRootNode)->setTouch(false);
			((MB_SceneGame *)m_pRootNode)->unschedule(schedule_selector(MB_SceneGame::tickAniamtion));

			if (m_pSprite){

				m_pSprite->setVisible(true);
				m_pSprite->setPosition(m_pSprite->getParent()->convertToNodeSpace(m_Point));
				CC_SAFE_RELEASE_NULL(m_pSprite);;
			}

			return;
		}


	}

	goPlay();
}
void MB_ActionMgr::goReStart(){

	((MB_SceneGame *)m_pRootNode)->setTouch(true);
	((MB_SceneGame *)m_pRootNode)->schedule(schedule_selector(MB_SceneGame::tickAniamtion));
	goPlay();
}
void MB_ActionMgr::goPlay(){

	bool iscrit = false;
	bool is_reel = false;

	this->AttackactionOver(m_pList->action);

	char state = m_pList->state;

	if ((state & STATE_ABSORB) == STATE_ABSORB){

		MB_Action * action = MB_ActionData::getInstance()->getActionByID(7);
		this->AttackactionOver(action);
	}

	if ((state & STATE_CRIT) == STATE_CRIT){

		iscrit = true;
	}
	if ((state & STATE_REEL) == STATE_REEL){

		is_reel = true;
		MB_Action * action = MB_ActionData::getInstance()->getActionByID(6);
		this->AttackactionOver(action);
	}
	if ((state & STATE_DAMAGE_BACK) == STATE_DAMAGE_BACK){

		MB_Action * action = MB_ActionData::getInstance()->getActionByID(8);
		this->AttackactionOver(action);

	}
	if ((state & STATE_DEAD) == STATE_DEAD){

		effectdead = true;
		isActionDead = false;
		MB_Action * action = MB_ActionData::getInstance()->getActionByID(4);
		this->AttackactionOver(action);
		isActionDead = true;
	}
	if (isActionDead == false && is_reel == true && m_pList->action->actionID != UN_REEL) {

		this->addReelEffct();
	}

	if (m_pList->action->actionID != ACTION_MISS){

		if (m_pList->addHp != 0) {

			CCNode * m_pDamage = m_pNowactionNode->getDamageNode();
			m_pNowactionNode->changeBoold(m_pList->addHp);

			if (global_sceneGame != NULL) {
				global_sceneGame->setBlood(m_pNowactionNode->getFighter()->petPos, m_pList->addHp);
			}


			MB_NodeDamage* label = MB_NodeDamage::create(m_pList->addHp, iscrit);
			m_pDamage->addChild(label, 20);
			if (m_pNowactionNode->getBoss()) {

				label->setScale(1.2f);
			}

		}


	}
	if (m_pList->action->actionID == UN_REEL) {

		this->delReelEffect();
	}
	if (m_pList->addSp != 0){

		m_pNowactionNode->changeSp(m_pList->addSp);
        if(m_pNowactionNode->getFighter()->petSp >= 100 && isActionDead == false ){
            
            addAngryEffct();
        }
        if(m_pNowactionNode->getFighter()->petSp <100){
            
            delAngryffect();
        }
	}

	if (isActionDead){

		m_pNowactionNode->whenDead();
		this->delReelEffect();
	}
}
void MB_ActionMgr::addReelEffct(){

	if (m_pNowactionNode->getParent()->getChildByTag(REEL_NODE) != NULL){

		return;
	}
	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	char filepath[] = "res/eff_node_stun.ccbi";
	// CCNode * node = ccbReader->readNodeGraphFromFile(filepath);
	CCData * data = readFileNode(filepath);
	if (data == NULL){

		return;
	}
	CCNode * node = ccbReader->readNodeGraphFromData(data, this, CCDirector::sharedDirector()->getWinSize());
	node = MB_NodeSkill::create(node);
	node->setTag(REEL_NODE);
	m_pNowactionNode->getParent()->addChild(node, 6);
	ccbReader->release();
	if (m_pNowactionNode->getBoss()) {

		node->setScale(1.5f);
	}

}
void MB_ActionMgr::delReelEffect(){

	for (CCNode *node = m_pNowactionNode->getParent()->getChildByTag(REEL_NODE); node != NULL; node = m_pNowactionNode->getParent()->getChildByTag(REEL_NODE)) {

		node->removeFromParentAndCleanup(true);
	}

}
static void rotation(CCNode* pNode, float angle)
{
	if (pNode == NULL || pNode->getChildrenCount() == 0)
	{
		return;
	}

	CCArray* pArray = pNode->getChildren();
	CCParticleSystemQuad *pParticle = NULL;
	CCNode* pTemp = NULL;
	CCSprite* pSprite = NULL;
	CCARRAY_FOREACH_4TYPE(pArray, CCNode*, pTemp)
	{
		pParticle = dynamic_cast<CCParticleSystemQuad*>(pTemp);
		if (pParticle)
		{
			pParticle->setAngle(pParticle->getAngle() + angle);
		}
		else
		{
			pSprite = dynamic_cast<CCSprite*>(pTemp);
			if (pSprite)
			{
				pSprite->setRotation(pSprite->getRotation() + angle);
			}
			else
			{
				rotation(pTemp, angle);
			}
		}
	}
}
void MB_ActionMgr::rotationNode(CCNode* pNode, const CCPoint& to, const CCPoint& from)
{
	float orginalAngel;
	CCPoint dir = ccpSub(to, from);

	if (from.x - to.x > 10) {
		orginalAngel = CC_RADIANS_TO_DEGREES(atan2f(dir.x, dir.y)) + 6;
	}
	else if (from.x - to.x < -10)
	{
		orginalAngel = CC_RADIANS_TO_DEGREES(atan2f(dir.x, dir.y))+5 ;
	}

//    CCLog("to.x=======%f",to.x);
//    CCLog("to.y=======%f",to.y);
//    CCLog("from.x=======%f",from.x);
//    CCLog("from.y=======%f",from.y);
//    CCLog("orginalAngel=======%f",orginalAngel);
	rotation(pNode, orginalAngel);
	return;
}

void MB_ActionMgr::effect(const char *filename, CCPoint &from, CCPoint &to, float starttime, float time, int flip, int turnMove,int  actionType, effectPosType type){
    if (from.y>300 && actionType!=6&& actionType!=9&& actionType!=11&& actionType!=0&& actionType!=13&& actionType!=7&& actionType!=10) {
        if (strcmp(filename, "fatalskill") == 0) {
            MB_SceneGame *showNode = (MB_SceneGame *)m_pRootNode;
            showNode->tempZhongZu = MB_PetMgr::getInstance()->getPetTemplateByID(m_pNowactionNode->getFighter()->petTypeID)->getPetKingdom();
        }
        return;
    }
    CCLOG("effect : %s", filename);
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    char filepath[100];
    if (strcmp(filename, "fatalskill") == 0) {
        sprintf(filepath, "res/fatalskill_poison_fly0%d.ccbi", MB_PetMgr::getInstance()->getPetTemplateByID(m_pNowactionNode->getFighter()->petTypeID)->getPetKingdom());
    }
    else if (strcmp(filename, "fatalskill_B") == 0) {
        MB_SceneGame *showNode = (MB_SceneGame *)m_pRootNode;
        sprintf(filepath, "res/fatalskill_pm_beattack0%d.ccbi", showNode->tempZhongZu);
    }
    else if (from.y<300&&strcmp(filename, "eff_node_stun.ccbi") == 0) {
        sprintf(filepath, "res/%s", "eff_node_stunOur.ccbi");
    }
    else
    {
        sprintf(filepath, "res/%s", filename);
    }
    CCData * data = readFileNode(filepath);
    if (data == NULL){
        return;
    }
    CCNode * node = ccbReader->readNodeGraphFromData(data, this, CCDirector::sharedDirector()->getWinSize());
    if (strcmp(filename, "skill_poison_fly.ccbi") == 0) {
        CCSprite* spr = (CCSprite*)node->getChildren()->objectAtIndex(0);
        if (from.x < to.x) {
            spr->setFlipX(true);
            spr->setPosition(ccp(-15,25));
        }else{
            spr->setPosition(ccp(15,25));
        }
    }
    //
    ccbReader->release();
    
    from = m_pNowactionNode->getParent()->convertToWorldSpace(m_pNowactionNode->getPosBeforeAnimation());
    from = m_pRootNode->convertToNodeSpace(from);
    if (m_bIsScaleAction) {
        node->setTag(123);
        m_pRootNode->addChild(node, 5);
    }else
    {
        node = MB_NodeSkill::create(node);
        if (node == NULL){
            
            return;
        }
        node->setPosition(ccp(0,0));
        m_pNowactionNode->m_pAnimationNode->addChild(node);
    }

    node->setVisible(false);

	if (m_pSprite){
		m_pSprite->setVisible(true);
		m_pSprite->setPosition(m_pSprite->getParent()->convertToNodeSpace(m_Point));
		CC_SAFE_RELEASE_NULL(m_pSprite);
	}

    if (m_pList->petPos < 0 && flip != 0){

        node->setRotation(180);
    }
    if (turnMove != 0&&!m_bIsScaleAction)
    {
        rotationNode(node, to, from);
    }

	if (type == kPosTypeMoveToTarget)
	{
		node->runAction(CCSequence::create(CCDelayTime::create(starttime), CCShow::create(), CCDelayTime::create(time*1.55f), CCCallFuncN::create(this, callfuncN_selector(MB_ActionMgr::stopEmit)), NULL));
	}
	else
	{
		if (effectdead || strcmp(filename, "eff_node_dead.ccbi") == 0){
			m_pNowactionNode->whenDead();
			this->delReelEffect();
			node->setTag(m_pNowactionNode->getFighter()->petPos + DEAD_EFFECT_TAG);

			node->removeFromParentAndCleanup(false);
			m_pNowactionNode->getParent()->addChild(node);
			node->setPosition(m_pNowactionNode->getPosition());
			node->setVisible(true);
		}
		else {
			node->runAction(CCSequence::create(CCDelayTime::create(starttime), CCShow::create(), CCDelayTime::create(time*1.55f), CCCallFuncN::create(this, callfuncN_selector(MB_ActionMgr::removeNodeAndCleanUp)), NULL));
		}
	}

	//複活
	if (strcmp(filename, "eff_node_reborn.ccbi") == 0)
	{
		CCNode* childer_ = m_pNowactionNode->getParent()->getChildByTag(m_pNowactionNode->getFighter()->petPos + DEAD_EFFECT_TAG);
		if (childer_ != NULL) {
			childer_->removeFromParent();
		}
        m_pNowactionNode->setShowCard();
        if (m_pNowactionNode->getFighter()->petSp >= 100)
        {
            addAngryEffct();
        }
	}
	if (m_pNowactionNode->getBoss()) {
		node->setScale(1.5f);
	}
}


void MB_ActionMgr::AttackactionOver(MB_Action *action){

	if (action->actionID == ACTION_REBORN){

		isActionDead = false;
		effectdead = false;
		m_pRootNode->removeChildByTag(m_pNowactionNode->getFighter()->petPos + DEAD_EFFECT_TAG);
		m_pNowactionNode->setDetailShow(m_pNowactionNode->isDetailShow());
	}

	if (isActionDead || action == NULL) {

		return;
	}
	if (m_pList->petPos < 0){
        if (strlen(action->actionFlipName) != 0) {
            m_pNowactionNode->callAnimationByName(action->actionFlipName);
        }else
        {
            if (strcmp(action->effect->effectName, "skill_poison_fly.ccbi") == 0) {
                m_pNowactionNode->callAnimationByName("pm_attack_B");
            }else
            {
                m_pNowactionNode->callAnimationByName(action->actionName);
            }
        }
    }else
    {
        if (strcmp(action->effect->effectName, "skill_poison_fly.ccbi") == 0) {
            m_pNowactionNode->callAnimationByName("pm_attack_B");
        }
    }
	MB_SceneGame *showNode = (MB_SceneGame *)m_pRootNode;
    if (action->effect!=NULL) {
        for (MB_ActionEffect * effect = action->effect; effect != NULL; effect = effect->next) {
            
            if (strlen(effect->sound) > 0) {
                
                MB_Audio::getInstance()->playEffect(effect->sound);
            }
            
            if (effect->effectType == kPosTypeSelf){
                
                CCPoint from = m_pNowactionNode->getParent()->getPosition();
                from = m_pNowactionNode->getParent()->getParent()->convertToWorldSpace(from);
                from = m_pRootNode->convertToNodeSpace(from);
                this->effect(effect->effectName, from, from, effect->effectStartTime, effect->effectTime, effect->flipType, effect->turnMove,action->actionType);
                
            }
            else  if (effect->effectType == kPosTypeMoveToTarget){
                
                for (int i = 0; m_pList->targetPos[i] != '\0' && i < 6; i++){
                    
                    MB_NodeShow *beattack = showNode->getActorByindexAndType(abs(m_pList->targetPos[i]) - 1, m_pList->targetPos[i]);
                    if (beattack == NULL){
                        
                        continue;
                    }
                    
                    CCPoint from = m_pNowactionNode->getParent()->getPosition();
                    CCPoint to = beattack->getParent()->getPosition();
                    to = beattack->getParent()->getParent()->convertToWorldSpace(to);
                    to = m_pRootNode->convertToNodeSpace(to);
                    
                    from = m_pNowactionNode->getParent()->getParent()->convertToWorldSpace(from);
                    from = m_pRootNode->convertToNodeSpace(from);
                    this->effect(effect->effectName, from, to, effect->effectStartTime, effect->effectTime, effect->flipType,action->actionType, kPosTypeMoveToTarget);
                    if (from.y<300 && strcmp(effect->effectName, "fatalskill") == 0) {
                        break;
                    }
                }
            }
            else  if (effect->effectType == kPosTypeTarget){
                
                for (int i = 0; m_pList->targetPos[i] != '\0' && i < 6; i++){
                    
                    MB_NodeShow *beattack = showNode->getActorByindexAndType(abs(m_pList->targetPos[i]) - 1, m_pList->targetPos[i]);
                    if (beattack == NULL){
                        
                        continue;
                    }
                    
                    CCPoint to = beattack->getParent()->getPosition();
                    to = beattack->getParent()->getParent()->convertToWorldSpace(to);
                    to = m_pRootNode->convertToNodeSpace(to);
                    this->effect(effect->effectName, to, to, effect->effectStartTime, effect->effectTime, effect->flipType, effect->turnMove,action->actionType);
                }
                
                
            }
            else  if (effect->effectType == kPosTypeOur){
                
                CCPoint pos = showNode->getCenterByType(m_pList->petPos > 0);
                this->effect(effect->effectName, pos, pos, effect->effectStartTime, effect->effectTime, effect->flipType, effect->turnMove,action->actionType);
                
            }
            else  if (effect->effectType == kPosTypeEnemy){
                
                CCPoint pos = showNode->getCenterByType(m_pList->petPos < 0);
                this->effect(effect->effectName, pos, pos, effect->effectStartTime, effect->effectTime, effect->flipType, effect->turnMove,action->actionType);
                
            }
        }
    }
}

bool MB_ActionMgr::goShock()
{
	CCScene* fightScene = CCDirector::sharedDirector()->getRunningScene();
	if (fightScene && fightScene->getChildByTag(FIGHTSCENE))
	{

	}
	else
	{
		return false;
	}

	CCPoint size = fightScene->getChildByTag(FIGHTSCENE)->getPosition();
	CCMoveTo* left1 = CCMoveTo::create(0.05, ccp(size.x + 3, size.y));
	CCMoveTo* right1 = CCMoveTo::create(0.05, ccp(size.x - 3, size.y));
	CCMoveTo* top1 = CCMoveTo::create(0.05, ccp(size.x, size.y + 3));
	CCMoveTo* rom1 = CCMoveTo::create(0.05, ccp(size.x, size.y - 3));
	CCMoveTo* last = CCMoveTo::create(0.05, ccp(size.x, size.y));
	CCFiniteTimeAction* action3 = CCSequence::create(left1, right1, top1, rom1, last, NULL);
	fightScene->getChildByTag(FIGHTSCENE)->runAction(action3);
	return true;
}
void MB_ActionMgr::removeNodeAndCleanUp(CCNode *p){
    if (p->getTag()==123) {
        m_bIsScaleAction = false;
        m_bGlobalIsScaleAction = false;
    }
	p->removeFromParentAndCleanup(true);
}

void MB_ActionMgr::stopEmit(CCNode* node)
{
	CCParticleSystem* parNode = NULL;
	CCNode* tempNode = NULL;

	for (int i = 0; i < node->getChildrenCount(); ++i) {
		parNode = dynamic_cast<CCParticleSystem*>(node->getChildren()->objectAtIndex(i));

		if (parNode != NULL)
		{
			parNode->setDuration(0.0f);
		}
		else
		{
			tempNode = dynamic_cast<CCNode*>(node->getChildren()->objectAtIndex(i));
			if (tempNode != NULL) {
				tempNode->removeFromParentAndCleanup(true);
			}
		}
	}
	node->runAction(CCCallFunc::create(node, callfunc_selector(CCNode::removeFromParent)));
}
bool MB_ActionMgr::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){

	if (strcmp(pMemberVariableName, "mpcover") == 0){
		pNode->setVisible(false);
		CC_SAFE_RELEASE_NULL(m_pSprite);
		m_pSprite = pNode;
		MB_RenderLayer::setFileAndPos((CCSprite *)pNode, m_pNowactionNode->getFilaeName(), m_pNowactionNode->getWorldPlace(), m_pNowactionNode->getCard()->getScaleX() *0.9f);
		CC_SAFE_RETAIN(m_pSprite);

	}
	return  false;
}

void MB_ActionMgr::playSkillsRead(uint16_t tid, uint8_t rank, char* skillName,bool isScaleAction)
{
	MB_NodeSkillsRead* pNode = MB_NodeSkillsRead::create();
	pNode->setCallBack(this, callfunc_selector(MB_ActionMgr::playKillAnimation));
	pNode->setCardTid(tid, rank, skillName,isScaleAction);
	m_pRootNode->addChild(pNode, 8);
}
void MB_ActionMgr::onSkillsReadOver()
{

}

void MB_ActionMgr::addAngryEffct(){
    
    if ( m_pNowactionNode->getParent()->getChildByTag(ANGERY_NODE) != NULL ){
        
        return;
    }
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    char filepath[] = "res/eff_node_capacity_2.ccbi";
    CCData * data = readFileNode(filepath);
    if(data == NULL){
        
        return;
    }
    CCNode * node =  ccbReader->readNodeGraphFromData(data,this,CCDirector::sharedDirector()->getWinSize());
    ccbReader->release();
    m_pNowactionNode->addCapacity(node);
}
void MB_ActionMgr::delAngryffect(){
    
    //    for (CCNode *node = m_pNowactionNode->getParent()->getChildByTag(ANGERY_NODE); node != NULL; node = m_pNowactionNode->getParent()->getChildByTag(ANGERY_NODE) ) {
    //
    //        node->removeFromParentAndCleanup(true);
    //    }
    m_pNowactionNode->removeCapacity();
    
}
MB_NodeSkillsRead::MB_NodeSkillsRead()
{
	m_pAnimation = NULL;
	m_pTarget = NULL;
	m_pTTFName1 = NULL;
    m_pSkill = NULL;
    m_pSpriteCard1 = NULL;
    m_pNode1 = NULL;
    m_pStar = NULL;
}
MB_NodeSkillsRead::~MB_NodeSkillsRead()
{
	CC_SAFE_RELEASE_NULL(m_pAnimation);
	CC_SAFE_RELEASE_NULL(m_pTarget);
	CC_SAFE_RELEASE_NULL(m_pTTFName1);
    CC_SAFE_RELEASE_NULL(m_pSkill);
    CC_SAFE_RELEASE_NULL(m_pSpriteCard1);
    CC_SAFE_RELEASE_NULL(m_pNode1);
    CC_SAFE_RELEASE_NULL(m_pStar);
}

bool MB_NodeSkillsRead::init()
{
	CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    pNode = pCCBReader->readNodeGraphFromFile("res/battle_layer_mustkill.ccbi", this);
	if (pNode == NULL)
	{
		CC_SAFE_RELEASE(pCCBReader);
		return false;
	}
    addChild(pNode,2);
    m_pAnimation = pCCBReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pAnimation);
    CC_SAFE_RELEASE(pCCBReader);

	CCClippingNode *clipper = CCClippingNode::create();
	clipper->setContentSize(CCDirector::sharedDirector()->getWinSize());
	clipper->setAnchorPoint(ccp(0.5, 0.5));
	clipper->setAlphaThreshold(0.05f);
    clipper->setPosition(clipper->getContentSize()/2);

    NSGameHelper::changeParent(clipper, m_pStar);
	clipper->setStencil(m_pStar);
    
    m_pStar->runAction(CCMoveTo::create(15/30.0f, ccp(152.8f,681.8f)));
    m_pStar->runAction(CCSequence::create(CCRotateBy::create(11/30.0f,90) ,CCRotateBy::create(34/30.0f,130),NULL) );
    NSGameHelper::changeParent(clipper, m_pSpriteCard1);
	m_pNode1->addChild(clipper);
    
    
    NSGameHelper::runOptActionIn(m_pSkill, .5f, true);
    
    bgColor = CCLayerColor::create(ccc4(0, 0, 0, 0), 640, 1136);
    bgColor->runAction(CCFadeTo::create(.1f, 150));
    addChild(bgColor,-1);
    
	return true;
}
bool MB_NodeSkillsRead::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTTFName1", CCLabelTTF*, m_pTTFName1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSkill", CCNode*, m_pSkill);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCard1", CCSprite*, m_pSpriteCard1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pStar", CCSprite*, m_pStar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNode1", CCNode*, m_pNode1);
    
	return false;
}

void MB_NodeSkillsRead::setCardTid(uint16_t tid, uint8_t rank, char* name,bool isScaleAction)
{
	MB_PetTemplate* pTemplete = MB_PetMgr::getInstance()->getPetTemplateByID(tid);
	if (pTemplete != NULL)
	{
		NSGameHelper::setSpriteFrame(m_pSpriteCard1, pTemplete->getPetCard(NSGameHelper::getShapeTypeByRank(rank)));
	}
	if (name != NULL)
	{
		m_pTTFName1->setString(name);
	}

	m_pAnimation->setAnimationCompletedCallback(this, callfunc_selector(MB_NodeSkillsRead::onAnimationOver));
    if (isScaleAction) {
        global_sceneGame->palyDaZhao(true);
    }
}

void MB_NodeSkillsRead::onExit()
{
	m_pAnimation->setAnimationCompletedCallback(NULL, NULL);
	MB_ResWindow::onExit();
}

void MB_NodeSkillsRead::onAnimationOver()
{
	m_pAnimation->setAnimationCompletedCallback(NULL, NULL);
	if (m_pTarget)
	{
		(m_pTarget->*m_pFunction)();
	}
//    NSGameHelper::runOptActionOut(pNode, .1f, true);
//    runAction(CCSequence::create(CCDelayTime::create(.5f),CCRemoveSelf::create(),NULL ));
//    bgColor->runAction(CCFadeOut::create(.5f));
    removeFromParent();
}

void MB_NodeSkillsRead::setCallBack(CCObject *target, SEL_CallFunc backFunc){
	CC_SAFE_RELEASE_NULL(m_pTarget);
	m_pTarget = target;
	m_pFunction = backFunc;
	CC_SAFE_RETAIN(m_pTarget);
}
