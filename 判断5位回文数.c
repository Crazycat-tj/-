//*一个五位数，判断它是不是回文数，如：12321是回文数，个位和万位相同，十位和千位相同。
输入：一个整数
输出：是回文数输出："Yes"，否则输出："No"，如果输入的不是五位数，输出："error"
例如输入：12321 输出：Yes *//


#include <stdio.h>
 
int main(){
	int n,s,m=0;
	scanf("%d",&n);
	s=n;
	int count=0;
	
	while(s>0){
		m=m*10+s%10;
		count++;
		s=s/10;
	}
	if(count==5){
	if(m==n){
		printf("Yes");
	}else{
		printf("No");
	}}else{
		printf("error");
	}
	
	return 0;
}
