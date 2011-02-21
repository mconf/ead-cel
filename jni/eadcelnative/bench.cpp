#include <android/log.h>
#include <time.h>
#include <algorithm>
#include "eadcelnative/bench.h"
using namespace std;

void initBenchVar(frameBench * frame, double interval, const char* title){
	frame->title = title;
	frame->tot_frames = 0;
	frame->max_time = -1.0;
	frame->min_time = BIG_NUMBER;
	frame->tot_time = 0.0;
	frame->init_time = 0.0;
	frame->elapsed = 0.0;
	frame->ref_time = 0.0;
	frame->log_interval = interval;
}

void resetBenchVar(frameBench * frame){
	frame->tot_frames = 0;
	frame->max_time = -1.0;
	frame->min_time = BIG_NUMBER;
	frame->tot_time = 0.0;
	frame->init_time = 0.0;
	frame->elapsed = 0.0;
	frame->ref_time = 0.0;
}

void beginPoint(frameBench * frame){
	frame->init_time = now_ms();
	if(frame->ref_time == 0.0){
		frame->ref_time = frame->init_time;
	}
}

void endPoint(frameBench * frame){
	frame->tot_frames++;
	double now = now_ms();
	frame->elapsed = now-frame->init_time;
	frame->tot_time += frame->elapsed;
	frame->max_time = max(frame->elapsed, frame->max_time);
	frame->min_time = min(frame->elapsed, frame->min_time);
	if(frame->log_interval > 0.0 && (now - frame->ref_time) > frame->log_interval){
		logBench(frame);
		resetBenchVar(frame);
	}
}

void logBench(frameBench * frame){
	__android_log_print(ANDROID_LOG_DEBUG,  "Bench", "%s\n", frame->title);
	__android_log_print(ANDROID_LOG_DEBUG,  "Bench", "Intervalo de monitoramento = %.2fms\n", frame->log_interval);
	__android_log_print(ANDROID_LOG_DEBUG,  "Bench", "Tempo total no trecho = %.2fms (%.0f%% do intervalo)\n", frame->tot_time, (frame->tot_time*100)/frame->log_interval);
	__android_log_print(ANDROID_LOG_DEBUG,  "Bench", "Numero de medicoes = %d\n", frame->tot_frames);
	__android_log_print(ANDROID_LOG_DEBUG,  "Bench", "Medicoes/s = %.0f\n", frame->tot_frames/(frame->log_interval/1000));
	__android_log_print(ANDROID_LOG_DEBUG,  "Bench", "Tempo maximo = %.2fms (Tempo minimo = %.2fms)\n", frame->max_time, frame->min_time);
	__android_log_print(ANDROID_LOG_DEBUG,  "Bench", "Tempo medio = %.2fms\n", frame->tot_time/frame->tot_frames);
}

double now_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec*1000. + tv.tv_usec/1000.;
}
