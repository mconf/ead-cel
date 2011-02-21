package com.example.eadcel;

//import android.content.Context;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.AudioTrack;
import android.media.MediaRecorder;
import android.util.Log;
//import android.view.SurfaceHolder;

class Mic extends Thread {   
	boolean running = false;
	AudioRecord record;
//	private Benchmarks mBench = null;
	 
	Mic(int b1, int b2, int b3, int b4, int port) {
	    super();
	    nativeSenderInitAudio(b1,b2,b3,b4,port);
//	    mBench = new Benchmarks("Frames de audio capturados pelo microfone e enviados para o C++");
	}
	
    /** Runs it in a new Thread. */
    public void run() {
    	int num;   	

    	int bufSizeRec = 2304;
    	int sizeUtilRec = bufSizeRec;
		
		if(  AudioRecord.getMinBufferSize(22050,
                AudioFormat.CHANNEL_CONFIGURATION_MONO,
                AudioFormat.ENCODING_PCM_16BIT) > bufSizeRec )
			bufSizeRec =  AudioRecord.getMinBufferSize(22050,
	                AudioFormat.CHANNEL_CONFIGURATION_MONO,
	                AudioFormat.ENCODING_PCM_16BIT);
		Log.v("Java", String.format("bufSizeRec = %d", bufSizeRec));
		//int sizeUtilRec = bufSizeRec;
		byte[] lin = new byte[sizeUtilRec];
		
    	//int fr = 44100/min;
    	//int sizelin = min*(fr+1);
    	//Log.v("Java", String.format("DEBUG: sizelin = %d", sizelin));
    	//byte[] lin = new byte[sizelin];
    	
    	record = null;
        record = new AudioRecord(MediaRecorder.AudioSource.MIC, 22050, AudioFormat.CHANNEL_IN_MONO, AudioFormat.ENCODING_PCM_16BIT, bufSizeRec);
        if (record.getState() != AudioRecord.STATE_INITIALIZED) {
                record = null;
                Log.v("Java", String.format("Erro: Nao foi possivel inicializar AudioRecord"));
                return;
        }
        record.startRecording();
        running = true;
        while (running) {
//        	mBench.simpleBench(5000);
        	num = record.read(lin, 0, sizeUtilRec);
        	//Log.v("Java", String.format("DEBUG: num = %d", num));
        	if(num <= 0){
        		continue;
        	}
        	/*for(int i = 0; i < sizeUtilRec; i++){
        		Log.v("Java", String.format("DEBUG: lin[%d] = %d", i, lin[i]));
        	}*/
        	nativeSenderAudio(lin);        
        }
    }   
    
    public void stopMic(){
    	running = false;
    	if (record != null) {
            record.stop();
            record.release();
    	}
    }
 
    native int nativeSenderInitAudio(int byte1,int byte2,int byte3,int byte4,int port);
    native int nativeSenderAudio(byte[] YIn);
}
