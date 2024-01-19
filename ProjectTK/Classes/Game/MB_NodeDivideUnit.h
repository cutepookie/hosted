

#ifndef __ProjectMB__MB_NodeDivideUnit__
#define __ProjectMB__MB_NodeDivideUnit__

#include "Game.h"
class MB_NodeDivideUnit:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver {
        
        private:
    
            CCLayer *m_pLayerParent;
    
        public :
        
        MB_NodeDivideUnit();
        ~MB_NodeDivideUnit();
        virtual bool init(CCLayer * layer);
        static MB_NodeDivideUnit * create(CCLayer * layer);
        virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
        virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
        virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
        void onDivideClick(CCObject *);
};
#endif /* defined(__ProjectMB__MB_NodeDivideUnit__) */
