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

void test_dict_hash()
{
    char *test = malloc(sizeof(char) * 4);
    strcpy(test, "abc");
    dict_entry_s *entry = create_entry_with_reference(test, 3);
    // la propia funcion de create_entry llama a dict_hash
    assert(entry->hash == 96354);
    dict_free(entry);
}

void test_dict_cmp()
{
    dict_entry_s *entry1 = create_entry_with_copy("abc", 3);
    dict_entry_s *entry2 = create_entry_with_copy("abc", 3);
    dict_entry_s *entry3 = create_entry_with_copy("abd", 3);

    assert(dict_cmp(entry1, entry2) == 1);
    assert(dict_cmp(entry1, entry3) == 0);

    dict_free(entry1);
    dict_free(entry2);
    dict_free(entry3);
}

void test_dict_add()
{
    TablaHash table = new_dict(100);
    dict_entry_s *entry1 = create_entry_with_copy("abc", 3);
    dict_entry_s *entry2 = create_entry_with_copy("abcd", 4);
    dict_entry_s *entry3 = create_entry_with_copy("abc", 3);
    dict_add(table, entry1);
    dict_add(table, entry2);
    assert(table->elems[entry1->hash % table->capacidad]->data == entry1);
    assert(table->elems[entry1->hash % table->capacidad]->sig == NULL);
    assert(table->elems[entry2->hash % table->capacidad]->data == entry2);
    assert(table->elems[entry2->hash % table->capacidad]->sig == NULL);
    dict_add(table, entry3);
    assert(table->elems[entry3->hash % table->capacidad]->data == entry3);
    assert(table->elems[entry3->hash % table->capacidad]->sig->data == entry1);
    assert(table->elems[entry3->hash % table->capacidad]->sig->sig == NULL);

    dict_free(entry1);
    dict_free(entry2);
    dict_free(entry3);
}

void test_dict_find()
{
    TablaHash table = new_dict(10);
    dict_entry_s *entry1 = create_entry_with_copy("abc", 3);
    dict_add(table, entry1);
    dict_entry_s *entry2 = create_entry_with_copy("abcd", 4);
    // Probamos con otro puntero
    dict_entry_s *entry3 = create_entry_with_copy("abc", 3);
    // No lo encuentra ya que no fue puesto
    assert(dict_find(table, entry2) == 0);
    assert(dict_find(table, entry3) == 1);

    dict_free(entry1);
    dict_free(entry2);
    dict_free(entry3);
}
int main()
{
    test_create_entry();
    test_dict_hash();
    test_dict_cmp();
    test_dict_add();
    test_dict_find();
    return 0;
}
