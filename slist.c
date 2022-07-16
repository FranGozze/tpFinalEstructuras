#include "slist.h"
#include <stdlib.h>

SList list_create()
{
  return NULL;
}

void list_destroy(SList list, functionListFree function)
{
  SNodo *oldNode;
  while (list != NULL)
  {
    oldNode = list;
    list = list->sig;
    function(oldNode);
  }
}

void list_push(SList *list, void *data)
{
  SList new = malloc(sizeof(SList));
  new->data = data;
  new->sig = *list;
  (*list) = new;
}
