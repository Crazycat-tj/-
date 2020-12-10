


#include <stdio.h>

int main(void){
	double a,b;
	char x,c;
	scanf("%lf %c %lf",&a,&c,&b);
	int isprime=1;

	
	while(isprime==1){
		if(c=='+'){
			printf("%.2f + %.2f = %.2f\n",a,b,a+b);
		}else if(c=='-'){
			printf("%.2f - %.2f = %.2f\n",a,b,a-b);
		}else if(c=='*'){
			printf("%.2f * %.2f = %.2f\n",a,b,a*b);
		}else if(c=='/'&&b!=0){
			printf("%.2f / %.2f = %.2f\n",a,b,a/b);
		}else{
			printf("error\n");
		}
		getchar();//getchar字符吃掉缓存区的\n字符
		scanf("%c",&x);
		if(x=='y'||x=='Y'){//键入y或Y来使程序继续。否则，退出程序
			getchar();
			scanf("%lf %c %lf",&a,&c,&b);//注意这里的数据类型要与上面一致，不然就出错了
		}else{
			isprime=0;
		}
	}
	return 0;
}

