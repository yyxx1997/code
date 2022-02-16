//#include<stdio.h>
//#include"SqList.h"
//#include <time.h>
//#include <stdlib.h>
//
//void print(int a[], int start, int pos) {
//	for (int i = 0;i < pos;i++)printf("%d\t", a[start + i]);
//	printf("\n");
//}
//
//int BinarySearch(SqList L, int key) {
//	int low = 0, high = L.length - 1, mid;
//	while (low <= high) {
//		mid = (low + high) / 2;
//		if (L.data[mid] == key)return mid;
//		else if (L.data[mid]>key) {
//			high = mid - 1;
//		}
//		else {
//			low = mid + 1;
//		}
//	}
//	return -1;
//	/*SqList L;
//	Init_List_Sq(L);
//	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
//	int key = 0;
//	for (int i = 0;i < 10;i++)List_Insert_Sq(L, i + 1, arr[i]);
//	Print_List_Sq(L);
//	printf("%d", BinarySearch(L, key));*/
//}
//
//void InsertSort(int a[], int n) {
//	int i, j;
//	for (i = 2;i <= n;i++) {
//		if (a[i] < a[i - 1]) {
//			a[0] = a[i];
//			for (j = i - 1;a[j] > a[0];j--) {
//				a[j + 1] = a[j];
//			}
//			a[j + 1] = a[0];
//		}
//	}
//}
//
//void BinarySort(int a[], int n) {
//	int i, j, low, high, mid;
//	for (i = 2;i <= n;i++) {
//		a[0] = a[i];
//		low = 1;high = i - 1;
//		while (low <= high) {
//			mid = (low + high) / 2;
//			if (a[mid] > a[0])high = mid - 1;
//			else low = mid + 1;
//		}
//		for (j = i - 1;j >= low;j--)a[j + 1] = a[j];
//		a[low] = a[0];
//	}
//}
//
//
//void ShellSort(int a[], int n) {
//	int dk, i, j;
//	for (dk = n / 2;dk >= 1;dk /= 2) {
//		for (i = dk + 1;i <= n;i++) {
//			if (a[i] < a[i - dk]) {
//				a[0] = a[i];
//				for (j = i - dk;j > 0 && a[0] < a[j];j -= dk)a[j + dk] = a[j];
//				a[j + dk] = a[0];
//			}
//		}
//	}
//}
//
//void swap(int& a, int& b) {
//	int temp;
//	temp = a;
//	a = b;
//	b = temp;
//}
//
//void BubbleSort(int a[], int n) {
//	int i, j, flag;
//	for (i = 0;i < n - 1;i++) {
//		flag = false;
//		for (j = n;j > i + 1;j--)
//			if (a[j - 1] > a[j]) {
//				swap(a[j - 1], a[j]);
//				flag = true;
//			}
//		if (!flag)return;
//	}
//}
//
//int Partition(int a[], int low, int high) {
//	int pivot = a[low];
//	while (low < high) {
//		while (low < high && a[high] >= pivot)--high;
//		a[low] = a[high];
//		while (low < high && a[low] <= pivot)++low;
//		a[high] = a[low];
//	}
//	a[low] = pivot;
//	return low;
//}
//
//void QuickSort(int a[], int low, int high) {
//	if (low < high) {
//		int pivotpos = Partition(a, low, high);
//		QuickSort(a, low, pivotpos - 1);
//		QuickSort(a, pivotpos + 1, high);
//	}
//}
//
//void SimpleSelectSort(int a[], int n) {
//	int i, j, min;
//	for (i = 0;i < n - 1;i++) {
//		min = i;
//		for (j = i + 1;j < n;j++)
//			if (a[j] < a[min])min = j;
//		if (min != j)swap(a[i], a[min]);
//	}
//}
//
//void HeadAdjust(int a[], int k, int len) {
//	a[0] = a[k];
//	for (int i = 2 * k;i <= len;i *= 2) {
//		if (i < len && a[i] < a[i + 1])i++;
//		if (a[0] >= a[i])break;
//		else {
//			a[k] = a[i];
//			k = i;
//		}
//	}
//	a[k] = a[0];
//}
//
//void BuildMaxHeap(int a[], int len) {
//	for (int i = len / 2;i > 0;i--)
//		HeadAdjust(a, i, len);
//}
//
//void HeapSort(int a[], int len) {
//	BuildMaxHeap(a, len);
//	for (int i = len;i > 1;i--) {
//		swap(a[1], a[i]);
//		HeadAdjust(a, 1, i - 1);
//	}
//}
//
//void Merge(int a[], int b[], int low, int mid, int high) {
//	int i, j, k;
//	
//	for (k = low;k <= high;k++)b[k] = a[k];
//	for (i = low, j = mid + 1, k = i;i <= mid && j <= high;k++) {
//		if (b[i] <= b[j])a[k] = b[i++];
//		else a[k] = b[j++];
//	}
//	while (i <= mid)a[k++] = b[i++];
//	while (j <= high)a[k++] = b[j++];
//}
//
//void MergeSort(int a[], int b[], int low, int high) {
//	if (low < high) {
//		int mid = (low + high) / 2;
//		printf("%d-%d\n", low, mid);
//		MergeSort(a, b, low, mid);
//		printf("%d-%d\n", mid+1, high);
//		MergeSort(a, b, mid + 1, high);
//		printf("merge:%d-%d\n", low, high);
//		Merge(a, b, low, mid, high);
//		print(a, 0, 9);
//	}
//}
//
//void DoubleBubbleSort(int a[], int n) {
//	/*双向冒泡排序：
//		1.每一轮进行两个方向上的冒泡交换——正向冒泡+反向冒泡
//		2.设置flag参数，当某一轮无交换发生时，排序已完成，此时直接退出
//		3.i代表每次排序的起点，j代表排序的终点，每一轮运行都会有i++/j--;
//	*/
//	int i = 0, j = n - 1, k, flag = false;
//	while (i < j) {
//		print(a, 0, n);
//		k = i;
//		while (k < j) {
//			if (a[k + 1] < a[k]) { swap(a[k + 1], a[k]); flag = true; }
//			k++;
//		}
//		k--;
//		while (k > 0) {
//			if (a[k - 1] > a[k]) { swap(a[k - 1], a[k]);  flag = true;}
//			k--;
//		}
//		if (!flag)break;
//		j--;
//		i++;
//		flag = false;
//	}
//}
//
//void DivideOddEven(int a[], int n) {
//	/*把所有的奇数移动到偶数前面
//		顺序扫描线性表，每次检查一个元素：
//		1.若遍历到偶数：a.从后往前遍历寻找奇数；b.找到后与偶数交换；c.找不到则退出，说明所有的奇数都在前端
//		2.若遍历到奇数不执行操作，继续下一个
//		3.重复以上直至结束
//	*/
//	int i = 0, j = n - 1;
//	while (i < j) {
//		print(a, 0, n);
//		if (a[i] % 2 == 0) {
//			while (j > i) {
//				if (a[j] % 2 == 1) {
//					swap(a[i], a[j]);
//					break;
//				}
//				j--;
//			}
//		}
//		i++;
//	}
//}
//
////int main() {
////
////
////	int a[11], aa;
////	int i;
////
////	 按时间重新播种
////	srand((unsigned)time(NULL));
////
////	for (i = 0; i < 11; i++)
////	{
////		aa = rand() % 200 + 1;
////		a[i] = aa;
////	}
////
////	for (i = 0; i < 10; i++)
////	{
////		printf("%-5d", a[i]);
////	}
////	printf("\n");
////	int b[15];
////	MergeSort(a,b,0,9);
////
////	for (i = 0; i < 10; i++)
////	{
////		printf("%-5d", a[i]);
////	}
////}
