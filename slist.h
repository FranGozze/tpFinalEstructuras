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
 * Destruccion de la lista.
 */
void list_destroy(SList list, functionListFree function);

/**
 *
 */
void list_push(SList *list, void *data);
#endif /* __SLIST_H__ */
