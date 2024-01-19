//
//  MB_NodeTaskItem.h
//  ProjectPM
//
//  Created by WenYong on 14-4-2.
//
//

#ifndef __ProjectMB__MB_NodeTaskItem__
#define __ProjectMB__MB_NodeTaskItem__

#include "MB_ResWindow.h"
class MB_TaskServerData;
class MB_NodeTaskItem:public MB_ResWindow,
public CCBMemberVariableAssigner,
public CCBSelectorResolver
{
public:
    
    MB_NodeTaskItem();
    ~MB_NodeTaskItem();
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool init(MB_TaskServerData* pData);
    static MB_NodeTaskItem* create(MB_TaskServerData* pData,bool bIsLastObj);
    static CCSize getItemSize();
    CCNode* m_pLine;
    virtual void setPosition(float x, float y);
protected:
    virtual void onStatusClicked(CCObject* pSender);
    void onChangePageClicked(CCObject* pSender);
private:
    CCLabelTTF*         m_pTitle;
    CCLabelTTF*         m_pDescription;
    CCNode*             m_pNodeComplate;
    CCControlButton*    m_pBtnStatus;
    CCLabelBMFont*      m_pNodeRewardCount;
    MB_TaskServerData*  m_pDataSource;
    CCLabelBMFont*      m_pSchedule;
    CCNode*             m_pNodeChangePage;
    CCNode*             m_pNodeSize;
    bool                m_bIsLastObj;
    CCSprite*           m_pState;
    CCLabelBMFont*      m_pAllCount;
    
};

#endif /* defined(__ProjectMB__MB_NodeTaskItem__) */
