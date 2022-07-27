#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Headers/dictionary.h"
#include "Headers/tablahash.h"
#include "Headers/slist.h"
#include "Headers/common.h"
#include "Headers/functions.h"

#include "Headers/correctWord.h"
int main()
{
    TablaHash table = readDictionary("diccionario.txt");
    text("input.txt", table);
    dict_destroy(table);
    return 0;
}