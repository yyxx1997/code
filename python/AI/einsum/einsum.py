import numpy as np
import numpy
# 2*4
A = np.matrix([
    [1,2,3,4],
    [2,3,4,5]
    ])
# 4*3
B = np.matrix([
    [1,2,3],
    [2,3,4],
    [3,4,5],
    [4,5,6]
    ])

M = np.einsum("ik, kj -> ijk", A, B)
print(M,end="\n")

M = np.empty((2, 3, 4))
for i in range(2):
    for j in range(3):
        for k in range(4):
            M[i, j, k] = A[i, k] * B[k, j]
print(M,end="\n")

M = np.einsum("ik, kj -> kij", A, B)
print(M,end="\n")

for i in range(2):
    for j in range(3):
        for k in range(4):
            M[k, i, j] = A[i, k] * B[k, j]
print(M,end="\n")

# 单操作数
x = np.random.rand(2, 3)
m = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
## 迹
M = np.empty(3)
for i in range(3):
    M[i]=m[i][i]
print(M)
M=np.einsum("ii -> i", m)
print(M)


# 如果看不懂就展开成循环

## 转置
M = np.empty((3,2))
for i in range(2):
    for j in range(3):
        M[j, i] = x[i, j]
print(M)
M=np.einsum("ij -> ji", x)
print(M)


## 求和
np.einsum("ij -> i", x) # 对行求和
np.einsum("ij -> j", x) #对列求和
np.einsum("ij -> ", x) # 全部求和

# 双操作数
a = np.random.rand(5)
b = np.random.rand(3)
c = np.random.rand(5)
## 内积
np.einsum("i, i ->", a, c)

## 外积
np.einsum("i, j -> ij", a, b) # (5, 3)

## 矩阵乘
y = np.random.rand(3, 5)
np.einsum("ik, kj -> ij", x, y)

# 多操作数
z = np.random.rand(5, 2)
np.einsum("ij, jk, kl -> il", x, y, z)

# 广播写法
A = numpy.random.rand(2, 3, 4, 2)
B = numpy.random.rand(2, 3, 4, 2)

M=np.einsum("nqhd,nkhd->nhqk", A,B) # （2, 4, 3 ,3)
print(M)

A=A.transpose(0,2,1,3) # nqhd -> nhqd
B=B.transpose(0,2,1,3) # nkhd -> nhkd
M=np.einsum('nhqd, nhkd->nhqk', A,B) # （2, 4, 3 ,3)
np.einsum('...qd, ...kd->...qk', A,B) # （2, 4, 3 ,3)
print(M)

# import torch 

# a=torch.rand(2,3,8)
# b=torch.rand(2,3,8)

# a=a.view(2,3,4,2)
# b=b.view(2,3,4,2)

# c=a.permute(0, 2, 1, 3)
# d=a.reshape(2, 4, 3, 2)
# e=a.transpose(1,2)
# f=a.view(2,4,3,2)
# print(a.sum(-1))
# print("以顺序后延的形式重排：")
# print(d.sum(-1))
# print(f.sum(-1))
# print("以转置的方式重排：")
# print(c.sum(-1))
# print(e.sum(-1))

