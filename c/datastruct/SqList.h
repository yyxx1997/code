#pragma once
#include<stdio.h>
#include<malloc.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef struct {
	int* data;
	int length;
	int listsize;
}SqList;

void Init_List_Sq(SqList& L) {
	L.data = (int*)malloc(sizeof(int) * LIST_INIT_SIZE);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
}

bool Incre_List_Sq(SqList& L) {
	int* newlist;
	newlist = (int*)malloc(sizeof(int) * (L.listsize + LISTINCREMENT));
	if (!newlist)return false;
	for (int i = 0;i < L.length;i++) {
		newlist[i] = L.data[i];
	}
	free(L.data);
	L.data = newlist;
	L.listsize += LISTINCREMENT;
	return true;
}

bool List_Insert_Sq(SqList& L, int i, int e) {
	if (i<1 || i>L.length + 1)	//i为插入位置，如果i的值不合法，返回错误
		return false;
	if (L.length >= L.listsize)	//若顺序表的长度不够插入，则扩容
		Incre_List_Sq(L);
	int j;
	for (j = L.length;j >= i;j--) {
		L.data[j] = L.data[j - 1];
	}
	L.data[j] = e;
	L.length++;
	return true;
}

bool List_Delete_Sq(SqList& L, int i, int& e) {
	if (i<1 || i>L.length)	//i为删除位置，如果i不合法，返回错误
		return false;
	e = L.data[i - 1];
	for (int j = i - 1;j < L.length - 1;j++)
		L.data[j] = L.data[j + 1];
	L.length--;
	return true;
}

void Print_List_Sq(SqList L) {
	for (int i = 0;i < L.length;i++)
		printf("%d\t", L.data[i]);
	printf("length is %d\nlistsize is %d\n", L.length, L.listsize);
}




