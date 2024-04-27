#include <stdio.h>
#include <stdlib.h>

//带头双向循环链表
typedef int LDataType;

typedef struct ListNode
{
	LDataType _data;
	struct listNode* _next;		//指向下一个节点的起始位置
	struct listNode* _prev;		//指向上一个节点的起始位置
}listNode;

typedef struct List
{
	listNode* _head;
}list;

//创建节点
listNode* createListNode(LDataType val)
{
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->_data = val;
	node->_next = NULL;
	node->_prev = NULL;
	return node;
}

//初始化	创建头
void initList(list* l)
{
	if (l == NULL)
		return;
	//空链表 创建一个环状结构
	l->_head = createListNode(0);
	l->_head->_next = l->_head->_prev = l->_head;
}

//尾插	时间复杂度O(1)
void pushBackList(list* l, LDataType val)
{
	if (l == NULL)
		return;
	listNode* last = l->_head->_prev;	//尾节点
	listNode* newNode = createListNode(val);
	//连接
	last->_next = newNode;
	newNode->_prev = last;
	newNode->_next = l->_head;
	l->_head->_prev = newNode;
}

//尾删
void popBackList(list* l)
{
	if (l == NULL)
		return;
	//空链表
	if (l->_head->_next == l->_head->_prev)
		return;
	listNode* last = l->_head->_prev;
	listNode* prev = last->_prev;
	free(last);
	prev->_next = l->_head;
	l->_head->_prev = prev;
}

//头插
void pushFrontList(list* l, LDataType val)
{
	if (l == NULL)
		return;
	listNode* next = l->_head->_next;
	listNode* newNode = createListNode(val);
	l->_head->_next = newNode;
	newNode->_prev = l->_head;
	newNode->_next = next;
	next->_prev = newNode;
}

//头删
void popFrontList(list* l)
{
	if (l == NULL || l->_head->_next == l->_head)
		return;
	listNode* next = l->_head->_next;
	listNode* nextnext = next->_next;
	nextnext->_prev = l->_head;
	l->_head->_next = nextnext;
	free(next);
}

//删除任意节点，不能删除头结点
void eraseList(list* l,listNode* node)
{
	//不能删除head节点
	if (l == NULL || l->_head == node)
		return;
	listNode* prev = node->_prev;
	listNode* next = node->_next;
	free(node);
	prev->_next = next;
	next->_prev = prev;

}

//在任意节点的前面插入数据
void insertList(list*l, listNode* node, LDataType val)
{
	if (l == NULL)
		return;
	listNode* prev = node->_prev;
	listNode* newNode = createListNode(val);
	prev->_next = newNode;
	newNode->_prev = prev;
	newNode->_next = node;
	node->_prev = newNode;
}

//打印
void printList(list* l)
{
	listNode* cur = l->_head->_next;
	while (cur != l->_head)
	{
		printf("%d ", cur->_data);
		cur = cur->_next;
	}
	printf("\n");
}

//销毁
void destroyList(list* l)
{
	if (l)
	{
		if (l->_head)
		{
			listNode* cur = l->_head->_next;
			while (cur != l->_head)
			{
				listNode* next = cur->_next;
				free(cur);
				cur = next;
			}
		}
		free(l->_head);
	}
}

int main()
{
	list lst;
	initList(&lst);
	pushBackList(&lst, 1);
	pushBackList(&lst, 2);
	pushBackList(&lst, 3);
	pushBackList(&lst, 4);
	pushBackList(&lst, 5);	//1 2 3 4 5
	printList(&lst);
	popBackList(&lst);
	popBackList(&lst);
	printList(&lst);		//1 2 3
	pushFrontList(&lst, 2);
	pushFrontList(&lst, 3);
	printList(&lst);		//3 2 1 2 3
	popFrontList(&lst);
	popFrontList(&lst);
	printList(&lst);		//1 2 3
	insertList(&lst, lst._head, 4);	//尾插
	insertList(&lst, lst._head, 5);
	printList(&lst);		//1 2 3 4 5
	insertList(&lst, lst._head->_next, 6);	//头插
	insertList(&lst, lst._head->_next, 7);
	printList(&lst);		//7 6 1 2 3 4 5
	eraseList(&lst, lst._head);		//无效，不能删除头结点
	eraseList(&lst, lst._head->_next);	//头删
	eraseList(&lst, lst._head->_prev);	//尾删
	printList(&lst);		//6 1 2 3 4 
	return;
}