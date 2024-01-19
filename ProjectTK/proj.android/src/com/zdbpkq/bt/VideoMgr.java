package com.zdbpkq.bt;

import java.io.IOException;

import com.zdbpkq.bt.VideoView.OnFinishListener;

import android.content.res.AssetFileDescriptor;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.ViewGroup;

public class VideoMgr implements OnFinishListener {
	private final int MSG_PLAY_VIDEO = 0;
	private final int MSG_PAUSE_VIDEO = 1;
	private final int MSG_STOP_VIDEO = 2;
	private final int MSG_STOP_RESUME_VIDEO = 3;
	private final int MSG_FINISH_VIDEO = 4;

	public VideoMgr() {
		group = (ViewGroup) ((ProjectMB) ProjectMB.getContext()).getWindow().getDecorView();
		msgHandler = new Handler() {
			public void handleMessage(Message msg) {
				switch (msg.what) {
				case MSG_PLAY_VIDEO:
					pv(_videoname);
					break;
				case MSG_PAUSE_VIDEO:
					if (videoView != null)
						videoView.pause();
					break;
				case MSG_STOP_VIDEO:
					if (videoView != null)
						videoView.stop();
					break;
				case MSG_STOP_RESUME_VIDEO:
					if (videoView != null)
						videoView.resume();
					break;
				case MSG_FINISH_VIDEO:
					group.removeView(videoView);
					videoView = null;
					break;
				}
			}
		};
	}

	private static VideoMgr instance = null;

	public static VideoMgr instance() {
		if (instance == null) {
			instance = new VideoMgr();
		}
		return instance;
	}

	private Handler msgHandler = null;
	private ViewGroup group;
	private VideoView videoView;
	private String _videoname = "";

	public void playVideo(final String name) {
		mCanClicke = true;
		_videoname = name;
		msgHandler.sendEmptyMessage(MSG_PLAY_VIDEO);
	}

	public void pauseVideo() {
		msgHandler.sendEmptyMessage(MSG_PAUSE_VIDEO);
	}

	public void stopVide() {
		msgHandler.sendEmptyMessage(MSG_STOP_VIDEO);
	}

	private Boolean mCanClicke = true;

	public void resumeVideo() {
		msgHandler.sendEmptyMessage(MSG_STOP_RESUME_VIDEO);
	}

	@Override
	public void onVideoFinish() {
		mCanClicke = false;
		msgHandler.sendEmptyMessage(MSG_FINISH_VIDEO);
		((ProjectMB) ProjectMB.getContext()).runOnGLThread(new Runnable() {
			@Override
			public void run() {
				onFinishVideo();
			}
		});

	}

	private void pv(String name) {
		videoView = new VideoView((ProjectMB) ProjectMB.getContext());
		videoView.setOnFinishListener(this);
		try {
			AssetFileDescriptor afd = ProjectMB.getContext().getAssets().openFd(name);
			videoView.setVideo(afd);
		} catch (IOException e) {
			e.printStackTrace();
		}
		group.addView(videoView);
		videoView.setZOrderMediaOverlay(true);
	}

	public native void onFinishVideo();
}
