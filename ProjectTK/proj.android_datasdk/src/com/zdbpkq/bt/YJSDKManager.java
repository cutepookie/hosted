package com.zdbpkq.bt;

import java.util.UUID;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.datasdk.Extend;
import com.datasdk.entity.GameRoleInfo;
import com.datasdk.entity.OrderInfo;
import com.datasdk.entity.UserInfo;
import com.datasdk.notifier.ExitNotifier;
import com.datasdk.notifier.InitNotifier;
import com.datasdk.notifier.LoginNotifier;
import com.datasdk.notifier.LogoutNotifier;
import com.datasdk.notifier.SwitchAccountNotifier;

import android.R.bool;
import android.R.string;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.DialogInterface.OnClickListener;
import android.content.pm.PackageInfo;
import android.net.Uri;
import android.os.Handler;
import android.os.Message;
import android.os.Process;
import android.text.TextUtils;
import android.util.Log;

//import com.sina.weibo.sdk.utils.Util;

public class YJSDKManager extends CommonSdkManager {
	private static String TAG = "sfwarning";
	private Handler mHandler = null;
	private final int MSG_LOGIN = 0;
	private final int MSG_PAY = 1;
	private final int MSG_TO_LOGIN = 2;
	private final int MSG_TO_LOGOUT = 3;
	private final int MSG_TO_EXIT = 4;
	private final int MSG_TO_CREATE_ROLE = 5;
	private final int MSG_TO_ENTER_GAME = 6;
	private final int MSG_TO_LEVEL_UP = 7;
	private final int MSG_TO_CHANGE_ROLE = 8;
	private final int app_id = 5509377;
	private final int cp_id = 22703;
	private final int server_id = 0;

	String appId;
	String channelId;
	String userId;
	String token;
	int amount = 0;
	int serverId = 0;
	String roleId = "";
	String payInfo = "";

	String roleName = "";
	int roleLevel = 0;
	String serverName = "";
	int vipLevel = 0;
	static boolean IsLoginOK = false;

