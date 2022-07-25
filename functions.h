#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
// creo que no hace falta este
#include "slist.h"

#include "dictionary.h"
#include "tablahash.h"

typedef void (*func)(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount,
                     TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *contador);

void freeArray(dict_entry_s *array[], int amount);
void change_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *contador);
void swap_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *contador);
void delete_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *contador);
void insert_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *contador);
void separate_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *contador);
void corrections(char *word, int wordLength, TablaHash table, dict_entry_s *results[]);

// from  https://stackoverflow.com/questions/69874895/inserting-a-character-into-a-char-array
// modifico la funcion para que haga lo que necesito
char *addInPosition(char *str, int strSize, char c, unsigned num);

#endif /* __FUNCTIONS_H__ */