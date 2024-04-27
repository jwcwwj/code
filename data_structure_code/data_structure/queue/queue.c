#include <stdio.h>
#include <stdlib.h>

typedef int QDataType;

//�ڵ�
typedef struct QNode
{
	struct QNode* _next;
	QDataType _data;
}qnode;

//����	������βָ�������
typedef struct Queue
{
	qnode* _front;
	qnode* _rear;
	int _size;		//һ�㲻�����Ԫ�أ���Ҫ�Լ�����	
}queue;	

//���г�ʼ��
void initQueue(queue* q)
{
	//��ʼ���ն���
	q->_front = q->_rear = NULL;
	q->_size = 0;
}

//�������нڵ�
qnode* createNode(QDataType val)
{
	qnode* node = (qnode*)malloc(sizeof(qnode));
	node->_data = val;
	node->_next = NULL;		//�������q._rear����һ���ڵ���NULL
	return node;
}

//���	β��
void pushBackQueue(queue* q, QDataType val)
{
	qnode* node = createNode(val);
	//�ն���
	if (q->_front == NULL)
		q->_front = q->_rear = node;
	else
	{
		q->_rear->_next = node;
		q->_rear = node;
	}
	++q->_size;
}

//����	ͷɾ 
void popFrontQueue(queue* q)
{
	if (q == NULL || q->_front == NULL)
		return;
	qnode* cur = q->_front;
	q->_front = q->_front->_next;
	if (q->_front == NULL)
		q->_rear = NULL;	//���q->_front��NULL�����������һ��Ԫ�ص�ɾ�����ı�q._rear��ָ��ΪNULL
	free(cur);
	--q->_size;
}

//��ȡ��ͷԪ��
QDataType getFrontQueue(queue* q)
{
	return q->_front->_data;
}

//��ȡ��βԪ��
QDataType getBackQueue(queue* q)
{
	return q->_rear->_data;
}

//��ȡ���д�С
int sizeQueue(queue* q)
{
	//return q->_size;
	int len = 0;
	qnode* cur = q->_front;
	while (cur)
	{
		++len;
		cur = cur->_next;
	}
	return len;
}

//�����Ƿ�Ϊ��
int emptyQueue(queue* q)
{
	if (sizeQueue(q))
		return 0;
	return 1;
}

//����
void destoryQueue(queue* q)
{
	//����Ҳ����ѭ��������
	qnode* cur = q->_front;
	while (cur)
	{
		qnode* next = cur->_next;
		free(cur);
		cur = next;
	}
	//�ͷ���֮�����ö���
	q->_front = q->_rear = NULL;
	q->_size = 0;
}

//��ӡ	����ֻ�ǲ��ԣ�����ֻ�ܷ�������Ԫ�أ����ܷ����м�Ԫ��(����ӿ��ǲ��ṩ�ģ�ֻ�ܴӶ�ͷ��ȡԪ�أ�ʹ���߲�֪���ڲ�ʵ��)
void printfQueue(queue* q)
{
	if (q == NULL || q->_front == NULL)
		return;
	qnode* cur = q->_front;
	while (cur != q->_rear)
	{
		printf("%d ", cur->_data);
		cur = cur->_next;
	}
	printf("%d\n", q->_rear->_data);
}

int main()
{
	queue q;
	initQueue(&q);
	pushBackQueue(&q, 1);
	pushBackQueue(&q, 2);
	pushBackQueue(&q, 3);
	pushBackQueue(&q, 4);
	pushBackQueue(&q, 5);
	printfQueue(&q);	//1 2 3 4 5
	printf("%d\n", sizeQueue(&q));	//5
	while (!emptyQueue(&q))
	{
		printf("%d ", q._front->_data);		//1 2 3 4 5
		popFrontQueue(&q);
	}
	return 0;
}