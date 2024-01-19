
#ifndef __ProjectMB__MB_LayerItemUnionUnit__
#define __ProjectMB__MB_LayerItemUnionUnit__

#include "Game.h"
class MB_LayerItemUnionUnit :public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver {
    
    private:
    
        CCNode *m_pNodeSize;
        CCLabelTTF *m_pItemName;
        CCLabelTTF *m_pNum;
        CCSprite *m_pStar[MAX_ITEM_STAR];
        CCNode *m_pNodeIcon;
        CCNode *m_pNodeEnough;
        CCLabelTTF* m_pPieceNeed;
        MB_ItemData *m_pData;
    
    public :
    
    MB_LayerItemUnionUnit();
    ~MB_LayerItemUnionUnit();
    virtual bool init();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    static MB_LayerItemUnionUnit* create();
    void onCheckClick(CCObject *);
    void onSoldClick(CCObject *);
    void setData(MB_ItemData * data);
    virtual void onResetWnd(void);
};


#endif /* defined(__ProjectMB__MB_LayerItemUnionUnit__) */
