#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Headers/tablahash.h"
#include "Headers/dictionary.h"
#include "Headers/common.h"
#include "Headers/correctWord.h"
#include "Headers/functions.h"

#define HASHSIZE 1241782
#define WORDS_SIZE 4096

TablaHash readDictionary(char *dictPath)
{
    FILE *file = fopen(dictPath, "rb");
    char buff[255];
    TablaHash table = new_dict(HASHSIZE);
    while (fscanf(file, "%s", buff) != EOF)
    {
        dict_entry_s *entry = create_entry_with_copy(buff, strlen(buff));
        dict_add(table, entry);
    }
    fclose(file);
    return table;
}

void text(char *texPath, TablaHash dict)
{
    FILE *input = fopen(texPath, "rb");
    FILE *output = fopen("salida.txt", "wb");
    char buff[255];
    int linea = 1;
    TablaHash table = new_correct_dict(WORDS_SIZE);
    while (fscanf(input, "%[^,. \n] %*[,. \n]", buff) != EOF)
    {
        dict_entry_s *entry = create_entry_with_copy(buff, strlen(buff));
        if (!dict_find(dict, entry))
        {
            correctWord *word = create_correction(entry);
            correctWord *find = tablahash_buscar(table, word);
            if (!find)
            {
                corrections(word, dict);
                tablahash_insertar(table, word);
                find = word;
            }
            else
            {
                corrections_free(word);
            }
            if (find->corrections[0])
                fprintf(output, "\nPalabra: %s  \n", find->entry->key);
            for (int i = 0; i < 5; i++)
                if (find->corrections[i])
                {
                    fprintf(output, " %s\n", find->corrections[i]->key);
                }
        }
        else
            dict_free(entry);
    }
    tablahash_destruir(table);
    fclose(output);
    fclose(input);
}