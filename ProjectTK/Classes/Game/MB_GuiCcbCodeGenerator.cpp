//
//  MB_GuiCcbCodeGenerator.cpp
//  ProjectPM
//
//  Created by WenYong on 14-6-3.
//
//

#include "MB_GuiCcbCodeGenerator.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;

#define USER_NAME       "wenyong"
#define PROJECT_NAME    "ProjectMB"
#define DEFAULT_INCLUDE "MB_ResWindow.h"
#define DEFAULT_INHERIT "MB_ResWindow"

#define CLASS_NAME(CLASS_TYPE,VALUE,NAME) \
if(dynamic_cast<CLASS_TYPE>(VALUE)) \
{\
(NAME) = #CLASS_TYPE;\
return true;\
}

bool CcbProperty::setName(const char *pName)
{
    if (pName == NULL || strlen(pName)==0)
    {
        return false;
    }
    
    m_szPropertyName = pName;
    
    return true;
}

CcbAssignedMember* CcbAssignedMember::create(const char* pName, CCNode* pNode)
{
    CcbAssignedMember* pInstance = new CcbAssignedMember;
    
    if (pInstance && pInstance->setName(pName) && pInstance->setTypeName(pNode))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}

bool CcbAssignedMember::setTypeName(CCNode* pNode)
{
    return getNodeType(m_szTypeName, pNode);
}

bool CcbAssignedMember::getNodeType(std::string& szType,CCNode* pNode)
{
    CLASS_NAME(CCLayerGradient*, pNode, szType);
    CLASS_NAME(CCLayerColor*, pNode, szType);
    CLASS_NAME(CCScale9Sprite*, pNode, szType);
    CLASS_NAME(CCLabelTTF*, pNode,szType);
    CLASS_NAME(CCSprite*, pNode, szType);
    CLASS_NAME(CCScrollView*, pNode, szType);
    CLASS_NAME(CCMenu*, pNode, szType);
    CLASS_NAME(CCControlButton*, pNode, szType);
    CLASS_NAME(CCMenuItemImage*, pNode, szType);
    CLASS_NAME(CCParticleSystemQuad*, pNode, szType);
    CLASS_NAME(CCLayer*, pNode, szType);
    CLASS_NAME(CCNode*, pNode, szType);
    return false;
}

bool CcbAssignedMember::generalCode(std::string& code)
{
    code = "    " + m_szTypeName + "\t" + m_szPropertyName + ";\n";
    return true;
}

CcbMenuSelector* CcbMenuSelector::create(const char* pName)
{
    CcbMenuSelector* pInstance = new CcbMenuSelector;
    if (pInstance && pInstance->setName(pName))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

bool CcbMenuSelector::generalCode(std::string& code)
{
    code = "    void " + m_szPropertyName + "(CCObject* pSender);\n";
    return true;
}

CcbControlSelector* CcbControlSelector::create(const char* pName)
{
    CcbControlSelector* pInstance = new CcbControlSelector;
    if (pInstance && pInstance->setName(pName))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

bool CcbControlSelector::generalCode(std::string& code)
{
    code = "    void " + m_szPropertyName + "(CCObject* pSender);\n";
    return true;
}

CcbWindowResolver::CcbWindowResolver()
{
    m_pMemberAssigned = new CCArray;
    m_pMenuSelector = new CCArray;
    m_pControlSelector = new CCArray;
}
CcbWindowResolver::~CcbWindowResolver()
{
    CC_SAFE_RELEASE_NULL(m_pMemberAssigned);
    CC_SAFE_RELEASE_NULL(m_pMenuSelector);
    CC_SAFE_RELEASE_NULL(m_pControlSelector);
}
bool CcbWindowResolver::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CcbAssignedMember* pObj = CcbAssignedMember::create(pMemberVariableName, pNode);
    if (pObj)
    {
        m_pMemberAssigned->addObject(pObj);
    }
    return false;
}

SEL_MenuHandler CcbWindowResolver::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CcbMenuSelector* pObj = CcbMenuSelector::create(pSelectorName);
    if (pObj)
    {
        m_pMenuSelector->addObject(pObj);
    }
    return NULL;
}

SEL_CCControlHandler CcbWindowResolver::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CcbControlSelector* pObj = CcbControlSelector::create(pSelectorName);
    if (pObj)
    {
        m_pControlSelector->addObject(pObj);
    }
    
    return NULL;
}

void CcbWindowResolver::clear()
{
    m_pMemberAssigned->removeAllObjects();
    m_pMenuSelector->removeAllObjects();
    m_pControlSelector->removeAllObjects();
}

bool CcbWindowResolver::init(const char* pFile)
{
    if (pFile == NULL)
    {
        return false;
    }
    
    clear();
    
    CCBReader* pReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    
    if (pReader)
    {
        pReader->readNodeGraphFromFile(pFile, this);
    }
    
    m_szFileName = pFile;
    
    CC_SAFE_RELEASE_NULL(pReader);
    
    return true;
};

