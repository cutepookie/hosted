//
//  MB_LayerServerContainer.h
//  ProjectMB
//
//  Created by wenyong on 14-8-28.
//
//

#ifndef __ProjectMB__MB_LayerServerContainer__
#define __ProjectMB__MB_LayerServerContainer__

#include "cocos2d.h"
USING_NS_CC;

class MB_LayerServerContainer : public CCLayer
{
public:
    static MB_LayerServerContainer* create(uint16_t begin, uint16_t end);
    void resetRange(uint16_t begin, uint16_t end);
};

#endif /* defined(__ProjectMB__MB_LayerServerContainer__) */
