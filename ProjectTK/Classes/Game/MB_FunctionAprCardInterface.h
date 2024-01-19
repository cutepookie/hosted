//
//  MB_FunctionAprCardInterface.h
//  ProjectMB
//
//  Created by yuanwugang on 15-3-10.
//
//

#ifndef __ProjectMB__MB_FunctionAprCardInterface__
#define __ProjectMB__MB_FunctionAprCardInterface__


#include "MB_FunctionModule.h"


class MB_AprCardData;
class MB_MsgBuffer;
class MB_FunctionAprCardInterface:public NSGameFunction::CCFunctionInterface
{
public:
    MB_FunctionAprCardInterface();
    ~MB_FunctionAprCardInterface();
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual void onLoadingScene();
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    
    
    void sendActivity_Month();
    void recvActivity_Month(MB_MsgBuffer* pRecv);
    void sendActivity_Month_Buy();
    void recvActivity_Month_Buy(MB_MsgBuffer* pRecv);
    void sendActivity_Month_Draw();
    void recvActivity_Month_Draw(MB_MsgBuffer* pRecv);
    
    MB_AprCardData* getAprCardData(){return m_pData;};
private:
    MB_AprCardData* m_pData;
};

#endif /* defined(__ProjectMB__MB_FunctionAprCardInterface__) */
