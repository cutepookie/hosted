
#ifndef ProjectMB_MB_GameInfoEnum_h
#define ProjectMB_MB_GameInfoEnum_h

enum kmGameInfo
{
    kmGameInfo_Buying = 0,//購買中
    kmGameInfo_BeEquip,   //已裝備
    kmGameInfo_StopCannotFightFailed,   //终止免戰失敗
    kmGameInfo_CannotFightOverTime, //免戰倒計時
    kmGameInfo_ComposeOverTime,//合成倒計時
    kmGameInfo_Win,   //勝利
    kmGameInfo_Failed,  //失敗
    kmGameInfo_FightWin,//戰胜了%s
    kmGameInfo_FightFailed,//戰敗於%s
    kmGameInfo_TakeSuccess,//成功獲得：
    kmGameInfo_TakeFailed,//未能獲得：
    kmGameInfo_RobCanTakeSth,//夺寶成功獲取【%s】
    kmGameInfo_StopCannotFight,//终止免戰
    kmGameInfo_StopCannotFightDes,//终止免戰信息
    kmGameInfo_ForceStop,//强行终止
    kmGameInfo_Cancel,//取消
    kmGameInfo_SpecialShopDesc,//奇遇商店描述
    kmGameInfo_UnSelectItem,    //未选中道具
    kmGameInfo_CallGeneralSingletonCost,//召喚單消耗
    kmGameInfo_CallGeneralDBCost,//召喚双消耗
    kmGameInfo_CallGeneralNotifyMessage,//【%s】幸运的獲得了极品：【%s】＊【%d】
    kmGameInfo_CallGeneralCannotTakeCardDes,//卡片已經被領取或者未進入召喚狀態
    kmGameInfo_Confirm,//確定
    kmGameInfo_Tip,//提示
    kmGameInfo_RankingDecayOvertime,//道具品階衰减倒計時：%d天:%d時:%d分%d:秒
    kmGameInfo_Sell_Success,//出售成功 獲得银两：%d
    kmGameInfo_Mail_Today,//当天
    kmGameInfo_Mail_Last,//%d天前
    kmGameInfo_Mail_Edit_InputName,//輸入名字
    kmGameInfo_Mail_Edit_InputContent,//輸入内容
    kmGameInfo_Pay,//儲值
    kmGameInfo_Shop_Buy_Forever,//無限購買
};

#endif
