

#ifndef ProjectMB_MB_ResWindow_h
#define ProjectMB_MB_ResWindow_h
#include "cocos2d.h"
#include "cocos-ext.h"
#include "../Common/SocketRequest.h"
#include "../Common/SocketResponse.h"

USING_NS_CC;
USING_NS_CC_EXT;


class MB_ResWindow:public CCLayer
{
public:
                 MB_ResWindow();
    virtual     ~MB_ResWindow();
    
    virtual void onEnter();
    virtual void dirty                       (void);
  
    virtual void replaceLayer                (MB_ResWindow* layer, bool ignoreParent = false);
    virtual void popWindow                    (bool isUpdate = false);
    virtual void pushWindow                   (MB_ResWindow* layer, bool hideParent = false);

    virtual void onResetWnd                  (void);
    virtual bool canResetWnd                 (void);
    virtual void onCheckTutorial             (void);

    virtual void tick(float dt);
    void setLogicParent(MB_ResWindow* layer);
    void setSubLayer(MB_ResWindow* layer);
    MB_ResWindow* getSubLayer();
    MB_ResWindow* getLogicParent();
    void releaseLogicParentAndSubLayer(MB_ResWindow* layer);
    void releaseSubLayerPtr(MB_ResWindow* layer);

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    CREATE_FUNC(MB_ResWindow);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    
    virtual void replaceSubLayer(MB_ResWindow* pWnd);
    virtual CCNode* loadResource(const char* pName);
    bool m_bTutorial;
protected:
    bool m_propertyDirty;
    bool m_bIgnoreParent;
    MB_ResWindow* m_pLayerParent;
    MB_ResWindow* m_pSubLayer;
    MB_ResWindow* m_pLayerParentDelete;
    CCArray* m_pTutorialNodeArray;
    uint16_t m_uTutorialTag;
    CC_SYNTHESIZE(bool, m_bShowRoleInfoPanel, ShowRoleInfoPanel);
    CC_SYNTHESIZE(bool, m_bShowHomeButton, ShowHomeButtonPanel);
    CC_SYNTHESIZE(bool, m_bShowEXP, ShowEXP);
};


#endif
