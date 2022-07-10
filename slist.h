#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>

typedef void (*functionListFree)(void *data);

typedef struct _SNodo
{
  void *data;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;

/**
 * Devuelve una lista vacía.
 */
SList slist_create();

/**
 * Destruccion de la lista.
 */
void slist_destroy(SList list, functionListFree function);

/**
 * Determina si la lista es vacía.
 */
int slist_vacia(SList list);

/**
 *
 */
void push(SList *list, void *data);
#endif /* __SLIST_H__ */
