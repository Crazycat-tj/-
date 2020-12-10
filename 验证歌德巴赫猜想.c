#include <stdio.h>
#include <math.h>

int isprime(int n){//函数用于判断是否为素数
	int i;
	for(i=2;i<sqrt((double)n);i++){//注意，sqrt函数里的数据类型应该为double（原型为double sqrt(double)，这里要强制类型转换（一般的编译器会自动优化，但码图上会出错）
		if(n%i==0){
			return 0;
		}
	}
	return 1;
}


int main(void){
	int x;
	scanf("%d",&x);//输入一个大于4小于2000的正偶数
	int i;
	
	if(x>=4&&x<=2000&&x%2==0){
	for(i=2;i<=x/2;i++){
		if(isprime(i)&&isprime(x-i)){//判断i和x-i是不是质数
			printf("%d %d",i,x-i);
			break;
		}
	}}else{
		printf("error");//如果输入错误的数据就输出error
	}
	
	return 0;
}
