//
//  MB_SuitActivateData.h
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-14.
//
//

#ifndef __ProjectMB__MB_SuitActivateData__
#define __ProjectMB__MB_SuitActivateData__

#include "Game.h"

/*
 <activate needAmount="2">
    <attr type="1" value="100" />
    <attr type="2" value="100" />
    <attr type="3" value="100" />
</activate>
 */
class MB_SuitActivateData:public CCObject
{
public:

    MB_SuitActivateData();

    virtual ~MB_SuitActivateData();

    bool getActivateAttr(CCArray* pArray);

    static MB_SuitActivateData* create(MB_XmlNode* pNode);

    virtual bool init(MB_XmlNode* pNode);

    CCNode* createActivatePanelByCount(uint32_t nCount,float width);
private:

    CC_SYNTHESIZE_READONLY(uint16_t, m_nNeedAmount, NeedAmount);
    CCArray*            m_pAttrArray;
};

#endif /* defined(__ProjectMB__MB_SuitActivateData__) */
