#include <stdio.h>
#include <stdlib.h>

//˳��ṹʵ��ջ
typedef int STDataType;

typedef struct stack
{
	STDataType* _data;
	int _size;
	int _capacity;
}stack;

void checkCapacityStack(stack* s)
{
	if (s->_size == s->_capacity)
	{
		int newCapacity = (s->_capacity == 0 ? 1 : 2 * s->_capacity);
		s->_data = (STDataType*)realloc(s->_data, sizeof(STDataType) * newCapacity);
		s->_capacity = newCapacity;
	}
}

//ջ�ĳ�ʼ��
void initStack(stack* s)
{
	if (s == NULL)
		return;
	s->_data = NULL;
	s->_capacity = s->_size = 0;
}

//��ջ
void pushStack(stack* s, STDataType val)
{
	//β��
	if (s == NULL)
		return;
	//checkCapacity(s);
	checkCapacityStack(s);
	s->_data[s->_size++] = val;
}

//��ջ
void popStack(stack* s)
{
	if (s == NULL)
		return;
	//βɾ
	if (s->_size > 0)
		--s->_size;
}

//��ȡջ��Ԫ��
STDataType getTopStack(stack* s)
{
	return s->_data[s->_size - 1];
}

//�ж�ջ�Ƿ�Ϊ��
int emptyStack(stack* s)
{
	if (s == NULL || s->_size == 0)
		return 1;
	return 0;
}

//����ջ��Ԫ��
void printStack(stack* s)
{
	if (s == NULL)
		return;
	while(!emptyStack(s))
	{
		printf("%d ", getTopStack(s));
		popStack(s);
	}
	printf("\n");
}

//��ȡջ�ĳ���
int sizeStack(stack* s)
{
	if (s == NULL)
		return 0;
	return s->_size;
}

int main()
{
	stack st;
	initStack(&st);
	pushStack(&st, 1);
	pushStack(&st, 2);
	pushStack(&st, 3);
	pushStack(&st, 4);
	//printStack(&st);	//4 3 2 1	//����Ĳ����ǳ�ջ����ջ�Ľṹ��Ӱ��
	popStack(&st);
	popStack(&st);
	printStack(&st);	//2 1
	return 0;
}