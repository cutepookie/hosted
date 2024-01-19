
#ifndef __ProjectMB__MB_LayerTutorialDialog__
#define __ProjectMB__MB_LayerTutorialDialog__

#include "Game.h"
#include "MB_RoleSoundSystem.h"
#include "SimpleAudioEngine.h"
class MB_LayerTutorialDialog: public MB_ResWindow
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
{
    
private:
    
    CCNode* m_pLeft;
    CCNode* m_pRight;
    CCLabelTTF* m_pLabelText;

    int m_nDialogPos;
    int m_nDialogLength;
    int m_nDialogUnicodePos;
    int m_nDialogUnicodeLength;
    char* m_pDialog;
    unsigned short* m_pDialogUnicode;
    CCObject *m_pTarget;
    SEL_CallFunc m_pCallBack;
    CCMenu* m_pmenu;
public:
    
    MB_LayerTutorialDialog();
    ~MB_LayerTutorialDialog();
    
    static MB_LayerTutorialDialog * create();
    static MB_LayerTutorialDialog * create(const char* dialog, bool isLeft);
    
    virtual bool init();
    virtual bool init(const char* dialog, bool isLeft);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName) ;
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName) ;
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode) ;
    
    void tickShowText(float dt);
    void setCallBack(CCObject *target,SEL_CallFunc backFunc);
    void onCloseClicked(CCObject* pSender);
    
    virtual void onExit()
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
        MB_ResWindow::onExit();
    }
    virtual void onEnterTransitionDidFinish()
    {
        MB_ResWindow::onEnterTransitionDidFinish();
        if(m_pTutorialTemplete->getSoundID() != -1)
        {
            MB_RoleSoundSystem::getInstance()->stopLastSound();
            const char* pPath = MB_RoleSoundSystem::getInstance()->getFilePathByKey(m_pTutorialTemplete->getSoundID());
            m_nSoundID = MB_Audio::getInstance()->playEffect(pPath);
        }
    }
    virtual void tick(float dt);
private:
    int m_nSoundID;
    void OnAnimationOver();
    bool m_bAnimationOver;
    bool m_bClicked;
    MB_TutorialTemplete* m_pTutorialTemplete;
};

#endif /* defined(__ProjectMB__MB_LayerTutorialDialog__) */
