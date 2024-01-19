//
//  MB_FunctionMainWnd.cpp
//  ProjectPM
//
//  Created by Wenyon on 14-3-24.
//
//

#include "MB_FunctionMainWnd.h"
#include "MB_SceneMain.h"

void MB_FunctionMainWnd::setRoleInfoPanelVisable(bool bVisable)
{
    MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
    if (pScene)
    {
        MB_ResWindow* pWnd = pScene->getLayerRoleInfoHeader();
        if (pWnd)
        {
            pWnd->setVisible(bVisable);
        }
    }
}

bool MB_FunctionMainWnd::getRoleInfoPanelVisable()
{
    MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
    if (pScene)
    {
        MB_ResWindow* pWnd = pScene->getLayerRoleInfoHeader();
        if (pWnd)
        {
            return pWnd->isVisible();
        }
    }
    return true;
}

MB_FunctionMainWnd::MB_FunctionMainWnd()
{
    //CCLOG("CreateMainWnd:%p",this);
}
MB_FunctionMainWnd::~MB_FunctionMainWnd()
{
    //CCLOG("DestroyMainWnd:%p",this);
}