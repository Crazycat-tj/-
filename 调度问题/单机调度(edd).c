//采用edd算法（earliest due date最早截止算法）可以实现在单机情况下，n项进程的最大延迟时间最短，这也是一种贪心思想
#include <stdio.h>

#define N 100
#define START 1

struct process{
    int number; //进程编号 j
    int pt; //任务 j 处理时间
    int dt; //任务 j 截止时间
}Process[N];

void edd(int num);
void quick_sort(int start, int end);
int sum(int num);
int delay(int num);
int maxDelay(int num);

int main() {
    int num;
    printf("欢迎来到单机调度服务平台......\n");
    printf("请输入进程数量:\n");
    scanf("%d",&num);
    edd(num);
    return 0;
}

void edd(int num){
    int i;
    for(i=1;i<=num;i++){
        Process[i].number = i;
        printf("请输入完成第 %d 号进程所需的工作时间(单位:s):\n",i);
        scanf("%d",&Process[i].pt);
        printf("请输入第 %d 号进程的截止时间(单位:s):\n",i);
        scanf("%d",&Process[i].dt);
    }
    quick_sort(START, num);
    printf("调度完成......\n");
    printf("预期进程排序:\n");
    for(i=1;i<=num;i++) {
        printf("%d.第 %d 号进程,需要处理的时间为 %d s,截止时间为第 %d s,完成时间为第 %d s,延迟时间为 %d s\n",
               i, Process[i].number, Process[i].pt, Process[i].dt, sum(i), delay(i));
    }
    printf("最大延时为： %d s\n",maxDelay(num));
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
    int mid = Process[start].dt; //基准点
    int left = start, right = end;
    while (left < right) {
        while (Process[right].dt > mid && left < right)
            right--;
        while (Process[left].dt <= mid && left < right)
            left++;
        if(left<right) {
            swap(&Process[left].pt, &Process[right].pt);
            swap(&Process[left].number, &Process[right].number);
            swap(&Process[left].dt, &Process[right].dt);
        }
    }
    swap(&Process[left].pt,&Process[start].pt);
    swap(&Process[left].number,&Process[start].number);
    swap(&Process[left].dt, &Process[start].dt);

    quick_sort(start, left - 1);
    quick_sort(left + 1, end);
}

//计算第num号进程完成时间
int sum(int num){
    int sum = 0;
    for(int i = 1;i <= num;i++){
        sum = sum + Process[i].pt;
    }
    return sum;
}

//计算第 j 号进程的延迟时间，若没有延迟返回 0
int delay(int j){
    if(sum(j)>Process[j].dt)
        return sum(j)-Process[j].dt;
    else
        return 0;
}

//计算n项进程中最大延迟时间
int maxDelay(int num){
    int mdelay = 0;
    for(int i = 1;i <= num;i++){
        if(delay(i)>mdelay)
            mdelay = delay(i);
    }
    return mdelay;
}
