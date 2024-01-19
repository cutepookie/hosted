//
//  MB_NodeItemBook.h
//  ProjectPM
//
//  Create by WenYong on 4/5/2014.
//
//
#ifndef __ProjectMB__MB_NodeItemBook__
#define __ProjectMB__MB_NodeItemBook__

#include "MB_ResWindow.h"

/*
 #define COIN_ID 20007//21100//钱币图标
 #define FRESH_ID 20003//21111 //黑石货币图表
 #define COLLECT_ID 21108 //感恩书图标
 #define SPEED_ID 21109    //神速令图标
 #define GOLD_ID 20008//21101 //元宝
 #define REPUTATION_ID 20006//21102//徽章
 #define ROLE_EXP_ID 30005 //角色经验
 #define GER_EXP_ID 21104
 #define COMPOS_ITEM3_ID 21144
 #define COMPOS_ITEM4_ID 21145
 #define COMPOS_ITEM5_ID 21146
 #define COMPOS_GER3_ID 21141
 #define COMPOS_GER4_ID 21142
 #define COMPOS_GER5_ID 21143
 
 #define GER_SHOP_CHAPTER_ID 6666
 #define ITEM_SHOP_CHAPTER_ID 8888
 */
class MB_NodeItemBook : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
	MB_NodeItemBook();
	virtual ~MB_NodeItemBook();
	virtual void onResetWnd();
	virtual bool init(uint16_t nTypeId,uint32_t num=0,bool bCircle = false);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    static MB_NodeItemBook* create(uint16_t nTypeId,uint32_t num=0,bool bCircle = false);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){return NULL;}
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onIconClicked(CCObject* pSender);
    void enableClick(bool bEnable);
    void activateSuitEffective();
protected:
    void showPetDetail();
    void showItemDetail();
    CCSprite*    m_pItemFrame;
    CCSprite* m_pItemIcon;
    CCLabelTTF*	m_pItemName;
    uint16_t    m_nTypeId;
    uint32_t    m_nNum;
    bool m_bCircle;
    CCNode*     m_pNodeMenu;
    CCNode* m_pNode;
private:
    CCNode* m_pSpriteDebris;
};

class MB_NodePetBook : public MB_NodeItemBook
{
public:
    static MB_NodePetBook* create(uint16_t nTypeId,uint32_t num=0);
    virtual void onResetWnd();
    virtual void onIconClicked(CCObject* pSender);
};

class MB_NodePetView : public MB_NodeItemBook
{
public:
    MB_NodePetView();
    ~MB_NodePetView();
    static MB_NodePetView* create(uint16_t nTypeId,uint16_t nLevel,uint16_t nRank);
    void setData(uint16_t nTypeId,uint16_t nLevel,uint16_t nRank);
    virtual void onResetWnd();
    virtual void onIconClicked(CCObject* pSender)
    {
        showPetDetail();
    }
private:
    uint16_t	m_nPetRank;     //精灵品阶
    uint16_t	m_nPetLevel;   //精灵等级
    uint16_t	m_nPetTypeID;  //精灵模版ID
};


class MB_NodeRewardItem : public MB_NodeItemBook
{
public:
    MB_NodeRewardItem();
    ~MB_NodeRewardItem();
    static MB_NodeRewardItem* create(uint16_t nTypeId,uint32_t num=0,bool bCircle = false);
    virtual bool init(uint16_t nTypeId,uint32_t num=0,bool bCircle = false);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onResetWnd();
    
    CCSize getSize(){return m_pNodeSize->getContentSize();};
private:
    CCNode*     m_pNodeSize;
    CCNode* m_pSpriteDebris;
};

class MB_NodeRewardPet :public MB_NodeRewardItem
{
public:
    static MB_NodeRewardPet* create(uint16_t nTypeId,uint32_t num=0,bool bCircle = false);
    virtual void onResetWnd();
    virtual void onIconClicked(CCObject* pSender)
    {
        showPetDetail();
    }
};

struct sMailReward;
class MB_LayerRewardContainer : public  CCLayer
{
public:
    MB_LayerRewardContainer();
    virtual ~MB_LayerRewardContainer();
    virtual void setContentSize(const CCSize& contentSize);
    static MB_LayerRewardContainer* create(CCArray* valueArray);
	static MB_LayerRewardContainer* create(CCArray* valueArray,bool b);
    static MB_LayerRewardContainer* createWithMailReward(sMailReward* pMailReward);
    virtual bool init(CCArray* valueArray);
	bool init(CCArray* valueArray, bool b);
    virtual void setScale(float scale);
    void setPosLeft();
protected:
    void setPostionOffset(float offset);
protected:
    CCSize     m_ItemSize;
	bool isB;
};

class MB_LayerRewardContainerEx : public  CCLayer
{
public:
    static MB_LayerRewardContainerEx* create(CCArray* valueArray);
    virtual bool init(CCArray* valueArray);
    const CCSize& getItemSize(){return m_ItemSize;}
    void setCenter(CCSize contanerSize);
protected:
    CCSize     m_ItemSize;
};
class MB_LayerRewardContainerMaoXian : public  CCLayer
{
public:
    static MB_LayerRewardContainerMaoXian* create(CCArray* valueArray);
    virtual bool init(CCArray* valueArray);
    const CCSize& getItemSize(){return m_ItemSize;}
protected:
    CCSize     m_ItemSize;
};

#endif /* defined(__ProjectMB__MB_NodeItemBook__) */
