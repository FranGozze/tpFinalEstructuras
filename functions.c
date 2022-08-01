#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Headers/slist.h"
#include "Headers/dictionary.h"
#include "Headers/tablahash.h"
#include "Headers/functions.h"
#include "Headers/correctWord.h"

#define MAX_WORDS 5
#define MAX_STEPS 3

void change_letter(dict_entry_s *word, dict_entry_s *results[], int *correctWordsAmount,
                   TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *partialResultsAmount, int step)
{
    char *copy = word->key;
    for (int i = 0; i < word->keyLength && (*correctWordsAmount) < MAX_WORDS; i++)
    {

        char originalLetter = copy[i];
        for (int letter = 'a'; letter <= 'z' && (*correctWordsAmount) < MAX_WORDS; letter++)
        {
            copy[i] = letter;
            dict_entry_s *entry = create_entry_with_copy(copy, word->keyLength);
            if (!dict_find(partialResultsTable, entry))
            {

                if (dict_find(table, entry))
                {
                    dict_add(partialResultsTable, entry);
                    partialResults[(*partialResultsAmount)++] = entry;
                    results[(*correctWordsAmount)++] = dict_copy(entry);
                }
                else if (step < 2)
                {
                    dict_add(partialResultsTable, entry);
                    partialResults[(*partialResultsAmount)++] = entry;
                }
                else
                    dict_free(entry);
            }
            else
                dict_free(entry);
        }
        copy[i] = originalLetter;
    }
}

void swap_letter(dict_entry_s *word, dict_entry_s *results[], int *correctWordsAmount,
                 TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *partialResultsAmount, int step)
{
    char *copy = word->key;
    char aux;
    for (int i = 0; i < word->keyLength - 1 && (*correctWordsAmount) < MAX_WORDS; i++)
    {
        aux = copy[i];
        copy[i] = copy[i + 1];
        copy[i + 1] = aux;
        dict_entry_s *entry = create_entry_with_copy(copy, word->keyLength);
        if (!dict_find(partialResultsTable, entry))
        {
            if (dict_find(table, entry))
            {
                dict_add(partialResultsTable, entry);
                partialResults[(*partialResultsAmount)++] = entry;
                results[(*correctWordsAmount)++] = dict_copy(entry);
            }
            else if (step < 2)
            {
                dict_add(partialResultsTable, entry);
                partialResults[(*partialResultsAmount)++] = entry;
            }
            else
                dict_free(entry);
        }
        else
            dict_free(entry);
        aux = copy[i];
        copy[i] = copy[i + 1];
        copy[i + 1] = aux;
    }
}
void delete_letter(dict_entry_s *word, dict_entry_s *results[], int *correctWordsAmount,
                   TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *partialResultsAmount, int step)
{
    for (int i = 0; i < word->keyLength && (*correctWordsAmount) < MAX_WORDS; i++)
    {
        char *copy = malloc(sizeof(char) * word->keyLength + 1);
        for (int j = 0; j < word->keyLength; j++)
            if (j < i)
                copy[j] = word->key[j];
            else
                copy[j] = word->key[j + 1];
        copy[word->keyLength] = '\0';

        dict_entry_s *entry = create_entry_with_reference(copy, word->keyLength - 1);

        if (!dict_find(partialResultsTable, entry))
        {

            if (dict_find(table, entry))
            {
                dict_add(partialResultsTable, entry);
                partialResults[(*partialResultsAmount)++] = entry;
                results[(*correctWordsAmount)++] = dict_copy(entry);
            }
            else if (step < 2)
            {
                dict_add(partialResultsTable, entry);
                partialResults[(*partialResultsAmount)++] = entry;
            }
            else
                dict_free(entry);
        }
        else
            dict_free(entry);
    }
}

char *addInPosition(char *str, int strSize, char c, unsigned num)
{
    char *copy = malloc(sizeof(char) * strSize + 2);
    strncpy(copy, str, num);
    char *aux = copy + num;
    *aux = c;
    strncpy(aux + 1, str + num, strSize - num);
    copy[strSize + 1] = '\0';
    return copy;
}

void insert_letter(dict_entry_s *word, dict_entry_s *results[], int *correctWordsAmount,
                   TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *partialResultsAmount, int step)
{
    for (int i = 0; i < word->keyLength + 1; i++)
    {
        for (int letter = 'a'; letter <= 'z' && (*correctWordsAmount) < MAX_WORDS; letter++)
        {
            char *copy = addInPosition(word->key, word->keyLength, letter, i);

            dict_entry_s *entry = create_entry_with_reference(copy, word->keyLength + 1);
            if (!dict_find(partialResultsTable, entry))
            {
                if (dict_find(table, entry))
                {
                    dict_add(partialResultsTable, entry);
                    partialResults[(*partialResultsAmount)++] = entry;
                    results[(*correctWordsAmount)++] = dict_copy(entry);
                }
                else if (step < 2)
                {
                    dict_add(partialResultsTable, entry);
                    partialResults[(*partialResultsAmount)++] = entry;
                }
                else
                    dict_free(entry);
            }
            else
                dict_free(entry);
        }
    }
}

