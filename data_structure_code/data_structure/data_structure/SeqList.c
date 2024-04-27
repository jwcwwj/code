#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//顺序表
/*
//顺序表的静态存储：空间不可变  在栈上开辟	不能开太大，容易造成栈溢出 结构体大小包含数据的大小
#define N 100
typedef int SLDateType;

typedef struct SeqList
{
	SLDateType array[N];	//定长数组
	size_t size;			//有效数据的个数
	size_t _capacity;		//当前可以存放的最大元素个数
}SeqList;
*/

//顺序表的动态存储：空间可变	在堆上开辟	结构体大小不包含数据的大小	
typedef int SLDateType;

typedef struct SeqList
{	
	SLDateType* _data;	//需要动态开辟的数组
	size_t _size;		//有效元素的个数
	size_t _capacity;	//当前可以存放的最大元素个数
}SeqList;

//初始化
void initSeqList(SeqList* s)
{
	assert(s);			//等价于if(s == NULL) return;  区别是assert只用于debug，在release下是没有作用的
	s->_data = NULL;
	s->_capacity = s->_size = 0;
}

/*
//数据拷贝
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

//检查容量
void checkCapacity(SeqList* s)
{
	if (s->_size == s->_capacity)			//空间满了，需要扩容
	{
		//下面的malloc操作可以用realloc替代：SLDateType* tmp = (SLDateType*)realloc(s->_data,sizeof(SLDateType) * newCapacity);	参数：数据 大小
		//开辟一个更大的空间，拷贝原来已有的数据，释放原来的空间
		
		int newCapacity = (s->_capacity == 0 ? 1 : 2 * s->_capacity);
		SLDateType * tmp = (SLDateType*)malloc(sizeof(SLDateType)*newCapacity);
		memcpy(tmp, s->_data, sizeof(SLDateType)*s->_size);		//字节拷贝	参数：新的空间 原有空间 拷贝的字节大小
		//SLDateType* tmp = (SLDateType*)realloc(s->_data, sizeof(SLDateType) * newCapacity);
		free(s->_data);		//释放
		//更新
		s->_data = tmp;
		s->_capacity = newCapacity; 
	}
}

//尾插数据	不考虑增容时间复杂度是O(1)
void pushBack(SeqList* s, SLDateType val)
{
	checkCapacity(s);
	s->_data[s->_size] = val;
	s->_size++;
}

//尾删数据	不考虑增容时间复杂度是O(1)
void popBack(SeqList* s)
{
	//并不是真正的删除数据，只是修改访问权限
	if (s == NULL)
		return;
	if (s->_size)	//s->_size > 0
	{
		s->_size--;
	}
}

//头插数据	 不考虑增容时间复杂度是O(n)
void pushFront(SeqList* s,SLDateType val)
{
	assert(s);
	checkCapacity(s);
	//移动元素：从后向前移动
	int end = s->_size;
	while (end > 0)
	{
		s->_data[end] = s->_data[end - 1];
		end--;
	}
	s->_data[0] = val;
	s->_size++;
} 

//头删数据	不考虑增容时间复杂度是O(n)
void popFront(SeqList* s)
{
	//assert(s && s->_size);	后者下面的
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

//任意位置的插入数据
void insert(SeqList* s, int pos, SLDateType val)
{
	if (s == NULL)
		return;
	if (pos >= 0 && pos <= s->_size)	//有效区间	0：头插	size：尾插
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

//任意位置的删除数据
void erase(SeqList* s, int pos)
{
	if (s == NULL || s->_size == 0)
		return;
	if (pos >= 0 && pos < s->_size)	//有效区间	0：头删	size - 1：尾删
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

//打印数据
void printSeqList(SeqList* s)
{
	for (int i = 0; i < s->_size; i++)
	{
		printf("%d ", s->_data[i]);
	}
	printf("\n");
}

//判断顺序表是否为空
int emptySeqList(SeqList* s)
{
	if (s == NULL || s->_size == 0)
		return 1;
	return 0;
}

//顺序表的大小
int sizeSeqList(SeqList* s)
{
	if (s == NULL)
		return 0;
	return s->_size;
}

//查找某一个元素
int findSeqList(SeqList* s,SLDateType val)
{
	for (int i = 0; i < s->_size; i++)
	{
		if (s->_data[i] == val)
			return i;	//返回找到的索引
	}
	return -1;	//没找到返回-1   因为0是合理返回之内的
}

//获取某一个位置的元素
SLDateType getSeqList(SeqList* s, int pos)
{
	//假定调用这个接口就是一个正确的操作
	return s->_data[pos];
}

//顺序表销毁  销毁手动申请的堆上的空间
//不销毁的话这个程序（进程）结束，资源会返还给系统。（系统进行释放）	内存泄漏严重的是程序在不间断运行（比如服务器）
void destroySeqList(SeqList* s)		 {
	if (s)
	{
		if (s->_data)
		{
			free(s->_data);		//释放堆上的空间	
			s->_data = NULL;	//避免是个野指针
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