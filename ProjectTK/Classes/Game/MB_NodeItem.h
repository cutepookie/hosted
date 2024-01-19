
#ifndef __ProjectMB__MB_NodeItem__
#define __ProjectMB__MB_NodeItem__

#include "Game.h"
class MB_ItemData;
class MB_NodeItem;
class MB_NodeItemDelegate
{
public:
    virtual void onClicked(MB_NodeItem* ) = 0;
};

typedef enum {
    kNINWNONE,
    kDAOJU,
    KRENWUXIANGQING,
    KXUANZEZHUANGBEI,
}NODEITEMNOWWINDOW;

class MB_NodeItem :public CCLayer,
public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
protected:
    CCSprite *m_pItem_card;
    
    CCLabelBMFont *m_pLabelLevel;
    CCLabelBMFont *m_pLabelNum;
    
    CCLabelTTF* m_pLabelName;
    CCNode* m_pNodeLevel;
    CCNode* m_pRootNodeNum;
    
    CC_SYNTHESIZE(MB_NodeItemDelegate*, m_pDelegate, Delegate);
    virtual void onClicked(CCObject*);
    CCNode* m_pNodeSelect;
    NODEITEMNOWWINDOW m_eNowWindow;
    CCNode* m_pSpriteDebris;
    CCMenu* m_pItemMenu;
    CCNode* m_pRootNodeLevel;
public :
    CC_SYNTHESIZE(uint64_t, m_nItemId, ItemId)
    CC_SYNTHESIZE(uint16_t, m_nItemType, ItemType)
    
    MB_NodeItem ();
    ~MB_NodeItem ();
    
    virtual bool init(uint64_t itemid = 0);
    virtual bool init(uint16_t itemType);
    virtual bool init(MB_ItemData *data);
    static MB_NodeItem * create(MB_ItemData *data,NODEITEMNOWWINDOW nowWindow = kDAOJU);
    static MB_NodeItem * create(uint16_t itemType,NODEITEMNOWWINDOW nowWindow = kDAOJU);
    static MB_NodeItem * create(uint64_t itemid,NODEITEMNOWWINDOW nowWindow = kDAOJU);
    static MB_NodeItem * create(const char *iamgeName,uint8_t star,NODEITEMNOWWINDOW nowWindow = kDAOJU);
    
    virtual bool init(const char *iamgeName,uint8_t star);
    void setNum(int num);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    const ccColor3B & getNodeColor();
    
    bool isSelected(){return m_pNodeSelect->isVisible(); }
    void setSelected(bool b);
    void setLevelNum(int level);
    void setOnClickEnable(bool b);
    void showNameCount(bool b);
    void showLevel(bool b);
    void showNameStar(bool b);
    void setIsEquiped();
    CCSprite *m_pStar[MAX_GER_STAR];
    CCNode* m_pNodeStar;
    CCNode* m_pEquipedStr;
    bool isTopZorder;
};


#endif /* defined(__ProjectMB__MB_NodeItem__) */
