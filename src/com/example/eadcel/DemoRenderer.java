package com.example.eadcel;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;


import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Display;
import android.view.Window;
import android.view.WindowManager;

class DemoRenderer extends GLSurfaceView_FFMPEG.Renderer {
	//private Benchmarks mBench = null;
	AudioThread mAudioThread = null;
	DisplayMetrics metrics = null;
	private int width,heigth;
	
	public DemoRenderer(int w, int h){
		super();
		width = w;
		heigth = h;
	}
	
	private void initVideoJava(){
		mAudioThread = new AudioThread();
		nativeVideoInitJavaCallbacks();
		mAudioThread.nativeAudioInitJavaCallbacks();
        //mBench = new Benchmarks();
		
		
	}
	
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
    }

    public void onSurfaceChanged(GL10 gl, int w, int h) {
        //nativeResize(w, h);
    }
    
    public void onDrawFrame(GL10 gl) {
    	initVideoJava();
    	nativeRender(width,heigth);
    	Log.v("Java", String.format("Finalizou EADCEL\n"));
    }
    
    public int swapBuffers() // Called from native code, returns 1 on success, 0 when GL context lost (user put app to background)
	{
		synchronized (this) {
			this.notify();
		}
		//Thread.yield();
		//mBench.simpleBench(30000);
		return super.SwapBuffers() ? 1 : 0;
	}
    
    public boolean volumeUp(){
		return mAudioThread.volumeUp();
	}
	
	public boolean volumeDown(){
		return mAudioThread.volumeDown();
	}
    
	public int getVolume(){
		return mAudioThread.getVolume();
		
	}

    private native int nativeVideoInitJavaCallbacks();
    private native int nativeRender(int width,int heigth);
}

