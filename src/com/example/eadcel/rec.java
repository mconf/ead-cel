package com.example.eadcel;

import java.io.IOException;

import android.content.Context;
import android.hardware.Camera;
import android.media.MediaRecorder;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

class rec extends SurfaceView implements SurfaceHolder.Callback {
    SurfaceHolder mHolder;
    MediaRecorder mMediaRecorderAudio;
    MediaRecorder mMediaRecorderVideo;
    
    rec(Context context) {
        super(context);
        
        // Install a SurfaceHolder.Callback so we get notified when the
        // underlying surface is created and destroyed.
        mHolder = getHolder();
        mHolder.addCallback(this);
        mHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
    }

    public void surfaceCreated(SurfaceHolder holder) {
        
    }

    public void surfaceDestroyed(SurfaceHolder holder) {

    }

    public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
    
    }

    public void iniciarrec() {
    	Log.v("Java", String.format("INICIAR RECORDING"));    	
    	//audio
    	if (mMediaRecorderAudio == null) {
            mMediaRecorderAudio = new MediaRecorder();
        } else {
            mMediaRecorderAudio.reset();
        }    	

        mMediaRecorderAudio.setAudioSource(MediaRecorder.AudioSource.MIC);
        mMediaRecorderAudio.setOutputFormat(MediaRecorder.OutputFormat.THREE_GPP);
        mMediaRecorderAudio.setAudioEncoder(MediaRecorder.AudioEncoder.AMR_NB);
        mMediaRecorderAudio.setOutputFile("/sdcard/testeaudiooficial.3gpp");
        
        try {
        	mMediaRecorderAudio.prepare();
            mMediaRecorderAudio.start();
        } catch (IOException exception) {
            mMediaRecorderAudio.reset();
            mMediaRecorderAudio.release();
            mMediaRecorderAudio = null;
       }

        //video
    	if (mMediaRecorderVideo == null) {
            mMediaRecorderVideo = new MediaRecorder();
        } else {
            mMediaRecorderVideo.reset();
        }                

        mMediaRecorderVideo.setVideoSource(MediaRecorder.VideoSource.CAMERA);
        mMediaRecorderVideo.setOutputFormat(MediaRecorder.OutputFormat.MPEG_4);
        mMediaRecorderVideo.setVideoEncoder(MediaRecorder.VideoEncoder.MPEG_4_SP);
        mMediaRecorderVideo.setOutputFile("/sdcard/testevideooficial.mp4");
        mMediaRecorderVideo.setPreviewDisplay(mHolder.getSurface());
        
        try {
        	mMediaRecorderVideo.prepare();
            mMediaRecorderVideo.start();
        } catch (IOException exception) {
            mMediaRecorderVideo.reset();
            mMediaRecorderVideo.release();
            mMediaRecorderVideo = null;
        }
	}
    
	public void pararrec() {
		Log.v("Java", String.format("PARAR RECORDING"));
		mMediaRecorderAudio.stop();
		mMediaRecorderAudio.reset();
        mMediaRecorderAudio.release();
        mMediaRecorderAudio = null;
        
        mMediaRecorderVideo.stop();
		mMediaRecorderVideo.reset();
        mMediaRecorderVideo.release();
        mMediaRecorderVideo = null;
	}

}