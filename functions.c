#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slist.h"
#include "dictionary.h"
#define MAX_WORDS 5
#define MAX_STEPS 3
#define ASCCI_a 97
#define ASCCI_z 122

typedef void (*func)(SList, func, func, char *[], int *, char *[]);

void change_letter(SList word, func firstFunction, func secondFunction, char *results[], int *correctWordsAmount, char *partialResults[])
{
    char *l = malloc(sizeof(char));
    char *originalLetter = malloc(sizeof(char));
    for (SList i = word; i && (*correctWordsAmount) < MAX_WORDS; i = i->sig)
    {
        (*originalLetter) = word->*data;
        for (int letter = ASCCI_a; letter <= ASCCI_z && (*correctWordsAmount) < MAX_WORDS; letter++)
        {
            (*l) = letter;
            word->*data = (*l);
            if (firstFunction)
                firstFunction(word, secondFunction, NULL, results, correctWordsAmount, partialResults);
            else if (find_dict(word))
            {
                results[(*correctWordsAmount)] = string_to_char(word);
                (*correctWordsAmount)++
            }
        }
        word->*data = (*originalLetter);
    }
}

void swap_letter()
{
}

void delete_letter() {}

void insert_letter(char *word, func firstFunction, func secondFunction) {}

void separate_letter() {}

void corrections(char *word, char *results[])
{

    void (*proccess[5])() = {change_letter,
                             swap_letter,
                             delete_letter,
                             insert_letter,
                             separate_letter};
    int *correctWordsAmount = malloc(sizeof(int));
    *correctWordsAmount = 0;
    for (int step = 1; step <= MAX_STEPS && (*correctWordsAmount) < MAX_WORDS; step++)
    {
        for (int firstFunction = 0; firstFunction < 5 && (*correctWordsAmount) < MAX_WORDS; firstFunction++)
        {
            if (step == 2)
                for (int k = 0; k < 5 && (*correctWordsAmount) < MAX_WORDS; k++)
                    if (step == 3)
                        for (int l = 0; l < 5 && (*correctWordsAmount) < MAX_WORDS; l++)
                            (*proccess[firstFunction])(word, (*proccess[k]), (*proccess[l]));

                    else
                        (*proccess[firstFunction])(word, (*proccess[k]), NULL);
            else
                (*proccess[firstFunction])(word, NULL, NULL);
        }
    }
}