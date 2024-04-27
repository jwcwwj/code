#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//插入排序	参数：数组	数组元素个数	假设是升序的
void insertSort(int* arr, int n) 
{
	//从第二个元素开始向后遍历待排序数组
	for (int i = 1; i < n; i++) {	
		//取出当前要插入的元素，避免被覆盖
		int data = arr[i];	 
		int j = i;
		//比较并移动
		//j > 0避免的是要插入的元素比已经排好序的数组中的最小的元素还小，避免下标越界
		while (j > 0 && arr[j - 1] > data) 
		{
			//arr[j - 1]是排好序的最后一个元素
			arr[j] = arr[j - 1];
			j--;
		}
		//将元素插入到正确位置
		arr[j] = data;
	}
}

//希尔排序	参数：数组	数组元素个数	假设是升序的
void shellSort(int* arr, int n)
{
	for (int gap = n / 2; gap > 0; gap /= 2) { // 先按照跨度 gap 进行分组
		for (int i = gap; i < n; i++) {       // 对每个子序列进行插入排序
			int data = arr[i];
			int j = i;
			while (j >= gap && arr[j - gap] > data) {
				arr[j] = arr[j - gap];
				j -= gap;
			}
			arr[j] = data;
		}
	}
}

//冒泡排序
void bubblesort(int* arr, int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

//优化后的冒泡排序	标记位

//快速排序 排序之后是增序序列
//获取基准值：三数取中法：起始  中间  结束
//没有优化时：数据有序时或者逆序时时间复杂度是O(n^2)，栈溢出会崩掉。	因为栈的调用层数是n	数据的个数
//优化后：比较均衡	时间复杂度是O(nlogn)	栈的调用层数是logn	会把最坏的情况下（数据有序或者数据逆序）变为最好的
int getMid(int* arr, int begin, int end)
{
	int mid = begin + (end - begin) / 2;
	if (arr[begin] > arr[mid])
	{
		if (arr[mid] > arr[end])
			return mid;		//begin mid end
		else if (arr[begin] > arr[end])
			return end;		//begin end mid
		else
			return begin;	//end begin mid
	}
	else
	{
		if (arr[begin] > arr[end])
			return begin;	//mid begin end
		else if (arr[mid] > arr[end])
			return end;		//mid end begin
		else
			return mid;		//end mid begin
	}
}

//方法1：hoare方法
//返回划分之后，基准值交换之后所在的位置
int partion(int* arr, int begin, int end)
{
	//获取基准值的位置
	int mid = getMid(arr, begin, end);
	//交换arr[mid]和arr[begin]
	int temp = arr[begin];
	arr[begin] = arr[mid];
	arr[mid] = temp;
	//选择基准值
	int key = arr[begin];
	int start = begin;
	while (begin < end)
	{
		//从后向前找小于基准值的位置
		while (begin < end && arr[end] >= key)
			--end;
		//从前向后找大于基准值的位置
		while (begin < end && arr[begin] <= key)
			++begin;
		//交换
		int temp = arr[begin];
		arr[begin] = arr[end];
		arr[end] = temp;
	}
	//交换基准值和相遇位置的数据
	temp = arr[begin];
	arr[begin] = arr[start];
	arr[start] = temp;
	return begin;	//基准值交换之后的位置
}

//方法2：挖坑法	
//返回基准值
int	partion2(int* arr, int begin, int end)
{
	//获取基准值的位置
	int mid = getMid(arr, begin, end);
	//交换arr[begin]和arr[mid]
	int temp = arr[begin];
	arr[begin] = arr[mid];
	arr[mid] = temp;
	//记录基准值
	int key = arr[begin];
	while (begin < end)
	{
		//从后向前找一个小于基准值的值
		while (begin < end && arr[end] >= key)
			--end;
		//填坑
		arr[begin] = arr[end];
		//从前向后找一个大于基准值的位置
		while (begin < end && arr[begin] <= key)
			++begin;
		//填坑
		arr[end] = arr[begin];
	}
	arr[begin] = key;	//begin和end相等的时候结束循环
	return begin;
}

//方法3:前后指针法
int partion3(int* arr, int begin, int end)
{
	int mid = getMid(arr, begin, end);
	int temp = arr[begin];
	arr[begin] = arr[mid];
	arr[mid] = temp;
	//第一个小于基准值的位置
	int prev = begin;
	//第二个小于基准值的位置
	int cur = begin + 1;
	int key = arr[begin];
	while (cur <= end)
	{
		//当cur走到小于基准值的位置，判断prev和cur是否连续
		if (arr[cur] < key && ++prev != cur)
		{
			//不连续	交换arr[prev]和arr[cur]
			int temp = arr[prev];
			arr[prev] = arr[cur];
			arr[cur] = temp;
		}
		++cur;
	}
	//交换基准值arr[begin]和arr[prev]
	temp = arr[begin];
	arr[begin] = arr[prev];
	arr[prev] = temp;
	return prev;
}

void quickSort(int* arr, int begin, int end)
{
	if (begin >= end)	//要么之后一个数据，要么越界了（排序结束）
		return;
	//小区间优化：在区间元素小于10的时候使用插入排序
	if (end - begin < 10)
		insertSort(arr + begin, end - begin + 1);	//区间的起始位置，区间的元素个数
	else
	{
		//一次划分之后	基准值的位置
		int div = partion3(arr, begin, end);
		//左右两部分的快速排序
		quickSort(arr, begin, div - 1);
		quickSort(arr, div + 1, end);
	}
} 

/*
//快速排序非递归实现
void quicksortNor(int* arr, int n)
{
	//创建一个顺序表，保存待划分的区间
	seqList sq;
	initList(&sq);
	//保存待划分的区间的范围
	//右
	pushBackSeqList(&sq, n - 1);
	//左
	pushBackSeqList(&sq, 0);
	//遍历顺序表，处理所有的区间
	while (!emptySeqList(&sq))
	{
		//取出左右区间
		int left = backSeqList(&sq);
		popBackSeqList(&sq);
		int right = backSeqList(&sq);
		popBackSeqList(&sq);

		//划分区间
		int div = partion(arr, left, right);
		//[left,div - 1]
		if (left < div - 1)		//至少有两个元素
		{
			pushBackSeqList(&sq, div - 1);
			pushBackSeqList(&sq, left);
		}
		//[div + 1,right]
		if (div + 1 < right)		//至少有两个元素
		{
			pushBackSeqList(&sq, right);
			pushBackSeqList(&sq, div + 1);
		}
	}
}
*/

//归并排序
//递归
void merge(int* arr, int begin, int mid, int end, int* tmp)
{
	int begin1 = begin;
	int end1 = mid;
	int begin2 = mid + 1;
	int end2 = end;
	//辅助空间的起始位置
	int idx = begin;
	//合并有序序列
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (arr[begin1] <= arr[begin2])
			tmp[idx++] = arr[begin1++];
		else
			tmp[idx++] = arr[begin2++];
	}
	//判断是否有剩余的元素没有合并
	if (begin1 <= end1)
		memcpy(tmp + idx, arr + begin1, sizeof(int) * (end1 - begin1 + 1));
	if (begin2 <= end2)
		memcpy(tmp + idx, arr + begin2, sizeof(int) * (end2 - begin2 + 1));
	//合并之后的序列拷贝到原始数组 对应区间
	memcpy(arr + begin, tmp + begin, sizeof(int) * (end - begin + 1));
}

