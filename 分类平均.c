//给定 n(n\le10000)n(n≤10000) 和 k(k\le 100)k(k≤100)，将从 1 到 nn 之间的所有正整数可以分为两类：
//A 类数可以被 kk 整除（也就是说是 kk 的倍数），而 B 类数不能。请输出这两类数的平均数，精确到小数点后 1 位，用空格隔开。

//数据保证两类数的个数都不会是 0。

#include <stdio.h>

int main()
{
	int n,k,i,count;
	double sum1,sum2;
	
	count = 0;
	scanf("%d %d",&n,&k);
	for(i=1;i<=n;i++){
		if(i%k==0){
			count++;
			sum1+=i;
		}else{
			sum2+=i;
		}
	}
	printf("%.1lf %.1lf",sum1/count,sum2/(n-count));
	
 } 
