#pragma once
#define MaxVertexNum 100
#include<malloc.h>
typedef struct ArcNode {
	int adjvex;
	struct ArcNode* next;
}ArcNode;
typedef struct VNode {
	char data;
	ArcNode* first;
}VNode,AdjList[MaxVertexNum];
typedef struct {
	AdjList vertices;
	int vexnum, arcnum;
}ALGraph;
int getIndex(char* vexs,int vexnum, char c) {
	for (int i = 0;i < vexnum;i++)
		if (vexs[i] == c)
			return i;
	return -1;
}

int getVerIndex(ALGraph G, char x) {
	int index_x = -1;
	for (int i = 0;i < G.vexnum;i++)
		if (G.vertices[i].data == x)
			index_x = i;
	return index_x;
}

void init_graph(ALGraph& G, char edges[][2], char* vexs, int vexnum, int arcnum) {
	G.vexnum = vexnum;
	G.arcnum = arcnum;
	ArcNode* N1 = NULL;
	ArcNode* N2 = NULL;
	for (int i = 0;i < G.vexnum;i++) {//初始化邻接表，为节点赋值
		G.vertices[i].data = vexs[i];
		G.vertices[i].first = NULL;
	}
	char c1, c2;
	ArcNode* p1, * p2;

	for (int i = 0;i < G.arcnum;i++) {
		c1 = edges[i][0];
		c2 = edges[i][1];
		N1 = (ArcNode*)malloc(sizeof(ArcNode) * 1);
		N2 = (ArcNode*)malloc(sizeof(ArcNode) * 1);
		N1->adjvex = getIndex(vexs, vexnum, c1);
		N2->adjvex = getIndex(vexs, vexnum, c2);
		p1 = G.vertices[N1->adjvex].first;
		p2 = G.vertices[N2->adjvex].first;
		if (!p1) {
			G.vertices[N1->adjvex].first = N2;
			N2->next = NULL;
		}
		else {
			while (p1->next)p1 = p1->next;
			p1->next = N2;
			N2->next = NULL;
		}
		if (!p2) {
			G.vertices[N2->adjvex].first = N1;
			N1->next = NULL;
		}
		else {
			while (p2->next)p2 = p2->next;
			p2->next = N1;
			N1->next = NULL;
		}
	}
}

bool Adjacent(ALGraph G, char x, char y) {
	ArcNode* p;
	int index_x = -1, index_y = -1;
	for (int i = 0;i < G.vexnum;i++) {
		if (G.vertices[i].data == x)index_x = i;
		if (G.vertices[i].data == y)index_y = i;
	}
	if (index_x >= 0) {
		p = G.vertices[index_x].first;
		while (p) {
			if (p->adjvex == index_y)return true;
			p = p->next;
		}
	}
	if (index_y >= 0) {
		p = G.vertices[index_y].first;
		while (p) {
			if (p->adjvex == index_x)return true;
			p = p->next;
		}
	}
	return false;
}
char* Neighbors(ALGraph G, char x) {
	char* neighbors = (char*)malloc(sizeof(char) * G.vexnum);
	int index_x = -1;
	for (int i = 0;i < G.vexnum;i++) {
		if (G.vertices[i].data == x)
			index_x = i;
	}
	if (index_x >= 0) {
		ArcNode* p = G.vertices[index_x].first;
		int i = 0;
		while (p) {
			neighbors[i++] = G.vertices[p->adjvex].data;
			p = p->next;
		}
		neighbors[i] = '\0';
	}
	return neighbors;
}
bool InsertVertex(ALGraph &G, char x) {
	if (getVerIndex(G, x) >= 0)return true;
	if (G.vexnum + 1 > MaxVertexNum)return false;
	G.vertices[G.vexnum].data = x;
	G.vertices[G.vexnum].first = NULL;
	G.vexnum++;
	return true;
}

void Graph_print(ALGraph G) {
	ArcNode* p;
	printf("vex:%d,arc:%d\n", G.vexnum, G.arcnum);
	for (int i = 0;i < G.vexnum;i++) {
		p = G.vertices[i].first;
		printf("%c:->", G.vertices[i].data);
		while (p) {
			printf("%c->", G.vertices[p->adjvex]);
			p = p->next;
		}
		printf("||\n");
	}
}

