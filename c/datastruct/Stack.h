#pragma once
#define MaxSize 50
typedef struct {
	int data[MaxSize];
	int top;
}SqStack;

void InitStack(SqStack &s) {
	s.top = -1;
}

bool Push(SqStack& s, int x){
	if (s.top == MaxSize - 1) {
		return false;
	}
	s.data[++s.top] = x;
	return true;
}

bool Pop(SqStack& s, int& e) {
	if (s.top != -1) {
		e = s.data[s.top--];
		return true;
	}
	return false;
}

bool StackEmpty(SqStack s) {
	if (s.top == -1)return true;
	return false;
}

bool GetTop(SqStack s,int &x) {
	if (s.top != -1) {
		x = s.data[s.top];
		return true;
	}
	return false;
}