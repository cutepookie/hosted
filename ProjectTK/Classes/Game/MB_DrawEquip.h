
#ifndef __ProjectMB__MB_DrawEquip__
#define __ProjectMB__MB_DrawEquip__
#include "MB_ResWindow.h"
#include "MB_ServerData.h"
#include "MB_LocalProto.h"
class MB_DrawCardData;
class MB_DrawEquip:public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    MB_DrawEquip();
    virtual ~MB_DrawEquip();
    static MB_DrawEquip* create(MB_DrawCardData* data);
    virtual bool init(MB_DrawCardData* data);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    
    void FlipFont(bool force = false);
    void FlipBack(bool force = false);
    void FlipBackFont();
    virtual void onResetWnd(void);
    bool getisDraw();
protected:
    void FlipFontCallBack();
    void onClicked(CCObject*);
private:
    CCSprite* m_pSpriteIcon;
    CCNode* m_pNodeDrawed;
    CCLabelTTF * m_pNameCount;
    CCBAnimationManager *m_pAnimation;
    CC_SYNTHESIZE_READONLY(MB_DrawCardData* ,m_pMB_DrawCardData,DrawCardData);
    void setDrawCardData(MB_DrawCardData*);
    CC_SYNTHESIZE_READONLY(bool, m_bFont, Font);
    CCNode* m_pStar[MAX_GER_STAR];
};

#endif /* defined(__ProjectMB__MB_DrawEquip__) */
