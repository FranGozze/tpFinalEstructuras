#ifndef __DICTIONARY_H_
#define __DICTIONARY_H_
#include "tablahash.h"

typedef struct dict_entry_s
{
    const char *key;
    int hash;
} dict_entry_s;

dict_entry_s *create_entry(const char *key);

unsigned dict_hash(dict_entry_s *entry);
void dict_free(dict_entry_s *entry);
int dict_cmp(dict_entry_s *entry1, dict_entry_s *entry2);
dict_entry_s *dict_copy(dict_entry_s *entry);

int dict_find(TablaHash table, dict_entry_s *entry);
void dict_add(TablaHash table, dict_entry_s *entry);
void dict_destroy(TablaHash table);
TablaHash new_dict();
#endif /* __DICTIONARY_H_ */