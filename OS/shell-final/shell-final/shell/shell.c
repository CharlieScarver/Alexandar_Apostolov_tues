#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Constants
const int COMMAND_LINE_LENGTH = 512; // size of command buffer
// for freeing the memory after parse_cmdline:
char* new_cmdline;
char** result;

// Global Variables
int arguments_count = 0; // used by the parse_cmdline function to cound the arguments in a string

//--------------------------------------------
// FUNCTION: strip
// Parses a C string and removes newline and 
// tabulation characters.
// PARAMETERS:
// const char* s - string to be parsed
//----------------------------------------------
char* strip(const char *string) {
	char *res = malloc(strlen(string) + 1);
	if(res) {
		char *temp = res;
		while(*string != '\0') {
			if(*string != '\t' && *string != '\n') {
				*temp++ = *string++;
			} else {
				++string;
			}
		}
		*temp = '\0';
	}
	return res;
}

//--------------------------------------------
// FUNCTION: parse_cmdline
// Parses a C string and delivers it words 
// delimited by whitespace in an array of 
// C strings
// PARAMETERS:
// const char* cmdline - a whole string with 
//	arguments
//----------------------------------------------
char** parse_cmdline(const char* cmdline) {
	int line_size = strlen(cmdline);
	new_cmdline = (char*) malloc(line_size*sizeof(char));
	char* lastpointer;
	result = (char**) malloc((line_size+1)*sizeof(char));
	arguments_count = 0;
	
	strcpy(new_cmdline, cmdline);
	lastpointer = strtok(new_cmdline," \t\n");
		
	while (lastpointer != NULL) {
		result[arguments_count] = lastpointer;
		lastpointer = strtok(NULL, " \t\n");
		arguments_count++;
	}

	result[arguments_count] = NULL;

	return result;
}

//--------------------------------------------
// FUNCTION: interpret
// Execution of shell commands.
// PARAMETERS:
// char* commands - C string containing the
//	commands that will be executed
//----------------------------------------------
int interpret(char* commands) {
	char** cmdline_buffer;
	pid_t pid = fork();

	if(pid == 0) {

		//child
		int i = 0;
		cmdline_buffer = parse_cmdline(commands);
		
		if(execv(cmdline_buffer[0], cmdline_buffer) == -1) {
			perror("Error");
			exit(1);
		}

	} else if (pid > 0) {
		
		// parent
		int status;
		pid_t child = waitpid (pid, &status, 0);		
		
		if(status < 0) {
			perror("Process error");
			return 1;
		}
		
		if(new_cmdline != NULL)
			free(new_cmdline);
		if(result != NULL)
			free(result);

	} else {
		
		// error
		perror("Error creating a new process");
		return 1;
	}
	
	return 0;
}

//--------------------------------------------
// FUNCTION: main
// Main function of the program.
// PARAMETERS:
// none
//----------------------------------------------
int main () {

	while(1) {
		printf("> ");
		
		char current_string[COMMAND_LINE_LENGTH];
		int input_chars = 0;
		
		fgets(current_string, COMMAND_LINE_LENGTH, stdin);

		if(current_string == NULL) {
			printf(">>> Something with your input is terribly wrong!\n");
			continue;
		} else if(strcmp(strip(current_string), "exit") == 0) {
			printf(">>> I, the Shell, will miss you! Have a nice day!\n");
			exit(0);
		} else if(strcmp(strip(current_string), "") == 0) {
			continue;
		} else {
			if(interpret(strip(current_string)) == 1) {
				continue;
			}	
		}
	} // end while
	
	return 0;
}
