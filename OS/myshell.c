//--------------------------------------------
// NAME: Alexandar Apostolov
// CLASS: XI b
// NUMBER: 3
// PROBLEM: #2
// FILE NAME: Alexandar_Apostolov_shell.c
// FILE PURPOSE:
// To reallize a simple command interpreter - shell.
// The program reads lines from STDIN and intepret them,
// divinding them by intervals, returning them as arrays
// of strings. The first string is a file name. 
// The program should try to execute the file, giving
// it the rest of the array's strings as arguments.
//---------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


const int STDIN_LENGTH = 512;

//--------------------------------------------
// FUNCTION: clean
// Cleans newline and tabulations 
// from a C string.
// PARAMETERS:
// const char* string -> string for parsing
//----------------------------------------------
char *clean(const char *string) {
	
  	char *cleaned = malloc(strlen(string) + 1);
	if(cleaned) {
		char *temp = cleaned;
		while(*string != '\0') {
			if(*string != '\t' && *string != '\n') {
				*temp++ = *string++;
			} 
			else {
				++string;
			}
		}
		*temp = '\0';
	}
	
	//printf("\ncleaned:\n%s\n",cleaned);
	return cleaned;
}	

//--------------------------------------------
// FUNCTION: parse_cmdline
// Parses the input, delimiting it by intervals
// and returning it in an array of C strings.
// PARAMETERS:
// const char* cmdline - the input string
//----------------------------------------------
char **parse_cmdline(const char *cmdline) { // why const?? why?

	int cmdl_size = strlen(cmdline);
	char *non_const_cmdline = (char*) malloc(cmdl_size*sizeof(char));
	// ^ why would you make the other one const? T.T
	strcpy(non_const_cmdline, cmdline);
	
	char **cmds = (char**) malloc((cmdl_size+1)*sizeof(char));
	int i = 0;
	
	char s[4] = " \t\n";
	char *token = strtok(non_const_cmdline, s); // first token

	// walk through the other tokens 
	while (token != NULL) 
	{
		cmds[i] = token;
		//printf( "%s\n", token);
		token = strtok(NULL, s);
		i++;
	}
	
	cmds[i] = NULL; // marks the end of the array for the execv() function 
	
	free(non_const_cmdline);
	return cmds;
}

//--------------------------------------------
// FUNCTION: main
// Main function.
// Runs an infinite loop to get the input.
// Creates the new process.
// Executes the shell commands.
// Checks for errors.
// PARAMETERS: -
//----------------------------------------------
int main () {

	while(1) { // infinite loop for input
		
		char input[STDIN_LENGTH];
		int input_chars = 0;
	
		fgets(input, STDIN_LENGTH, stdin);

		if(input == NULL) { // shit happens
			printf("Input error!");
		} 
		else if(!strcmp(clean(input), "exit")) {
			exit(0); // exit the program on input "exit"
		} 
		else { // parsing input
			char **res = parse_cmdline(clean(input));
			int i = 0;
			while (i < 3) {printf("%d: %s\n", i, res[i]); i++;}
			
			pid_t pid = fork();
			
			if (pid == 0) { // child process
				
				int err_check = execv(res[0], res);
				if (err_check == -1) {
					perror(res[0]);
					exit(1);
				}
			}
			else if (pid > 0) { // parent process
				
				int status;
				pid_t child = waitpid (pid, &status, 0);	// waiting for child state change
		
				if(status < 0) {
					perror("Child Process Error");
					return -2;
				}
				
				//if (cmds != NULL) free(cmds);
				//if (non_const_cmdline != NULL) free(non_const_cmdline);
				
			}
			else { // if process creation fails

				perror("Process could not be created");
				return -3;
			}
			
			free(res);	
		} // end of parsing input
			
	} // infinite while
	
	return 0;
}