	public YJSDKManager() {
		com.datasdk.DataSdk.getInstance()
				// 1.设置初始化通知(必接)
				.setInitNotifier(new InitNotifier() {

					@Override
					public void onSuccess() {
						Log.d(TAG, "SDK初始化成功");
					}

					@Override
					public void onFailed(String message, String trace) {
						Log.d(TAG, "SDK初始化失败:" + message);
					}
				})
				// 2.设置登录通知(必接)
				.setLoginNotifier(new LoginNotifier() {

					@Override
					public void onSuccess(final UserInfo userInfo) {
						// 登录成功，获取到用户信息userInfo
						// 通过userInfo中的UID、token做服务器登录认证
						System.out.println("sdk login  success...........................");
						System.out.println("getPlatformUid=" + userInfo.getPlatformUid());
						System.out.println("getPlatformUsername=" + userInfo.getPlatformUsername());
						System.out.println("getUID=" + userInfo.getUID());
						System.out.println("getUserName=" + userInfo.getUserName());
//						System.out.println("getToken=" + userInfo.getToken());

						System.out.println("onLoginSuccess");

						// 跳转到游戏界面
						((Cocos2dxActivity) ProjectMB.getContext()).runOnGLThread(new Runnable() {
							public void run() {
								// do something
								YJSDKManager.IsLoginOK = true;
								// 登陆成功回调
								String appId = ProjectMB.ProductKey;
								String channelId = Extend.getInstance().getExtrasConfig("channel");
								if (channelId == null || channelId.equals("")) {
									channelId = Extend.getInstance().getChannelType() + "";
								}

								System.out.println("channelId..........................." + channelId);

								String userId = userInfo.getUID();
								String token = userInfo.getToken();
								if (token.length() == 0) {
									token = "0";
								}
//								Log.i("main", "token -> " + token.length());
								login(appId, channelId, userId, token);
							}
						});
					}

					@Override
					public void onCancel() {
						Log.d(TAG, "取消登陆");
					}

					@Override
					public void onFailed(final String message, String trace) {
						Log.d(TAG, "登陆失败:" + message);
					}

				})
				// 3.设置注销通知(必接)
				.setLogoutNotifier(new LogoutNotifier() {

					@Override
					public void onSuccess() {
						Log.d(TAG, "注销成功");
						// TODO 进行游戏注销的处理
						mHandler.sendEmptyMessage(MSG_TO_LOGOUT);
					}

					@Override
					public void onFailed(String message, String trace) {
						Log.d(TAG, "注销失败:" + message);
					}
				})
				// 4.设置切换账号通知（必接）
				.setSwitchAccountNotifier(new SwitchAccountNotifier() {
					@Override
					public void onSuccess(UserInfo userInfo) {
						// TODO 进行登录验证、游戏注销、游戏登录的处理
						mHandler.sendEmptyMessage(MSG_TO_LOGOUT);
					}

					@Override
					public void onCancel() {

					}

					@Override
					public void onFailed(String s, String s1) {

					}
				})
				// 5.设置退出通知(必接)
				.setExitNotifier(new ExitNotifier() {

					@Override
					public void onSDKExit() {
						// TODO SDK已退出，进行游戏退出的处理
						android.os.Process.killProcess(Process.myPid());
					}

					@Override
					public void onNoExiterProvide() {
						gameExit();
					}
				});

		mHandler = new Handler() {

			public void handleMessage(Message msg) {

				switch (msg.what) {

				case MSG_TO_LOGIN: {
					com.datasdk.User.getInstance().login((ProjectMB) ProjectMB.getContext());
				}
					break;
				case MSG_TO_LOGOUT: {
					((ProjectMBApp) (((ProjectMB) ProjectMB.getContext()).getApplicationContext()))
							.restartApplication();
				}
					break;
				case MSG_PAY: {
					// 创建Payment对象，用于传递充值信息 //初始化测试数据

					// 设置金额
					String customerorderId = encodeUrl(serverId + "|" + roleId);
					String productname = "宝石";
					if (payInfo.equals("11011")) {
						productname = "月卡";
					}

					OrderInfo orderInfo = new OrderInfo();
					orderInfo.setAmount(Double.valueOf(amount));// 购买商品的总金额
					orderInfo.setCpOrderID(UUID.randomUUID().toString().replace("-", "") + roleId);// cp订单号
					orderInfo.setCount(1); // 商品数量
					orderInfo.setExtrasParams(customerorderId);// 拓展参数，会在支付回调时原样返回
					orderInfo.setGoodsID(payInfo);// 商品id
					orderInfo.setGoodsName(productname);// 商品名称，该参数是玩家购买商品时看到的商品名，请确保合理且唯一
					GameRoleInfo roleInfo = new GameRoleInfo();
					roleInfo.setServerID(String.valueOf(serverId));// 服务器 ID
					roleInfo.setServerName(serverName);// 服务器名称
					roleInfo.setGameRoleName(roleName);// 角色名称
					roleInfo.setGameRoleLevel(String.valueOf(roleLevel)); // 设置游戏角色等级，
					roleInfo.setGameRoleID(roleId);// 角色 ID
					roleInfo.setVipLevel(String.valueOf(vipLevel)); // 设置当前用户
																	// vip
																	// 等级，必须为整型字符串
					roleInfo.setGameBalance("0"); // 角色现有游戏币,若游戏无此字段请传入定值
					roleInfo.setPartyName("无帮派"); // 设置帮派，公会名称；若游戏无此字段请传入"无帮派"
					// 调用sdk支付接口
					com.datasdk.Payment.getInstance().pay((ProjectMB) ProjectMB.getContext(), orderInfo, roleInfo);
				}
					break;
				case MSG_TO_EXIT: {
					com.datasdk.Sdk.getInstance().exit((ProjectMB) ProjectMB.getContext());
				}
					break;
				case MSG_TO_CREATE_ROLE: {
					submitExtendData(true, false);
				}
					break;

				case MSG_TO_ENTER_GAME: {
					submitExtendData(false, false);
				}
					break;
				case MSG_TO_LEVEL_UP: {
					submitExtendData(false, true);
				}
					break;
				case MSG_TO_CHANGE_ROLE: {
					goChangeRole(appId, channelId, userId, token);
				}
					break;
				}
				super.handleMessage(msg);
			}
		};

	}

	public static String encodeUrl(String url) {
		return Uri.encode(url, "-![.:/,%?&=]");
	}

