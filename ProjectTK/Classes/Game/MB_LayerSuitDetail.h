//
//  MB_LayerSuitDetail.h
//  ProjectPM
//
//  Created by WenYong on 14-6-5.
//
//

#ifndef __ProjectMB__MB_LayerSuitDetail__
#define __ProjectMB__MB_LayerSuitDetail__

#include "cocos2d.h"
USING_NS_CC;

class MB_LayerSuitDetail : public CCLayer
{
public:
    MB_LayerSuitDetail();
    static MB_LayerSuitDetail* create(uint64_t uid);
    static MB_LayerSuitDetail* createByTid(uint16_t tid);
    
    bool setUid(uint64_t uid);
    bool setTid(uint16_t tid);
    void reset();
protected:
    void resetByUid();
    void resetByTID(uint16_t tid);
    bool itemHasActivated(uint16_t tid);
private:
    int         m_nSuitID;
    uint64_t    m_nSuitUID;
    uint16_t    m_nSuitTID;
};

#endif /* defined(__ProjectMB__MB_LayerSuitDetail__) */
