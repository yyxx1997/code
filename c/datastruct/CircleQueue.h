#pragma once
#define MaxSize 10
typedef struct {
	int data[MaxSize];
	int front;
	int rear;
	int tag;
}SqQueue;

void InitQueue(SqQueue& s) {
	s.front = 0;
	s.rear = 0;
	s.tag = 0;
}

bool EnQueue(SqQueue& s, int x) {
	if (s.rear==s.front&&s.tag==1)
		return false;
	s.data[s.rear] = x;
	s.rear = (s.rear + 1) % MaxSize;
	s.tag = 1;
	return true;
}

bool DeQueue(SqQueue& s,int &x) {
	if (s.rear == s.front && s.tag == 0)
		return false;
	x = s.data[s.front];
	s.front = (s.front + 1) % MaxSize;
	s.tag == 0;
}