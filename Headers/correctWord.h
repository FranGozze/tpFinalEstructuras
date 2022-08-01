#ifndef __CORRECTWORD_H_
#define __CORRECTWORD_H_
#include "tablahash.h"
#include "dictionary.h"

typedef struct _correctWord
{
    dict_entry_s *entry;
    dict_entry_s **corrections;
} correctWord;

/*
    Crea una nueva en correcion a partir de un dict_entry_s
*/
correctWord *create_correction(dict_entry_s *entry);

/*
    devuelve el hash de una correcion
*/
unsigned corrections_hash(correctWord *entry);

/*
    Libera la memoria de una correcion
*/
void corrections_free(correctWord *entry);

/*
    compara dos correciones, fijandose en las entradas de la misma
*/
int corrections_cmp(correctWord *entry1, correctWord *entry2);

/*
    copia una correcion
*/
correctWord *corrections_copy(correctWord *entry);

/*
    Busca una correcion en la tabla, y si la encuentra devuelve 1, en caso contrario 0
*/
int corrections_find(TablaHash table, correctWord *entry);

/*
    Crea un tabla de correciones, con sus funciones correspondientes
*/
TablaHash new_correct_dict(int size);

#endif /* __CORRECTWORD_H_ */
