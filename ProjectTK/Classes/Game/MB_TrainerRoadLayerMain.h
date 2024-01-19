//
//  MB_TrainerRoadLayerMain.h
//  ProjectMB
//
//  Create by wenyong on 15/1/2015.
//
//
#ifndef __ProjectMB__MB_TrainerRoadLayerMain__
#define __ProjectMB__MB_TrainerRoadLayerMain__

#include "MB_FunctionMainWnd.h"
class MB_TrainerRoadLayerMap;
class MB_FunctionTrainerRoad;
class MB_TrainerRoadLayerMain : public MB_FunctionMainWnd
{
public:
	MB_TrainerRoadLayerMain();
	virtual ~MB_TrainerRoadLayerMain();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    
    void send_road_fight(std::string);
    void onEnterTransitionDidFinish();
    void send_road_box();
    void recv_road_box(MB_MsgBuffer* pRecv);
protected:
    virtual void onInitialized();
    void onCloseClicked(CCObject* pSender);
    void onResetClicked(CCObject* pSender);
    void onExtClicked(CCObject*);
private:
    CCNode*     m_pNodeMap;
    CCLabelBMFont*	m_pResetTimes;
    MB_TrainerRoadLayerMap* m_pLayerMap;
    MB_FunctionTrainerRoad* m_pFunction;
    CCScrollView* m_pScrollView;
    
    //神秘关卡
    CCNode* m_pNodeExt;
};
#endif /* defined(__ProjectMB__MB_TrainerRoadLayerMain__) */
