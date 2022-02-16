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
	if (p1 > p2 || m1 > m2 || (p2 - p1) != (m2 - m1))
		T = NULL;
	else {
		T = (BTNode*)malloc(sizeof(BTNode));
		T->data = porder[p1];
		int count = 0;
		for (int i = m1;morder[i] != porder[p1];i++)count++;
		CreateBTreeBy_PMOrder(T->lchild, porder, morder, p1 + 1, p1 + count, m1, m1 + count - 1);
		CreateBTreeBy_PMOrder(T->rchild, porder, morder, p1 + count + 1, p2, m1 + count + 1, m2);
	}
}

void PreOrder(BiTree T) {
	if (T) {
		printf("%c", T->data);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
}

void MidOrder(BiTree T) {
	if (T) {
		MidOrder(T->lchild);
		printf("%c", T->data);
		MidOrder(T->rchild);
	}
}

void PostOrder(BiTree T) {
	if (T) {
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		printf("%c", T->data);
	}
}

int length(char arr[]) {
	int i;
	for (i = 0;arr[i] != '\0';i++);
	return i;
}


char Comm_Ancestor(char a[], int i, int j) {
	if (a[i] != '#' && a[j] != '#') {
		while (i != j) {
			if (i > j) {
				i = i / 2;
			}
			else
			{
				j = j / 2;
			}
		}
		return a[i];
	}
}

char Comm(char a[], int i, int j) {
	if (a[i] != '#' && a[j] != '#') {
		if (i == j)return a[i];
		if (i > j)return Comm(a, i / 2, j);
		else return Comm(a, i, j / 2);
	}
}

void MidOrderNoRecursion(BiTree T) {
	BiTree stack[MaxSize],p=T;//ʹ�ø���ջstack
	int top = -1;//topָ��ջ��Ԫ�أ���ֵΪ-1
	while (p||top!=-1) {//��ǰ�ڵ㲻Ϊ�ջ���ջ��Ϊ��ʱ����
		if (p) {//����ǰ�ڵ㲻Ϊ�գ�����ջ�����ż���������������
			stack[++top] = p;
			p = p->lchild;
		}
		else
		{//����ǰ�ڵ�Ϊ�գ�����ջ�����ʣ����ż���������������
			p = stack[top--];
			printf("%c", p->data);
			p = p->rchild;
		}
	}
}

void PreOrderNoRecursion(BiTree T) {
	BiTree stack[MaxSize], p = T;//ʹ�ø���ջstack
	int top = -1;//topָ��ջ��Ԫ�أ���ֵΪ-1
	while (p || top != -1) {//��ǰ�ڵ㲻Ϊ�ջ���ջ��Ϊ��ʱ����
		if (p) {//����ǰ�ڵ㲻Ϊ�գ�����ʲ���ջ�����ż���������������
			printf("%c", p->data);
			stack[++top] = p;
			p = p->lchild;
		}
		else
		{//����ǰ�ڵ�Ϊ�գ�����ջ�����ż�������ջ���ڵ��������
			p = stack[top--];
			p = p->rchild;
		}
	}
}

void PostOrderNoRecursion(BiTree T) {
	BiTree stack[MaxSize], p = T,r=NULL;//ʹ�ø���ջ������rָ���¼����ջʱ��������ʹ����������ڵ�
	int top = -1;//topָ��ջ��Ԫ�أ���ֵΪ-1
	while (p || top != -1) {//��ǰ�ڵ㲻Ϊ�ջ���ջ��Ϊ��ʱ����
		if (p) {//����ǰ�ڵ㲻Ϊ�գ�����ʲ���ջ�����ż���������������
			stack[++top] = p;
			p = p->lchild;
		}
		else
		{//����ǰ�ڵ�Ϊ�գ���
			p = stack[top];//ȡ��������ջ��Ԫ��
			if (p->rchild&&p->rchild!=r) {//��ջ��Ԫ�ص����������ڲ��һ�δ�����ʹ����������������
				p = p->rchild;
			}
			else
			{
				top--;//������ջ������
				printf("%c", p->data);
				r = p;//��r��Ϊ��ǰ�ڵ㣬��ʾ�˽ڵ�����ջ�����иձ����ʹ�
				p = NULL;//һ��ע�������pҪ��Ϊ�գ���Ϊ��ǰ�ڵ�������������ѱ�������ɣ�Ҫ�˵���һ��
			}
		}
	}
}

void LevelOrder(BiTree T) {
	BiTree Queue[MaxSize],p=T;//������������ʵ��
	int front = 0,rear=0;//frontָ����еĶ�ͷԪ�أ�rearָ���βԪ�صĺ���һλ
	Queue[rear++] = p;//��ʼʱ���ڵ����
	while (front!=rear) {//���Ӳ���ʱ����
		p = Queue[front++];//���Ӳ�����
		printf("%c", p->data);
		if (p->lchild)Queue[rear++] = p->lchild;//���ýڵ����������������
		if (p->rchild)Queue[rear++] = p->rchild;//���ýڵ����������������
	}
}

void LevelOrderReverse(BiTree T) {
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

void BTreeDepthRecursion(BiTree T, int& h,int k) {
	if (T) {
		k++;
		BTreeDepthRecursion(T->lchild, h, k);
		BTreeDepthRecursion(T->rchild, h, k);
		if (k > h)h = k;
	}
}

int BTreeDepthRecursion2(BiTree T) {
	int lh = 0, rh = 0;
	if (T) {
		lh = BTreeDepthRecursion2(T->lchild);//lh����������������
		rh = BTreeDepthRecursion2(T->rchild);//rh����������������
		if (lh > rh)return lh + 1;//����������ߴ������������򷵻ؽϸ���+1
		return rh + 1;
	}
	else
	{
		return 0;//�����ǰ�ڵ�Ϊ�գ����ظ߶�Ϊ0
	}
}

int BTreeDepth(BiTree T) {
	int maxlength=0;
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
	return maxlength+1;
}

int BTreeDepthLevel(BiTree T) {
	BiTree Queue[MaxSize], p = T;//��������
	int front = 0, rear = 0;//frontָ����еĶ�ͷԪ�أ�rearָ���βԪ�صĺ���һλ
	int last = 1, level = 0;//last����ǰ������һ���ڵ㣬��ֵ����Ϊ�����е��±ꣻlevel��ʾ������
	Queue[rear++] = p;
	while (front != rear) {
		p = Queue[front++];
		if (p->lchild)Queue[rear++] = p->lchild;
		if (p->rchild)Queue[rear++] = p->rchild;
		if (front == last) {//ÿ�����ʵ���ǰ������һ���ڵ�ʱ
			level++;//����+1
			last = rear;//last��Ϊ��һ������һ���ڵ�
		}
	}
	return level;
}

bool IsFullBTree(BiTree T) {
	BiTree Queue[MaxSize], p = T;
	if (p == NULL)return 0;	//Ϊ�����򷵻�
	int front = 0, rear = 0;	//front��rear��ʾ��ͷ��β
	int last = 1, nowLevel = 0,lastLevel=1;
	/*
	last	��ʾ��ǰ���Ԫ���ڶ�����Ľ��ޣ����жϱ�����һ������ݣ���ʼΪ1
	lastLevel	��ʾ��ǰ���ڱ�����ĳ���,��ʼΪ1�����ڵ����ڲ㣩
	nowLevel	��ʾ���ڱ�������²㳤��
	*/
	Queue[rear++] = p;
	while (front != rear) {
		p = Queue[front++];
		if (p->lchild) { //�����㵱ǰ�ڵ�����������ڣ����²�ڵ���+1
			Queue[rear++] = p->lchild; 
			nowLevel++; 
		}
		if (p->rchild) { //�����㵱ǰ�ڵ�����������ڣ����²�ڵ���+1
			Queue[rear++] = p->rchild; 
			nowLevel++; 
		}
		if (front == last) {
			/*
			�����������һ���ڵ�ʱ��
				����һ��ڵ�����������ǵ�ǰ��ڵ�������������ǰ��Ϊ����
				������һ��ڵ���ڵ�����������0
			*/
			if (nowLevel == lastLevel * 2) {
				lastLevel = nowLevel;
				nowLevel = 0;
				last = rear;
			}
			else if(nowLevel!=0)
			{
				return 0;
			}
		}
	}
	return 1;//����������޷����㣬�򷵻�1
}

int IsCompleteBTree(BiTree T) {
	BiTree Queue[MaxSize], p = T;
	int front = 0, rear = 0;
	if (p == NULL)return 0;
	Queue[rear++] = p;
	while (front != rear) {
		p = Queue[front++];
		if (p) {//���۽ڵ�p�����������������Ƿ�Ϊ�գ��������
			Queue[rear++] = p->lchild;
			Queue[rear++] = p->rchild;
		}
		else
		{//���ڳ��ӱ��������г��ֿսڵ�ʱ
			while (front != rear) {//���Ӳ������˽ڵ���ÿһ���ڵ�ֱ���ӿ�
				p = Queue[front++];
				if (p)//�ڴ��ڼ���������һ�ǿսڵ㣬����������������ȫ������������0
					return 0;
			}
		}
	}
	return 1;
}

int CountDoubleBrand(BiTree T) {
	int ln = 0, rn = 0, now = 0;
	if (T) {
		if (T->lchild)ln = CountDoubleBrand(T->lchild);//lnΪ��������˫��֧�ڵ����
		if (T->rchild)rn = CountDoubleBrand(T->rchild);//rnΪ��������˫��֧�ڵ����
		now = T->lchild && T->rchild;//nowΪ��ǰ�ڵ��Ƿ�Ϊ˫��֧������Ϊ1������Ϊ0
	}
	return ln + rn + now;
}

void ChangeLeftRight(BiTree& T) {
	BiTree temp;
	if (T) {
		temp = T->lchild;
		T->lchild = T->rchild;
		T->rchild = temp;
		ChangeLeftRight(T->lchild);
		ChangeLeftRight(T->rchild);
	}
}

char PreOrderNumk(BiTree T,int& h,int k) {
	char i = '#',lh,rh;
	if (T) {
		h++;
		if (h == k) {
			i = T->data;
			return i;
		}
		lh=PreOrderNumk(T->lchild,h,k);
		if (lh != '#')return lh;
		rh=PreOrderNumk(T->rchild,h,k);
		if (rh != '#')return rh;
	}
	return i;
}

void DeleteTree(BiTree& T) {
	if (T) {//�ݹ�ɾ��������T
		DeleteTree(T->lchild);
		DeleteTree(T->rchild);
		free(T);
	}
}

void DeleteXTree(BiTree& T,char x,BiTree &father,int isleft) {
	if (T) {
		if (T->data == x) 
		{ 
			DeleteTree(T);
			if (father) {
				if (isleft)father->lchild = NULL;
				else father->rchild = NULL;
			}
			return; 
		}
		DeleteXTree(T->lchild, x, T, 1);
		DeleteXTree(T->rchild, x, T, 0);
	}
}

void DeleteXTreeLevel(BiTree& T,char x) {
	BiTree Queue[MaxSize], p=T;
	int front = 0, rear = 0;
	if (T->data == x)DeleteTree(T);
	else Queue[rear++] = p;
	while(front != rear) {
		p = Queue[front++];
		if (p->lchild) {//�����ǰ�ڵ����������Ϊ����ֵΪx����ɾ���������������������
			if (p->lchild->data == x) {
				DeleteTree(p->lchild);
				p->lchild = NULL;
			}
			else {
				Queue[rear++] = p->lchild;
			}
		}
		if (p->rchild) {//�����ǰ�ڵ����������Ϊ����ֵΪx��ɾ���������������Һ������
			if (p->rchild->data == x) {
				DeleteTree(p->rchild);
				p->rchild = NULL;
			}
			else {
				Queue[rear++] = p->rchild;
			}
		}
	}
}

void FindAllAncestor(BiTree T, char x) {
	//���ں������Ѱ��ֵΪx�Ľڵ����������
	BiTree Stack[MaxSize], p = T, r=NULL;
	int top = -1;
	while (top != -1 || p) {
		if (p) {
			if (p->data == x) {//�����ǰ�ڵ�ֵΪx�����ջ�����ݼ�Ϊ��������
				for (int i = top;i != -1;i--)
					printf("\t%c", Stack[i]->data);
				break;
			}
			Stack[++top] = p;
			p = p->lchild;
		}
		else
		{
			p = Stack[top];
			if (p->rchild && p->rchild != r) {
				p = p->rchild;
			}
			else {
				top--;
				r = p;
				p = NULL;
			}
		}
			
	}
}

int BTreeWidthLevel(BiTree T) {
	/*
	���ȣ������Ϊ�գ�����Ϊ0��
	���ڲ�α����Զ��������з��ʣ�ͳ�����п�����Ĳ���еĽڵ�������
	*/
	if (!T)return 0;
	BiTree Queue[MaxSize], p = T;
	int front = 0, rear = 0, last = 1, maxWidth = 1, width = 0;
	Queue[rear++] = p;
	while (front != rear) {
		p = Queue[front++];
		if (p->lchild) { Queue[rear++] = p->lchild; width++; }
		if (p->rchild) { Queue[rear++] = p->rchild; width++; }
		if (front == last) {//�����������һ���ڵ�ʱ
			if (width > maxWidth)maxWidth = width;//������ڵ������������ȣ��޸������
			width = 0;//��һ���У�����ͳ�Ƹò�ڵ���
			last = rear;
		}
	}
	return maxWidth;
}

void FullBTreePreToPost(char pre[],int h1,int h2, char post[], int l1,int l2) {
	int size;
	if(h2>=h1){
		post[l2] = pre[h1];
		size = (h2 - h1) / 2;
		FullBTreePreToPost(pre, h1 + 1, h1 + size, post, l1, l1 + size - 1);
		FullBTreePreToPost(pre, h1 + 1 + size, h2, post, l1 + size, l2 - 1);
	}
}

BiTree LeafToLink(BiTree& T) {
	BiTree Stack[MaxSize], p = T, pre = NULL,head=NULL;
	int top = -1;
	while (top != -1 || p) {
		if (p) {
			if (p->lchild == NULL && p->rchild == NULL) {
				if (pre)pre->rchild = p;
				else head = p;
				pre = p;
			}
			Stack[++top] = p;
			p = p->lchild;
		}
		else
		{
			p = Stack[top--];
			p = p->rchild;
		}
	}
	if (pre)pre->rchild = NULL;
	return head;
}

bool JudgeSimilarTree(BiTree T1, BiTree T2) {
	if (T1 == NULL && T2 == NULL)return true;
	else if ((T1 && (T1->lchild == NULL) && (T1->rchild == NULL)) && (T2 && (T2->lchild == NULL) && (T2->rchild == NULL)))return true;
	else if(T1&&T2){
		return JudgeSimilarTree(T1->lchild, T2->lchild) && JudgeSimilarTree(T1->rchild, T2->rchild);
	}
	else return false;
}

int wpl(BiTree T) {
	static int w = 0;
	if (T) {
		if (T->lchild == NULL && T->rchild == NULL) {
			w += 1;
		}
		wpl(T->lchild);
		wpl(T->rchild);
	}
	return w;
}

int main()
{
	printf("�������������ǰ��ת����������Ϊ��");
	char preorder[] = "ABCDEFG";
	char postorder[MaxSize];
	int len = length(preorder);
	FullBTreePreToPost(preorder,0,len-1, postorder, 0, len-1);
	for (int i = 0;i < len;i++)printf("%c", postorder[i]);

	BiTree T;
	/*char porder[] = "ABDEGFCH";
	char morder[] = "DBGEFACH";*/
	char porder[] = "ABDHCEF";
	char morder[] = "DBHAECF";
	CreateBTreeBy_PMOrder(T, porder, morder, 0, length(porder)-1, 0, length(morder)-1);
	printf("\n��̬�������ԣ�%d", wpl(T));
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
	printf("%d���ݹ��㷨2��\n", BTreeDepthRecursion2(T));
	h = BTreeDepth(T);printf("%d�����ں�������ķǵݹ���߶��㷨��\n", h);
	h = BTreeDepthLevel(T);printf("%d����α�����߶��㷨��\n", h);
	printf("�Ƿ�Ϊ����������%d\n", IsFullBTree(T));
	printf("�Ƿ�Ϊ��ȫ��������%d\n", IsCompleteBTree(T));
	printf("˫��֧�ڵ������%d\n", CountDoubleBrand(T));
	printf("���������Ϊ��%d\n", BTreeWidthLevel(T));

	printf("��ӡx�ڵ���������ȣ�");
	FindAllAncestor(T, 'H');
	
	
	h = 0;
	int k = 7;
	printf("\nǰ������� %d ���ڵ��ֵΪ: %c", k, PreOrderNumk(T, h, k));

	printf("\n���ڲ�α���ɾ���Խڵ�ֵxΪ��������֮��������Ϊ��");
	DeleteXTreeLevel(T, 'C');
	printf("\t�����������");
	PreOrder(T);
	printf("\t�����������");
	MidOrder(T);

	printf("\n����ǰ�����ɾ���Խڵ�ֵxΪ��������֮��������Ϊ��");
	DeleteXTree(T, 'C', T, 1);
	printf("\t�����������");
	PreOrder(T);
	printf("\t�����������");
	MidOrder(T);
	
	printf("\n������������֮��������Ϊ��");
	ChangeLeftRight(T);
	printf("\t�����������");
	PreOrder(T);
	printf("\t�����������");
	MidOrder(T);

	printf("\n����Ҷ�ӽڵ㴮���ɵ��������Ϊ��");
	BiTree head, p;
	head = LeafToLink(T);
	p = head;
	while (p) {
		printf("%c", p->data);
		p = p->rchild;
	}
}