
#ifndef __SOCKET_REQUEST_H__
#define __SOCKET_REQUEST_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "MB_MsgBuffer.h"

NS_CC_EXT_BEGIN


class SocketRequest : public CCObject
{
public:
    
    SocketRequest()
    {
        _requestData = new MB_MsgBuffer();
        _tag = 0;
        _pTarget = NULL;
        _pSelector = NULL;
    };
    
    /** Destructor */
    virtual ~SocketRequest()
    {

//        修改為注册和注销方式,不再需要用count數来记录
//        if (_pTarget)
//        {
//            _pTarget->release();
//        }
        
        delete _requestData;
    };
    
    /** Override autorelease method to avoid developers to call it */
    CCObject* autorelease(void)
    {
        CCAssert(false, "SocketResponse is used between network thread and ui thread \
                 therefore, autorelease is forbidden here");
        return NULL;
    }
            
    // setter/getters for properties
     
    /** Option field. You can set your post data here
     */
    inline void setRequestData(const char* buffer, unsigned int len)
    {
        _requestData->Write(buffer, len);
    };
    /** Get the request data pointer back */
    inline MB_MsgBuffer* getRequestData()
    {
        return _requestData;
    }
    /** Get the size of request data back */
    inline int getRequestDataSize()
    {
        return _requestData->GetLength();
    }
    /** Required field. You should set the callback selector function at ack the http request completed
     */
    inline void setResponseCallback(CCObject* pTarget, SEL_CallFuncND pSelector)
    {
        _pTarget = pTarget;
        _pSelector = pSelector;
        //修改為注册和注销方式,不再需要用count數来记录
//        if (_pTarget)
//        {
//            _pTarget->retain();
//        }
    }
    /** Get the target of callback selector funtion */
    inline CCObject* getTarget()
    {
        return _pTarget;
    }
    /** Get the selector function pointer */
    inline SEL_CallFuncND getSelector()
    {
        return _pSelector;
    }
    /** Option field. You can set a unsigned short protocol tag to identify your request */
    inline void setTag(uint16_t tag)
    {
        _tag = tag;
    };
    /** Get the string tag back to identify the request.
     The best practice is to use it in your MyClass::onMyHttpRequestCompleted(sender, HttpResponse*) callback
     */
    inline uint16_t getTag()
    {
        return _tag;
    };

protected:
    // properties
    MB_MsgBuffer*              _requestData;       // used for POST
    uint16_t                  _tag;               // user defined tag, to identify different requests in response callback
    CCObject*               _pTarget;           // callback target of pSelector function
    SEL_CallFuncND          _pSelector;         // callback function,
                                                // e.g. MyLayer::onHttpResponse(CCObject *sender, void *data)
    
};

NS_CC_EXT_END

#endif //__SOCKET_REQUEST_H__
