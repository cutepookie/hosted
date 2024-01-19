package com.zdbpkq.bt;

import java.util.UUID;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.quicksdk.Extend;
import com.quicksdk.Payment;
import com.quicksdk.QuickSDK;
import com.quicksdk.Sdk;
import com.quicksdk.User;
import com.quicksdk.entity.GameRoleInfo;
import com.quicksdk.entity.OrderInfo;
import com.quicksdk.entity.UserInfo;
import com.quicksdk.notifier.ExitNotifier;
import com.quicksdk.notifier.LoginNotifier;
import com.quicksdk.notifier.LogoutNotifier;
import com.quicksdk.notifier.SwitchAccountNotifier;

import android.R.bool;
import android.R.string;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.net.Uri;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

//import com.sina.weibo.sdk.utils.Util;

public class YJSDKManager extends CommonSdkManager {

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
		QuickSDK.getInstance().setLoginNotifier(new LoginNotifier() {
			@Override
			public void onSuccess(final UserInfo userInfo) {
				// 登录成功，获取到用户信息userInfo
				// 通过userInfo中的UID、token做服务器登录认证
				System.out.println("sdk login  success...........................");
				System.out.println("getPlatformUid=" + userInfo.getPlatformUid());
				System.out.println("getPlatformUsername=" + userInfo.getPlatformUsername());
				System.out.println("getUID=" + userInfo.getUID());
				System.out.println("getUserName=" + userInfo.getUserName());
				System.out.println("getToken=" + userInfo.getToken());

				System.out.println("onLoginSuccess");

				// 跳转到游戏界面
				((Cocos2dxActivity) ProjectMB.getContext()).runOnGLThread(new Runnable() {
					public void run() {
						// do something
						YJSDKManager.IsLoginOK = true;
						// 登陆成功回调
						String appId = ProjectMB.appid;
						String channelId = Extend.getInstance().getExtrasConfig("channel");
						if (channelId == null || channelId.equals("")) {
							channelId = Extend.getInstance().getChannelType() + "";
						}

						System.out.println("channelId..........................." + channelId);

						String userId = userInfo.getUID();
						String token = userInfo.getToken();
						Log.i("main", "token -> " + token.length());
						login(appId, channelId, userId, token);
					}
				});
			}

			@Override
			public void onCancel() {
				System.out.println("登录取消");
				// 登录取消
			}

			@Override
			public void onFailed(final String message, String trace) {
				System.out.println("登录失败");
				System.out.println("message：" + message + "========trace：" + trace);
				// 登录失败
			}
		});

		QuickSDK.getInstance().setLogoutNotifier(new LogoutNotifier() {
			@Override
			public void onSuccess() {
				// 注销成功
				Log.e("MyGame", "注销成功");
				mHandler.sendEmptyMessage(MSG_TO_LOGOUT);
				// goLogout();
			}

			@Override
			public void onFailed(String message, String trace) {
				// 注销失败，不做处理
			}
		});

		QuickSDK.getInstance().setSwitchAccountNotifier(new SwitchAccountNotifier() {
			@Override
			public void onSuccess(UserInfo userInfo) {
				// 切换账号成功的回调，返回新账号的userInfo
				// 一些渠道在悬浮框有切换账号的功能，此回调即切换成功后的回调。游戏应清除当前的游戏角色信息。在切换账号成功后回到选择服务器界面，请不要再次调用登录接口。
				Log.e("MyGame", "切换账号成功");
				// appId = ProjectMB.appid;
				// channelId = userInfo.getUID();
				// userId = userInfo.getUID() + userInfo.getPlatformUid() + "";
				// token = userInfo.getToken();
				// Log.i("main", "token -> " + token.length());

				mHandler.sendEmptyMessage(MSG_TO_LOGOUT);
			}

			@Override
			public void onCancel() {
				// 切换账号取消
			}

			@Override
			public void onFailed(String message, String trace) {
				// 切换账号失败
			}
		});

