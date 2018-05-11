#ifndef AEROPORTO_H
#define AEROPORTO_H

#include "aviao.h"
#include <semaphore.h>
#include "fila.h"

typedef size_t tempo_t;

typedef struct {
	size_t n_pistas
	size_t n_portoes
	size_t n_esteiras,
	size_t n_max_avioes_esteira,
	tempo_t t_pouso_decolagem;
	tempo_t t_remover_bagagens;
	tempo_t t_inserir_bagagens;
	tempo_t t_bagagens_esteira;
	sem_t sem_pistas;
	sem_t sem_portoes;
	sem_t sem_esteiras;
	pthread_t thread;
    fila_ordenada_t *fila_pistas;
	
	// Adicionar aqui outros atributos que vocÃª achar necessÃ¡rios.
	// Exemplo: esteiras, portÃµes, etc...
} aeroporto_t;


/**
 * Esta funÃ§Ã£o deve fazer a alocaÃ§Ã£o dinÃ¢mica de um aeroporto (malloc)
 * e atribuir os parÃ¢metros (recebidos por um array de unsigned ints)
 * aos atributos da struct aeroporto
 **/
aeroporto_t* iniciar_aeroporto (size_t* args, size_t n_args);

/**
 * Esta funÃ§Ã£o deve ser chamada quando um novo aviÃ£o se aproxima
 * do aeroporto. Nesta situaÃ§Ã£o um aviÃ£o deve pousar em seguida,
 * mas somente se houver uma pista livre para ele.
 **/
void aproximacao_aeroporto (aeroporto_t* aeroporto, aviao_t* aviao);

/**
 * Esta funÃ§Ã£o deve fazer com que o aviao pouse, utilizando uma pista livre.
 * Ela nÃ£o pode ser chamada se nÃ£o houver pistas livres. Em seguida o aviÃ£o
 * deve se acoplar a um portÃ£o, caso haja um livre, se nÃ£o houver, ele deve
 * esperar.
 **/
void pousar_aviao (aeroporto_t* aeroporto, aviao_t* aviao);

/**
 * Esta funÃ§Ã£o deve acoplar um aviÃ£o a um portÃ£o de embarque livre.
 * Ela nÃ£o deve ser chamada caso nÃ£o hajam portÃµes livres. Em seguida, o
 * o aviÃ£o deve transportar suas bagagens para fora e receber novas bagagens.
 * Um aviÃ£o nÃ£o pode decolar sem receber novas bagagens.
 **/
void acoplar_portao (aeroporto_t* aeroporto, aviao_t* aviao);

/**
 * Esta funÃ§Ã£o deve levar as bagagens de um aviÃ£o para uma esteira e
 * colocar novas bagagens num aviÃ£o para que ele seja liberado para
 * decolagem. Um aviÃ£o nÃ£o pode decolar sem receber novas bagagens.
 * Um aviÃ£o nÃ£o pode receber novas bagagens sem colocar as antigas
 * em uma esteira.
 **/
void transportar_bagagens (aeroporto_t* aeroporto, aviao_t* aviao);

/**
 * Esta funÃ§Ã£o deve colocar novas bagagens numa esteira, caso ela
 * esteja disponÃ­vel. A esteira ficarÃ¡ ocupada enquanto houverem
 * bagagens nela.
 **/
void adicionar_bagagens_esteira (aeroporto_t* aeroporto, aviao_t* aviao);

/**
 * Esta funÃ§Ã£o deve fazer com que um aviÃ£o decole, caso haja
 * uma pista disponÃ­vel para tal. Um aviÃ£o que decolar deve
 * ter sua execuÃ§Ã£o terminada.
 **/
void decolar_aviao (aeroporto_t* aeroporto, aviao_t* aviao);

/**
 * Esta funÃ§Ã£o deve desalocar todos os recursos previamente
 * alocados pelo aeroporto. Retorna 1 caso bem sucedido.
 **/
int finalizar_aeroporto (aeroporto_t* aeroporto);

#endif
