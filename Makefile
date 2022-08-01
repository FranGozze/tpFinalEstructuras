run: main.c src/slist.c src/tablahash.c src/dictionary.c src/common.c src/functions.c src/correctWord.c
	- clear
	- gcc main.c  src/slist.c src/tablahash.c src/dictionary.c src/common.c  src/functions.c src/correctWord.c -o main 
	- time ./main input.txt salida.txt
	-rm main
val: main.c src/slist.c src/tablahash.c src/dictionary.c src/common.c src/functions.c src/correctWord.c
	- clear	
	- gcc main.c src/slist.c src/tablahash.c src/dictionary.c src/common.c  src/functions.c src/correctWord.c -o main 
	- valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./main input.txt salida.txt
	- rm main

test: 
	- clear
	- gcc Tests/slist_tests.c  src/slist.c -o test
	- ./test
	- rm test

	- gcc Tests/functions_tests.c src/functions.c src/dictionary.c src/correctWord.c src/tablahash.c src/slist.c -o test
	- ./test
	- rm test
	
	- gcc Tests/dictionary_tests.c src/functions.c src/dictionary.c  src/tablahash.c src/slist.c -o test
	- ./test
	- rm test

	- gcc Tests/correctWord_tests.c src/functions.c src/dictionary.c  src/tablahash.c src/slist.c src/correctWord.c -o test
	- ./test
	- rm test
