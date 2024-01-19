
#include "Game.h"
#include "MB_DescriptionCommon.h"


MB_DescriptionCommon::MB_DescriptionCommon()
{
    m_isInit   = false;
}
MB_DescriptionCommon::~MB_DescriptionCommon()
{
    desCommonMap_It it = m_desCommonMap.begin();
    while (m_desCommonMap.end() != it)
    {
        CC_SAFE_DELETE(it->second);
        it++;
    }
    m_desCommonMap.clear();
}

void MB_DescriptionCommon::load (std::string file)
{
    if (!m_isInit)
    {
        xmlDocPtr    g_sharedDoc;
        CCFileUtils* pfileutils;
        
        m_isInit    = true;

        pfileutils  = CCFileUtils::sharedFileUtils();
        g_sharedDoc = MB_XmlReader::readXml(file.c_str());
        
        if (g_sharedDoc)
        {
            xmlNodePtr      curNode;
            sDesCommon*     desCommon;
            
            curNode = xmlDocGetRootElement(g_sharedDoc);
            curNode = curNode->xmlChildrenNode;
            char*    value;
            uint16_t key;
            
            while(curNode)
            {
                struct _xmlAttr * attr = curNode->properties;
                
                if(attr)
                {
                    desCommon   = new sDesCommon();
                    value       = (char*)xmlNodeGetContent(attr->children);
                    key         = atoi(value);
                    CC_SAFE_FREE(value);
                    //next
                    attr        = attr->next;
                    while (attr)
                    {
                        std::string namekey;
                        namekey = (char*)(attr->name);
                        value   = (char*)xmlNodeGetContent(attr->children);
                        desCommon->insertPair(namekey,
                                              value);
                        CC_SAFE_FREE(value);
                        attr = attr->next;
                    }
                    
                    m_desCommonMap.insert(std::make_pair(key,desCommon));
                }
                
                curNode = curNode->next;
            }
            xmlFreeDoc(g_sharedDoc);
        }
    }
}

sDesCommon* MB_DescriptionCommon::getDesCommon (uint16_t key)
{
    return contains(key)?m_desCommonMap[key]:NULL;
}

bool MB_DescriptionCommon::contains (uint16_t key)
{
    desCommonMap_It finder = m_desCommonMap.find(key);
    return finder != m_desCommonMap.end();
}
