

#ifndef ProjectMB_Game_h
#define ProjectMB_Game_h
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include <libxml/parser.h>
#include <libxml/tree.h>
#include "MB_Aescrypt.h"
#include "cppjson.h"


#include "MB_MsgBuffer.h"
#include "MB_ClientSocket.h"
#include "MB_Audio.h"
#include "MB_XmlReader.h"
#include "MB_DirtyWordsCheck.h"
#include "MB_DefineProto.h"
#include "MB_LocalProto.h"
#include "MB_ResWindow.h"
#include "OCandCppHelper.h"
//struct
#include "MB_Message.h"
#include "MB_ServerList.h"
#include "MB_DefineProto.h"
#include "MB_ItemData.h"
#include "MB_FightData.h"
#include "MB_TeamData.h"
#include "MB_petData.h"
#include "MB_ActionData.h"
#include "MB_ShopData.h"
#include "MB_RoleData.h"
#include "MB_ChapterData.h"
#include "MB_NotificationData.h"
#include "MB_DataPVP.h"
#include "MB_DataTeamCompare.h"
#include "MB_DataShowPic.h"
#include "MB_DataFriend.h"
#include "MB_MoneyEevntData.h"
#include "MB_ShopData.h"
#include "MB_TutorialMgr.h"

#include "MB_LayerRoleLevelUp.h"


#include "MB_LayerInviteUnite.h"
#include "MB_LayerInvite.h"
#include "MB_LayerInviteHelp.h"
#include "MB_NodeItemUnit.h"
#include "MB_LayerItemUnionUnit.h"
#include "MB_LayerPetUnion.h"

#include "MB_TableCell.h"

#include "MB_NodeDamage.h"

//#include "MB_NodeDescription.h"
#include "MB_ActionMgr.h"

#include "MB_NodeDungeonUnit.h"

#include "MB_NodePet.h"
#include "MB_LayerPetTeam.h"
#include "MB_NodePetUnit.h"
#include "MB_LayerPetSell.h"
#include "MB_NodePetList.h"
#include "MB_LayerPetDetail.h"
#include "MB_NodePetCard.h"
#include "MB_NodeItem.h"


#include "MB_NodeUpdatePetList.h"
#include "MB_ItemCard.h"

#include "MB_LayerReportTop8.h"
#include "MB_NodeReportBox.h"

#include "MB_NodeLuckyPlayer.h"
#include "MB_LayerRewardOne.h"
#include "MB_LayerRewardMore.h"
#include "MB_LayerRoleInfoHeader.h"
#include "MB_LayerWarningHeader.h"
#include "MB_LayerPVPRanking.h"
#include "MB_SceneRegist.h"

#include "MB_NetStructFight.h"
#include "MB_SceneServerList.h"
#include "MB_SceneLoginBackground.h"
#include "MB_SceneLoading.h"
#include "MB_SceneMain.h"
#include "MB_SceneTeamCompare.h"

#include "MB_PublicNoticeData.h"
#include "MB_SceneRoleCreate.h"
#include "MB_GameInfo.h"
#include "MB_SceneReconnect.h"
#include "../Common/GameLib/CCGameLib.h"

#include "MB_CardStarConfig.h"
#include "MB_BattleConfigData.h"
#include "MB_SuitSystem.h"
#include "MB_ComposeSystem.h"




extern bool isAutoTanChuSign;
extern bool m_bIsDemoFight;
extern int m_bIsChangeRole;
extern char* change_appid;
extern char* change_channelid;
extern char* change_userid;
extern char* change_token;
extern const char* ChapterFileChar;
extern int m_bToPageID;
extern int m_bNowPassPageID;
extern bool m_bIsToHome;
extern bool m_bGlobalIsScaleAction;
extern bool global_isRePlay;
extern bool global_isYeShiJieToShop;
extern std::vector<uint64_t> teamV;
extern bool m_bIsCanToChapter;
extern uint16_t nowHomeShowPetTypeID;
extern bool m_IsCanRetryGame;
extern bool m_SceneGameIsSetLevelUI;
extern int m_SceneGameBigLevel;
extern int m_SceneGameLittleLevel;
extern const char* m_SceneGameLevelName;
extern CCNode* global_tutorialNode;
class MB_LayerPetEquipment;
class MB_SceneGame;
class MB_LayerItemDetail;
class MB_LayerBackpack;
extern MB_SceneGame* global_sceneGame;
extern MB_LayerPetEquipment* global_layerPetEquipment;
extern MB_LayerPetDetail* global_layerPetDetail;
extern MB_LayerItemDetail* global_layerItemDetail;
extern MB_LayerBackpack* global_layerBackpack;
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#define MB_LOG(format,...)       CCLOG(format,##__VA_ARGS__)
#define MB_LOGERROR(format,...)  CCLOGERROR(format,##__VA_ARGS__)
#define MB_LOGWARN(format,...)    do {} while (0)
#elif defined(DEBUG)

#define MB_LOG(format,...)       CCLOG(format,##__VA_ARGS__)
#define MB_LOGERROR(format,...)  CCLOGERROR(format,##__VA_ARGS__)
#define MB_LOGWARN(format,...)    do {} while (0)
#else
#define MB_LOG(format,...)
#define MB_LOGERROR(format,...)
#define MB_LOGWARN(format,...)
#endif

#ifdef DEBUG

// 時間輸出，测試性能消耗用
static struct timeval s_tStartTime;
static struct timeval s_tCurrentTime;

#define RECORD_TIME(str)                                        \
            gettimeofday(&s_tStartTime, NULL);                  \
            MB_LOG("%s start",str);

#define PRINT_TIME(str)                                                                                                         \
            gettimeofday(&s_tCurrentTime,  NULL);                                                                               \
            MB_LOG("%s cost: %f", str, CCTime::timersubCocos2d((struct cc_timeval *)&s_tStartTime, (struct cc_timeval *)&s_tCurrentTime)); \
            gettimeofday(&s_tStartTime, NULL);
#else

#define RECORD_TIME(str)

#define PRINT_TIME(str)

#endif  // DEBUG

#endif  // ProjectMB_Game_h