	public void submitExtendData(boolean isCreateRole, boolean isLeveUp) {
		try {
			GameRoleInfo roleInfo = new GameRoleInfo();
			roleInfo.setServerID(String.valueOf(serverId));// 服务器 ID
			roleInfo.setServerName(serverName);// 服务器名称
			roleInfo.setGameRoleName(roleName);// 角色名称
			roleInfo.setGameRoleLevel("2"); // 设置游戏角色等级，
			roleInfo.setGameRoleID(roleId);// 角色 ID
			roleInfo.setVipLevel(String.valueOf(vipLevel)); // 设置当前用户 vip
															// 等级，必须为整型字符串
			roleInfo.setGameBalance("0"); // 角色现有游戏币,若游戏无此字段请传入定值
			roleInfo.setPartyName("无帮派"); // 设置帮派，公会名称；若游戏无此字段请传入"无帮派"
			if (isCreateRole) {
				roleInfo.setRoleCreateTime(String.valueOf(System.currentTimeMillis())); // 值为位数时间戳
			}
			// 调用sdk上报角色接口
			com.datasdk.User.getInstance().setGameRoleInfo((ProjectMB) ProjectMB.getContext(), roleInfo, isCreateRole,
					isLeveUp);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public native void login(String appId, String channelId, String userId, String token);

	public native void goLogout();

	public native void goChangeRole(String appId, String channelId, String userId, String token);

	public native void payCancel();

	public native void payFail();

	public native void removeLoading();

	public native void playVideo();

	public static YJSDKManager instance() {

		if (mSharedManager == null) {

			mSharedManager = new YJSDKManager();
		}
		return (YJSDKManager) mSharedManager;
	}

	public void destroySDK(ProjectMB context) {

	}

	public void gologin() {

		try {

			mHandler.sendEmptyMessage(MSG_TO_LOGIN);

		} catch (Exception e) {

			Log.e("error", e.getMessage());
		}

	}

	public void logout() {

		try {

			mHandler.sendEmptyMessage(MSG_TO_LOGOUT);

		} catch (Exception e) {

			Log.e("error", e.getMessage());
		}
	}
	public void quitGame() {
		System.exit(0);
	}
	public String getRoleName() {

		return roleName;
	}

	public void pay(int amount, int serverid, String roleid, String payinfo) {
		try {
			this.amount = amount;
			this.serverId = serverid;
			this.roleId = roleid;
			this.payInfo = payinfo;
			mHandler.sendEmptyMessage(MSG_PAY);

		} catch (Exception e) {

			Log.e("error", e.getMessage());
		}
	}

	public void createRole(String roleId, String roleName, int roleLevel, int ServerId, String ServerName,
			int vipLevel) {
		this.roleId = roleId;
		this.roleName = roleName;
		this.roleLevel = roleLevel;
		this.serverId = ServerId;
		this.serverName = ServerName;
		this.vipLevel = vipLevel;
		try {
			mHandler.sendEmptyMessage(MSG_TO_CREATE_ROLE);

		} catch (Exception e) {

			Log.e("error", e.getMessage());
		}
	}

	public void enterGame(String roleId, String roleName, int roleLevel, int ServerId, String ServerName,
			int vipLevel) {
		this.roleId = roleId;
		this.roleName = roleName;
		this.roleLevel = roleLevel;
		this.serverId = ServerId;
		this.serverName = ServerName;
		this.vipLevel = vipLevel;
		try {
			mHandler.sendEmptyMessage(MSG_TO_ENTER_GAME);

		} catch (Exception e) {

			Log.e("error", e.getMessage());
		}
	}

	public void roleLevelUp(String roleId, String roleName, int roleLevel, int ServerId, String ServerName,
			int vipLevel) {
		this.roleId = roleId;
		this.roleName = roleName;
		this.roleLevel = roleLevel;
		this.serverId = ServerId;
		this.serverName = ServerName;
		this.vipLevel = vipLevel;
		try {
			mHandler.sendEmptyMessage(MSG_TO_LEVEL_UP);

		} catch (Exception e) {

			Log.e("error", e.getMessage());
		}
	}

	public long getAppid() {

		return app_id;
	}

	public void exit() {
		try {
			mHandler.sendEmptyMessage(MSG_TO_EXIT);

		} catch (Exception e) {

			Log.e("error", e.getMessage());
		}
	}

	void gameExit() {
		AlertDialog.Builder builder = new AlertDialog.Builder(ProjectMB.getContext());
		builder.setMessage("确认退出游戏吗？");

		builder.setTitle("提示");
		builder.setPositiveButton("确认", new AlertDialog.OnClickListener() {

			public void onClick(DialogInterface dialog, int which) {
				dialog.dismiss();
				((ProjectMB) ProjectMB.getContext()).sdkManager.exit();
				Intent startMain = new Intent(Intent.ACTION_MAIN);
				startMain.addCategory(Intent.CATEGORY_HOME);
				startMain.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
				ProjectMB.getContext().startActivity(startMain);
				System.exit(0);
			}
		});

		builder.setNegativeButton("取消", new AlertDialog.OnClickListener() {

			@Override
			public void onClick(DialogInterface dialog, int arg1) {

				dialog.dismiss();

			}
		});

		builder.create().show();
	}
}
