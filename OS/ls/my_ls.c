#include <stdio.h>
#include <dirent.h> 
#include <unistd.h>

int a_opt = 0;

void get_flags (int ac, char* av[]);
void read_dir (char* dir);

int main(int argc, char *argv[]) {

	get_flags(argc, argv);

    if(optind == argc) {
    	read_dir(".");
    }
    
    int i = 1;
    for(i = argc - 1; i >= optind; i--) {
    	read_dir(argv[i]);
    }

	return 0;
}

void get_flags (int ac, char* av[]) {

	char options;
	while ((options = getopt(ac,av,"a")) != -1) {
		switch (options) {
			case 'a':
				a_opt = 1;
				break;
		}
	}
	
}

void read_dir (char* dir) {

    struct dirent *pDirent;
    DIR *pDir;

    pDir = opendir (dir);
    if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", dir);
    } else {
    
		while ((pDirent = readdir(pDir)) != NULL) {
			if(pDirent->d_name[0] != '.' || a_opt == 1) {
			    printf ("%s\n", pDirent->d_name);
			}
		}
		
	}
	
    closedir (pDir);

}


