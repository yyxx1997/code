from collections import deque

# kahn拓扑排序算法
def solve(numCourses, prerequisites):
    states = [0] * numCourses
    edges = {}
    for e, s in prerequisites:
        states[e] += 1
        if s not in edges:
            edges[s] = set()
        edges[s].add(e)
    queue = deque()
    for i, d in enumerate(states):
        if d == 0:
            queue.append(i)
    ans = []
    while queue:
        s = queue.popleft()
        ans.append(s)
        for e in edges.get(s, []):
            states[e] -= 1
            if states[e] == 0:
                queue.append(e)
    return ans if len(ans) == numCourses else []

numCourses = 4
prerequisites = [[1,0],[2,0],[3,1],[3,2]]
print(solve(numCourses, prerequisites))
