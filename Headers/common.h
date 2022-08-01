#ifndef __COMMON_H__
#define __COMMON_H__
#include "tablahash.h"
#include "dictionary.h"

/*
    Esta funcion lee un archivo donde esten guardas palabras, y devuelve un tabla hash con las mismas
*/
TablaHash readDictionary(char *dictPath);

/*
    Esta funcion lee un archivo donde esten guardas palabras, las busca en un tabla hash cargada previamente.
    En caso de no encontrarla, busca posibles correciones y las imprime en un archivo de texto.
*/
void text(char *texPath, TablaHash dict);

#endif /* __COMMON_H__ */