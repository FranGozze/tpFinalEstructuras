#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Headers/dictionary.h"
#include "Headers/tablahash.h"
#include "Headers/slist.h"
#include "Headers/common.h"
#include "Headers/functions.h"

#include "Headers/correctWord.h"
int main(int argc, char **argv)
{
    if (argc < 3)
        exit(1);
    printf("%s %s \n", argv[1], argv[2]);
    TablaHash table = readDictionary("diccionario.txt");
    if (table)
    {
        text("input.txt", table);
        dict_destroy(table);
    }

    return 0;
}