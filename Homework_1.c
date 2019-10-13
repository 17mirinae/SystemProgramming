#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

	int rfd, sum = 0, nReadSize, i = 0, j;
	char buf[100];
	char temp[100];
	int  aaaa;

	rfd = open("./Data_Homework_1.txt", O_RDONLY); // open file

	if(rfd == -1) {
		perror("Open Data_Homework_1.txt");
		exit(1);
	}

	while(1)
	{
		nReadSize = read(rfd, buf, 1);

		if(nReadSize == -1 || nReadSize == 0)
		{	// file end
			temp[i] = 0;
			sum = sum + atoi(temp);

			break;
		}

		if(buf[0]=='\r' || buf[0]=='\n')
		{
			temp[i] = 0;
			sum = sum + atoi(temp);
			for(j=0;j<i;j++)
				temp[j] = 0;
			i=0;
		}
		else
		{
			temp[i] = buf[0];
			i++; 
		}
	}
	
	printf("sum = %d\n", sum);

	close(rfd);
	
	return 0;
}
