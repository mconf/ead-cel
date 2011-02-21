#define BIG_NUMBER 123456789.0

/* estrutura para realizar benchmarks */
/* exemplo de uso para imprimir log com as estatisticas de desempenho
 * de um trecho de codigo x a cada 30 segundos:

#include eadcelnative/bench.h
frameBench medida;
initBenchVar(&medida, 30000, "Benchmark do trecho de codigo x");
while(true){ //laco qualquer dentro do programa
	...
	beginPoint(&medida);
	<trecho de codigo x>
	endPoint(&medida);
	...
}

*/
struct frameBench {
	const char* title; //nome da medida que se esta fazendo
	int tot_frames; //contador de frames
	double max_time; //maximo tempo ja contabilizado
	double min_time; //minimo tempo ja contabilizado
	double tot_time; //tempo total
	double init_time; //tempo do inicio da medida do frame atual
	double elapsed; //tempo passado entre o inicio e o final da medida do frame atual
	double ref_time; //tempo de referencia para imprimir o log
	double log_interval; //intervalo de tempo em milisegundos para imprimir na tela. 0 caso nao queira imprimir.
};

/* retorna um valor de milisegundos para o instante atual */
double now_ms(void);

/* inicializa uma variavel de benchmark para poder usa-la corretamente */
void initBenchVar(frameBench * frame, double interval, const char* title);

/* reseta uma variavel de benchmark apos um log para poder usa-la novamente */
void resetBenchVar(frameBench * frame);

/* deve ser colocado no inicio de onde se quer medir */
void beginPoint(frameBench * frame);

/* deve ser colocado no final de onde se quer medir */
void endPoint(frameBench * frame);

/* imprime na tela os dados do frame */
void logBench(frameBench * frame);
