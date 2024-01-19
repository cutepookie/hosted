
#ifndef __ProjectMB__MB_LayerRoleInfoHeader__
#define __ProjectMB__MB_LayerRoleInfoHeader__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class MB_LayerRoleInfoHeader : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
,public CCNodeLoaderListener
{
    
private:
    
    CCMenu *m_pMenu;
    CCSprite *m_pSpriteEnergy;
    CCSprite *m_pSpriteExp;
    CCProgressTimer* m_pExpTimer;
    CCLabelBMFont *m_pRoleEnergy;
    CCLabelBMFont *m_pRoleEnergy2;
    CCLabelBMFont *m_pRoleExp;
    CCLabelBMFont *m_pRoleLevel;
    CCLabelTTF *m_pRoleName;
    CCLabelBMFont * m_pRoleGold;
    CCLabelBMFont * m_pRoleCoin;
    CCLabelBMFont * m_pRoleReputatiton;
    CCNode* m_pNodeSize;

public:
    MB_LayerRoleInfoHeader();
    ~MB_LayerRoleInfoHeader();
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MB_LayerRoleInfoHeader, create);

	virtual bool init();
     virtual void onEnterTransitionDidFinish();
    static void setMenuEnable(bool b,const char* key);
    static bool showRoleInfoHeader(bool b = true);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    bool recvrole_update_energy(MB_MsgBuffer *recvPacket);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    void onBuyEnergeClick(CCObject *);
    void onChargeClick(CCObject *);
    CCNode* m_pLVNameExp;
private:
    void updataExp();
};

class MB_LayerRoleInfoHeaderLoader:public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MB_LayerRoleInfoHeaderLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MB_LayerRoleInfoHeader);
};

#endif /* defined(__ProjectMB__MB_LayerRoleInfoHeader__) */
