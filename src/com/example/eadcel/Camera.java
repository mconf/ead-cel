package com.example.eadcel;

import java.io.IOException;
import java.lang.reflect.Method;

import android.content.Context;
import android.graphics.PixelFormat;
import android.hardware.Camera;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

class Preview extends SurfaceView implements SurfaceHolder.Callback,Camera.PreviewCallback {
    SurfaceHolder mHolder;
    Camera mCamera;
    //private Benchmarks mBench = null;
    private static final String TAG = "MyActivity";
    
    int contFrames = 0;
     
    
    Preview(Context context, int b1, int b2, int b3, int b4, int port) {
        super(context);
        
        // Install a SurfaceHolder.Callback so we get notified when the
        // underlying surface is created and destroyed.
        mHolder = getHolder();
        mHolder.addCallback(this);
        mHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
        
        
        nativeSenderInitVideo(b1,b2,b3,b4,port);
        
		//mBench = new Benchmarks("Frames de video capturados pela camera e enviados para o C++");
    }

    // Preview is started or resumed
    public void surfaceCreated(SurfaceHolder holder) {
        // The Surface has been created, acquire the camera and tell it where
        // to draw.
        mCamera = Camera.open();
        try {
           //mCamera.setPreviewDisplay(holder);
        	mCamera.setPreviewDisplay(mHolder);
        } catch (IOException exception) {
            mCamera.release();
            mCamera = null;
            // TODO: add more exception handling logic here
      	}
    }

    public void surfaceDestroyed(SurfaceHolder holder) {
        // Surface will be destroyed when we return, so stop the preview.
        // Because the CameraDevice object is not a shared resource, it's very
        // important to release it when the activity is paused.
        mCamera.stopPreview();
        mCamera.release();
        mCamera = null;
    }
    
    public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
        // Now that the size is known, set up the camera parameters and begin
        // the preview.
        Camera.Parameters parameters = mCamera.getParameters();
//        Log.v("Java", String.format("PICTURE FORMAT %d\n",parameters.getPictureFormat()));
//        Log.v("Java", String.format("PREVIEW FORMAT %d\n",parameters.getPreviewFormat()));
//        Log.v("Java", String.format("PREVIEW FRAMERATE %d\n",parameters.getPreviewFrameRate()));
        
        w=  320; h = 240;
//        parameters.setPictureSize(176, 144);
        parameters.setPreviewFrameRate(15);        
        parameters.setPreviewSize(w, h);
//        Log.v("Java", String.format("previewsizew = %d, previewsizeh = %d\n", w, h));
        
        mCamera.setParameters(parameters);
//        Log.v("Java", String.format("PREVIEW FRAMERATE %d\n",parameters.getPreviewFrameRate()));
        
        //2.2 hack
        PixelFormat p = new PixelFormat();
		PixelFormat.getPixelFormatInfo(parameters.getPreviewFormat(),p);
		Log.v("Java", String.format("FORMATO DE PIXEL = %d, BYTES PER PIXEL = %d, BITS PER PIXEL = %d\n", parameters.getPreviewFormat(), p.bytesPerPixel, p.bitsPerPixel));
		int bufSize = (w*h*p.bitsPerPixel)/8;
		 //Must call this before calling addCallbackBuffer to get all the
        // reflection variables setup
        initForACB();
        byte[] buffer = new byte[bufSize];
        addCallbackBuffer_Android2p2(buffer);   
        buffer = new byte[bufSize];
        addCallbackBuffer_Android2p2(buffer);
        setPreviewCallbackWithBuffer();
         
        //2.0 correto
//        mCamera.setPreviewCallback(this);        
        
        //2.2 correto
//        mCamera.addCallbackBuffer(callbackBuffer);
//		mCamera.setPreviewCallbackWithBuffer(this);
        
