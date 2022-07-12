#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablahash.h"
#include "dictionary.h"
#define HASHSIZE 620909
dict_entry_s *create_entry(char *key)
{
    dict_entry_s *entry = malloc(sizeof(dict_entry_s));
    entry->key = malloc(sizeof(char) * strlen(key) + 1);
    strcpy(entry->key, key);
    entry->hash = dict_hash(key);
    return entry;
}
unsigned dict_hash(char *key)
{
    return KRHash(key);
}
void dict_destroy(dict_entry_s *entry)
{
    free(entry->key);
    free(entry);
}
int dict_cmp(dict_entry_s *entry1, char *key)
{
    return strcmp(entry1->key, key);
}
dict_entry_s *dict_copy(dict_entry_s *entry)
{
    dict_entry_s *copy = create_entry(entry->key);
    return copy;
}

int find_dict(TablaHash table, char *key)
{
    return tablahash_buscar(table, key)) ? 1 : 0 ;
}
void add_dict();
void destroy_dict();
TablaHash new_dict()
{
    return tablahash_crear(HASHSIZE, (FuncionCopiadora)dict_copy, (FuncionComparadora)dict_cmp, (FuncionDestructora)dict_destroy, (FuncionHash)dict_hash);
}