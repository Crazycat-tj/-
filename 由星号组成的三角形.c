//*输出由*组成的三角形。
指定底边长度。第一排输出*，第二排输出***，每行中间需对齐，每行的最后一个*后输出回车。
输入边长(1-80中的奇数)，错误边长，输出error。
例如，
输入1，输出*回车
输入2，输出error
输入3，输出
 *
***回车*//

#include <stdio.h>
 
int main(){
	int n;
	scanf("%d",&n);
	
	if(n%2==1){
		int i,x,m;
		x=n/2;
		for(i=1;i<=n;i+=2){
			for(m=1;m<=x;m++){
				printf(" ");
			}
			x--;
			for(m=1;m<=i;m++){
				printf("*");
			}
			printf("\n");
		}
	}else{
		printf("error");
	}
	return 0;
}
