//
//  MB_LayerComposePlatform.h
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-18.
//
//

#ifndef __ProjectMB__MB_LayerComposePlatform__
#define __ProjectMB__MB_LayerComposePlatform__

#include "Game.h"
#include "MB_NodeSelect.h"

struct ComposeUint
{
    ComposeUint()
    {
        m_pItemFrame = NULL;
        m_pItemIcon = NULL;
        m_pAddBtn = NULL;
        m_pBtn = NULL;
        m_ItemUID = 0;
        m_TypeID = 0;
    }
    ~ComposeUint()
    {
        releaseAll();
    }
    void releaseAll()
    {
        CC_SAFE_RELEASE_NULL(m_pItemFrame);
        CC_SAFE_RELEASE_NULL(m_pItemIcon);
        CC_SAFE_RELEASE_NULL(m_pAddBtn);
        CC_SAFE_RELEASE_NULL(m_pBtn);
    }
    void clear();
    void setUID(uint64_t uid);
    bool getIsInput(){return m_ItemUID != 0;}
    void setTID(uint16_t tid);
    void setType(uint16_t type){m_Type = type;}
    uint64_t getUID()const{return m_ItemUID;}
    uint16_t getTypeID(){return m_TypeID;}
    int getItemRank();
    CCSprite*   m_pItemIcon;
    CCSprite*   m_pItemFrame;
    CCControlButton*   m_pAddBtn;
    CCControlButton*   m_pBtn;
    void reset();

    void setActivated(bool bActivate);
private:
    uint16_t    m_TypeID;
    uint64_t    m_ItemUID;
    uint16_t    m_Type; // 1:pet,2:item
    CCSpriteFrame* m_pDefaultIconFrame;
};

enum PlatformType
{
    kPlatform2IN1 = 0,
    kPlatform3IN1 = 1,
    kPlatform4IN1 = 2,
    kPlatform5IN1 = 3,
    kPlatform5IN1Random = 4,
    kPlatformCount,
};

struct RewardData
{
    RewardData(){ReSet();};
    void ReSet()
    {
        type = 0;
        typeID = 0;
        num = 0;
        rank = 0;
    };
    uint8_t type;
    uint16_t typeID;
    uint32_t num;
    uint8_t rank;
};

struct OldData
{
    std::vector<uint64_t> oldUID;
    int star;
    OldData()
    {
        clean();
    }
    void clean()
    {
        oldUID.clear();
        star = -1;
    };
};
class MB_ComposeTemplate;

class MB_LayerComposePlatform:public MB_ResWindow,
public CCBMemberVariableAssigner,
public CCBSelectorResolver,
public MB_NodeSelectDelegate
{
public:
    MB_LayerComposePlatform();

    virtual ~MB_LayerComposePlatform();

    virtual bool init(uint16_t nComposeID,int nType);

    virtual void onResetWnd();
    
    void reloadComposeUnit(CCNode* pParent);

    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);

    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);

    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);

    static MB_LayerComposePlatform* create(uint16_t nComposeID,int nType);

    bool getIsInputComplate();

    int calcTargetComposedRank();

    // if nothing inputed,return -1,other wise,retuan star value
    int getInputItemStar();

    virtual void onNodeSelected(uint64_t nUid,uint16_t nType);

    void onMsgRecv(CCNode* node, SocketResponse* response);

    void destroyUnit();
    
    void cleanAll();
    
    void onCallbackAnimation();
    
    void onExit();
protected:
    void recvcombine_fail(MB_MsgBuffer* pbuff);

    virtual void recvcombine_pet(MB_MsgBuffer* pbuff);

    virtual void recvcombine_equip(MB_MsgBuffer* pbuff);

protected:
    void onAutoInputClicked(CCObject*);

    void onComposeClicked(CCObject*);

    virtual void onCloseClicked(CCObject*);

    void onSelectItemClicked(CCObject*);
    
    void onRuleClicked(CCObject*);

    void goSelectItem(int clickedIndex);

    virtual void goSelectItemRandom(int clickIndex);

    virtual void resetNormal();

    virtual void resetRandom();

    int getRandomInputComplate();

    int getInputedCount();

    int getNeedCount();
    
    int getOneStarForRandom();

    void removeInputedUidFromContainer(std::vector<uint64_t>& vContainer);

    bool autoPick4RandomSelected(std::vector<uint64_t>& vContainer,int nStar);

    bool filterUidByStar(std::vector<uint64_t>& vContainer,uint16_t star);

    void onAniComplete(CCObject*);
    void getLastData(std::vector<uint64_t>& vContainer,std::vector<uint64_t>& vClear);
protected:
    CC_SYNTHESIZE_READONLY(uint32_t, m_PlatformType, PlatformType);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nComposeID, ComposeID);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nSelected, Selected);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nType, Type);
    int                     m_nCurrentStar;
    CCLabelBMFont*             m_pTargetItemCost;
    ComposeUint             m_PlatformUint[5];
    MB_ComposeTemplate*     m_pComposeTemplate;
    CCNode*                 m_pTouchRectNode;
    CCNode*                 m_pUnitRoot;
    CCBAnimationManager*    m_pCCBAnimationMgr;
    int m_nstartStar;
    CCArray*                m_pRewardData;
    bool m_bInAnimation;
    OldData                 m_OldData;
    
    int16_t m_nCurItemType[5];
};
#endif /* defined(__ProjectMB__MB_LayerComposePlatform__) */
