#pragma once
#include<stdio.h>
#include<malloc.h>

typedef struct LNode {
	int data;
	LNode* next;
}LNode, * LinkList;

LinkList List_HeadInsert(LinkList& L) {
	LinkList s;int x;
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	scanf_s("%d", &x);
	while (x != 9999) {
		s= (LinkList)malloc(sizeof(LNode));
		s->data = x;
		s->next = L->next;
		L->next = s;
		scanf_s("%d", &x);
	}
	return L;
}

LinkList List_TailInsert(LinkList& L) {
	LinkList s,r;int x;
	L = (LinkList)malloc(sizeof(LNode));
	r = L;
	L->next = NULL;
	scanf_s("%d", &x);
	while (x != 9999) {
		s = (LinkList)malloc(sizeof(LNode));
		s->data = x;
		r->next=s;
		r = s;
		scanf_s("%d", &x);
	}
	r->next = NULL;
	return L;
}

LinkList List_TailInsert_Arr(LinkList& L,int arr[],int length) {
	LinkList s, r;int x;
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	r = L;
	for (int i = 0;i < length;i++) {
		s = (LinkList)malloc(sizeof(LNode));
		s->data = arr[i];
		r->next = s;
		r = s;
	}
	r->next = NULL;
	return L;
}

LinkList List_HeadInsert_nohead(LinkList& L) {
	LinkList s;int x;
	L=NULL;
	scanf_s("%d", &x);
	while (x != 9999) {
		s = (LinkList)malloc(sizeof(LNode));
		s->data = x;
		s->next = L;
		L = s;
		scanf_s("%d", &x);
	}
	return L;
}

void Print_List_Link(LinkList& L) {
	printf("\n遍历链表结果为：");
	LinkList p = L->next;
	while (p) {
		printf("%d\t", p->data);
		p = p->next;
	}
	printf("\n");
}

void Print_List_Link_nohead(LinkList& L) {
	LinkList p = L;
	while (p) {
		printf("%d\t", p->data);
		p = p->next;
	}
}