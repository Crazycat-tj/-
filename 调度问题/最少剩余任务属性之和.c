#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TNumber 1000
#define MNumber 100
#define N 100
struct task{
    int m = 0; //不能分发到指定机器的序号(若为0则任意)
    int w; //任务的特定属性(用于负载能力判定与处理机返回)
    int type; //type为1指定机器不能放，type为2必须共同运行，type为3必须分开运行，type为4表示特殊任务
    int isScheduled = 0; //记录是否已经被调度
}T[TNumber];
struct machine{
    int c = 12; //机器剩余负载能力（用于w区间检测）
    int y = 5; //剩余可以容纳特殊任务的容量（初始为阈值）
    int num; //记录机器编号，用于判断任务能否分发到指定机器
    int identity[N] = {0}; //存储放入机器的任务序号
    int store[N] = {0};
    int isCrash = 0;
}M[MNumber];
int Sum = 0,Num = 0;

void init();
void sortTask(int start,int end);
void sortMachine(int start,int end);
void scheduling(int turn);
void putinto(int task,int machine,int turn);
int  check(int m,int j);
int check2(int task1,int task2,int machine);
void print();
void find(int task,int machine,int turn);
void clear();
void prLeft(int turn);
int probablity(int machine,int task);
int isdown(int p);
void out();

int main() {
    init();
    sortTask(0,TNumber-1); //对任务排序
    print();
    int isContinue = 1,turn = 1,i;
    while(isContinue){
        for(i = 0;i<TNumber;i++){
            if(T[i].isScheduled==0)//检测是否还有任务未被调度
                break;
        }
        if(i==TNumber)
            break;

        scheduling(turn);
        clear();
        turn++;
    }
    printf("****************************************\n");
    printf("总共 %d 次调度，历次调度剩余任务数量总和为 %d , 剩余任务的总w属性之和为 %d \n",turn-1,Num,Sum);

    return 0;
}

//初始化任务和机器
void init(){
    srand(time(NULL));
    int select;
    for(int i = 0;i < TNumber;i++){
        select = rand()%5 + 1;//随机数决定任务类型
        if(select == 1)
            T[i].type = 2;
        else if(select == 2)
            T[i].type = 3;
        else if(select == 3) {
            T[i].m = (rand() % 100) + 1;
            T[i].type = 1;
        }
        else if(select == 4)
            T[i].type = 4;
        else
            T[i].type = 5;
        T[i].w = rand()%5 + 1;
    }
    for(int j = 0;j< MNumber;j++){
        M[j].num = j+1;
    }
}



//对任务的属性值从大到小排序
void sortTask(int start,int end){
    static task temp;
    if (start >= end)
        return;
    int mid = T[start].w; //基准点
    temp = T[start];
    int left = start, right = end;
    while (left < right) {
        if (T[right].w <= mid && left < right)
            right--;
        T[left] = T[right];
        if (T[left].w > mid && left < right)
            left++;
        T[right] = T[left];
    }
    T[left] = temp;

    sortTask(start, left - 1);
    sortTask(left + 1, end);
}

//对机器剩余处理能力从大到小排序
void sortMachine(int start,int end){
    struct machine temp;
    if (start >= end)
        return;
    int mid = M[start].c; //基准点
    temp = M[start];
    int left = start, right = end;
    while (left < right) {
        if (M[right].c <= mid && left < right)
            right--;
        M[left] = M[right];
        if(M[left].c > mid && left < right)
            left++;
        M[right] = M[left];
    }
    M[right] = temp;

    sortMachine(start, left - 1);
    sortMachine(left + 1, end);
}

//模拟每一轮调度，turn表示第几轮
void scheduling(int turn){
    printf("*******************************************************\n");
    for(int i = 0;i < TNumber;i++){
        sortMachine(0,MNumber-1); //对机器处理能力（剩余负载能力）从大到小排序
        for(int j = 0;j<MNumber;j++){
            if(check(i,j)==0)
                continue;
            else if(T[i].type==2){
                find(i,j,turn);
            }else
                putinto(i,j,turn);//当前任务不是type2但能放入，因此直接放入机器
        }
    }
    prLeft(turn);
    out();
}

