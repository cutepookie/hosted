
#include "MB_DirtyWordsCheck.h"
#include "MB_XmlReader.h"
MB_DirtyWordsCheck*  MB_DirtyWordsCheck::s_pData = NULL ;

void  MB_DirtyWordsCheck::initWords(){

    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/dirtywords.xml");
    
    if (!g_sharedDoc)
    {
        return;
    }
    xmlNodePtr root;    
    root=xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    while(curNode != NULL) {
        
        if (xmlStrcmp(curNode->name,BAD_CAST "dirtyword")) {
            curNode = curNode->next;
            continue;
        }
        struct _xmlAttr * attr = curNode->properties;
        if (attr&&!xmlStrcmp(attr->name,BAD_CAST "word"))
        {
            value = (char*)xmlNodeGetContent(attr->children);
            CCString *str = CCString::create(value);
            m_pArray->addObject(str);
            CC_SAFE_FREE(value);
            attr = attr->next;
        }
        curNode = curNode->next;
    }
    
    xmlFreeDoc(g_sharedDoc);
}
MB_DirtyWordsCheck::MB_DirtyWordsCheck(){

    m_pArray = new CCArray();
    initWords();
}
MB_DirtyWordsCheck::~MB_DirtyWordsCheck(){

    CC_SAFE_DELETE(m_pArray);
}
MB_DirtyWordsCheck *  MB_DirtyWordsCheck::getInstance(){

    if(s_pData == NULL){
    
        s_pData  = new MB_DirtyWordsCheck();
    }
    return s_pData;
}
void  MB_DirtyWordsCheck::destroyInstance(){

    if(s_pData != NULL){
    
        delete s_pData;
        s_pData = NULL;
    }
}
bool MB_DirtyWordsCheck::checkDatabuf(const char * databuf){
    if(databuf == NULL)return true;
    CCObject *str;
    std::string check = databuf;
    CCARRAY_FOREACH(m_pArray, str){
    
        if(check.find(((CCString *)str)->getCString()) != std::string::npos){
            
            return true;
        }
    }
    return false;
}
void MB_DirtyWordsCheck::replaceDirtys(std::string *checkstr){
    CCObject  *str;
    char replace[128];
    CCARRAY_FOREACH(m_pArray, str){
       
        int pos = 0 ;
        const char * src = ((CCString *)str)->getCString();
        int srclen = strlen(src);
        for (int i =0 ; i <srclen ; i++) {
         
            replace[i] = '*';
        }
        replace[srclen] = '\0';
        while( (pos =checkstr->find(src, pos)) != std::string::npos )
        {
            
            checkstr->replace(pos, srclen, replace);
            pos += srclen;
        }
        
    }

}
