//
//  MB_ResearchInstituteInterface.h
//  ProjectPM
//
//  Created by chk on 14-4-14.
//
//

#ifndef __ProjectMB__MB_ResearchInstituteInterface__
#define __ProjectMB__MB_ResearchInstituteInterface__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"

class MB_ResearchInstituteInterface:public NSGameFunction::CCFunctionInterface
{
public:
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual void onLoadingScene();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    virtual void onEntryClicked(CCObject* pSender);
};

#endif /* defined(__ProjectMB__MB_ResearchInstituteInterface__) */
