#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/tablahash.h"
#include "../Headers/dictionary.h"
#include "../Headers/correctWord.h"

void test_create_correction()
{
    dict_entry_s *entry = create_entry_with_copy("abc", 3);
    correctWord *testWord = create_correction(entry);

    assert(testWord->entry == entry);

    corrections_free(testWord);
}

void test_correction_cmp()
{
    dict_entry_s *entry1 = create_entry_with_copy("abc", 3);
    dict_entry_s *entry2 = create_entry_with_copy("abc", 3);
    dict_entry_s *entry3 = create_entry_with_copy("abd", 3);
    correctWord *word1 = create_correction(entry1);
    correctWord *word2 = create_correction(entry2);
    correctWord *word3 = create_correction(entry3);

    assert(corrections_cmp(word1, word2) == 1);
    assert(corrections_cmp(word1, word3) == 0);

    corrections_free(word1);
    corrections_free(word2);
    corrections_free(word3);
}

void test_correction_hash()
{
    dict_entry_s *entry = create_entry_with_copy("abc", 3);
    correctWord *testWord = create_correction(entry);
    assert(entry->hash == testWord->entry->hash);
    corrections_free(testWord);
}

int main()
{
    // La funcion que se encarga de hacer los frees se testea con valgrind
    test_create_correction();
    test_correction_cmp();
    test_correction_hash();
    return 0;
}