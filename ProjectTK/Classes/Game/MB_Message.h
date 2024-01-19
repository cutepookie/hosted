

#ifndef __ProjectMB__MB_MessageBox___
#define __ProjectMB__MB_MessageBox___

#include "cocos2d.h"
#include "cocos-ext.h"
//#include "CCLabelFX.h"
#include "MB_ResWindow.h"
USING_NS_CC;
USING_NS_CC_EXT;
#define MESSAGE_TAG 654321
#define ZUZHIMESSAGE_TAG 654320
#define MESSAGE_LITE_TAG 654322
#define TOUCHPROPERTY -128
// 消息控制单例类
//
class MB_MessageEditDeleate{
    
    public :
    
    virtual ~MB_MessageEditDeleate(){ }
    virtual void setString(const char *codeback) = 0;
    
};
// 消息显示类
//

class MB_MessageBox2: public MB_ResWindow, public cocos2d::extension::CCBSelectorResolver

, public cocos2d::extension::CCBMemberVariableAssigner{
    
        CCLabelTTF *m_text_message;
        CCControlButton *m_onOk;
        CCControlButton *m_onOk2;
        CCControlButton * m_onCancel;    
        CCObject *target;        //按钮回调消息处理
        SEL_MenuHandler buttonOneCall; //回调函数
        SEL_MenuHandler buttonTwoCall; //回调函数
        bool buttonIsGo[3];
        CCBAnimationManager *m_pAniamtion;
        bool m_nGoDistroy;
    
    public :
    
        MB_MessageBox2();
        ~MB_MessageBox2();
        virtual bool init();    
        void set(const char * title, const char *message,const char *buttonone,const char *buttontwo, CCObject *target ,SEL_MenuHandler buttonOneCall,SEL_MenuHandler buttonTwoCall);
        virtual void registerWithTouchDispatcher();
        virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
        virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
        virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
        CREATE_FUNC(MB_MessageBox2);
        void onConfirmClicked(CCObject *);
        void onConfirmClicked2(CCObject *);
        void onBackClicked(CCObject *);
        virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
        virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
        virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};

class MB_MessageBox3: public CCLayer, public cocos2d::extension::CCBSelectorResolver

, public cocos2d::extension::CCBMemberVariableAssigner{
        
    CCBAnimationManager *m_pAniamtion;
   
    public :
    MB_MessageBox3();
    ~MB_MessageBox3();
    virtual bool init();
    virtual void registerWithTouchDispatcher();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);    
    CREATE_FUNC(MB_MessageBox3);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);    
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void setPosition(CCPoint pos);
    void MessageOver();
//    virtual void onExit();
};
class MB_MessageBox4: public CCLayer, public cocos2d::extension::CCBSelectorResolver

, public cocos2d::extension::CCBMemberVariableAssigner{
    
        CCLabelTTF *m_text_message;
        CCBAnimationManager *m_pAnimation;
    
    public :
    
        MB_MessageBox4();
        ~MB_MessageBox4();
        virtual bool init();
        void set(const char *message);
        virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
        virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
        virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
        CREATE_FUNC(MB_MessageBox4);
        void MessageOver();
    virtual void onExit();
};

class MB_MessageBox5: public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
,public CCEditBoxDelegate{
    
    CCLabelTTF *m_title;    
    CCControlButton *m_onOk2;
    MB_MessageEditDeleate *target;        //按钮回调消息处理
    bool buttonIsGo[1];
    CCEditBox* m_pEditCode;
    
    public :
    
    MB_MessageBox5();
    ~MB_MessageBox5();    
    virtual bool init();    
    void set(const char * title, const char *message,const char *buttonone,   MB_MessageEditDeleate *target);
    virtual void registerWithTouchDispatcher();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    CREATE_FUNC(MB_MessageBox5);
    void onConfirmClicked(CCObject *);   
    void onBackClicked(CCObject *);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);    
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void editBoxReturn(CCEditBox* editBox) ;
    virtual void editBoxEditingDidEnd(CCEditBox* editBox);
    void initEditBox(CCEditBox* editBox);
};
class MB_MessageBoxZuZhi: public CCLayer
{
public:
    MB_MessageBoxZuZhi();
    ~MB_MessageBoxZuZhi();
    CREATE_FUNC(MB_MessageBoxZuZhi);
    virtual bool init();
};
class MB_ResWindow;
class MB_Message :public CCObject{
    
private:
    
