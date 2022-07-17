run: main.c slist.c tablahash.c dictionary.c common.c functions.c
	- gcc main.c  slist.c tablahash.c dictionary.c common.c  functions.c -o main
	- ./main
val: main.c slist.c tablahash.c dictionary.c common.c functions.c
	- gcc main.c  slist.c tablahash.c dictionary.c common.c  functions.c -o main
	- valgrind ./main