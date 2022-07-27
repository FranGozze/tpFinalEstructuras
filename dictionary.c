#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Headers/dictionary.h"
#include "Headers/dictionary.h"
dict_entry_s *create_entry_with_copy(char *key, int keyLength)
{
    dict_entry_s *entry = malloc(sizeof(dict_entry_s));
    entry->key = malloc(sizeof(char) * keyLength + 1);
    for (int i = 0; i < keyLength; i++)
        entry->key[i] = tolower(key[i]);
    entry->key[keyLength] = '\0';
    entry->keyLength = keyLength;
    entry->hash = dict_hash(entry);
    return entry;
}
dict_entry_s *create_entry_with_reference(char *key, int keyLength)
{
    dict_entry_s *entry = malloc(sizeof(dict_entry_s));
    entry->key = key;
    entry->keyLength = keyLength;
    entry->hash = dict_hash(entry);
    return entry;
}
unsigned dict_hash(dict_entry_s *entry)
{
    return KRHash(entry->key);
}
unsigned hash(dict_entry_s *entry) { return entry->hash; }
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
    dict_entry_s *copy = create_entry_with_copy(entry->key, entry->keyLength);
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

TablaHash new_dict(int size)
{
    return tablahash_crear(size, (FuncionCopiadora)dict_copy, (FuncionComparadora)dict_cmp, (FuncionDestructora)dict_free, (FuncionHash)hash);
}