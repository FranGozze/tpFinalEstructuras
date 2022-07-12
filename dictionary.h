#ifndef __DICTIONARY_H_
#define __DICTIONARY_H_

typedef struct dict_entry_s
{
    const char *key;
    int hash;
} dict_entry_s;

unsigned hash_dict();
void destroy_dict();
int cmp();
dict_entry_s *copy();

void add_dict();
void new_dict();
void find_dict();

#endif /* __DICTIONARY_H_ */