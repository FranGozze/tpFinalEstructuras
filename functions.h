#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "tablahash.h"

typedef void (*func)(SList, char *[], int *, char *[], TablaHash table);

void freeArray(char *array[], int amount);
void change_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResults, TablaHash table);
void swap_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResults, TablaHash table);
void delete_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResults, TablaHash table);
void insert_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResults, TablaHash table);
void separate_letter(char *word, int wordLength, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResults, TablaHash table);
void corrections(char *word, TablaHash table, dict_entry_s *results[]);

// from  https://stackoverflow.com/questions/69874895/inserting-a-character-into-a-char-array
// modifico la funcion para que haga lo que necesito
char *addInPosition(char *str, int strSize, char c, unsigned num);

#endif /* __FUNCTIONS_H__ */