//
//  MB_NodeSkillContainer.h
//  ProjectMB
//
//  Create by WenYong on 25/9/2014.
//
//
#ifndef __ProjectMB__MB_NodeSkillContainer__
#define __ProjectMB__MB_NodeSkillContainer__

#include "MB_ResWindow.h"

class MB_SkillData;
class MB_NodeSkillContainer2 : public MB_ResWindow,public CCBMemberVariableAssigner
{
public:
    enum
    {
        kTypeSkillNormal = 1,
        kTypeSkillBig,
    };
    MB_NodeSkillContainer2();
    ~MB_NodeSkillContainer2();
    static MB_NodeSkillContainer2* create(const char* petName,MB_SkillData* pData,int type);
    virtual bool init(const char* petName,MB_SkillData* pData,int type);
    virtual void onRestWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
private:
    CCLabelTTF* m_pTTFSkillDes1;
    CCLabelTTF* m_pTTFSkillName1;
    CCSprite* m_pSpriteSkillNormal;
    CCSprite* m_pSpriteSkillBig;
    CCNode*     m_pNodeSize;
    MB_SkillData*    m_pData;
    CCSprite* m_pIcon;
};



class MB_NodeSkillUint : public MB_ResWindow,public CCBMemberVariableAssigner
{
public:
    MB_NodeSkillUint();
    ~MB_NodeSkillUint();
    static MB_NodeSkillUint* create(const char* petName,MB_SkillData* pData,int index,bool bActive);
    virtual bool init(const char* petName,MB_SkillData* pData,int index,bool bActive);
    virtual void onRestWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
private:
    CCNode* m_pNodeSize;
    CCLabelTTF* m_pTTFSkillName;
    CCLabelTTF* m_pTTFLimit;
    CCLabelTTF* m_pTTFSkillDes;
    MB_SkillData* m_pData;
    int m_nIndex;
    bool m_bActive;
    CCNode* m_pLocked;
    CCSprite* m_pIcon;
};
#endif /* defined(__ProjectMB__MB_NodeSkillContainer__) */
