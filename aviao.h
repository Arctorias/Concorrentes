#ifndef AVIAO_H
#define AVIAO_H

#include <pthread.h>

/**
 * O id deve ser usado pra indentificar individualmente cada aviÃ£o e
 * sua a situaÃ§Ã£o do aviÃ£o no programa.
 **/
typedef struct {
  pthread_t thread; // Uso dos recursos pelo aviÃ£o Ã© monitorado pela thread
  size_t combustivel; // Indica prioridade do aviÃ£o para pousar
  size_t id; // Identificador do aviÃ£o: 0, 1, 2, ...
  int status;
} aviao_t;

// Estas funcoes devem cuidar da alocacao dinÃ¢mica de memÃ³ria
aviao_t * aloca_aviao (size_t combustivel, size_t id);
void desaloca_aviao (aviao_t* aviao);

#endif
