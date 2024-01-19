//
//  MB_NodeItemIcon.h
//  ProjectPM
//
//  Create by WenYong on 23/7/2014.
//
//
#ifndef __ProjectMB__MB_NodeItemIcon__
#define __ProjectMB__MB_NodeItemIcon__

#include "MB_ResWindow.h"

class MB_NodeItemIcon : public MB_ResWindow,public CCBMemberVariableAssigner
{
public:
	MB_NodeItemIcon();
	virtual ~MB_NodeItemIcon();
	virtual void onResetWnd();
    static MB_NodeItemIcon* create(uint16_t tid,int nRank=1);
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    void setData(uint16_t tid,int nRank=1);
protected:
private:
    int         m_nRank;
    uint16_t    m_nTypeID;
    CCSprite*	m_pItemIcon;
    CCSprite*	m_pItemFrame;
    CCNode* m_pSpriteDebris;
};
#endif /* defined(__ProjectMB__MB_NodeItemIcon__) */