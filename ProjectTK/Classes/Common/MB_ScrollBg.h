

#ifndef __ProjectMB__MB_ScrollBg__
#define __ProjectMB__MB_ScrollBg__
#include "Game.h"
using namespace std;
typedef enum {
    left_top,
    left_bottom,
    right_top,
    right_bottom,
} ScrollBgDiction;
class MB_ScrollBg:public CCNode
{
public:
    MB_ScrollBg(ScrollBgDiction _sbd,float _speed,int index);
    static MB_ScrollBg* create(ScrollBgDiction _sbd,float _speed,int index = 0);
    virtual bool init();
    void update(float dt);
    void createSpr(CCPoint p);
    ScrollBgDiction sbd;
    CCSize sprSize;
    CCSize winSize;
    float speed;
    int bgIndex;
};

#endif /* defined(__ProjectMB__MB_ScrollBg__) */
