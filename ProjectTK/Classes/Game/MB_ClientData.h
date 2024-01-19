//
//  MB_ClientData.h
//  ProjectPM
//
//  Created by WenYong on 14-4-15.
//
//

#ifndef ProjectMB_MB_ClientData_h
#define ProjectMB_MB_ClientData_h
#include "cocos2d.h"
USING_NS_CC;
class MB_XmlNode;

class MB_ClientData:public CCObject
{
public:
    virtual bool init(MB_XmlNode* pNode) = 0;
};

#endif
