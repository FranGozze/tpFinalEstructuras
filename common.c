#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    if (!file)
    {
        fclose(file);
        exit(1);
    }
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
    int linea = 1, posicion = 0, ban = 1;
    TablaHash table = new_correct_dict(WORDS_SIZE);

    while (ban)
    {
        buff[posicion] = fgetc(input);
        if (isalpha(buff[posicion]))
            buff[posicion++] = tolower(buff[posicion]);

        else if (buff[posicion] == ' ' || buff[posicion] == '\n' || buff[posicion] == EOF)
        {
            if (buff[posicion] == EOF)
                ban = 0;

            if (buff[posicion] == '\n')
                linea++;
            buff[posicion] = '\0';
            posicion = 0;
            dict_entry_s *entry = create_entry_with_copy(buff, strlen(buff));
            if (!dict_find(dict, entry))
            {
                correctWord *word = create_correction(entry);
                correctWord *find = find_tablahash(table, word);
                if (!find)
                {
                    corrections(word, dict);
                    insert_tablehash(table, word);
                    if (word->corrections[0])
                    {
                        fprintf(output, "Linea %d, '%s' no esta en el diccionario.\nQuizas quiso decir: ", linea, word->entry->key);
                        for (int i = 0; i < 5; i++)
                        {
                            if (word->corrections[i])
                            {
                                fprintf(output, "%s", word->corrections[i]->key);
                            }
                            if (word->corrections[i + 1])
                                fprintf(output, ", ");
                        }
                        fprintf(output, "\n");
                    }
                    else
                        fprintf(output, "\nNo se encontraron correciones para la palabra: %s  \n", word->entry->key);
                }
                else
                {
                    corrections_free(word);
                }
            }
            else
                dict_free(entry);
        }
    }

    destroy_tablehash(table);
    fclose(output);
    fclose(input);
}