    static MB_Message *m_sharedMB_Message;

public:
    
    MB_Message();
    ~MB_Message();
    //获得单例
    static MB_Message* sharedMB_Message();
    static MB_ResWindow* createMessageBox2(const char * title, const char *message,const char *buttonone,const char *buttontwo, CCObject *target ,SEL_MenuHandler buttonOneCall,SEL_MenuHandler buttonTwoCall);
    static MB_ResWindow* createMessageBox1(const char * title, const char *message,const char *buttonone, CCObject *target ,SEL_MenuHandler buttonOneCall);
    static void purge();
    //默认 中点1分钟后消失消息
    void showMessage(float time);
    void showMessage(const char *message);
    //默认设置位置 1分钟后消失消息
    void showMessage(const char *message, CCPoint *point);
    //默认 中点 time后消失消息
    void showMessage(const char *message, float time);
    /** 建立一个消息筐 消息为message time秒后自动消失
     */
    void showMessage(const char *message,float time,CCPoint *point);
    /*建立一个消息筐 消息为message time秒后自动消失 并回调函数*/
    void showMessage(const char *message,float time , CCObject *target ,SEL_CallFunc  actionCall,CCPoint *point);
    //中点显示消息右一个按钮不回调
    void showMessage(const char * title, const char *message,const char *buttonone);
    //设置位置 显示消息一个按钮不回调
    void showMessage(const char * title, const char *message,const char *buttonone, CCPoint *point);
    //中点显示消息右一个按钮可回调函数
    void showMessage(const char * title, const char *message,const char *buttonone, CCObject *target ,SEL_MenuHandler buttonOneCall);
    //设置位 显示消息 一个按钮可回调函数
    void showMessage(const char * title, const char *message,const char *buttonone, CCObject *target ,SEL_MenuHandler buttonOneCall,CCPoint *point);
    //中点 显示消息 两个按钮不回调函数
    void showMessage(const char * title, const char *message,const char *buttonone,const char *buttontwo);
    //中点 显示消息 回调函数
    MB_ResWindow* showMessage(const char * title, const char *message,const char *buttonone,const char *buttontwo, CCObject *target ,SEL_MenuHandler buttonOneCall,SEL_MenuHandler buttonTwoCall);
    //设置位置 显示消息 回调函数
    void showEditBox(const char * title, const char *message,const char *buttonone, MB_MessageEditDeleate *target );
    /** 建立一个消息筐 消息为message
     buttone文字按钮1
     butttow文字按钮2
     target 回调函数触发者
     buttonOneCall 按钮1回调函数
     buttonTowCall 按钮1回调函数
     */
    void showMessage(const char * title, const char *message,const char *buttonone,const char *buttontwo, CCObject *target ,SEL_MenuHandler buttonOneCall,SEL_MenuHandler buttonTwoCall,CCPoint *point);
    void showZuZhiMessage(const char *message, float time);
    /** 建立一个消息筐 消息为message
     
     buttononeSelectFrame按钮1选中图片
     buttononeDisselectFrame按钮1没选中图片
     
     buttontwoSelectFrame按钮2选中图片
     buttontwoDisselectFrame按钮2没选中图片
     
     target 回调函数触发者
     buttonOneCall 按钮1回调函数
     buttonTowCall 按钮1回调函数
     */
    /*  void showMessageWithImageButton(const char * title, const char *message,
     const char *buttononeNormalFrame,
     const char *buttononeSelectFrame,
     const char *buttontwoNormalFrame,
     const char *buttontwoSelectFrame,
     CCObject *target ,SEL_MenuHandler buttonOneCall,SEL_MenuHandler buttonTwoCall,CCPoint *point);
     */
    
    static void setDelayTime(float time);
    static float getDelayTime();
    static void removeALLMessage();
    static void removeAllZuZhiMessage();
    
    
};
#endif /* defined(__ProjectMB__MessageBox___) */
