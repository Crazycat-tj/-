//1|rj,pmtn|Lmax,抢占式单机调度，约束条件为进程到达时间，可以证明，edd算法仍适用于此题，不过需要在每次加入新的进程时重新对现有进程进行edd调度
#include <stdio.h>

#define N 100
#define START 1

struct process{
    int number; //进程编号 j
    int pt; //任务 j 处理时间
    int dt; //任务 j 截止时间
    int rt; //任务 j 到达时间
    int ret; //任务 j 剩余工作时间
    int lt; //任务 j 延迟时间
    int ct; //任务 j 完成时间
}Process[N],Arrange[N];

void edd(int num);
void quick_sort(int start, int end);
void maxDelay(int num);
void quick_sort_rj(int start, int end);

int main() {
    int num;
    printf("欢迎来到单机调度服务平台......\n");
    printf("请输入进程数量:\n");
    scanf("%d",&num);
    edd(num);
    return 0;
}

//抢占式edd调度
void edd(int num) {
    int i;
    for (i = 1; i <= num; i++) {
        Process[i].number = i; //编号
        printf("请输入完成第 %d 号进程所需的工作时间(单位:s):\n", i);
        scanf("%d", &Process[i].pt);
        Process[i].ret = Process[i].pt;
        printf("请输入第 %d 号进程的到达时间(单位:s):\n", i);
        scanf("%d", &Process[i].rt);
        printf("请输入第 %d 号进程的截止时间(单位:s):\n", i);
        scanf("%d", &Process[i].dt);
    }
    //复制进程队列，用来对到达时间排序
    for ( i = 1; i <= num; i++) {
        Arrange[i].number = Process[i].number;
        Arrange[i].rt = Process[i].rt;
        Arrange[i].dt = Process[i].dt;
        Arrange[i].pt = Process[i].pt;
        Arrange[i].ret = Process[i].ret;
    }
    quick_sort_rj(START, num); //按照到达时间排序
    
    printf("调度完成......\n");
    printf("预期进程方案如下:\n");
    //思路：按照到达时间遍历,模仿每个进程依次到达,每到达一个进程就将当前正在处理的进程挂起，对现有的进程队列进行一次edd调度
    for (int i = 1; i <= num; i++) {
        printf("----------------------------------------------\n");
        printf("当前为第 %d s, 第 %d 号进程到达,当前进程调度如下：\n", Arrange[i].rt, Arrange[i].number);
        //加入一个新的进程，然后将当前进程挂起，计算上一次调度的进程剩余工作时间，完成时间和延迟时间
        //注意：此时Possess数组仍是上一次调度的顺序
        if(i>1) {
            int time = Arrange[i].rt - Arrange[i - 1].rt;//距离上一次调度的间隔时间
            int ltime = Arrange[i-1].rt; //上一次调度的时刻 
            for (int j = 1; j < i; j++) {
                if (time >= Process[j].ret && Process[j].ret > 0) { //任务 j 执行完成
                    Process[j].ct = ltime + Process[j].ret; //进程 j 的完成时间
                    Process[j].lt = Process[j].ct-Process[j].dt; //进程 j 的延迟时间
                    time -= Process[j].ret;
                    Process[j].ret = 0;
                    ltime = Process[j].ct;
                } else if (time < Process[j].ret && time > 0) {
                    Process[j].ret-=time; 
                    time = 0;
                } else if (time <= 0)
                    break;
            }
        }
        
        quick_sort(START, i); //对当前进程队列执行edd,按照最早截止时间调度
        int x = 0;
        for (int j = 1; j <= i; j++) {
            if (Process[j].ret > 0) {
                x++;
                printf("%d. 第 %d 号进程\n", x, Process[j].number);
            }
        }
        
        printf("***当前已完成进程***\n");
        x = 0;
        for (int j = 1; j <= i; j++) {
            if (Process[j].ret == 0) {
                x++;
                printf("%d. 第 %d 号进程,完成时间为第 %d s,截止时间为 %d s,延迟时间为 %d s\n",
                       x, Process[j].number,Process[j].ct,Process[j].dt,Process[j].lt);
            }
        }
    }
    
    //最后一次调度完成后，让全部进程执行完毕
    int time = Arrange[num].rt;
    for(int j = 1;j <= num;j++){
        if(Process[j].ret > 0){
            Process[j].ct = time + Process[j].ret;
            Process[j].lt = Process[j].ct-Process[j].dt;
            Process[j].ret = 0;
            time = Process[j].ct;
        }
    }
    //结算所有进程的完成情况
    printf("----------------------------------------------\n");
    printf("全部进程工作结束状态总览：\n");
    int x = 0;
    for (int j = 1; j <= num; j++) {
        if (Process[j].ret == 0) {
            x++;
            printf("%d. 第 %d 号进程,完成时间为第 %d s,截止时间为 %d s,延迟时间为 %d s\n",
                   x, Process[j].number,Process[j].ct,Process[j].dt,Process[j].lt);
        }
    }
    printf("-------------------------------------\n");
    maxDelay(num); //计算最大延迟时间并打印
}

//交换数值
void swap(int *x,int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

// 快速排序,按照截止时间排序
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
            swap(&Process[left].dt, &Process[right].dt);
        }
    }
    swap(&Process[left].pt,&Process[start].pt);
    swap(&Process[left].number,&Process[start].number);
    swap(&Process[left].dt, &Process[start].dt);
    swap(&Process[left].rt,&Process[start].rt);

    quick_sort(start, left - 1);
    quick_sort(left + 1, end);
}

//计算num项进程中最大延迟时间
void maxDelay(int num){
    int mdelay = 0;
    for(int i = 1;i <= num;i++){
        if(Process[i].dt>mdelay)
            mdelay = Process[i].dt;
    }
    if(mdelay>0)
        printf("最大延迟时间：%d s",mdelay);
    else
        printf("没有延迟.......");
}


// 快速排序,按照到达时间排序
 void quick_sort_rj(int start, int end) {
    if (start >= end)
        return;
    int mid = Arrange[start].rt; //基准点
    int left = start, right = end;
    while (left < right) {
        while (Arrange[right].rt > mid && left < right)
            right--;
        while (Arrange[left].rt <= mid && left < right)
            left++;
        if(left<right) {
            swap(&Arrange[left].pt, &Arrange[right].pt);
            swap(&Arrange[left].number, &Arrange[right].number);
            swap(&Arrange[left].dt, &Arrange[right].dt);
            swap(&Arrange[left].rt,&Arrange[right].rt);
        }
    }
    swap(&Arrange[left].pt,&Arrange[start].pt);
    swap(&Arrange[left].number,&Arrange[start].number);
    swap(&Arrange[left].dt, &Arrange[start].dt);
    swap(&Arrange[left].rt,&Arrange[start].rt);

    quick_sort_rj(start, left - 1);
    quick_sort_rj(left + 1, end);
}
