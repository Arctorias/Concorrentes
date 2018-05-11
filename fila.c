#include "fila.h"
#include "stdlib.h"


/**
 * fila.c
 * ImplementaCB'CB#o das funCB'CB5es da fila.h
 * DescriCB'CB5es em fila.h
 **/

elemento_t * aloca_elemento (aviao_t * dado)
{
  elemento_t *e = (elemento_t *) malloc (sizeof (elemento_t));
  el->dado = dado;
  return elemento;
}

void desaloca_elemento (elemento_t * elemento)
{
  free (elemento);
}

fila_ordenada_t * criar_fila ()
{
  fila_ordenada_t *fila =
    (fila_ordenada_t *) malloc (sizeof (fila_ordenada_t));
  fila->primeiro = NULL;
  fila->ultimo = NULL;
  fila->n_elementos = 0;
  pthread_mutex_init (&fila->mutex, NULL);
  return fila;
}

void desaloca_fila (fila_ordenada_t * fila)
{
  elemento_t *auxFirst = fila->primeiro;
  for (unsigned int i = 0; i < fila->n_elementos; i++)
    {
      elemento_t *auxNext = auxFirst->proximo;
      free (aux_primeiro);
      auxFirst = auxNext;
    }
  pthread_mutex_destroy (&fila->mutex);
  free (fila);
}

void inserir (fila_ordenada_t * fila, aviao_t * dado)
{
  pthread_mutex_lock (&fila->mutex);
  elemento_t *e = aloca_elemento (dado);
  if (fila->n_elementos == 0)
    {
      fila->primeiro = e;
      fila->ultimo = e;
    }
  else
    {
      if (dado->combustivel < 10)
	{
	  fila->primeiro->anterior = e;
	  e->proximo = fila->primeiro;
	  fila->primeiro = e;
	}
      else
	{
	  if (dado->id < fila->ultimo->dado->id)
	    {
	      elemento_t *a = fila->primeiro;
	      while (a->dado->combustivel < 10)
		{
		  a = a->proximo;
		}
	      elemento->proximo = a->proximo;
	      elemento->anterior = a;
	      a->proximo->anterior = elemento;
	      a->proximo = elemento;
	    }
	  else
	    {
	      fila->ultimo->proximo = elemento;
	      elemento->anterior = fila->ultimo;
	      fila->ultimo = elemento;
	    }
	}
    }
  fila->n_elementos++;
  pthread_mutex_unlock (&fila->mutex);
}

aviao_t * remover (fila_ordenada_t * fila)
{
  pthread_mutex_lock (&fila->mutex);
  if (fila->n_elementos == 0)
    {
      pthread_mutex_unlock (&fila->mutex);
      return NULL;
    }
  if (fila->n_elementos == 1)
    {
      aviao_t *dado = fila->primeiro->dado;
      free (fila->primeiro);
      fila->primeiro = NULL;
      fila->n_elementos--;
      pthread_mutex_unlock (&fila->mutex);
      return dado;
    }
  aviao_t *dado = fila->primeiro->dado;
  elemento_t *novo_primeiro = fila->primeiro->proximo;
  novo_primeiro->anterior = NULL;
  free (fila->primeiro);
  fila->primeiro = novo_primeiro;
  fila->n_elementos--;
  pthread_mutex_unlock (&fila->mutex);
  return dado;
}
