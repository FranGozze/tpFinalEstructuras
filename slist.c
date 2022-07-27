#include "Headers/slist.h"
#include <stdlib.h>

SList list_create()
{
  return NULL;
}

void list_push(SList *list, void *data)
{
  SList new = malloc(sizeof(SNodo));
  new->data = data;
  new->sig = *list;
  (*list) = new;
}
