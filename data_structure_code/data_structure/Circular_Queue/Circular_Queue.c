#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//循环队列
typedef struct MyCircularQueue {
	//第一种实现：头和尾
	int* _data;
	int _front;
	int _rear;
	int _k;	//队列中会放多少元素	长度的记录
} MyCircularQueue;

//检查循环队列是否为空
int myCircularQueueIsEmpty(MyCircularQueue* obj) {
	if (obj->_front == obj->_rear)
		return 1;
	return 0;
}

//检查循环队列是否已满
int myCircularQueueIsFull(MyCircularQueue* obj) {
	if ((obj->_rear + 1) % (obj->_k + 1) == obj->_front)
		return 1;	//满了
	return 0;		//没有满
}
	
//从队首获取元素。如果队列为空，返回 -1 
int myCircularQueueFront(MyCircularQueue* obj) {
	if (myCircularQueueIsEmpty(obj))
		return -1;
	return obj->_data[obj->_front];
}

//获取队尾元素。如果队列为空，返回 -1 
int myCircularQueueRear(MyCircularQueue* obj) {
	if (myCircularQueueIsEmpty(obj))
		return -1;
	//返回队尾：rear的前一个位置的元素
	//判断rear是否为0
	if (obj->_rear != 0)
		return obj->_data[obj->_rear - 1];
	else
		return obj->_data[obj->_k];
}

//设置队列长度为k
MyCircularQueue* myCircularQueueCreate(int k) {
	//多开一个元素的空间
	MyCircularQueue* mq = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
	mq->_data = (int*)malloc(sizeof(int) * (k + 1));
	mq->_front = mq->_rear = 0;	//这里可以置0到k中的任意一个值，只要mq->_front == mq->_rear就表示为空
	mq->_k = k;
	return mq;
}

//向循环队列插入一个元素，如果插入成功则返回真
int myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
	//判断队列是否已经满了
	if (myCircularQueueIsFull(obj))
		return 0;
	//入队	更新索引
	obj->_data[obj->_rear++] = value;
	//判断队尾是否越界
	if (obj->_rear > obj->_k)
		obj->_rear = 0;
	return 1;
}

//从循环队列中删除一个元素。如果成功删除则返回真
int myCircularQueueDeQueue(MyCircularQueue* obj) {
	//判断队列是否为空
	if (obj->_front == obj->_rear)
		return 0;
	//出队
	obj->_front++;
	//判断队头是否越界
	if (obj->_front > obj->_k)
		obj->_front = 0;
	return 1;
}

//销毁队列
void myCircularQueueFree(MyCircularQueue* obj) {
	free(obj->_data);
	free(obj);
}

int main()
{ 
	return 0;
}