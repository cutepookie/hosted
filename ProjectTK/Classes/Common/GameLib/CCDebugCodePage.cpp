//
//  CCDebugCodePage.cpp
//  ProjectTK
//
//  Created by yong wen on 2/26/14.
//
//

#include "CCDebugCodePage.h"
#include "UnityXml/MB_XmlManager.h"
#include "Game.h"
#include "MB_BattleConfigData.h"
#include "MB_CardStarConfig.h"
#include "MB_SuitSystem.h"
#include "MB_LayerScale9Sprite.h"
#include "MB_LayerRuningCool.h"

NSDebugSpace::CCDebugInterface* pDebug = NULL;

void NSDebugSpace::beginDebugCode()
{
    
#ifdef DEBUG
    pDebug = new CCGuiCodeGenerator;
    pDebug->begin();

#endif
}
void NSDebugSpace::endDebugCode()
{
#ifdef DEBUG
    pDebug->end();
    delete  pDebug;
#endif
}




#include "MB_GuiCcbCodeGenerator.h"

void NSDebugSpace::CCGuiCodeGenerator::generate(const char* pClassName,const char* pFile)
{
    std::string class_name = pClassName;
    CcbWindowClass* pClass = CcbWindowClass::create(class_name.c_str(), pFile);
    if (pClass)
    {
        pClass->generalHeader(("/Users/yuanwugang/Desktop/save_code/"+class_name+".h").c_str());
        pClass->generalCpp(("/Users/yuanwugang/Desktop/save_code/"+class_name+".cpp").c_str());
    }
}

void NSDebugSpace::CCGuiCodeGenerator::begin()
{

    generate("MB_NoticeMain","res/notice_layer_01.ccbi");
}

#include "MB_LayerRegistration.h"

void NSDebugSpace::CCCalenderDebug::begin()
{
    CCScene* pScene = CCScene::create();
    pScene->addChild(MB_LayerRegistration::create());
    CCDirector::sharedDirector()->replaceScene(pScene);
}
