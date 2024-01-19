//
//  MB_FunctionModule.h
//  ProjectPM
//
//  Created by WenYong on 14-3-26.
//
//

#ifndef ProjectMB_MB_FunctionModule_h
#define ProjectMB_MB_FunctionModule_h
#include "MB_PveModule.h"
#include "MB_PvpModule.h"
#include "MB_FunctionMgr.h"
#include "MB_FunctionConfig.h"
#include "../Common/GameLib/CCGameLib.h"
enum FunctionType
{
    //悬浮
    kFunctionDaily          = 101,      //簽到
    kFunctionActivaty       = 102,      //配置活動 (主界面)
    kFunctionIngotsShop     = 103,      //VIP禮包
    kFunctionPayShop        = 104,      //儲值
    kFunctionEmail          = 105,      //邮箱
    kFunctionPic            = 106,      //图鉴
    kActivatyRecoverEnergy  = 107,      //補充能量
    kActivatyChangeCoin     = 108,      //招財
    kFunctionYeShiJie       = 109,      //夜世界
    kActivatyGifts          = 110,      //禮包
    kFunctionAprCard        = 111,      //月卡
    kFunctionGongGao        = 112,      //公告
    kFunctionJianShang      = 113,      //鉴赏
    //建筑
    kFunctionCompose        = 201,      //合成炉            合成
    kFunctionItemShop       = 202,      //道具商店
    kFunctionToy            = 203,      //扭蛋
    kFunctionPetPackage     = 204,      //精靈仓库
    kFunctionBackpack       = 205,      //道具仓库（整合道具 和 裝備）
    kFunctionAchievement    = 206,      //成就入口
    kFunctionRefreshShop    = 207,      //刷新商店   MB 新加功能
    kFunctionTask           = 208,      //任務              任務
    kFunctionMysteryShop    = 209,      //神秘商店
    kFunctionRanking        = 210,      //排行榜
    
    //副本
    kFunctionResearchInstitute  = 401,  //研究所          （戰南蛮） (超梦)
    kFunctionBudokan            = 402,  //道观
    kFunctionArena              = 403,  //競技场           (爭霸)
    kFunctionPerfectRace        = 404,  //超梦邀請賽 （華麗大賽）         (称帝)
    kFunctionRuleFight          = 405, //秩序戰场
    kFunctionTrainerRoad        = 406, //訓練師之路
    kFunctionKing               = 407, //精靈王
    kFunctionTrainerTrove       = 408, //訓練師寶库(金幣副本)
    kFunctionNoRuleFight        = 409, //大乱鬥

    
    //下放功能按钮
    kFunctionHome               = 301,  // 主頁
    kFunctionFormation          = 302,  // 隊形
    kFunctionAbsolved           = 303,  // 剧情挑战
    kFunctionRoom               = 304,  // 房间
    kFunctionBigWorld           = 305,  // 副本
    kFunctionFriend             = 306,  // 好友
    kFunctionMaoXian            = 307,  // 冒险
    
    
    //暂時不開放的功能
//    kFunctionKing           = 102,      // 精靈王            拜皇帝
    kFunction3v3                = 206,  // 3v3
    kFunctionWorldWar           = 207,  // 异星大戰
    
    // 自定义活動
    kFunctionFestival           = 601,  // 春節活動
    kFunctionValentineDay       = 602,  // 情人節活動
    kFunctionDrawCard           = 603,  // 翻牌抽裝備
    kFunctionUnknow,
    
    
    //其他
    kFunctionGuard              = 701   //精靈守護
};

enum ActivatyType
{
    kActivatyChat               = 503,  //聊天
    kActivatyConfig             = 504,  //配置活動  (子活動)
    kActivatyUnknow
};

#endif
