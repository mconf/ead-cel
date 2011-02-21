/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.example.eadcel;

import android.app.Activity;
import android.content.Context;
import android.content.res.Configuration;
import android.media.AudioManager;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Display;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;

import android.view.Window;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.widget.AutoCompleteTextView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class eadcel extends Activity implements OnClickListener
{
	
	private Context context;
	DisplayMetrics metrics = null;
	private boolean flagFullScreen = false;
    /** Called when the activity is first created. */
    
	private int width = 0, height = 0;
	
	private Button button = null;
	private Button button2 = null;
	private Button button3 = null;
	//private Button button4 = null;
	
	
	
	// Create a button click listener for the Done button.
//	private final Button.OnClickListener btnIPsendOnClick = new Button.OnClickListener() {
//	public void onClick(View v) {
//		stringIpSend = etxtIPsend.getText().toString();
//		//Log the input string
//		Log.v("IP send = ", stringIpSend);
//		
//		etxtIPsend.setText("");
//	}
//	};

	private EADDialog dialog = null;
	
	@Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        
        
        context = getApplication().getApplicationContext();
        // Hide the Title Bar
        requestWindowFeature(Window.FEATURE_NO_TITLE);

        
        setVolumeControlStream(AudioManager.STREAM_MUSIC);
        
        // Hide the Status Bar
        //getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
        //	         WindowManager.LayoutParams.FLAG_FULLSCREEN);
        
        Log.v("Java", String.format("onCreate\n"));
        
        metrics = new DisplayMetrics();
        Display display = ((WindowManager) getSystemService(WINDOW_SERVICE)).getDefaultDisplay();
        display.getMetrics(metrics);
        
        width = metrics.widthPixels;
        height = metrics.heightPixels;
        
        changeOrientation(width,height);
        
        Log.v("Java", String.format("Tamanho da tela: %d X %d\n",width, height));
        
        //mGLView = (DemoGLSurfaceView) findViewById(R.id.GLSurfaceView);
        
        //setContentView(R.layout.ip_send_layout);
        
        setContentView(R.layout.relative);
        
        button = (Button)findViewById(R.id.Button01);
        try{
        button.setOnClickListener(this);
        }catch(Exception e){
        	Log.v("Java", String.format("erro no button.setOnClickListener(this);\n"));
        }        
        button2 = (Button)findViewById(R.id.Button02);
        try{
        button2.setOnClickListener(this);
        }catch(Exception e){
        	Log.v("Java", String.format("erro no button2.setOnClickListener(this);\n"));
        }        
  
        dialog = new EADDialog(this);
        
        
        //mGLView = new DemoGLSurfaceView(this);
        //setContentView(mGLView);
        
        
    }
    
    @Override
    protected void onPause() {
        super.onPause();
        Log.v("Java", String.format("onPause\n"));
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.v("Java", String.format("onResume\n"));   
    }
    
    protected void onStop() {
    	super.onStop();
    	Log.v("Java", String.format("onStop\n"));
    	if(mMic != null){
    		mMic.stopMic();
    	}
    	stopThreads();
   	    Log.v("Java", String.format("stopThreads() \n"));
    }
    
    protected void onStart() {
    	super.onStart();
    	Log.v("Java", String.format("onStart\n"));        
    }
    
    protected void onRestart() {
    	super.onRestart();
    	Log.v("Java", String.format("onRestart\n"));       
    }
    
    protected void onDestroy() {
    	super.onDestroy();
    	Log.v("Java", String.format("onDestroy\n"));
   }
   
    private Preview mPreview;
    //private rec mRec;
    private Mic mMic = null;
   public void onClick(View v) {
	      // do something when the button is clicked
	    
	        switch (v.getId()) {
			case R.id.Button01:
				Log.v("Java", String.format("onClick - Button01\n"));
				if(mGLView==null){
					mGLView = new DemoGLSurfaceView(this,width,height);
					//mGLView.setOnKeyListener();
					
			        //mGLView.findViewById(R.id.SurfaceVideo);
					//mGLView = (DemoGLSurfaceView)findViewById(R.id.surfaceVideo);
				}
				else Log.v("Java", String.format("mGLView not null!\n"));
				//mGLView.setVisibility(1);
				setContentView(mGLView);
				//mGLView.setOnClickListener(this);
				break;
			case R.id.Button02:
				Log.v("Java", String.format("onClick - Button02 - Camera software\n"));
				
				
				mostraTelaIPsend(); //tela de escolha de IP destino com string  
				//mostraTelaIPsendV2(); //tela de escolha de IP destino com 4 bytes
										
				//Old call to preview:
				//mPreview = new Preview(this);
				//ViewGroup.LayoutParams x = new ViewGroup.LayoutParams(320,240);
				//setContentView(mPreview, x);
				
		        //setContentView(mPreview);
		        //mMic = new Mic();
		        //mMic.start();
				break;
//			case R.id.Button03:
//				Log.v("Java", String.format("onClick - Button03\n"));
//				
//				//mPreview = new Preview(this);
//		        //setContentView(mPreview);
//		        mMic = new Mic();
//		        mMic.start();
//				break;
			
			/*case R.id.Button04:
				Log.v("Java", String.format("onClick - Button04\n"));
				
				mRec = new rec(this);
				setContentView(mRec);
				
			break;*/
			
		   }
			
	      
	  }
   
   
   private EditText etxtIPsend; //textbox to destination IP (field 1)
   private EditText etxtIPbyte1, etxtIPbyte2, etxtIPbyte3, etxtIPbyte4; //textbox to destination (fields 2 to 4)
   
   private EditText eTxtVideoPortSend; //textbox to destination IP
   private EditText eTxtAudioPortSend; //textbox to destination IP
   private Button buttonIPsend; //confirmation button
   private Button buttonIPsendAudio; //confirmation button
   private Button buttonIPsendVideo; //confirmation button
   
   private InputMethodManager imm; 
   
      
   private class OnClickBtnIPSend implements OnClickListener{

		@Override
		public void onClick(View v) {
					
			String stringIpSend = etxtIPsend.getText().toString();
			
			Log.v("Java", String.format("\nantes split"));
			String[] ipv4Bytes = stringIpSend.split("\\.");
			Log.v("Java", String.format("\ndepois split"));
			
			int byte1=127, byte2=0, byte3=0, byte4=1;
			try{
				Integer byteAux = new Integer(ipv4Bytes[0]);
				if(byteAux!=null)byte1 = byteAux.intValue();
				Log.v("Java", String.format("\nbyte1 e = %d\n",byte1));
				
				byteAux = new Integer(ipv4Bytes[1]);
				if(byteAux!=null)byte2 = byteAux.intValue();
				Log.v("Java", String.format("\nbyte2 e = %d\n",byte2));
				
				byteAux = new Integer(ipv4Bytes[2]);
				if(byteAux!=null)byte3 = byteAux.intValue();
				Log.v("Java", String.format("\nbyte3 e = %d\n",byte3));
				
				byteAux = new Integer(ipv4Bytes[3]);
				if(byteAux!=null)byte4 = byteAux.intValue();
				Log.v("Java", String.format("\nbyte4 e = %d\n",byte4));
				
				Integer intPort = new Integer(eTxtVideoPortSend.getText().toString()); 
				int portVideo = 12001;
				if(intPort!=null)portVideo =  intPort.intValue();
				
				intPort = new Integer(eTxtAudioPortSend.getText().toString()); 
				int portAudio = 12002;
				if(intPort!=null)portAudio =  intPort.intValue();
				
				
			
				switch (v.getId()) {
				case R.id.buttonIPsend:
					initAudioSend(byte1,byte2,byte3,byte4,portAudio);
					initCameraPreview(byte1,byte2,byte3,byte4,portVideo);
//					initAudioSend(byte1,byte2,byte3,byte4,portAudio);
					break;
				case R.id.buttonIPsendVideo:
					initCameraPreview(byte1,byte2,byte3,byte4,portVideo);					
					break;
				case R.id.buttonIPsendAudio:
					initAudioSend(byte1,byte2,byte3,byte4,portAudio);
				break;
				}
				
			}
			catch(Exception e){
				Log.v("Java", String.format("\nException e = %s\n",e.toString()));
				Toast.makeText(context, "Endereço IP invalido!", Toast.LENGTH_SHORT);
				
				//TODO: chamar toast para informar usuário
			}
			
			
			
		
			Toast.makeText(context, "Endereço IP valido!", Toast.LENGTH_SHORT);
			
			
			//Tira o teclado da tela: 
			imm = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
			//imm.hideSoftInputFromWindow(etxtIPsend.getWindowToken(), 0);
			imm.hideSoftInputFromWindow(eTxtAudioPortSend.getWindowToken(), 0);
			
				
		}
		
	}
   

   //Initiate the camera with 4 bytes address defined by user
   private void initCameraPreview(int b1,int b2, int b3, int b4, int port){
		  
	   Log.v("Java", String.format("initCameraPreview --> address to send video = %d.%d.%d.%d:%d\n",b1,b2,b3,b4,port));
	  
	   mPreview = new Preview(this,b1,b2,b3,b4,port);
	   ViewGroup.LayoutParams x = new ViewGroup.LayoutParams(320,240);
	   setContentView(mPreview, x);
   }
   //Initiate the camera with 4 bytes address defined by user
   private void initAudioSend(int b1,int b2, int b3, int b4, int port){
		  
	   Log.v("Java", String.format("initAudioSend --> address to send audio = %d.%d.%d.%d:%d\n",b1,b2,b3,b4,port));
	 	   
	   mMic = new Mic(b1,b2,b3,b4,port);
       mMic.start();
   }
   
   /**
    * mostra tela de definicao de IP destino
    * 
    */
   private void mostraTelaIPsend() {

	    Log.v("Java", String.format("chamou mostraTelaIPsend()"));
	   
	    setContentView(R.layout.ipsend_layout);
	    
	    //Invoca os objetos das Views
	    TextView txtView = (TextView) findViewById(R.id.txtViewIPsend);
	    etxtIPsend = (EditText) findViewById(R.id.eTxtIPsend);
	    eTxtVideoPortSend = (EditText) findViewById(R.id.eTxtVideoPortSend);
	    eTxtAudioPortSend = (EditText) findViewById(R.id.eTxtAudioPortSend);
	    buttonIPsend = (Button) findViewById(R.id.buttonIPsend);
	    buttonIPsendAudio = (Button) findViewById(R.id.buttonIPsendAudio);
	    buttonIPsendVideo = (Button) findViewById(R.id.buttonIPsendVideo);
	    
	    //Set the event handler for the buttonIPsend 
		OnClickBtnIPSend buttonIPsendListener = new OnClickBtnIPSend();
		OnClickBtnIPSend buttonIPsendAudioListener = new OnClickBtnIPSend();
		OnClickBtnIPSend buttonIPsendVideoListener = new OnClickBtnIPSend();
		
		
		buttonIPsend.setOnClickListener(buttonIPsendListener);	  
		buttonIPsendAudio.setOnClickListener(buttonIPsendAudioListener);	
		buttonIPsendVideo.setOnClickListener(buttonIPsendVideoListener);	
	}
   
   
   
   @Override
   public boolean onTouchEvent(MotionEvent event) {
	// TODO Auto-generated method stub
	  
	   
	   if(event.getAction() == MotionEvent.ACTION_DOWN)
	   if(!flagFullScreen){
     		 getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
       	     WindowManager.LayoutParams.FLAG_FULLSCREEN);
        flagFullScreen = true;
     	 }
     	 else {
     		
     		getWindow().clearFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
     		
        flagFullScreen = false;
     	 }
	return super.onTouchEvent(event);
   }
    
    
    public boolean onKeyDown(int keyCode, final KeyEvent event) {
        super.onKeyDown(keyCode, event);
        // Overrides Back key to use in our app
        Log.v("Java", String.format("onKeyEvent - KEYCODE = %d\n",keyCode));
        
        if( keyCode == KeyEvent.KEYCODE_BACK){
        	 Log.v("Java", String.format("onKeyEvent - EXIT \n"));
        	 
        }
        switch(keyCode){
        case 24: if(mGLView!=null){
        	mGLView.volumeUp();
        	
        	//Toast.makeText(this, "Volume = "+mGLView.getVolume(), 0).show();
        	
            }
        	break;
        case 25: if(mGLView!=null){
        		mGLView.volumeDown();
        		
        		//Toast.makeText(this, "Volume = "+mGLView.getVolume(), 0 ).show();
        	}
        	break;
        
        
        case 82: 
        	dialog.setClickable(true);
        	dialog.show_something();
        	break;
        	
        /*case 45: 
        	mRec.pararrec();
        	break;
        case 46:
        	mRec.iniciarrec();
        	break;*/
        }
//        if( keyCode == KeyEvent.KEYCODE_ENTER){
//       	 Log.v("Java", String.format("onKeyEvent - ENTER \n"));
//       	 if(!flagFullScreen){
//       		
//       		 getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
//         	         WindowManager.LayoutParams.FLAG_FULLSCREEN);
//        
//          
//       		 
//          flagFullScreen = true;
//       	 }
//       	 else {
//       		
//       		getWindow().clearFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
//       		
//          flagFullScreen = false;
//       	 }
//       }
 
        return true;
    }
    
    public void onConfigurationChanged(Configuration newConfig) { 
        super.onConfigurationChanged(newConfig); 
        //---code to redraw your activity here---
        //...
        Display display = ((WindowManager) getSystemService(WINDOW_SERVICE)).getDefaultDisplay();
        display.getMetrics(metrics);
        int rotation = display.getOrientation();

        //mGLView.
        Log.v("Java", String.format("Rotation = %d - Tamanho da tela: %d X %d\n",rotation,metrics.widthPixels, metrics.heightPixels));
        
        changeOrientation(metrics.widthPixels, metrics.heightPixels);
        
        
    }
    
    private DemoGLSurfaceView mGLView = null;
    
    native void changeOrientation(int w,int h);
    
    native void stopThreads();
    
    /* this is used to load the 'eadcel' library on application
     * startup. The library has already been unpacked into
     * /data/data/com.example.eadcel/lib/libeadcel.so at
     * installation time by the package manager.
     */
    static {
    	System.loadLibrary("avutil");
    	System.loadLibrary("swscale");
        System.loadLibrary("avcodec");
        System.loadLibrary("avformat");
        System.loadLibrary("thread");
    	System.loadLibrary("common");
    	System.loadLibrary("sockets");
    	System.loadLibrary("queue");
    	System.loadLibrary("net");
    	System.loadLibrary("decode");
    	System.loadLibrary("encode");
    	System.loadLibrary("eadcel");  
        
        Log.v("Java", String.format("**** CARREGOU Libraries **** \n"));
    }
}
