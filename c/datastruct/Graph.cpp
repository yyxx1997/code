#include<stdio.h>
#include"ALGraph.h"
#define MaxSize 100

void BFS(ALGraph G, char x,int flag[]) {
    int Queue[MaxSize],p;
    int front = 0, rear = 0;//front指向队列的队头元素，rear指向队尾元素的后面一位
    int index_x = getVerIndex(G, x);
    if (index_x < 0)return;
    Queue[rear++] = index_x;//开始时根节点入队
    while (front != rear) {//当队不空时运行
        p = Queue[front++];//出队并访问
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

void SimplePath(ALGraph G, char x, char y) {//打印从顶点x到顶点y的所有简单路径
    int index_x, index_y;
    index_x = getVerIndex(G, x);
    index_y = getVerIndex(G, y);
    if (index_x < 0 || index_y < 0)return;  //若图不存在x或者y则退出
    char path[MaxSize];                      //存放当前路径
    int count = 0;
    path[count++] = x;
    int flag[MaxSize];                      //存放访问标记
    for (int i = 0;i < G.vexnum;i++)flag[i] = 0;
    flag[index_x] = 1;
    for (int i = FirstNeighbor(G, x);i != -1;i = NextNeighbor(G, x, G.vertices[i].data)) {
        SimpleDFS(G, G.vertices[i].data, y, flag, path, count);
    }
}

//void DFS_Non_RC(ALGraph G, int v) {
//    int w;                          //顶点序号       
//    InitStack(S);                   //初始化栈S
//    for (int i = 0;i < G.vexnum;i++)
//        visited[i] = FALSE;         //visited为访问标记数组
//    Push(S, v);
//    visited[v] = TRUE;
//    while (!IsEmpty(S)) {
//        k = Pop(S);visit(k);        //退栈并访问
//        for(w=FirstNeighbor(G,k);w>=0;w=NextNeighbor(G,k,w))
//            if (!visited[w]) {      //未进栈的顶点进栈
//                Push(S, w);
//                visited[w] = TRUE;  //防止再次入栈
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
//    printf("是否存在边(%c,%c):%d\n", x, y, Adjacent(G, x, y));
//    char* neighbors=Neighbors(G,'A');
//    printf("%c的邻居是%s\n", x, neighbors);
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