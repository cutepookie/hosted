
//

#ifndef __ProjectMB__MB_SceneLoginBackground__
#define __ProjectMB__MB_SceneLoginBackground__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "MB_ResWindow.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MB_SceneLoginBackground : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
private :

    CCLabelTTF *    m_pLabelVersion;
    std::string m_nUpdateUrl;
    int updateType;

    
        
public:
    MB_SceneLoginBackground();
    ~MB_SceneLoginBackground();
//    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MB_SceneLoginBackground, create);
	
    static CCLayer* create();

//    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
//	virtual bool init();
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
//	
//    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
//    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
//    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
//    
//    void enterVersionLayer();
//    void sendMainVersionCheck();
//    void onHttpMsgRecv(CCNode* node, CCHttpResponse* response);
//    void onUpdateClick(CCObject *);
//    void onCancel(CCObject *);
    
};

#endif /* defined(__ProjectMB__MB_SceneLoginBackground__) */
