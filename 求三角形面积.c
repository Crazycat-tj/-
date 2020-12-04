/*一个三角形的三边长分别是 a、b、c，那么它的面积为sqrt(p(p-a)(p-b)(p-c))
 ，其中 p=(a+b+c)/2
输入这三个数字，计算三角形的面积，四舍五入精确到 1 位小数。
保证能构成三角形，0≤a,b,c≤1000，每个边长输入时不超过2位小数。*/

#include <stdio.h>
#include <math.h>
 
int main()
{
	double a,b,c,p,S;
	scanf("%lf %lf %lf",&a,&b,&c);
	p = (a + b + c)/2;
	S = sqrt(p*(p-a)*(p-b)*(p-c));
	printf("%.1lf",S);
 } 
 
