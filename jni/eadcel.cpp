#include <android/log.h>
#include <jni.h>

//Instrucoes: descomentar os includes desejados e comentar os includes que estavam ativos
//1) Teste x:
//#include <x.h>

//2) Teste das libs do IVA:
#include "eadcelnative/opengl.h"
#include "iva/net/NetRecv.h"
#include "iva/net/NetSend.h"
#include "iva/decode/DecodeVideo.h"
#include "iva/decode/DecodeAudio.h"
#include "iva/encode/EncodeVideo.h"
#include "iva/encode/EncodeAudio.h"
#include "iva/encode/EncodeVideoParams.h"
#include "iva/encode/EncodeAudioParams.h"
#include "eadcelnative/bench.h"
#include "eadcelnative/convert.h"
#include "eadcelnative/params.h"

#ifdef __cplusplus
extern "C"{
#endif

/* flag p/ finalizar programa */
bool flagReceive = true;

/* flag p/ exibir ou nao o video */
bool flagVideo = true;

/* variaveis globais para o iva */
queue_t *frames_video; //frames codificados de entrada de video
queue_t *frames_audio; //frames codificados de entrada de audio
queue_t *frames; //frames decodificados de audio/video de saída
QueueExtraData * extraData;
uint32_t timestamp, outbufSize;
uint8_t * outbuffer;
queue_consumer_t *_consumer;

queue_t *frames_video_raw; //frames de video da captura da camera nao codificados
queue_t *frames_audio_raw; //frames de audio da captura da camera nao codificados
queue_t *frames_video_send; //frames de video codificados prontos para serem enviados
queue_t *frames_audio_send;
queue_consumer_t *_encode_consumer; // consumidor dos frames_video_raw p/ a encode
jbyte *im_Y;
jbyte *im_Yaudio;
QueueExtraDataVideo * extraCapVideo;
QueueExtraDataAudio * extraCapAudio;
NetSend *netSendVideo;
NetSend *netSendAudio;
EncodeVideo *video_enc;
EncodeAudio *audio_enc;


/* variaveis globais para o video */
static JNIEnv* JavaEnv = NULL;
static jobject JavaRenderer = NULL;
static jclass JavaRendererClass = NULL;
static jmethodID JavaSwapBuffers = NULL;
int w, h, dw, dh, wmax=0, hmax=0;

/* constantes para o audio */
#define AUDIO_FREQ 22050
#define CHANNELS 1
#define BPS 2
#define SIZE_AUDIO_BUF 2304

/* variaveis globais para o audio */
jobject JavaAudioThread = NULL;
jmethodID JavaInitAudio = NULL;
jmethodID JavaDeinitAudio = NULL;
JavaVM *jniVM = NULL;
jmethodID JavaFillBuffer = NULL;
jbyteArray audioBufferJNIB = NULL;
int8_t * audioBufferB = NULL;

int nativeAudioInitAudio(JNIEnv *jniEnv, jobject thiz){
	/* inicializa audio */
	jniVM->AttachCurrentThread(&jniEnv, NULL);
	if( !jniEnv )
	{
		__android_log_print(ANDROID_LOG_DEBUG, "ERRO", "Java VM AttachCurrentThread() failed");
		return (-1);
	}

	size_t audioBufferSize = 0;
	audioBufferSize = jniEnv->CallIntMethod( JavaAudioThread, JavaInitAudio,
						(jint)AUDIO_FREQ, (jint)CHANNELS,
						(jint)(( BPS == 2 ) ? 1 : 0), (jint)SIZE_AUDIO_BUF);

	if( audioBufferSize == 0 )
	{
		__android_log_print(ANDROID_LOG_INFO, "ERRO", "failed to get audio buffer from JNI");
//		ANDROIDAUD_CloseAudio(this); TODO: implementar CloseAudio
		return(-1);
	}

	return 1;
}

int nativeAudioInitThread(JNIEnv *jniEnv, jobject thiz){
	/* inicializa thread */
	jmethodID JavaInitThread = NULL;
	jclass JavaAudioThreadClass = NULL;
	jniVM->AttachCurrentThread(&jniEnv, NULL);
	JavaAudioThreadClass = jniEnv->GetObjectClass(JavaAudioThread);
	/* HACK: raise our own thread priority to max to get rid of "W/AudioFlinger: write blocked for 54 msecs" errors */
	JavaInitThread = jniEnv->GetMethodID(JavaAudioThreadClass, "initAudioThread", "()I");
	jniEnv->CallIntMethod( JavaAudioThread, JavaInitThread );

	jmethodID JavaGetBuffer = NULL;
	jboolean isCopy = JNI_TRUE;
	JavaFillBuffer = jniEnv->GetMethodID(JavaAudioThreadClass, "fillBuffer", "()I");
	JavaGetBuffer = jniEnv->GetMethodID(JavaAudioThreadClass, "getBufferB", "()[B");
	audioBufferJNIB = (_jbyteArray*)jniEnv->CallObjectMethod( JavaAudioThread, JavaGetBuffer );
	audioBufferB = (int8_t*)jniEnv->GetByteArrayElements(audioBufferJNIB, &isCopy);
	if( !audioBufferB )
	{
		__android_log_print(ANDROID_LOG_ERROR, "ERRO", "JNI::GetByteArrayElements() failed! we will crash now");
		return (-1);
	}
	if( isCopy == JNI_TRUE )
		__android_log_print(ANDROID_LOG_ERROR, "WARNING", "JNI returns a copy of byte (or short) array - no audio will be played");
	memset(audioBufferB, '\0', SIZE_AUDIO_BUF);

	return 1;
}

jint Java_com_example_eadcel_DemoRenderer_nativeVideoInitJavaCallbacks(JNIEnv *jniEnv, jobject thiz){
	/* inicializa callbacks */
	JavaEnv = jniEnv;
	JavaRenderer = thiz;
	JavaRendererClass = JavaEnv->GetObjectClass(thiz);
	JavaSwapBuffers = JavaEnv->GetMethodID(JavaRendererClass, "swapBuffers", "()I");
	return 1;
}

jint Java_com_example_eadcel_AudioThread_nativeAudioInitJavaCallbacks(JNIEnv *jniEnv, jobject thiz){
	/* inicializa callbacks */
	jclass JavaAudioThreadClass = NULL;
	JavaAudioThread = jniEnv->NewGlobalRef(thiz);
	JavaAudioThreadClass = jniEnv->GetObjectClass(JavaAudioThread);
	JavaInitAudio = jniEnv->GetMethodID(JavaAudioThreadClass, "initAudio", "(IIII)I");
	JavaDeinitAudio = jniEnv->GetMethodID(JavaAudioThreadClass, "deinitAudio", "()I");
	return 1;
}

int nativeAudioDeinitAudio(JNIEnv *jniEnv, jobject thiz){
	/* fecha audio */
	jniVM->AttachCurrentThread(&jniEnv, NULL);
	audioBufferJNIB = NULL;
	audioBufferB = NULL;
	jniEnv->CallIntMethod( JavaAudioThread, JavaDeinitAudio );
	return 1;
}

int nativeAudioDeinitThread(JNIEnv *jniEnv, jobject thiz){
	/* fecha thread */
	jniVM->DetachCurrentThread();

	return 1;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved)
{
	jniVM = vm;
	return JNI_VERSION_1_2;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved)
{
	jniVM = vm;
};


jint Java_com_example_eadcel_DemoRenderer_nativeRender(JNIEnv *env, jobject obj,jint width,jint height){
	/* inicializa variaveis de benchmark */
	frameBench audio, video;
	initBenchVar(&audio, 30000, "Benchmark do trecho de codigo de execução de audio");
	initBenchVar(&video, 30000, "Benchmark do trecho de codigo de execução de video");
	
	__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "Tamanho da tela disponível: w = %d h = %d \n",width,height);

	flagReceive = true;


	wmax = width;
	hmax = height;


	IvaString ipStr("127.0.0.1");
	IPv4 ipv4(ipStr);

	//audio e video
	frames = queue_create(); //fila que recebe os frames de audio e video decodificados do ivaeadcel
	_consumer = queue_registerConsumer(frames);

	//audio
	frames_audio = queue_create(); //fila que recebe os frames de audio codificados do iva
	NetRecv * _netAudio = new NetRecv(NET_TYPE_AUDIO, frames_audio);
	__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "NetRecv p/ audio criada!\n");
	_netAudio->start(ipv4, 12002);
	__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "NetRecv p/ audio iniciada!\n");
	DecodeAudio *audio_dec;
	audio_dec = new DecodeAudio();
	audio_dec->open(COMMON_CODEC_AUDIO_MP2);
	audio_dec->start(frames_audio, frames);
	__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "decode audio iniciada!\n");
	nativeAudioInitAudio(env, obj);
	nativeAudioInitThread(env, obj);

	//video
	frames_video = queue_create(); //fila que recebe os frames de video codificados do iva
	NetRecv * _netVideo = new NetRecv(NET_TYPE_VIDEO, frames_video);
	__android_log_print(ANDROID_LOG_DEBUG,  "TesteReceive", "NetRecv p/ video criada!\n");
	_netVideo->start(ipv4, 12001);
	__android_log_print(ANDROID_LOG_DEBUG,  "TesteReceive", "NetRecv p/ video iniciada!\n");
	DecodeVideo *video_dec;
	video_dec = new DecodeVideo();
	video_dec->open(COMMON_CODEC_VIDEO_MPEG4);
	video_dec->start(frames_video, frames);
	__android_log_print(ANDROID_LOG_DEBUG,  "TesteReceive", "decode video iniciada!\n");

	/* achouav:
	 * 0: nao achou nenhum frame ainda
	 * 1: achou frame de audio apenas
	 * 2: achou frame de video apenas
	 * 3: achou frame de audio e video */
	int achouav = 0;

	int wp2, hp2, Size;
	uint8_t *aux;

	//wmax = width;
	//hmax = height;

	w=0;h=0,dw=0,dh=0;

	/* primeiro while:
	 * aguarda ate receber o primeiro frame,
	 * detecta se ele e de audio ou de video,
	 * faz a inicializacao correspondente
	 * e sai do laco */
	while(flagReceive){
		if (queue_dequeue(_consumer, &aux, &outbufSize, &timestamp, &extraData) != E_OK) {
			continue;
		}
		switch(extraData->getType()){
			case QueueExtraData::EXTRA_DATA_AUDIO:
				//TODO: inicializa audio aqui e obtem os valores de frequencia, canais, etc
				__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "detectou primeiro frame de audio ...\n");
				achouav = 1;
				break;
			case QueueExtraData::EXTRA_DATA_VIDEO:
				//inicializa video aqui e obtem os valores de resolucao, etc
				__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "detectou primeiro frame de video ...\n");
				__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "detectando tamanho do vídeo ...\n");
				QueueExtraDataVideo * extraDataVideo;
				extraDataVideo = (QueueExtraDataVideo *)extraData;
				w = extraDataVideo->getWidth();
				h = extraDataVideo->getHeight();

				dw = (wmax - w)/2;
				dh = (hmax - h)/2;
				__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "wmax = %d, hmax = %d\n",wmax,hmax);
				wp2 = next_power_of_2(w);
				hp2 = next_power_of_2(h);
				__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "w = %d, h = %d, wp2 = %d, hp2 = %d\n", w, h, wp2, hp2);
				initGL(w,h);
				Size = avpicture_get_size(PIX_FMT_RGB565LE, wp2, hp2);
				outbuffer = (uint8_t *) malloc(Size);
				for(int i = 0; i < Size; i++){
					outbuffer[i] = 0;
				}
				aplly_first_texture(outbuffer, wp2, hp2);
				free(outbuffer);
				achouav = 2;
				break;
		}
		queue_free(_consumer);
		aux = NULL;
		free(aux);
		if(achouav != 0){
			//caso tenha detectado o tipo do primeiro frame, sai do while
			break;
		}
	}

	/* segundo while
	 * ate o momento o programa detectou apenas um tipo de frame (audio ou video)
	 * este while apenas renderiza os frames do tipo que ja foi detectado
	 * caso seja detectado o outro tipo, ele e inicializado e sai do laco */
	while(flagReceive){
		if (queue_dequeue(_consumer, &aux, &outbufSize, &timestamp, &extraData) != E_OK) {
			continue;
		}
		switch(extraData->getType()){
			case QueueExtraData::EXTRA_DATA_AUDIO:
				switch(achouav){
					case 1:
						//audio ja foi inicializado. Renderiza frame de audio
						beginPoint(&audio);
						memcpy(audioBufferB, aux, outbufSize);
						env->CallIntMethod( JavaAudioThread, JavaFillBuffer );
						endPoint(&audio);
						break;
					case 2:
						//TODO: inicializa audio aqui e obtem os valores de frequencia, canais, etc
						__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "detectou primeiro frame de audio ...\n");
						achouav = 3;
						break;
				}
				break;
			case QueueExtraData::EXTRA_DATA_VIDEO:
				switch(achouav){
					case 1:
						//inicializa video aqui e obtem os valores de resolucao, etc
						__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "detectou primeiro frame de video ...\n");
						__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "detectando tamanho do vídeo ...\n");
						QueueExtraDataVideo * extraDataVideo;
						extraDataVideo = (QueueExtraDataVideo *)extraData;
						w = extraDataVideo->getWidth();
						h = extraDataVideo->getHeight();
						dw = (wmax - w)/2;
						dh = (hmax - h)/2;
						__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "wmax = %d, hmax = %d\n",wmax,hmax);
						wp2 = next_power_of_2(w);
						hp2 = next_power_of_2(h);
						__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "w = %d, h = %d, wp2 = %d, hp2 = %d\n", w, h, wp2, hp2);
						initGL(w,h);
						Size = avpicture_get_size(PIX_FMT_RGB565LE, wp2, hp2);
						outbuffer = (uint8_t *) malloc(Size);
						for(int i = 0; i < Size; i++){
							outbuffer[i] = 0;
						}
						aplly_first_texture(outbuffer, wp2, hp2);
						free(outbuffer);
						achouav = 3;
						break;
					case 2:
						//video ja foi inicializado. Renderiza frame de video
						beginPoint(&video);
						update_frame(aux, w, h, dw, dh);
						JavaEnv->CallIntMethod( JavaRenderer, JavaSwapBuffers );
						endPoint(&video);
						break;
				}
				break;
		}
		queue_free(_consumer);
		aux = NULL;
		free(aux);
		if(achouav == 3){
			//caso um frame de audio e um de video ja tenham sido detectados pelo programa, sai do while
			break;
		}
	}
	__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "wx = %d, hx =%d\n", dw, dh);
	__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "Ambos os tipos de frame ja foram detectados\n");
	/* ultimo while
	 * neste momento ja foram detectados os dois tipos de frame
	 * este e o while comum */
	while(flagReceive){
		if (queue_dequeue(_consumer, &aux, &outbufSize, &timestamp, &extraData) != E_OK) {
			continue;
		}
		switch(extraData->getType()){
			case QueueExtraData::EXTRA_DATA_AUDIO:
				beginPoint(&audio);
				memcpy(audioBufferB, aux, outbufSize);
				env->CallIntMethod( JavaAudioThread, JavaFillBuffer );
				endPoint(&audio);
				break;
			case QueueExtraData::EXTRA_DATA_VIDEO:
				beginPoint(&video);
				//if(flagVideo){
				update_frame(aux, w, h, dw, dh);
				JavaEnv->CallIntMethod( JavaRenderer, JavaSwapBuffers );
				//}
				endPoint(&video);
				break;
		}
		queue_free(_consumer);
		aux = NULL;
		free(aux);
	}

	if(!flagVideo){
		video_dec->close();
		__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "Video desabilitado! Finalizou decodificador de vídeo\n");
		_netVideo->stop();
		__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "Video desabilitado! Finalizou recebimento de vídeo\n");
		flagReceive = true;

		while(flagReceive){
				if (queue_dequeue(_consumer, &aux, &outbufSize, &timestamp, &extraData) != E_OK) {
					continue;
				}
				if(extraData->getType()==QueueExtraData::EXTRA_DATA_AUDIO){
				memcpy(audioBufferB, aux, outbufSize);
				env->CallIntMethod( JavaAudioThread, JavaFillBuffer );
				}

				queue_free(_consumer);
				aux = NULL;
				free(aux);
			}
	}
	else {
		video_dec->close();
		__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "Finalizou decodificador de vídeo\n");
		_netVideo->stop();
		__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "Finalizou recebimento de vídeo\n");
	}

	audio_dec->close();
	__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "Finalizou decodificador de áudio\n");
	_netAudio->stop();
	__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "Finalizou recebimento de áudio\n");

	nativeAudioDeinitAudio(env, obj);
	__android_log_print(ANDROID_LOG_DEBUG,  "NativeRender", "Finalizou audiotrack\n");
	return 1;
}

