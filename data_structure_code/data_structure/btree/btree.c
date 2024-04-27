#include <stdio.h>
#include <stdlib.h>  

typedef char DataType;

//�ڵ�
typedef struct BNode
{
	DataType _data;
	struct BNode* _left;
	struct BNode* _right;
}BNode;

// ͨ��ǰ�����������"ABD##E#H##CF##G##"����������
BNode* createBTree(DataType arr[], int* idx)
{
	if (arr[*idx] == '#')
	{
		++(*idx);
		return NULL;
	}
	else
	{
		//�����Ե�ǰ����Ϊ��������
		BNode* root = (BNode*)malloc(sizeof(BNode));
		root->_data = arr[*idx];
		++(*idx);
		//������rootΪ����������
		root->_left = createBTree(arr, idx);
		root->_right = createBTree(arr, idx);
		return root;
	}
}

//ǰ�����һ����
void preOrder(BNode* root)
{
	//ǰ���������	������	������
	if (root)
	{
		printf("%c ", root->_data);
		preOrder(root->_left);
		preOrder(root->_right);
	}
}

//�������
void inOrder(BNode* root)
{
	if (root)
	{
		//������ �� ������
		inOrder(root->_left);
		printf("%c ", root->_data);
		inOrder(root->_right);
	}
}

//��������
void postOrder(BNode* root)
{
	if (root)
	{
		//������ ������ ��
		postOrder(root->_left);
		postOrder(root->_right);
		printf("%c ", root->_data);
	}
}

//����������Ľڵ�ĸ���
int bTreeSize(BNode* root)
{
	//�������Ľڵ���� + �������Ľڵ���� + 1
	if (root == NULL)
		return 0;
	return bTreeSize(root->_left) + bTreeSize(root->_right) + 1;
}

//����������ڵ�ĸ����ڶ���д��
void bTreeSize2(BNode* root,int* idx)
{
	if (root)
	{
		(*idx)++;
		bTreeSize2(root->_left, idx);
		bTreeSize2(root->_right, idx);
	}
}

//�����������Ҷ�ӵĸ���
int bTreeLeafSize(BNode* root)
{
	//ֻ��һ�����ӽڵ��ʱ��
	if (root == NULL)
		return 0;
	//���Һ��ӽڵ㶼�����ڵ�ʱ�򷵻�1
	if (root->_left == NULL && root->_right == NULL)
		return 1;
	return bTreeLeafSize(root->_left) + bTreeLeafSize(root->_right);
}

//��k���ж��ٽڵ�
int bTreeKSize(BNode* root,int k)
{
	if (root == NULL)
		return 0;
	//��һ����1���ڵ�
	if (k == 1)
		return 1;
	//��������k - 1��Ľڵ����֮��
	return bTreeKSize(root->_left, k - 1) + bTreeKSize(root->_right, k - 1);
}

//����ĳһ���ڵ��ڶ������е�λ��
BNode* bTreeFind(BNode* root, DataType ch)
{
	if (root == NULL)
		return NULL;
	if (root->_data == ch)
		return root;
	//������
	BNode* node = bTreeFind(root->_left, ch);
	if (node)
		return node;
	//������
	return bTreeFind(root->_right, ch);
}

//���ٶ������Ľṹ	����ָ�봫���޸�һ��ָ�룬һ��ָ�봫��Ҳ�����ͷţ��������Ұָ��
void bTreeDestroy(BNode** root)
{ 
	if (*root)
	{
		bTreeDestroy(&((*root)->_left));
		bTreeDestroy(&((*root)->_right));
		free(*root);
		*root = NULL;
	}
}

//����
typedef BNode* QDataType;

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

//������������ʵ�ֲ������
void bTreeLevelOrder(BNode* root)
{
	//�������б���ڵ�
	queue q;
	initQueue(&q);
	//���ڵ�������
	if (root)
		pushBackQueue(&q, root);
	//���������е�ÿһ���ڵ�
	while (!emptyQueue(&q))
	{
		//��ȡ��ͷԪ��
		BNode* front = getFrontQueue(&q);
		//����
		popFrontQueue(&q);
		printf("%c ", front->_data);
		//�����ͷԪ�ص����Һ��ӽڵ�
		if(front->_left)
			pushBackQueue(&q, front->_left);
		if (front->_right)
			pushBackQueue(&q, front->_right);
	}
	printf("\n");
}

//�����Ƕ��У�����Ҳ���ԣ�ֻҪ�����Ƚ��ȳ��Ϳɿ���
//�ж��ǲ�����ȫ������	�������	�ڵ��������м�û�пսڵ�
int isCompleteBTree(BNode* root)
{
	queue q;
	initQueue(&q);
	if (root)
		pushBackQueue(&q, root);	//���ĸ��ڵ���ھ����
	while (!emptyQueue(&q))
	{
		//��ȡ��ͷԪ��
		BNode* front = getFrontQueue(&q);
		//����
		popFrontQueue(&q);
		//���Һ��ӽڵ����
		if (front)
		{
			pushBackQueue(&q, front->_left);
			pushBackQueue(&q, front->_right);
		}
		else
			break;
	}
	//���������Ƿ��зǿսڵ�
	while (!emptyQueue(&q))
	{
		//��ȡ��ͷԪ��
		BNode* front = getFrontQueue(&q);
		//���ʣ��ڵ��д��ڵķǿսڵ㣬˵���ڵ㲻����
		if (front)
			return 0;	//������ȫ������
		//����
		popFrontQueue(&q);
	}
	return 1;		//����ȫ������
}

int main()
{  
	char arr[] = "ABD##E#H##CF##G##";
	int idx = 0;
	BNode* node;
	BNode* root = createBTree(arr, &idx);
	preOrder(root);		//A B D E H C F G
	printf("\n");
	inOrder(root);		//D B E H A F C G
	printf("\n");
	postOrder(root);	//D H E B F G C A
	printf("\n");
	printf("%d\n", bTreeSize(root));
	idx = 0;
	bTreeSize2(root, &idx);
	printf("idx = %d\n", idx);	//idx = 8
	printf("%d\n", bTreeLeafSize(root));	//4
	printf("%d\n", bTreeKSize(root, 3));	//4
	printf("%d\n", bTreeKSize(root, 4));	//1
	node = bTreeFind(root, 'G');
	printf("%p   %c\n", node,node->_data);		//0000014A8E3AF0B0	G
	node = bTreeFind(root, 'g');
	printf("%p\n", node);		//0000000000000000(NULL)
	bTreeLevelOrder( root);		//A B C D E F G H
	printf("%d",isCompleteBTree(root));		//0
	return 0;
}