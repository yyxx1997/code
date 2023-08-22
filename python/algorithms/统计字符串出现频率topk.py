import heapq

def topKstrings(strings, k):
    # write code here
    dct = {}
    for i in strings:
        dct[i] = dct.get(i, 0) + 1
    h = []
    for key, v in dct.items():
        if len(h) < k:
            heapq.heappush(h, [v, key])
        elif v > heapq.nsmallest(1, h)[0][0]:
            heapq.heapreplace(h, [v, key])
    return [[i[1], i[0]] for i in heapq.nlargest(k, h)[::-1]]


s, k = ["123","123","231","32"], 2
print(topKstrings(s, 3))