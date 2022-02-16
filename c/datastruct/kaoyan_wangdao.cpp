#include<stdio.h>
#include<malloc.h>

typedef struct LNode {//链表结构体定义
	int data;
	LNode* next;
}LNode, * LinkList;

LinkList List_HeadInsert(LinkList& L) {//头插法建立链表（带头节点的链表）
	LinkList s;int x;
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	printf("\n头插法建立链表，输入数字后再按enter继续，输入9999结束输入:\n");
	scanf_s("%d", &x);
	while (x != 9999) {
		printf("\n请继续输入：\n");
		s = (LinkList)malloc(sizeof(LNode));
		s->data = x;
		s->next = L->next;
		L->next = s;
		scanf_s("%d", &x);
	}
	return L;
}

void Print_List_Link(LinkList& L) {//遍历输出链表元素
	LinkList p = L->next;
	printf("\n链表元素依次为:");
	while (p) {
		printf("%d\t", p->data);
		p = p->next;
	}
}

void Question_237_1(LinkList& L, int s, int t) {//删除单链表中值大于s小于t的节点
	LinkList p = L->next, pre = L, q;
	while (p) {
		if (p->data<t && p->data>s) {
			q = p;
			pre->next = p->next;
			p = p->next;
			free(q);
		}
		else
		{
			pre = p;
			p = p->next;
		}
	}
}

//int main()
//{
//	LinkList L;
//	List_HeadInsert(L);
//	Print_List_Link(L);
//	Question_237_1(L, 3, 7);
//	Print_List_Link(L);
//}