#include <stdio.h> 
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>

//---------------------------------------------
// FUNCTION: read_directory
// It receives the current directory name and
// display mode (if display mode equals 1, it 
// displays permissions, otherise, it doesn't)
//---------------------------------------------
int read_directory(char*, int);

//---------------------------------------------
// FUNCTION: determine_flags
// It receives argc and argv and iterates over
// argv, finding the searched characters
//---------------------------------------------
void determine_flags(int, char*[]);
//---------------------------------------------
// FUNCTION: display_stats
// It receives current file name and stat
// for that file, so that it can print the
// file's permissions
//---------------------------------------------
void display_stats(char*, struct stat);

int l_flag = 0;
int a_flag = 0;
int R_flag = 0;
int total = 0;
int number_of_subdirectories;
char** subdirectories = NULL;
int is_directory = 0;

int main(int argc, char *argv[]) {

	int i = 1;

	determine_flags(argc, argv);
	
	if(optind == argc) {
		total = read_directory(".", 0);
		printf("%s:\n", ".");
		if(l_flag == 1) {
			printf("total %d\n", total);
		}	
		read_directory(".", 1);
	}

	for(i = argc - 1; i >= optind; i--) {
		total = read_directory(argv[i], 0);
		if(is_directory == 1) {
			printf("%s:\n", argv[i]);
			if(l_flag == 1) {
				printf("total %d\n", total);
			}
			read_directory(argv[i], 1);
		}

		if(i > optind) {
			printf("\n");
		}
		is_directory = 0;
	}

	return 0;
}

int read_directory(char* directory, int display_mode) {
	DIR *dir = opendir(directory);
	int total = 0;
	struct dirent *dt;
	struct stat current_file_stat;
	if(dir != NULL) {
			
		while((dt = readdir(dir)) != NULL) {
			/*char first[500];
			char second[300];
			strcpy(first, directory);
			strcat(first, "/");
			strcpy(second, dt->d_name);
			strcat(first, second);*/

			if((strcmp(dt->d_name, ".") == 0) || (strcmp(dt->d_name, "..") == 0) || (dt->d_name[0] == '.')) {
				
				if((strcmp(dt->d_name, ".") == 0) || (strcmp(dt->d_name, "..") == 0)) {
					is_directory = 1;
				}
				if(a_flag == 0 ) {
					continue;
				}
			}
			if(l_flag == 0) {
				if(display_mode == 1) {
					printf("%s\n", dt->d_name);
				}
			}else if(l_flag == 1) {
				char first[2048];
				char second[512];
				strcpy(first, directory);
				strcat(first, "/");
				strcpy(second, dt->d_name);
				strcat(first, second);		
		
				if(stat(first, &current_file_stat) == -1) {
					//fprintf(stderr, "ls: cannot open directory %s:\n", dt->d_name);
				}

				total += current_file_stat.st_blocks;

				if(display_mode == 1) {
					display_stats(first, current_file_stat);
				}
					
			}
			
		}	
		//if(errno != 0) perror("readdir:");

		closedir(dir);
		if(R_flag == 1) {
				dir = opendir(directory);
				if(dir != NULL) {
					while((dt = readdir(dir)) != NULL) {
						if(stat(dt->d_name, &current_file_stat) == -1) {
							//fprintf(stderr, "ls: cannot open directory %s:\n", dt->d_name);
						}
						if(S_ISDIR(current_file_stat.st_mode) && ((strcmp(dt->d_name, ".") != 0) && (strcmp(dt->d_name, "..") != 0))) {
								printf("%s\n", dt->d_name);
								total = read_directory(dt->d_name, 0);
								printf("%s:\n", dt->d_name);
								if(l_flag == 1) {
									printf("total %d\n", total);
								}
								read_directory(dt->d_name, 1);
							
							
						}
					}
				}
			}
		
	} else {
		if(access(directory, F_OK) != -1) {
			if(stat(directory, &current_file_stat) == -1) {
				fprintf(stderr, "ls: cannot access file %s:\n", directory);
			}
			if((strcmp(directory, ".") == 0) || (strcmp(directory, "..") == 0) || (directory[0] == '.')) {
				if(a_flag == 0) {
					//continue;
				}
			}
			if(l_flag == 0) {
				printf("%s\n", directory);
			} else if(l_flag > 0) {	
		
				if(stat(directory, &current_file_stat) == -1) {
					fprintf(stderr, "ls: cannot open directory %s:\n", directory);
				}

				total += current_file_stat.st_blocks;

				if(display_mode == 1) {
					display_stats(directory, current_file_stat);
				}
					
			}

		} else {
			//fprintf(stderr, "ls: cannot access %s: No such file or directory\n", directory);
		}
	}
	return total / 2;
}

void determine_flags(int ac, char* av[]) {
	char current_options;
	while((current_options = getopt(ac, av, "lRa")) != -1) {
		switch(current_options) {
			case 'a':
				a_flag = 1;
				break;
			case 'R':
				R_flag = 1;
				break;
			case 'l':
				l_flag = 1;
				break;
		}
	}
}

void display_stats(char* name, struct stat current_file_stat) {
	if(S_ISDIR(current_file_stat.st_mode)) {
		printf("d");
	} else { 
		printf("-");
	}
	if(current_file_stat.st_mode & S_IRUSR) {
		printf("r");
	} else { 
		printf("-");
	}
	if(current_file_stat.st_mode & S_IWUSR) {
		printf("w");
	} else {
		printf("-");
	}
	if(current_file_stat.st_mode & S_IXUSR) {
		printf("x");
	} else {
		printf("-");
	}
	if(current_file_stat.st_mode & S_IRGRP) {
		printf("r");
	} else {
		printf("-");
	}
	if(current_file_stat.st_mode & S_IWGRP) {
		printf("w");
	} else {
		printf("-");
	}
	if(current_file_stat.st_mode & S_IXGRP) {
		printf("x");
	} else {
		printf("-");
	}
	if(current_file_stat.st_mode & S_IROTH) {
		printf("r");
	} else {
		printf("-");
	}
	if(current_file_stat.st_mode & S_IWOTH) {
		printf("w");
	} else {
		printf("-");
	}
	if(current_file_stat.st_mode & S_IXOTH) {
		printf("x");
	} else {
		printf("-");
	}

	printf(" %3d ", current_file_stat.st_nlink);
		
	struct passwd *pw = getpwuid(current_file_stat.st_uid);
	struct group *gr = getgrgid(current_file_stat.st_gid);
	if(pw != NULL) {
		printf("%6s ", pw->pw_name);
	}
	if(gr != NULL) {
		printf("%6s ", gr->gr_name);
	}

	printf("%8lld " , (long long) current_file_stat.st_size);		
					
	char last_modified_date[20];
	strftime(last_modified_date, 20, " %F  %k:%M", localtime(&(current_file_stat.st_mtime)));
	printf("%s ", last_modified_date);
	printf(" %s\n", name);

}







