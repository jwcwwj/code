#include <stdio.h>
#include <stdlib.h>

//��ͷ�����ѭ��������
typedef int LDataType;

//�ڵ�
typedef struct listNode
{
	LDataType _data;
	struct listNode* _next;
}listNode;

//������
typedef struct list
{
	//��ŵ�һ���ڵ�ĵ�ַ
	listNode* _head;
}list;

//��ʼ��
void initList(list* l)
{
	if (l == NULL)
		return;
	//��ʼ��Ϊ�յ�����
	l->_head = NULL;
}

//�����ڵ�
listNode* createNode(LDataType val)
{
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->_data = val;
	node->_next = NULL;
	return node;
}

//β��
void pushBackList(list* l,LDataType val)
{
	if (l == NULL)
		return;
	//��һ�����������������һ������
	if (l->_head == NULL)
	{
		l->_head = createNode(val);
	}
	//�ڶ�������� ���ǿ�����
	else
	{
		//�����ҵ����һ���ڵ�
		listNode* tail = l->_head;
		while (tail->_next)
		{
			tail = tail->_next;
		}
		//����
		tail->_next = createNode(val);
	}
}

//βɾ
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
	//ɾ���ڵ�
	free(tail);
	//����
	if (prev == NULL)	//ɾ����Ϊͷ��㣬����ͷ���
		l->_head == NULL;
	else
		prev->_next = NULL;
}

//ͷ��
void pushFrontList(list* l,LDataType val)
{
	if (l == NULL)
		return;
	if (l->_head == NULL)
	{
		//������
		l->_head == createNode(val);
	}
	else
	{
		listNode* node = createNode(val);
		node->_next = l->_head;
		l->_head = node;
	}
}

//ͷɾ
void popFrontList(list* l)
{
	if (l == NULL || l->_head == NULL)
		return;
	listNode* next = l->_head->_next;
	free(l->_head);
	l->_head = next;
}

//��������
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
	//ѭ��֮����û���ҵ�
	return NULL;
}

//����λ�õĲ���	��һ���ڵ�ĺ������һ������	ʱ�临�Ӷ�O(1)
void insertAfterList(listNode* cur, LDataType val)
{
	if (cur == NULL)
		return;
	listNode* node = createNode(val);
	node->_next = cur->_next;
	cur->_next = node;
}

//����λ�õ�ɾ��	ɾ��һ���ڵ����һ���ڵ�	ʱ�临�Ӷ�O(1)
void eraseAfterList(listNode* cur)
{
	if (cur == NULL)
		return;
	listNode* next = cur->_next;
	if (next == NULL)	//������ֱ��fanhui 
		return;
	cur->_next = next->_next;
	free(next);
}

//��ӡ
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

//����ĳ���
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

//���������
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