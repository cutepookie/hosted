//
//  MB_TrainerRoadLayerMap.cpp
//  ProjectMB
//
//  Create by wenyong on 20/1/2015.
//
//
#include "MB_TrainerRoadLayerMap.h"
#include "MB_FunctionTrainerRoad.h"
#include "MB_TrainerRoadConfigure.h"
#include "MB_LocalProto.h"
#include "MB_TrainerRoadNodeBox.h"
#include "MB_TrainerRoadNodePass.h"
MB_TrainerRoadLayerMap* MB_TrainerRoadLayerMap::create(MB_FunctionTrainerRoad* pFunction)
{
    MB_TrainerRoadLayerMap* pLayer = new MB_TrainerRoadLayerMap;
    if (pLayer && pLayer->init())
    {
        pLayer->m_pFunction = pFunction;
        pLayer->addNodes();
        pLayer->onResetWnd();
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}
MB_TrainerRoadLayerMap::MB_TrainerRoadLayerMap()
{
    m_pNodeSize	 = NULL;
    m_pFunction = NULL;
    m_pActivtedNode = NULL;
    for (int i = 0; i<20; ++i)
    {
        m_pNodeD[i] = NULL;
        m_pNodeB[i] = NULL;
    }
}
MB_TrainerRoadLayerMap::~MB_TrainerRoadLayerMap()
{
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    for (int i = 0; i<20; ++i)
    {
        CC_SAFE_RELEASE_NULL(m_pNodeD[i]);
        CC_SAFE_RELEASE_NULL(m_pNodeB[i]);
    }
}
bool MB_TrainerRoadLayerMap::init()
{
    CCNode* pNode = loadResource("res/road_layer_map.ccbi");
    if(pNode)
	{
		addChild(pNode);
        onResetWnd();
		return true;
	}
	return false;
}

#define ROAD_NODE_TAG 22
void MB_TrainerRoadLayerMap::addNodes()
{
    if(!m_pFunction)return;
    CCArray* pDungeons = MB_TrainerRoadConfig::getInstance()->getDungeons();
    CCArray* pBoxs = MB_TrainerRoadConfig::getInstance()->getBox();
    
    MB_TrainerRoadDungeon* pDungeon = NULL;
    int index = 0;
    CCARRAY_FOREACH_4TYPE(pDungeons, MB_TrainerRoadDungeon*, pDungeon)
    {
        MB_TrainerRoadNodePass* pNode = MB_TrainerRoadNodePass::create(pDungeon);

        m_pNodeD[index++]->addChild(pNode,0,ROAD_NODE_TAG);
    }
    
    index = 0;
    MB_TrainerRoadRewardBox* pBox = NULL;
    CCARRAY_FOREACH_4TYPE(pBoxs, MB_TrainerRoadRewardBox*, pBox)
    {
        MB_TrainerRoadNodeBox* pNode = MB_TrainerRoadNodeBox::create(pBox);
        m_pNodeB[index++]->addChild(pNode,0,ROAD_NODE_TAG);
    }
}

void MB_TrainerRoadLayerMap::onResetWnd()
{
    if(m_pFunction == NULL)return;
    int nCurIndex = m_pFunction->getCurID() - ROLE_BEGIN_ID;
    for (int i = 0; i<DungeonCount; ++i)
    {
        CCNode* pNode = m_pNodeD[i]->getChildByTag(ROAD_NODE_TAG);
        if(pNode)
        {
            MB_TrainerRoadNodePass* pTemp = dynamic_cast<MB_TrainerRoadNodePass*>(pNode);
            if (pTemp)
            {
                if(i == nCurIndex)
                {
                    pTemp->setStatus(m_pFunction->getStatus(),m_pFunction->getStatus() == DUNGEON_NOT_PASS);
                    m_pActivtedNode = pTemp->getParent();
                }
                else if(i < nCurIndex)
                {
                    pTemp->setStatus(DUNGEON_PASSED,false);
                }
                else
                {
                     pTemp->setStatus(DUNGEON_NOT_PASS,false);
                }
            }
        }
        
        pNode = m_pNodeB[i]->getChildByTag(ROAD_NODE_TAG);
        if(pNode)
        {
            MB_TrainerRoadNodeBox* pTemp = dynamic_cast<MB_TrainerRoadNodeBox*>(pNode);
            if (pTemp)
            {
                if(i == nCurIndex)
                {
                    if(m_pFunction->getStatus()==DUNGEON_NOT_PASS)
                    {
                        pTemp->setStatus(BOX_NOT_ACTIVATED);
                    }
                    else if(m_pFunction->getStatus()==DUNGEON_REWARDED)
                    {
                        pTemp->setStatus(BOX_ACTIVATED_REWARDED);
                    }
                    else
                    {
                        pTemp->setStatus(BOX_ACTIVATED);
                    }
                }
                else if(i < nCurIndex)
                {
                    pTemp->setStatus(BOX_ACTIVATED_REWARDED);
                }
                else pTemp->setStatus(BOX_NOT_ACTIVATED);
            }
        }
    }
}

bool MB_TrainerRoadLayerMap::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize",CCNode*,m_pNodeSize);
    
    char buff[10] = {0};
    for (int i = 0; i<20; ++i)
    {
        sprintf(buff, "D%d",i);
        if (pTarget == this && 0 == strcmp(pMemberVariableName, buff))
        {
            m_pNodeD[i] = pNode;
            CC_SAFE_RETAIN(m_pNodeD[i]);
            return true;
        }
        
        sprintf(buff, "B%d",i);
        if (pTarget == this && 0 == strcmp(pMemberVariableName, buff))
        {
            m_pNodeB[i] = pNode;
            CC_SAFE_RETAIN(m_pNodeB[i]);
            return true;
        }
    }
	return false;
}
