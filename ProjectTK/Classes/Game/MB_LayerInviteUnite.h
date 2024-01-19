
#ifndef __ProjectMB__MB_LayerInviteUnite__
#define __ProjectMB__MB_LayerInviteUnite__

#include "Game.h"
class  inviteData :public CCObject{

    private :
    
        std::string m_strRoleName;
    
    public :
    
        inviteData(){
        }
        virtual ~inviteData(){
        }
        CC_SYNTHESIZE(int, m_nRoleID, RoleID);
        CC_SYNTHESIZE(bool, m_nisMale, isMale);
        CC_SYNTHESIZE(uint8_t,m_nLevel, level);
        CC_SYNTHESIZE(uint8_t, m_nTitle, Title);
        const char * getRoleName(){ return m_strRoleName.c_str(); }
        void setRoleName(const char *rolename){
        
            m_strRoleName = rolename;
        }
        CC_SYNTHESIZE(bool, m_nIsPay, Ispay);

};
class MB_LayerInviteUnite:public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver {
    
    private:
    
        CCLabelTTF *m_pRoleName;
        CCLabelTTF *m_pLevel;
        CCLabelTTF *m_pNotFirstTime;
        CCLabelTTF *m_pHasFirstTime;
        CCSprite *m_pNodeIcon;
        CCNode *m_pNodeSize;
    
    public :
    
        MB_LayerInviteUnite();
        ~MB_LayerInviteUnite();
        virtual bool init();
        void setViteData(inviteData *data);
        static  MB_LayerInviteUnite* create();
        virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
        virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
        virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
        void onMailClick(CCObject *);
        CCSize getUnitSize();
};
#endif /* defined(__ProjectMB__MB_LayerInviteUnite__) */