void Java_com_example_eadcel_eadcel_videoFlagOff(JNIEnv *env,jobject obj){
	flagVideo = false;
	flagReceive = false;
}

void Java_com_example_eadcel_eadcel_videoFlagOn(JNIEnv *env,jobject obj){
	flagVideo = true;
}


jint
Java_com_example_eadcel_Benchmarks_QueueSize(JNIEnv * env, jobject obj)
{

	//__android_log_print(ANDROID_LOG_DEBUG,  "QueueSize", "video = %d audio = %d frames out = %d\n",queue_length(frames_video),queue_length(frames_audio),queue_length(frames));

	__android_log_print(ANDROID_LOG_DEBUG,  "QueueSize", "videoraw = %d videosend = %d\n",queue_length(frames_video_raw),queue_length(frames_video_send));

//	return queue_length(frames);

	return 0;
}

void Java_com_example_eadcel_eadcel_stopThreads(JNIEnv *env,jobject obj)
{
	__android_log_print(ANDROID_LOG_DEBUG,  "(eadcel.cpp)Java_com_example_eadcel_stopThreads", "Finalizando threads\n");

	flagReceive = false;
}

void Java_com_example_eadcel_eadcel_changeOrientation(JNIEnv *env,jobject obj,jint width,jint height)
{
	wmax=width;
	hmax=height;

	if(w>0){
	if(width>w)dw = (width - w)/2;
	else dw = 0;
	if(height>h)dh = (height - h)/2;
	else dh = 0;

	}
	__android_log_print(ANDROID_LOG_DEBUG,  "(eadcel.cpp)Java_com_example_eadcel_changeOrientation", "wmax=%d, hmax=%d --> w=%d dw=%d h=%d dh=%d\n",wmax,hmax,w,dw,h,dh);

}

