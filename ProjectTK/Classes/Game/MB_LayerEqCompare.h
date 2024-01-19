

#ifndef __ProjectMB__MB_LayerEqCompare__
#define __ProjectMB__MB_LayerEqCompare__

#include "Game.h"
class MB_LayerEqCompare:public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver
,public cocos2d::extension::CCScrollViewDelegate{
    
private:
    
    CCNode *m_pScoller;
    CCScrollView * m_pTableView;
    int m_nLength;
    int m_nIndex ;
    CCNode *m_pNodeScroller;
    CCScrollView *m_pCmdScroll;
    int m_nCMDLength;
    float m_nCmdWidth;
    TeamDataStruct *m_pTeamData;
    CCArray *m_pLiArray;
    CCLabelTTF * m_pText_tile;
    CCLabelTTF * m_pText_tile1;
            CCNode *m_pZdlSpr;
    CCLabelTTF *m_pDestinyName[DESTINY_MAX];
    CCNode *m_pitem[EQUIP_MAX];
    CCLabelTTF *m_pitemname[EQUIP_MAX];
    
    CCLabelTTF * m_pAidAddAtk;
    CCLabelTTF * m_pAidAddHp;
    
    CCLabelBMFont *m_pLevel;
    CCLabelBMFont *m_pFightPower;
    CCLabelTTF *m_pAttack;
    CCLabelTTF *m_pLife;
    CCLabelTTF *m_pPetName;
        CCNode* m_pNodeStar;
    CCNode*   m_pStar[7];
    CCArray *m_pArray;
    int64_t m_nPetID;
    uint16_t m_nAtkadd;
    uint16_t m_nHpadd;
public :
    
    MB_LayerEqCompare();
    ~MB_LayerEqCompare();
    virtual bool init(TeamDataStruct **teamData,CCArray *liArray,int index,const char * rolename,uint16_t atkadd,uint16_t hpadd);
    static  MB_LayerEqCompare * create(TeamDataStruct **teamData,CCArray *liArray,int index,const char * rolename,uint16_t atkadd,uint16_t hpadd);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) ;
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);
    void whenMoveOver(CCNode *node);
    void onBackClicked(CCObject *);
    void moveToIndex(uint8_t index);
    void changeSelect(int reIndxe,int nowindex);
    void onResetShow();
    bool IsUnLockDestiny(MB_DestinyData *data,TeamDataStruct* tdata);
    bool IsFindInTeam(int petType);
    bool IsFindInItem(int ItemType,TeamDataStruct* tdata);
   // bool isActiveDestinyInLiteam(uint16_t type);
    void setItemShow(MB_ItemData* data, int index);
private:
    bool m_bCommandShow;
};


#endif /* defined(__ProjectMB__MB_LayerEqCompare__) */
