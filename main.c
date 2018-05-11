#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "aviao.h"
#include "aeroporto.h"

#define NOVO_AVIAO_MIN 30
#define NOVO_AVIAO_MAX 120
#define COMBUSTIVEL_MIN 1
#define COMBUSTIVEL_MAX 10
#define TEMPO_POUSO_DECOLAGEM 40
#define TEMPO_REMOVER_BAGAGENS 90
#define TEMPO_INSERIR_BAGAGENS 110
#define TEMPO_BAGAGENS_ESTEIRA 200
#define TEMPO_SIMULACAO 10000

void *planeThread(void *arg);
aeroporto_t* meu_aeroporto;

int main (int argc, char** argv) {

	// VariÃ¡veis temporais (inicio t_)
	size_t t_novo_aviao_min, t_novo_aviao_max;
	size_t t_pouso_decolagem;
	size_t t_remover_bagagens, t_inserir_bagagens;
	size_t t_bagagens_esteira, t_simulacao;

	// VariÃ¡veis discretas (inicio n_)
	size_t n_pistas, n_portoes;
	size_t n_max_avioes_esteira, n_esteiras;
	size_t n_args;

	// VariÃ¡veis de prioridade (inicio p_)
	size_t p_combustivel_min, p_combustivel_max;

	if (argc == 5) { // Argumentos sem tempos de execuÃ§Ã£o
		t_novo_aviao_min = NOVO_AVIAO_MIN;
		t_novo_aviao_max = NOVO_AVIAO_MAX;
		t_pouso_decolagem = TEMPO_POUSO_DECOLAGEM;
		t_remover_bagagens = TEMPO_REMOVER_BAGAGENS;
		t_inserir_bagagens = TEMPO_INSERIR_BAGAGENS;
		t_bagagens_esteira = TEMPO_BAGAGENS_ESTEIRA;
		t_simulacao = TEMPO_SIMULACAO;
		p_combustivel_min = COMBUSTIVEL_MIN;
		p_combustivel_max = COMBUSTIVEL_MAX;
		n_pistas = atoi(argv[1]);
		n_portoes = atoi(argv[2]);
		n_max_avioes_esteira = atoi(argv[3]);
		n_esteiras = atoi(argv[4]);

	} else if (argc == 14) { // Argumentos com tempos de execuÃ§Ã£o
		int i = 0; // Este contador serÃ¡ incrementado antes de coletar um argumento
		t_novo_aviao_min = atoi(argv[++i]);
		t_novo_aviao_max = atoi(argv[++i]);
		p_combustivel_min = atoi(argv[++i]);
		p_combustivel_max = atoi(argv[++i]);
		t_pouso_decolagem = atoi(argv[++i]);
		n_pistas = atoi(argv[++i]);
		t_remover_bagagens = atoi(argv[++i]);
		t_inserir_bagagens = atoi(argv[++i]);
		n_portoes = atoi(argv[++i]);
		n_max_avioes_esteira = atoi(argv[++i]);
		t_bagagens_esteira = atoi(argv[++i]);
		n_esteiras = atoi(argv[++i]);
		t_simulacao = atoi(argv[++i]);

	} else { // NÃºmero incorreto de argumentos
		printf("Todas as entradas sÃ£o inteiros positivos!!\nUso:\n");
		printf("./aeroporto  NOVO_AVIAO_MIN  NOVO_AVIAO_MAX\n");
		printf("COMBUSTIVEL_MIN COMBUSTIVEL_MAX\n");
		printf("TEMPO_POUSO_DECOLAGEM  NUMERO_PISTAS  TEMPO_REMOVER_BAGAGENS\n");
		printf("TEMPO_INSERIR_BAGAGENS  NUMERO_PORTOES  MAXIMO_AVIOES_ESTEIRA\n");
		printf("TEMPO_BAGAGENS_ESTEIRA  NUMERO_ESTEIRAS  TEMPO_SIMULACAO\n");
		printf("----------OU----------\n");
		printf("./airport  NUMERO_PISTAS  NUMERO_PORTOES  MAXIMO_AVIOES_ESTEIRA  NUMERO_ESTEIRAS\n");
		return 0;
	}

	// ImpressÃ£o com os parÃ¢metros selecionados para simulaÃ§Ã£o
	printf("SimulaÃ§Ã£o iniciada com tempo total: %lu\n", t_simulacao);
	printf("Tempo para criaÃ§Ã£o de aviÃµes: %lu - %lu\n", t_novo_aviao_min, t_novo_aviao_max);
	printf("NÃºmero de pistas de pouso: %lu\n", n_pistas);
	printf("Tempo de pouso e decolagem: %lu\n", t_pouso_decolagem);
	printf("NÃºmero de portÃµes de embarque: %lu\n", n_portoes);
	printf("Tempo de inserÃ§Ã£o (%lu) e remoÃ§Ã£o (%lu) de bagagens\n", t_inserir_bagagens, t_remover_bagagens);
	printf("NÃºmero de esteiras: %lu, com %lu aviÃµes por esteira\n", n_esteiras, n_max_avioes_esteira);
	printf("Tempo das bagagens nas esteiras: %lu\n", t_bagagens_esteira);

	// InicializaÃ§Ã£o do aeroporto
	
	pthread_t* threads_created[1+t_simulacao/t_novo_aviao_min];
	
	n_args = 8;
	size_t args[8] = {n_pistas, n_portoes, n_esteiras,
				n_max_avioes_esteira,
				t_pouso_decolagem, t_remover_bagagens,
				t_inserir_bagagens, t_bagagens_esteira};

    meu_aeroporto = iniciar_aeroporto(args, n_args);

	// Descreve aqui sua simulaÃ§Ã£o usando as funÃ§Ãµes definidas no arquivo "aeroporto.h"
	// Lembre-se de implementÃ¡-las num novo arquivo "aeroporto.c"

    int counter = 0;
	srand(time(NULL));
	for (size_t i = 0; i < 2; i++) {
		int combustivel = (rand() % ((p_combustivel_max-p_combustivel_min)) + (p_combustivel_min));
		size_t combustivelAviao = (size_t)(100*(double) combustivel/p_combustivel_max);
		aviao_t* aviao = aloca_aviao(combustivelAviao, i);
		pthread_create(&aviao->thread, NULL, planeThread, (void *) aviao);
		threads_criadas[counter++] = &aviao->thread;
		usleep(100000*rand() % ((t_novo_aviao_max-t_novo_aviao_min)+t_novo_aviao_min));
		
	}
	for (int i = 0; i < counter; i++) {
		pthread_join(*threads_criadas[i], NULL);
    }

	finalizar_aeroporto(meu_aeroporto);
	return 1;
}

void *planeThread(void *arg) {
	aviao_t* plane = (aviao_t *) arg;
	aproximacao_aeroporto(meu_aeroporto, plane);
	takeoff_landing(meu_aeroporto);
	return NULL;
}