//将task放到machine中(第turn轮)
void putinto(int task,int machine,int turn){
    int x = 0;
    int p = probablity(machine,task);
    if(isdown(p)) {
        M[machine].isCrash = 1;
    }
    while(M[machine].identity[x]!=0)x++;
    M[machine].identity[x] = T[task].type;
    M[machine].store[x] = T[task].w;
    M[machine].c-=T[task].w;
    T[task].isScheduled = 1;
    if(T[task].type==4)
        M[machine].y--;
    printf("第%d轮调度，将第%d号任务分发到%d号机器上\n",turn,task+1,M[machine].num);
}

//判断m号任务能否分发到第j号机器中(用于检测第1，3，4，5类）
int check(int m,int j){
    if(T[m].isScheduled==1)
        return 0;
    if(T[m].w>M[j].c)
        return 0;
    if(T[m].type==1&&T[m].m==M[j].num)
        return 0;
    if(T[m].type==4&&M[j].y==0)
        return 0;
    if(T[m].type==3){
        int x = 0,isFind = 0;
        while(M[j].identity[x]!=0){
            if(M[j].identity[x]==3){
                isFind = 1;
                break;
            }
            x++;
        }
        if(isFind == 1)
            return 0;
    }
    return 1;
}

//判断task1和task2（均为type2）能否一起放到machine中
int check2(int task1,int task2,int machine){
    if(T[task1].isScheduled==1||T[task2].isScheduled==1)return 0;
    if(T[task1].w+T[task2].w>M[machine].c)return 0;
    return 1;
}

//打印初始化后的任务列表
void print(){
    printf("-----------------------------------------\n");
    for(int i = 0;i<TNumber;i++){
        printf("第%d号任务：type：%d, m:%d, w:%d\n",i+1,T[i].type,T[i].m,T[i].w);
    }
}

//寻找当前机器中有无type2类型的任务，若无则在当前任务位置向后寻找type2并判断能否一并放入，若无则跳过
void find(int task,int machine,int turn){
    int x = 0,isFind = 0,value = 0;
    while(M[machine].identity[x]!=0){
        if(M[machine].identity[x]==2){
            isFind = 1;
            break;
        }
        x++;
    }
    if(isFind == 1){//在当前机器中有同类任务
        putinto(task,machine,turn);//将任务分发到该机器中
        return;
    }else {
        for (int m = task + 1; m < TNumber; m++) { //从当前位置开始在任务队列中查找有无同类任务
            if (T[m].type == 2)//找到同类任务
                value = check2(task,m,machine);//检测其加上当前任务是否能被放入,若能放入返回1，否则返回0
            if (value == 1) {
                putinto(task,machine,turn);//将两个任务一起放入
                putinto(m,machine,turn);
                return;
            }
        }
    }
}

//每一轮调度后需要将machine中的任务清空，并将machine刷新
void clear(){
    for(int j = 0;j<MNumber;j++){
        for(int x = 0;x<N;x++){
            M[j].identity[x] = 0;
            M[j].store[x] = 0;
        }
        M[j].c = 12;
        M[j].y = 5;
        M[j].isCrash = 0;
    }
}

//打印第turn轮调度剩下的任务数量和w属性之和
void prLeft(int turn){
    int num = 0,sum = 0;
    for(int i = 0;i<TNumber;i++){
        if(T[i].isScheduled==0) {
            num++;
            Num++;
            sum+=T[i].w;
            Sum+=T[i].w;
        }
    }
    printf("****************************************\n");
    printf("第 %d 轮调度剩余任务数量 %d , 剩余任务的w属性之和为 %d \n",turn,num,sum);
}

//判断宕机概率。返回宕机的概率
int probablity(int machine,int task){
    int sum = 12 - M[machine].c+T[task].w;
    if(sum>=1&&sum<=5)
        return 1;
    else if(sum>=6&&sum<=10)
        return 2*sum-9;
    else if(sum==11)
        return 14;
    else if(sum==12)
        return 20;
    else
        return 100;
}

//根据概率判断当前任务放入机器是否会宕机
int isdown(int p){
    int x = rand()%100 + 1;
    if(x<p)
        return 1;
    else
        return 0;
}

//打印每次调度分发到机器中的任务w值列表，若宕机则返回0
void out(){
    for(int i = 0;i < MNumber;i++){
        if(M[i].isCrash==1)
            printf("第 %d 台机器：0\n",M[i].num);
        else {
            int x = 0;
            printf(" 第%d 台机器：[", M[i].num);
            while (M[i].store[x]!=0){
                printf(" %d,",M[i].store[x]);
                x++;
            }
            printf("]\n");
        }
    }
}
