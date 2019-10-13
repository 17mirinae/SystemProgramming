#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

//166p, Question 6
int main(int argc, char *argv[]) {
	DIR *dp; // open directory
	struct dirent *dent;
	int numOfFiles = 0;
	char dir[100];

	if((dp = opendir(argv[1])) == NULL) {
		printf("No Directory!\n\n");
		perror("opendir error");
		exit(1);
	}

	while((dent = readdir(dp))) {
		if(dent->d_name[0] == '.')
			continue;
		else {
			printf("Name : %s\n", dent->d_name);
			numOfFiles++;
		}
	}

	if(numOfFiles == 0) printf("Empty!\n\n");

	closedir(dp);

	return 0;
}