bool DeleteVertex(ALGraph& G, char x) {
	int index_x = -1;
	for (int i = 0;i < G.vexnum;i++) {
		if (G.vertices[i].data == x)
			index_x = i;
	}
	if (index_x < 0)return false;
	ArcNode* p, * temp,* pre;
	p = G.vertices[index_x].first;
	for (int i = 0;i < G.vexnum;i++) {
		pre = G.vertices[i].first;
		if (!pre)
			continue;
		if (pre->adjvex == index_x) {
			G.vertices[i].first = pre->next;
			free(pre);
			continue;
		}
		p = pre->next;
		while (p) {
			if (p->adjvex == index_x) {
				temp = p;
				pre->next = p->next;
				free(temp);
				break;
			}
			pre = p;
			p = p->next;
		}
	}
	for (int i = 0;i < G.vexnum;i++) {
		p = G.vertices[i].first;
		while (p) {
			if (p->adjvex > index_x)p->adjvex--;
			p = p->next;
		}
	}
	p = G.vertices[index_x].first;
	while (p) {
		temp = p;
		p = p->next;
		free(temp);
	}
	for (int i = index_x;i < G.vexnum-1;i++) {
		G.vertices[i].data = G.vertices[i + 1].data;
		G.vertices[i].first = G.vertices[i + 1].first;
	}
	G.vexnum--;
	return true;
}

bool AddEdge(ALGraph& G, char x, char y) {
	if (!(InsertVertex(G, x) && InsertVertex(G, y)))return false;
	if (Adjacent(G, x, y))return true;
	int index_x, index_y;
	ArcNode* p;
	index_x = getVerIndex(G, x);
	index_y = getVerIndex(G, y);
	p = G.vertices[index_x].first;
	while (p&&p->next) {
		if (p->next->adjvex == index_y)break;
		p = p->next;
	}
	if (!p) {
		ArcNode* N = (ArcNode*)malloc(sizeof(ArcNode));
		N->adjvex = index_y;
		N->next = NULL;
		G.vertices[index_x].first = N;
	}
	else if(!p->next)
	{
		ArcNode* N = (ArcNode*)malloc(sizeof(ArcNode));
		N->adjvex = index_y;
		N->next = NULL;
		p->next = N;
	}

	p = G.vertices[index_y].first;
	while (p && p->next) {
		if (p->next->adjvex == index_x)break;
		p = p->next;
	}
	if (!p) {
		ArcNode* N = (ArcNode*)malloc(sizeof(ArcNode));
		N->adjvex = index_x;
		N->next = NULL;
		G.vertices[index_y].first = N;
	}
	else if (!p->next)
	{
		ArcNode* N = (ArcNode*)malloc(sizeof(ArcNode));
		N->adjvex = index_x;
		N->next = NULL;
		p->next = N;
	}
	G.arcnum++;
	return true;
}
void RemoveEdge(ALGraph& G, char x, char y) {
	int index_x, index_y;
	ArcNode* p, * pre, * temp;
	index_x = getVerIndex(G, x);
	index_y = getVerIndex(G, y);
	if (index_x < 0 || index_y < 0)return;
	pre = G.vertices[index_x].first;
	if (pre&&pre->adjvex==index_y) {
		G.vertices[index_x].first = pre->next;
		free(pre);
	}
	else if(pre)
	{
		p = pre->next;
		while (p) {
			if (p->adjvex == index_y) {
				temp = p;
				pre->next = p->next;
				free(temp);
				break;
			}
			pre = p;
			p = p->next;
		}
	}
	pre = G.vertices[index_y].first;
	if (pre && pre->adjvex == index_x) {
		G.vertices[index_y].first = pre->next;
		free(pre);
	}
	else if (pre)
	{
		p = pre->next;
		while (p) {
			if (p->adjvex == index_x) {
				temp = p;
				pre->next = p->next;
				free(temp);
				break;
			}
			pre = p;
			p = p->next;
		}
	}
}
int FirstNeighbor(ALGraph G, char x) {
	int index = getVerIndex(G, x);
	if (index >= 0 && G.vertices[index].first)index = G.vertices[index].first->adjvex;
	else index = -1;
	return index;
}
int NextNeighbor(ALGraph G, char x, char y) {
	if (!Adjacent(G, x, y))return -1;
	int index_x, index_y;
	ArcNode* p, * pre, * temp;
	index_x = getVerIndex(G, x);
	index_y = getVerIndex(G, y);
	p = G.vertices[index_x].first;
	while (p) {
		if (p->adjvex == index_y)
			return p->next ? p->next->adjvex : -1;
		p = p->next;
	}
	return -1;
}