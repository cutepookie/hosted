//
//  MB_XmlItems.h
//  XmlManager
//
//  Created by crimoon00007 on 14-1-24.
//  Copyright (c) 2014年 crimoon. All rights reserved.
//

#ifndef __XmlManager__MB_XmlItems__
#define __XmlManager__MB_XmlItems__

#include "Game.h"

class MB_XmlItem:public cocos2d::CCObject
{
public:
    MB_XmlItem();
    ~MB_XmlItem();
    virtual void print()=0;
    virtual cocos2d::CCArray* getChilden()=0;
    bool getIsNameEqual(const char* pStr){return m_pName->compare(pStr)==0;}
    virtual bool queryNodesByName(const char* pName,cocos2d::CCArray* pArray)=0;
public:
    static void filterNodeByName(const char* pName,cocos2d::CCArray* pArray);
    static void splitStringByChar(char ch,const char* pString,cocos2d::CCArray* pStringArray);
    static bool nodeGetAttributeContent(xmlNodePtr pNode,CCString* pString);
    static bool isNodeNameCompare(xmlNodePtr pNode,const char* pName);
protected:
    cocos2d::CCString*       m_pName;
};

class MB_XmlFile:public MB_XmlItem
{
public:
    MB_XmlFile();
    ~MB_XmlFile();
    
    bool readXmlData(const char* pPath);
    virtual bool queryNodesByName(const char* pName,cocos2d::CCArray* pArray);
    virtual void print();
    virtual cocos2d::CCArray* getChilden(){return m_pNodeArray;}
    
public:
    static xmlDocPtr readXml(const char* pPath);
    static void parseFileName(const char* pPath,std::string& szPath);
    static MB_XmlFile* create(const char* pPath);
    static bool readNodesFromFile(const char* pFile,const char* pLayerout,cocos2d::CCArray* pNodeArray);
    
protected:
    static bool readNodesFromXmlNode(xmlNodePtr pNode,const char* pLayerout,cocos2d::CCArray* pNodeArray);
    bool read2Array(xmlDocPtr pXml);
private:
    cocos2d::CCArray*        m_pNodeArray;
};

class MB_XmlNode:public MB_XmlItem
{
public:
    MB_XmlNode();
    ~MB_XmlNode();
    bool init(xmlNodePtr pNode);
    virtual void print();
    const cocos2d::CCString*   queryAttributeByName(const char* pName)const;
    virtual cocos2d::CCArray* getChilden(){return m_pChildren;}
    virtual bool queryNodesByName(const char* pName,cocos2d::CCArray* pArray);
    const MB_XmlNode& operator[](const char* attr)const;
private:
    cocos2d::CCArray*    m_pAttributes;
    cocos2d::CCArray*    m_pChildren;
};

class MB_XmlAttribute:public MB_XmlItem
{
public:
    MB_XmlAttribute();
    ~MB_XmlAttribute();
    bool init(xmlAttrPtr pAttr);
    friend class MB_XmlNode;
    virtual void print();
    virtual bool queryNodesByName(const char* pName,cocos2d::CCArray* pArray){return false;}
    virtual cocos2d::CCArray* getChilden(){return NULL;}
private:
    cocos2d::CCString*     m_pAttributeName;
    cocos2d::CCString*     m_pValue;
};
#endif /* defined(__XmlManager__MB_XmlItems__) */
