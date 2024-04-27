#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//��������	����������	����Ԫ�ظ���	�����������
void insertSort(int* arr, int n) 
{
	//�ӵڶ���Ԫ�ؿ�ʼ����������������
	for (int i = 1; i < n; i++) {	
		//ȡ����ǰҪ�����Ԫ�أ����ⱻ����
		int data = arr[i];	 
		int j = i;
		//�Ƚϲ��ƶ�
		//j > 0�������Ҫ�����Ԫ�ر��Ѿ��ź���������е���С��Ԫ�ػ�С�������±�Խ��
		while (j > 0 && arr[j - 1] > data) 
		{
			//arr[j - 1]���ź�������һ��Ԫ��
			arr[j] = arr[j - 1];
			j--;
		}
		//��Ԫ�ز��뵽��ȷλ��
		arr[j] = data;
	}
}

//ϣ������	����������	����Ԫ�ظ���	�����������
void shellSort(int* arr, int n)
{
	for (int gap = n / 2; gap > 0; gap /= 2) { // �Ȱ��տ�� gap ���з���
		for (int i = gap; i < n; i++) {       // ��ÿ�������н��в�������
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

//ð������
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

//�Ż����ð������	���λ

//�������� ����֮������������
//��ȡ��׼ֵ������ȡ�з�����ʼ  �м�  ����
//û���Ż�ʱ����������ʱ��������ʱʱ�临�Ӷ���O(n^2)��ջ����������	��Ϊջ�ĵ��ò�����n	���ݵĸ���
//�Ż��󣺱ȽϾ���	ʱ�临�Ӷ���O(nlogn)	ջ�ĵ��ò�����logn	����������£�������������������򣩱�Ϊ��õ�
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

//����1��hoare����
//���ػ���֮�󣬻�׼ֵ����֮�����ڵ�λ��
int partion(int* arr, int begin, int end)
{
	//��ȡ��׼ֵ��λ��
	int mid = getMid(arr, begin, end);
	//����arr[mid]��arr[begin]
	int temp = arr[begin];
	arr[begin] = arr[mid];
	arr[mid] = temp;
	//ѡ���׼ֵ
	int key = arr[begin];
	int start = begin;
	while (begin < end)
	{
		//�Ӻ���ǰ��С�ڻ�׼ֵ��λ��
		while (begin < end && arr[end] >= key)
			--end;
		//��ǰ����Ҵ��ڻ�׼ֵ��λ��
		while (begin < end && arr[begin] <= key)
			++begin;
		//����
		int temp = arr[begin];
		arr[begin] = arr[end];
		arr[end] = temp;
	}
	//������׼ֵ������λ�õ�����
	temp = arr[begin];
	arr[begin] = arr[start];
	arr[start] = temp;
	return begin;	//��׼ֵ����֮���λ��
}

//����2���ڿӷ�	
//���ػ�׼ֵ
int	partion2(int* arr, int begin, int end)
{
	//��ȡ��׼ֵ��λ��
	int mid = getMid(arr, begin, end);
	//����arr[begin]��arr[mid]
	int temp = arr[begin];
	arr[begin] = arr[mid];
	arr[mid] = temp;
	//��¼��׼ֵ
	int key = arr[begin];
	while (begin < end)
	{
		//�Ӻ���ǰ��һ��С�ڻ�׼ֵ��ֵ
		while (begin < end && arr[end] >= key)
			--end;
		//���
		arr[begin] = arr[end];
		//��ǰ�����һ�����ڻ�׼ֵ��λ��
		while (begin < end && arr[begin] <= key)
			++begin;
		//���
		arr[end] = arr[begin];
	}
	arr[begin] = key;	//begin��end��ȵ�ʱ�����ѭ��
	return begin;
}

//����3:ǰ��ָ�뷨
int partion3(int* arr, int begin, int end)
{
	int mid = getMid(arr, begin, end);
	int temp = arr[begin];
	arr[begin] = arr[mid];
	arr[mid] = temp;
	//��һ��С�ڻ�׼ֵ��λ��
	int prev = begin;
	//�ڶ���С�ڻ�׼ֵ��λ��
	int cur = begin + 1;
	int key = arr[begin];
	while (cur <= end)
	{
		//��cur�ߵ�С�ڻ�׼ֵ��λ�ã��ж�prev��cur�Ƿ�����
		if (arr[cur] < key && ++prev != cur)
		{
			//������	����arr[prev]��arr[cur]
			int temp = arr[prev];
			arr[prev] = arr[cur];
			arr[cur] = temp;
		}
		++cur;
	}
	//������׼ֵarr[begin]��arr[prev]
	temp = arr[begin];
	arr[begin] = arr[prev];
	arr[prev] = temp;
	return prev;
}

void quickSort(int* arr, int begin, int end)
{
	if (begin >= end)	//Ҫô֮��һ�����ݣ�ҪôԽ���ˣ����������
		return;
	//С�����Ż���������Ԫ��С��10��ʱ��ʹ�ò�������
	if (end - begin < 10)
		insertSort(arr + begin, end - begin + 1);	//�������ʼλ�ã������Ԫ�ظ���
	else
	{
		//һ�λ���֮��	��׼ֵ��λ��
		int div = partion3(arr, begin, end);
		//���������ֵĿ�������
		quickSort(arr, begin, div - 1);
		quickSort(arr, div + 1, end);
	}
} 

/*
//��������ǵݹ�ʵ��
void quicksortNor(int* arr, int n)
{
	//����һ��˳�����������ֵ�����
	seqList sq;
	initList(&sq);
	//��������ֵ�����ķ�Χ
	//��
	pushBackSeqList(&sq, n - 1);
	//��
	pushBackSeqList(&sq, 0);
	//����˳����������е�����
	while (!emptySeqList(&sq))
	{
		//ȡ����������
		int left = backSeqList(&sq);
		popBackSeqList(&sq);
		int right = backSeqList(&sq);
		popBackSeqList(&sq);

		//��������
		int div = partion(arr, left, right);
		//[left,div - 1]
		if (left < div - 1)		//����������Ԫ��
		{
			pushBackSeqList(&sq, div - 1);
			pushBackSeqList(&sq, left);
		}
		//[div + 1,right]
		if (div + 1 < right)		//����������Ԫ��
		{
			pushBackSeqList(&sq, right);
			pushBackSeqList(&sq, div + 1);
		}
	}
}
*/

//�鲢����
//�ݹ�
void merge(int* arr, int begin, int mid, int end, int* tmp)
{
	int begin1 = begin;
	int end1 = mid;
	int begin2 = mid + 1;
	int end2 = end;
	//�����ռ����ʼλ��
	int idx = begin;
	//�ϲ���������
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (arr[begin1] <= arr[begin2])
			tmp[idx++] = arr[begin1++];
		else
			tmp[idx++] = arr[begin2++];
	}
	//�ж��Ƿ���ʣ���Ԫ��û�кϲ�
	if (begin1 <= end1)
		memcpy(tmp + idx, arr + begin1, sizeof(int) * (end1 - begin1 + 1));
	if (begin2 <= end2)
		memcpy(tmp + idx, arr + begin2, sizeof(int) * (end2 - begin2 + 1));
	//�ϲ�֮������п�����ԭʼ���� ��Ӧ����
	memcpy(arr + begin, tmp + begin, sizeof(int) * (end - begin + 1));
}

void _mergeSort(int* arr, int begin, int end, int* tmp)
{
	if (begin >= end)
		return;
	//�м�λ��
	int mid = begin + (end - begin) / 2;
	_mergeSort(arr, begin, mid, tmp);
	_mergeSort(arr, mid + 1, end, tmp);
	//�ϲ����������������[begin,mid][mid + 1,end]
	merge(arr, begin, mid, end, tmp);
}

void mergeSort(int* arr, int n)
{
	//���븨���ռ�
	int* tmp = (int*)malloc(sizeof(int) * n);
	_mergeSort(arr, 0, n - 1, tmp);
	free(tmp);	
}

//�ǵݹ�Ĺ鲢����
void mergeSortNor(int* arr, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	int step = 1;	//�����еĲ���
	while (step < n)
	{
		for (int idx = 0; idx < n; idx += 2 * step)
		{
			//�ҵ��������ϲ�������������[begin,mid][mid + 1,end]
			int begin = idx;
			int mid = idx + step - 1;
			//�ж��Ƿ���ڵڶ���������
			if (mid >= n - 1)
				continue;		//�����ڵڶ���������ֱ������
			int end = idx + 2 * step - 1;
			//�жϵڶ����������Ƿ�Խ��
			if (end >= n)
				end = n - 1;
			merge(arr, begin, mid, end, tmp);
		}
		//���²���
		step *= 2;
	}
}

//ʱ�临�Ӷȣ�n�����ֵ����Сֵ��ֵ�����ֵ		�ռ临�Ӷȣ����ֵ����Сֵ��ֵ		ȱ�㣺������Ҫ�ܴ�Ŀռ䣬����˷�
//��������
void  countSort(int* arr, int n)
{
	//�ҵ����ֵ����Сֵ
	int max, min;
	min = max = arr[0];
	for (int i = 1; i < n; ++i)
	{
		if (arr[i] > max)
			max = arr[i];
		if (arr[i] < min)
			min = arr[i];
	}
	//���㷶Χ
	int range = max - min + 1;
	//����һ���������飬��ʼ��Ϊ
	int* countArr = (int*)calloc(range, sizeof(int));
	//����
	for (int i = 0; i < n; ++i)
	{
		countArr[arr[i] - min]++;
	}
	//�����������飬����
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
	//��������
	int arr[10] = { 5,8,9,4,3,6,7,10,2,1 };
	int n = sizeof(arr) / sizeof(arr[0]);
	insertSort(arr, n);
	printf("���������飺\n");
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);	//1 2 3 4 5 6 7 8 9 10
}

void test2()
{
	//ϣ������
	int arr[10] = { 5,8,9,4,3,6,7,10,2,1 };
	int n = sizeof(arr) / sizeof(arr[0]);
	shellSort(arr, n);
	printf("���������飺\n");
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);	//1 2 3 4 5 6 7 8 9 10
}

