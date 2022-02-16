#pragma once
#define ElemType char
#include<stdio.h>
#include<malloc.h>
typedef struct BTNode {
	ElemType data;
	BTNode* lchild;
	BTNode* rchild;
}*BiTree;

void CreateBTreeByArr(BiTree& T, char arr[], int& count) {
	if (arr[count] == '#')T=NULL;
	else {
		T = (BTNode*)malloc(sizeof(BTNode));
		T->data = arr[count];
		CreateBTreeByArr(T->lchild, arr, ++count);
		CreateBTreeByArr(T->rchild, arr, ++count);
	}
}

void CreateBTreeBy_PMOrder(BiTree& T, char porder[], char morder[], int p1, int p2, int m1, int m2) {
	if (p1 > p2 || m1 > m2||(p2-p1)!=(m2-m1))
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

/*char a[] = "#abcdefg";
printf("%c", Comm(a, 4, 5));*/
/*
BiTree T;
int count=0;
char a[]= "AB#DE###C##";
CreateBTreeByArr(T, a, count);*/

/*gets_s(a);
while (*p != '\0') {
	printf("%c", *p);
	p++;
}*/
