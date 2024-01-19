//
//  MB_LayerTrainerTrove.h
//  ProjectMB
//
//  Create by wenyong on 27/2/2015.
//
//
#ifndef __ProjectMB__MB_LayerTrainerTrove__
#define __ProjectMB__MB_LayerTrainerTrove__

#include "MB_FunctionModule.h"



class MB_FunctionTrainerTroveInterface;
class MB_LayerTrainerTrove : public MB_FunctionMainWnd
{
    enum
    {
        kTypeFightEasy = 1,
        kTypeFightNormal = 2,
        kTypeFightHard = 3
    };
public:
    
	MB_LayerTrainerTrove();
	virtual ~MB_LayerTrainerTrove();
	virtual void onResetWnd();
	virtual bool init();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    void updataTick(float dt);
    virtual void onEnter();
    void onEnterTransitionDidFinish();
protected:
    void onCloseClick(CCObject* pSender);
    void onRuleClick(CCObject* pSender);
    void onEasyFightClick(CCObject* pSender);
    void onNormalFightClick(CCObject* pSender);
    void onHardFightClick(CCObject* pSender);
    
    
    bool checkCanFight();
private:
    CCLabelTTF*	m_pTTFLastFightCount;
    CCLabelTTF* m_pTTFFightTime;
    MB_FunctionTrainerTroveInterface* m_pInterface;
};
#endif /* defined(__ProjectMB__MB_LayerTrainerTrove__) */
