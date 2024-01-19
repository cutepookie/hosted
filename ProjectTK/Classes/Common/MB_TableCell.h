
#ifndef __ProjectMB__MB_TableCell__
#define __ProjectMB__MB_TableCell__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../Game/MB_ResWindow.h"
using namespace cocos2d;
using namespace cocos2d::extension;
class MB_TableCell: public  MB_ResWindow{
    
public:
   
    MB_TableCell();
    virtual ~MB_TableCell();
    static MB_TableCell* create();
    bool  init();
    virtual bool  checkInTouch(CCPoint worldPoint);
    virtual void activate();
    virtual void selected();
    virtual void unselected();
    CC_SYNTHESIZE(bool, m_pIsTouchEnable, IsTouchEnable);

};

#endif /* defined(__ProjectMB__MB_TableCell__) */
