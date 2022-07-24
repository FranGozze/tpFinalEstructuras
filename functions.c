#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slist.h"
#include "dictionary.h"
#include "tablahash.h"
#include "functions.h"

#define MAX_WORDS 5
#define MAX_STEPS 3

void freeArray(dict_entry_s *array[], int amount)
{
    for (int i = 0; i < amount; i++)
    {
        free(array[i]->key);
        free(array[i]);
    }
}

func *arrayOfFunctions()
{
    func *proccess = malloc(sizeof(func) * 5);

    proccess[0] = swap_letter;
    proccess[1] = delete_letter;
    proccess[2] = separate_letter;
    proccess[3] = change_letter;
    proccess[4] = insert_letter;
    return proccess;
}

void change_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount,
                   TablaHash partialResultsTable, TablaHash table,
                   int step)
{
    for (int i = 0; i < wordLength && (*correctWordsAmount) < MAX_WORDS; i++)
    {

        char *copy = malloc(sizeof(char) * wordLength + 1);
        strcpy(copy, word);
        for (int letter = 'a'; letter <= 'z' && (*correctWordsAmount) < MAX_WORDS; letter++)
        {
            copy[i] = letter;
            if (step != 0)
            {
                func *proccess = arrayOfFunctions();
                for (int function = 0; function < 5 && (*correctWordsAmount) < MAX_WORDS; function++)
                    (*proccess[function])(copy, wordLength, results, correctWordsAmount, partialResultsTable, table, step - 1);
                free(proccess);
            }
            else
            {

                dict_entry_s *entry = create_entry(copy);
                if (!dict_find(partialResultsTable, entry))
                {
                    dict_add(partialResultsTable, entry);
                    if (dict_find(table, entry))
                        results[(*correctWordsAmount)++] = dict_copy(entry);
                }
                else
                    dict_free(entry);
            }
        }
        free(copy);
    }
}

void swap_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount,
                 TablaHash partialResultsTable, TablaHash table,
                 int step)
{
    for (int i = 0; i < wordLength - 1 && (*correctWordsAmount) < MAX_WORDS; i++)
    {
        char *copy = malloc(sizeof(char) * wordLength + 1);
        strcpy(copy, word);
        char aux = copy[i];
        copy[i] = copy[i + 1];
        copy[i + 1] = aux;
        if (step != 0)
        {
            func *proccess = arrayOfFunctions();
            for (int function = 0; function < 5 && (*correctWordsAmount) < MAX_WORDS; function++)
                (*proccess[function])(copy, wordLength, results, correctWordsAmount, partialResultsTable, table, step - 1);
            free(proccess);
        }
        else
        {
            dict_entry_s *entry = create_entry(copy);
            if (!dict_find(partialResultsTable, entry))
            {
                dict_add(partialResultsTable, entry);
                if (dict_find(table, entry))
                    results[(*correctWordsAmount)++] = dict_copy(entry);
            }
            else
                dict_free(entry);
        }
        free(copy);
    }
}

void delete_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount,
                   TablaHash partialResultsTable, TablaHash table, int step)
{
    for (int i = 0; i < wordLength && (*correctWordsAmount) < MAX_WORDS; i++)
    {
        char *copy = malloc(sizeof(char) * wordLength);
        strcpy(copy, word);
        memmove(&copy[i], &copy[i + 1], wordLength - i);
        if (step != 0)
        {
            func *proccess = arrayOfFunctions();
            for (int function = 0; function < 5 && (*correctWordsAmount) < MAX_WORDS; function++)
                (*proccess[function])(copy, wordLength - 1, results, correctWordsAmount, partialResultsTable, table, step - 1);
            free(proccess);
        }
        else
        {

            dict_entry_s *entry = create_entry(copy);
            if (!dict_find(partialResultsTable, entry))
            {
                dict_add(partialResultsTable, entry);
                if (dict_find(table, entry))
                    results[(*correctWordsAmount)++] = dict_copy(entry);
            }
            else
                dict_free(entry);
        }
        free(copy);
    }
}

