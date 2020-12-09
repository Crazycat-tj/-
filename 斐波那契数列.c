//有一对兔子，从出生后第3个月起每个月都生一对兔子。小兔子长到第三个月后每个月又生一对兔子。
假设所有的兔子都不死，问第n个月时有几对兔子。即求第n个Fibonacci数。
例如输入1，输出1；
输入2，输出1；
输入3，输出2；
输入4，输出3；

//数组
#include <stdio.h>
 
int main(){
	int i,n;
	int a[1000]={1,1};
	scanf("%d",&n);
	
	for(i=2;i<=n-1;i++){
		a[i]=a[i-1]+a[i-2];
	}
	printf("%d",a[i-1]);
	return 0;
}

//递归
int Fibon1(int n)
{
	if (n == 1 || n == 2)
	{
		return 1;
	}
	else
	{
		return Fibon1(n - 1) + Fibon1(n - 2);
	}
}
int main()
{
	int n = 0;
	int ret = 0;
	scanf("%d", &n);
	ret = Fibon1(n);
	printf("ret=%d", ret);
	return 0;
}

//非递归
int Fibno2(int n)
{
	int num1 = 1;
	int num2 = 1;
	int tmp = 0;
	int i = 0;
	if (n < 3)
	{
		return 1;
	}
	else
	{
		for (i = 0; i>n-3; i++)
		{
			tmp = num1 + num2;
			num1 = num2;
			num2 = tmp;
		}
		return tmp;
	}
}

//队列
public int Fibno4(int n)
{
	Queue<int> queue = new Queue<int>();
	queue.Enqueue(1);
	queue.Enqueue(1);
	for (int i = 0; i <= n - 2; i++)
	{
		queue.Enqueue(queue.AsQueryable().First() + queue.AsQueryable().Last());
		queue.Dequeue();
	}
	 return queue.Peek();
}
