#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slist.h"
#include "dictionary.h"
#include "tablahash.h"
#include "functions.h"

#define MAX_WORDS 5
#define MAX_STEPS 3

void freeArray(char *array[], int amount)
{
    for (int i = 0; i < amount; i++)
        free(array[i]);
}

void change_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResults, TablaHash table)
{
    char *l = malloc(sizeof(char));
    char *originalLetter = malloc(sizeof(char));
    for (int i = 0; i <= wordLength && (*correctWordsAmount) < MAX_WORDS; i++)
    {

        char *copy = malloc(sizeof(char) * wordLength + 1);
        strcpy(copy, word);
        for (int letter = 'a'; letter <= 'z' && (*correctWordsAmount) < MAX_WORDS; letter++)
        {
            copy[i] = letter;
            dict_entry_s *entry = create_entry(copy);
            if (dict_find(table, entry) && !dict_find(partialResults, entry))
            {
                results[(*correctWordsAmount)++] = entry;
            }
            dict_add(partialResults, entry);
        }
        free(copy);
    }
}

void swap_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResults, TablaHash table)
{
    for (int i = 0; i <= wordLength && (*correctWordsAmount) < MAX_WORDS; i++)
    {
        char *copy = malloc(sizeof(char) * wordLength + 1);
        strcpy(copy, word);
        char aux = copy[i];
        copy[i] = copy[i + 1];
        copy[i + 1] = aux;
        dict_entry_s *entry = create_entry(copy);
        if (dict_find(table, entry) && !dict_find(partialResults, entry))
            results[(*correctWordsAmount)++] = entry;
        dict_add(partialResults, entry);
    }
}

void delete_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResults, TablaHash table)
{
    for (int i = 0; i < wordLength && (*correctWordsAmount) < MAX_WORDS; i++)
    {
        char *copy = malloc(sizeof(char) * wordLength);
        strcpy(copy, word);
        memmove(&copy[i], &copy[i + 1], wordLength - i);
        dict_entry_s *entry = create_entry(copy);
        if (dict_find(table, entry) && !dict_find(partialResults, entry))
            results[(*correctWordsAmount)++] = entry;
        dict_add(partialResults, entry);
    }
}

void insert_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResults, TablaHash table)
{
    for (int i = 0; i < wordLength; i++)
    {
        for (int letter = 'a'; letter <= 'z' && (*correctWordsAmount) < MAX_WORDS; letter++)
        {
            char *copy = malloc(sizeof(char) * wordLength + 2);
        }
    }
}

void separate_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResults, TablaHash table)
{
    char *a = word;
    for (int i = 0; i < wordLength; i++)
    {
        char *copy1 = malloc(sizeof(char) * (i + 1));
        char *copy2 = malloc(sizeof(char) * (wordLength - (i + 1)));
        copy2 = a + (i + 1);
        memcpy(copy1, a, i + 1);
        dict_entry_s *entry1 = create_entry(copy1);
        dict_entry_s *entry2 = create_entry(copy2);
        if (dict_find(table, entry1) && dict_find(table, entry2))
        {
            char *copy3 = malloc(sizeof(char) * wordLength + 2);
            strcpy(copy3, copy1);
            copy3[i + 1] = ' ';
            strcpy(copy3, copy2);
            dict_entry_s *result = create_entry(copy3);
            results[(*correctWordsAmount)++] = result;
        }
        // free(copy1);
        // free(copy2);
    }
}

void corrections(char *word, TablaHash table, dict_entry_s *results[])
{
    int wordLength = strlen(word);
    void (*proccess[5])(char *, int, dict_entry_s *[], int *, TablaHash, TablaHash) = {change_letter,
                                                                                       swap_letter,
                                                                                       delete_letter,
                                                                                       separate_letter};
    // insert_letter,
    int *correctWordsAmount = malloc(sizeof(int));
    *correctWordsAmount = 0;

    //                  insert_letter           change_letter       swap_letter       delete_letter
    int firstStepPartialResultsAmount = (wordLength + 1) * 26 + wordLength * 26 + (wordLength - 1) + wordLength;
    TablaHash firstStepPartialResults = new_dict((int)(firstStepPartialResultsAmount / 0.7));
    int sizeWord = strlen(word);
    int *cont = malloc(sizeof(int));
    *cont = 0;
    // delete_letter(word, sizeWord, results, correctWordsAmount, firstStepPartialResults, table);
    for (int firstFunction = 0; firstFunction < 4 && (*correctWordsAmount) < MAX_WORDS; firstFunction++)
        (*proccess[firstFunction])(word, sizeWord, results, correctWordsAmount, firstStepPartialResults, table);

    // if (*correctWordsAmount < MAX_WORDS)
    // {
    //     int secondStepPartialResultsAmount;
    //     char *secondStepPartialResults[secondStepPartialResultsAmount];
    //     for (int i = 0; i < firstStepPartialResultsAmount; i++)
    //         (*proccess[i])(firstStepPartialResults[i], results, correctWordsAmount, secondStepPartialResults);
    //     if ((*correctWordsAmount) < MAX_WORDS)
    //     {
    //         freeArray(firstStepPartialResults, firstStepPartialResultsAmount);
    //         int thirdStepPartialResultsAmount;
    //         char *thirdStepPartialResults[thirdStepPartialResultsAmount];
    //         for (int i = 0; i < secondStepPartialResultsAmount; i++)
    //             (*proccess[i])(secondStepPartialResults[i], results, correctWordsAmount, thirdStepPartialResults);
    //         freeArray(secondStepPartialResults, secondStepPartialResultsAmount);
    //         freeArray(thirdStepPartialResults, thirdStepPartialResultsAmount);
    //     }
    //     else
    //         freeArray(secondStepPartialResults, secondStepPartialResultsAmount);
    // }
    // else
    //     freeArray(firstStepPartialResults, firstStepPartialResultsAmount);
}