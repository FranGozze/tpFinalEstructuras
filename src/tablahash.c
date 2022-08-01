#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../Headers/tablahash.h"
#include "../Headers/slist.h"

/**
 * Estructura principal que representa la tabla hash.
 */

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash create_tablehash(unsigned capacidad, FuncionCopiadora copia,
                           FuncionComparadora comp, FuncionDestructora destr,
                           FuncionHash hash)
{

  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  assert(tabla != NULL);
  tabla->elems = malloc(sizeof(SList) * capacidad);
  assert(tabla->elems != NULL);
  tabla->numElems = 0;
  tabla->capacidad = capacidad;
  tabla->copia = copia;
  tabla->comp = comp;
  tabla->destr = destr;
  tabla->hash = hash;

  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < capacidad; ++idx)
  {
    tabla->elems[idx] = NULL;
  }

  return tabla;
}

/**
 * Retorna el numero de elementos de la tabla.
 */
int tablahash_nelems(TablaHash tabla) { return tabla->numElems; }

/**
 * Retorna la capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla) { return tabla->capacidad; }

/**
 * Destruye la tabla.
 */
void destroy_tablehash(TablaHash tabla)
{

  // Destruir cada uno de los datos.
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx)
    if (tabla->elems[idx] != NULL)
      for (SList node = tabla->elems[idx]; node;)
      {
        SList oldNode = node;
        node = (node)->sig;
        tabla->destr(oldNode->data);
        free(oldNode);
      }

  // Liberar el arreglo de casillas y la tabla.
  free(tabla->elems);
  free(tabla);
  return;
}

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 * IMPORTANTE: La implementacion no maneja colisiones.
 */
void insert_tablehash(TablaHash tabla, void *dato)
{
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  tabla->numElems++;

  list_push(&tabla->elems[idx], dato);
  return;
}

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void *find_tablahash(TablaHash tabla, void *dato)
{
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  if (tabla->elems[idx] == NULL)
    return NULL;

  else
    for (SList node = tabla->elems[idx]; node; node = node->sig)
      if (tabla->comp(node->data, dato))
        return node->data;

  // Retornar NULL en otro caso.
  return NULL;
}

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato)
{

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Retornar si la casilla estaba vacia.
  if (tabla->elems[idx] == NULL)
    return;
  // Vaciar la casilla si hay coincidencia.
  else
    for (SList node = tabla->elems[idx]; node; node = node->sig)
      if (tabla->comp(node->data, dato))
      {
        tabla->numElems--;
        // VER ESTO
        // tabla->destr(node);
        tabla->elems[idx] = NULL;
        return;
      }
}

/**
 * Funcion de hash para strings propuesta por Kernighan & Ritchie en "The C
 * Programming Language (Second Ed.)".
 */
unsigned KRHash(char *s)
{
  unsigned hashval;
  for (hashval = 0; *s != '\0'; ++s)
    hashval = (*s) + 31 * hashval;

  return hashval;
}