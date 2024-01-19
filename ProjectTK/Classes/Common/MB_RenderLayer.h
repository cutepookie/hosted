//
//  MB_RenderLayer.h
//  ProjectPM
//
//  Created by crimoon on 14-7-1.
//
//

#ifndef __ProjectMB__MB_RenderLayer__
#define __ProjectMB__MB_RenderLayer__

#include "cocos2d.h"
using namespace  cocos2d;

class MB_RenderLayer {
    
    public :
    
        MB_RenderLayer();
        ~MB_RenderLayer();
        //filename 遮罩图片的名字， point 遮罩所在全局的位置
        static void setFileAndPos(CCSprite *sprite ,const char * filename ,CCPoint point,float scale);
};
class MB_RenderSprite: public CCSprite{

    private :
    
    bool isDraw;

    public :
    
    MB_RenderSprite();
    ~MB_RenderSprite();
    virtual bool init(const char * filename );
    static MB_RenderSprite * create(const char *filename);
    virtual void draw();

    
};
#endif /* defined(__ProjectMB__MB_RenderLayer__) */
