//
//  MB_RandomComposePlatform.h
//  ProjectPM
//
//  Created by cri-mac on 14-5-9.
//
//

#ifndef __ProjectMB__MB_RandomComposePlatform__
#define __ProjectMB__MB_RandomComposePlatform__

#include "MB_LayerComposePlatform.h"
class MB_RandomComposePlatform:public MB_LayerComposePlatform
{
public:
    
    static MB_RandomComposePlatform* create(int nType);
    virtual bool init(uint16_t nComposeID,int nType);
protected:
    virtual void onCloseClicked(CCObject*);
    virtual void setType(int type);
};

#endif /* defined(__ProjectMB__MB_RandomComposePlatform__) */
