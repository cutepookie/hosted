
#ifndef __ProjectMB__MB_NodePetUnit__
#define __ProjectMB__MB_NodePetUnit__

#include "Game.h"

class MB_NodePet;

class MB_NodePetUnit:public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver {
    
    private:
    
        uint64_t m_nPetId;
        CCLabelTTF *m_pLabel_name;
        CCScale9Sprite *m_pSprite_back;
        CCNode *m_pNode_icon;
        CCLabelTTF *m_pText_hp;
        //CCLabelTTF *m_pMoneyLabel;
        CCSprite *m_pSprite_country;
        CCSprite *m_pSprite_inbattle;
        CCSprite *m_pStar[MAX_GER_STAR];
        CCSprite *m_pOnSoldSelect,*m_pOnSoldSelect2;
        CCNode *m_pNodeGuard;
        CCLabelTTF* m_pTTFGuard;
        MB_NodePet* m_pNodeer;
        CCNode* m_pNodeSize;
        CCNode* m_pNodeNomal;
        CCNode* m_pNodeChange;
        CCNode* m_pNodeSale;
        CCNode* m_pNodeChoose;
        CCNode* m_pNodeChooseNone;
        int m_pUnitType;
        bool m_pHeadCanClick;
        bool m_bIsSelect;
       bool m_bShowTutoral;
    public :
    
        MB_NodePetUnit();
        ~MB_NodePetUnit();    
        virtual bool init( uint64_t petId, bool isSelected);
        virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
        virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
        virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
        int64_t  getData();
        bool isCanClick();
        bool changeSel();
        void onPetClick();
        void onChangeClick();
        void onSoldClick();
        void onEnhanceClick();
        void onUpdateClick();
        void onChooseNoneClick();
        void onChooseClick();
        CCSize getCellSize();
        bool setIsHeadCanClick(bool iscanClick);
    static MB_NodePetUnit * create(uint64_t petId,bool isSelected,bool showTurtorial = false);
        void setUnitType(int UnitType);
        void onNodeCallBack();
    
 
};


#endif /* defined(__ProjectMB__MB_NodePetUnit__) */
