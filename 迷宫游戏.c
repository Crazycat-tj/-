#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

int rank = 6;
//地图边长 L，包括迷宫主体 20，外侧的包围的墙体 2，最外侧包围路径 2
#define L 24
#define WALL 0 //墙
#define ROUTE 1 //路径
#define PLAYER 2 //玩家

void start();
int init(int** maze);
void print(int** maze);
void move(int** maze, char t, int& x, int& y);
void swap(int*x ,int*y);
void dig(int** maze,int x,int y);


int main() {
    char c;
    while (1) {
        system("cls");
        printf("---------------------\n");
        printf("---欢迎来到迷宫游戏---\n");
        printf("----1. 开始游戏 -----\n");
        printf("----0. 退出游戏 -----\n");
        printf("--------------------\n");
        c = _getch();
        switch (c) {
            case '1':
                start();
                break;
            case '0':
                printf("欢迎下次继续游玩........\n");
                Sleep(1500);
                exit(0);
            default:
                break;
        }
    }
    return 0;
}

//开始游戏
void start() {
    char t;
    //x，y是玩家的坐标，out是出口的纵坐标(行号)
    int i, x = 2, y = 1, out = 0;
    //初始化随机数种子，利用系统时间生成随机数,之后就可以使用rand函数生成随机数
    srand((unsigned)time(NULL));
    //初始化迷宫,且全部设置为墙
    int** maze = (int**)malloc(L * sizeof(int*));
    for (i = 0; i < L; i++) {
        maze[i] = (int*)calloc(L, sizeof(int));
    }
    //得到出口纵坐标
    out = init(maze);
    system("cls");
    print(maze);
    while (t = _getch()) {
        system("cls");
        move(maze, t, x, y);
        print(maze);
        if (x == out && y == L - 2) {
            system("cls");
            printf("恭喜你，到达了终点!\n");
            printf("即将返回主菜单\n");
            Sleep(1500);
            break;
        }
    }
    for (i = 0; i < L; i++)
        free(maze[i]);
    free(maze);
}


//初始化迷宫
int init(int** maze) {
    int i;
    //将最外层都设置为空的路径，防止挖穿
    for (i = 0; i < L; i++) {
        maze[i][0] = ROUTE;
        maze[0][i] = ROUTE;
        maze[i][L - 1] = ROUTE;
        maze[L - 1][i] = ROUTE;
    }
    dig(maze,2,2);
    maze[2][1] = PLAYER; //给玩家初始位置
    //寻找出口，出口可能不在[L-3][L-2]，因此需要查找
    for (i = L - 3; i >= 0; i--) {
        if (maze[i][L - 3] == ROUTE) {
            maze[i][L - 2] = ROUTE;
            return i; //出口返回纵坐标
        }
    }
}

//打印迷宫
void print(int** maze) {
    int i, j;
    for (i = 0; i < L; i++) {
        for (j = 0; j < L; j++) {
            if (maze[i][j] == ROUTE)
                printf("  ");
            else if (maze[i][j] == WALL)
                printf("墙");
            else if (maze[i][j] == PLAYER)
                printf("十");
        }
        printf("\n");
    }
}


//移动
void move(int** maze, char t, int& x, int& y) {
    int i, j;
    i = x;
    j = y;
    switch (t) {
        case 'w':
            x--;
            break;
        case 's':
            x++;
            break;
        case 'a':
            y--;
            break;
        case 'd':
            y++;
            break;
        default:
            break;
    }
    if (x >= 0 && x < L-1 && y >= 0 && y < L-1 && maze[x][y] != WALL) {
        maze[i][j] = ROUTE;
        maze[x][y] = PLAYER;
    }
    else {
        x = i;
        y = j;
    }
}

void dig(int** maze,int x,int y){
    if(maze[x][y]==WALL){
        if(maze[x-1][y]+maze[x+1][y]+maze[x][y+1]+maze[x][y-1]<=ROUTE){
            maze[x][y] = ROUTE;
            int i,direction[4] = {0,1,2,3};
            for(i=4;i>0;i--){
                int r = rand()%i;
                swap(&direction[r],&direction[i-1]);
                switch(direction[i-1]){
                    case 0:
                        dig(maze,x-1,y);
                        break;
                    case 1:
                        dig(maze,x+1,y);
                        break;
                    case 2:
                        dig(maze,x,y-1);
                        break;
                    case 3:
                        dig(maze,x,y+1);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void swap(int*x,int*y){
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
