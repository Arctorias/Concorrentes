#include "aeroporto.h"
#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"

/**
 * aeroporto.c
 * ImplementaÃ§Ã£o das funÃ§Ãµes do aeroporto.h
 * DescriÃ§Ãµes em aeroporto.h
 **/

aeroporto_t* iniciar_aeroporto (size_t* args, size_t n_args) {
	aeroporto_t* aeroporto = (aeroporto_t*) malloc(sizeof(aeroporto_t));
	aeroporto->n_pistas = args[0];
	aeroporto->n_portoes = args[1];
	aeroporto->n_esteiras = args[2];
	aeroporto->n_max_avioes_esteira = args[3];
	aeroporto->t_pouso_decolagem = args[4];
	aeroporto->t_remover_bagagens = args[5];
	aeroporto->t_inserir_bagagens = args[6];
	aeroporto->t_bagagens_esteira = args[7];
	int aux = aeroporto->n_esteiras * aeroporto->n_max_avioes_esteira;
	sem_init(&aeroporto->sem_esteiras, 0, aux);
	sem_init(&aeroporto->sem_portoes, 0, aeroporto->n_portoes);
	sem_init(&aeroporto->sem_pistas, 0, aeroporto->n_pistas);
	aeroporto->fila_pistas = criar_fila();
    return aeroporto;
}

void takeoff_landing(aeroporto_t* aeroporto) {
	aviao_t* aviaoAux = remover(aeroporto->fila_pistas);
	if (aviaoAux == NULL){
		printf("\nNo clue\n");
		return;
	}
	if (aviaoAux->status == 0) {
		pousar_aviao(aeroporto, aviaoAux);
	} else {
		decolar_aviao(aeroporto, aviaoAux);
	}
}

void aproximacao_aeroporto (aeroporto_t* aeroporto, aviao_t* aviao) {
    inserir(aeroporto->fila_pistas, aviao);
	takeoff_landing(aeroporto);
    printf("Plane %zu incoming.\n", aviao->id);
}

void pousar_aviao (aeroporto_t* aeroporto, aviao_t* aviao) {
    usleep(1000*aeroporto->t_pouso_decolagem);
	printf("Plane %zu has arrived.\n", aviao->id);
	sem_wait(&aeroporto->sem_portoes);
    acoplar_portao(aeroporto, aviao);
}

void acoplar_portao (aeroporto_t* aeroporto, aviao_t* aviao) {
    printf("Plane %zu locked in gate.\n", aviao->id);
	transportar_bagagens(aeroporto, aviao);
    sem_post(&aeroporto->sem_portoes);
}

void transportar_bagagens (aeroporto_t* aeroporto, aviao_t* aviao) {
    usleep(1000*aeroporto->t_remover_bagagens);
	printf("Plane %zu unloaded baggage\n", aviao->id);
	usleep(1000*aeroporto->t_inserir_bagagens); //
	printf("Plane %zu loaded baggage\n", aviao->id);
	aviao->status = 1;
	inserir(aeroporto->fila_pistas, aviao);
	printf("Plane exiting.\n");
    takeoff_landing(aeroporto);
}

void adicionar_bagagens_esteira (aeroporto_t* aeroporto, aviao_t* aviao) {
    sem_wait(&aeroporto->sem_esteiras);
	usleep(1000*aeroporto->t_bagagens_esteira);
	printf("Plane %zu loaded baggage into lift\n", aviao->id);
    sem_post(&aeroporto->sem_esteiras);
}

void decolar_aviao (aeroporto_t* aeroporto, aviao_t* aviao) {
    usleep(1000*aeroporto->t_pouso_decolagem);
	printf("Plane %zu took off.", aviao->id);
	takeoff_landing(aeroporto);
    desaloca_aviao(aviao);
}

int finalizar_aeroporto (aeroporto_t* aeroporto) {
	sem_destroy(&(aeroporto->sem_portoes));
	sem_destroy(&(aeroporto->sem_pistas));
	sem_destroy(&(aeroporto->sem_esteiras));
	desaloca_fila(aeroporto->fila_pistas);
	free(aeroporto);
    return 1;
}