frameBench audiocapt;
void Java_com_example_eadcel_Mic_nativeSenderInitAudio(JNIEnv *env, jclass jc,jint byte1, jint byte2, jint byte3, jint byte4, jint port){

	__android_log_print(ANDROID_LOG_DEBUG,  "(eadcel.cpp)Java_com_example_eadcel_Preview_nativeSenderInitAudio", "inicio\n");

	initBenchVar(&audiocapt, 30000, "CAPTURA DE AUDIO");

	frames_audio_raw = queue_create();
//	_encode_consumer = queue_registerConsumer(frames_video_raw);

	frames_audio_send = queue_create();

	__android_log_print(ANDROID_LOG_DEBUG,  "(eadcel.cpp)Java_com_example_eadcel_Preview_nativeSenderInitAudio", "criacao das filas OK!\n");

//	extraCapVideo = new QueueExtraDataVideo();
//	extraCapVideo.setBitrate(800);
//	extraCapVideo.setCodecId(COMMON_CODEC_VIDEO_MPEG4);
//	extraCapVideo.setFps(10); /// \todo Usar fps setado externamente na capenc
//	extraCapVideo.setWidth(720);
//	extraCapVideo.setHeight(480);
//	extraCapVideo.setVideoId(0);

	EncodeAudioParams * paramsAudio = new EncodeAudioParams();

	__android_log_print(ANDROID_LOG_DEBUG,  "(eadcel.cpp)Java_com_example_eadcel_Preview_nativeSenderInitAudio", "erro na ini do EncodeAudioParams\n");

	extraCapAudio = new QueueExtraDataAudio();
	//extraCapVideo.setCodecId(0);
	//extraCapVideo.setFps(30);
	//extraCapVideo.setWidth(paramsVideo->image->getFrameWidth());
	//extraCapVideo.setHeight(paramsVideo->image->getFrameHeight());
	//extraCapVideo.setPixelFmt(paramsVideo->image->getPixelFormat());
	//extraCapVideo.setVideoId(0);
	audio_enc = new EncodeAudio();

	setAudioParams(&paramsAudio);

	__android_log_print(ANDROID_LOG_DEBUG,  "(eadcel.cpp)Java_com_example_eadcel_Preview_nativeSenderInitAudio", "QueueExtraDataAudio OK\n");

	audio_enc->open(paramsAudio);

	__android_log_print(ANDROID_LOG_DEBUG,  "(eadcel.cpp)Java_com_example_eadcel_Preview_nativeSenderInitAudio", "passou pelo audio_enc\n");

	audio_enc->start(frames_audio_raw, frames_audio_send);

	__android_log_print(ANDROID_LOG_DEBUG,  "(eadcel.cpp)Java_com_example_eadcel_Preview_nativeSenderInitAudio", "passou pelo start do audio_enc\n");


	netSendAudio = new NetSend(NET_TYPE_AUDIO, frames_audio_send, 0/*apr.netcom.client->getSessionData().getSessionId()*/);

	__android_log_print(ANDROID_LOG_DEBUG,  "(eadcel.cpp)Java_com_example_eadcel_Preview_nativeSenderInitAudio", "inicializou o NetSendAudio\n");

	int error = netSendAudio->start(IPv4(byte1,byte2,byte3,byte4), port);
	__android_log_print(ANDROID_LOG_DEBUG,  "eadcel.cpp", "ip: %d.%d.%d.%d:%d\n", byte1,byte2,byte3,byte4,port);
	if(error!=E_OK)
		__android_log_print(ANDROID_LOG_DEBUG,  "(eadcel.cpp)Java_com_example_eadcel_Preview_nativeSenderInitAudio", "erro no netSendAudio->start!\n");

}

