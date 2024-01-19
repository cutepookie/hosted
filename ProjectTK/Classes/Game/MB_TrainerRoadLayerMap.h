//
//  MB_TrainerRoadLayerMap.h
//  ProjectMB
//
//  Create by wenyong on 20/1/2015.
//
//
#ifndef __ProjectMB__MB_TrainerRoadLayerMap__
#define __ProjectMB__MB_TrainerRoadLayerMap__

#include "MB_ResWindow.h"
class MB_FunctionTrainerRoad;

#define DungeonCount 20
class MB_TrainerRoadLayerMap : public MB_ResWindow,public CCBMemberVariableAssigner
{
public:
    static MB_TrainerRoadLayerMap* create(MB_FunctionTrainerRoad*);
	MB_TrainerRoadLayerMap();
	virtual ~MB_TrainerRoadLayerMap();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    
    CCSize getLayerSize(){return m_pNodeSize->getContentSize();}
protected:
    void addNodes();
private:
    CCNode*	m_pNodeSize;
    CCNode*	m_pNodeD[DungeonCount];
    CCNode*	m_pNodeB[DungeonCount];
    MB_FunctionTrainerRoad* m_pFunction;
    
    CC_SYNTHESIZE_READONLY(CCNode*, m_pActivtedNode, ActivtedNode);
};
#endif /* defined(__ProjectMB__MB_TrainerRoadLayerMap__) */