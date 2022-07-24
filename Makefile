run: main.c slist.c tablahash.c dictionary.c common.c functions.c
	- clear
	- gcc main.c  slist.c tablahash.c dictionary.c common.c  functions.c -o main
	- time ./main
val: main.c slist.c tablahash.c dictionary.c common.c functions.c
	- clear	
	- gcc main.c  slist.c tablahash.c dictionary.c common.c  functions.c -o main
	- valgrind  --track-origins=yes --leak-check=full ./main