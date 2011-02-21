package com.example.eadcel;

import android.os.SystemClock;
import android.util.Log;

class Benchmarks {	
	private double msbefore;
	private int tot_frames;
	private String nomeBench;
		
	public Benchmarks(String nome){
		nomeBench = nome;
	}
	public void resetSimpleBench(){
		tot_frames = 0;
		msbefore = SystemClock.uptimeMillis();
	}
	
	public void simpleBench(int msinterval) {
       	tot_frames++;
       	if(SystemClock.uptimeMillis() >= msbefore + msinterval){
       		Log.v("Benchmark Java", String.format("%s", nomeBench));
//    		Log.v("Java: onDrawFrame()", String.format("Passaram %d segundos:\n", msinterval/1000));
//    		Log.v("Java: onDrawFrame()", String.format("Numero de vezes que passou no trecho = %d\n", tot_frames));
    		Log.v("Benchmark Java", String.format("Frames/s = %d\n", tot_frames/(msinterval/1000)));
    		
    		QueueSize();
    		
    		resetSimpleBench();
    	}
    }
	
	public native int QueueSize();
}
