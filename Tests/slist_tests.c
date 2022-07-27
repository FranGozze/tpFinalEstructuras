#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Headers/slist.h"

void test_push()
{
    SList list = list_create();
    char *test1 = malloc(sizeof(char) * 3);
    strcpy(test1, "12");
    list_push(&list, test1);
    assert(strcmp(list->data, "12") == 0);
    assert(list->sig == NULL);
    char *test2 = malloc(sizeof(char) * 3);
    strcpy(test2, "34");
    list_push(&list, test2);
    assert(strcmp(list->data, "34") == 0);
    assert(strcmp(list->sig->data, "12") == 0);
    assert(list->sig->sig == NULL);

    for (SList node = list; node;)
    {
        SList aux = node;
        node = node->sig;
        free(aux->data);
        free(aux);
    }
}

int main()
{
    test_push();
    return 0;
}