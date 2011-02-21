package com.example.eadcel;

import android.app.Activity;
import android.content.Context;
import android.util.Log;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.Toast;

class DemoGLSurfaceView extends GLSurfaceView_FFMPEG {	
	
	DemoRenderer mRenderer;
	
	private Toast toast = null;
	private LinearLayout lay = null;
	
	
	
	public DemoGLSurfaceView(Activity ctx,int w, int h) {
		super(ctx);
			
//		toast = Toast.makeText(ctx, text, duration);
//		ImageView view = new ImageView(ctx);
//		view.setImageResource(R.drawable.icon);
//		toast.setView(view);
		
		toast = Toast.makeText(ctx, "Volume", Toast.LENGTH_LONG);
		toast.setGravity(Gravity.BOTTOM, 0, 0);
		View textView = toast.getView();
		lay = new LinearLayout(ctx);
		lay.setOrientation(LinearLayout.HORIZONTAL);
		ImageView view = new ImageView(ctx);
		view.setImageResource(R.drawable.sound);
		lay.addView(view);
		lay.addView(textView);
		toast.setView(lay);
	
		
		mRenderer = new DemoRenderer(w,h);
		setRenderer(mRenderer);
		
		
		
    }
    
	public boolean onTouchEvent(MotionEvent event) {
		// TODO Auto-generated method stub
		  
		Log.v("Java", String.format("DemoGLSurfaceView - onTouchEvent\n"));
		
        
		return super.onTouchEvent(event);
		
	   }
	
	public boolean onKeyDown(int keyCode, final KeyEvent event) {
        super.onKeyDown(keyCode, event);
        // Overrides Back key to use in our app
        Log.v("Java", String.format("mGLView - onKeyEvent - KEYCODE = %d\n",keyCode));
        
        
        
        
        if( keyCode == KeyEvent.KEYCODE_BACK){
        	 Log.v("Java", String.format("onKeyEvent - EXIT \n"));
        	 
        }

 
        return super.onKeyDown(keyCode, event);
    }
	
	public boolean volumeUp(){
		int vol = getVolume();
		if(vol==0){
			((ImageView)lay.getChildAt(0)).setImageResource(R.drawable.sound);
			
		}
		if(vol<10)toast.setText("Volume = "+(vol+1));
    	toast.show();
		return mRenderer.volumeUp();
	}
	
	public boolean volumeDown(){
		int vol = getVolume();
		if(vol>1){
			
			toast.setText("Volume = "+(vol-1));
		}
		else {
			
			((ImageView)lay.getChildAt(0)).setImageResource(R.drawable.nosound); 
			toast.setText("Mudo");
		}
    	toast.show();
		return mRenderer.volumeDown();
	}
	
	public int getVolume(){
		return mRenderer.getVolume();
		
	}
    
}

