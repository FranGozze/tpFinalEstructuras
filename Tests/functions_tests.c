#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Headers/functions.h"
#include "../Headers/dictionary.h"
#include "../Headers/tablahash.h"
#include "../Headers/correctWord.h"

void test_delete()
{
    TablaHash dict = new_dict(10);
    dict_entry_s *entry = create_entry_with_copy("ac", 2);
    dict_add(dict, entry);
    TablaHash partialResultsTable = new_dict(10);
    dict_entry_s *test = create_entry_with_copy("abc", 3);
    correctWord *correctionsTest = create_correction(test);
    int *position1 = malloc(sizeof(int)), *position2 = malloc(sizeof(int));
    *position1 = 0;
    *position2 = 0;
    dict_entry_s *partialResults[10] = {NULL};
    delete_letter(test, correctionsTest->corrections, position1, partialResultsTable, dict, partialResults, position2, 0);

    assert((*position2) == 3);
    assert(partialResultsTable->numElems == 3);
    assert(strcmp(partialResults[0]->key, "bc") == 0 && partialResults[0]->keyLength == 2);
    assert(strcmp(partialResults[1]->key, "ac") == 0 && partialResults[0]->keyLength == 2);
    assert(strcmp(partialResults[2]->key, "ab") == 0 && partialResults[0]->keyLength == 2);

    assert((*position1) == 1);
    assert(strcmp(correctionsTest->corrections[0]->key, "ac") == 0 && correctionsTest->corrections[0]->keyLength == 2);

    dict_destroy(dict);
    dict_destroy(partialResultsTable);
    corrections_free(correctionsTest);
    free(position1);
    free(position2);
}
void test_insert()
{
    TablaHash dict = new_dict(10);
    dict_entry_s *entry = create_entry_with_copy("adbc", 4);
    dict_add(dict, entry);
    TablaHash partialResultsTable = new_dict(4 * 26);
    dict_entry_s *test = create_entry_with_copy("abc", 3);
    correctWord *correctionsTest = create_correction(test);
    int *position1 = malloc(sizeof(int)), *position2 = malloc(sizeof(int));
    *position1 = 0;
    *position2 = 0;
    dict_entry_s *partialResults[4 * 26] = {NULL};
    insert_letter(test, correctionsTest->corrections, position1, partialResultsTable, dict, partialResults, position2, 0);

    assert((*position2) <= (4 * 26));
    assert(partialResultsTable->numElems <= (4 * 26));
    assert((*position1) == 1);
    assert(strcmp(correctionsTest->corrections[0]->key, "adbc") == 0 && correctionsTest->corrections[0]->keyLength == 4);

    dict_destroy(dict);
    dict_destroy(partialResultsTable);
    corrections_free(correctionsTest);
    free(position1);
    free(position2);
}
void test_change()
{
    TablaHash dict = new_dict(10);
    dict_entry_s *entry = create_entry_with_copy("aac", 4);
    dict_add(dict, entry);
    TablaHash partialResultsTable = new_dict(3 * 26);
    dict_entry_s *test = create_entry_with_copy("abc", 3);
    correctWord *correctionsTest = create_correction(test);
    int *position1 = malloc(sizeof(int)), *position2 = malloc(sizeof(int));
    *position1 = 0;
    *position2 = 0;
    dict_entry_s *partialResults[3 * 26] = {NULL};
    change_letter(test, correctionsTest->corrections, position1, partialResultsTable, dict, partialResults, position2, 0);

    assert((*position2) <= (3 * 26));
    assert(partialResultsTable->numElems <= (3 * 26));
    assert((*position1) == 1);
    assert(strcmp(correctionsTest->corrections[0]->key, "aac") == 0 && correctionsTest->corrections[0]->keyLength == 3);

    dict_destroy(dict);
    dict_destroy(partialResultsTable);
    corrections_free(correctionsTest);
    free(position1);
    free(position2);
}
void test_swap()
{
    TablaHash dict = new_dict(10);
    dict_entry_s *entry = create_entry_with_copy("acb", 3);
    dict_add(dict, entry);
    TablaHash partialResultsTable = new_dict(10);
    dict_entry_s *test = create_entry_with_copy("abc", 3);
    correctWord *correctionsTest = create_correction(test);
    int *position1 = malloc(sizeof(int)), *position2 = malloc(sizeof(int));
    *position1 = 0;
    *position2 = 0;
    dict_entry_s *partialResults[10] = {NULL};
    swap_letter(test, correctionsTest->corrections, position1, partialResultsTable, dict, partialResults, position2, 0);

    assert((*position2) == 2);
    assert(partialResultsTable->numElems == 2);
    assert(strcmp(partialResults[0]->key, "bac") == 0 && partialResults[0]->keyLength == 3);
    assert(strcmp(partialResults[1]->key, "acb") == 0 && partialResults[0]->keyLength == 3);
    assert((*position1) == 1);
    assert(strcmp(correctionsTest->corrections[0]->key, "acb") == 0 && correctionsTest->corrections[0]->keyLength == 3);

    dict_destroy(dict);
    dict_destroy(partialResultsTable);
    corrections_free(correctionsTest);
    free(position1);
    free(position2);
}
void test_separate()
{

    TablaHash dict = new_dict(10);
    dict_entry_s *entry = create_entry_with_copy("a", 1);
    dict_entry_s *entry2 = create_entry_with_copy("bc", 2);
    dict_add(dict, entry);
    dict_add(dict, entry2);
    TablaHash partialResultsTable = new_dict(10);
    dict_entry_s *test = create_entry_with_copy("abc", 3);
    correctWord *correctionsTest = create_correction(test);
    int *position1 = malloc(sizeof(int)), *position2 = malloc(sizeof(int));
    *position1 = 0;
    *position2 = 0;
    dict_entry_s *partialResults[10] = {NULL};

    separate_words(test, correctionsTest->corrections, position1, partialResultsTable, dict, partialResults, position2, 0);

    assert(partialResultsTable->numElems == 0);
    assert((*position1) == 1);
    assert(strcmp(correctionsTest->corrections[0]->key, "a bc") == 0 && correctionsTest->corrections[0]->keyLength == 4);

    dict_destroy(dict);
    dict_destroy(partialResultsTable);
    corrections_free(correctionsTest);
    free(position1);
    free(position2);
}

int main()
{
    test_delete();
    test_separate();
    test_swap();
    test_insert();
    test_change();
    return 0;
}