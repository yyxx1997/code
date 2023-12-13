class UnionFind:

    def __init__(self, n) -> None:
        self.root = [i for i in range(n)]
        self.rank = [1 for _ in range(n)]

    def find(self, x):
        if x == self.root[x]:
            return x
        self.root[x] = self.find(self.root[x])
        return self.root[x]

    def union(self, x, y):
        rootX = self.find(x)
        rootY = self.find(y)
        if rootX != rootY:
            if self.rank[rootX] > self.rank[rootY]:
                self.root[rootY] = rootX
            elif self.rank[rootX] < self.rank[rootY]:
                self.root[rootX] = rootY
            else:
                self.root[rootY] = rootX
                self.rank[rootX] += 1

    def connected(self, x, y):
        return self.find(x) == self.find(y)

# Kruskal算法
def solve(points):
    n = len(points)
    candidates = []
    for i in range(n):
        for j in range(i+1, n):
            distance = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1])
            candidates.append((i, j, distance))
    candidates.sort(key=lambda x: x[-1])
    uf = UnionFind(n)
    total = 0
    ans = 0
    for i, j, w in candidates:
        if not uf.connected(i, j):
            ans += w
            uf.union(i, j)
            total += 1
        if total == n-1:
            break
    return ans

points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
print(solve(points))

points = [[3,12],[-2,5],[-4,1]]
print(solve(points))

points = [[0,0],[1,1],[1,0],[-1,1]]
print(solve(points))

points = [[-1000000,-1000000],[1000000,1000000]]
print(solve(points))

points = [[0,0]]
print(solve(points))

# Prim算法
def solve(points):
    n = len(points)
    ans = 0
    current = [False] * n
    cnt = 1
    for i in range(1, n):
        current[i] = abs(points[0][0] - points[i][0]) + abs(points[0][1] - points[i][1])
    while cnt != n:
        minv = float('inf')
        for i in range(n):
            if current[i]:
                if minv > current[i]:
                    minv = current[i]
                    minindex = i
        cnt += 1
        ans += current[minindex]
        current[minindex] = False
        for i in range(n):
            if current[i]:
                new = abs(points[minindex][0] - points[i][0]) + abs(points[minindex][1] - points[i][1])
                if current[i] > new:
                    current[i] = new
    return ans

points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
print(solve(points))

points = [[3,12],[-2,5],[-4,1]]
print(solve(points))

points = [[0,0],[1,1],[1,0],[-1,1]]
print(solve(points))

points = [[-1000000,-1000000],[1000000,1000000]]
print(solve(points))

points = [[0,0]]
print(solve(points))