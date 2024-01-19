
#ifndef __ProjectMB__MB_NodeTanChuangUnit__
#define __ProjectMB__MB_NodeTanChuangUnit__

#include "Game.h"
class MB_NodeTanChuangUnit: public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
    
public:
    
    MB_NodeTanChuangUnit();
    ~MB_NodeTanChuangUnit();
    static  MB_NodeTanChuangUnit* create(uint16_t type,uint16_t rank,uint16_t level,bool isItem);
  	virtual bool init(uint16_t type,uint16_t rank,uint16_t level,bool isItem);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void onClickDetail(CCObject* pSender);
private:
    CCLabelBMFont *m_pQiangHua;
    CCLabelBMFont *m_pLevel;
    CCLabelTTF *m_pName;
    CCControlButton* m_pDetailBtn;
    CCSprite* m_pSprite_face;
    CCSprite* m_pBg;
    CCSprite *m_pStar[MAX_GER_STAR];
    bool m_bIsItem;
};

#endif /* defined(__ProjectMB__MB_NodeTanChuangUnit__) */
