//
//  MB_PayShopEntry
//  ProjectMB
//
//  Created by chenhongkun on 14-9-1.
//
//

#ifndef __ProjectMB__MB_MysteryShopEntry__
#define __ProjectMB__MB_MysteryShopEntry__
#include "MB_NodeHoverEntry.h"
class MB_PayShopEntry:public MB_NodeHoverEntry
{
public:
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onEntranceClicked(CCObject* pSender);
};


#endif /* defined(__ProjectMB__MB_MysteryShopEntry__) */
