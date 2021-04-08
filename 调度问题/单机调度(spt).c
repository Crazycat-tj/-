#include <stdio.h>

#define N 100
#define START 1

struct process{
    int number; //进程编号 j
    int pt; //任务 j 处理时间
}Process[N];

void spt(int num);
void quick_sort(int start, int end);
int csum(int num);
int sum(int num);

int main() {
    int num;
    printf("欢迎来到单机调度服务平台......\n");
    printf("请输入进程数量:\n");
    scanf("%d",&num);
    spt(num);
    return 0;
}

void spt(int num){
    int i;
    for(i=1;i<=num;i++){
        Process[i].number = i;
        printf("请输入完成第 %d 号进程所需的工作时间(单位：s):\n",i);
        scanf("%d",&Process[i].pt);
    }
    quick_sort(START, num);
    printf("调度完成......\n");
    printf("预期进程排序:\n");
    for(i=1;i<=num;i++){
        printf("%d.第 %d 号进程，需要处理的时间为 %d s，完成时间为第 %d s\n",i,Process[i].number,Process[i].pt,sum(i));
    }
    printf("所有进程的完成时间之和为：%d s\n",csum(num));
}


//交换数值
void swap(int *x,int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

// 快速排序
void quick_sort(int start, int end) {
    if (start >= end)
        return;
    int mid = Process[start].pt; //基准点
    int left = start, right = end;
    while (left < right) {
        while (Process[right].pt > mid && left < right)
            right--;
        while (Process[left].pt <= mid && left < right)
            left++;
        if(left<right) {
            swap(&Process[left].pt, &Process[right].pt);
            swap(&Process[left].number, &Process[right].number);
        }
    }
    swap(&Process[left].pt,&Process[start].pt);
    swap(&Process[left].number,&Process[start].number);

    quick_sort(start, left - 1);
    quick_sort(left + 1, end);
}

//计算1-num号进程完成时间之和
int csum(int num){
    int csum = 0;
    for(int i = 1;i <= num;i++){
        csum += sum(i);
    }
    return csum;
}

//计算第num号进程完成时间
int sum(int num){
    int sum = 0;
    for(int i = 1;i <= num;i++){
        sum = sum + Process[i].pt;
    }
    return sum;
}
