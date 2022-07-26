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

    proccess[0] = separate_letter;
    proccess[1] = swap_letter;
    proccess[2] = delete_letter;
    proccess[3] = change_letter;
    proccess[4] = insert_letter;
    return proccess;
}

void change_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount,
                   TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *contador, int step)
{
    char *copy = word;
    for (int i = 0; i < wordLength && (*correctWordsAmount) < MAX_WORDS; i++)
    {

        char originalLetter = copy[i];
        for (int letter = 'a'; letter <= 'z' && (*correctWordsAmount) < MAX_WORDS; letter++)
        {
            copy[i] = letter;
            dict_entry_s *entry = create_entry_with_copy(copy, wordLength);
            if (!dict_find(partialResultsTable, entry))
            {
                if (step < 2)
                {
                    dict_add(partialResultsTable, entry);
                    partialResults[(*contador)++] = entry;
                }
                if (dict_find(table, entry))
                {
                    if (step == 2)
                        dict_add(partialResultsTable, entry);
                    results[(*correctWordsAmount)++] = dict_copy(entry);
                }
            }
            else
                dict_free(entry);
        }
        copy[i] = originalLetter;
    }
}

void swap_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount,
                 TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *contador, int step)
{
    char *copy = word;
    char aux;
    for (int i = 0; i < wordLength - 1 && (*correctWordsAmount) < MAX_WORDS; i++)
    {
        aux = copy[i];
        copy[i] = copy[i + 1];
        copy[i + 1] = aux;
        dict_entry_s *entry = create_entry_with_copy(copy, wordLength);
        if (!dict_find(partialResultsTable, entry))
        {
            if (step < 2)
            {
                dict_add(partialResultsTable, entry);
                partialResults[(*contador)++] = entry;
            }
            if (dict_find(table, entry))
            {
                if (step == 2)
                    dict_add(partialResultsTable, entry);
                results[(*correctWordsAmount)++] = dict_copy(entry);
            }
        }
        else
            dict_free(entry);
        aux = copy[i];
        copy[i] = copy[i + 1];
        copy[i + 1] = aux;
    }
}
void delete_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount,
                   TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *contador, int step)
{
    for (int i = 0; i < wordLength && (*correctWordsAmount) < MAX_WORDS; i++)
    {
        char *copy = malloc(sizeof(char) * wordLength);
        for (int j = 0; j < wordLength; j++)
            if (j < i)
                copy[j] = word[j];
            else
                copy[j] = word[j + 1];
        copy[wordLength] = '\0';

        dict_entry_s *entry = create_entry_with_reference(copy, wordLength - 1);

        if (!dict_find(partialResultsTable, entry))
        {

            if (step < 2)
            {
                dict_add(partialResultsTable, entry);
                partialResults[(*contador)++] = entry;
            }
            if (dict_find(table, entry))
            {
                if (step == 2)
                    dict_add(partialResultsTable, entry);
                results[(*correctWordsAmount)++] = dict_copy(entry);
            }
        }
        else
            dict_free(entry);
    }
}

// from  https://stackoverflow.com/questions/69874895/inserting-a-character-into-a-char-array
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

void insert_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount,
                   TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *contador, int step)
{
    for (int i = 0; i < wordLength + 1; i++)
    {
        for (int letter = 'a'; letter <= 'z' && (*correctWordsAmount) < MAX_WORDS; letter++)
        {
            char *copy = addInPosition(word, wordLength, letter, i);
            dict_entry_s *entry = create_entry_with_reference(copy, wordLength + 1);
            if (!dict_find(partialResultsTable, entry))
            {
                if (step < 2)
                {
                    dict_add(partialResultsTable, entry);
                    partialResults[(*contador)++] = entry;
                }
                if (dict_find(table, entry))
                {
                    if (step == 2)
                        dict_add(partialResultsTable, entry);
                    results[(*correctWordsAmount)++] = dict_copy(entry);
                }
            }
            else
                dict_free(entry);
        }
    }
}

