#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablahash.h"
#include "dictionary.h"
#include "common.h"

#define HASHSIZE 886987

TablaHash readDictionary(char *dictPath)
{
    FILE *file = fopen(dictPath, "rb");
    char buff[255];
    TablaHash table = new_dict(HASHSIZE);
    while (fscanf(file, "%s", buff) != EOF)
    {
        dict_entry_s *entry = create_entry(buff);
        dict_add(table, entry);
    }
    fclose(file);
    return table;
}