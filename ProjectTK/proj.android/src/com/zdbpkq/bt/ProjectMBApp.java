package com.zdbpkq.bt;

import com.quicksdk.QuickSdkApplication;

import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class ProjectMBApp extends QuickSdkApplication {
	@Override
	public void onCreate() {
		super.onCreate();
	}

	public void restartApplication() {
		final Intent intent = getPackageManager().getLaunchIntentForPackage(getPackageName());
		intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
		startActivity(intent);
		android.os.Process.killProcess(android.os.Process.myPid());
	}
}
