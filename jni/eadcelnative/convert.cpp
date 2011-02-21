#include "eadcelnative/convert.h"
#include <cstring>

int pixels, halfpixels, quarterpixels, halfby;
jbyte *aux;

void initNV21toYUV420P(int w, int h){
	pixels = w*h;
	halfpixels = pixels/2;
	quarterpixels = pixels/4;
	halfby = quarterpixels+pixels;

	if(aux){
		free(aux);
	}
	aux = (jbyte *) malloc(halfpixels);
}

void NV21toYUV420P(jbyte **in){
	memcpy(aux,&(*in)[pixels],halfpixels);
	int count = -pixels;
	for(int i = pixels; i < halfby; i++){
		(*in)[i+quarterpixels] = aux[i+count];
		count++;
		(*in)[i] = aux[i+count];
	}
}