void separate_words(dict_entry_s *word, dict_entry_s *results[], int *correctWordsAmount,
                    TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *partialResultsAmount, int step)
{
    char *aux = word->key;
    for (int i = 0; i + 1 < word->keyLength && (*correctWordsAmount) < MAX_WORDS; i++)
    {
        char *copy1 = malloc(sizeof(char) * word->keyLength + 2);
        char *copy2;
        copy2 = aux + (i + 1);
        strncpy(copy1, aux, i + 1);
        copy1[i + 1] = '\0';

        dict_entry_s *entry1 = create_entry_with_copy(copy1, i + 1);
        dict_entry_s *entry2 = create_entry_with_copy(copy2, word->keyLength - (i + 1));
        if (dict_find(table, entry1) && dict_find(table, entry2))
        {
            copy1[i + 1] = ' ';
            strncpy(copy1 + i + 2, word->key + i + 1, word->keyLength - (i + 1));
            copy1[word->keyLength + 1] = '\0';
            dict_entry_s *result = create_entry_with_reference(copy1, word->keyLength + 1);
            results[(*correctWordsAmount)++] = result;
        }
        else
            free(copy1);
        dict_free(entry1);
        dict_free(entry2);
    }
}

void corrections(correctWord *word, TablaHash table)
{
    int wordLength = word->entry->keyLength;
    int *correctWordsAmount = malloc(sizeof(int));
    *correctWordsAmount = 0;
    func proccess[5] = {separate_words,
                        delete_letter,
                        swap_letter,
                        change_letter,
                        insert_letter};
    // insert_letter change_letter swap_letter delete_letter unsigned
    unsigned int FirstResultsAmount = (wordLength + 1) * 26 + wordLength * 26 + (wordLength - 1) + wordLength;

    // en segundo paso  swap_letter
    unsigned int SecondResultsAmount = (FirstResultsAmount - ((wordLength + 1) * 26) - wordLength) * (wordLength - 1) + (wordLength + 1) * 26 * wordLength + wordLength * (wordLength - 2);
    // caso insert en segundo paso          Resto las palabras que tiene 1 letra mas y 1 menos                  Palabras con 1 letra mas                        palabras con 1 letra menos
    SecondResultsAmount += (FirstResultsAmount - ((wordLength + 1) * 26) - wordLength) * (wordLength + 1) * 26 + (wordLength + 1) * 26 * (wordLength + 2) * 26 + (wordLength) * (wordLength)*26;
    // caso delete
    SecondResultsAmount += (FirstResultsAmount - ((wordLength + 1) * 26) - wordLength) * wordLength + (wordLength + 1) * 26 * (wordLength + 1) + wordLength * (wordLength - 1);
    // caso change
    SecondResultsAmount += (FirstResultsAmount - ((wordLength + 1) * 26) - wordLength) * (wordLength)*26 + (wordLength + 1) * 26 * (wordLength + 1) * 26 + (wordLength) * (wordLength - 1) * 26;

    unsigned int ResultsAmount = FirstResultsAmount + SecondResultsAmount;

    TablaHash PartialResultsTable = new_dict((unsigned int)(ResultsAmount / 0.5));
    dict_entry_s **partialResults = malloc(sizeof(dict_entry_s *) * ResultsAmount);
    for (unsigned int i = 0; i < ResultsAmount; i++)
        partialResults[i] = NULL;

    unsigned int *partialResultsAmount = malloc(sizeof(int));
    (*partialResultsAmount) = 0;

    for (int step = 0; step < MAX_STEPS && (*correctWordsAmount) < MAX_WORDS; step++)
    {
        switch (step)
        {
        case 0:
            for (int firstFunction = 0; firstFunction < 5 && (*correctWordsAmount) < MAX_WORDS; firstFunction++)
            {
                (*proccess[firstFunction])(word->entry, word->corrections, correctWordsAmount, PartialResultsTable, table, partialResults, partialResultsAmount, step);
            }
            break;
        case 1:

            for (unsigned int i = 0; i < FirstResultsAmount && (*correctWordsAmount) < MAX_WORDS; i++)
            {

                for (int firstFunction = 0; firstFunction < 5 && (*correctWordsAmount) < MAX_WORDS; firstFunction++)
                {
                    (*proccess[firstFunction])(partialResults[i], word->corrections, correctWordsAmount, PartialResultsTable, table, partialResults, partialResultsAmount, step);
                }
            }
            break;
        case 2:
            for (unsigned int i = FirstResultsAmount; partialResults[i] && i < ResultsAmount && (*correctWordsAmount) < MAX_WORDS; i++)
            {

                for (int firstFunction = 0; firstFunction < 5 && (*correctWordsAmount) < MAX_WORDS; firstFunction++)
                {
                    (*proccess[firstFunction])(partialResults[i], word->corrections, correctWordsAmount, PartialResultsTable, table, partialResults, partialResultsAmount, step);
                }
            }
            break;

        default:
            break;
        }
    }

    dict_destroy(PartialResultsTable);
    free(partialResults);
    free(partialResultsAmount);
    free(correctWordsAmount);
}