run: main.c src/slist.c src/tablahash.c src/dictionary.c src/common.c src/functions.c src/correctWord.c
	- clear
	- gcc -g -std=c99 main.c  src/slist.c src/tablahash.c src/dictionary.c src/common.c  src/functions.c src/correctWord.c -o corrector 
	
memory: main.c src/slist.c src/tablahash.c src/dictionary.c src/common.c src/functions.c src/correctWord.c
	- clear	
	- gcc -g -std=c99 main.c src/slist.c src/tablahash.c src/dictionary.c src/common.c  src/functions.c src/correctWord.c -o main 
	- valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./main inputValgrind.txt salida.txt
	- rm main

test: 
	- clear
	- gcc -g -std=c99 Tests/slist_tests.c  src/slist.c -o test
	- ./test
	- rm test

	- gcc -g -std=c99 Tests/functions_tests.c src/functions.c src/dictionary.c src/correctWord.c src/tablahash.c src/slist.c -o test
	- ./test
	- rm test
	
	- gcc -g -std=c99 Tests/dictionary_tests.c src/functions.c src/dictionary.c  src/tablahash.c src/slist.c -o test
	- ./test
	- rm test

	- gcc -g -std=c99 Tests/correctWord_tests.c src/functions.c src/dictionary.c  src/tablahash.c src/slist.c src/correctWord.c -o test
	- ./test
	- rm test
