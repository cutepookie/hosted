
#ifndef __ProjectMB__MB_ItemCard__
#define __ProjectMB__MB_ItemCard__
#include "MB_ResWindow.h"
#include "MB_Macro.h"

class MB_ItemCard:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
             MB_ItemCard();
    virtual ~MB_ItemCard();
    
    static MB_ItemCard* create(uint64_t itemUID = 0,bool bCircleFrame = false);
    
    virtual bool init(uint64_t itemUID,bool bCircleFrame = false);
    
    CC_PROPERTY(uint16_t, m_itemID  , ItemID);
    CC_PROPERTY(uint64_t, m_itemUID , ItemUID);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

protected:
    
    virtual void onResetWnd(void);

    void animateComplete(void);
    
private:
    CCNode*    m_pIcon;
    CCSprite*    m_pTypeIcon;
    CCNode *     m_pScroll;
    CCSprite *   m_pOverTime;
    bool m_bCircleFrame;
};

#endif /* defined(__ProjectMB__MB_ItemCard__) */
