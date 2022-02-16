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
	BiTree stack[MaxSize],p=T;//使用辅助栈stack
	int top = -1;//top指向栈顶元素，初值为-1
	while (p||top!=-1) {//当前节点不为空或者栈不为空时运行
		if (p) {//若当前节点不为空，则入栈，接着继续遍历其左子树
			stack[++top] = p;
			p = p->lchild;
		}
		else
		{//若当前节点为空，则退栈并访问，接着继续遍历其右子树
			p = stack[top--];
			printf("%c", p->data);
			p = p->rchild;
		}
	}
}

void PreOrderNoRecursion(BiTree T) {
	BiTree stack[MaxSize], p = T;//使用辅助栈stack
	int top = -1;//top指向栈顶元素，初值为-1
	while (p || top != -1) {//当前节点不为空或者栈不为空时运行
		if (p) {//若当前节点不为空，则访问并入栈，接着继续遍历其左子树
			printf("%c", p->data);
			stack[++top] = p;
			p = p->lchild;
		}
		else
		{//若当前节点为空，则退栈，接着继续遍历栈顶节点的右子树
			p = stack[top--];
			p = p->rchild;
		}
	}
}

void PostOrderNoRecursion(BiTree T) {
	BiTree stack[MaxSize], p = T,r=NULL;//使用辅助栈，并设r指针记录在退栈时最近被访问过的右子树节点
	int top = -1;//top指向栈顶元素，初值为-1
	while (p || top != -1) {//当前节点不为空或者栈不为空时运行
		if (p) {//若当前节点不为空，则访问并入栈，接着继续遍历其左子树
			stack[++top] = p;
			p = p->lchild;
		}
		else
		{//若当前节点为空，则：
			p = stack[top];//取出并考察栈顶元素
			if (p->rchild&&p->rchild!=r) {//若栈顶元素的右子树存在并且还未被访问过，则访问其右子树
				p = p->rchild;
			}
			else
			{
				top--;//否则退栈并访问
				printf("%c", p->data);
				r = p;//将r置为当前节点，表示此节点在退栈过程中刚被访问过
				p = NULL;//一定注意这里的p要置为空，因为当前节点的左右子树都已被遍历完成，要退到上一级
			}
		}
	}
}

