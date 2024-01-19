

#ifndef _PayMentViewCocos2d_
#define _PayMentViewCocos2d_
#include "Game.h"
class PayMentViewCocos2d{
 
private:
    

    static PayMentViewCocos2d* s_PayMent;
  
    
public :

    PayMentViewCocos2d();
    ~PayMentViewCocos2d();
    void *payViewController;
    void *objobject;
    static PayMentViewCocos2d* sharedPayMentView();
    void setPayment(const char *productid);
    void removeCoord(const char *);
    void checkList();
    void loadFile();
    void saveFile();
    
};
#endif




