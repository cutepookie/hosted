//
//  MB_FunctionEntery2ActivatyEntery.h
//  ProjectMB
//
//  Created by wenyong on 15-1-13.
//
//

#ifndef __ProjectMB__MB_FunctionEntery2ActivatyEntery__
#define __ProjectMB__MB_FunctionEntery2ActivatyEntery__

#include "MB_NodeSubActivatyEntry.h"

class MB_FunctionEntery2ActivatyEntery : public MB_NodeSubActivatyEntry
{
public:
    MB_FunctionEntery2ActivatyEntery();
    virtual bool init();
    virtual void onInitializedWnd();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual bool setFunction(NSGameFunction::CCFunctionInterface* pFunction);
    virtual void onEntranceClicked(CCObject* pSender);
    virtual int getActivityID();
    virtual void enter();
protected:
    int      m_nConvertedActivityID;
    NSGameFunction::CCFunctionInterface* m_pInterface;
};

#endif /* defined(__ProjectMB__MB_FunctionEntery2ActivatyEntery__) */
