
#ifndef ProjectMB_MB_GameInfo_h
#define ProjectMB_MB_GameInfo_h

#include "MB_DescriptionCommonTable.h"

#define GET_GAME_DESCRIPTION(filename,key)    MB_GameInfo::GetDescription(filename,key)
#define SHOW_WND_TIP(filename,key)            MB_GameInfo::ShowWndTip(filename,key,"关闭")
#define SHOW_WND_TIPLite(filename,key)        MB_GameInfo::ShowWndTipLite(filename,key)
#define GET_CONFIG_VALUE(filename,key,des)    MB_GameInfo::GetConfigValue(filename,key,des)
#define GET_GAMEINFO(key)                     MB_GameInfo::GetDescription("popup_message.xml",key)
#define GET_BACKGROUND(key)                   MB_GameInfo::GetConfigValue("BGM.xml",key,"filepath")
#define GET_CONFIG_COMMON(filename,key)       MB_GameInfo::GetConfigCommon(filename,key)
class MB_GameInfo
{
public:
    static void         ShowWndTip      (std::string filename,
                                         uint16_t key,
                                         std::string buttonname = "关闭",
                                         CCPoint* pos = NULL);
    static void         ShowWndTipLite     (std::string filename,
                                         uint16_t key);
    
    
    static std::string  GetDescription  (std::string filename,uint16_t key);
    
    static std::string  GetConfigValue  (std::string filename,uint16_t key,std::string des);
    
    static sDesCommon*  GetConfigCommon (std::string filename,uint16_t key);

    static std::string  g_language;//语言配置
};

#endif
