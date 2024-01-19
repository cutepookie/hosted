//
//  MB_LoginBackground.h
//  ProjectTK
//
//  Created by wenyong on 14-9-6.
//
//

#ifndef __ProjectMB__MB_LoginBackground__
#define __ProjectMB__MB_LoginBackground__

#include "MB_ResWindow.h"
#include "MB_UpdateSystem.h"
class RichText;
USING_NS_CC;
USING_NS_CC_EXT;
class MB_LayerResourceUpdate;
class MB_LoginBackground : public MB_ResWindow,
	public CCBMemberVariableAssigner,
	public CCBSelectorResolver,
	public MB_UpdateDelagete
{
private:
	virtual void onUpdateComplated();
	virtual void onFinishedInitialize();
	bool m_bCanUpdate;
	bool m_bCanTouch;
	bool isEndUpdate;
	CCNode* pRootNode;
	CCLabelTTF* m_pPecentTTF;
public:
	CREATE_FUNC(MB_LoginBackground);
	virtual void onError(AssetsManager::ErrorCode errorCode);
	virtual void onProgress(int percent);
	virtual void onSuccess();
	MB_LoginBackground();
	virtual void onEnter();
	~MB_LoginBackground();
	virtual bool init();
	virtual void onResetWnd(){};
	static cocos2d::CCScene* scene();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);

	void sendMainVersionCheck();
	void onHttpMsgRecv(CCNode* node, CCHttpResponse* response);
	void onUpdateClick(CCObject *);
	void onCancel(CCObject *);
	virtual void onNoPatchUpdate();
	void update(float dt);
	void setSomeVisible(bool b);
	MB_LayerResourceUpdate* m_pUpdateProgress;
};

#endif /* defined(__ProjectMB__MB_LoginBackground__) */
