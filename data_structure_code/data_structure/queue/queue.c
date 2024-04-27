#include <stdio.h>
#include <stdlib.h>

typedef int QDataType;

//节点
typedef struct QNode
{
	struct QNode* _next;
	QDataType _data;
}qnode;

//队列	含有首尾指针的链表
typedef struct Queue
{
	qnode* _front;
	qnode* _rear;
	int _size;		//一般不给这个元素，需要自己遍历	
}queue;	

//队列初始化
void initQueue(queue* q)
{
	//初始化空队列
	q->_front = q->_rear = NULL;
	q->_size = 0;
}

//创建队列节点
qnode* createNode(QDataType val)
{
	qnode* node = (qnode*)malloc(sizeof(qnode));
	node->_data = val;
	node->_next = NULL;		//这里表明q._rear的下一个节点是NULL
	return node;
}

//入队	尾插
void pushBackQueue(queue* q, QDataType val)
{
	qnode* node = createNode(val);
	//空队列
	if (q->_front == NULL)
		q->_front = q->_rear = node;
	else
	{
		q->_rear->_next = node;
		q->_rear = node;
	}
	++q->_size;
}

//出队	头删 
void popFrontQueue(queue* q)
{
	if (q == NULL || q->_front == NULL)
		return;
	qnode* cur = q->_front;
	q->_front = q->_front->_next;
	if (q->_front == NULL)
		q->_rear = NULL;	//如果q->_front是NULL，表明是最后一个元素的删除，改变q._rear的指向为NULL
	free(cur);
	--q->_size;
}

//获取队头元素
QDataType getFrontQueue(queue* q)
{
	return q->_front->_data;
}

//获取队尾元素
QDataType getBackQueue(queue* q)
{
	return q->_rear->_data;
}

//获取队列大小
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

//队列是否为空
int emptyQueue(queue* q)
{
	if (sizeQueue(q))
		return 0;
	return 1;
}

//销毁
void destoryQueue(queue* q)
{
	//销毁也可以循环出队列
	qnode* cur = q->_front;
	while (cur)
	{
		qnode* next = cur->_next;
		free(cur);
		cur = next;
	}
	//释放完之后重置队列
	q->_front = q->_rear = NULL;
	q->_size = 0;
}

//打印	这里只是测试，队列只能访问两边元素，不能访问中间元素(这个接口是不提供的，只能从队头获取元素，使用者不知道内部实现)
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