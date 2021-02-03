#include <iostream>
#include <algorithm>

using namespace std;

void QuickSort(int* arr, int p, int r)//p为数组首元素位置，r为数组末尾元素位置
{
	if (p < r) {
		int i = p, j = r + 1;
		int x = arr[p];//基准元素
		while (true) {
			while (arr[++i] < x && i < r);//从左往右找，找出第一个大于x的值
			while (arr[--j] > x);    //从右往左找，找出第一个小于x的值 
			if (i >= j)    //跳出while循环 
				break;
			swap(arr[i], arr[j]);    //当i寻到大于x的元素，j寻到小于x的元素时，进行交换 
		}
		arr[p] = arr[j];
		arr[j] = x;
		QuickSort(arr, p, i - 1);    //递归的对小于x的元素继续进行排序 
		QuickSort(arr, j + 1, r);    //递归的对大于x的元素继续进行排序 
	}
}

int main()
{
	int num[12] = { 19,35,23,87,45,23,56,78,10,45,26,64 };
	int n = 12;
	QuickSort(num, 0, n - 1);    //以数组的第一个元素作为基准元素 
	cout << "排序后的数组为：" << endl;
	for (int i = 0; i < n; i++)
		cout << num[i] << ' ';
	cout << endl;
	return 0;
}