void separate_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount,
                     TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *contador, int step)
{
    char *aux = word;
    for (int i = 0; i + 1 < wordLength; i++)
    {
        char *copy1 = malloc(sizeof(char) * wordLength + 1);
        char *copy2;
        copy2 = aux + (i + 1);
        strncpy(copy1, aux, i + 1);
        copy1[i + 1] = '\0';

        dict_entry_s *entry1 = create_entry_with_copy(copy1, i + 1);
        dict_entry_s *entry2 = create_entry_with_copy(copy2, wordLength - (i + 1));
        if (dict_find(table, entry1) && dict_find(table, entry2))
        {
            copy1[i + 1] = ' ';
            strncpy(copy1 + i + 2, word + i + 1, wordLength - (i + 1));
            copy1[wordLength + 1] = '\0';
            dict_entry_s *result = create_entry_with_reference(copy1, wordLength + 1);
            results[(*correctWordsAmount)++] = result;
        }
        dict_free(entry1);
        dict_free(entry2);
    }
}

void corrections(char *word, int wordLength, TablaHash table, dict_entry_s *results[])
{
    int *correctWordsAmount = malloc(sizeof(int));
    *correctWordsAmount = 0;
    func proccess[5] = {separate_letter,
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

    int ResultsAmount = FirstResultsAmount + SecondResultsAmount;

    TablaHash PartialResultsTable = new_dict((int)(ResultsAmount / 0.5));
    dict_entry_s **partialResults = malloc(sizeof(dict_entry_s *) * ResultsAmount);
    for (int i = 0; i < ResultsAmount; i++)
        partialResults[i] = NULL;

    unsigned int *contador = malloc(sizeof(int));
    (*contador) = 0;
    // delete_letter("Phasellus", 9, results, correctWordsAmount, PartialResultsTable, table, partialResults, contador, 0);

    // printf("%d %d\n", PartialResultsTable->numElems, (9 - 1) * 26 * 9);
    // for (int i = 0; i < 9; i++)
    // {
    //     change_letter(partialResults[i]->key, partialResults[i]->keyLength, results, correctWordsAmount, PartialResultsTable, table, partialResults, contador, 0);
    // }
    // printf("%d %d\n", PartialResultsTable->numElems, (9 - 1) * 26 * 9);
    // for (unsigned int i = 0; i < (9 - 1 * 26) * 9 && partialResults[i]; i++)
    // {
    //     if (!(strcmp(partialResults[i]->key, "hasellas")))
    //         separate_letter(partialResults[i]->key, partialResults[i]->keyLength, results, correctWordsAmount, PartialResultsTable, table, partialResults, contador, 0);
    // }

    // Ver porque no funciona si hago contador = 0 al principio del for
    for (int step = 0; step < MAX_STEPS && (*correctWordsAmount) < MAX_WORDS; step++)
    {
        switch (step)
        {
        case 0:
            for (int firstFunction = 0; firstFunction < 5 && (*correctWordsAmount) < MAX_WORDS; firstFunction++)
            {
                (*proccess[firstFunction])(word, wordLength, results, correctWordsAmount, PartialResultsTable, table, partialResults, contador, step);
            }
            break;
        case 1:

            for (unsigned int i = 0; i < FirstResultsAmount && (*correctWordsAmount) < MAX_WORDS; i++)
            {
                int partialLength = partialResults[i]->keyLength;

                for (int firstFunction = 0; firstFunction < 5 && (*correctWordsAmount) < MAX_WORDS; firstFunction++)
                {
                    (*proccess[firstFunction])(partialResults[i]->key, partialLength, results, correctWordsAmount, PartialResultsTable, table, partialResults, contador, step);
                }
            }
            break;
        case 2:
            for (unsigned int i = FirstResultsAmount; i < (SecondResultsAmount + FirstResultsAmount) && (*correctWordsAmount) < MAX_WORDS; i++)
            {

                int partialLength = partialResults[i]->keyLength;
                for (int firstFunction = 0; firstFunction < 5 && (*correctWordsAmount) < MAX_WORDS; firstFunction++)
                {
                    (*proccess[firstFunction])(partialResults[i]->key, partialLength, results, correctWordsAmount, PartialResultsTable, table, partialResults, contador, step);
                }
            }
            break;

        default:
            break;
        }
    }
    dict_destroy(PartialResultsTable);
    free(partialResults);
    free(contador);
    free(correctWordsAmount);
}