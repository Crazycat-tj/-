#include <stdio.h>
#define MAXLINE 100
int getline(char* line, int lim);
void copy(char* from, char* to);
/*print the longest input line*/
int main() {
	int max = 0,len;
	char longest[MAXLINE];//存放最长的那一行文本
	char line[MAXLINE];//用于读取文本

	while ((len=getline(line,MAXLINE))>0)
	{
		if (len > max) {
			max = len;
			copy(line,longest);
		}
	}
	if (max > 0)
		printf("%s", longest);
	return 0;
}
/*用于读取行，返回每一行的长度*/
int getline(char* line, int lim) {
	int c,i = 0;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n';i++) {
		line[i] = c;
	}
	if (c == '\n') {
		line[i] = c;
		++i;
	}
	line[i] = '\0';
	return i;
}

void copy(char* from, char* to) {
	int i=0;
	while ((to[i]=from[i]) != '\0') {
		i++;
	}
}



