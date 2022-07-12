#ifndef __DICTIONARY_H_
#define __DICTIONARY_H_

typedef struct dict_entry_s
{
    const char *key;
    int hash;
} dict_entry_s;

unsigned hash_dict(dict_entry_s *entry);
void destroy_dict(dict_entry_s *entry);
int cmp(dict_entry_s *entry1, dict_entry_s *entry2);
dict_entry_s *copy(dict_entry_s *entry);

void add_dict();
void new_dict();
void find_dict();

#endif /* __DICTIONARY_H_ */