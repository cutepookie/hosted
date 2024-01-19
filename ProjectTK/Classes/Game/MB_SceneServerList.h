

#ifndef __ProjectMB__MB_SceneServerList__
#define __ProjectMB__MB_SceneServerList__

#include "Game.h"

USING_NS_CC;
USING_NS_CC_EXT;
class SDS_ServerListTouchDelegate;
class MB_SceneServerList : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
,public CCTableViewDataSource
,public CCTableViewDelegate
{
public:
    
    MB_SceneServerList();
    ~MB_SceneServerList();
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MB_SceneServerList, create);
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    
    void onLoginClicked(CCObject* pSender);
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    
    //从服务器收到消息的回调函数
    void onMsgRecv(CCNode* node, SocketResponse* response);
    //从服务器收到消息的回调函数
    void onHttpMsgRecv(CCNode* node, CCHttpResponse* response);
    
    //登陆协议
    void sendaccount_login();
    void recvaccount_login(MB_MsgBuffer* recvPacket);
    void sendversion();
    void goUpdate(CCObject *);
    void canCelUpdate();
    //发送服务器我这次登陆的服务器记录
    bool http_sendserver_info(int serverID);

    void onBackClicked(CCObject* pSender);
private:
    CCSize m_cellSize;
    CCNode* m_pTableContainer;
    std::string     m_sAccid;
    bool  m_nIsGoUpdate;
    bool  isLoadingOver;
};

class MB_SceneServerListLoader:public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MB_SceneServerListLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MB_SceneServerList);
};

#endif /* defined(__ProjectMB__MB_SceneServerList__) */
