#include<stdio.h>
#include"ALGraph.h"
#define MaxSize 100

void BFS(ALGraph G, char x,int flag[]) {
    int Queue[MaxSize],p;
    int front = 0, rear = 0;//frontָ����еĶ�ͷԪ�أ�rearָ���βԪ�صĺ���һλ
    int index_x = getVerIndex(G, x);
    if (index_x < 0)return;
    Queue[rear++] = index_x;//��ʼʱ���ڵ����
    while (front != rear) {//���Ӳ���ʱ����
        p = Queue[front++];//���Ӳ�����
        char c = G.vertices[p].data;
        if (!flag[p]) {
            printf("%c-", c);
            flag[p] = 1;
        }
        else continue;
        //for (int j = 0;j < G.vexnum;j++) {
        //    printf("%d ", flag[j]);
        //}
        //printf("\n");
        for (int i = FirstNeighbor(G, c);i != -1;i = NextNeighbor(G, c, G.vertices[i].data)) {
            if (!flag[i]) { 
                Queue[rear++] = i;
            }
        }
    }
}

void Scan_BFS(ALGraph G) {
    int flag[MaxSize];
    for (int i = 0;i < G.vexnum;i++)flag[i] = 0;
    for (int i = 0;i < G.vexnum;i++) {
        if (!flag[i])BFS(G, G.vertices[i].data, flag);
    }
}

void DFS(ALGraph G, char x, int flag[]) {
    int index_x = getVerIndex(G, x);
    if (index_x < 0)return;
    if (flag[index_x])return;
    flag[index_x] = 1;
    printf("%c-",x);
    for (int i = FirstNeighbor(G, x);i != -1;i = NextNeighbor(G, x, G.vertices[i].data)) {
        DFS(G, G.vertices[i].data, flag);
    }
}

void Scan_DFS(ALGraph G) {
    int flag[MaxSize];
    for (int i = 0;i < G.vexnum;i++)flag[i] = 0;
    for (int i = 0;i < G.vexnum;i++) {
        DFS(G, G.vertices[i].data, flag);
    }
}

void SimpleDFS(ALGraph G, char x, char y, int flag[], char path[], int& count) {
    int index_x = getVerIndex(G, x);
    if (flag[index_x])return;
    if (x == y) {
        for (int i = 0;i < count;i++)printf("%c-", path[i]);
        printf("%c\n", x);
        return;
    }
    for (int i = FirstNeighbor(G, x);i != -1;i = NextNeighbor(G, x, G.vertices[i].data)) {
        path[count++] = x;
        flag[index_x] = 1;
        SimpleDFS(G, G.vertices[i].data, y, flag, path, count);
        count--;
        flag[index_x] = 0;
    }
}

void SimplePath(ALGraph G, char x, char y) {//��ӡ�Ӷ���x������y�����м�·��
    int index_x, index_y;
    index_x = getVerIndex(G, x);
    index_y = getVerIndex(G, y);
    if (index_x < 0 || index_y < 0)return;  //��ͼ������x����y���˳�
    char path[MaxSize];                      //��ŵ�ǰ·��
    int count = 0;
    path[count++] = x;
    int flag[MaxSize];                      //��ŷ��ʱ��
    for (int i = 0;i < G.vexnum;i++)flag[i] = 0;
    flag[index_x] = 1;
    for (int i = FirstNeighbor(G, x);i != -1;i = NextNeighbor(G, x, G.vertices[i].data)) {
        SimpleDFS(G, G.vertices[i].data, y, flag, path, count);
    }
}

//void DFS_Non_RC(ALGraph G, int v) {
//    int w;                          //�������       
//    InitStack(S);                   //��ʼ��ջS
//    for (int i = 0;i < G.vexnum;i++)
//        visited[i] = FALSE;         //visitedΪ���ʱ������
//    Push(S, v);
//    visited[v] = TRUE;
//    while (!IsEmpty(S)) {
//        k = Pop(S);visit(k);        //��ջ������
//        for(w=FirstNeighbor(G,k);w>=0;w=NextNeighbor(G,k,w))
//            if (!visited[w]) {      //δ��ջ�Ķ����ջ
//                Push(S, w);
//                visited[w] = TRUE;  //��ֹ�ٴ���ջ
//            }
//    }
//}

//int main() {
//    char vexs[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
//    char edges[][2] = {
//        {'A', 'C'},
//        {'A', 'D'},
//        {'A', 'F'},
//        {'B', 'C'},
//        {'C', 'D'},
//        {'E', 'G'},
//        {'F', 'G'} 
//    };
//    ALGraph G;
//    int vexnum = sizeof(vexs);
//    int arcnum = sizeof(edges)/2;
//    init_graph(G, edges,vexs,vexnum,arcnum);
//    //Graph_print(G);
//    InsertVertex(G, 'N');
//    Graph_print(G);
//    /*char x, y;
//    x = 'A';
//    y = 'N';
//    printf("�Ƿ���ڱ�(%c,%c):%d\n", x, y, Adjacent(G, x, y));
//    char* neighbors=Neighbors(G,'A');
//    printf("%c���ھ���%s\n", x, neighbors);
//    free(neighbors);*/
//    /*DeleteVertex(G, 'G');
//    Graph_print(G);
//    AddEdge(G, 'B', 'E');
//    Graph_print(G);
//    RemoveEdge(G, 'A', 'H');
//    Graph_print(G);*/
//    //printf("%d\n", FirstNeighbor(G, 'N'));
//    /*printf("%d\n", NextNeighbor(G, 'A','D'));
//    printf("%d\n", NextNeighbor(G, 'A', 'C'));
//    printf("%d\n", NextNeighbor(G, 'A', 'F'));
//    printf("%d\n", NextNeighbor(G, 'A', 'H'));*/
//    /*printf("BFS:\n");
//    Scan_BFS(G);
//    printf("\nDFS:\n");
//    Scan_DFS(G);*/
//    SimplePath(G, 'A', 'B');
//}