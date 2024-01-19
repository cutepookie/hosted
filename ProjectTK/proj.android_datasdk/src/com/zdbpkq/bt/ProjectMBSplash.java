package com.zdbpkq.bt;

import com.datasdk.DataSdkSplashActivity;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Color;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;

public class ProjectMBSplash extends DataSdkSplashActivity {
	boolean isCanEnter = false;
	@Override
	public int getBackgroundColor() {
		// 返回闪屏的背景颜色
		return Color.BLACK;
	}


	@Override
	public void onSplashStop() {
		try {
			isCanEnter = true;
			// check权限
			if ((ContextCompat.checkSelfPermission(ProjectMBSplash.this,
					Manifest.permission.READ_PHONE_STATE) != PackageManager.PERMISSION_GRANTED)
					|| (ContextCompat.checkSelfPermission(ProjectMBSplash.this,
							Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED)) {
				// 没有 ， 申请权限 权限数组
				ActivityCompat.requestPermissions(ProjectMBSplash.this, new String[] {
						Manifest.permission.READ_PHONE_STATE, Manifest.permission.WRITE_EXTERNAL_STORAGE }, 1);
			} else {
				// 有 则执行初始化
				// 设置通知，用于监听初始化，登录，注销，支付及退出功能的返回值(必接)
				// TODO Auto-generated method stub
				// 闪屏结束进入游戏
				Intent intent = new Intent(this, ProjectMB.class);
				startActivity(intent);
				this.finish();
			}
		} catch (Exception e) {
			// 异常 继续申请
			ActivityCompat.requestPermissions(ProjectMBSplash.this,
					new String[] { Manifest.permission.READ_PHONE_STATE, Manifest.permission.WRITE_EXTERNAL_STORAGE },
					1);
		}
	}
	
	// 申请权限的回调（结果）
		@Override
		public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
			if (isCanEnter) {
				if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {
					// 申请成功
					Intent intent = new Intent(this, ProjectMB.class);
					startActivity(intent);
					this.finish();
				} else {
					// 失败 这里逻辑以游戏为准 这里只是模拟申请失败 退出游戏 cp方可改为继续申请 或者其他逻辑
					System.exit(0);
					finish();
				}
			}
		}
}
