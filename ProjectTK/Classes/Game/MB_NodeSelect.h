//
//  MB_NodeSelect.h
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-19.
//
//

#ifndef __ProjectMB__MB_NodeSelect__
#define __ProjectMB__MB_NodeSelect__

#include "MB_ResWindow.h"
typedef void (CCObject::*SEL_CHOOSE)(uint64_t);
#define choose_selector(_SELECTOR) (SEL_SELECTOR)(&_SELECTOR)
struct AttrPair
{
    AttrPair()
    {
        m_pIcon = NULL;
        m_pValue = NULL;
    }
    ~AttrPair()
    {
        CC_SAFE_RELEASE_NULL(m_pIcon);
        CC_SAFE_RELEASE_NULL(m_pValue);
    }
    void show();
    void hide();
    CCSprite*   m_pIcon;
    CCLabelTTF* m_pValue;
};

class MB_NodeSelectDelegate
{
public:
    virtual void onNodeSelected(uint64_t nUid,uint16_t nType) = 0;
    virtual void onInputedNodeSelected(uint64_t nUid,uint16_t nType){};
};

enum SelectNodeType
{
    kSelectPet = 1,
    kSelectItem = 2,
    kSelectUnknow,
};
class MB_NodeSelect:public MB_ResWindow
{
public:
    MB_NodeSelect();
    virtual ~MB_NodeSelect();
    virtual uint64_t getSelectUID()const;
    static MB_NodeSelect* create(uint16_t nType,uint64_t nItem,bool showTutoril = false);
    const CCSize& getNodeSize()const;
    void onResetWnd();
    void setStar(int star);
    void setMenuVisable(bool bVisable);
    void setButtonVisable(bool bVisable);
    void setMenuVisableByTag(bool bVisable,int nTag);
    void setButtonVisableByTag(bool bVisable,int nTag);
    void setButtonEnableByTag(bool bEnable,int nTag);
    void setMenuText(const char* pText);
    static CCSize getUintSize(uint16_t nType);
    CCControlButton*    m_pBtn1;
protected:
    CC_SYNTHESIZE_READONLY(uint16_t, m_nType, Type);
    uint64_t    m_nItemUID;
    CCLabelTTF* m_pName;
    CCLabelTTF* m_pMenuText;
    CCNode*     m_pNodeIcon;
    CCNode*     m_pStars[7];
    CCSize      m_nSize;
    CCNode*     m_pNodeMenu;
    CCNode*     m_pNodeButton;
    CC_SYNTHESIZE(bool, m_bInputed, IsInputed);
};

#endif /* defined(__ProjectMB__MB_NodeSelect__) */
