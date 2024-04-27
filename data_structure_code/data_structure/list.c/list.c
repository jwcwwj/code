#include <stdio.h>
#include <stdlib.h>

//无头单向非循环单链表
typedef int LDataType;

//节点
typedef struct listNode
{
	LDataType _data;
	struct listNode* _next;
}listNode;

//单链表
typedef struct list
{
	//存放第一个节点的地址
	listNode* _head;
}list;

//初始化
void initList(list* l)
{
	if (l == NULL)
		return;
	//初始化为空的链表
	l->_head = NULL;
}

//创建节点
listNode* createNode(LDataType val)
{
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->_data = val;
	node->_next = NULL;
	return node;
}

//尾插
void pushBackList(list* l,LDataType val)
{
	if (l == NULL)
		return;
	//第一种情况：空链表插入第一个数据
	if (l->_head == NULL)
	{
		l->_head = createNode(val);
	}
	//第二种情况： 不是空链表
	else
	{
		//遍历找到最后一个节点
		listNode* tail = l->_head;
		while (tail->_next)
		{
			tail = tail->_next;
		}
		//插入
		tail->_next = createNode(val);
	}
}

//尾删
void popBackList(list* l)
{
	if (l == NULL || l->_head == NULL)
		return;
	listNode* tail = l->_head;
	listNode* prev = NULL;
	while (tail->_next)
	{
		prev = tail;
		tail = tail->_next;
	}
	//删除节点
	free(tail);
	//连接
	if (prev == NULL)	//删除的为头结点，更新头结点
		l->_head == NULL;
	else
		prev->_next = NULL;
}

//头插
void pushFrontList(list* l,LDataType val)
{
	if (l == NULL)
		return;
	if (l->_head == NULL)
	{
		//空链表
		l->_head == createNode(val);
	}
	else
	{
		listNode* node = createNode(val);
		node->_next = l->_head;
		l->_head = node;
	}
}

//头删
void popFrontList(list* l)
{
	if (l == NULL || l->_head == NULL)
		return;
	listNode* next = l->_head->_next;
	free(l->_head);
	l->_head = next;
}

//查找数据
listNode* findList(list* l, LDataType val)
{
	if (l == NULL || l->_head == NULL)
		return NULL;
	listNode* cur = l->_head;
	while (cur)
	{
		if (cur->_data == val)
			return cur;
		cur = cur->_next;
	}
	//循环之后还是没有找到
	return NULL;
}

//任意位置的插入	给一个节点的后面插入一个数据	时间复杂度O(1)
void insertAfterList(listNode* cur, LDataType val)
{
	if (cur == NULL)
		return;
	listNode* node = createNode(val);
	node->_next = cur->_next;
	cur->_next = node;
}

//任意位置的删除	删除一个节点的下一个节点	时间复杂度O(1)
void eraseAfterList(listNode* cur)
{
	if (cur == NULL)
		return;
	listNode* next = cur->_next;
	if (next == NULL)	//不存在直接fanhui 
		return;
	cur->_next = next->_next;
	free(next);
}

//打印
void printList(list* l)
{
	if (l == NULL)
		return;
	listNode* cur = l->_head;
	while (cur)
	{
		printf("%d ", cur->_data);
		cur = cur->_next;
	}
	printf("\n");
}

//链表的长度
int sizeList(list* l)
{
	if (l == NULL || l->_head == NULL)
		return 0;
	listNode* cur = l->_head;
	int len = 0;
	while (cur)
	{
		++len;
		cur = cur->_next;
	}
	return len;
}

//链表的销毁
void destroyList(list* l)
{
	if (l == NULL || l->_head == NULL)
		return;
	listNode* cur = l->_head;
	while (cur)
	{
		listNode* next = cur->_next;
		free(cur);
		cur = next;
	}
	l->_head = NULL;
}

int main()
{
	list lst;
	initList(&lst);
	pushBackList(&lst, 1);
	pushBackList(&lst, 2);
	pushBackList(&lst, 3);
	pushBackList(&lst, 4);
	pushBackList(&lst, 5);
	printList(&lst);	//1 2 3 4 5
	popBackList(&lst);
	popBackList(&lst);
	printList(&lst);	//1 2 3 
	pushFrontList(&lst, 10);
	pushFrontList(&lst, 8);
	printList(&lst);	//8 10 1 2 3 
	popFrontList(&lst);
	popFrontList(&lst);
	popFrontList(&lst);
	printList(&lst);	//2 3
	listNode* ret = findList(&lst, 3);
	insertAfterList(ret, 5);
	printList(&lst);	//2 3 5
	ret = findList(&lst, 2);
	eraseAfterList(ret);
	printList(&lst);	//2 5
	printf("%d\n", sizeList(&lst));
	return 0;
}