jint Java_com_example_eadcel_Mic_nativeSenderAudio(JNIEnv *env, jclass jc, jbyteArray YIn) {
	beginPoint(&audiocapt);
	im_Yaudio = env->GetByteArrayElements(YIn, 0);
    //-----
    // neste momento o im_Yaudio tem os dados RAW do frame atual
    //-----

	Milliseconds ts;
    ts.setTimestamp();
    uint32_t tempo = ts.getTime();
    if(queue_length(frames_audio_raw) < 5){
    	if(queue_enqueue(frames_audio_raw, (uint8_t*)im_Yaudio, sizeof(im_Yaudio), tempo, extraCapAudio) != E_OK){
    		__android_log_print(ANDROID_LOG_DEBUG, "eadcel.cpp","erro no enqueue. Timestamp = %d", tempo);
    	}
    } /*else {
    	env->ReleaseByteArrayElements(YIn, im_Y, JNI_ABORT);
    	usleep(200);
    	return 0;
    }*/
    env->ReleaseByteArrayElements(YIn, im_Yaudio, JNI_ABORT);
    endPoint(&audiocapt);
    return 0;
}

frameBench videocapt;
void Java_com_example_eadcel_Preview_nativeSenderInitVideo(JNIEnv *env, jclass jc, jint byte1, jint byte2, jint byte3, jint byte4, jint port){
	__android_log_print(ANDROID_LOG_DEBUG,  "(eadcel.cpp)Java_com_example_eadcel_Preview_nativeSenderInitVideo", "inicio\n");

	initBenchVar(&videocapt, 30000, "CAPTURA DE VIDEO");

	frames_video_raw = queue_create();
	frames_video_send = queue_create();
	__android_log_print(ANDROID_LOG_DEBUG,  "(eadcel.cpp)Java_com_example_eadcel_Preview_nativeSenderInitVideo", "criacao das filas OK!\n");

	EncodeVideoParams * paramsVideo = new EncodeVideoParams();
	__android_log_print(ANDROID_LOG_DEBUG,  "(eadcel.cpp)Java_com_example_eadcel_Preview_nativeSenderInitVideo", "erro na ini do EncodeVideoParams\n");

	video_enc = new EncodeVideo();

	initNV21toYUV420P(320,240);

	setVideoParams(&paramsVideo);
	__android_log_print(ANDROID_LOG_DEBUG,  "(eadcel.cpp)Java_com_example_eadcel_Preview_nativeSenderInitVideo", " setVideoParams(&paramsVideo) OK\n");

	video_enc->open(paramsVideo);
	__android_log_print(ANDROID_LOG_DEBUG,  "(eadcel.cpp)Java_com_example_eadcel_Preview_nativeSenderInitVideo", "passou pelo video_enc\n");

	video_enc->start(frames_video_raw, frames_video_send);
	__android_log_print(ANDROID_LOG_DEBUG,  "(eadcel.cpp)Java_com_example_eadcel_Preview_nativeSenderInitVideo", "passou pelo start do video_enc\n");

	netSendVideo = new NetSend(NET_TYPE_VIDEO, frames_video_send);
	__android_log_print(ANDROID_LOG_DEBUG,  "(eadcel.cpp)Java_com_example_eadcel_Preview_nativeSenderInitVideo", "inicializou o NetSendVideo\n");


	int error = netSendVideo->start(IPv4(byte1,byte2,byte3,byte4), port); //old
	__android_log_print(ANDROID_LOG_DEBUG,  "eadcel.cpp", "ip: %d.%d.%d.%d:%d\n", byte1,byte2,byte3,byte4,port);

	//TODO: adaptar o string ipSend e a porta
	//IvaString strIPsend = new IvaString((const char *)ipSend);
	//int error = netSendVideo->start(IPv4(strIPsend), port);

	if(error!=E_OK)
		__android_log_print(ANDROID_LOG_DEBUG,  "(eadcel.cpp)Java_com_example_eadcel_Preview_nativeSenderInitVideo", "erro no netSendVideo->start!\n");

	//else __android_log_print(ANDROID_LOG_DEBUG,  "(eadcel.cpp)Java_com_example_eadcel_Preview_nativeSenderInitVideo", "netSendVideo->start(%s,%d) OK!\n",ipSend,port);

}


