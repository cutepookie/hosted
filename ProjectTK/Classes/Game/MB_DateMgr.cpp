
#include "MB_DateMgr.h"

MB_DataMgr::MB_DataMgr()
{
    m_mapLayerWindowEx.clear();
    m_isReleased = false;
}

MB_DataMgr::~MB_DataMgr()
{
    m_mapLayerWindowEx.clear();
}

void MB_DataMgr::callUi(uint32_t message,cocos2d::CCObject *param)
{
//    mapLayerWindowEx_It it;
//    m_isReleased = false;
//    it = m_mapLayerWindowEx.begin();
//    while (it!=m_mapLayerWindowEx.end())
//    {
//        it->second->onMessage(message, param);
//        if(m_isReleased)
//            break;
//        it++;
//    }
}

MB_ResWindow* MB_DataMgr::getUi(std::string name)
{
    MB_ResWindow* ret;
    mapLayerWindowEx_It finder;
    finder  = m_mapLayerWindowEx.find(name);
    ret     = (finder != m_mapLayerWindowEx.end())? \
              finder->second:NULL;
    return ret;
}

void MB_DataMgr::RegisterUi(std::string name, MB_ResWindow *layer)
{
    //CCAssert(getUi(name) == NULL,"layer is existed! ")
    UnRegisterUi(name);
    m_mapLayerWindowEx.insert(std::make_pair(name, layer));
}

void MB_DataMgr::UnRegisterUi(std::string name)
{
    if(m_mapLayerWindowEx.find(name) != m_mapLayerWindowEx.end())
    {m_isReleased = true;m_mapLayerWindowEx.erase(name);}
}