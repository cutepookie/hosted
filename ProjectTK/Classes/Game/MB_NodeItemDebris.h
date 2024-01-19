

#ifndef __MB__MB_NodeItemDebris__
#define __MB__MB_NodeItemDebris__


#include "Game.h"

class MB_NodeItemDebris:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_NodeItemDebris();
    virtual ~MB_NodeItemDebris();
    static MB_NodeItemDebris* create(uint64_t uid);
    virtual bool init(uint64_t uid);
    virtual void onResetWnd(void);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    static const  CCSize & getSize();
public:
    
    
protected:
    void onComposeClicked(CCObject* pSender);
    void onDetailClicked(CCObject* pSender);
private:
    CCSprite*     m_pSpriteIcon;
    CCSprite*     m_pSpriteFrame;
    CCSprite* m_pStar[7];
    CCNode*   m_pNodeSize;
    CCLabelTTF* m_pTTFName;
    CCLabelTTF* m_pTTFDescription;
    CCNode*     m_pNodeCompose;
    CCLabelTTF* m_pTTFCount;
protected:
    uint64_t m_uPetUid;
    uint16_t m_uPetTid;
};
#endif