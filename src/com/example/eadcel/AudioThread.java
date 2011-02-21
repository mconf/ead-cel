package com.example.eadcel;

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.util.Log;
import android.widget.Toast;

class AudioThread {
	private AudioTrack mAudio;
	private byte[] mAudioBufferB;
	private int sizeUtil;
	private float volume;
	
	
	public int getVolume(){
		if(mAudio!=null)return (int)(volume*10);
		else return 0;
	}
	
	public boolean volumeUp(){
		if(mAudio!=null){
			if(volume<AudioTrack.getMaxVolume()){
				volume+=0.1;
				mAudio.setStereoVolume(volume, volume);
				
				Log.v("Java", String.format("Aumentou volume para %.2f\n",volume));
			}
				
			return true;
		}
		else return false;
	}
	
	public boolean volumeDown(){
		if(mAudio!=null){
			
			if(volume>=0.1){
				volume-=0.1;
				mAudio.setStereoVolume(volume, volume);
				Log.v("Java", String.format("Diminuiu volume para %.2f\n",volume));
			}
			
			return true;
		}
		else return false;
	}
	
	public int fillBuffer()
	{
		mAudio.write( mAudioBufferB, 0, sizeUtil );
		return 1;
	}
	
	public int initAudio(int rate, int channels, int encoding, int bufSize)
	{
		volume = (AudioTrack.getMaxVolume()-AudioTrack.getMinVolume())/2;
		Log.v("Java", String.format("Volume medio = %.2f\n",volume));
		
		
		if( mAudio == null )
		{
			channels = ( channels == 1 ) ? AudioFormat.CHANNEL_CONFIGURATION_MONO : 
											AudioFormat.CHANNEL_CONFIGURATION_STEREO;
			encoding = ( encoding == 1 ) ? AudioFormat.ENCODING_PCM_16BIT :
											AudioFormat.ENCODING_PCM_8BIT;

			sizeUtil = bufSize;
			
			if( AudioTrack.getMinBufferSize( rate, channels, encoding ) > bufSize )
				bufSize = AudioTrack.getMinBufferSize( rate, channels, encoding );
			
			mAudioBufferB = new byte[sizeUtil];
			
			mAudio = new AudioTrack(AudioManager.STREAM_MUSIC, 
										rate,
										channels,
										encoding,
										bufSize,
										AudioTrack.MODE_STREAM );
			
			mAudio.play();
				
		}
		
		mAudio.setStereoVolume(volume, volume);
		
		
		
		return mAudioBufferB.length;
	}
	
	public byte[] getBufferB()
	{
		return mAudioBufferB;
	}
	
	public int deinitAudio()
	{
		if( mAudio != null )
		{
			mAudio.stop();
			mAudio.release();
			mAudio = null;
		}
		mAudioBufferB = null;
		
		
		
		return 1;
	}
	
	public int initAudioThread()
	{
		// Make audio thread priority higher so audio thread won't get underrun
		Thread.currentThread().setPriority(Thread.MAX_PRIORITY);
		return 1;
	}
	
	native int nativeAudioInitJavaCallbacks();
}

