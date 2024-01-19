package com.zdbpkq.bt;

import java.io.IOException;

import android.app.Activity;
import android.content.res.AssetFileDescriptor;
import android.media.MediaPlayer;
import android.net.Uri;
import android.util.Log;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;

public class VideoView extends SurfaceView implements 
SurfaceHolder.Callback, 
View.OnTouchListener, 
MediaPlayer.OnPreparedListener, 
MediaPlayer.OnErrorListener, 
MediaPlayer.OnInfoListener,
MediaPlayer.OnCompletionListener {
	private static final String TAG = "VideoView";

	private MediaPlayer mPlayer;
	private Activity gameActivity;
	private Uri resUri;
	private AssetFileDescriptor fd;
	private boolean surfaceCreated;
	private OnFinishListener onFinishListener = null;


	public VideoView(Activity context) {
		super(context);

		this.gameActivity = context;

		final SurfaceHolder holder = getHolder();
		holder.addCallback(this);
		holder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
//		setOnTouchListener(this);

		mPlayer = new MediaPlayer();
		mPlayer.setScreenOnWhilePlaying(true);

		mPlayer.setOnPreparedListener(this);
		mPlayer.setOnCompletionListener(this);
		mPlayer.setOnErrorListener(this);
		mPlayer.setOnInfoListener(this);
	}

	public VideoView setOnFinishListener(OnFinishListener onFinishListener) {
		this.onFinishListener = onFinishListener;
		return this;
	}

	public void setVideo(Uri resUri) {
		this.resUri = resUri;

		try {
			mPlayer.setDataSource(gameActivity, resUri);
			mPlayer.prepare();
		} catch (Exception e) { }
	}

	public void setVideo(AssetFileDescriptor fd) {
		this.fd = fd;

		try {
			mPlayer.setDataSource(fd.getFileDescriptor(), fd.getStartOffset(), fd.getLength());
			mPlayer.prepare();
		} catch (IOException e) {
			e.printStackTrace();

			onCompletion(null);
		}

	}

	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
	}

	@Override
	public void surfaceCreated(final SurfaceHolder holder) {
		Log.i(TAG, "surfaceCreated");

		surfaceCreated = true;

		mPlayer.setDisplay(holder);
		try {
			mPlayer.prepare();
		} catch (Exception e1) {
		}
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		Log.i(TAG, "surfaceDestroyed");
		surfaceCreated = false;

		if(mPlayer != null){
			mPlayer.stop();
			mPlayer.reset();
		}
	}

	@Override
	public void onPrepared(MediaPlayer player) 
	{
		Log.i(TAG, "onPrepared");

//		int wWidth = getWidth();
//		int wHeight = getHeight();
//		int vWidth = mPlayer.getVideoWidth();
//		int vHeight = mPlayer.getVideoHeight();
//
//		float wRatio = (float) vWidth / (float) wWidth;
//		float hRatio = (float) vHeight / (float) wHeight;
//		
//		Log.v(TAG, wRatio + "  " + hRatio);
//		float ratio = Math.min(wRatio, hRatio);
//		vWidth = (int) Math.ceil((float) vWidth * ratio);
//		vHeight = (int) Math.ceil((float) vHeight * ratio);
//
//		Log.v(TAG, vWidth + " " + vHeight);
//		getHolder().setFixedSize(vWidth, vHeight);
//		//		mPlayer.seekTo(posttion);
//		mPlayer.start();
		
	    player.start();   
	}

	private void dispose() {
		if(mPlayer != null)mPlayer.release();
		mPlayer = null;
		resUri = null;
		if (fd != null) {
			try {
				fd.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
			fd = null;
		}
	}

	@Override
	public void onCompletion(MediaPlayer mp) {
		Log.i(TAG, "onCompletion");

		dispose();

		if(onFinishListener != null)
			onFinishListener.onVideoFinish();
	}

	@Override
	public boolean onInfo(MediaPlayer mp, int what, int extra) {
		return true;
	}

	@Override
	public boolean onError(MediaPlayer mp, int what, int extra) 
	{
		dispose();

		Log.i(TAG, "onError"+"what:"+what+"extra:"+extra);
		if(onFinishListener != null)
			onFinishListener.onVideoFinish();
		return true;
	}

	
	
	@Override
	public boolean onTouch(View v, MotionEvent event) 
	{
		setOnTouchListener(null);
		if (event.getAction() == MotionEvent.ACTION_DOWN) {
			stop();
		}
		return true;
	}

	public void stop() {
		if(mPlayer != null)
		{
			mPlayer.stop();
			dispose();
			if(onFinishListener != null)
				onFinishListener.onVideoFinish();
		}
	}

	int posttion;
	public void pause() {
		posttion = mPlayer.getCurrentPosition();
		if(mPlayer != null)mPlayer.pause();

		Log.i(TAG, "pause");
	}

	public void resume() {
		Log.i(TAG, "resume");
		if(surfaceCreated)
		{
			mPlayer.start();
		}
		else 
		{
			try 
			{
				if(resUri != null)
					mPlayer.setDataSource(gameActivity, resUri);
				else if (fd != null) 
				{
					mPlayer.setDataSource(fd.getFileDescriptor(), fd.getStartOffset(), fd.getLength());
				}
			} 
			catch (Exception e) 
			{
			}
		}
	}

	public interface OnFinishListener
	{
		public void onVideoFinish();
	}
}
