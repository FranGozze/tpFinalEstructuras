#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablahash.h"
#include "dictionary.h"
#include "common.h"
#include "correctWord.h"
#include "functions.h"

#define HASHSIZE 886987
#define WORDS_SIZE 4096

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

void text(char *texPath, TablaHash dict)
{
    FILE *file = fopen(texPath, "rb");
    FILE *output = fopen("salida.txt", "wb");
    char buff[255];
    // TablaHash table = new_correct_dict(WORDS_SIZE);
    // correctWord *word = create_correction(create_entry("aaaa"));
    dict_entry_s *aa[5] = {NULL};
    corrections("aaaa", 4, dict, aa);
    // for (int i = 0; i < 5; i++)
    //     if (word->corrections[i])
    //     {
    //         // printf("%s\n", find->corrections[i]->key);
    //         fprintf(output, "%s\n", word->corrections[i]->key);
    //     }
    // while (fscanf(file, "%s", buff) != EOF)
    // {
    //     dict_entry_s *entry = create_entry(buff);
    //     correctWord *word = create_correction(entry);
    //     correctWord *find = tablahash_buscar(table, word);
    //     if (!find)
    //     {
    //         corrections(buff, strlen(buff), dict, word->corrections);
    //         // tablahash_insertar(table, word);
    //         find = word;
    //     }
    //     else
    //         corrections_free(word);

    //     for (int i = 0; i < 5; i++)
    //         if (find->corrections[i])
    //         {
    //             // printf("%s\n", find->corrections[i]->key);
    //             fprintf(output, "%s\n", find->corrections[i]->key);
    //         }
    // }
    // tablahash_destruir(table);
}