jint Java_com_example_eadcel_Preview_nativeSenderVideo(JNIEnv *env, jclass jc, jbyteArray YIn) {
	beginPoint(&videocapt);
	im_Y = env->GetByteArrayElements(YIn, 0);
    //-----
    // neste momento o im_Y tem os dados YUV do frame atual
    //-----
	//converte do formato padrao de captura do android (NV21 == yuv420sp)
	//para o formato yuv420p, porque o ffmpeg nao codifica NV21 em mpeg4 diretamente
	NV21toYUV420P(&im_Y);

    Milliseconds ts;
    ts.setTimestamp();
    uint32_t tempo = ts.getTime();
    if(queue_length(frames_video_raw) < 5){
    	if(queue_enqueue(frames_video_raw, (uint8_t*)im_Y, sizeof(im_Y), tempo, extraCapVideo) != E_OK){
    		__android_log_print(ANDROID_LOG_DEBUG, "eadcel.cpp","erro no enqueue. Timestamp = %d", tempo);
    	}
    } /*else {
    	env->ReleaseByteArrayElements(YIn, im_Y, JNI_ABORT);
    	usleep(200);
    	return 0;
    }*/
    env->ReleaseByteArrayElements(YIn, im_Y, JNI_ABORT);
    endPoint(&videocapt);
    return 0;
}



#ifdef __cplusplus
}
#endif
