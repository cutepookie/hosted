//
//  CCEventListener.h
//  ProjectTK
//
//  Created by crimoon00007 on 14-2-28.
//
//

#ifndef __ProjectTK__CCEventListener__
#define __ProjectTK__CCEventListener__

#include "Game.h"

typedef void (CCObject::*SEL_CallFuncD)(CCNode*, void*);
#define callfuncD_selector(_SELECTOR) (SEL_CallFuncD)(&_SELECTOR)

namespace NSGameFunction
{
    class CCCallBackObject:public CCObject
    {
    public:
        virtual ~CCCallBackObject();
        CCCallBackObject();
        void execute(void* param);
    private:
        SEL_CallFuncD   m_pFunction;
        CCObject*       m_pOwner;
    };
    
    class CCEventListener:public CCObject
    {
    public:
        static CCEventListener* getInstance();
        static void detroyInstance();
    private:
        CCEventListener();
        virtual ~CCEventListener();
    private:
        static CCEventListener* m_pSingletonInstance;
    };
};

#endif /* defined(__ProjectTK__CCEventListener__) */