		QuickSDK.getInstance().setExitNotifier(new ExitNotifier() {
			@Override
			public void onSuccess() {
				// 退出成功，游戏在此做自身的退出逻辑处理
				((ProjectMB) ProjectMB.getContext()).sdkManager.exit();
				Intent startMain = new Intent(Intent.ACTION_MAIN);
				startMain.addCategory(Intent.CATEGORY_HOME);
				startMain.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
				ProjectMB.getContext().startActivity(startMain);
				System.exit(0);
			}

			@Override
			public void onFailed(String message, String trace) {
				// 退出失败，不做处理
			}
		});
		mHandler = new Handler() {

			public void handleMessage(Message msg) {

				switch (msg.what) {

				case MSG_TO_LOGIN: {
					User.getInstance().login((ProjectMB) ProjectMB.getContext());
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
					int price = amount; // 必传入
					String customerorderId = encodeUrl(serverId + "|" + roleId);
					String productname = "宝石";
					GameRoleInfo roleInfo = new GameRoleInfo();
					roleInfo.setServerID(String.valueOf(serverId));// 数字字符串
					roleInfo.setServerName(serverName);
					roleInfo.setGameRoleName(roleName);
					roleInfo.setGameRoleID(roleId);
					roleInfo.setGameUserLevel(String.valueOf(roleLevel));
					roleInfo.setVipLevel(String.valueOf(vipLevel));
					roleInfo.setGameBalance("0");
					roleInfo.setPartyName("0");
					OrderInfo orderInfo = new OrderInfo();
					orderInfo.setCpOrderID(UUID.randomUUID().toString().replace("-", ""));
					orderInfo.setGoodsName(productname);// 商品名称，不带数量
					orderInfo.setCount(1);// 游戏币数量
					orderInfo.setAmount(price);
					orderInfo.setGoodsID(payInfo);
					orderInfo.setExtrasParams(customerorderId);
					Payment.getInstance().pay((ProjectMB) ProjectMB.getContext(), orderInfo, roleInfo);
				}
					break;
				case MSG_TO_EXIT: {
					if (QuickSDK.getInstance().isShowExitDialog()) {
						Sdk.getInstance().exit((ProjectMB) ProjectMB.getContext());
					} else {
						// 游戏调用自身的退出对话框，点击确定后，调用quick的exit接口
						gameExit();
					}
				}
					break;
				case MSG_TO_CREATE_ROLE: {
					submitExtendData(true);
				}
					break;

				case MSG_TO_ENTER_GAME: {
					submitExtendData(false);
				}
					break;
				case MSG_TO_LEVEL_UP: {
					submitExtendData(false);
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

	public void submitExtendData(boolean b) {
		try {
			PackageInfo pkg = ProjectMB.getContext().getPackageManager()
					.getPackageInfo(((ProjectMB) ProjectMB.getContext()).getApplication().getPackageName(), 0);
			String appName = pkg.applicationInfo.loadLabel(ProjectMB.getContext().getPackageManager()).toString();

			// 注：GameRoleInfo的字段，如果游戏有的参数必须传，没有则不用传
			GameRoleInfo roleInfo = new GameRoleInfo();
			roleInfo.setServerID(String.valueOf(serverId));// 数字字符串，不能含有中文字符
			roleInfo.setServerName(serverName);
			roleInfo.setGameRoleName(roleName);
			roleInfo.setGameRoleID(roleId);
			roleInfo.setGameBalance("0");
			roleInfo.setVipLevel(String.valueOf(vipLevel)); // 设置当前用户vip等级，必须为整型字符串
			roleInfo.setGameUserLevel(String.valueOf(roleLevel));// 设置游戏角色等级
			roleInfo.setPartyName("0");// 设置帮派名称
			roleInfo.setRoleCreateTime(String.valueOf(System.currentTimeMillis())); // UC，当乐与1881，TT渠道必传，值为10位数时间戳
			User.getInstance().setGameRoleInfo((ProjectMB) ProjectMB.getContext(), roleInfo, b);
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

	public void openurl() {
		try {
			Intent intent = new Intent();
			intent.setAction("android.intent.action.VIEW");
			Uri content_url = Uri.parse("http://tmzz.private.andersengame.com");// splitflowurl为分流地址
			intent.setData(content_url);
			if (!hasPreferredApplication(ProjectMB.getContext(), intent)) {
				intent.setClassName("com.android.browser", "com.android.browser.BrowserActivity");
			}
			ProjectMB.getContext().startActivity(intent);
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
		}
	}

	// 判断系统是否设置了默认浏览器
	public boolean hasPreferredApplication(Context context, Intent intent) {
		PackageManager pm = context.getPackageManager();
		ResolveInfo info = pm.resolveActivity(intent, PackageManager.MATCH_DEFAULT_ONLY);
		return !"android".equals(info.activityInfo.packageName);
	}

	// 如果info.activityInfo.packageName为android,则没有设置,否则,有默认的程序.
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

	public void quitGame() {
		logout();
	}
}
