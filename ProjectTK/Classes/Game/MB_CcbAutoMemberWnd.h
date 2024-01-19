//
//  MB_CcbAutoMemberWnd.h
//  ProjectPM
//
//  Created by WenYong on 14-4-2.
//
//

#ifndef __ProjectMB__MB_CcbAutoMemberWnd__
#define __ProjectMB__MB_CcbAutoMemberWnd__
#include "MB_ResWindow.h"
#include <map>

class MB_MemberAttribult:public CCObject
{
public:
    MB_MemberAttribult();
    ~MB_MemberAttribult();
    static MB_MemberAttribult* create(const char* pName,CCNode* pNode);
    std::string m_pName;
    CCNode*     m_pNode;
};
class MB_CcbAutoMemberWnd:public MB_ResWindow,
public CCBMemberVariableAssigner
{
public:
    MB_CcbAutoMemberWnd();
    virtual ~MB_CcbAutoMemberWnd();
    static MB_CcbAutoMemberWnd* create(const char* pCcbFile);
    virtual bool init(const char* pCcbFile);
    CCNode* operator[](const char* pNodeName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
private:
    CCArray* m_pMembers;
};

#endif /* defined(__ProjectMB__MB_CcbAutoMemberWnd__) */
