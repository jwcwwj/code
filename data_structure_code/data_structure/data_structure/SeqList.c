#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//˳���
/*
//˳���ľ�̬�洢���ռ䲻�ɱ�  ��ջ�Ͽ���	���ܿ�̫���������ջ��� �ṹ���С�������ݵĴ�С
#define N 100
typedef int SLDateType;

typedef struct SeqList
{
	SLDateType array[N];	//��������
	size_t size;			//��Ч���ݵĸ���
	size_t _capacity;		//��ǰ���Դ�ŵ����Ԫ�ظ���
}SeqList;
*/

//˳���Ķ�̬�洢���ռ�ɱ�	�ڶ��Ͽ���	�ṹ���С���������ݵĴ�С	
typedef int SLDateType;

typedef struct SeqList
{	
	SLDateType* _data;	//��Ҫ��̬���ٵ�����
	size_t _size;		//��ЧԪ�صĸ���
	size_t _capacity;	//��ǰ���Դ�ŵ����Ԫ�ظ���
}SeqList;

//��ʼ��
void initSeqList(SeqList* s)
{
	assert(s);			//�ȼ���if(s == NULL) return;  ������assertֻ����debug����release����û�����õ�
	s->_data = NULL;
	s->_capacity = s->_size = 0;
}

/*
//���ݿ���
void *memcpy(void *dest, const void *src, size_t count)
{
	//assert(dest && src);
	char* pdest = (char*)dest;
	const char* psrc = (const char*)src;
	while (count--)
	{
		*pdest++ = *psrc++;
	}
	return dest;
}
*/

//�������
void checkCapacity(SeqList* s)
{
	if (s->_size == s->_capacity)			//�ռ����ˣ���Ҫ����
	{
		//�����malloc����������realloc�����SLDateType* tmp = (SLDateType*)realloc(s->_data,sizeof(SLDateType) * newCapacity);	���������� ��С
		//����һ������Ŀռ䣬����ԭ�����е����ݣ��ͷ�ԭ���Ŀռ�
		
		int newCapacity = (s->_capacity == 0 ? 1 : 2 * s->_capacity);
		SLDateType * tmp = (SLDateType*)malloc(sizeof(SLDateType)*newCapacity);
		memcpy(tmp, s->_data, sizeof(SLDateType)*s->_size);		//�ֽڿ���	�������µĿռ� ԭ�пռ� �������ֽڴ�С
		//SLDateType* tmp = (SLDateType*)realloc(s->_data, sizeof(SLDateType) * newCapacity);
		free(s->_data);		//�ͷ�
		//����
		s->_data = tmp;
		s->_capacity = newCapacity; 
	}
}

//β������	����������ʱ�临�Ӷ���O(1)
void pushBack(SeqList* s, SLDateType val)
{
	checkCapacity(s);
	s->_data[s->_size] = val;
	s->_size++;
}

//βɾ����	����������ʱ�临�Ӷ���O(1)
void popBack(SeqList* s)
{
	//������������ɾ�����ݣ�ֻ���޸ķ���Ȩ��
	if (s == NULL)
		return;
	if (s->_size)	//s->_size > 0
	{
		s->_size--;
	}
}

//ͷ������	 ����������ʱ�临�Ӷ���O(n)
void pushFront(SeqList* s,SLDateType val)
{
	assert(s);
	checkCapacity(s);
	//�ƶ�Ԫ�أ��Ӻ���ǰ�ƶ�
	int end = s->_size;
	while (end > 0)
	{
		s->_data[end] = s->_data[end - 1];
		end--;
	}
	s->_data[0] = val;
	s->_size++;
} 

//ͷɾ����	����������ʱ�临�Ӷ���O(n)
void popFront(SeqList* s)
{
	//assert(s && s->_size);	���������
	if (s == NULL || s->_size == 0)
		return;
	int begin = 0;
	while (begin < s->_size - 1)
	{
		s->_data[begin] = s->_data[begin + 1];
		begin++;
	}
	s->_size--;
}

//����λ�õĲ�������
void insert(SeqList* s, int pos, SLDateType val)
{
	if (s == NULL)
		return;
	if (pos >= 0 && pos <= s->_size)	//��Ч����	0��ͷ��	size��β��
	{
		checkCapacity(s);
		int end = s->_size;
		while (end > pos)
		{
			s->_data[end] = s->_data[end - 1];
			end--;
		}
		s->_data[pos] = val;
		s->_size++;
	}
}

//����λ�õ�ɾ������
void erase(SeqList* s, int pos)
{
	if (s == NULL || s->_size == 0)
		return;
	if (pos >= 0 && pos < s->_size)	//��Ч����	0��ͷɾ	size - 1��βɾ
	{
		int begin = pos;
		while (begin < s->_size - 1)
		{
			s->_data[begin] = s->_data[begin + 1];
			begin++;
		}
		s->_size--;
	}
}

//��ӡ����
void printSeqList(SeqList* s)
{
	for (int i = 0; i < s->_size; i++)
	{
		printf("%d ", s->_data[i]);
	}
	printf("\n");
}

//�ж�˳����Ƿ�Ϊ��
int emptySeqList(SeqList* s)
{
	if (s == NULL || s->_size == 0)
		return 1;
	return 0;
}

//˳���Ĵ�С
int sizeSeqList(SeqList* s)
{
	if (s == NULL)
		return 0;
	return s->_size;
}

//����ĳһ��Ԫ��
int findSeqList(SeqList* s,SLDateType val)
{
	for (int i = 0; i < s->_size; i++)
	{
		if (s->_data[i] == val)
			return i;	//�����ҵ�������
	}
	return -1;	//û�ҵ�����-1   ��Ϊ0�Ǻ�����֮�ڵ�
}

//��ȡĳһ��λ�õ�Ԫ��
SLDateType getSeqList(SeqList* s, int pos)
{
	//�ٶ���������ӿھ���һ����ȷ�Ĳ���
	return s->_data[pos];
}

//˳�������  �����ֶ�����Ķ��ϵĿռ�
//�����ٵĻ�������򣨽��̣���������Դ�᷵����ϵͳ����ϵͳ�����ͷţ�	�ڴ�й©���ص��ǳ����ڲ�������У������������
void destroySeqList(SeqList* s)		 {
	if (s)
	{
		if (s->_data)
		{
			free(s->_data);		//�ͷŶ��ϵĿռ�	
			s->_data = NULL;	//�����Ǹ�Ұָ��
		}
	}
}

int main()
{
	SeqList s1;			
	initSeqList(&s1);  
	pushBack(&s1, 1);
	pushBack(&s1, 2);
	pushBack(&s1, 3);
	pushBack(&s1, 4);
	pushBack(&s1, 5);
	printSeqList(&s1);	//1 2 3 4 5
	popBack(&s1);
	printSeqList(&s1);	//1 2 3 4
	pushFront(&s1, 8);
	pushFront(&s1, 7);
	printSeqList(&s1);	//7 8 1 2 3 4
	popFront(&s1);
	popFront(&s1);
	popFront(&s1);		
	printSeqList(&s1);	//2 3 4
	insert(&s1, s1._size, 10);
	insert(&s1, 0, 11);
	printSeqList(&s1);	//11 2 3 4 10
	erase(&s1, 0);
	erase(&s1, s1._size - 1);
	printSeqList(&s1);	//2 3 4
	return 0;
}