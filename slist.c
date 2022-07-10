#include "slist.h"
#include <stdlib.h>

SList slist_create()
{
  return NULL;
}

void slist_destroy(SList list, functionListFree function)
{
  SNodo *oldNode;
  while (list != NULL)
  {
    oldNode = list;
    list = list->sig;
    function(oldNode);
  }
}

void push(SList *list, void *data)
{
  (*list)->data = data;
}
