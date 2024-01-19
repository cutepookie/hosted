//
//  MB_XmlItems.cpp
//  XmlManager
//
//  Created by crimoon00007 on 14-1-24.
//  Copyright (c) 2014年 crimoon. All rights reserved.
//

#include "MB_XmlItems.h"
#include "MB_Aescrypt.h"
USING_NS_CC;
MB_XmlFile::MB_XmlFile()
{
    m_pNodeArray = CCArray::create();
    m_pNodeArray->retain();
}

MB_XmlFile::~MB_XmlFile()
{
    CC_SAFE_RELEASE_NULL(m_pNodeArray);
}

void MB_XmlFile::parseFileName(const char* pPath,std::string& szPath)
{
    char filename[256];
    int length = strlen(pPath);
    strcpy(filename, pPath);
    for (int i = length -1;  i >= 0; i--)
    {
        if(filename[i] == '.')
        {
            filename[i+1] = 'c';
            filename[i+2] = 'b';
            filename[i+3] = '\0';
            break;
        }
    }
    szPath = filename;
}

MB_XmlFile* MB_XmlFile::create(const char* pPath)
{
    MB_XmlFile* pInstance = new MB_XmlFile();
    if (pInstance && pInstance->readXmlData(pPath))
    {
        pInstance->autorelease();
        return pInstance;
    }
    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}

bool MB_XmlFile::readXmlData(const char* pPath)
{
    xmlDocPtr ptr = readXml(pPath);
    if (ptr == NULL)
    {
        CCLog("[read xml failed:%s]",pPath);
        return false;
    }
    m_pName->initWithFormat("%s",pPath);
    
    bool ret = read2Array(ptr);
    xmlFreeDoc(ptr);
    
    return ret;
}





bool MB_XmlFile::readNodesFromFile(const char* pFile,const char* pLayerout,CCArray* pNodeArray)
{
    assert(pLayerout);
    
    xmlDocPtr pDoc = readXml(pFile);
    
    if (pDoc)
    {
        xmlNodePtr curNode = xmlDocGetRootElement(pDoc);
        bool ret = false;
        if (curNode)
        {
            ret = readNodesFromXmlNode(curNode,pLayerout,pNodeArray);
        }
        xmlFreeDoc(pDoc);
        return ret;
    }
    return false;
}
bool MB_XmlItem::nodeGetAttributeContent(xmlNodePtr pNode,CCString* pString)
{
    assert(pString);
    pString->initWithFormat("%s",(char*)pNode->name);
    return true;
}

bool MB_XmlItem::isNodeNameCompare(xmlNodePtr pNode,const char* pName)
{
    assert(pName);
    return strcmp((char*)pNode->name, pName)==0;
}

bool MB_XmlFile::readNodesFromXmlNode(xmlNodePtr pNode,const char* pLayerout,cocos2d::CCArray* pNodeArray)
{
    assert(pNode);
    if (strlen(pLayerout)==0)
    {
        return false;
    }
    
    std::string name = pLayerout;
    size_t sz = name.find('|',0);
    bool bHasChild = false;
    if(sz!=std::string::npos)
    {
        name.assign(name.c_str(),sz);
        bHasChild = true;
    }
    
    if (isNodeNameCompare(pNode, name.c_str()))
    {
        if (!bHasChild)
        {
            MB_XmlNode* pXmlNode = new MB_XmlNode;
            if (pXmlNode->init(pNode))
            {
                pNodeArray->addObject(pXmlNode);
            }
            CC_SAFE_RELEASE_NULL(pXmlNode);
            return true;
        }
        else
        {
            xmlNodePtr pn = pNode->xmlChildrenNode;
            while (pn)
            {
                if(readNodesFromXmlNode(pn, pLayerout+name.length()+1, pNodeArray))
                {
                    return true;
                }
                pn = pn->next;
            }
        }
    }
    
    return false;
}

bool MB_XmlFile::read2Array(xmlDocPtr pXml)
{
    assert(pXml);

    xmlNodePtr curNode = xmlDocGetRootElement(pXml);
    MB_XmlNode* pNode = NULL;
    m_pNodeArray->removeAllObjects();
    while (curNode)
    {
        pNode = new MB_XmlNode;
        if (pNode->init(curNode))
        {
            m_pNodeArray->addObject(pNode);
        }
        CC_SAFE_RELEASE_NULL(pNode);
        curNode = curNode->next;
    }
    return true;
}
void MB_XmlItem::splitStringByChar(char ch,const char* pString,cocos2d::CCArray* pStringArray)
{
    assert(pString);
    size_t len = strlen(pString);
    size_t begin = 0;
    size_t nLen = 0;
    std::string str;
    for (size_t i=0; i<len; ++i)
    {
        ++nLen;
        if (pString[i]==ch)
        {
            str.assign(pString+begin, pString+begin+nLen);
            CCString* p = CCString::create(str);
            pStringArray->addObject(p);
            ++i;
            begin = i;
            nLen = 0;
        }
    }
}

