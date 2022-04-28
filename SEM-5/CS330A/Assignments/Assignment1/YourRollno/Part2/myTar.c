#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

int main( int arg, char** args){
	
	printf("%s\n", args[1]);

	if( strcmp( args[1], "-c") == 0 ){                          // creation of args[3] tar file inside args[2] directory path.

		if( arg != 4 ){
			perror("Failed to complete creation operation\n");
			exit(1);
		}

		printf("check1\n");                            // For testing purpose, args[2] = ~/testfiles/

		int k = 0;
		k = chdir( args[2]);                           // k = 0 on success and -1 in case of error.
		DIR *dir;
		if ((dir = opendir (".")) == NULL) {
    	    perror ("Failed to complete creation operation");
    	    exit (1);
    	}
		if( k < 0 ){
			k = write( 2, "Failed to complete creation operation\n", 39);
		}
		
		// fd1 points to tar file for writing and reading.
		int fd1 = open( args[3], O_CREAT | O_RDWR, 0644 );
		FILE* fptr1 = fopen( args[3], "a");
		if( fd1 < 0 || fptr1 == NULL ){
			write( 2, "Failed to complete creation operation\n", 39);
			exit(-1);
		}

		struct dirent *dp;
		while( (dp = readdir(dir)) ){
			if( (strcmp(dp->d_name, ".") == 0) || (strcmp(dp->d_name, "..") == 0) || (strcmp( dp->d_name, args[3]) == 0) ) continue;
			char buff[17];
			strcpy( buff, dp->d_name);
			int fd2 = open( buff, O_RDONLY);
			FILE* fptr2 = fopen( buff, "r");
			if( fptr2 == NULL || fd2 < 0 ){
				perror("Failed to complete creation operation\n");
				exit(1);
			}
			int s = strlen(buff);
			write( fd1, buff, s);
			write( fd1, " ", 1);
			struct stat record;
    		fstat( fd2, &record);
    		long int size = record.st_size;

			char len[16];
			sprintf( len, "%ld", size);
			write( fd1, len, strlen(len));
			write( fd1, "\n", 1);
			if( fd2 < 0 ){
				int t = write( 2, "Failed to complete creation operation\n", 39);
				exit(-1);
			}
			
			char c[1];
			while( read( fd2, c, 1) == 1 ){
				write( fd1, c, 1);
			}
			
			write( fd1, "\n", 1);
			close(fd2);
			fclose(fptr2);
		}

		close(fd1);
		fclose(fptr1);
		closedir(dir);
	}


	if( strcmp( args[1], "-d") == 0 ){                           // Extraction of all files from tar file located at args[2] /location/<tar_file_name>.
		printf("check2\n");
		// Printing Potel Piolet Piyush Standard Piyush

		if( arg != 3 ){
			perror("Failed to complete extraction operation");
			exit(1);
		}

		char* temp = strtok( args[2], "/");
		char* address = (char *)malloc(50*sizeof(char));
		address[0] = '/';
		address[1] = '\0';
		
		char* filename;
		while( temp != NULL ){
			strcat( address, temp);
			strcat( address, "/");
			filename = temp;
			temp = strtok( NULL, "/");
		}
		int t = strlen(filename);
		address[strlen(address)-t-2] = '\0';

		int k = 0;
		k = chdir( address);                                                         // k = 0 on success and -1 in case of error.
		if( k < 0 ){
			k = write( 2, "Failed to complete extraction operation\n", 35);
		}
		DIR *dir;
		if ((dir = opendir (".")) == NULL) {
    	    perror("Failed to complete extraction operation");
    	    exit(1);
    	}

		char dirname[60];
		dirname[0] = '\0';
		strcat( dirname, filename);
		dirname[strlen(dirname)-4] = '\0';
		strcat( dirname, "Dump");

		k = mkdir( dirname, 0777);
		if( k < 0 ){
			perror("Failed to complette exraction operation");
			exit(1);
		}
		// return 0;
		int fd2 = open( filename, O_RDONLY);                //fd2 points to tar file.
		
		k = chdir( dirname);                                                // k = 0 on success and -1 in case of error.
		if( k < 0 ){
			perror("Failed to complete extraction operation\n");
			exit(1);
		}
		// return 0;
		DIR* dir1;
		if ((dir1 = opendir (".")) == NULL) {
  		    perror("Failed to complete extraction operation\n");
  		    exit (1);
	  	}
		// return 0;
		char c[1], file_name[17], file_size[16];
		read( fd2, c, 1);
		int i = 0;
		while( c[0] != ' ' && c[0] != '\n' ){
			i = 0;
			while( c[0] != ' ' ){
				file_name[i++] = c[0];
				read( fd2, c, 1);
			}
			file_name[i] = '\0';
			i = 0;
			read( fd2, c, 1);
			while( c[0] != '\n' ){
				file_size[i++] = c[0];
				read( fd2, c, 1);
			}
			file_size[i] = '\0';
			int local_size = atoi( file_size);
			char* buff = (char *)malloc( (local_size+1)*sizeof(char));
			
			int fd1 = open( file_name, O_CREAT|O_RDWR , 0644);                  // write info about tar file i.e. <filename>
			// FILE* fptr1 = fopen( args[3], "a");
			if( fd1 < 0 ){
				perror("Failed to complete extraction operation\n");
  		 	    exit (1);
			}
			buff[0] = '\0';
			read( fd2, buff, local_size);
			buff[local_size] = '\0';
			write( fd1, buff, local_size);
			close(fd1);
			
			free(buff);
			read( fd2, c, 1);
			read( fd2, c, 1);
		}
		close(fd2);
		closedir(dir);
		
	}

	if( strcmp( args[1], "-e") == 0 ){                           // Extraction of args[3] file from tar file located at args[2] /location/<tar_file_name>. 
		
		if( arg != 4 ){
			perror("Failed to complete extraction operation\n");
			exit(1);
		}
		
		printf("check3\n");
		// Printing

		char* temp = strtok( args[2], "/");
		char* address = (char *)malloc(50*sizeof(char));
		address[0] = '/';
		address[1] = '\0';
		// printf("%s", address);
		
		char* filename;
		while( temp != NULL ){
			strcat( address, temp);
			// printf("%s", address);
			strcat( address, "/");
			filename = temp;
			temp = strtok( NULL, "/");
		}
		int t = strlen(filename);
		address[strlen(address)-t-2] = '\0';
		// printf("%s %s", address, filename);
		
		int k = 0;
		k = chdir( address);                                                // k = 0 on success and -1 in case of error.
		if( k < 0 ){
			perror("Failed to complete extraction operation\n");
			exit(1);
		}
		DIR *dir;
		if ((dir = opendir (".")) == NULL) {
    	    perror("Failed to complete extraction operation\n");
    	    exit (1);
    	}

		// filename = tar file name.
		int fd2 = open( filename, O_RDONLY);
		char c[1], file_name[17], file_size[16];
		read( fd2, c, 1);
		int i = 0;
		while( c[0] != ' ' && c[0] != '\n' ){
			i = 0;
			while( c[0] != ' ' ){
				file_name[i++] = c[0];
				read( fd2, c, 1);
			}
			file_name[i] = '\0';
			i = 0;
			read( fd2, c, 1);
			while( c[0] != '\n' ){
				file_size[i++] = c[0];
				read( fd2, c, 1);
			}
			file_size[i] = '\0';
			int local_size = atoi( file_size);
			if( strcmp( args[3], file_name) == 0 ){
				char buff[local_size+1];
				k = mkdir( "IndividualDump", 0777);
				// write( 1, buff, local_size);
				
				if( k < 0 ){
					perror("Failed to complete extraction operation\n");
					exit(1);
				}
				// 	return 0;
				k = chdir( "IndividualDump");                                                // k = 0 on success and -1 in case of error.
				if( k < 0 ){
					perror("Failed to complete extraction operation\n");
					exit(1);
				}
				DIR* dir1;
				if ((dir1 = opendir (".")) == NULL) {
  			  	    perror("Failed to complete extraction operation\n");
  			  	    exit (1);
	  		  	}
				// return 0;
				int fd1 = open( args[3], O_CREAT|O_RDWR , 0644);                  // write info about tar file i.e. <filename>
				// FILE* fptr1 = fopen( args[3], "a");
				if( fd1 < 0 ){
					perror("Failed to complete extraction operation\n");
  			  	    exit (1);
				}
				
				read( fd2, buff, local_size);
				write( fd1, buff, local_size);
				close(fd1);
				closedir(dir1);
				exit(1);
			} 
			lseek( fd2, local_size, SEEK_CUR);
			read( fd2, c, 1);
			read( fd2, c, 1);
		}
		close(fd2);
		closedir(dir);
		printf("No such file is present in tar file.\n");

	}

	if( strcmp( args[1], "-l") == 0 ){                                      // listing all files of tar file. 
	
		printf("check4\n");

		if( arg != 3 ){
			perror("Failed to complete list operation");
			exit(1);
		}

		char* temp = strtok( args[2], "/");
		char* address = (char *)malloc(50*sizeof(char));
		address[0] = '/';
		address[1] = '\0';
		
		char* filename;
		while( temp != NULL ){
			strcat( address, temp);
			strcat( address, "/");
			filename = temp;
			temp = strtok( NULL, "/");
		}
		int t = strlen(filename);
		address[strlen(address)-t-2] = '\0';

		int k = 0;
		k = chdir( address);                                                         // k = 0 on success and -1 in case of error.
		if( k < 0 ){
			k = write( 2, "Failed to complete list operation\n", 35);
		}
		DIR *dir;
		if ((dir = opendir (".")) == NULL) {
    	    perror("Failed to complete list operation");
    	    exit (1);
    	}
		
		int fd1 = open( "tarStructure", O_CREAT|O_RDWR , 0644);                        // write info about tar file i.e. <filename>
		int fd2 = open( filename, O_RDONLY);

		struct stat record;
    	fstat( fd2, &record);
    	long int size = record.st_size;
		char len[16];
		sprintf( len, "%ld", size);
		write( fd1, len, strlen(len));
		write( fd1, "\n", 1);

		char** matrix = (char **)malloc( 1000*sizeof(char *));
		for( int j = 0 ; j < 1000 ; j++ ){
			matrix[j] = (char *)malloc( 36*sizeof(char));
		}
		int i = 0, j = 0;                                                             // j row and i column
		char c[1], file_size[16];
		read( fd2, c, 1);
		while( c[0] != ' ' && c[0] != '\n' ){
			i = 0;
			int k = 0;
			int flag = 0;
			while( c[0] != '\n' ){
				matrix[j][i++] = c[0];
				if( flag ) file_size[k++] = c[0];
				if( c[0] == ' ' ) flag = 1;
				read( fd2, c, 1);
			}
			matrix[j][i++] = '\n';
			matrix[j][i] = '\0';
			file_size[k] = '\0';
			long local_size = atoi(file_size);

			lseek( fd2, local_size, SEEK_CUR);

			read( fd2, c, 1);
			read( fd2, c, 1);
			j++;
		}
		len[0] = '\0';
		sprintf( len, "%d", j);
		write( fd1, len, strlen(len));
		write( fd1, "\n", 1);
		for( int p = 0 ; p < j ; p++ ){
			write( fd1, matrix[p], strlen(matrix[p]));
		}
		close(fd1);
		close(fd2);
		closedir(dir);
	}

	return 0;
}
