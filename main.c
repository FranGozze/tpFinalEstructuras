#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"
#include "tablahash.h"
#include "slist.h"
#include "common.h"
#include "functions.h"

int main()
{
    TablaHash table = readDictionary("diccionario.txt");
    dict_entry_s *results[5] = {NULL};
    corrections("zuzone", table, results);
    printf("\n\n");
    for (int i = 0; i < 5; i++)
        if (results[i])
            printf("%s\n", results[i]->key);
    // dict_entry_s *entry = create_entry("aa");
    // printf("%d\n", dict_find(table, entry));
    return 0;
}