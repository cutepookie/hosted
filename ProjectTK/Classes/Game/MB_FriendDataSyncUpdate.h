//
//  MB_FriendDataSyncUpdate.h
//  ProjectPM
//
//  Created by CRIMOON0073 on 14-7-1.
//
//

#ifndef __ProjectMB__MB_FriendDataSyncUpdate__
#define __ProjectMB__MB_FriendDataSyncUpdate__

/*
 李华超  11:32
 %%交配冷卻時間好友通知
 message recvhomestead_sync_mating_cool_second[id=20230]{
 required		int32			roleID							=1;
 required		int32			matingCoolSecond	=2;//交配冷卻結束時間
 }
 %%守護神变化好友通知
 message recvhomestead_sync_pet[id=20231]{
 required		int32			roleID							=1;
 required		int32			petTypeID					=2;//守護武將類型
 required		int16			petQuality					=3;//守護武將品质
 }
 %%充能狀態好友通知
 message recvhomestead_sync_add_enagy[id=20232]{
 required		int32				roleID						=1;
 required		int32				beginGold				=2[default=0];//充能(金幣)開始時間
 required		int32               endGold					=3[default=0];//充能(金幣)結束時間
 required		int32				beginBadge              =4[default=0];//充能(徽章)開始時間
 required		int32				endBadge				=5[default=0];//充能(徽章)結束時間
 }
 */

#define SC_HOMESTEAD_SYNC_MATING_COOL_SECOND    20230
#define SC_HOMESTEAD_SYNC_GER                   20231
#define SC_HOMESTEAD_SYNC_ADD_ENGRY             20232


#endif /* defined(__ProjectMB__MB_FriendDataSyncUpdate__) */
