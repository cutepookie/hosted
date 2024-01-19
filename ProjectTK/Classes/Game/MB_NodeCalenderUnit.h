//
//  MB_NodeCalenderUnit.h
//  ProjectMB
//
//  Create by WenYong on 28/8/2014.
//
//
#ifndef __ProjectMB__MB_NodeCalenderUnit__
#define __ProjectMB__MB_NodeCalenderUnit__

#include "MB_ResWindow.h"

enum
{
    kNext = 1,   //未到
    kRegister,   //已签到
    kMiss,       //未签到
};
class MB_NodeCalenderUnit : public MB_ResWindow,public CCBMemberVariableAssigner
{
public:
    static MB_NodeCalenderUnit* create(uint16_t num,int state,bool bIsToday);
    CREATE_FUNC(MB_NodeCalenderUnit);
    static const CCSize& getWndSize();
	MB_NodeCalenderUnit();
	virtual ~MB_NodeCalenderUnit();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    void setDataNumber(uint16_t num,int state,bool bIsToday);
    void setState(int state);
    void setFlag(bool b);
protected:
private:
    uint16_t    m_nDataNumber;
    int        m_nState;
    bool        m_bIsToday;
    CCNode*     size;
    CCLabelBMFont*     m_pNodeData;
    CCNode*     m_pNodeRegister;
    CCNode*     m_pNodeMiss;
    CCNode*     m_pNodeToday;
};
#endif /* defined(__ProjectMB__MB_NodeCalenderUnit__) */
