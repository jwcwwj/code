#include <stdio.h>
#include <stdlib.h>

//堆
typedef int HDataType;

//假设小堆
//向下调整	参数：数组名	树节点的个数	位置
void shiftDown(int* arr, int n, int cur)
{
	//找到孩子的位置
	//左孩子
	int child = 2 * cur + 1;
	while (child < n)
	{
		//从左右孩子中找一个最小的
		if (child + 1 < n && arr[child + 1] < arr[child])
			++child;
		//和当前数据比较
		if (arr[child] < arr[cur])
		{
			//调整：孩子 < 当前
			int temp = arr[cur];
			arr[cur] = arr[child];
			arr[child] = temp;
			//更新位置	继续调整
			cur = child;
			child = 2 * cur + 1;
		}
		else
			//不调整 孩子 >= 当前
			break;
	}
}

//向上调整
void shiftUp(int* arr, int n, int cur)
{
	//和父节点进行比较
	int parent = (cur - 1) / 2;
	while (cur > 0)		//这里可以直接写cur（一会测试）
	{
		if (arr[cur] < arr[parent])
		{
			int temp = arr[cur];
			arr[cur] = arr[parent];
			arr[parent] = temp;
			//更新位置
			cur = parent;
			parent = (cur - 1) / 2;
		}
		else
			break;
	}
}

typedef struct heap
{
	HDataType* _data;
	int _size;
	int _capapcity;
}heap;

//堆的初始化
void initHeap(heap* hp)
{
	if (hp == NULL)
		return;
	//空堆
	hp->_data = NULL;
	hp->_capapcity = hp->_size = 0;
}

void checkCapacity(heap* hp)
{
	if (hp->_capapcity == hp->_size)
	{
		int newCapccity = (hp->_capapcity == 0 ? 1 : 2 * hp->_capapcity);
		hp->_data = (HDataType*)realloc(hp->_data, sizeof(HDataType) * newCapccity);
		hp->_capapcity = newCapccity;
	}
}

//堆的插入	时间复杂度：O(logn)	尾插是O(1)	调整是O(logn)
void pushHead(heap* hp, HDataType val)
{
	if (hp == NULL)
		return;
	//检查空间
	checkCapacity(hp);
	//尾插
	hp->_data[hp->_size++] = val;
	//向上调整
	shiftUp(hp->_data, hp->_size, hp->_size - 1);
}

//堆的删除	获取最值	时间复杂度：O(n) 尾删是O(1)	从上向下调整是O(logn)
void popHeap(heap* hp)
{
	if (hp->_size)
	{
		//交换
		int temp = hp->_data[0];
		hp->_data[0] = hp->_data[hp->_size - 1];
		hp->_data[hp->_size - 1] = temp;
		//尾删
		hp->_size--;
		//从堆顶位置向下调整
		shiftDown(hp->_data, hp->_size, 0);
	}
}

//获取堆顶元素
HDataType topHeap(heap* hp)
{
	return hp->_data[0];
}

//判空
int emptyHeap(heap* hp)
{
	if (hp == NULL || hp->_size == 0)
		return 1;
	return 0;
}

//获取最大K个元素
void printTopk(int* arr, int n, int k)
{
	heap hp;
	initHeap(&hp);
	for (int i = 0; i < n; ++i)
	{
		pushHead(&hp, arr[i]);
	}
	for (int i = 0; i < k; ++i)
	{
		printf("%d ", topHeap(&hp));
		popHeap(&hp);
	}
}


//堆排序
void sortHeap()
{
	int arr[] = { 10,8,5,1,2,9,6,4,3,7 };
	int n = sizeof(arr) / sizeof(arr[0]);
	//建堆
	for (int i = (n - 2) / 2; i >= 0; --i)
	{
		shiftDown(arr, n, i);
	}
	//堆排序
	int end = n - 1;
	while (end > 0)
	{
		int temp = arr[0];
		arr[0] = arr[end];
		arr[end] = temp;
		shiftDown(arr, end, 0);
		end--;
	}
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", arr[i]);
	}
}

int main()
{
	int arr[] = { 10,9,8,7,6,5,4,3,2,1 };
	//建堆	小堆
	int n = sizeof(arr) / sizeof(arr[0]);
	heap hp;
	initHeap(&hp);
	for (int i = 0; i < n; i++)
	{
		pushHead(&hp, arr[i]);
		for (int j = 0; j <= i; j++)
		{
			printf("%d ", hp._data[j]);
		}
		printf("\n");
	} 
	for (int i = 0; i < n; i++)
	{
		popHeap(&hp);
		for (int j = 0; j < n; j++)
		{
			printf("%d ", hp._data[j]);
		}
		printf("\n");
	}

	printTopk(arr, 10, 5);
	return 0;
}