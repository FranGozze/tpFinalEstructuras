#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
// creo que no hace falta este
#include "slist.h"

#include "dictionary.h"
#include "tablahash.h"
#include "correctWord.h"

typedef void (*func)(dict_entry_s *word, dict_entry_s *results[], int *correctWordsAmount,
                     TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *contador, int step);

/*
    Esta funcion intercambia cada letra de la palabra por todas las letras del abecedario y se fija
    si alguna nueva palabra esta en el diccionario. De ser asi la guarda en los resultados.
    Independientemente de si la palabra esta en el diccionario, esta funcion guardar cada resultado parcial en una tabla hash
    y en un array (que apuntaran al mismo puntero), para en los pasos siguientes probar con estas palabras
*/
void change_letter(dict_entry_s *word, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *partialResultsAmount, int step);

/*
    Esta funcion intercambia las letras adyacentes de la palabra y se fija
    si alguna nueva palabra esta en el diccionario. De ser asi la guarda en los resultados.
    Independientemente de si la palabra esta en el diccionario, esta funcion guardar cada resultado parcial en una tabla hash
    y en un array (que apuntaran al mismo puntero), para en los pasos siguientes probar con estas palabras
*/
void swap_letter(dict_entry_s *word, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *partialResultsAmount, int step);

/*
    Esta funcion elimina un caracter en todas la posibles posiciones de la palabra y se fija
    si alguna nueva palabra esta en el diccionario. De ser asi la guarda en los resultados.
    Independientemente de si la palabra esta en el diccionario, esta funcion guardar cada resultado parcial en una tabla hash
    y en un array (que apuntaran al mismo puntero), para en los pasos siguientes probar con estas palabras
*/
void delete_letter(dict_entry_s *word, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *partialResultsAmount, int step);

/*
    Esta funcion mete en todas la posibles posiciones todas las letras del abecedario y se fija
    si alguna nueva palabra esta en el diccionario. De ser asi la guarda en los resultados.
    Independientemente de si la palabra esta en el diccionario, esta funcion guardar cada resultado parcial en una tabla hash
    y en un array (que apuntaran al mismo puntero), para en los pasos siguientes probar con estas palabras
*/
void insert_letter(dict_entry_s *word, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *partialResultsAmount, int step);

/*
    Esta funcion separa cada palabra en 2, en las distintas posiciones posibles, y se fija que el nuevo par palabras
    de pertenezcan al diccionario. Si esto se cumple a la palabra original le mete un espacio donde dividio la palabra
    y guarda el resultado. Esta funcion no guarda resultados parciales
*/
void separate_words(dict_entry_s *word, dict_entry_s *results[], int *correctWordsAmount, TablaHash partialResultsTable, TablaHash table, dict_entry_s **partialResults, unsigned int *partialResultsAmount, int step);

/*
    Esta funcion busca, aplicando las 5 reglas dadas, posibles correciones para una palabra. Para encontrar posibles
    correcciones la funcion hara hasta 3 ciclos, donde en cada ciclo aplicara las reglas a las palabras obtenidas en el ciclo anterior
    (a excepcion del primer ciclo que simplemente aplicara las reglas a la palabra original)
*/
void suggestions(correctWord *word, TablaHash table);

/*
    char*, int, char, unsigned ->  char*
    Esta funcion inserta una letra a una palabra en una posicion especifica
*/
char *addInPosition(char *str, int strSize, char c, unsigned num);

#endif /* __FUNCTIONS_H__ */