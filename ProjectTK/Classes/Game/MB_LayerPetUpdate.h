
#ifndef __ProjectMB__MB_LayerPetUpdate__
#define __ProjectMB__MB_LayerPetUpdate__

#include "Game.h"
#include "MB_LayerRoleInfoHeader.h"
#include "MB_RoleSoundSystem.h"
class MB_NodeUpdatePetList;
class MB_LayerPetUpdate :public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver
,public CCTableViewDataSource
{
    
private:
    
    CCLabelTTF *m_pPetName;

    CCLabelBMFont *m_pTextNextExp;
    CCLabelBMFont *m_pTextLevel1;
    CCLabelBMFont *m_pTextAttack1;
    CCLabelBMFont *m_pTextLife1;
    CCLabelBMFont *m_pTextLevel2;
    CCLabelBMFont *m_pTextAttack2;
    CCLabelBMFont *m_pTextLife2;
    CCLabelBMFont *m_pTextExp;
    CCSprite *m_pExpBar;
    CCNode *m_pPetNode[6];
    CCNode* m_pTableContainer;
    CCTableView* m_pTableView;
    CCNode *m_pCard;

    uint64_t m_nPetId;
    float m_nExternExp;
    bool isHomeButtonShow;
    CCControlButton * m_pUpdateBt;
    CCControlButton * m_pCollect;
    CCSprite* m_pStar[MAX_GER_STAR];
    int m_nNowLevel;
    uint64_t m_nNowExp;
    uint64_t m_nNextExp;
    uint64_t m_nSelectExp;
    CCProgressTimer *m_pExpTimer;
    CCArray* m_pArrayCanChoose;
    void deallocAndReload();
    CCMenuItemImage  *m_pItem;
    
    CCBAnimationManager* m_pCCBAnimationMgr;
public:
    CCArray *m_pSoldList;
    virtual void onEnter()
    {
        MB_ResWindow::onEnter();
        PlayRoleSound(kSoundEnterCardLevelUp);
    }
private:
    bool m_bRoleInfoHeaderShow;
    public :
    
    MB_LayerPetUpdate();
    ~MB_LayerPetUpdate();
    static MB_LayerPetUpdate* create(uint64_t petID);
    virtual bool init(uint64_t petID);
    virtual bool setPetUid(uint64_t petId);
    virtual void onResetWnd();
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    
    void onCloseClick(CCObject *);
    void onUpdateClick(CCObject *);
    void onAutoUpdateClick(CCObject *);
    void setAttribute(const char *buf,char *databuf, int attribute);
    void reloadData();
    bool addData(MB_ItemData *data);
    void removeData(MB_ItemData *data);
    void autoAdd();
    bool sendpet_eat();
    void onMsgRecv(CCNode* node, SocketResponse* response);
    void reloadShow();
    void readLoadPet(uint64_t petID);
    void changeLevel();
    void goItemShop(CCObject* pSender);
    bool isUpdateUI;
    bool m_bReady;
    CCSize m_szCell;
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
};


#endif /* defined(__ProjectMB__MB_LayerPetUpdate__) */
