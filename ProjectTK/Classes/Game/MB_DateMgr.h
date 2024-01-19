
#ifndef __ProjectMB__MB_DateMgr__
#define __ProjectMB__MB_DateMgr__
#include "cocos2d.h"
#include "MB_ResWindow.h"

#define PopupPauseMsgBox MB_Message::sharedMB_Message()->showMessage(GET_GAMEINFO(kmGameInfo_Buying).c_str(),15, NULL);
#define ClosePauseMsgBox MB_Message::sharedMB_Message()->removeALLMessage();

class MB_DataMgr:public CCObject
{
public:
    typedef  std::map<std::string,MB_ResWindow*> mapLayerWindowEx;
    typedef  mapLayerWindowEx::iterator  mapLayerWindowEx_It;
    
    //register ui
    void     RegisterUi  (std::string name,MB_ResWindow* layer);
    void     UnRegisterUi(std::string name);
    
protected:
             MB_DataMgr();
    virtual ~MB_DataMgr();
public:
    void                callUi (uint32_t message,cocos2d::CCObject *param);
    MB_ResWindow*   getUi  (std::string name);
private:
    mapLayerWindowEx    m_mapLayerWindowEx;
    bool                m_isReleased;
};
#endif /* defined(__ProjectMB__MB_DateMgr__) */
