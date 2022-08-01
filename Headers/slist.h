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
SList list_create();

/**
 * Mete un elemento en la primera posicion de la lista
 */
void list_push(SList *list, void *data);
#endif /* __SLIST_H__ */
