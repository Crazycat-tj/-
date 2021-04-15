#include <stdio.h>

int Greedy(int *a,int n,int m);
void sort(int *array,int num);
int findmin(int array[],int num);
void swap(int *num1,int*num2);

int main(){
    int n ,m;
    printf("请输入任务总数:\n");
    scanf("%d",&n);
    int a[n];
    for(int i = 0;i < n;i++){
        printf("请输入第%d号任务的工作时间:\n",i+1);
        scanf("%d",&a[i]);
    }
    printf("请输入机器数量:\n");
    scanf("%d",&m);
    int x = Greedy(a,n,m);
    printf("Cmax = %d\n",x);
}

//贪心算法，返回Cmax
int Greedy(int *a,int n,int m){
    int b[n],id[n];
    for(int i = 0;i < n;i++)
        b[i] = a[i];
    sort(a,n);
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            if(a[i] == b[j]){
                id[i] = j+1; //记录任务的标签
                break;
            }
        }
    }
    int machine[m]; //机器
    for(int i = 0;i < m;i++){
        machine[i] = 0;
    }
    if(n <= m){
        printf("为每一台作业分配一台机器\n");
        return a[0];
    }else{
        for(int i = 0;i<n;i++){
            int min = findmin(machine,m);
            machine[min] = machine[min] + a[i];
            printf("将第%d个作业分配到第%d号机器\n",id[i],min+1);
        }
        sort(machine,m);
        return machine[0];
    }
}
//冒泡排序，从大到小排序
void sort(int *array,int num){
       for(int i = 0;i < num ;i++){
           for(int j = 1;j < num - i ;j++){
               if(array[j]>array[j-1]) {
                   swap(&array[j],&array[j-1]);
               }
           }
       }
}
//交换值
void swap(int *num1,int*num2){
    int temp;
    temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}
//寻找数组中值最小的位置
int findmin(int array[],int num){
    int i,min = 10000,position = -1;
    for(i = 0;i < num;i++){
        if(array[i]<min) {
            position = i;
            min = array[i];
        }
    }
    return position;
}