void _mergeSort(int* arr, int begin, int end, int* tmp)
{
	if (begin >= end)
		return;
	//中间位置
	int mid = begin + (end - begin) / 2;
	_mergeSort(arr, begin, mid, tmp);
	_mergeSort(arr, mid + 1, end, tmp);
	//合并两个有序的子序列[begin,mid][mid + 1,end]
	merge(arr, begin, mid, end, tmp);
}

void mergeSort(int* arr, int n)
{
	//申请辅助空间
	int* tmp = (int*)malloc(sizeof(int) * n);
	_mergeSort(arr, 0, n - 1, tmp);
	free(tmp);	
}

//非递归的归并排序
void mergeSortNor(int* arr, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	int step = 1;	//子序列的步长
	while (step < n)
	{
		for (int idx = 0; idx < n; idx += 2 * step)
		{
			//找到两个待合并的子序列区间[begin,mid][mid + 1,end]
			int begin = idx;
			int mid = idx + step - 1;
			//判断是否存在第二个子序列
			if (mid >= n - 1)
				continue;		//不存在第二个子序列直接跳过
			int end = idx + 2 * step - 1;
			//判断第二个子序列是否越界
			if (end >= n)
				end = n - 1;
			merge(arr, begin, mid, end, tmp);
		}
		//更新步长
		step *= 2;
	}
}

