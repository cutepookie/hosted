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
class MB_IngotsShopEntry:public MB_NodeHoverEntry
{
public:
    MB_IngotsShopEntry();
    virtual ~MB_IngotsShopEntry();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onResetWnd();
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);

};


#endif /* defined(__ProjectMB__MB_MysteryShopEntry__) */
