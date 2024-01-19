
#include "MB_XmlReader.h"
#include "cocos2d.h"

xmlDocPtr MB_XmlReader::readFromString(const char* pString)
{
    assert(pString);
    
    return xmlReadMemory(pString,strlen(pString),  NULL, "utf-8", XML_PARSE_RECOVER);
}

xmlDocPtr  MB_XmlReader::readXml(const char *path){


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    static char filename[1024];
    int length = strlen(path);
    strcpy(filename, path);
    for (int i = length -1;  i >= 0; i--) {
        
        if(filename[i] == '.'){
        
            filename[i+1] = 'c';
            filename[i+2] = 'b';
            filename[i+3] = '\0';
            break;
        }
    }
    FILE  *fp = fopen(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(filename).c_str(), "r");
    if(fp == 0){
    
        xmlDocPtr g_sharedDoc =  xmlReadFile(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(path).c_str(), "utf-8", XML_PARSE_RECOVER);
        return g_sharedDoc;
        
    }
    unsigned long size ;
    char *out =(char *) MB_Aescypt::decrypt_stream(fp,&size);
    xmlDocPtr g_sharedDoc = xmlReadMemory(out,size,  NULL, "utf-8", XML_PARSE_RECOVER);
    CC_SAFE_DELETE_ARRAY(out);
    return g_sharedDoc;
    
#else  
    
    static char filename[1024];
    int length = strlen(path);
    strcpy(filename, path);
    for (int i = length -1;  i >= 0; i--) {
        
        if(filename[i] == '.'){
            
            filename[i+1] = 'c';
            filename[i+2] = 'b';
            filename[i+3] = '\0';
            break;
        }
    }
    unsigned long size ;
    char* pBuff = (char*)cocos2d::CCFileUtils::sharedFileUtils()->getFileData(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(filename).c_str(),"r", &size  );
    if(pBuff == NULL){

        FILE  *fp = fopen(filename, "r");
        if(fp == 0){
            
            xmlDocPtr g_sharedDoc =  xmlReadFile(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(path).c_str(), "utf-8", XML_PARSE_RECOVER);
            return g_sharedDoc;
        }
        char *out =(char *) MB_Aescypt::decrypt_stream(fp,&size);
        xmlDocPtr g_sharedDoc = xmlReadMemory(out,size,  NULL, "utf-8", XML_PARSE_RECOVER);
        CC_SAFE_DELETE_ARRAY(out);
        return g_sharedDoc;

    }
    char *out  = (char *) MB_Aescypt::decrypt_stream(pBuff,&size  );
    xmlDocPtr g_sharedDoc = xmlReadMemory(out,size,  NULL, "utf-8", XML_PARSE_RECOVER);
    CC_SAFE_DELETE_ARRAY(pBuff);
    return g_sharedDoc;    
#endif

}
void MB_XmlReader::saveXml(const char *path){

}