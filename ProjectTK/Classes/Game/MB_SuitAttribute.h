//
//  MB_SuitAttribute.h
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-14.
//
//

#ifndef __ProjectMB__MB_SuitAttribute__
#define __ProjectMB__MB_SuitAttribute__

#include "Game.h"

/*
 <attr type="1" value="100" />
 */
class MB_SuitAttribute:public CCObject
{
public:
    MB_SuitAttribute();

    virtual ~MB_SuitAttribute();

    bool init(MB_XmlNode* pNode);

    static MB_SuitAttribute* create(MB_XmlNode* pNode);

    const char* getAttrDescribe()const;

    CCLabelTTF* createAttrPanel(float fontSz=20.0f);
private:
    CC_SYNTHESIZE_READONLY(int, m_nType, Type);
    CC_SYNTHESIZE_READONLY(int, m_nValue, Value);
};

#endif /* defined(__ProjectMB__MB_SuitAttribute__) */
