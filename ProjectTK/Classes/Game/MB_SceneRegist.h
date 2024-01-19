
#ifndef __ProjectMB__MB_SceneRegist__
#define __ProjectMB__MB_SceneRegist__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;


class MB_SceneRegist : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
,public CCNodeLoaderListener
,public CCEditBoxDelegate
{
public:
    MB_SceneRegist();
    ~MB_SceneRegist();
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MB_SceneRegist, create);
    static MB_SceneRegist * create(int LayerTag);
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    void initAccountEditBox(CCEditBox* editBox);
    void initPasswordEditBox(CCEditBox* editBox);
    void initPassword2EditBox(CCEditBox* editBox);
    void initPhoneEditBox(CCEditBox* editBox);
    
    void onCommitClicked(CCObject* pSender);
    void onBackClicked(CCObject* pSender);
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
//	static cocos2d::CCScene* scene();
	
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
    
    //从服务器收到消息的回调函数
    void onMsgRecv(CCNode* node, SocketResponse* response);
    void onHttpMsgRecv(CCNode* node, CCHttpResponse* response);
    void createAccInfo();
    
private:
    //CCBAnimationMgr *m_pAnimationMgr;
    CCBReader* pCCBReader;
    CCEditBox* m_pEditName;
    CCEditBox* m_pEditPassword;
    CCEditBox* m_pEditPasswordConfirm;
    CCEditBox* m_pEditPhone;
};

class MB_SceneRegistLoader:public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MB_SceneRegistLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MB_SceneRegist);
};


#endif /* defined(__ProjectMB__MB_SceneRegist__) */
