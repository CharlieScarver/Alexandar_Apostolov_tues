#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
	
	char *input[1000];
	char chunk[50];
	
	int let_cnt = 0, word_cnt = 0;
	char buffer;
	read(STDIN_FILENO, &buffer, 1);
	while (buffer != '1') {
	
		if ((buffer == ' ') || (buffer == '\n')) {
			input[word_cnt] = chunk;
			printf("%s, del\n", input[word_cnt]);
			memset(chunk,0,sizeof(chunk));
			word_cnt++;
			let_cnt = 0;
		} else {
			chunk[let_cnt] = buffer;
			printf("pass\n");
			let_cnt++;
		}
		
		read(STDIN_FILENO, &buffer, 1);
	}
	
	printf("\n%s\n", chunk);
	/*
	for (let_cnt = 0; let_cnt < 5; let_cnt++) {
		//printf("\nYour input is: \n%s\n", chunk);
		printf("input[%d] = %s\n", let_cnt, input[let_cnt]);
	}
	*/
	
	// Bez chunk direktno zapazvame buffer v input[...]
	
	return 0;
}

