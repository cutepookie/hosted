
#include "Game.h"
#include "MB_DescriptionCommonTable.h"

MB_DescriptionCommonTable::MB_DescriptionCommonTable()
{
    loadConfig("config/description/config.xml");
}

MB_DescriptionCommonTable::~MB_DescriptionCommonTable()
{
    desTable_It it = m_desTable.begin();
    while (m_desTable.end() != it)
    {
        CC_SAFE_DELETE(it->second);
        it++;
    }
    m_desTable.clear();
}

sDesCommon* MB_DescriptionCommonTable::getDesCommon (std::string file,uint16_t key)
{
    sDesCommon* ret     = NULL;
    desTable_It finder  = m_desTable.find(file);
    ret = (finder != m_desTable.end())? \
          finder->second->getDesCommon(key):NULL;
    return ret;
}

void MB_DescriptionCommonTable::loadConfig (std::string file)
{
    xmlDocPtr    g_sharedDoc;
  
    g_sharedDoc = MB_XmlReader::readXml(file.c_str());
                              
    if (g_sharedDoc)
    {
        xmlNodePtr        curNode;
        _xmlAttr *        attr;
        curNode = xmlDocGetRootElement(g_sharedDoc);
        curNode = curNode->xmlChildrenNode;
        char* value;
                                  
        while(curNode)
        {
            attr = curNode->properties;
                                      
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "path"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                loadDesCommon(value);
                CC_SAFE_FREE(value);
            }
            curNode = curNode->next;
        }
        xmlFreeDoc(g_sharedDoc);
    }
}

void MB_DescriptionCommonTable::loadDesCommon(std::string file)
{
    MB_DescriptionCommon* pdes = new MB_DescriptionCommon();
    pdes->load("config/description/"+file);
    m_desTable.insert(std::make_pair(file,pdes));
}