bool CcbWindowResolver::getMemberString(std::string& szMember)
{
    CcbProperty* pMember = NULL;
    
    CCObject* pObject = NULL;
    
    std::string code;
    
    szMember = "private:\n";
    
    CCARRAY_FOREACH(m_pMemberAssigned, pObject)
    {
        pMember = dynamic_cast<CcbProperty*>(pObject);
        if (pMember)
        {
            pMember->generalCode(code);
            szMember += code;
        }
    }
    
    return true;
}

bool CcbWindowResolver::getSelectorString(std::string& szSelector)
{
    CcbProperty* pMember = NULL;
    
    CCObject* pObject = NULL;
    
    std::string code;
    
    szSelector = "protected:\n";
    
    CCARRAY_FOREACH(m_pMenuSelector, pObject)
    {
        pMember = dynamic_cast<CcbProperty*>(pObject);
        if (pMember)
        {
            pMember->generalCode(code);
            szSelector += code;
        }
    }
    
    CCARRAY_FOREACH(m_pControlSelector, pObject)
    {
        pMember = dynamic_cast<CcbProperty*>(pObject);
        if (pMember)
        {
            pMember->generalCode(code);
            szSelector += code;
        }
    }
    
    return true;
}

bool CcbWindowResolver::getOverrideDeclare(std::string& szContent,const std::string& szClassName)
{
    szContent = "public:\n";
    
    szContent += "\t" + szClassName + "();\n";
    szContent += "\tvirtual ~" + szClassName + "();\n";
    szContent += "\tvirtual void onResetWnd();\n";
    szContent += "\tvirtual bool init();\n";
    
    if (m_pMemberAssigned->count())
    {
        szContent += "\tvirtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);\n";
    }
    
    if (m_pMenuSelector->count() || m_pControlSelector->count())
    {
        szContent += "\tvirtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);\n\tvirtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);\n";
    }
    
    return true;
}

const char* CcbWindowResolver::getInheritHeader()
{
    std::string header = "public " + std::string(DEFAULT_INHERIT);
    
    if (m_pMemberAssigned->count()!=0)
    {
        header += ",public CCBMemberVariableAssigner";
    }
    
    if (m_pMenuSelector->count()!=0
        || m_pControlSelector->count()!=0)
    {
        
        
        header += ",public CCBSelectorResolver";
    }
    
    return header.c_str();
}

bool CcbWindowResolver::getHeaderContent(std::string& szContent,
                                         const std::string& szClassName,
                                         const std::string& szInheritClasses)
{
    std::string member,selector,override;
    
    std::string inherit_class = szInheritClasses;
    if (inherit_class.empty())
    {
        inherit_class = getInheritHeader();
    }
    
    getOverrideDeclare(override,szClassName);
    getMemberString(member);
    getSelectorString(selector);
    
    szContent = "class " + szClassName + " : " + inherit_class + "\n{\n" + override + selector + member + "};\n";
    
    return true;
}


bool CcbWindowResolver::getCppContent(std::string& szContent,const std::string& szClassName)
{
    std::string header = "#include \"" + szClassName + ".h\"\n\n" + szClassName + "::" + szClassName + "()\n{\n";
    
    CcbProperty* pTemp = NULL;
    CCObject* pObject = NULL;
    
    std::string sub_content;
    
    CCARRAY_FOREACH(m_pMemberAssigned, pObject)
    {
        pTemp = dynamic_cast<CcbProperty*>(pObject);
        sub_content += "    " + pTemp->getName() + "\t = NULL;\n";
    }
    
    szContent = header + sub_content + "}\n";
    
    header = szClassName + "::~" + szClassName + "()\n{\n";
    sub_content = "";
    
    CCARRAY_FOREACH(m_pMemberAssigned, pObject)
    {
        pTemp = dynamic_cast<CcbProperty*>(pObject);
        sub_content += "    CC_SAFE_RELEASE_NULL(" + pTemp->getName() + ");\n";
    }
    
    szContent += header + sub_content + "}\n";
    
    
    header = "bool " + szClassName + "::init()\n{\n";
    sub_content = "    CCNode* pNode = loadResource(\"" + m_szFileName + "\");\n    if(pNode)\n\t{\n\t\taddChild(pNode);\n\t\treturn true;\n\t}\n\treturn false;\n}\n";
    
    szContent += header + sub_content;
    
    
    szContent += "void " + szClassName + "::onResetWnd()\n{\n\n}\n";
    
    
    if (m_pMemberAssigned->count())
    {
        header = "bool " + szClassName + "::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)\n{\n";
        sub_content = "";
        
        CcbAssignedMember* pMember = NULL;
        CCARRAY_FOREACH(m_pMemberAssigned, pObject)
        {
            pMember = dynamic_cast<CcbAssignedMember*>(pObject);
            sub_content += "    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,\"" + pMember->getName() + "\"," + pMember->getTypeName() + "," + pMember->getName() +  ");\n";
        }
        
        szContent += header + sub_content + "\treturn false;\n}\n";
    }
    
    if (m_pMenuSelector->count()!=0 || m_pControlSelector->count()!=0)
    {
        std::string sel_define = "";
        header = "SEL_MenuHandler " + szClassName + "::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)\n{\n";
        sub_content = "";
        
        CCARRAY_FOREACH(m_pMenuSelector, pObject)
        {
            pTemp = dynamic_cast<CcbProperty*>(pObject);
            if (pTemp)
            {
                sub_content += "    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,\"" + pTemp->getName() + "\"," + szClassName + "::" + pTemp->getName() + ");\n";
                sel_define += "void " + szClassName + "::" + pTemp->getName() + "(CCObject* pSender)\n{\n}\n";
            }
        }
        
        szContent += header + sub_content + "\treturn NULL;\n}\n";
        
        header = "SEL_CCControlHandler " + szClassName + "::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)\n{\n";
        sub_content = "";
        
        CCARRAY_FOREACH(m_pControlSelector, pObject)
        {
            pTemp = dynamic_cast<CcbProperty*>(pObject);
            if (pTemp)
            {
                sub_content += "    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,\"" + pTemp->getName() + "\"," + szClassName + "::" + pTemp->getName() + ");\n";
                sel_define += "void " + szClassName + "::" + pTemp->getName() + "(CCObject* pSender)\n{\n}\n";
            }
        }
        
        szContent += header + sub_content + "\treturn NULL;\n}\n" + sel_define;
    }
    
    return true;
}

