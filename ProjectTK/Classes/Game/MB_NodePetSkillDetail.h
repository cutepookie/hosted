
#ifndef __ProjectMB__MB_NodePetSkillDetail__
#define __ProjectMB__MB_NodePetSkillDetail__

#include "Game.h"
class MB_NodePetSkillDetail:
public CCNode
,public CCBMemberVariableAssigner
,public CCBSelectorResolver{
    
    private:
    
        CCNode * m_pNodeSize;
        CCLabelTTF * m_pSkillname;
        CCLabelTTF * m_pSkilldes;
        CCLabelTTF * m_pSkillactivity;
    
    public :
    
         MB_NodePetSkillDetail();
        ~MB_NodePetSkillDetail();
        static MB_NodePetSkillDetail *create(uint8_t index, int skillid,uint8_t rank);
        bool init(uint8_t index,int skillid,uint8_t rank);
        CCSize getUnitSize();
        virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
        virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
        virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
};

#endif /* defined(__ProjectMB__MB_NodePetSkillDetail__) */
