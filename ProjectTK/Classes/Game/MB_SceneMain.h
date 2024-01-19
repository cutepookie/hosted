

#ifndef __ProjectMB__MB_SceneMain__
#define __ProjectMB__MB_SceneMain__

#include "Game.h"
class MB_LayerMainCommand;
class MB_LayerPetMgr;
class MB_LayerRoleDetail;
class MB_LayerPVP;
class MB_ExplorerData ;
class MB_LayerMap;
class MB_LayerPveCommand;
class MB_LayerPvpCommand;
class MB_LayerRoleInfoHeader;
class MB_LayerWarningHeader;
class MB_FunctionPveMain;
class MB_FunctionPvpMain;
class MB_SceneMain:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
        
public:
    
    MB_SceneMain();
    ~MB_SceneMain();
    
    virtual bool init(CCScene *scene);
    
    /** create one layer */
    static MB_SceneMain *create(CCScene *scene);
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

    virtual void onEnter();
    virtual void onExit();
//    void update(float);
    bool onEnterLayerRoleInfoHeader();
    bool onExitLayerRoleInfoHeader();
    MB_LayerRoleInfoHeader* getLayerRoleInfoHeader();
    
    bool onEnterLayerWarningHeader();
    bool onExitLayerWarningHeader();
    MB_ResWindow* getRoleInfoWindow(){return m_pLayerRoleInfoHeader;}
    MB_LayerWarningHeader* getLayerWarningHeader();
    
    bool onEnterLayerMap();
    bool onExitLayerMap();
    //MB_LayerMap *getLayerMap();
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    void onMainClicked(CCObject* pSender);
    void onPVPClicked(CCObject* pSender);
    void onPVEClicked(CCObject* pSender);
    void onRoleClicked(CCObject* pSender);
    void onShopClicked(CCObject* pSender);
    void onOtherClicked(CCObject* pSender);
    void changeMainLayer(CCObject* pSender);
    
    void animaitionOver();

    void updateButton();
    void enterLayer(int mainLayer, int subLayer);
    void onCloseCommander();
    void tickOfRecovery(float dt);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual void replaceSubLayer(MB_ResWindow* pWnd);
    virtual void replaceMainLayer(MB_ResWindow* pWnd);
    
    void updateLayerStatus(int mainLayer, int subLayer);
    void goLayerHome();
    MB_ResWindow* getFunctionWindow();
    
    MB_LayerRoleInfoHeader* m_pLayerRoleInfoHeader;
private:
    
    CC_SYNTHESIZE(int, m_nSubLayerStatus, SubLayerStatus);
    CC_SYNTHESIZE(int, m_kMainLayerStatus, MainLayerStatus);

    MB_LayerWarningHeader* m_pLayerWarningHeader;
    //MB_LayerPveCommand  *m_pPveCommand;
    MB_FunctionPveMain* m_pPveCommand;
    //MB_LayerPvpCommand  *m_pPvpCommand;
    MB_FunctionPvpMain*   m_pPvpCommand;
    MB_ResWindow * m_pLayerHome;
    MB_ResWindow*  m_pCurrentFunctionWindow;
    MB_ResWindow* m_pNextMainLayer;
    int             m_nHomeLayerType;
    bool            m_bChangeMainLayer;
};

#endif /* defined(__ProjectMB__MB_SceneMain__) */