void LevelOrder(BiTree T) {
	BiTree Queue[MaxSize],p=T;//借助辅助队列实现
	int front = 0,rear=0;//front指向队列的队头元素，rear指向队尾元素的后面一位
	Queue[rear++] = p;//开始时根节点入队
	while (front!=rear) {//当队不空时运行
		p = Queue[front++];//出队并访问
		printf("%c", p->data);
		if (p->lchild)Queue[rear++] = p->lchild;//若该节点有左子树，则入队
		if (p->rchild)Queue[rear++] = p->rchild;//若该节点有右子树，则入队
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
		lh = BTreeDepthRecursion2(T->lchild);//lh返回左子树的树高
		rh = BTreeDepthRecursion2(T->rchild);//rh返回右子树的树高
		if (lh > rh)return lh + 1;//如果左子树高大于右子树，则返回较高者+1
		return rh + 1;
	}
	else
	{
		return 0;//如果当前节点为空，返回高度为0
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
	BiTree Queue[MaxSize], p = T;//辅助队列
	int front = 0, rear = 0;//front指向队列的队头元素，rear指向队尾元素的后面一位
	int last = 1, level = 0;//last代表当前层的最后一个节点，数值具体为队列中的下标；level表示层数；
	Queue[rear++] = p;
	while (front != rear) {
		p = Queue[front++];
		if (p->lchild)Queue[rear++] = p->lchild;
		if (p->rchild)Queue[rear++] = p->rchild;
		if (front == last) {//每当访问到当前层的最后一个节点时
			level++;//层数+1
			last = rear;//last置为下一层的最后一个节点
		}
	}
	return level;
}

bool IsFullBTree(BiTree T) {
	BiTree Queue[MaxSize], p = T;
	if (p == NULL)return 0;	//为空树则返回
	int front = 0, rear = 0;	//front、rear表示队头队尾
	int last = 1, nowLevel = 0,lastLevel=1;
	/*
	last	表示当前层的元素在队列里的界限，是判断遍历完一层的依据，初始为1
	lastLevel	表示当前正在遍历层的长度,初始为1（根节点所在层）
	nowLevel	表示正在遍历层的下层长度
	*/
	Queue[rear++] = p;
	while (front != rear) {
		p = Queue[front++];
		if (p->lchild) { //若本层当前节点的左子树存在，则下层节点数+1
			Queue[rear++] = p->lchild; 
			nowLevel++; 
		}
		if (p->rchild) { //若本层当前节点的右子树存在，则下层节点数+1
			Queue[rear++] = p->rchild; 
			nowLevel++; 
		}
		if (front == last) {
			/*
			遍历本层最后一个节点时：
				若下一层节点存在且总数是当前层节点数的两倍，则当前层为满；
				否则下一层节点存在但非满，返回0
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
	return 1;//遍历完成且无非满层，则返回1
}

int IsCompleteBTree(BiTree T) {
	BiTree Queue[MaxSize], p = T;
	int front = 0, rear = 0;
	if (p == NULL)return 0;
	Queue[rear++] = p;
	while (front != rear) {
		p = Queue[front++];
		if (p) {//无论节点p的左子树和右子树是否为空，都先入队
			Queue[rear++] = p->lchild;
			Queue[rear++] = p->rchild;
		}
		else
		{//当在出队遍历过程中出现空节点时
			while (front != rear) {//出队并遍历此节点后的每一个节点直至队空
				p = Queue[front++];
				if (p)//在此期间若出现任一非空节点，表明二叉树不是完全二叉树，返回0
					return 0;
			}
		}
	}
	return 1;
}

int CountDoubleBrand(BiTree T) {
	int ln = 0, rn = 0, now = 0;
	if (T) {
		if (T->lchild)ln = CountDoubleBrand(T->lchild);//ln为左子树中双分支节点个数
		if (T->rchild)rn = CountDoubleBrand(T->rchild);//rn为右子树中双分支节点个数
		now = T->lchild && T->rchild;//now为当前节点是否为双分支，是则为1，否则为0
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
	if (T) {//递归删除二叉树T
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
		if (p->lchild) {//如果当前节点的左子树不为空且值为x，则删除左子树；否则左孩子入队
			if (p->lchild->data == x) {
				DeleteTree(p->lchild);
				p->lchild = NULL;
			}
			else {
				Queue[rear++] = p->lchild;
			}
		}
		if (p->rchild) {//如果当前节点的右子树不为空且值为x，删除左子树；否则右孩子入队
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
	//基于后序遍历寻找值为x的节点的所有祖先
	BiTree Stack[MaxSize], p = T, r=NULL;
	int top = -1;
	while (top != -1 || p) {
		if (p) {
			if (p->data == x) {//如果当前节点值为x，输出栈中内容即为所有祖先
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
	首先，如果树为空，则宽度为0；
	基于层次遍历对二叉树进行访问，统计树中宽度最大的层具有的节点数即可
	*/
	if (!T)return 0;
	BiTree Queue[MaxSize], p = T;
	int front = 0, rear = 0, last = 1, maxWidth = 1, width = 0;
	Queue[rear++] = p;
	while (front != rear) {
		p = Queue[front++];
		if (p->lchild) { Queue[rear++] = p->lchild; width++; }
		if (p->rchild) { Queue[rear++] = p->rchild; width++; }
		if (front == last) {//遍历本层最后一个节点时
			if (width > maxWidth)maxWidth = width;//若本层节点个数大于最大宽度，修改最大宽度
			width = 0;//下一层中，重新统计该层节点数
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
	printf("输出满二叉树的前序转后序遍历结果为：");
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
	printf("\n静态变量测试：%d", wpl(T));
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
	printf("%d（递归算法2）\n", BTreeDepthRecursion2(T));
	h = BTreeDepth(T);printf("%d（基于后序遍历的非递归求高度算法）\n", h);
	h = BTreeDepthLevel(T);printf("%d（层次遍历求高度算法）\n", h);
	printf("是否为满二叉树：%d\n", IsFullBTree(T));
	printf("是否为完全二叉树：%d\n", IsCompleteBTree(T));
	printf("双分支节点个数：%d\n", CountDoubleBrand(T));
	printf("树的最大宽度为：%d\n", BTreeWidthLevel(T));

	printf("打印x节点的所有祖先：");
	FindAllAncestor(T, 'H');
	
	
	h = 0;
	int k = 7;
	printf("\n前序遍历第 %d 个节点的值为: %c", k, PreOrderNumk(T, h, k));

	printf("\n基于层次遍历删除以节点值x为根的子树之后遍历结果为：");
	DeleteXTreeLevel(T, 'C');
	printf("\t先序遍历——");
	PreOrder(T);
	printf("\t中序遍历——");
	MidOrder(T);

	printf("\n基于前序遍历删除以节点值x为根的子树之后遍历结果为：");
	DeleteXTree(T, 'C', T, 1);
	printf("\t先序遍历——");
	PreOrder(T);
	printf("\t中序遍历——");
	MidOrder(T);
	
	printf("\n交换左右子树之后遍历结果为：");
	ChangeLeftRight(T);
	printf("\t先序遍历——");
	PreOrder(T);
	printf("\t中序遍历——");
	MidOrder(T);

	printf("\n树的叶子节点串联成单链表输出为：");
	BiTree head, p;
	head = LeafToLink(T);
	p = head;
	while (p) {
		printf("%c", p->data);
		p = p->rchild;
	}
}