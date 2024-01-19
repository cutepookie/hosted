package com.zdbpkq.bt;

import java.io.InputStream;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;


public class CommonSdkManager {

	protected static CommonSdkManager mSharedManager = null;
	protected String roleName ;

	public static CommonSdkManager getCommonSdkManager() { return mSharedManager ; }

	public CommonSdkManager(){
		
		roleName ="00:00:00:00:00:00";
		
	}
	public String getRoleName(){
		
		return roleName;
	}

	public static void initSDK(ProjectMB context){

		context.sdkManager = YJSDKManager.instance();//ZZSDKManager.instance();
		/* try {
	    	
	    	InputStream is=	context.getResources().getAssets().open("zzconfig.xml");
	    	DocumentBuilderFactory factory=DocumentBuilderFactory.newInstance();
			DocumentBuilder db = factory.newDocumentBuilder();
			Document xmlDoc = db.parse(is);
			Element root = xmlDoc.getDocumentElement();
			
			NodeList list = root.getElementsByTagName("serverid");
			Element child = (Element)list.item(0);
			String value = child.getTextContent();
//			ZZSDKManager.instance().setServerID(value);
//			SDKManager.setGameServerId(value);
			
			list = root.getElementsByTagName("projectid");
			child = (Element)list.item(0);
			value = child.getTextContent();
			context.projectID = value;
//			SDKManager.setProjectId(value);
	
			list = root.getElementsByTagName("productid");
			child = (Element)list.item(0);
			value = child.getTextContent();
//			SDKManager.setProductId(value);
//			ZZSDKManager.instance().setProductID(value);
			
			list = root.getElementsByTagName("appid");
			child = (Element)list.item(0);
			value = child.getTextContent();
//			SDKManager.setAppKey(value);	
			
//			SDKManager.setAntiAddiction(false);
//			SDKManager mSDKManager = SDKManager.getInstance(context.getBaseContext());
//			mSDKManager.setConfigInfo(true, true, true);
			
//			ZZSDKManager.instance().setSDKManager(mSDKManager);
//			context.sdkManager = ZZSDKManager.instance();
		
	    } catch (Exception e) {
			e.printStackTrace();
		}
		
		*/
	}
	public void destroySDK(ProjectMB context){
		
		
	}
	public void exit(){
		
	}
	public void onExit(){
		((ProjectMB)ProjectMB.getContext()).sdkManager.exit();
		/*
		AlertDialog.Builder builder = new AlertDialog.Builder(
				ProjectMB.getContext());
		builder.setMessage("确认退出游戏吗？");

		builder.setTitle("提示");
		builder.setPositiveButton("确认", new AlertDialog.OnClickListener() {

			public void onClick(DialogInterface dialog, int which) {
				dialog.dismiss();
				((ProjectMB)ProjectMB.getContext()).sdkManager.exit();
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
		*/
	}
	
	public void onResume(){
		
		
	}
	public void onPause(){
		
		
	}
	public void onStop(){
		
		
	}
	public void onStart(){
		
		
	}
}


