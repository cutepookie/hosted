
#ifndef __ProjectMB__MB_XmlReader__
#define __ProjectMB__MB_XmlReader__

#include <iostream>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "MB_Aescrypt.h"
class MB_XmlReader{

    public :
    
        MB_XmlReader(){
    
        }
        ~MB_XmlReader(){
            
        }
        static xmlDocPtr readXml(const char *path);
        static void saveXml(const char *path);
    static xmlDocPtr readFromString(const char* pString);
};
#endif /* defined(__ProjectMB__MB_XmlReader__) */
