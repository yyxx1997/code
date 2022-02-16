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
	/*�ݹ������������򴴽���������
	BiTree& T	Ϊ���ڵ��ָ��, 
	char porder[]	�������������������, 
	char morder[]	�������������������, 
	int p1, int p2, ��ǰ������������е���ʼλ�ú���ֹλ�ã������±꣩��
	int m1, int m2	��ǰ������������е���ʼλ�ú���ֹλ�ã������±꣩
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

void PreOrder(BiTree T) {//�������
	if (T) {
		printf("%c", T->data);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
}

void MidOrder(BiTree T) {//�������
	if (T) {
		MidOrder(T->lchild);
		printf("%c", T->data);
		MidOrder(T->rchild);
	}
}

void PostOrder(BiTree T) {//�������
	if (T) {
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		printf("%c", T->data);
	}
}

void MidOrderNoRecursion(BiTree T) {//��������ǵݹ�ʵ��
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

void PreOrderNoRecursion(BiTree T) {//��������ǵݹ�ʵ��
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

void PostOrderNoRecursion(BiTree T) {//��������ǵݹ�ʵ��
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

void LevelOrder(BiTree T) {//��α���
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

void LevelOrderReverse(BiTree T) {//�����α���
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

void BTreeDepthRecursion(BiTree T, int& h, int k) {//�ݹ�����������
	if (T) {
		k++;
		BTreeDepthRecursion(T->lchild, h, k);
		BTreeDepthRecursion(T->rchild, h, k);
		if (k > h)h = k;
	}
}

int BTreeDepth(BiTree T) {//�ǵݹ�����������
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

int BTreeDepthLevel(BiTree T) {//��α���������������
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
	CreateBTreeBy_PMOrder(T, porder, morder, 0, 6, 0, 6);//��������������������Ψһȷ��һ������������ϸ����˵��������
	printf("\n���������");
	PreOrder(T);
	printf("\n���������");
	MidOrder(T);
	printf("\n���������");
	PostOrder(T);
	printf("\n��������޵ݹ飺");
	MidOrderNoRecursion(T);
	printf("\nǰ������޵ݹ飺");
	PreOrderNoRecursion(T);
	printf("\n��������޵ݹ飺");
	PostOrderNoRecursion(T);
	printf("\n��α�����");
	LevelOrder(T);
	printf("\n�����α������������ϣ��������󣩣�");
	LevelOrderReverse(T);
	printf("\n����Ϊ��\n");
	int h = 0;
	BTreeDepthRecursion(T, h, 0);printf("%d���ݹ��㷨��\n", h);
	h = BTreeDepth(T);printf("%d�����ں�������ķǵݹ���߶��㷨��\n", h);
	h = BTreeDepthLevel(T);printf("%d����α�����߶��㷨��\n", h);
}