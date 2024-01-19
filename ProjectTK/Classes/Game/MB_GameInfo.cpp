
#include "MB_GameInfo.h"
#include "MB_Message.h"
#include "MB_GameInfoEnum.h"

std::string MB_GameInfo::g_language = "汉语";

void MB_GameInfo::ShowWndTip (std::string filename,
                              uint16_t key,
                              std::string buttonname /*= "關閉"*/,
                              CCPoint* pos /*= NULL*/)
{
    std::string str;
    str = GetDescription(filename,key);
    MB_Message::sharedMB_Message()->showMessage(GET_GAMEINFO(kmGameInfo_Tip).c_str(), str.c_str(),
                                                buttonname.c_str(),
                                                NULL, NULL, NULL, NULL);
}
void MB_GameInfo::ShowWndTipLite (std::string filename,uint16_t key)
{
    std::string str;
    str = GetDescription(filename,key);
    MB_Message::sharedMB_Message()->showMessage(str.c_str());
}

std::string MB_GameInfo::GetDescription (std::string filename,uint16_t key)
{
    sDesCommon* pDc;
    pDc = MB_DescriptionCommonTable::getInstance().getDesCommon(filename, key);    
    return pDc?pDc->queryValue(g_language).toString():"";
}

std::string MB_GameInfo::GetConfigValue (std::string filename,uint16_t key ,std::string des)
{
    sDesCommon* pDc;
    pDc = MB_DescriptionCommonTable::getInstance().getDesCommon(filename, key);
    return pDc?pDc->queryValue(des).toString():"";
}

sDesCommon* MB_GameInfo::GetConfigCommon(std::string filename, uint16_t key)
{
    sDesCommon* pDc;
    pDc = MB_DescriptionCommonTable::getInstance().getDesCommon(filename, key);
    return pDc;
}