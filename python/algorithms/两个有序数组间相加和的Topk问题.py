# 1 2 3 4 5
# 3 5 7 9 11

# 链接：https://www.nowcoder.com/questionTerminal/7201cacf73e7495aa5f88b223bbbf6d1?toCommentId=3518525
# 来源：牛客网

# 给定两个有序数组arr1和arr2，再给定一个整数k，返回来自arr1和arr2的两个数相加和最大的前k个，两个数必须分别来自两个数组
# 按照降序输出
# [要求]
# 时间复杂度为O(klogk)

import sys
import heapq as hq

def topksum(a1, a2, k):
    visited=set()
    m, n = len(a1), len(a2)
    visited.add((m-1,n-1))
    que=[(-a1[m-1]-a2[n-1], m-1,n-1)]#分别是值，ij坐标
    res=[]
    while len(res)<k:
        # 先取当前老大
        val,i,j=hq.heappop(que)
        res.append(val)
        # 加进新的候选人
        if i-1>=0 and (i-1,j) not in visited:
            hq.heappush(que, (-a1[i-1]-a2[j] ,i-1,j))
            visited.add( (i-1,j) )
        if j-1>=0 and (i,j-1) not in visited:
            hq.heappush(que, (-a1[i]-a2[j-1] ,i,j-1))
            visited.add( (i,j-1) )
    # 取反输出
    return " ".join([str(-i) for i in res])

arr1 = [1,2,3,4,5]
arr2 = [3,5,7,9,11]
print(topksum(arr1,arr2,5))