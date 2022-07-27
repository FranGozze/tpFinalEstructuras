#ifndef __CORRECTWORD_H_
#define __CORRECTWORD_H_
#include "tablahash.h"
#include "dictionary.h"

typedef struct _correctWord
{
    dict_entry_s *entry;
    dict_entry_s **corrections;
} correctWord;

correctWord *create_correction(dict_entry_s *entry);
unsigned corrections_hash(correctWord *entry);
void corrections_free(correctWord *entry);
int corrections_cmp(correctWord *entry1, correctWord *entry2);
correctWord *corrections_copy(correctWord *entry);
int corrections_find(TablaHash table, correctWord *entry);
TablaHash new_correct_dict(int size);

#endif /* __CORRECTWORD_H_ */
