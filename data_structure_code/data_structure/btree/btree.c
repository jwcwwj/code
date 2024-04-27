#include <stdio.h>
#include <stdlib.h>  

typedef char DataType;

//节点
typedef struct BNode
{
	DataType _data;
	struct BNode* _left;
	struct BNode* _right;
}BNode;

// 通过前序遍历的数组"ABD##E#H##CF##G##"构建二叉树
BNode* createBTree(DataType arr[], int* idx)
{
	if (arr[*idx] == '#')
	{
		++(*idx);
		return NULL;
	}
	else
	{
		//创建以当前数据为根的子树
		BNode* root = (BNode*)malloc(sizeof(BNode));
		root->_data = arr[*idx];
		++(*idx);
		//创建以root为根的左子树
		root->_left = createBTree(arr, idx);
		root->_right = createBTree(arr, idx);
		return root;
	}
}

//前序遍历一颗树
void preOrder(BNode* root)
{
	//前序遍历：根	左子树	右子树
	if (root)
	{
		printf("%c ", root->_data);
		preOrder(root->_left);
		preOrder(root->_right);
	}
}

//中序遍历
void inOrder(BNode* root)
{
	if (root)
	{
		//左子树 根 右子树
		inOrder(root->_left);
		printf("%c ", root->_data);
		inOrder(root->_right);
	}
}

//后续遍历
void postOrder(BNode* root)
{
	if (root)
	{
		//左子树 右子树 根
		postOrder(root->_left);
		postOrder(root->_right);
		printf("%c ", root->_data);
	}
}

//计算二叉树的节点的个数
int bTreeSize(BNode* root)
{
	//左子树的节点个数 + 右子树的节点个数 + 1
	if (root == NULL)
		return 0;
	return bTreeSize(root->_left) + bTreeSize(root->_right) + 1;
}

//计算二叉树节点的个数第二种写法
void bTreeSize2(BNode* root,int* idx)
{
	if (root)
	{
		(*idx)++;
		bTreeSize2(root->_left, idx);
		bTreeSize2(root->_right, idx);
	}
}

//计算二叉树中叶子的个数
int bTreeLeafSize(BNode* root)
{
	//只有一个孩子节点的时候
	if (root == NULL)
		return 0;
	//左右孩子节点都不存在的时候返回1
	if (root->_left == NULL && root->_right == NULL)
		return 1;
	return bTreeLeafSize(root->_left) + bTreeLeafSize(root->_right);
}

//第k层有多少节点
int bTreeKSize(BNode* root,int k)
{
	if (root == NULL)
		return 0;
	//第一层右1个节点
	if (k == 1)
		return 1;
	//左右子树k - 1层的节点个数之和
	return bTreeKSize(root->_left, k - 1) + bTreeKSize(root->_right, k - 1);
}

//查找某一个节点在二叉树中的位置
BNode* bTreeFind(BNode* root, DataType ch)
{
	if (root == NULL)
		return NULL;
	if (root->_data == ch)
		return root;
	//左子树
	BNode* node = bTreeFind(root->_left, ch);
	if (node)
		return node;
	//右子树
	return bTreeFind(root->_right, ch);
}

//销毁二叉树的结构	二级指针传参修改一级指针，一级指针传参也可以释放，但会造成野指针
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

//队列
typedef BNode* QDataType;

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

//借助队列容器实现层序遍历
void bTreeLevelOrder(BNode* root)
{
	//借助队列保存节点
	queue q;
	initQueue(&q);
	//根节点存入队列
	if (root)
		pushBackQueue(&q, root);
	//遍历队列中的每一个节点
	while (!emptyQueue(&q))
	{
		//获取队头元素
		BNode* front = getFrontQueue(&q);
		//出队
		popFrontQueue(&q);
		printf("%c ", front->_data);
		//保存队头元素的左右孩子节点
		if(front->_left)
			pushBackQueue(&q, front->_left);
		if (front->_right)
			pushBackQueue(&q, front->_right);
	}
	printf("\n");
}

//这里是队列，链表也可以，只要满足先进先出就可可以
//判断是不是完全二叉树	层序遍历	节点连续，中间没有空节点
int isCompleteBTree(BNode* root)
{
	queue q;
	initQueue(&q);
	if (root)
		pushBackQueue(&q, root);	//树的根节点存在就入队
	while (!emptyQueue(&q))
	{
		//获取队头元素
		BNode* front = getFrontQueue(&q);
		//出队
		popFrontQueue(&q);
		//左右孩子节点入队
		if (front)
		{
			pushBackQueue(&q, front->_left);
			pushBackQueue(&q, front->_right);
		}
		else
			break;
	}
	//看队列中是否有非空节点
	while (!emptyQueue(&q))
	{
		//获取队头元素
		BNode* front = getFrontQueue(&q);
		//如果剩余节点中存在的非空节点，说明节点不连续
		if (front)
			return 0;	//不是完全二叉树
		//出队
		popFrontQueue(&q);
	}
	return 1;		//是完全二叉树
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