        mCamera.startPreview();
    }
    
    /**
     * This method will list all methods of the android.hardware.Camera class,
     * even the hidden ones. With the information it provides, you can use the same
     * approach I took below to expose methods that were written but hidden in eclair
     */
    private void listAllCameraMethods(){
    	try {
			Class c = Class.forName("android.hardware.Camera");
			Method[] m = c.getMethods();
			for(int i=0; i<m.length; i++){
				Log.i("AR","  method:"+m[i].toString());
			}
		} catch (Exception e) {
			Log.i("AR",e.toString());
		}
    }
    
    Method mAcb;       // method for adding a pre-allocated buffer 
    Object[] mArglist; // list of arguments

    /*
	 *  newstuff: addCallbackBuffer();
	 */
    private void initForACB(){
    	try {
			Class mC = Class.forName("android.hardware.Camera");
		
			Class[] mPartypes = new Class[1];
			// variable that will hold parameters for a function call
			mPartypes[0] = (new byte[1]).getClass(); //There is probably a better way to do this.
			mAcb = mC.getMethod("addCallbackBuffer", mPartypes);

			mArglist = new Object[1];
		} catch (Exception e) {
			Log.e("AR","Problem setting up for addCallbackBuffer: " + e.toString());
		}
    }
    
    /**
     * This method allows you to add a byte buffer to the queue of buffers to be used by preview.
     * See: http://android.git.kernel.org/?p=platform/frameworks/base.git;a=blob;f=core/java/android/hardware/Camera.java;hb=9db3d07b9620b4269ab33f78604a36327e536ce1
     * 
     * @param b The buffer to register. Size should be width * height * bitsPerPixel / 8.
     */
    private void addCallbackBuffer_Android2p2(byte[] b){ //  this function is native in Android 2.2 ?!
    	//Check to be sure initForACB has been called to setup
    	// mAcb and mArglist
    	if(mArglist == null){
    		initForACB();
    	}

    	mArglist[0] = b;
    	try {
    		mAcb.invoke(mCamera, mArglist);
    	} catch (Exception e) {
    		Log.e("AR","invoking addCallbackBuffer failed: " + e.toString());
    	}
    }
    
    /**
     * Use this method instead of setPreviewCallback if you want to use manually allocated
     * buffers. Assumes that "this" implements Camera.PreviewCallback
     */
    private void setPreviewCallbackWithBuffer(){
    	try {
			Class c = Class.forName("android.hardware.Camera");
			Method spcwb = null;  // sets a preview with buffers
			//This way of finding our method is a bit inefficient, but I am a reflection novice,
			// and didn't want to waste the time figuring out the right way to do it.
			// since this method is only called once, this should not cause performance issues			
			
			Method[] m = c.getMethods(); // get all methods of camera
			for(int i=0; i<m.length; i++){
				if(m[i].getName().compareTo("setPreviewCallbackWithBuffer") == 0){
					spcwb = m[i];
					break;
				}
			}
			
			
			/*
			Class[] mPartypes = new Class[1];
			mPartypes[0] = (new byte[1]).getClass(); //There is probably a better way to do this.
			spcwb = c.getMethod("setPreviewCallbackWithBuffer", mPartypes);
			*/
			
			//If we were able to find the setPreviewCallbackWithBuffer method of Camera, 
			// we can now invoke it on our Camera instance, setting 'this' to be the
			// callback handler
			if(spcwb != null){
				Object[] arglist = new Object[1];
				arglist[0] = this; // receives a copy of a preview frame
				spcwb.invoke(mCamera, arglist);
				//Log.i("AR","setPreviewCallbackWithBuffer: Called method");
			} else {
				Log.i("AR","setPreviewCallbackWithBuffer: Did not find method");
			}
			
		} catch (Exception e) {
			Log.i("AR",e.toString());
		}
    }
    
    public void onPreviewFrame (byte[] _data, Camera camera)
    {
    	//mBench.simpleBench(5000);
    	addCallbackBuffer_Android2p2(_data);
    	//Log.v("Java", String.format("JAVA = %d\n", _data[10]));
    	nativeSenderVideo(_data);
    	
    	//Usado na medicao isolada da codificacao dos 100 primeiros frames
//    	contFrames++;
//    	if(contFrames==101){
//    		mCamera.stopPreview();
//            mCamera.release();
//            mCamera = null;
//    	}
    }
    
    native int nativeSenderInitVideo(int byte1,int byte2,int byte3,int byte4,int port);
    
    //native int nativeSenderInitVideo(String strIPSend,int port); //new
    
    native int nativeSenderVideo(byte[] YIn);
}