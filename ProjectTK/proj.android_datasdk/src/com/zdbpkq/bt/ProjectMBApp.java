package com.zdbpkq.bt;

import com.datasdk.DataSdkApplication;

import android.content.Intent;

public class ProjectMBApp extends DataSdkApplication {
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