// query the nodes by name, combain with  root|child|...|attr
bool MB_XmlFile::queryNodesByName(const char* pName,CCArray* pArray)
{
    assert(pName);
    std::string name = pName;
    size_t sz = name.find('|',0);
    bool bHasChild = false;
    if(sz!=std::string::npos)
    {
        name.assign(name.c_str(),sz);
        bHasChild = true;
    }

    CCObject* pObject = NULL;
    MB_XmlNode* pNode = NULL;
    CCARRAY_FOREACH(m_pNodeArray, pObject)
    {
        pNode = dynamic_cast<MB_XmlNode*>(pObject);
        if (pNode)
        {
            if (pNode->getIsNameEqual(name.c_str()))
            {
                if (bHasChild)
                {
                    pNode->queryNodesByName(pName+name.length()+1,pArray);
                }
                else
                {
                    pArray->addObject(pNode);
                }
            }
        }
    }

    return pArray->count()!=0;
}

bool MB_XmlNode::queryNodesByName(const char* pName,cocos2d::CCArray* pArray)
{
    assert(pName);
    std::string name = pName;
    size_t sz = name.find('|',0);
    bool bHasChild = false;
    if(sz!=std::string::npos)
    {
        name.assign(name.c_str(),sz);
        bHasChild = true;
    }
    
    CCObject* pObject = NULL;
    MB_XmlNode* pNode = NULL;
    CCARRAY_FOREACH(m_pChildren, pObject)
    {
        pNode = dynamic_cast<MB_XmlNode*>(pObject);
        if (pNode)
        {
            if (pNode->getIsNameEqual(name.c_str()))
            {
                if (bHasChild)
                {
                    pNode->queryNodesByName(pName+name.length()+1,pArray);
                }
                else
                {
                    pArray->addObject(pNode);
                }
            }
        }
    }
    
    return pArray->count()!=0;
}

void MB_XmlFile::print()
{
    CCObject* pObject = NULL;
    MB_XmlNode* pNode = NULL;
    CCARRAY_FOREACH(m_pNodeArray, pObject)
    {
        pNode = dynamic_cast<MB_XmlNode*>(pObject);
        if (pNode)
        {
            pNode->print();
        }
    }
}

xmlDocPtr MB_XmlFile::readXml(const char *pPath)
{
    std::string real_path;
    parseFileName( pPath, real_path);

    xmlDocPtr doc = NULL;
    unsigned long size = 0;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

    FILE  *fp = fopen(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(real_path.c_str()).c_str(), "r");
    if(fp == 0)
    {

        doc =  xmlReadFile(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(pPath).c_str(), "utf-8", XML_PARSE_RECOVER);
        return doc;

    }
    char *out =(char *) MB_Aescypt::decrypt_stream(fp,&size);
    doc = xmlReadMemory(out,size,  NULL, "utf-8", XML_PARSE_RECOVER);
    CC_SAFE_DELETE_ARRAY(out);
    return doc;

#else
    char* pBuff = (char*)cocos2d::CCFileUtils::sharedFileUtils()->getFileData(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(real_path.c_str()).c_str(),"r", &size  );
    if(pBuff == NULL)
    {
        FILE  *fp = fopen(real_path.c_str(), "r");
        if(fp == 0)
        {

            doc = xmlReadFile(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(pPath).c_str(), "utf-8", XML_PARSE_RECOVER);
            return doc;
        }
        char *out =(char *) MB_Aescypt::decrypt_stream(fp,&size);
        doc = xmlReadMemory(out,size,  NULL, "utf-8", XML_PARSE_RECOVER);
        CC_SAFE_DELETE_ARRAY(out);
        return doc;
    }
    char *out  = (char *) MB_Aescypt::decrypt_stream(pBuff,&size  );
    doc = xmlReadMemory(out,size,  NULL, "utf-8", XML_PARSE_RECOVER);
    CC_SAFE_DELETE_ARRAY(pBuff);
    return doc;
#endif
}

////////////////XML ITEM////////////////

MB_XmlItem::MB_XmlItem()
{
    m_pName = CCString::create("");
    m_pName->retain();
}

