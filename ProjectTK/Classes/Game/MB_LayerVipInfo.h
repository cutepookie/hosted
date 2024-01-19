//
//  MB_LayerVipInfo.h
//  ProjectTK
//
//

#ifndef __ProjectMB__MB_LayerVipInfo__
#define __ProjectMB__MB_LayerVipInfo__

#include "Game.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MB_LayerVipInfo : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
    
public:
    MB_LayerVipInfo(bool dealwithheadinfomenu);
    ~MB_LayerVipInfo();
    
    static MB_LayerVipInfo* create(CCObject* p);
    
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    void onCloseClicked(CCObject* sender);
    void loadDetail();
    bool detailExist(int index);
    virtual void onResetWnd();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

private:
    void onTurnleftClicked(CCObject* pSender);
    void onTurnRightClicked(CCObject* pSender);
    CCNode* createVipUnit(int index);
    CCNode* m_pBtnLeft;
    CCNode* m_pBtnRight;
    CCLabelBMFont* m_pVipLevel;
private:
    CCNode* m_pVipContainer;
    CCNode* m_pCellSize;
    char* m_strVipLevel;
    int m_nCurrentPage;
    std::vector<std::string> m_VipContent;
    
    bool m_bDealWithHeadInfoMenu;
    
    CCPoint m_pPoint;
};

#endif /* defined(__ProjectMB__MB_LayerVipInfo__) */
