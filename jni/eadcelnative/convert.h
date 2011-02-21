#include <android/log.h>
#include <jni.h>

// inicializa as variaveis globais caso se queira converter de NV21 para yuv420p
void initNV21toYUV420P(int w, int h);

// converte in (passado por referencia) de nv21 (yuv420sp) para yuv420p
// chamar initNV21toYUV420p apenas antes de usar a funcao pela primeira vez
// e sempre que w ou h mudarem de valor
void NV21toYUV420P(jbyte **in);


