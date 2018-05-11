#include "aviao.h"
#include "stdlib.h"

/**
 * aviao.c
 * ImplementaÃ§Ã£o das funÃ§Ãµes do aviao.h
 * DescriÃ§Ãµes em aviao.h
 **/

aviao_t * aloca_aviao (size_t combustivel, size_t id) {
  aviao_t* aviao = (aviao_t*) malloc(sizeof(aviao_t));
  aviao->combustivel = combustivel;
  aviao->id = id;
  aviao->status = 0;
  return aviao;
}

void desaloca_aviao(aviao_t* aviao) {
    pthread_exit(&(aviao->thread)); // fim da thread do avião
    free(aviao);
}
