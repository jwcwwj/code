#include <stdio.h>
#include <stdlib.h>

//��
typedef int HDataType;

//����С��
//���µ���	������������	���ڵ�ĸ���	λ��
void shiftDown(int* arr, int n, int cur)
{
	//�ҵ����ӵ�λ��
	//����
	int child = 2 * cur + 1;
	while (child < n)
	{
		//�����Һ�������һ����С��
		if (child + 1 < n && arr[child + 1] < arr[child])
			++child;
		//�͵�ǰ���ݱȽ�
		if (arr[child] < arr[cur])
		{
			//���������� < ��ǰ
			int temp = arr[cur];
			arr[cur] = arr[child];
			arr[child] = temp;
			//����λ��	��������
			cur = child;
			child = 2 * cur + 1;
		}
		else
			//������ ���� >= ��ǰ
			break;
	}
}

//���ϵ���
void shiftUp(int* arr, int n, int cur)
{
	//�͸��ڵ���бȽ�
	int parent = (cur - 1) / 2;
	while (cur > 0)		//�������ֱ��дcur��һ����ԣ�
	{
		if (arr[cur] < arr[parent])
		{
			int temp = arr[cur];
			arr[cur] = arr[parent];
			arr[parent] = temp;
			//����λ��
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

//�ѵĳ�ʼ��
void initHeap(heap* hp)
{
	if (hp == NULL)
		return;
	//�ն�
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

//�ѵĲ���	ʱ�临�Ӷȣ�O(logn)	β����O(1)	������O(logn)
void pushHead(heap* hp, HDataType val)
{
	if (hp == NULL)
		return;
	//���ռ�
	checkCapacity(hp);
	//β��
	hp->_data[hp->_size++] = val;
	//���ϵ���
	shiftUp(hp->_data, hp->_size, hp->_size - 1);
}

//�ѵ�ɾ��	��ȡ��ֵ	ʱ�临�Ӷȣ�O(n) βɾ��O(1)	�������µ�����O(logn)
void popHeap(heap* hp)
{
	if (hp->_size)
	{
		//����
		int temp = hp->_data[0];
		hp->_data[0] = hp->_data[hp->_size - 1];
		hp->_data[hp->_size - 1] = temp;
		//βɾ
		hp->_size--;
		//�ӶѶ�λ�����µ���
		shiftDown(hp->_data, hp->_size, 0);
	}
}

//��ȡ�Ѷ�Ԫ��
HDataType topHeap(heap* hp)
{
	return hp->_data[0];
}

//�п�
int emptyHeap(heap* hp)
{
	if (hp == NULL || hp->_size == 0)
		return 1;
	return 0;
}

//��ȡ���K��Ԫ��
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


//������
void sortHeap()
{
	int arr[] = { 10,8,5,1,2,9,6,4,3,7 };
	int n = sizeof(arr) / sizeof(arr[0]);
	//����
	for (int i = (n - 2) / 2; i >= 0; --i)
	{
		shiftDown(arr, n, i);
	}
	//������
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
	//����	С��
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