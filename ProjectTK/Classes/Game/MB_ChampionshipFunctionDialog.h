//
//  MB_ChampionshipFunctionDialog.h
//  ProjectPM
//
//  Created by chk on 14-3-24.
//
//

#ifndef __ProjectMB__MB_ChampionshipFunctionDialog__
#define __ProjectMB__MB_ChampionshipFunctionDialog__

#include "MB_FunctionMainWnd.h"
#include "MB_NodeReportBox.h"


enum kmPvpTable
{
    kmPvpTable_Pvp,             //挑战
    kmPvpTable_Report,          //战报
    kmPvpTable_Rank,      //排行
    kmPvpTable_Shop,      //商店
};

//精靈榜功能窗口
class MB_ChampionshipFunctionDialog:public MB_FunctionMainWnd
{
public:
    MB_ChampionshipFunctionDialog();
    ~MB_ChampionshipFunctionDialog();
    virtual bool init();
    virtual void onEnter();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onLoadingScene(){};
    virtual void onMsgRecv(CCNode* node, SocketResponse* response){};
    virtual bool                 onAssignCCBMemberVariable      (CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
    virtual SEL_MenuHandler      onResolveCCBCCMenuItemSelector (CCObject * pTarget,const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onResetWnd();
    void onEnterTransitionDidFinish();
protected:
    void update(float dt);
    NSGameFunction::CCFunctionInterface*  m_pInterface;
    void onCloseClicked(CCObject* pSender);
    void onTZClick(CCObject* pSender);
    void onZBClick(CCObject* pSender);
    void onPMClick(CCObject* pSender);
    void onJJSDClick(CCObject* pSender);
    CCLabelBMFont*          m_pMailNum;
    kmPvpTable           m_currentPage;
    CCNode *            m_pNodeMailNum;
    CCNode* m_pSelectedSpr;
    CCNode* m_pNode;
};

#endif /* defined(__ProjectMB__MB_ChampionshipFunctionDialog__) */
