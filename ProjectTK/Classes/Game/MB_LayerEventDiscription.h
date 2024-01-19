
#ifndef __ProjectMB__MB_LayerEventDiscription__
#define __ProjectMB__MB_LayerEventDiscription__

#include "Game.h"
class MB_LayerEventDiscription:public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver {
    
protected:
    
    CCLabelTTF * m_pTimeCount;
    CCLabelTTF *m_pDiscription;
    CCLabelTTF *m_pDetail;
    int m_nCloseTime;
    int m_nActivyId;
    
    public :
    
    MB_LayerEventDiscription();
    ~MB_LayerEventDiscription();
    virtual bool init();
    static  MB_LayerEventDiscription * create();
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void tickTime(float dt);
    void setClostTime(int m_nCloseTime);
    void setDiscription(const char * discription);
    void setActivyID(int activyid);
    void setNomCount(int type, int count);
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
};

#endif /* defined(__ProjectMB__MB_LayerEventDiscription__) */
