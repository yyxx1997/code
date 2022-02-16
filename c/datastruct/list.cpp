#include<stdio.h>
#include<malloc.h>
#include"LinkList.h"
#include"SqList.h"


int Question_223_1(SqList& L) {
	if (L.length <= 0)
		return false;
	int temp,min = 0;
	for (int i = 1;i < L.length;i++) {
		if (L.data[i] < L.data[min])
			min = i;
	}
	temp = L.data[min];
	L.data[min] = L.data[L.length - 1];
	L.length--;
	return temp;
}

void Question_223_2(SqList& L) {
	int temp;
	for (int i = 0;i < L.length / 2;i++) {
		temp = L.data[i];
		L.data[i] = L.data[L.length - i - 1];
		L.data[L.length - i - 1]=temp;
	}
}

void Question_223_3(SqList& L, int x) {
	int p=0,count=0;
	for (int i = 0;i < L.length;i++) {
		if (L.data[i] == x)
			count++;
		else 
			L.data[p++] = L.data[i]; 
	}
	L.length -= count;
}

void Question_223_3_2(SqList& L, int x) {
	int p = 0,q=L.length-1,count = 0;
	while (p != q) {
		if (L.data[p] == x) {
			while ((q > p)&& L.data[q]==x)q--;
			if (p == q)break;
			else
			{
				L.data[p] = L.data[q--];
				count++;
			}
		}
		else
		{
			count++;
		}
		p++;
	}
	L.length = count;
}

bool Question_223_4(SqList& L, int s,int t) {
	if (s > t||L.length==0)return false;
	int i = 0;
	while (i < L.length && L.data[i] <= s)i++;
	int j = i+1;
	while (j < L.length && L.data[j] < t)j++;
	for (int k = j;k < L.length;k++) {
		L.data[k - j + i] = L.data[k];
	}
	L.length -= j - i;
	return true;
}

void Question_223_5(SqList& L, int s,int t) {
	int p = 0, count = 0;
	for (int i = 0;i < L.length;i++) {
		if (L.data[i]>s&&L.data[i]<t)
			count++;
		else
			L.data[p++] = L.data[i];
	}
	L.length -= count;
}

void Question_223_6(SqList& L) {
	int p = 1, count = 0;
	for (int i = 1;i < L.length;i++) {
		if (L.data[i]==L.data[i-1])
			count++;
		else
			L.data[p++] = L.data[i];
	}
	L.length -= count;
}

void Question_223_7(SqList L1, SqList L2,SqList &L3) {
	int i = 0, j = 0, k = 0;
	while(i < L1.length && j < L2.length) {
		if (L1.data[i] < L2.data[j])
			L3.data[k++] = L1.data[i++];
		else 
			L3.data[k++] = L2.data[j++];
	}
	if(i==L1.length)
		for(;j < L2.length;j++)
			L3.data[k++] = L2.data[j];
	else {
		for (;i < L1.length;i++)
			L3.data[k++] = L1.data[i];
	}
	L3.length = k;
}

void Reverse_SqList(SqList& L, int start, int end) {
	int temp;
	for (int i = start;i <= (start + end) / 2;i++) {
		temp = L.data[i];
		L.data[i] = L.data[end + start - i];
		L.data[end + start - i] = temp;
	}
}

void Question_223_8(SqList& L,int m) {
	Reverse_SqList(L, 0, L.length - 1);
	Reverse_SqList(L, 0, L.length-m-1);
	Reverse_SqList(L, L.length - m, L.length-1);
}

void Question_223_9(SqList& L, int x) {
	int temp,mid,low = 0, high = L.length-1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (L.data[mid] == x)break;
		else if (L.data[mid] > x)high = mid - 1;
		else low = mid + 1;
	}
	if (L.data[mid] == x && mid != L.length - 1) {
		temp = L.data[mid + 1];
		L.data[mid + 1] = L.data[mid];
		L.data[mid] = temp;
		return;
	}
	if(low>high){
		for (int i = L.length;i > low;i--) {
			L.data[i] = L.data[i - 1];
		}
		L.data[low] = x;
		L.length++;
	}
}

int Question_223_11(int A[], int B[],int length) {
	int a1=0, a2=length-1, b1=0, b2=length-1;
	int mid1, mid2;
	while(a1!=a2&&b1!=b2){
		mid1 = (a1 + a2) / 2;
		mid2 = (b1 + b2) / 2;
		if (A[mid1] == B[mid2]) {
			return A[mid1];
		}
		else if(A[mid1] < B[mid2])
		{
			if ((a1 + a2) % 2 == 0) {
				a1 = mid1;
				b2 = mid2;
			}
			else {
				a1 = mid1 + 1;
				b2 = mid2;
			}
			
		}
		else
		{
			if ((a1 + a2) % 2 == 0) {
				a2 = mid1;
				b1 = mid2;
			}
			else {
				a2 = mid1;
				b2 = mid2+1;
			}
			
		}
	}
	return A[a1] < B[b2] ? A[a1] : B[b2];
}

