#include <stdio.h>
#include <stdlib.h>

//��ͷ˫��ѭ������
typedef int LDataType;

typedef struct ListNode
{
	LDataType _data;
	struct listNode* _next;		//ָ����һ���ڵ����ʼλ��
	struct listNode* _prev;		//ָ����һ���ڵ����ʼλ��
}listNode;

typedef struct List
{
	listNode* _head;
}list;

//�����ڵ�
listNode* createListNode(LDataType val)
{
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->_data = val;
	node->_next = NULL;
	node->_prev = NULL;
	return node;
}

//��ʼ��	����ͷ
void initList(list* l)
{
	if (l == NULL)
		return;
	//������ ����һ����״�ṹ
	l->_head = createListNode(0);
	l->_head->_next = l->_head->_prev = l->_head;
}

//β��	ʱ�临�Ӷ�O(1)
void pushBackList(list* l, LDataType val)
{
	if (l == NULL)
		return;
	listNode* last = l->_head->_prev;	//β�ڵ�
	listNode* newNode = createListNode(val);
	//����
	last->_next = newNode;
	newNode->_prev = last;
	newNode->_next = l->_head;
	l->_head->_prev = newNode;
}

//βɾ
void popBackList(list* l)
{
	if (l == NULL)
		return;
	//������
	if (l->_head->_next == l->_head->_prev)
		return;
	listNode* last = l->_head->_prev;
	listNode* prev = last->_prev;
	free(last);
	prev->_next = l->_head;
	l->_head->_prev = prev;
}

//ͷ��
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

//ͷɾ
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

//ɾ������ڵ㣬����ɾ��ͷ���
void eraseList(list* l,listNode* node)
{
	//����ɾ��head�ڵ�
	if (l == NULL || l->_head == node)
		return;
	listNode* prev = node->_prev;
	listNode* next = node->_next;
	free(node);
	prev->_next = next;
	next->_prev = prev;

}

//������ڵ��ǰ���������
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

//��ӡ
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

//����
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
	insertList(&lst, lst._head, 4);	//β��
	insertList(&lst, lst._head, 5);
	printList(&lst);		//1 2 3 4 5
	insertList(&lst, lst._head->_next, 6);	//ͷ��
	insertList(&lst, lst._head->_next, 7);
	printList(&lst);		//7 6 1 2 3 4 5
	eraseList(&lst, lst._head);		//��Ч������ɾ��ͷ���
	eraseList(&lst, lst._head->_next);	//ͷɾ
	eraseList(&lst, lst._head->_prev);	//βɾ
	printList(&lst);		//6 1 2 3 4 
	return;
}