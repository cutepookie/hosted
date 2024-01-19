//
//  MB_DataExchange.h
//  ProjectPM
//
//  Created by cri-mac on 14-5-4.
//
//

#ifndef __ProjectMB__MB_DataExchange__
#define __ProjectMB__MB_DataExchange__

#include <string>
#include "cocos2d.h"
using namespace::cocos2d;

class NSDataExchange
{
public:
    static std::string g_LocationName;
    static bool g_bInCharge;
};
class MB_LayerRewardOne;
class MB_VideoMgr:public CCObject
{
    MB_VideoMgr();
public:
    static MB_VideoMgr* m_pShareVideoMgr;
    ~MB_VideoMgr();
    static MB_VideoMgr* getInstance();
    void playVideo(MB_LayerRewardOne* lro,int nStar);
    
    
    //视频播放完畢会调用
    void onFinishVideo();
    
    MB_LayerRewardOne* m_pLro;
};



#endif /* defined(__ProjectMB__MB_DataExchange__) */
