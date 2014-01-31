//--------------------------------------------
// NAME: Alexandar Apostolov
// CLASS: XI b
// NUMBER: 3
// PROBLEM: #1
// FILE NAME: Alexandar_Apostolov_head.c
// FILE PURPOSE:
// To recreate the Unix command "head" which 
// recieves a list of files as arguments and 
// prints the first 10 rows of every file in 
// the Terminal
//---------------------------------------------

#include <stdio.h> // The program is running without it, but you always put so... 
#include <unistd.h> // including STDOUT_FILENO, read(), write(), close()
#include <fcntl.h> // including O_RDWR, open()
#include <sys/stat.h> // including S_IRUSR, S_IWUSR
#include <string.h> // including strlen()
#include <errno.h> // including errno

int main (int argc, char* argv[]) {
	
	int i = 1;
	while (argv[i] != '\0') { // loop for all the files in argv[]
		
		if ((*argv[i]) != '-') { // if we DON'T have an '-' argument we enter here 
		
			int file; // this is the file descriptor
			file = open(argv[i], O_RDWR, S_IRUSR|S_IWUSR); // opening the current file
		
			char *filename = argv[i];
		
			if (file == -1) {	// gives us error if the file failed to open
				
				char error1[] = "head: cannot open '";
				strcat(error1, filename);
				char error2[] = "' for reading";
				strcat(error1, error2);
				perror(error1);
				return -12;
				
			}
		
			if (argv[2] != '\0') {	// if we have only one argument we skip the title writing
		
				char ftitle_b[] = "==> "; // the beginning of the title for every file
				char ftitle_e[] = " <==\n"; // the end of the title for every file
		
				int w_title;
				w_title = write(STDOUT_FILENO, ftitle_b, 4); // writing the beginning of the title
		
				if (w_title == -1) { // check for error in write()
					char error[] = "head: Error Writing Title_beginning - ";
					strcat(error, filename);
					perror(error);
					return -2;
				}
		
				w_title = write(STDOUT_FILENO, argv[i], strlen(argv[i])); // writing the name of the file
		
				if (w_title == -1) { // check for error in write()
					char error[] = "head: Error Writing File Name - ";
					strcat(error, filename);
					perror(error);
					return -3;
				}
		
				w_title = write(STDOUT_FILENO, ftitle_e, 5); // writing the end of the title
		
				if (w_title == -1) { // check for error in write()
					char error[] = "head: Error Writing Title_end - ";
					strcat(error, filename);
					perror(error);
					return -4;
				}
			}

			char reader; // the buffer
			int rows = 1; // number of rows

			while (rows <= 10) {	// loop for the reading of the first 10 rows
				int status;
				status = read(file, &reader, sizeof(char)); // reading one char
			
				if (status == -1) {	// gives us error if it can't read the char
					char error[] = "head: Error Reading File - ";
					strcat(error, filename);
					perror(error);
					return -5;
				}
		
				if (reader == '\n') { // counts the rows

					rows += 1;
				}
			
				int result;
				result = write(STDOUT_FILENO, &reader, status); // writing the read char in the standart output
			
				if (result == -1) { // check for error in write()
					char error[] = "head: Error Writing In File - ";
					strcat(error, filename);
					perror(error);
					return -6;
				}
			
	
			}

			if (close(file)) { // gives us error if the file failed to close
				char error[] = "head: Error Closing File - ";
				strcat(error, filename);
				perror(error);
				return -7;
			}
		
		} // if argv[i] != '-'
		
		else {
			int rows2 = 1;
			char reader = '0'; // buffer
			while (rows2 <= 10) {
				int status = -1;
				status = read(STDIN_FILENO, &reader, sizeof(char)); // read from the standart input char by char
			
				if (status == -1) {	// gives us error if it can't read the char
					perror("head: Error Writing In STDOUT");
					return -10;
				}
				
				if (reader == '\n') { // counts the rows

					rows2 += 1;
				}
			
				int result;
				result = write(STDOUT_FILENO, &reader, status);
			
				if (result == -1) { // check for error in write()
					perror("head: Error Writing In STDIN");
					return -11;
				}
				 	
			}
			
		} // else

		i += 1; // next file, if such exists

	} // while argv[i] != '\0'
	
	if (argv[1] == '\0') { // if we have no arguments we enter here
		char reader = '0'; // buffer
		while (reader != EOF) {
			int status = -1;
			status = read(STDIN_FILENO, &reader, sizeof(char)); // read from the standart input char by char
			
			if (status == -1) {	// gives us error if it can't read the char
				perror("head: Error Writing In STDOUT");
				return -8;
			}
			
			int result;
			result = write(STDOUT_FILENO, &reader, status);
			
			if (result == -1) { // check for error in write()
				perror("head: Error Writing In STDIN");
				return -9;
			}
			 	
			
		}
	}

	return 0;
}

