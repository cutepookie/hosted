//
//  CCEventListener.cpp
//  ProjectTK
//
//  Created by crimoon00007 on 14-2-28.
//
//

#include "CCEventListener.h"
using namespace NSGameFunction;

CCEventListener* CCEventListener::getInstance()
{
    if (m_pSingletonInstance == NULL)
    {
        m_pSingletonInstance = new CCEventListener;
    }

    return m_pSingletonInstance;
}

void CCEventListener::detroyInstance()
{
    CC_SAFE_RELEASE_NULL(m_pSingletonInstance);
}

CCEventListener::CCEventListener()
{

}

CCEventListener::~CCEventListener()
{

}

CCEventListener* CCEventListener::m_pSingletonInstance = NULL;