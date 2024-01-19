//
//  MB_ValentineDayNodeRank.cpp
//  ProjectMB
//
//  Created by wenyong on 15-1-22.
//
//

#include "MB_ValentineDayNodeRank.h"

bool MB_ValentineDayNodeRank::init()
{
    CCNode* pNode = loadResource("res/valentineday_node_rank.ccbi");
    if(pNode)
	{
		addChild(pNode);
		return true;
	}
	return false;
}