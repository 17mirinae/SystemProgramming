#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

void LineParsing(char *pBuffer)
{
	printf("called = %s\n", pBuffer);
}


int main() {

	int rfd, wfd, nReadSize, i = 0, j = 0, h = 0, cnt = 0;

	int sum = 0;

	float ave = 0.0;

	char buf[100];
	char temp[1024];

	char name[100];
	char numSum[100];
	
	char str[100], bstr[100];

	rfd = open("./Data_Homework_2.txt", O_RDONLY);

	if(rfd == -1){
		perror("Open Data_Homework_2.txt");
		exit(1);
	}

	wfd = open("./Data_Homework_2_result.txt", O_RDWR|O_CREAT);

	if(wfd == -1) {
		perror("Open Data_Homework_2_result.txt");
		exit(1);
	}

	for(i = 0;i < strlen(temp);i++) {
		name[i] = 0;
		numSum[i] = 0;
		temp[i] = 0;
	} // clear name

	while(1) {
		nReadSize = read(rfd, buf, 1);
		if(nReadSize == -1 || nReadSize == 0)
		{	// end of file
			break;
		}

		if(buf[0] == '\r' || buf[0] == '\n') // line end
		{

			temp[i] = 0;

			// call line parsing function
			LineParsing(temp);

			// separate line by tab
			for(j = 0;j < i + 1;j++) {
				if((temp[j] >= 'a' && temp[j] <= 'z') || (temp[j] >= 'A' && temp[j] <= 'Z')) {
					name[j] = temp[j];
				}
				else if(temp[j] != '\t') {
					numSum[h] = temp[j];
					h++;
				}
				else if(temp[j] == '\t' || temp[j] == '\0') {
					sum += atoi(numSum);
					h = 0;
					cnt++;
				}
			}

			sum += atoi(numSum);
			ave += (float)sum / (float)cnt;

			printf("name = %s\n", name);

			printf("sum = %d\n", sum);
			
			printf("ave = %.2f\n", ave);

			strcpy(bstr, "name = ");
			strcat(bstr, name);
			strcat(bstr, "\r\n");
			
			strcat(bstr, "sum = ");
			sprintf(str, "%d", sum);
			strcat(bstr, str);
			strcat(bstr, "\r\n");

			strcat(bstr, "ave = ");
			sprintf(str, "%.2f", ave);
			strcat(bstr, str);
			strcat(bstr, "\r\n\n");

			write(wfd, bstr, strlen(bstr));

			// clear temp
			for(j=0; j<i; j++) {
				temp[j] = 0;
				name[j] = 0;
				numSum[j] = 0;
				str[j] = 0;
				bstr[j] = 0;
			}

			sum = 0;
			ave = 0.0;
			cnt = 0;
			i = 0;
			h = 0;
		}
		else
		{
			temp[i] = buf[0];
			i++;
		}
	}

	close(rfd);
	close(wfd);

	return 0;
}
