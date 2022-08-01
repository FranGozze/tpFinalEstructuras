run: main.c slist.c tablahash.c dictionary.c common.c functions.c correctWord.c
	- clear
	- gcc main.c  slist.c tablahash.c dictionary.c common.c  functions.c correctWord.c -o main 
	- time ./main input.txt salida.txt
	-rm main
val: main.c slist.c tablahash.c dictionary.c common.c functions.c correctWord.c
	- clear	
	- gcc main.c  slist.c tablahash.c dictionary.c common.c  functions.c correctWord.c -o main
	- valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./main input.txt salida.txt
	- rm main

test: 
	- clear
	- gcc Tests/slist_tests.c  slist.c -o test
	-  ./test
	- rm test

	- gcc Tests/functions_tests.c functions.c dictionary.c correctWord.c tablahash.c slist.c -o test
	- ./test
	- rm test
	
	- gcc Tests/dictionary_tests.c functions.c dictionary.c  tablahash.c slist.c -o test
	- ./test
	- rm test
