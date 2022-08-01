#ifndef __DICTIONARY_H_
#define __DICTIONARY_H_
#include "tablahash.h"

typedef struct dict_entry_s
{
    char *key;
    int keyLength;
    int hash;
} dict_entry_s;

/*
    Esta funcion crea un dict_entry_s copiando el contenido del string que se le pasa
*/
dict_entry_s *create_entry_with_copy(char *key, int keyLength);

/*
    Esta funcion crea un dict_entry_s usando el mismo puntero que se le pasa
*/
dict_entry_s *create_entry_with_reference(char *key, int keyLength);

/*
    Esta funcion devuelve el hash de un dict_entry_s
*/
unsigned dict_hash(dict_entry_s *entry);

/*
    Esta funcion libera la memoria de un dict_entry_s
*/
void dict_free(dict_entry_s *entry);

/*
    Esta funcion compara dos dict_entry_s, devuelve 1 si son iguales, 0 si son diferentes
*/
int dict_cmp(dict_entry_s *entry1, dict_entry_s *entry2);

/*
    Esta funcion copia un dict_entry_s
*/
dict_entry_s *dict_copy(dict_entry_s *entry);
/*
    Esta funcion busca en la tabla un dict_entry_s, si lo encuentra devuelve 1, caso contrario devuelve 0
*/
int dict_find(TablaHash table, dict_entry_s *entry);

/*
    Esta funcion agrega una entrada a una tabla hash
*/
void dict_add(TablaHash table, dict_entry_s *entry);

/*
    Esta funcion se encarga de reccorer un tabla y liberar la memoria de todas su entradas
*/
void dict_destroy(TablaHash table);

/*
    Esta funcion crea un nuevo diccionario con el tamaño indicado,
     y con las funciones correspondientes a dict_entry_s
*/
TablaHash new_dict(unsigned int size);
#endif /* __DICTIONARY_H_ */