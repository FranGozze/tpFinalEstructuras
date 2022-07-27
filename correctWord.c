#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Headers/tablahash.h"
#include "Headers/dictionary.h"
#include "Headers/correctWord.h"

correctWord *create_correction(dict_entry_s *entry)
{
    correctWord *word = malloc(sizeof(correctWord));
    word->entry = entry;
    word->corrections = malloc(sizeof(dict_entry_s *) * 5);
    for (int i = 0; i < 5; i++)
        word->corrections[i] = NULL;

    return word;
}
unsigned corrections_hash(correctWord *word)
{
    return KRHash(word->entry->key);
}
void corrections_free(correctWord *word)
{
    dict_free(word->entry);
    for (int i = 0; i < 5; i++)
        if (word->corrections[i])
            dict_free(word->corrections[i]);
    free(word->corrections);
    free(word);
}
int corrections_cmp(correctWord *word, correctWord *word2)
{
    return word->entry->hash == word2->entry->hash && strcmp(word->entry->key, word2->entry->key) == 0;
}
correctWord *corrections_copy(correctWord *word)
{
    correctWord *copy = create_correction(word->entry);
    return copy;
}

int corrections_find(TablaHash table, correctWord *entry)
{
    return tablahash_buscar(table, entry) ? 1 : 0;
}

TablaHash new_correct_dict(int size)
{
    return tablahash_crear(size, (FuncionCopiadora)corrections_copy, (FuncionComparadora)corrections_cmp, (FuncionDestructora)corrections_free, (FuncionHash)corrections_hash);
}