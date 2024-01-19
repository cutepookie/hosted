//
//  MB_LayerMainGift1.h
//  ProjectMB
//
//  Create by wenyong on 17/12/2014.
//
//
#ifndef __ProjectMB__MB_LayerMainGift1__
#define __ProjectMB__MB_LayerMainGift1__

#include "MB_FunctionMainWnd.h"
#include "MB_GiftsProtocol.h"
class MB_GiftsInterface;
class MB_LayerMainGift1 : public MB_FunctionMainWnd
{
public:
    MB_LayerMainGift1();
    virtual ~MB_LayerMainGift1();
    virtual void onResetWnd();
    virtual bool init();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);

    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    void go2Page(EGiftType);

    void cs_daily_reward_get(uint8_t type,uint32_t needValue);
protected:
    void onCloseClick(CCObject* pSender);
    void sc_daily_reward_get(MB_MsgBuffer* pRecv);
private:

    CCNode*    m_pContainer;
    CCTableView* m_pTableView;
    MB_GiftsInterface* m_pInterface;
    CCTableViewDataSource* m_pDataSource;

    CCLabelTTF* m_pLableGiftTime;

    EGiftType m_nCurType;
};


class MB_LayerMainGift2 : public MB_FunctionMainWnd
{
public:
    MB_LayerMainGift2();
    virtual ~MB_LayerMainGift2();
    virtual void onResetWnd();
    virtual bool init();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    void go2Page(EGiftType);
    
    void cs_daily_reward_get(uint8_t type,uint32_t needValue);
protected:
    void onCloseClick(CCObject* pSender);
    void sc_daily_reward_get(MB_MsgBuffer* pRecv);
private:
    
    CCNode*    m_pContainer;
    CCTableView* m_pTableView;
    MB_GiftsInterface* m_pInterface;
    CCTableViewDataSource* m_pDataSource;
    
    CCLabelTTF* m_pLableGiftTime;
    
    EGiftType m_nCurType;
};

class MB_LayerMainGift3 : public MB_FunctionMainWnd
{
public:
    MB_LayerMainGift3();
    virtual ~MB_LayerMainGift3();
    virtual void onResetWnd();
    virtual bool init();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    void go2Page(EGiftType);
    
    void cs_daily_reward_get(uint8_t type,uint32_t needValue);
protected:
    void onCloseClick(CCObject* pSender);
    void sc_daily_reward_get(MB_MsgBuffer* pRecv);
private:
    
    CCNode*    m_pContainer;
    CCTableView* m_pTableView;
    MB_GiftsInterface* m_pInterface;
    CCTableViewDataSource* m_pDataSource;
    
    CCLabelTTF* m_pLableGiftTime;
    
    EGiftType m_nCurType;
};
#endif /* defined(__ProjectMB__MB_LayerMainGift1__) */
