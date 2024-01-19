//
//  MB_GuiCcbCodeGenerator.h
//  ProjectPM
//
//  Created by WenYong on 14-6-3.
//
//

#ifndef __ProjectMB__MB_GuiCcbCodeGenerator__
#define __ProjectMB__MB_GuiCcbCodeGenerator__

#include "cocos2d.h"
#include "CCBMemberVariableAssigner.h"
#include "CCBSelectorResolver.h"
#include <string>
USING_NS_CC;
USING_NS_CC_EXT;

class CcbProperty:public CCObject
{
public:
    virtual bool generalCode(std::string& code)=0;
    const std::string& getName()const{return m_szPropertyName;}
protected:
    bool setName(const char* pName);
protected:
    std::string m_szPropertyName;
};

class CcbAssignedMember:public CcbProperty
{
public:
    static CcbAssignedMember* create(const char* pName, CCNode* pNode);
    virtual bool generalCode(std::string& code);
    static bool getNodeType(std::string& szType,CCNode* pNode);
    const std::string& getTypeName()const{return m_szTypeName;}
protected:
    bool setTypeName(CCNode* pNode);
private:
    std::string     m_szTypeName;
};

class CcbMenuSelector:public CcbProperty
{
public:
    static CcbMenuSelector* create(const char* pName);
    virtual bool generalCode(std::string& code);
};

class CcbControlSelector:public CcbProperty
{
public:
    static CcbControlSelector* create(const char* pName);
    virtual bool generalCode(std::string& code);
};

class CcbWindowResolver:public CCNode,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    CcbWindowResolver();
    virtual ~CcbWindowResolver();
    virtual bool init(const char* pFile);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void clear();
    bool getMemberString(std::string& szMember);
    bool getSelectorString(std::string& szSelector);
    const char* getInheritHeader();
    bool getHeaderContent(std::string& szContent,
                          const std::string& szClassName,
                          const std::string& szInheritClasses);
    bool getCppContent(std::string& szContent,const std::string& szClassName);
    
    bool getOverrideDeclare(std::string& szContent,const std::string& szClassName);
private:
    std::string m_szFileName;
    CCArray* m_pMemberAssigned;
    CCArray* m_pMenuSelector;
    CCArray* m_pControlSelector;
};

class CcbWindowClass:public CcbProperty
{
public:
    CcbWindowClass();
    virtual ~CcbWindowClass();
    static CcbWindowClass* create(const char* pClassName,
                                  const char* pCcbFile);
    
    virtual bool init(const char* pFile);
    virtual bool generalCode(std::string& code);
    bool generalHeader(const char* pFile);
    bool generalCpp(const char* pFile);
    bool getNoteContent(bool bHeader,std::string& szContent);
private:
    CcbWindowResolver*  m_pWindowResolver;
};


#endif /* defined(__ProjectMB__MB_GuiCcbCodeGenerator__) */
