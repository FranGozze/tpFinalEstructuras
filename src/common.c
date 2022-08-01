#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../Headers/tablahash.h"
#include "../Headers/dictionary.h"
#include "../Headers/common.h"
#include "../Headers/correctWord.h"
#include "../Headers/functions.h"

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

void text(char *texPath, TablaHash dict, char *outputPath)
{
    FILE *input = fopen(texPath, "rb");

    if (input)
    {
        FILE *output = fopen(outputPath, "wb");
        char buff[255];
        int line = 1, position = 0, flag = 1;
        TablaHash table = new_correct_dict(WORDS_SIZE);
        while (flag)
        {
            buff[position] = fgetc(input);
            if (isalpha(buff[position]))
                buff[position++] = tolower(buff[position]);
            else if (buff[position] == ' ' || buff[position] == '\n' || buff[position] == EOF)
            {
                if (buff[position] == EOF)
                    flag = 0;
                if (buff[position] == '\n')
                    line++;
                buff[position] = '\0';
                position = 0;
                dict_entry_s *entry = create_entry_with_copy(buff, strlen(buff));
                if (!dict_find(dict, entry))
                {
                    correctWord *word = create_correction(entry);
                    if (!find_tablahash(table, word))
                    {
                        suggestions(word, dict);
                        insert_tablehash(table, word);
                        if (word->suggestions[0])
                        {
                            fprintf(output, "Line %d, '%s' no esta en el diccionario.\nQuizas quiso decir: ", line, word->entry->key);
                            for (int i = 0; i < 5; i++)
                            {
                                if (word->suggestions[i])
                                    fprintf(output, "%s", word->suggestions[i]->key);
                                if (word->suggestions[i + 1])
                                    fprintf(output, ", ");
                            }
                            fprintf(output, "\n");
                        }
                        else
                            fprintf(output, "\nNo se encontraron correciones para la palabra: %s  \n", word->entry->key);
                    }
                    else
                        corrections_free(word);
                }
                else
                    dict_free(entry);
            }
        }
        destroy_tablehash(table);
        fclose(input);
        fclose(output);
    }
    else
        printf("El archivo de entrada esta vacio \n");
}