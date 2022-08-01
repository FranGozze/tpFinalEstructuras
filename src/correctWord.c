#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/tablahash.h"
#include "../Headers/dictionary.h"
#include "../Headers/correctWord.h"

correctWord *create_correction(dict_entry_s *entry)
{
    correctWord *word = malloc(sizeof(correctWord));
    word->entry = entry;
    word->suggestions = malloc(sizeof(dict_entry_s *) * 6);
    for (int i = 0; i < 6; i++)
        word->suggestions[i] = NULL;

    return word;
}
unsigned corrections_hash(correctWord *word)
{
    return word->entry->hash;
}
void corrections_free(correctWord *word)
{
    dict_free(word->entry);
    for (int i = 0; i < 5; i++)
        if (word->suggestions[i])
            dict_free(word->suggestions[i]);
    free(word->suggestions);
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

TablaHash new_correct_dict(int size)
{
    return create_tablehash(size, (FuncionCopiadora)corrections_copy, (FuncionComparadora)corrections_cmp, (FuncionDestructora)corrections_free, (FuncionHash)corrections_hash);
}