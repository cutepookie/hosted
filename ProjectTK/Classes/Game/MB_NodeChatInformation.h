

#ifndef __ProjectMB__MB_NodeChatInformation__
#define __ProjectMB__MB_NodeChatInformation__
#include "Game.h"

#include "../Common/RichText.h"
class MB_ChatData;
class MB_NodeChatInformation:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
,public RichTextDelegate
{

private:
    CCNode *m_pNodeSize;
    CC_SYNTHESIZE(MB_ChatData*, m_nChatData, ChatData);

    CCLabelTTF* m_pRoleName;
    CCLabelTTF* m_pContent;
    CCSprite* m_pRoleIcon;
    
    RichText* m_pContentRichText;
    RichText* m_pRoleNameRichText;
    CCScale9Sprite* m_pContentSprite;
public :
    MB_NodeChatInformation();
    ~MB_NodeChatInformation();
    virtual bool init(MB_ChatData *chatData);
    static MB_NodeChatInformation * create(MB_ChatData *chatData);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    CCSize getNodeSize();
    void onClickRole(CCObject *);
    virtual void onClickedTextTTF(RichText * obj,int id,CCTouch *pTouch);
};


class MB_NodeChatTime:public MB_ResWindow
,public CCBMemberVariableAssigner
{
public:
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    CCSize getNodeSize();
    
    virtual bool init(time_t t);
    static MB_NodeChatTime * create(time_t t);
    MB_NodeChatTime();
    ~MB_NodeChatTime();
private:
    CCLabelTTF* m_pTime;
    CCNode* m_pNodeSize;
};
#endif /* defined(__ProjectMB__File__) */