void test3()
{
	//��������
	int arr[10] = { 5,8,9,4,3,6,7,10,2,1 };
	int n = sizeof(arr) / sizeof(arr[0]);
	quickSort(arr, 0, n - 1);
	printf("���������飺\n");
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);	//1 2 3 4 5 6 7 8 9 10
}

void test4()
{
	//�鲢����
	int arr[10] = { 5,8,9,4,3,6,7,10,2,1 };
	int n = sizeof(arr) / sizeof(arr[0]);
	//mergeSort(arr, n);
	mergeSortNor(arr, n);
	printf("���������飺\n");
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);	//1 2 3 4 5 6 7 8 9 10
}

void test5()
{
	//��������
	int arr[10] = { 5,8,9,4,3,6,7,10,2,1 };
	int n = sizeof(arr) / sizeof(arr[0]); 
	countSort(arr, n);
	printf("���������飺\n");
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);	//1 2 3 4 5 6 7 8 9 10
}

//���������㷨������
void test()
{
	int n;
	printf("������:\n");
	scanf_s("%d", &n);
	srand((unsigned)time(NULL));	//���������
	int* arr = (int*)malloc(sizeof(int) * n);
	int* copy1 = (int*)malloc(sizeof(int) * n);
	int* copy2 = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand();
	}
	memcpy(copy1, arr, sizeof(int) * n);
	memcpy(copy2, arr, sizeof(int) * n);
	time_t begin = clock();	//ʱ����ʼʱ��
	insertSort(copy1, n);
	time_t end = clock();	//ʱ�ӽ���ʱ��
	printf("ֱ�Ӳ�������ʱ�䣺%d\n", end - begin);
	begin = clock();	 
	shellSort(copy2, n);
	end = clock();
	printf("ϣ������ʱ�䣺%d\n", end - begin);
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