int Question_223_12(int a[],int length) {
	int now = a[0], count=1;
	for (int i = 1;i < length;i++) {
		if (a[i] == now)
			count++;
		else
		{
			count--;
			if (count <= 0) {
				now = a[i];
				count = 0;
			}
		}
	}
	if (count < 1)return -1;
	count = 0;
	for (int k = 0;k < length;k++)
		if (a[k] == now)count++;
	if (count > length / 2)
		return now;
	else return -1;
}

int Question_223_13(int a[], int length) {
	int	*b,i;
	b = (int*)malloc(sizeof(int) * length);
	for (i = 0;i < length;i++)b[i] = 0;
	for (i = 0;i < length;i++) {
		if (a[i] > 0 && a[i] <=length) {
			b[a[i] - 1] = 1;
		}
	}
	for (i = 0;i < length;i++)
		if (b[i] == 0)break;
	return i + 1;
}

void Question_237_1(LinkList& L, int x) {
	LNode* p;
	if (L == NULL)return;
	if (L->data == x) {
		p = L;
		L = L->next;
		free(p);
		Question_237_1(L,x);
	}
	else
	{
		Question_237_1(L->next, x);
	}
}

void Question_237_1(LinkList& L, int s,int t) {
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

void Question_237_1_2(LinkList& L, int s, int t) {
	LinkList p = L->next, r=L, q;
	while (p) {
		if (p->data<t && p->data>s) {
			q = p;
			p = p->next;
			free(q);
		}
		else
		{
			r->next = p;
			r = p;
			p = p->next;
		}
	}
	r->next = NULL;
}

void Question_237_3(LinkList& L) {
	if (L->next) {
		Question_237_3(L->next);
	}
	printf("%d", L->data);
}

void Question_237_4(LinkList& L) {
	LinkList p, pre, minp, minpre;
	if (!L)return;
	p = L;pre = NULL;
	minp = p;minpre = pre;
	while (p) {
		if (p->data < minp->data) {
			minp = p;
			minpre = pre;
		}
		pre = p;
		p = p->next;
	}
	if (!minpre) {
		L = L->next;
		free(minp);
		return;
	}
	minpre->next = minp->next;
	free(minp);
}

void Question_237_6(LinkList& L) {
	LinkList p, pre, r, bottom;
	p = L->next;pre = bottom = L;
	while (p) {
		r = p->next;
		while (pre!=bottom) {
			if (pre->next->data > p->data) {
				p->next = pre->next;
				pre->next = p;
				break;
			}
			pre = pre->next;
		}
		if (pre == bottom) { bottom->next = p; bottom = p;}
		pre = L;
		p = r;
	}
	bottom->next = NULL;
}

void Question_237_15(LinkList& A, LinkList& B) {
	LinkList p = A->next, q = B->next, pre = A, temp;
	B->next = NULL;
	while (p&&q)
	{
		if (p->data == q->data) {
			temp = q;
			q = q->next;
			free(temp);
			pre = p;
			p = p->next;
		}
		else if(p->data<q->data)
		{
			temp = p;
			pre->next = p->next;
			p = p->next;
			free(temp);
		}
		else
		{
			temp = q;
			q = q->next;
			free(temp);
		}
	}
	if (!p)
		p = q;

	while (p)
	{
		temp = p;
		p = p->next;
		free(temp);
	}
	pre->next = NULL;
}

int Question_237_21(LinkList& L, int k) {
	int count=0;
	LinkList p = L->next,q=L->next;
	while (p)
	{
		if (count >= k) {
			q = q->next;
		}
		p = p->next;
		count++;
	}
	if (count < k)return 0;
	else return q->data;
}

void straightinsertsort(LinkList head)
{
	LinkList  s, p, pre;
	int t;
	if (head == 0 || head->next == 0)
		return;
	else {
		for (pre = head, p = head->next;p != 0;p = pre->next)
		{
			for (s = head;s != pre->next;s = s->next)
				if (s->data > p->data)
					break;
			if (s == pre->next)
				pre = p;
			else {
				pre->next = p->next;
				p->next = s->next;
				s->next = p;
				t = p->data;
				p->data = s->data;
				s->data = t;
			}
		}
	}
}


int main(){
	int arr[5] = { 5, 2, 3, 1, 4 };
	LinkList head;
	List_TailInsert_Arr(head, arr, 5);
	Print_List_Link(head);
	straightinsertsort(head);
	Print_List_Link(head);
}