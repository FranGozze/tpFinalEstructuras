#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"
#include "tablahash.h"
#include "slist.h"
#include "common.h"
#include "functions.h"

#include "correctWord.h"
int main()
{
    TablaHash table = readDictionary("diccionario.txt");
    text("input.txt", table);
    dict_destroy(table);
    // char *aa = malloc(sizeof(char) * 4);
    // strcpy(aa, "123");
    // dict_entry_s *entry = create_entry_with_reference(aa, strlen(aa));
    // correctWord *cor = create_correction(entry);
    // corrections_free(cor);
    // dict_free(entry);
    //  dict_entry_s *entry = create_entry("aa");
    //  printf("%d\n", dict_find(table, entry));
    return 0;
}