

#ifndef __ProjectMB__MB_SceneRoleCreate__
#define __ProjectMB__MB_SceneRoleCreate__

#include "Game.h"
#include "MB_LayerHomeFlipDelegate.h"
USING_NS_CC;
USING_NS_CC_EXT;
class MB_LayerAnimation;
class MB_SceneRoleCreate : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
,public CCEditBoxDelegate
,public MB_FlipDelegate
{
public:
    MB_SceneRoleCreate();
    ~MB_SceneRoleCreate();
    
    CREATE_FUNC(MB_SceneRoleCreate)
	virtual bool init();
	static cocos2d::CCScene* scene();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
    void initRoleEditBox(CCEditBox* editBox);
    void initKeyEditBox(CCEditBox* editBox);
    void sendaccount_create();
    void recvaccount_create(MB_MsgBuffer* recvPacket);
    void sendrolename_check(const char* pName);
    void recvrolename_check(MB_MsgBuffer* recvPacket);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    void onMaleClicked(CCObject* pSender);
    void onFemaleClicked(CCObject* pSender);
    void onRandomClicked(CCObject* pSender);
    void onNextStepClicked(CCObject* pSender);
    void randomName();
    void onMonsterSeleted(uint16_t tid);
    bool sendrole_select_pet();
    bool recvrole_select_pet(MB_MsgBuffer *recvPacket);
    bool checkUserName(const char* pName);
    virtual void onFlipLeft();
    virtual void onFlipRight();
protected:
    void onAnimationCallBack(CCNode* pNode);
private:
    uint8_t m_iSex;
    CCMenuItemImage*    m_pButtonMale;
    CCMenuItemImage*    m_pButtonFemale;
    MB_LayerAnimation*  m_pAnimation;
    uint8_t             m_iActionMark;
    CCEditBox*          m_pRoleName;
    
    std::vector<std::string> m_vecMaleFirstName;
    std::vector<std::string> m_vecFemaleFirstName;
    std::vector<std::string> m_vecMaleName;
    std::vector<std::string> m_vecFemaleName;
    CCPoint         m_TouchBegin;
    bool initNameTemplete();
    CCRect          m_TouchRect;
    uint16_t        m_nSelectPet;
};

#endif /* defined(__ProjectMB__MB_SceneRoleCreate__) */
