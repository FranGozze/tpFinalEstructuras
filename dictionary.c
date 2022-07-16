#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablahash.h"
#include "dictionary.h"
#define HASHSIZE 620909
dict_entry_s *create_entry(const char *key)
{
    dict_entry_s *entry = malloc(sizeof(dict_entry_s));
    entry->key = malloc(sizeof(char) * strlen(key) + 1);
    strcpy(entry->key, key);
    entry->hash = dict_hash(entry);
    return entry;
}
unsigned dict_hash(dict_entry_s *entry)
{
    return KRHash(entry->key);
}
void dict_free(dict_entry_s *entry)
{
    free(entry->key);
    free(entry);
}
int dict_cmp(dict_entry_s *entry1, dict_entry_s *entry2)
{
    return entry1->hash == entry2->hash && strcmp(entry1->key, entry2->key) == 0;
}
dict_entry_s *dict_copy(dict_entry_s *entry)
{
    dict_entry_s *copy = create_entry(entry->key);
    return copy;
}

int dict_find(TablaHash table, dict_entry_s *entry)
{
    return tablahash_buscar(table, entry) ? 1 : 0;
}
void dict_add(TablaHash table, dict_entry_s *entry)
{
    tablahash_insertar(table, entry);
}
void dict_destroy(TablaHash table)
{
    tablahash_destruir(table);
}

TablaHash new_dict()
{
    return tablahash_crear(HASHSIZE, (FuncionCopiadora)dict_copy, (FuncionComparadora)dict_cmp, (FuncionDestructora)dict_free, (FuncionHash)dict_hash);
}