// from  https://stackoverflow.com/questions/69874895/inserting-a-character-into-a-char-array
char *addInPosition(char *str, int strSize, char c, unsigned num)
{
    char *copy = malloc(sizeof(char) * strSize + 2);
    strcpy(copy, str);
    char *aux = copy;
    for (int i = 0; i != num; i++)
    {
        aux++;
        strSize--;
    }
    memmove(aux + 1, aux, strSize);
    *aux = c;
    return copy;
}

void insert_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount,
                   TablaHash partialResultsTable, TablaHash table,
                   int step)
{
    for (int i = 0; i < wordLength + 1; i++)
    {
        for (int letter = 'a'; letter <= 'z' && (*correctWordsAmount) < MAX_WORDS; letter++)
        {
            char *copy = addInPosition(word, wordLength, letter, i);
            if (step != 0)
            {
                func *proccess = arrayOfFunctions();
                for (int function = 0; function < 5 && (*correctWordsAmount) < MAX_WORDS; function++)
                    (*proccess[function])(copy, wordLength + 1, results, correctWordsAmount, partialResultsTable, table, step - 1);
                free(proccess);
            }
            else
            {
                dict_entry_s *entry = create_entry(copy);
                if (!dict_find(partialResultsTable, entry))
                {
                    dict_add(partialResultsTable, entry);
                    if (dict_find(table, entry))
                        results[(*correctWordsAmount)++] = dict_copy(entry);
                }
                else
                    dict_free(entry);
            }
            free(copy);
        }
    }
}

void separate_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount,
                     TablaHash partialResultsTable, TablaHash table, int step)
{
    char *aux = word;
    for (int i = 0; i + 1 < wordLength; i++)
    {
        char *copy1 = malloc(sizeof(char) * (i + 1));
        char *copy2;
        copy2 = aux + (i + 1);
        memcpy(copy1, aux, i + 1);

        dict_entry_s *entry1 = create_entry(copy1);
        dict_entry_s *entry2 = create_entry(copy2);

        if (dict_find(table, entry1) && dict_find(table, entry2))
        {
            char *copy3 = addInPosition(aux, wordLength, ' ', i + 1);
            dict_entry_s *result = create_entry(copy3);
            results[(*correctWordsAmount)++] = result;
            free(copy3);
        }
        dict_free(entry1);
        dict_free(entry2);
        free(copy1);
        // free(copy2);
    }
}

void corrections(char *word, int wordLength, TablaHash table, dict_entry_s *results[])
{
    int *correctWordsAmount = malloc(sizeof(int));
    *correctWordsAmount = 0;

    func *proccess = arrayOfFunctions();
    unsigned FirstResultsAmount = (wordLength + 1) * 26 + wordLength * 26 + (wordLength - 1) + wordLength;
    // en segundo paso change_letter y swap_letter
    unsigned SecondResultsAmount = FirstResultsAmount * 2;
    // caso insert en segundo paso
    SecondResultsAmount += (wordLength + 2) * 26 + (wordLength + 1) * 26 + (wordLength) + wordLength + 1;
    // caso delete
    SecondResultsAmount += (wordLength)*26 + (wordLength - 1) * 26 + (wordLength - 2) + (wordLength - 1);

    int thirdResultAmount = FirstResultsAmount;

    int ResultsAmount = FirstResultsAmount + SecondResultsAmount;

    TablaHash PartialResultsTable = new_dict((int)(ResultsAmount / 0.7));

    for (int step = 0; step < MAX_STEPS && (*correctWordsAmount) < MAX_WORDS; step++)
        for (int firstFunction = 0; firstFunction < 5 && (*correctWordsAmount) < MAX_WORDS; firstFunction++)
        {
            (*proccess[firstFunction])(word, wordLength, results, correctWordsAmount, PartialResultsTable, table, step);
        }

    dict_destroy(PartialResultsTable);
    free(proccess);
    free(correctWordsAmount);
}