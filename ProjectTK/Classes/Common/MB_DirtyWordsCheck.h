
#ifndef __ProjectMB__MB_DirtyWordsCheck__
#define __ProjectMB__MB_DirtyWordsCheck__

#include "cocos2d.h"
using namespace cocos2d;
class MB_DirtyWordsCheck{
    
private:
    
    static  MB_DirtyWordsCheck* s_pData ;
    void initWords();
    CCArray *m_pArray;
    
public:
   
    MB_DirtyWordsCheck();
    ~MB_DirtyWordsCheck();
    
    static MB_DirtyWordsCheck * getInstance();
    static void destroyInstance();
    bool  checkDatabuf(const char * databuf);
    void  replaceDirtys(std::string *checkstr);
};
#endif /* defined(__ProjectMB__MB_DirtyWordsCheck__) */
