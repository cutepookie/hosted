
#ifndef __ProjectMB__MB_LayerChatMain__
#define __ProjectMB__MB_LayerChatMain__

#include "Game.h"
class MB_LayerChatMain :public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
    private:
        CCNode *m_pNode;
        CCSprite *m_pSprite;
        CCSize m_pSize;
        bool isMove;
        CCBAnimationManager *m_pAnimation;
        uint16_t m_nNewmessage;
    public :
        MB_LayerChatMain();
        ~MB_LayerChatMain();
        virtual bool init();
        virtual void onResetWnd();
        static  MB_LayerChatMain * create();
        virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
//        virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
        virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
        virtual void registerWithTouchDispatcher(void);
        virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
        virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
        virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
        void onChatClick(CCObject *);
        void onRecieveMessage();
        void onNoMessage();
        virtual void onExit();
        void onMsgRecv(CCNode* node, SocketResponse* response);
    
    static void SetChatMainVisible(bool b,const char* key);
};

#endif /* defined(__ProjectMB__MB_LayerChatMain__) */
