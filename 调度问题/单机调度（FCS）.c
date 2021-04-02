#include <stdio.h>
#define N 100
#define START 1
struct process{
    int number; //进程编号
    int ct; //完成进程所需时间
}Process[N];

void saf(int num);
void quick_sort_recursive(int start, int end);

int main() {
    int num;
    printf("欢迎来到单机调度服务平台......\n");
    printf("请输入进程数量:\n");
    scanf("%d",&num);
    saf(num);
    return 0;
}

void saf(int num){
    int i;
    for(i=1;i<=num;i++){
        Process[i].number = i;
        printf("请输入完成第 %d 号进程所需的工作时间:\n",i);
        scanf("%d",&Process[i].ct);
    }
    quick_sort_recursive(START, num);
    printf("调度完成......\n");
    printf("预期进程排序:\n");
    for(i=1;i<=num;i++){
        printf("%d.第 %d 号进程，完成所需时间 %d s\n",i,Process[i].number,Process[i].ct);
    }
}


//交换数值
void swap(int *x,int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void quick_sort_recursive(int start, int end) {
    if (start >= end)
        return;
    int mid = Process[end].ct; //基准点
    int left = start, right = end;
    while (left < right) {
        while (Process[left].ct < mid && left < right)
            left++;
        while (Process[right].ct >= mid && left < right)
            right--;
        swap(&Process[left].ct, &Process[right].ct);
    }
    if (Process[left].ct >= Process[end].ct)
        swap(&Process[left].ct, &Process[end].ct);
    else
        left++;
    if (left)
        quick_sort_recursive(start, left - 1);
    quick_sort_recursive(left + 1, end);
}
