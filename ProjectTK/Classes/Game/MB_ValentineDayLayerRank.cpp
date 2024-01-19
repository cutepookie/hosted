//
//  MB_ValentineDayLayerRank.cpp
//  ProjectMB
//
//  Created by wenyong on 15-1-22.
//
//

#include "MB_ValentineDayLayerRank.h"
#include "MB_FunctionModule.h"

bool MB_ValentineDayLayerRank::init()
{
    CCNode* pNode = loadResource("res/valentineday_layer_rank.ccbi");
    if(pNode)
	{
        addChild(NSGameHelper::createDisableTouchLayer1());
		addChild(pNode);
        onInitialized();
		return true;
	}
	return false;
}