#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ѭ������
typedef struct MyCircularQueue {
	//��һ��ʵ�֣�ͷ��β
	int* _data;
	int _front;
	int _rear;
	int _k;	//�����л�Ŷ���Ԫ��	���ȵļ�¼
} MyCircularQueue;

//���ѭ�������Ƿ�Ϊ��
int myCircularQueueIsEmpty(MyCircularQueue* obj) {
	if (obj->_front == obj->_rear)
		return 1;
	return 0;
}

//���ѭ�������Ƿ�����
int myCircularQueueIsFull(MyCircularQueue* obj) {
	if ((obj->_rear + 1) % (obj->_k + 1) == obj->_front)
		return 1;	//����
	return 0;		//û����
}
	
//�Ӷ��׻�ȡԪ�ء��������Ϊ�գ����� -1 
int myCircularQueueFront(MyCircularQueue* obj) {
	if (myCircularQueueIsEmpty(obj))
		return -1;
	return obj->_data[obj->_front];
}

//��ȡ��βԪ�ء��������Ϊ�գ����� -1 
int myCircularQueueRear(MyCircularQueue* obj) {
	if (myCircularQueueIsEmpty(obj))
		return -1;
	//���ض�β��rear��ǰһ��λ�õ�Ԫ��
	//�ж�rear�Ƿ�Ϊ0
	if (obj->_rear != 0)
		return obj->_data[obj->_rear - 1];
	else
		return obj->_data[obj->_k];
}

//���ö��г���Ϊk
MyCircularQueue* myCircularQueueCreate(int k) {
	//�࿪һ��Ԫ�صĿռ�
	MyCircularQueue* mq = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
	mq->_data = (int*)malloc(sizeof(int) * (k + 1));
	mq->_front = mq->_rear = 0;	//���������0��k�е�����һ��ֵ��ֻҪmq->_front == mq->_rear�ͱ�ʾΪ��
	mq->_k = k;
	return mq;
}

//��ѭ�����в���һ��Ԫ�أ��������ɹ��򷵻���
int myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
	//�ж϶����Ƿ��Ѿ�����
	if (myCircularQueueIsFull(obj))
		return 0;
	//���	��������
	obj->_data[obj->_rear++] = value;
	//�ж϶�β�Ƿ�Խ��
	if (obj->_rear > obj->_k)
		obj->_rear = 0;
	return 1;
}

//��ѭ��������ɾ��һ��Ԫ�ء�����ɹ�ɾ���򷵻���
int myCircularQueueDeQueue(MyCircularQueue* obj) {
	//�ж϶����Ƿ�Ϊ��
	if (obj->_front == obj->_rear)
		return 0;
	//����
	obj->_front++;
	//�ж϶�ͷ�Ƿ�Խ��
	if (obj->_front > obj->_k)
		obj->_front = 0;
	return 1;
}

//���ٶ���
void myCircularQueueFree(MyCircularQueue* obj) {
	free(obj->_data);
	free(obj);
}

int main()
{ 
	return 0;
}