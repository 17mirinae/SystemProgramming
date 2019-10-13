#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

//166p, Question 7
int removeFile(char *file) {
	int unlinkFile = unlink(file);
	if(unlinkFile != 0) {
		return 1;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	DIR *dp; // open directory
	FILE *fileIn;
	FILE *fileOut;
	int nread;
	int removed;
	struct dirent *dent;
	char *cwd;
	char buffer[1024];

	if(argc != 3) {
		printf("Not enough parameter\n\n");
		exit(1);
	}
	
	if((dp = opendir(argv[2])) == NULL) {
		cwd = getcwd(NULL, 1024);
		
		fileIn = fopen(argv[1], "rb");
		if(fileIn == NULL) {
			printf("%s not found\n\n", argv[1]);
			exit(1);
		}
		
		fileOut = fopen(argv[2], "wb");
		if(fileOut == NULL) {
			printf("%s not found\n\n", argv[2]);	
			exit(1);
		}
	
		while(nread = fread(buffer, 1, 1, fileIn) > 0) {
			if(fwrite(buffer, nread, 1, fileOut) < nread) {
				fclose(fileIn);
				fclose(fileOut);
			}
		}
	}
	else {	
		cwd = getcwd(NULL, 1024);
		
		fileIn = fopen(argv[1], "rb");
		if(fileIn == NULL) {
			printf("%s not found\n\n", argv[1]);
			exit(1);
		}
		
		chdir(argv[2]);
		
		fileOut = fopen(argv[1], "wb");
		if(fileOut == NULL) {
			printf("%s not found\n\n", argv[2]);	
			exit(1);
		}
	
		while(nread = fread(buffer, 1, 1, fileIn) > 0) {
			if(fwrite(buffer, nread, 1, fileOut) < nread) {
				fclose(fileIn);
				fclose(fileOut);
			}
		}
		chdir(cwd);
	}
	
	if(0 != removeFile(argv[1])) {
		printf("file %s delete failed\n\n", argv[1]);
	}

	return 0;
}
