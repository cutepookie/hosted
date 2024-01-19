//
//  MB_NodeSuitProperty.h
//  ProjectPM
//
//  Create by WenYong on 4/5/2014.
//
//
#ifndef __ProjectMB__MB_NodeSuitProperty__
#define __ProjectMB__MB_NodeSuitProperty__

#include "MB_ResWindow.h"

class MB_SuitActivateData;

class MB_NodeSuitProperty : public MB_ResWindow,public CCBMemberVariableAssigner
{
public:
	MB_NodeSuitProperty();
	virtual ~MB_NodeSuitProperty();
	virtual void onResetWnd();
	virtual bool init(MB_SuitActivateData* pData);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    static MB_NodeSuitProperty* create(MB_SuitActivateData* pData);
    void activate(bool bActivate);
    CCSize getNodeSize()const;
    CCNode* m_pLineSpr;
private:
    CCNode*	m_pNodeSize;
    CCSprite*	m_pSpActivated;
    CCSprite*	m_pSpUnActivated;
    CCLabelTTF* m_pTTFPropertys[4];
    bool        m_bActivated;
    MB_SuitActivateData* m_pActivateData;
};
#endif /* defined(__ProjectMB__MB_NodeSuitProperty__) */
