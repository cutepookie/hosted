//
//  MB_MailSubItem
//  ProjectTK
//
//  Created by lic
//
//

#ifndef __MB__MB_MailSubItem__
#define __MB__MB_MailSubItem__
#include "MB_ResWindow.h"
#include "Game.h"
#include "RichText.h"

class MB_MailSubItem:public MB_ResWindow ,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
    
    
public:
    MB_MailSubItem();
    virtual ~MB_MailSubItem();
    
    CREATE_FUNC(MB_MailSubItem);
public:
    virtual bool                 onAssignCCBMemberVariable      (CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
    virtual SEL_MenuHandler      onResolveCCBCCMenuItemSelector (CCObject * pTarget,const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){return NULL;}
    CC_SYNTHESIZE(uint64_t, m_mailUid, MailUid)
    
public:
    virtual void onInitDidFinish (void);
    CCSize getUiDesignSize();
    bool init();
protected:
    void OnClickReplay  (CCObject* pSender);
protected:
    virtual void onResetWnd     (void);
    void onSetRbfText   (std::string str);
private:
    CCNode*           m_pAgree;
    CCNode*           m_pDelete;
    CCNode*           m_pRefuse;
    CCNode*           m_pReply;
    CCNode*           m_pTake;
    CCNode*           m_pReplay;
    CCLabelTTF*       m_pTime;
    CCMenu*           m_pmenu;
    CCNode*           m_pSizeNode;
    CCSize            m_uiDesignSize;
    CCLabelTTF*       m_pLabelTitle;
    CCLabelTTF*       Description;
    CCSprite*         m_pResultSpr_victory;
    CCSprite*         m_pResultSpr_lose;
    CCMenu*           m_pMenu;
};
#endif
