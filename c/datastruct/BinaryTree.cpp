#include<stdio.h>
#include<malloc.h>
#define MaxSize 20
#define ElemType char
typedef struct BTNode {
	ElemType data;
	BTNode* lchild;
	BTNode* rchild;
}*BiTree;

void CreateBTreeByArr(BiTree& T, char arr[], int& count) {
	if (arr[count] == '#')T = NULL;
	else {
		T = (BTNode*)malloc(sizeof(BTNode));
		T->data = arr[count];
		CreateBTreeByArr(T->lchild, arr, ++count);
		CreateBTreeByArr(T->rchild, arr, ++count);
	}
}

void CreateBTreeBy_PMOrder(BiTree& T, char porder[], char morder[], int p1, int p2, int m1, int m2) {
	/*递归根据先序和中序创建二叉树：
	BiTree& T	为树节点的指针, 
	char porder[]	存放先序遍历结果的数组, 
	char morder[]	存放中序遍历结果的数组, 
	int p1, int p2, 当前处理的先序序列的起始位置和终止位置（数组下标），
	int m1, int m2	当前处理的中序序列的起始位置和终止位置（数组下标）
	*/
	if (p1 > p2 || m1 > m2 || (p2 - p1) != (m2 - m1))T = NULL;
	else {
		T = (BTNode*)malloc(sizeof(BTNode));
		T->data = porder[p1];
		int count = 0;
		for (int i = m1;morder[i] != porder[p1];i++)count++;
		CreateBTreeBy_PMOrder(T->lchild, porder, morder, p1 + 1, p1 + count, m1, m1 + count - 1);
		CreateBTreeBy_PMOrder(T->rchild, porder, morder, p1 + count + 1, p2, m1 + count + 1, m2);
	}
}

void PreOrder(BiTree T) {//先序遍历
	if (T) {
		printf("%c", T->data);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
}

void MidOrder(BiTree T) {//中序遍历
	if (T) {
		MidOrder(T->lchild);
		printf("%c", T->data);
		MidOrder(T->rchild);
	}
}

void PostOrder(BiTree T) {//后序遍历
	if (T) {
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		printf("%c", T->data);
	}
}

void MidOrderNoRecursion(BiTree T) {//中序遍历非递归实现
	BiTree stack[MaxSize], p = T;
	int top = -1;
	while (p || top != -1) {
		if (p) {
			stack[++top] = p;
			p = p->lchild;
		}
		else
		{
			p = stack[top--];
			printf("%c", p->data);
			p = p->rchild;
		}
	}
}

void PreOrderNoRecursion(BiTree T) {//先序遍历非递归实现
	BiTree stack[MaxSize], p = T;
	int top = -1;
	while (p || top != -1) {
		if (p) {
			printf("%c", p->data);
			stack[++top] = p;
			p = p->lchild;
		}
		else
		{
			p = stack[top--];
			p = p->rchild;
		}
	}
}

void PostOrderNoRecursion(BiTree T) {//后序遍历非递归实现
	BiTree stack[MaxSize], p = T, r = NULL;
	int top = -1;

	while (p || top != -1) {
		if (p) {
			stack[++top] = p;
			p = p->lchild;
		}
		else
		{
			p = stack[top];
			if (p->rchild && p->rchild != r) {
				p = p->rchild;
			}
			else
			{
				top--;
				printf("%c", p->data);
				r = p;
				p = NULL;
			}
		}
	}
}

void LevelOrder(BiTree T) {//层次遍历
	BiTree Queue[MaxSize], p = T;
	int front = 0, rear = 0;
	Queue[rear++] = p;
	while (front != rear) {
		p = Queue[front++];
		printf("%c", p->data);
		if (p->lchild)Queue[rear++] = p->lchild;
		if (p->rchild)Queue[rear++] = p->rchild;
	}
}

void LevelOrderReverse(BiTree T) {//反向层次遍历
	BiTree Queue[MaxSize], p = T;
	char Stack[MaxSize];
	int top = -1;
	int front = 0, rear = 0;
	Queue[rear++] = p;
	while (front != rear) {
		p = Queue[front++];
		Stack[++top] = p->data;
		if (p->lchild)Queue[rear++] = p->lchild;
		if (p->rchild)Queue[rear++] = p->rchild;
	}
	while (top != -1) {
		printf("%c", Stack[top--]);
	}
}

void BTreeDepthRecursion(BiTree T, int& h, int k) {//递归求二叉树深度
	if (T) {
		k++;
		BTreeDepthRecursion(T->lchild, h, k);
		BTreeDepthRecursion(T->rchild, h, k);
		if (k > h)h = k;
	}
}

int BTreeDepth(BiTree T) {//非递归求二叉树深度
	int maxlength = 0;
	BiTree stack[MaxSize], p = T, r = NULL;
	int top = -1;

	while (p || top != -1) {
		if (p) {
			stack[++top] = p;
			if (maxlength < top)maxlength = top;
			p = p->lchild;
		}
		else
		{
			p = stack[top];
			if (p->rchild && p->rchild != r) {
				p = p->rchild;
			}
			else
			{
				top--;
				r = p;
				p = NULL;
			}
		}
	}
	return maxlength + 1;
}

int BTreeDepthLevel(BiTree T) {//层次遍历法求二叉树深度
	BiTree Queue[MaxSize], p = T;
	int top = -1;
	int front = 0, rear = 0;
	int last = 1, level = 0;
	Queue[rear++] = p;
	while (front != rear) {
		p = Queue[front++];
		if (p->lchild)Queue[rear++] = p->lchild;
		if (p->rchild)Queue[rear++] = p->rchild;
		if (front == last) {
			level++;
			last = rear;
		}
	}
	return level;
}

int main()
{
	BiTree T;
	char porder[] = "ABDGCEF";
	char morder[] = "DGBAECF";
	CreateBTreeBy_PMOrder(T, porder, morder, 0, 6, 0, 6);//根据先序遍历和中序遍历唯一确定一个二叉树，详细参数说明见函数
	printf("\n先序遍历：");
	PreOrder(T);
	printf("\n中序遍历：");
	MidOrder(T);
	printf("\n后序遍历：");
	PostOrder(T);
	printf("\n中序遍历无递归：");
	MidOrderNoRecursion(T);
	printf("\n前序遍历无递归：");
	PreOrderNoRecursion(T);
	printf("\n后序遍历无递归：");
	PostOrderNoRecursion(T);
	printf("\n层次遍历：");
	LevelOrder(T);
	printf("\n反向层次遍历（从下至上，从右至左）：");
	LevelOrderReverse(T);
	printf("\n树高为：\n");
	int h = 0;
	BTreeDepthRecursion(T, h, 0);printf("%d（递归算法）\n", h);
	h = BTreeDepth(T);printf("%d（基于后序遍历的非递归求高度算法）\n", h);
	h = BTreeDepthLevel(T);printf("%d（层次遍历求高度算法）\n", h);
}