package com.zdbpkq.bt;

import java.io.Serializable;


import android.content.Intent;
import android.util.Log;

public class PushMessageManager{


	private static PushMessageManager mShareManager = null;

	
	public  PushMessageManager(){
		
		
		
	}

	public static  PushMessageManager instance(){
		
		if(mShareManager == null){
			
			mShareManager = new PushMessageManager();
		}
		return mShareManager;
	}
	public void pushMessage(String message,int time,String messageName){

 
	}
	public void cancelMessage(String messageName){
	

		
	}
	public void removeAllMessage(){
		

	}
	
} 

class PushMessage implements  Serializable{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private String message;
	private String messageName;
	private int  time;
	private int  passtime;
	public PushMessage(){
		
		 passtime = 0;
	}
	public String getMessage() {
		return message;
	}
	public void setMessage(String message) {
		this.message = message;
	}
	public String getMessageName() {
		return messageName;
	}
	public void setMessageName(String messageName) {
		this.messageName = messageName;
	}
	public float getTime() {
		return time;
	}
	public void setTime(int time) {
		this.time = time;
	}
	public int getPasstime() {
		return passtime;
	}
	public void setPasstime(int passtime) {
		this.passtime = passtime;
	}


	
}