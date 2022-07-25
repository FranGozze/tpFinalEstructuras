run: main.c slist.c tablahash.c dictionary.c common.c functions.c correctWord.c
	- clear
	- gcc main.c  slist.c tablahash.c dictionary.c common.c  functions.c correctWord.c -o main  
	- time ./main
	-rm main
val: main.c slist.c tablahash.c dictionary.c common.c functions.c correctWord.c
	- clear	
	- gcc main.c  slist.c tablahash.c dictionary.c common.c  functions.c correctWord.c -o main
	- valgrind  --track-origins=yes --leak-check=full ./main
	-rm main