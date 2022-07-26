run: main.c slist.c tablahash.c dictionary.c common.c functions.c correctWord.c
	- clear
	- gcc main.c  slist.c tablahash.c dictionary.c common.c  functions.c correctWord.c -o main  
	- time ./main
	-rm main
val: main.c slist.c tablahash.c dictionary.c common.c functions.c correctWord.c
	- clear	
	- gcc main.c  slist.c tablahash.c dictionary.c common.c  functions.c correctWord.c -o main
	- valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./main
	-rm main