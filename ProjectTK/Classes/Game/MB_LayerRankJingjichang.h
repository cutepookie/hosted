//
//  MB_LayerRankJingjichang.h
//  ProjectMB
//
//  Create by wenyong on 24/12/2014.
//
//
#ifndef __ProjectMB__MB_LayerRankJingjichang__
#define __ProjectMB__MB_LayerRankJingjichang__

#include "MB_FunctionMainWnd.h"

class MB_RankDataSource;
class MB_FunctionRanking;
class MB_LayerRankJingjichang : public MB_FunctionMainWnd
{
public:
    MB_LayerRankJingjichang();
    virtual ~MB_LayerRankJingjichang();
    CREATE_FUNC(MB_LayerRankJingjichang);
    virtual void onResetWnd();
    virtual bool init();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    void resetData();
protected:
    void onCloseClicked(CCObject* pSender);
    void onInitialized();
private:
    CCTableView* m_pTableView;
    MB_FunctionRanking* m_pInterface;
    CCNode* m_pContainer;
    MB_RankDataSource* rds;
};
#endif /* defined(__ProjectMB__MB_LayerRankJingjichang__) */
