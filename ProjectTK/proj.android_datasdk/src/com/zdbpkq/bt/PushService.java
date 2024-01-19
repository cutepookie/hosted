package com.zdbpkq.bt;




import java.util.ArrayList;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.IBinder;
import android.util.Log;


public class PushService extends Service {
	
	public static String action = "com.crimoon.ProjectMB.PushService";
	private NotificationManager mManager;
	public static  ArrayList<PushMessage> array = new ArrayList();
	MyReceiver receiver;
	@Override
	public IBinder onBind(Intent arg0) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void onCreate() {
		super.onCreate();

	}

	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {

		return super.onStartCommand(intent, flags, startId);
	}
	
	
	private void doTask() {

	}
	
	
	@Override
	public void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
	}
	
}
class  MyReceiver extends BroadcastReceiver{

	@Override
	public void onReceive(Context arg0, Intent arg1) {

		
	}
	
};