MB_XmlItem::~MB_XmlItem()
{
    CC_SAFE_RELEASE_NULL(m_pName);
}


void MB_XmlItem::filterNodeByName(const char* pName,cocos2d::CCArray* pArray)
{

}
////////////////////////////////////////

////////////////XML NODE////////////////
MB_XmlNode::MB_XmlNode()
{
    m_pAttributes = CCArray::create();
    m_pChildren = CCArray::create();
    m_pAttributes->retain();
    m_pChildren->retain();
}

MB_XmlNode::~MB_XmlNode()
{
    CC_SAFE_RELEASE_NULL(m_pChildren);
    CC_SAFE_RELEASE_NULL(m_pAttributes);
}


bool MB_XmlNode::init(xmlNodePtr pNode)
{
    assert(pNode);
    m_pName->initWithFormat("%s",(char*)pNode->name);
    
    xmlNodePtr curNode = pNode->xmlChildrenNode;
    
    MB_XmlNode* pChild = NULL;
    
    m_pChildren->removeAllObjects();
    while(curNode)
    {
        pChild = new MB_XmlNode;
        if (pChild->init(curNode))
        {
            //pChild->print();
            m_pChildren->addObject(pChild);
        }
        CC_SAFE_RELEASE_NULL(pChild);
        curNode = curNode->next;
    }


    struct _xmlAttr * attr = pNode->properties;
    MB_XmlAttribute* pAttr = NULL;
    m_pAttributes->removeAllObjects();

    while (attr)
    {
        pAttr = new MB_XmlAttribute;
        if (pAttr->init(attr))
        {
            m_pAttributes->addObject(pAttr);
        }
        CC_SAFE_RELEASE_NULL(pAttr);
        attr = attr->next;
    }
    return true;
}
void MB_XmlNode::print()
{
    CCObject* pObject = NULL;

    MB_XmlAttribute* pAttr = NULL;
//    printf("<%s ",m_pName->getCString());
    CCARRAY_FOREACH(m_pAttributes, pObject)
    {
        pAttr = dynamic_cast<MB_XmlAttribute*>(pObject);
        if (pAttr)
        {
            pAttr->print();
        }
    }
//    printf("/>\n");

    MB_XmlNode* pNode = NULL;
    CCARRAY_FOREACH(m_pChildren, pObject)
    {
        pNode = dynamic_cast<MB_XmlNode*>(pObject);
        if (pNode)
        {
            pNode->print();
        }
    }
}

const CCString*   MB_XmlNode::queryAttributeByName(const char* pName)const
{
    assert(pName);

    CCObject* pObj = NULL;
    MB_XmlAttribute* pAttr = NULL;
    CCARRAY_FOREACH(m_pAttributes, pObj)
    {
        pAttr = dynamic_cast<MB_XmlAttribute*>(pObj);
        if (pAttr->m_pAttributeName->compare(pName)==0)
        {
            return pAttr->m_pValue;
        }
    }

    return CCString::createWithFormat("");
}

const MB_XmlNode& MB_XmlNode::operator[](const char* pName)const
{
    if (m_pAttributes->count()==0 || pName==NULL)
    {
        CCLog("[Error:]no xmlnode named %s,return the root instead",pName);
        return *this;
    }
    
    MB_XmlNode* pNode = NULL;
    CCARRAY_FOREACH_4TYPE(m_pChildren, MB_XmlNode*, pNode)
    {
        if (pNode->getIsNameEqual(pName))
        {
            return *pNode;
        }
    }
    
    CCLog("[Error:]no xmlnode named %s,return the root instead",pName);
    return *this;
}

////////////////////////////////////////

//////////////////XML ATTR///////////////////

MB_XmlAttribute::MB_XmlAttribute()
{
    m_pAttributeName = new CCString("");
    m_pValue = new CCString("");
}

MB_XmlAttribute::~MB_XmlAttribute()
{
    CC_SAFE_RELEASE_NULL(m_pValue);
    CC_SAFE_RELEASE_NULL(m_pAttributeName);
}

bool MB_XmlAttribute::init(xmlAttrPtr pAttr)
{
    assert(pAttr);
    m_pAttributeName->initWithFormat("%s",(char*)pAttr->name);
    char* str = (char*)xmlNodeGetContent(pAttr->children);
    m_pValue->initWithFormat("%s",str);
    free(str);
    return true;
}

void MB_XmlAttribute::print()
{
//    printf("%s=\"%s\" ",m_pAttributeName->getCString(),m_pValue->getCString());
}

/////////////////////////////////////////////
































