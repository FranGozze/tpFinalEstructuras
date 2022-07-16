#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"
#include "tablahash.h"
#include "slist.h"
#include "common.h"

int main()
{
    TablaHash table = readDictionary("diccionario.txt");
    char *corrections[] = malloc(sizeof(char) * 30);
    dict_entry_s *entry = create_entry("pe");
    printf("%d\n", dict_find(table, entry));
    return 0;
}