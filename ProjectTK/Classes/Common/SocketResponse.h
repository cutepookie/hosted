
#ifndef __SOCKET_RESPONSE_H__
#define __SOCKET_RESPONSE_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "MB_MsgBuffer.h"

NS_CC_EXT_BEGIN


class SocketResponse : public CCObject
{
public:
    
    SocketResponse()
    {
        _responseData = new MB_MsgBuffer();
        _socketRequest = NULL;
        _succeed = false;
        time(&_startTime);
    };
    
    SocketResponse(SocketRequest* request)
    {
        _socketRequest = request;
        if (_socketRequest)
        {
            _socketRequest->retain();
        }
        
        _succeed = false;
        _responseData = new MB_MsgBuffer();
        time(&_startTime);
    }
    
    /** Destructor */
    virtual ~SocketResponse()
    {
        if (_socketRequest)
        {
            _socketRequest->release();
        }
        
        delete _responseData;

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
    inline void setResponseData(const char* buffer, unsigned int len)
    {
        _responseData->Write(buffer, len);
    };
    /** Get the request data pointer back */
    inline MB_MsgBuffer* getResponseData()
    {
        return _responseData;
    }
    /** Get the size of request data back */
    inline uint32_t getResponseDataSize()
    {
        return _responseData->GetLength();
    }
    
    inline SocketRequest* getSocketRequest()
    {
        return _socketRequest;
    }
    
    inline void setSucceed(bool value)
    {
        _succeed = value;
    }
    
    inline bool isSucceed()
    {
        return _succeed;
    }
    
    inline time_t getStartTime()
    {
        return _startTime;
    }
    
    
    
protected:
    // properties
    MB_MsgBuffer*          _responseData;      // used for POST
    SocketRequest*      _socketRequest;     // the corresponding SocketRequest pointer who leads to this response
    bool                _succeed;           // to indecate if the socket reqeust is successful reply
    time_t              _startTime;          // 等待反应時間
    
};

NS_CC_EXT_END

#endif //__SOCKET_RESPONSE_H__