//时间复杂度：n和最大值和最小值差值的最大值		空间复杂度：最大值和最小值差值		缺点：可能需要很大的空间，造成浪费
//计数排序
void  countSort(int* arr, int n)
{
	//找到最大值和最小值
	int max, min;
	min = max = arr[0];
	for (int i = 1; i < n; ++i)
	{
		if (arr[i] > max)
			max = arr[i];
		if (arr[i] < min)
			min = arr[i];
	}
	//计算范围
	int range = max - min + 1;
	//创建一个计数数组，初始化为
	int* countArr = (int*)calloc(range, sizeof(int));
	//计数
	for (int i = 0; i < n; ++i)
	{
		countArr[arr[i] - min]++;
	}
	//遍历计数数组，排序
	int idx = 0;
	for (int i = 0; i < range; ++i)
	{
		while (countArr[i]--)
		{
			arr[idx++] = min + i;
		}
	}
}

void test1() 
{
	//插入排序
	int arr[10] = { 5,8,9,4,3,6,7,10,2,1 };
	int n = sizeof(arr) / sizeof(arr[0]);
	insertSort(arr, n);
	printf("排序后的数组：\n");
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);	//1 2 3 4 5 6 7 8 9 10
}

void test2()
{
	//希尔排序
	int arr[10] = { 5,8,9,4,3,6,7,10,2,1 };
	int n = sizeof(arr) / sizeof(arr[0]);
	shellSort(arr, n);
	printf("排序后的数组：\n");
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);	//1 2 3 4 5 6 7 8 9 10
}

void test3()
{
	//快速排序
	int arr[10] = { 5,8,9,4,3,6,7,10,2,1 };
	int n = sizeof(arr) / sizeof(arr[0]);
	quickSort(arr, 0, n - 1);
	printf("排序后的数组：\n");
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);	//1 2 3 4 5 6 7 8 9 10
}

void test4()
{
	//归并排序
	int arr[10] = { 5,8,9,4,3,6,7,10,2,1 };
	int n = sizeof(arr) / sizeof(arr[0]);
	//mergeSort(arr, n);
	mergeSortNor(arr, n);
	printf("排序后的数组：\n");
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);	//1 2 3 4 5 6 7 8 9 10
}

void test5()
{
	//计数排序
	int arr[10] = { 5,8,9,4,3,6,7,10,2,1 };
	int n = sizeof(arr) / sizeof(arr[0]); 
	countSort(arr, n);
	printf("排序后的数组：\n");
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);	//1 2 3 4 5 6 7 8 9 10
}

//测试排序算法的性能
void test()
{
	int n;
	printf("数据量:\n");
	scanf_s("%d", &n);
	srand((unsigned)time(NULL));	//随机数种子
	int* arr = (int*)malloc(sizeof(int) * n);
	int* copy1 = (int*)malloc(sizeof(int) * n);
	int* copy2 = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand();
	}
	memcpy(copy1, arr, sizeof(int) * n);
	memcpy(copy2, arr, sizeof(int) * n);
	time_t begin = clock();	//时钟起始时间
	insertSort(copy1, n);
	time_t end = clock();	//时钟结束时间
	printf("直接插入排序时间：%d\n", end - begin);
	begin = clock();	 
	shellSort(copy2, n);
	end = clock();
	printf("希尔排序时间：%d\n", end - begin);
	for (int i = 0; i < n; i++)
	{
		printf("%d\n", copy1[i]);
	}
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		printf("%d\n", copy2[i]);
	}
}

int main()
{
	test5();
	return 0;
}