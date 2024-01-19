
#include "MB_SceneReconnect.h"
MB_SceneReconnect::MB_SceneReconnect(){

}
MB_SceneReconnect::~MB_SceneReconnect(){

}
CCScene *MB_SceneReconnect::scene(){

    CCScene *scene = CCScene::create();
    MB_SceneReconnect  * layer = MB_SceneReconnect::create();
    scene->addChild(layer);
    
    return scene;
}
MB_SceneReconnect * MB_SceneReconnect::create(){

    MB_SceneReconnect *ptr = new MB_SceneReconnect();
    if(ptr && ptr->init()){
    
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
bool MB_SceneReconnect::init(){

    CCLayer::init();
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/main_layer_loading.ccbi", this);
    CC_SAFE_DELETE(pCCBReader);
    this->addChild(node);

    return true;
}
