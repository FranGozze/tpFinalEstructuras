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
    TablaHash dict = readDictionary("diccionario.txt");
    if (dict)
    {
        text(argv[1], dict, argv[2]);
        dict_destroy(dict);
    }

    return 0;
}