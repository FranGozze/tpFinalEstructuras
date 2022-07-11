#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slist.h"
#include "dictionary.h"
#define MAX_WORDS 5
#define MAX_STEPS 3
#define ASCCI_a 97
#define ASCCI_z 122

typedef void (*func)(SList, char *[], int *, char *[]);

void freeArray(char *array[], int amount)
{
    for (int i = 0; i < amount; i++)
        free(array[i]);
}

void change_letter(char *word, int wordLength, char *results[], int *correctWordsAmount, char *partialResults[], int *partialResultPos)
{
    char *l = malloc(sizeof(char));
    char *originalLetter = malloc(sizeof(char));
    for (int i = 0; i && (*correctWordsAmount) < MAX_WORDS; i = i->sig)
    {
        for (int letter = ASCCI_a; letter <= ASCCI_z && (*correctWordsAmount) < MAX_WORDS; letter++)
        {
            char *copy = malloc(sizeof(char) * wordLength + 1);
            strcpy(copy, word);
            copy[i] = letter;
            if (find_dict(copy))
                results[(*correctWordsAmount)++] = copy;

            partialResults[(*partialResultPos)++] = copy;
        }
    }
}

void swap_letter(char *word, int wordLength, char *results[], int *correctWordsAmount, char *partialResults[], int *partialResultPos)
{
    for (int i = 0; i < wordLength && (*correctWordsAmount) < MAX_WORDS; i++)
    {
        char *copy = malloc(sizeof(char) * wordLength + 1);
        strcpy(copy, word);
        char aux = copy[i];
        copy[i] = copy[i + 1];
        copy[i + 1] = aux;

        if (find_dict(copy))
            results[(*correctWordsAmount)++] = copy;
        partialResults[(*partialResultPos)++] = copy;
    }
}

void delete_letter(char *word, int wordLength, char *results[], int *correctWordsAmount, char *partialResults[], int *partialResultPos)
{
    for (int i = 0; i < wordLength && (*correctWordsAmount) < MAX_WORDS; i++)
    {
        char *copy = malloc(sizeof(char) * wordLength);
        strcpy(copy, word);
        memmove(&copy[i], &copy[i + 1], wordLength - i);
        if (find_dict(copy))
            results[(*correctWordsAmount)++] = copy;
        partialResults[(*partialResultPos)++] = copy;
    }
}

void insert_letter(char *word, int wordLength, char *results[], int *correctWordsAmount, char *partialResults[], int *partialResultPos)
{
    for (int i = 0; i < wordLength; i++)
    {
        for (int letter = ASCCI_a; letter <= ASCCI_z && (*correctWordsAmount) < MAX_WORDS; letter++)
        {
            char *copy = malloc(sizeof(char) * wordLength + 2);
        }
    }
}

void separate_letter(char *word, int wordLength, char *results[], int *correctWordsAmount, char *partialResults[], int *partialResultPos)
{
    char *a = word;
    for (int i = 0; i < wordLength; i++)
    {
        char *copy1 = malloc(sizeof(char) * (i + 1));
        char *copy2 = malloc(sizeof(char) * (wordLength - (i + 1)));
        copy2 = a + (i + 1);
        memcpy(copy1, a, i + 1);

        if (find_dict(copy1) && find_dict(copy2))
        {
            char *copy3 = malloc(sizeof(char) * wordLength + 2);
            strcpy(copy3, copy1);
            copy3[i + 1] = ' ';
            strcpy(copy3, copy2);
            results[(*correctWordsAmount)++] = copy3;
        }
        free(copy1);
        free(copy2);
    }
}

void corrections(char *word, char *results[])
{
    int wordLength = strlen(word);
    void (*proccess[5])(char *, int, char *[], int *, char *[], int *) = {change_letter,
                                                                          swap_letter,
                                                                          delete_letter,
                                                                          insert_letter,
                                                                          separate_letter};
    int *correctWordsAmount = malloc(sizeof(int));
    *correctWordsAmount = 0;
    //                  insert_letter           change_letter       swap_letter       delete_letter
    int firstStepPartialResultsAmount = (wordLength + 1) * 26 + wordLength * 26 + (wordLength - 1) + wordLength;
    char *firstStepPartialResults[firstStepPartialResultsAmount];
    for (int firstFunction = 0; firstFunction < 5 && (*correctWordsAmount) < MAX_WORDS; firstFunction++)
        (*proccess[firstFunction])(word, results, correctWordsAmount, firstStepPartialResults);

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