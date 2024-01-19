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

import com.datasdk.Sdk;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.WindowManager;
import android.widget.Toast;

public class ProjectMB extends Cocos2dxActivity {

	public String projectID = "0";
	public CommonSdkManager sdkManager = null;
	// private UpdateModule updataDlg = null;
	static String ProductCode = "20191128002";
	static String ProductKey = "ecd79fcff90747198c4221fbb02b7f8d";
	
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Sdk.getInstance().onCreate(this);

		PushMessageManager.instance();
		initSDK();
		CommonSdkManager.initSDK(this);
		VideoMgr.instance();

		getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,
				WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		Log.d("Main Activity", "Initialize complated!");
	}

	static {

		System.loadLibrary("cocos2dcpp");
	}

	public void initSDK() {
		// SDK初始化，第二与第三个参数需替换成分配的productCode和productKey值
		Sdk.getInstance().init(this, ProductCode, ProductKey);
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
		Sdk.getInstance().onResume(this);
		if (sdkManager != null) {

			sdkManager.onResume();
		}
	}

	@Override
	protected void onPause() {

		super.onPause();
		sdkManager.onPause();
		VideoMgr.instance().pauseVideo();
		Sdk.getInstance().onPause(this);
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		sdkManager.destroySDK(this);
		Sdk.getInstance().onDestroy(this);
	}

	@Override
	protected void onStop() {

		super.onStop();
		sdkManager.onStop();
		Sdk.getInstance().onStop(this);
	}

	@Override
	protected void onStart() {

		super.onStart();
		sdkManager.onStart();
		Sdk.getInstance().onStart(this);
	}

	@Override
	protected void onRestart() {
		super.onRestart();
		Sdk.getInstance().onRestart(this);
	}

	public void toUpdate(String url) {
	}

	@Override
	protected void onNewIntent(Intent intent) {
		super.onNewIntent(intent);
		setIntent(intent);
		Sdk.getInstance().onNewIntent(intent);
	}

	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		Sdk.getInstance().onActivityResult(this, requestCode, resultCode, data);
	}

}
