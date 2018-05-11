#ifndef FILA_AVIAO_H
#define FILA_AVIAO_H

#include "aviao.h"
#include "stdlib.h"

/**
 * Esta estrutura auxiliar deve facilitar a implementaÃ§Ã£o da fila ordenada.
 * Preencha a fila com elemento_t que contÃ©m os aviÃµes apontado para o
 * anterior e o prÃ³ximo. Use estes ponteiros para ordenar a fila a cada
 * insercÃ£o
 **/
typedef struct elemento_t {
  struct elemento_t * anterior;
  struct elemento_t * proximo;
  aviao_t * dado;
} elemento_t;

// Alocacao dinamica do elemento
elemento_t * aloca_elemento (aviao_t * dado);
void desaloca_elemento (elemento_t * elemento);

/**
 * Esta estrutura de dados deve conter uma fila de aviÃµes odernada por
 * prioridade.
 **/
typedef struct {
  elemento_t * primeiro;
  elemento_t * ultimo;
  size_t n_elementos;
  pthread_mutex_t mutex;
} fila_ordenada_t;

// AlocacÃ£o dinÃ¢mica da fila ordenada de aviÃµes
fila_ordenada_t * criar_fila ();

// Desaloca a fila.
// NÃ£o se esqueca de desalocar todos os elementos antes de finalizar.
void desaloca_fila (fila_ordenada_t * fila);

// Insere dados de forma ordenada na fila
// NÃ£o se esqueca de criar o elemento_t
void inserir (fila_ordenada_t * fila, aviao_t * dado);

// Remove o Ãºltimo da fila.
aviao_t * remover (fila_ordenada_t * fila);

#endif
