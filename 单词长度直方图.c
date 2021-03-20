/*问题描述：打印输入中单词长度的直方图，要求垂直方向绘制*/
#include <stdio.h>

void prints(int* ndight);
int iskong(int* ndight);
int main() {
	int c, i, j = 0;
	int ndight[21];
	int length = 0;

	for (i = 0; i < 21; ++i) {
		ndight[i] = 0;
	}
	while ((c = getchar()) != EOF) {
		if (c == '\n' || c == ' ' || c == '\t') {
			ndight[length]++;
			length = 0;
		}
		else {
			++length;
		}
	}
	for (i = 1; i < 21; i++) {
		printf("%d ", i);
	}
	printf("\n");
	while (iskong(ndight)) {
		prints(ndight);
		printf("\n");
	}
	return 0;
}
//判断数组是否为空
int iskong(int* ndight) {
	int i;
	for (i = 1; i < 21; i++) {
		if (ndight[i] > 0)
			return 1;
	}
	return 0;
}
//逐行打印
void prints(int* ndight) {
	int i;
	for (i = 1; i < 21; i++) {
		if (ndight[i] > 0) {
			printf("* ");
			ndight[i]--;
		}
		else {
			printf("  ");
		}
	}
}
