/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package com.zdbpkq.bt;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import com.quicksdk.QuickSDK;
import com.quicksdk.notifier.InitNotifier;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.util.Log;
import android.view.KeyEvent;
import android.view.WindowManager;

public class ProjectMB extends Cocos2dxActivity {

	public String projectID = "0";
	public CommonSdkManager sdkManager = null;
	// private UpdateModule updataDlg = null;
	static String appid = "64384157674600678213664697108274";
	String ProductKey = "71212899";

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		try {
			// check权限
			if ((ContextCompat.checkSelfPermission(ProjectMB.this,
					Manifest.permission.READ_PHONE_STATE) != PackageManager.PERMISSION_GRANTED)
					|| (ContextCompat.checkSelfPermission(ProjectMB.this,
							Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED)) {
				// 没有 ， 申请权限 权限数组
				ActivityCompat.requestPermissions(ProjectMB.this, new String[] { Manifest.permission.READ_PHONE_STATE,
						Manifest.permission.WRITE_EXTERNAL_STORAGE }, 1);
			} else {
				// 有 则执行初始化
				// 设置通知，用于监听初始化，登录，注销，支付及退出功能的返回值(必接)
				initSDK();
			}
		} catch (Exception e) {
			// 异常 继续申请
			ActivityCompat.requestPermissions(ProjectMB.this,
					new String[] { Manifest.permission.READ_PHONE_STATE, Manifest.permission.WRITE_EXTERNAL_STORAGE },
					1);
		}
		com.quicksdk.Sdk.getInstance().onCreate(this);
		CommonSdkManager.initSDK(this);
		VideoMgr.instance();

		getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,
				WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		Log.d("Main Activity", "Initialize complated!");
		// updataDlg = new UpdateModule();
		// updataDlg.initMsgHanlder();

	}

	// 申请权限的回调（结果）
	@Override
	public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
		if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {
			// 申请成功
			initSDK();
		} else {
			// 失败 这里逻辑以游戏为准 这里只是模拟申请失败 退出游戏 cp方可改为继续申请 或者其他逻辑
			System.exit(0);
			finish();
		}
	}

	public Cocos2dxGLSurfaceView onCreateView() {
		Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
		// TestCpp should create stencil buffer
		glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);

		return glSurfaceView;
	}

	static {

		System.loadLibrary("cocos2dcpp");
	}

	public void initSDK() {
		try {
			QuickSDK.getInstance().setInitNotifier(new InitNotifier() {
				@Override
				public void onSuccess() {
					// 初始化成功
					System.out.println("调用安卓初始化sdk");
				}

				@Override
				public void onFailed(String message, String trace) {
					// 初始化失败
					System.out.println("调用安卓初始化sdk2");
				}
			});
			com.quicksdk.Sdk.getInstance().init(this, appid, ProductKey);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {

		if (keyCode == KeyEvent.KEYCODE_BACK) {
			YJSDKManager.instance().exit();
			return true;
		}
		return super.onKeyDown(keyCode, event);
	}

	@Override
	protected void onResume() {

		super.onResume();
		VideoMgr.instance().stopVide();
		com.quicksdk.Sdk.getInstance().onResume(this);
		if (sdkManager != null) {

			sdkManager.onResume();
		}
	}

	@Override
	protected void onPause() {

		super.onPause();
		sdkManager.onPause();
		VideoMgr.instance().pauseVideo();
		com.quicksdk.Sdk.getInstance().onPause(this);
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		sdkManager.destroySDK(this);
		com.quicksdk.Sdk.getInstance().onDestroy(this);
	}

	@Override
	protected void onStop() {

		super.onStop();
		sdkManager.onStop();
		com.quicksdk.Sdk.getInstance().onStop(this);
	}

	@Override
	protected void onStart() {

		super.onStart();
		sdkManager.onStart();
		com.quicksdk.Sdk.getInstance().onStart(this);
	}

	@Override
	protected void onRestart() {
		super.onRestart();
		com.quicksdk.Sdk.getInstance().onRestart(this);
	}

	public void toUpdate(String url) {
	}

	@Override
	protected void onNewIntent(Intent intent) {
		super.onNewIntent(intent);
		setIntent(intent);
		com.quicksdk.Sdk.getInstance().onNewIntent(intent);
	}

	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		com.quicksdk.Sdk.getInstance().onActivityResult(this, requestCode, resultCode, data);
	}

}
