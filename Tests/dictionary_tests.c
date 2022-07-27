#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Headers/tablahash.h"
#include "../Headers/dictionary.h"

void test_create_entry()
{
    char *test = malloc(sizeof(char) * 4);
    strcmp(test, "abc");
    dict_entry_s *entry = create_entry_with_copy(test, 3);
    dict_entry_s *entry2 = create_entry_with_reference(test, 3);
    assert(strcmp(entry->key, test) == 0 && entry->key != test && entry->keyLength);
    assert(strcmp(entry2->key, test) == 0 && entry2->key == test && entry2->keyLength);

    dict_free(entry);
    dict_free(entry2);
}

int main()
{
    test_create_entry();
    return 0;
}
