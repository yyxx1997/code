# Dijkstra算法

def solve(times, n, k):
    states = [[float('inf'), None] for _ in range(n+1)]
    edges = {}
    for s, d, l in times:
        if s in edges:
            edges[s][d] = l
        else:
            edges[s] = {d: l}
    states[k][0] = 0
    states[k][1] = 0
    visited = set()
    last = -1
    while last != len(visited):
        last = len(visited)
        minv = float('inf')
        for i in range(1, n+1):
            if i not in visited:
                if minv > states[i][0]:
                    minv = states[i][0]
                    minindex = i
        visited.add(minindex)
        if minindex not in edges:
            continue
        for d, l in edges[minindex].items():
            if states[d][0] > states[minindex][0] + l:
                states[d][0] = states[minindex][0] + l
                states[d][1] = minindex
    maxlatency = max(i[0] for i in states[1:])
    return maxlatency if maxlatency < float('inf') else -1

times = [[2,1,1],[2,3,1],[3,4,1]]
n = 4
k = 2
print(solve(times, n, k))

times = [[1,2,1]]
n = 2
k = 1
print(solve(times, n, k))

times = [[1,2,1]]
n = 2
k = 2
print(solve(times, n, k))


# 基于队列优化的Bellman Ford算法
from collections import deque

def solve(times, n, k):
    inf = float('inf')
    states = [inf] * n
    edges = {}
    for s, d, l in times:
        s, d = s-1, d-1
        if s in edges:
            edges[s][d] = l
        else:
            edges[s] = {d: l}
    states[k-1] = 0
    queue = deque()
    queue.append(k-1)
    while queue:
        s = queue.popleft()
        if s not in edges:
            continue
        for d, l in edges[s].items():
            if states[s] + l < states[d]:
                states[d] = states[s] + l
                queue.append(d)

    maxlatency = max(states)
    return maxlatency if maxlatency < inf else -1

times = [[2,1,1],[2,3,1],[3,4,1]]
n = 4
k = 2
print(solve(times, n, k))

times = [[1,2,1]]
n = 2
k = 1
print(solve(times, n, k))

times = [[1,2,1]]
n = 2
k = 2
print(solve(times, n, k))

# 普通的动态规划 bellman ford + 提前终止
def solve(n, flights, src, dst, k):
    inf = float('inf')
    k = min(k, n)
    states = [[inf] * n for _ in range(k+2)]
    states[0][src] = 0
    final = 1
    for i in range(1, k+2):
        final = i
        flag = False
        for j in range(n):
            states[i][j] = states[i-1][j]
        for s, d, l in flights:
            if states[i-1][s] + l < states[i][d]:
                states[i][d] = states[i-1][s] + l
                flag = True
        if not flag:
            break
    maxlatency = states[min(final, k+1)][dst]
    return maxlatency if maxlatency < inf else -1

n = 3
flights = [[0,1,100],[1,2,100],[0,2,500]]
src = 0
dst = 2
k = 1
print(solve(n, flights, src, dst, k))

n = 3
flights = [[0,1,100],[1,2,100],[0,2,500]]
src = 0
dst = 2
k = 0
print(solve(n, flights, src, dst, k))