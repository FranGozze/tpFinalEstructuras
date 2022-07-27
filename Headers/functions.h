#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
// creo que no hace falta este
#include "slist.h"

#include "dictionary.h"
#include "tablahash.h"
#include "correctWord.h"

typedef void (*func)(dict_entry_s *word, dict_entry_s *results[], int *correctWordsAmount,
                     TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *contador, int step);

void freeArray(dict_entry_s *array[], int amount);
void change_letter(dict_entry_s *word, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *contador, int step);
void swap_letter(dict_entry_s *word, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *contador, int step);
void delete_letter(dict_entry_s *word, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *contador, int step);
void insert_letter(dict_entry_s *word, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *contador, int step);
void separate_letter(dict_entry_s *word, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *contador, int step);
void corrections(correctWord *word, TablaHash table);

// from  https://stackoverflow.com/questions/69874895/inserting-a-character-into-a-char-array
// modifico la funcion para que haga lo que necesito
char *addInPosition(char *str, int strSize, char c, unsigned num);

#endif /* __FUNCTIONS_H__ */