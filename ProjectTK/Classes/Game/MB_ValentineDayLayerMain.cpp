//
//  MB_ValentineDayLayerMain.cpp
//  ProjectMB
//
//  Created by wenyong on 15-1-22.
//
//

#include "MB_ValentineDayLayerMain.h"


bool MB_ValentineDayLayerMain::init()
{
    CCNode* pNode = loadResource("res/valentineday_layer_activity.ccbi");
    if(pNode)
	{
		addChild(pNode);
        onInitialized();
		return true;
	}
	return false;
}