CcbWindowClass::CcbWindowClass()
{
    m_pWindowResolver = NULL;
}

CcbWindowClass::~CcbWindowClass()
{
    CC_SAFE_RELEASE_NULL(m_pWindowResolver);
}

CcbWindowClass* CcbWindowClass::create(const char* pClassName,
                                       const char* pCcbFile)
{
    CcbWindowClass* pInstance = new CcbWindowClass;
    if (pInstance && pInstance->setName(pClassName)
        && pInstance->init(pCcbFile))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return NULL;
}

bool CcbWindowClass::init(const char* pFile)
{
    CC_SAFE_RELEASE_NULL(m_pWindowResolver);
    
    m_pWindowResolver = new CcbWindowResolver;
    
    if (m_pWindowResolver && m_pWindowResolver->init(pFile))
    {
        return true;
    }
    
    return false;
}

bool CcbWindowClass::generalCode(std::string& code)
{
    if (m_pWindowResolver)
    {
        m_pWindowResolver->getHeaderContent(code, m_szPropertyName, "");
        return true;
    }
    
    return false;
}

bool CcbWindowClass::getNoteContent(bool bHeader,std::string& szContent)
{
    std::string file_name = m_szPropertyName;
    if (bHeader)
    {
        file_name += ".h";
    }
    else
    {
        file_name += ".cpp";
    }
    
    time_t t = time(NULL);
    tm* pt = localtime(&t);
    char buff[128] = {};
    sprintf(buff, "Create by %s on %d/%d/%d.\n//\n//\n",USER_NAME,pt->tm_mday,pt->tm_mon+1,pt->tm_year+1900);
    
    szContent = "//\n//  " + file_name + "\n//  " + std::string(PROJECT_NAME) + std::string("\n//\n//  ") + buff;
    
    if (bHeader)
    {
        szContent += "#ifndef __" + std::string(PROJECT_NAME) + "__" + m_szPropertyName + "__\n";
        szContent += "#define __" + std::string(PROJECT_NAME) + "__" + m_szPropertyName + "__\n\n";
        szContent += "#include \"" + std::string(DEFAULT_INCLUDE) + "\"\n\n";
    }
    
    return true;
}

bool CcbWindowClass::generalHeader(const char* pFile)
{
    if (m_pWindowResolver == NULL)
    {
        return false;
    }
    
    FILE* pf = fopen(pFile, "w");
    if (pf)
    {
        std::string content;
        getNoteContent(true, content);
        fwrite(content.c_str(), content.length(), 1, pf);
        
        m_pWindowResolver->getHeaderContent(content, m_szPropertyName, "");
        
        fwrite(content.c_str(), content.length(), 1, pf);
        
        content = "#endif /* defined(__" + std::string(PROJECT_NAME) + "__" + m_szPropertyName + "__) */";
        
        fwrite(content.c_str(), content.length(), 1, pf);
        
        fclose(pf);
        return true;
    }
    
    return false;
}

bool CcbWindowClass::generalCpp(const char* pFile)
{
    if (m_pWindowResolver == NULL)
    {
        return false;
    }
    
    FILE* pf = fopen(pFile, "w");
    if (pf)
    {
        std::string content;
        getNoteContent(false, content);
        fwrite(content.c_str(), content.length(), 1, pf);
        
        m_pWindowResolver->getCppContent(content, m_szPropertyName);
        
        fwrite(content.c_str(), content.length(), 1, pf);
        
        fclose(pf);
        return true;
    }
    
    return false;
}